通过 `union` 简单模拟 **SSO：Small String Optimization，小字符串优化**。

SSO 的核心思想是：

> 字符串较短时，不申请堆内存，直接把字符存在对象内部；字符串较长时，再申请堆内存。

这样可以减少频繁 `new/delete` 带来的开销。

---

# 一、类的整体结构

题目给出的类是：

```cpp
class String {
public:
    String(const char * pstr);
    ~String();
    char & operator[](size_t idx);

    friend
    ostream & operator<<(ostream & os,const String & rhs);
private:
    union Buffer{
        char * _pointer;
        char _local[16];
    };

    size_t _size;
    size_t _capacity;
    Buffer _buffer;
};
```

其中最关键的是这个 `union`：

```cpp
union Buffer {
    char * _pointer;
    char _local[16];
};
```

`union` 的特点是：所有成员共用同一块内存。

也就是说，`_pointer` 和 `_local` 不能同时有效。对象要么使用 `_local` 存短字符串，要么使用 `_pointer` 指向堆空间存长字符串。

---

# 二、为什么 `_local[16]` 最多只能存 15 个字符？

C 风格字符串必须以 `'\0'` 结尾。

例如：

```cpp
"hello"
```

实际存储是：

```cpp
'h' 'e' 'l' 'l' 'o' '\0'
```

虽然字符串长度是 5，但实际需要 6 个字符空间。

所以：

```cpp
char _local[16];
```

最多只能存：

```cpp
15 个有效字符 + 1 个 '\0'
```

因此我们可以约定：

```cpp
_size <= 15
```

使用 `_local`；

```cpp
_size > 15
```

使用堆空间 `_pointer`。

---

# 三、完整代码，带详细注释

这版代码补充了：

1. 构造函数
2. 析构函数
3. `operator[]`
4. `operator<<`
5. `size()`
6. `capacity()`
7. `c_str()`
8. `usingLocal()`，用于验证是否使用 SSO
9. 拷贝构造函数
10. 赋值运算符

虽然题目没有要求拷贝构造和赋值运算符，但为了代码更完整，建议补上。

```cpp
#include <iostream>
#include <cstring>
#include <stdexcept>

using std::cout;
using std::endl;
using std::ostream;
using std::out_of_range;

class String {
public:
    /*
        构造函数：
        根据传入字符串的长度，决定使用本地数组 _local，
        还是使用堆空间 _pointer。

        SSO 思想：
        - 短字符串：直接存在对象内部的 _local[16] 中
        - 长字符串：申请堆内存，由 _pointer 指向
    */
    String(const char * pstr)
    : _size(strlen(pstr))
    {
        /*
            _local[16] 最多存 15 个有效字符，
            因为最后一个位置要留给字符串结束符 '\0'。

            因此：
            - _size <= 15 时，使用 _local
            - _size > 15 时，使用 _pointer
        */
        if (_size <= 15) {
            /*
                这里约定：
                _capacity == 15 表示当前对象使用 _local 存储。

                _capacity 表示不包含 '\0' 的最大可容纳字符数。
            */
            _capacity = 15;

            /*
                把 pstr 中的内容复制到本地数组中。
                strcpy 会连同 '\0' 一起复制。
            */
            strcpy(_buffer._local, pstr);
        } else {
            /*
                长字符串无法放进 _local[16]，
                因此需要在堆上申请空间。

                这里简单处理：
                容量刚好等于字符串长度。
                例如长度为 16，就申请 17 个 char，
                其中 16 个放有效字符，最后 1 个放 '\0'。
            */
            _capacity = _size;

            /*
                new char[_capacity + 1]：
                +1 是为了存放 '\0'。

                后面的 () 会把数组初始化为 0，
                虽然后面 strcpy 会覆盖内容，
                但这样写比较安全。
            */
            _buffer._pointer = new char[_capacity + 1]();

            /*
                把字符串内容复制到堆空间中。
            */
            strcpy(_buffer._pointer, pstr);
        }
    }

    /*
        拷贝构造函数：
        用一个已有的 String 对象初始化新对象。

        例如：
            String s1("hello");
            String s2 = s1;

        如果原对象使用 _local，新对象也使用自己的 _local。
        如果原对象使用 _pointer，新对象必须重新申请堆空间，
        不能直接拷贝指针地址，否则会出现浅拷贝问题。
    */
    String(const String & rhs)
    : _size(rhs._size)
    , _capacity(rhs._capacity)
    {
        if (rhs.usingLocal()) {
            /*
                rhs 使用本地数组，
                当前对象也使用自己的本地数组。
            */
            strcpy(_buffer._local, rhs._buffer._local);
        } else {
            /*
                rhs 使用堆空间，
                当前对象需要重新申请一块堆空间，
                然后复制字符串内容。
            */
            _buffer._pointer = new char[_capacity + 1]();
            strcpy(_buffer._pointer, rhs._buffer._pointer);
        }
    }

    /*
        赋值运算符：
        用一个已有对象给另一个已经存在的对象赋值。

        例如：
            String s1("hello");
            String s2("world");
            s2 = s1;

        注意：
        赋值运算符要考虑三个问题：
        1. 自赋值：s1 = s1;
        2. 原对象如果使用堆空间，需要先释放旧空间
        3. 根据 rhs 的存储方式重新复制内容
    */
    String & operator=(const String & rhs) {
        /*
            防止自赋值。

            如果没有这个判断，s1 = s1 时，
            可能先 delete 掉自己的堆空间，
            后面又从已经释放的空间里读取数据。
        */
        if (this != &rhs) {
            /*
                如果当前对象原来使用的是堆空间，
                赋新值之前要先释放旧的堆空间，
                防止内存泄漏。
            */
            if (!usingLocal()) {
                delete [] _buffer._pointer;
                _buffer._pointer = nullptr;
            }

            /*
                复制基本信息。
            */
            _size = rhs._size;
            _capacity = rhs._capacity;

            /*
                根据 rhs 的存储方式进行复制。
            */
            if (rhs.usingLocal()) {
                strcpy(_buffer._local, rhs._buffer._local);
            } else {
                _buffer._pointer = new char[_capacity + 1]();
                strcpy(_buffer._pointer, rhs._buffer._pointer);
            }
        }

        /*
            返回当前对象本身，支持连续赋值：

                s3 = s2 = s1;
        */
        return *this;
    }

    /*
        析构函数：
        对象生命周期结束时自动调用。

        如果当前对象使用堆空间，则需要 delete[]。
        如果使用 _local，则不需要手动释放。
    */
    ~String() {
        if (!usingLocal()) {
            delete [] _buffer._pointer;
            _buffer._pointer = nullptr;
        }
    }

    /*
        下标访问运算符：
        允许像数组一样访问和修改字符。

        例如：
            String s("hello");
            s[0] = 'H';

        返回 char&，所以既可以读，也可以写。
    */
    char & operator[](size_t idx) {
        /*
            做一个边界检查。
            idx >= _size 表示越界。

            注意：
            这里不允许访问 '\0' 的位置。
            如果想允许访问 '\0'，判断可以改成 idx > _size。
        */
        if (idx >= _size) {
            throw out_of_range("String subscript out of range");
        }

        if (usingLocal()) {
            return _buffer._local[idx];
        } else {
            return _buffer._pointer[idx];
        }
    }

    /*
        const 版本的 operator[]：
        当对象是 const String 时，也可以通过下标读取字符。

        例如：
            const String s("hello");
            cout << s[0] << endl;

        返回 const char&，只能读，不能改。
    */
    const char & operator[](size_t idx) const {
        if (idx >= _size) {
            throw out_of_range("String subscript out of range");
        }

        if (usingLocal()) {
            return _buffer._local[idx];
        } else {
            return _buffer._pointer[idx];
        }
    }

    /*
        返回字符串长度，不包含 '\0'。
    */
    size_t size() const {
        return _size;
    }

    /*
        返回当前容量，不包含 '\0'。

        在这个简单实现中：
        - 短字符串容量固定为 15
        - 长字符串容量等于字符串长度
    */
    size_t capacity() const {
        return _capacity;
    }

    /*
        判断当前是否使用 _local 存储。

        这是我们自己约定的判断规则：
        - _capacity <= 15：使用 _local
        - _capacity > 15：使用 _pointer

        因为 _local[16] 最多能存 15 个有效字符。
    */
    bool usingLocal() const {
        return _capacity <= 15;
    }

    /*
        返回 C 风格字符串指针。

        这样可以统一拿到字符串内容，
        不需要每次在外面判断使用的是 _local 还是 _pointer。
    */
    const char * c_str() const {
        if (usingLocal()) {
            return _buffer._local;
        } else {
            return _buffer._pointer;
        }
    }

    /*
        输出运算符重载。
        让 String 对象可以直接用 cout 输出。

        例如：
            String s("hello");
            cout << s << endl;
    */
    friend
    ostream & operator<<(ostream & os, const String & rhs);

private:
    /*
        union 联合体：
        _pointer 和 _local 共用同一块内存。

        使用场景：
        1. 短字符串时：
            使用 _local[16] 存储字符内容。
        2. 长字符串时：
            使用 _pointer 指向堆空间。

        注意：
        union 里同一时刻只能认为一个成员是有效的。
    */
    union Buffer {
        char * _pointer;
        char _local[16];
    };

    /*
        字符串长度，不包含 '\0'。
    */
    size_t _size;

    /*
        当前容量，不包含 '\0'。

        本实现中还用 _capacity 来判断当前存储方式：
        - _capacity <= 15：使用 _local
        - _capacity > 15：使用 _pointer
    */
    size_t _capacity;

    /*
        实际存储区域。
        可能是本地数组，也可能是堆指针。
    */
    Buffer _buffer;
};

/*
    operator<< 的实现。

    这里直接调用 c_str()，
    避免重复判断 usingLocal()。
*/
ostream & operator<<(ostream & os, const String & rhs) {
    os << rhs.c_str();
    return os;
}
```

---

# 四、测试代码

```cpp
void test0() {
    String str1("hello");
    String str2("hello,world!!!!!");

    cout << "===== 初始状态 =====" << endl;
    cout << "str1 = " << str1 << endl;
    cout << "str1.size() = " << str1.size() << endl;
    cout << "str1.capacity() = " << str1.capacity() << endl;
    cout << "str1.usingLocal() = " << str1.usingLocal() << endl;

    cout << endl;

    cout << "str2 = " << str2 << endl;
    cout << "str2.size() = " << str2.size() << endl;
    cout << "str2.capacity() = " << str2.capacity() << endl;
    cout << "str2.usingLocal() = " << str2.usingLocal() << endl;

    cout << endl;

    cout << "===== 测试 operator[] 修改字符 =====" << endl;
    str1[0] = 'H';
    str2[0] = 'H';

    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;

    cout << endl;

    cout << "===== 测试拷贝构造 =====" << endl;
    String str3 = str1;
    String str4 = str2;

    cout << "str3 = " << str3 << endl;
    cout << "str3.usingLocal() = " << str3.usingLocal() << endl;

    cout << "str4 = " << str4 << endl;
    cout << "str4.usingLocal() = " << str4.usingLocal() << endl;

    cout << endl;

    cout << "===== 测试赋值运算符 =====" << endl;
    String str5("short");
    String str6("this is a very long string");

    cout << "赋值前：" << endl;
    cout << "str5 = " << str5 << endl;
    cout << "str6 = " << str6 << endl;

    str5 = str2;
    str6 = str1;

    cout << "赋值后：" << endl;
    cout << "str5 = " << str5 << endl;
    cout << "str5.usingLocal() = " << str5.usingLocal() << endl;

    cout << "str6 = " << str6 << endl;
    cout << "str6.usingLocal() = " << str6.usingLocal() << endl;

    cout << endl;

    cout << "===== 测试自赋值 =====" << endl;
    str5 = str5;
    cout << "str5 = " << str5 << endl;
}

int main() {
    test0();
    return 0;
}
```

---

# 五、预期输出示例

注意：`bool` 默认会输出 `0` 或 `1`。

```text
===== 初始状态 =====
str1 = hello
str1.size() = 5
str1.capacity() = 15
str1.usingLocal() = 1

str2 = hello,world!!!!!
str2.size() = 16
str2.capacity() = 16
str2.usingLocal() = 0

===== 测试 operator[] 修改字符 =====
str1 = Hello
str2 = Hello,world!!!!!

===== 测试拷贝构造 =====
str3 = Hello
str3.usingLocal() = 1
str4 = Hello,world!!!!!
str4.usingLocal() = 0

===== 测试赋值运算符 =====
赋值前：
str5 = short
str6 = this is a very long string
赋值后：
str5 = Hello,world!!!!!
str5.usingLocal() = 0
str6 = Hello
str6.usingLocal() = 1

===== 测试自赋值 =====
str5 = Hello,world!!!!!
```

---

# 六、为什么一定要写拷贝构造和赋值运算符？

因为类中有裸指针：

```cpp
char * _pointer;
```

只要一个类自己管理堆内存，通常就要考虑：

```cpp
析构函数
拷贝构造函数
赋值运算符
```

也就是常说的 **Rule of Three**。

如果不写拷贝构造函数，编译器默认生成的拷贝构造函数只会做浅拷贝。

例如：

```cpp
String s1("hello,world!!!!!");
String s2 = s1;
```

如果是浅拷贝，那么 `s1._buffer._pointer` 和 `s2._buffer._pointer` 会指向同一块堆空间。

这会导致两个严重问题：

1. 修改 `s2` 可能影响 `s1`
2. 析构时同一块空间被 `delete[]` 两次，程序可能崩溃

所以长字符串一定要深拷贝：

```cpp
_buffer._pointer = new char[_capacity + 1]();
strcpy(_buffer._pointer, rhs._buffer._pointer);
```

---

# 七、为什么用 `_capacity <= 15` 判断是否使用本地数组？

因为我们自己设计了一个约定：

```cpp
_capacity <= 15
```

表示使用 `_local`；

```cpp
_capacity > 15
```

表示使用 `_pointer`。

在构造时我们保证：

```cpp
if (_size <= 15) {
    _capacity = 15;
    strcpy(_buffer._local, pstr);
} else {
    _capacity = _size;
    _buffer._pointer = new char[_capacity + 1]();
    strcpy(_buffer._pointer, pstr);
}
```

所以后面的析构、输出、下标访问，都可以根据这个规则判断当前到底该用哪个成员。

---

# 八、`str2("hello,world!!!!!")` 为什么是长字符串？

数一下：

```text
hello,world!!!!!
```

字符数量是：

```text
hello       5
,           1
world       5
!!!!!       5
总计        16
```

`_local[16]` 只能存 15 个有效字符，还要留 1 个位置给 `'\0'`。

所以长度为 16 的 `"hello,world!!!!!"` 不能放进 `_local[16]`，必须使用堆空间。

---

# 九、可以更直观地看对象内部状态

你也可以把测试写得更清楚一点：

```cpp
void printInfo(const String & s, const char * name) {
    cout << name << " = " << s << endl;
    cout << name << ".size() = " << s.size() << endl;
    cout << name << ".capacity() = " << s.capacity() << endl;
    cout << name << ".usingLocal() = " << s.usingLocal() << endl;
    cout << endl;
}

void test1() {
    String s1("123456789012345");
    String s2("1234567890123456");

    printInfo(s1, "s1");
    printInfo(s2, "s2");
}
```

结果会看到：

```text
s1 = 123456789012345
s1.size() = 15
s1.capacity() = 15
s1.usingLocal() = 1

s2 = 1234567890123456
s2.size() = 16
s2.capacity() = 16
s2.usingLocal() = 0
```

这正好验证了 SSO 的边界：

```cpp
长度 <= 15：本地数组
长度 > 15：堆空间
```

---

# 十、最终你可以这样理解这个类

这个 `String` 对象内部大概是这样：

短字符串：

```cpp
String s("hello");
```

对象内部：

```text
_size = 5
_capacity = 15
_buffer._local = "hello"
```

长字符串：

```cpp
String s("hello,world!!!!!");
```

对象内部：

```text
_size = 16
_capacity = 16
_buffer._pointer ---> 堆空间："hello,world!!!!!"
```

所以析构时：

```cpp
if (_capacity > 15) {
    delete [] _buffer._pointer;
}
```

短字符串不需要释放；长字符串才需要释放。

---
