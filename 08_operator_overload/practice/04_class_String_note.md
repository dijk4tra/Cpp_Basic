重点是理解 **C++ 中对象如何管理动态内存**。
---
# 一、这个 String 类要解决什么问题？

C 语言字符串本质上是一个字符数组，例如：

```cpp
char str[] = "hello";
```

它在内存中大概长这样：

```cpp
'h' 'e' 'l' 'l' 'o' '\0'
```

最后的 `'\0'` 是字符串结束标志。

你的 `String` 类内部只有一个成员：

```cpp
char *_pstr;
```

也就是说，这个类要自己完成：

```cpp
申请内存
复制字符串
释放内存
拼接字符串
比较字符串
访问字符
```

所以它本质上是在模拟标准库中的 `std::string` 的一部分功能。

---

# 二、为什么必须深拷贝？

假设有下面的错误写法：

```cpp
String::String(const String &rhs)
{
    _pstr = rhs._pstr;
}
```

这叫**浅拷贝**。

问题是两个对象会指向同一块内存：

```cpp
String s1("hello");
String s2(s1);
```

内存关系会变成：

```cpp
s1._pstr ─┐
          ├── "hello"
s2._pstr ─┘
```

程序结束时，`s1` 和 `s2` 的析构函数都会执行：

```cpp
delete[] _pstr;
```

同一块内存被释放两次，就会出错。

所以必须深拷贝：

```cpp
s1._pstr ---> "hello"

s2._pstr ---> "hello"
```

两个对象内容一样，但内存独立。

---

# 三、推荐的类声明

这里我把头文件和实现放在一个 `.cpp` 文件里，方便你交作业或者直接运行。

```cpp
#include <iostream>
#include <cstring>
#include <stdexcept>

class String 
{
public:
    // 默认构造函数
    // 创建一个空字符串 ""
    String();

    // 带参构造函数
    // 用 C 风格字符串初始化 String 对象
    String(const char *);

    // 拷贝构造函数
    // 用一个已有 String 对象初始化新对象
    String(const String &);

    // 析构函数
    // 释放对象内部申请的堆内存
    ~String();

    // 拷贝赋值运算符
    // 用一个已有 String 对象给当前对象赋值
    String &operator=(const String &);

    // 用 C 风格字符串给当前对象赋值
    String &operator=(const char *);

    // 拼接另一个 String 对象
    String &operator+=(const String &);

    // 拼接 C 风格字符串
    String &operator+=(const char *);
    
    // 下标访问运算符
    // 非 const 对象可以通过它修改字符
    char &operator[](std::size_t index);

    // const 对象只能读取字符，不能修改字符
    const char &operator[](std::size_t index) const;
    
    // 返回字符串长度，不包括 '\0'
    std::size_t size() const;

    // 返回内部 C 风格字符串指针
    const char* c_str() const;
    
    // 判断两个字符串是否相等
    friend bool operator==(const String &, const String &);

    // 判断两个字符串是否不相等
    friend bool operator!=(const String &, const String &);
    
    // 字典序比较
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);
    
    // 输出运算符
    friend std::ostream &operator<<(std::ostream &os, const String &s);

    // 输入运算符
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    // 指向堆区字符数组
    // 保存真正的字符串内容
    char * _pstr;
};

// 普通的全局函数，不是成员函数
// 用于实现字符串相加
String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);
```

---

# 四、完整实现代码，带详细注释

```cpp
// 默认构造函数
// 创建一个空字符串
String::String()
{
    // 即使是空字符串，也要分配 1 个字符空间
    // 用来保存字符串结束符 '\0'
    _pstr = new char[1];

    // 空字符串的内容就是一个结束符
    _pstr[0] = '\0';
}
```

为什么不让 `_pstr = nullptr`？

因为如果 `_pstr` 是空指针，那么这些操作都可能崩溃：

```cpp
strlen(_pstr);
cout << _pstr;
strcmp(_pstr, other._pstr);
```

所以让它始终指向一个合法字符串更安全。

---

```cpp
// 带参构造函数
// 允许这样创建对象：String s("hello");
String::String(const char *str)
{
    // 如果传入的是空指针 nullptr
    // 那么我们把它当作空字符串处理
    if (str == nullptr)
    {
        _pstr = new char[1];
        _pstr[0] = '\0';
    }
    else
    {
        // strlen(str) 计算字符串长度，不包括 '\0'
        // 所以申请空间时必须 +1，用来存放 '\0'
        _pstr = new char[std::strlen(str) + 1];

        // strcpy 会把字符串内容和最后的 '\0' 一起复制过去
        std::strcpy(_pstr, str);
    }
}
```

例如：

```cpp
String s("hello");
```

`strlen("hello")` 是 `5`，但实际需要 `6` 个字符空间：

```cpp
'h' 'e' 'l' 'l' 'o' '\0'
```

---

```cpp
// 拷贝构造函数
// 用一个已有对象初始化新对象
// 例如：String s2(s1);
String::String(const String &rhs)
{
    // 申请一块新的内存
    // 大小和 rhs 中的字符串一样
    _pstr = new char[std::strlen(rhs._pstr) + 1];

    // 把 rhs 的字符串内容复制到当前对象中
    std::strcpy(_pstr, rhs._pstr);
}
```

注意，这里一定要重新申请内存，不能直接：

```cpp
_pstr = rhs._pstr;
```

否则两个对象会共享同一块内存，导致析构时重复释放。

---

```cpp
// 析构函数
// 对象生命周期结束时自动调用
String::~String()
{
    // 由于前面使用 new char[] 申请内存
    // 所以这里必须使用 delete[]
    delete[] _pstr;

    // 把指针置空不是必须的
    // 但这是一个良好的习惯，可以避免野指针
    _pstr = nullptr;
}
```

注意：

```cpp
new char[10];
```

对应：

```cpp
delete[] p;
```

不要写成：

```cpp
delete p;
```

---

## 赋值运算符：`operator=(const String &)`

```cpp
// 拷贝赋值运算符
// 例如：s1 = s2;
String &String::operator=(const String &rhs)
{
    // 防止自赋值
    // 例如：s1 = s1;
    if (this != &rhs)
    {
        // 先申请新空间
        // 这样做比先 delete 更安全
        char *tmp = new char[std::strlen(rhs._pstr) + 1];

        // 把 rhs 的字符串复制到 tmp 中
        std::strcpy(tmp, rhs._pstr);

        // 释放当前对象原来的字符串空间
        delete[] _pstr;

        // 让当前对象指向新的字符串空间
        _pstr = tmp;
    }

    // 返回当前对象本身
    // 这样可以支持连续赋值：s1 = s2 = s3;
    return *this;
}
```

为什么要判断自赋值？

假设没有判断，写成这样：

```cpp
delete[] _pstr;
_pstr = new char[strlen(rhs._pstr) + 1];
```

当执行：

```cpp
s1 = s1;
```

`rhs._pstr` 和当前对象的 `_pstr` 是同一个指针。

你先释放了 `_pstr`，再去 `strlen(rhs._pstr)`，这时 `rhs._pstr` 已经是无效内存了。

---

## 赋值运算符：`operator=(const char *)`

```cpp
// 使用 C 风格字符串给 String 对象赋值
// 例如：s1 = "hello";
String &String::operator=(const char *str)
{
    // 如果传入 nullptr，就当作空字符串处理
    if (str == nullptr)
    {
        str = "";
    }

    // 先申请新空间
    char *tmp = new char[std::strlen(str) + 1];

    // 复制字符串内容
    std::strcpy(tmp, str);

    // 释放原来的空间
    delete[] _pstr;

    // 指向新的空间
    _pstr = tmp;

    return *this;
}
```

这里也使用了“先申请新空间，再释放旧空间”的方式。

这样写比较安全。如果申请新空间失败，原对象的内容还没有被破坏。

---

# 五、拼接运算符

## `operator+=(const String &)`

```cpp
// 把另一个 String 对象拼接到当前对象后面
// 例如：s1 += s2;
String &String::operator+=(const String &rhs)
{
    // 当前字符串长度
    std::size_t len1 = std::strlen(_pstr);

    // 右边字符串长度
    std::size_t len2 = std::strlen(rhs._pstr);

    // 新字符串长度 = len1 + len2
    // 还需要 +1 保存 '\0'
    char *tmp = new char[len1 + len2 + 1];

    // 先把当前字符串复制到 tmp
    std::strcpy(tmp, _pstr);

    // 再把 rhs 的字符串追加到 tmp 后面
    std::strcat(tmp, rhs._pstr);

    // 释放原来的字符串空间
    delete[] _pstr;

    // 当前对象指向拼接后的新字符串
    _pstr = tmp;

    return *this;
}
```

例如：

```cpp
String s1("hello");
String s2(" world");

s1 += s2;
```

结果：

```cpp
s1 == "hello world"
```

---

## `operator+=(const char *)`

```cpp
// 拼接 C 风格字符串
// 例如：s1 += " world";
String &String::operator+=(const char *str)
{
    // 如果 str 是 nullptr，直接不做任何操作
    if (str == nullptr)
    {
        return *this;
    }

    std::size_t len1 = std::strlen(_pstr);
    std::size_t len2 = std::strlen(str);

    char *tmp = new char[len1 + len2 + 1];

    std::strcpy(tmp, _pstr);
    std::strcat(tmp, str);

    delete[] _pstr;
    _pstr = tmp;

    return *this;
}
```

---

# 六、下标访问运算符

## 非 const 版本

```cpp
// 非 const 对象调用这个版本
// 可以修改字符
char &String::operator[](std::size_t index)
{
    // 下标范围是 0 到 size() - 1
    // 如果 index >= size()，说明越界
    if (index >= size())
    {
        throw std::out_of_range("String index out of range");
    }

    // 返回字符的引用
    // 因为返回的是引用，所以可以修改
    return _pstr[index];
}
```

例如：

```cpp
String s("hello");
s[0] = 'H';
```

执行后：

```cpp
s == "Hello"
```

---

## const 版本

```cpp
// const 对象调用这个版本
// 只能读取，不能修改
const char &String::operator[](std::size_t index) const
{
    if (index >= size())
    {
        throw std::out_of_range("String index out of range");
    }

    return _pstr[index];
}
```

例如：

```cpp
const String s("hello");
std::cout << s[0];
```

可以。

但是：

```cpp
s[0] = 'H';
```

不可以，因为 `s` 是 const 对象。

---

# 七、size 和 c_str

```cpp
// 返回字符串长度
// 不包括最后的 '\0'
std::size_t String::size() const
{
    return std::strlen(_pstr);
}
```

例如：

```cpp
String s("hello");
std::cout << s.size();
```

输出：

```cpp
5
```

---

```cpp
// 返回内部 C 风格字符串
const char* String::c_str() const
{
    return _pstr;
}
```

为什么返回 `const char *`？

因为不希望外部通过这个指针随意修改内部数据。

例如下面这种写法应该被禁止：

```cpp
char *p = s.c_str();
p[0] = 'X';
```

所以返回 `const char *` 更安全。

---

# 八、比较运算符

字符串比较不能直接用指针比较。

错误写法：

```cpp
return lhs._pstr == rhs._pstr;
```

这比较的是两个指针地址，不是字符串内容。

应该使用：

```cpp
std::strcmp(lhs._pstr, rhs._pstr)
```

`strcmp` 的规则：

```cpp
strcmp(a, b) == 0   表示 a 和 b 内容相等
strcmp(a, b) < 0    表示 a 按字典序小于 b
strcmp(a, b) > 0    表示 a 按字典序大于 b
```

完整代码：

```cpp
bool operator==(const String &lhs, const String &rhs)
{
    return std::strcmp(lhs._pstr, rhs._pstr) == 0;
}

bool operator!=(const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const String &lhs, const String &rhs)
{
    return std::strcmp(lhs._pstr, rhs._pstr) < 0;
}

bool operator>(const String &lhs, const String &rhs)
{
    return rhs < lhs;
}

bool operator<=(const String &lhs, const String &rhs)
{
    return !(rhs < lhs);
}

bool operator>=(const String &lhs, const String &rhs)
{
    return !(lhs < rhs);
}
```

这里有一个小技巧：

```cpp
lhs > rhs
```

等价于：

```cpp
rhs < lhs
```

所以可以复用已经写好的 `<` 运算符。

---

# 九、输入输出运算符

## 输出运算符

```cpp
std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s._pstr;
    return os;
}
```

这样就可以：

```cpp
String s("hello");
std::cout << s;
```

输出：

```cpp
hello
```

返回 `os` 是为了支持连续输出：

```cpp
std::cout << s1 << s2 << std::endl;
```

---

## 输入运算符

```cpp
std::istream &operator>>(std::istream &is, String &s)
{
    // 临时缓冲区
    // 这里最多读取 1023 个有效字符
    // 最后一个位置留给 '\0'
    char buffer[1024];

    // is >> buffer 会读取一个单词
    // 遇到空格、Tab、换行会停止
    if (is >> buffer)
    {
        // 调用 operator=(const char *)
        // 把 buffer 中的内容赋值给 s
        s = buffer;
    }

    return is;
}
```

注意：这个版本的 `operator>>` 不能读取带空格的整行字符串。

例如输入：

```cpp
hello world
```

它只会读到：

```cpp
hello
```

如果想读取整行，需要用 `getline`，但你的类声明里没有要求实现。

---

# 十、加法运算符

`operator+` 和 `operator+=` 的区别：

```cpp
s1 += s2;
```

会修改 `s1`。

```cpp
s3 = s1 + s2;
```

不会修改 `s1` 和 `s2`，而是产生一个新对象。

---

```cpp
// String + String
String operator+(const String &lhs, const String &rhs)
{
    // 先用 lhs 创建一个临时对象
    String tmp(lhs);

    // 再把 rhs 拼接到 tmp 后面
    tmp += rhs;

    // 返回拼接后的新对象
    return tmp;
}
```

---

```cpp
// String + const char *
String operator+(const String &lhs, const char *rhs)
{
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}
```

---

```cpp
// const char * + String
String operator+(const char *lhs, const String &rhs)
{
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}
```

---

# 十一、完整带注释代码

下面是一份可以直接复制运行的完整版本。

```cpp
#include <iostream>
#include <cstring>
#include <stdexcept>

class String 
{
public:
    // 默认构造函数：创建空字符串
    String();

    // 带参构造函数：使用 C 风格字符串初始化
    String(const char *);

    // 拷贝构造函数：使用已有 String 对象初始化新对象
    String(const String &);

    // 析构函数：释放动态申请的内存
    ~String();

    // 拷贝赋值运算符：String 对象之间赋值
    String &operator=(const String &);

    // 赋值运算符：使用 C 风格字符串赋值
    String &operator=(const char *);

    // 拼接 String 对象
    String &operator+=(const String &);

    // 拼接 C 风格字符串
    String &operator+=(const char *);
    
    // 下标访问：非 const 对象使用，可以修改字符
    char &operator[](std::size_t index);

    // 下标访问：const 对象使用，只能读取字符
    const char &operator[](std::size_t index) const;
    
    // 返回字符串长度
    std::size_t size() const;

    // 返回 C 风格字符串
    const char* c_str() const;
    
    // 友元函数可以访问 private 成员 _pstr
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);
    
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);
    
    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    // 指向动态字符数组
    // 用来保存字符串内容
    char * _pstr;
};

// 全局 operator+ 函数声明
String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);


// 默认构造函数
String::String()
{
    _pstr = new char[1];
    _pstr[0] = '\0';
}


// 带参构造函数
String::String(const char *str)
{
    if (str == nullptr)
    {
        _pstr = new char[1];
        _pstr[0] = '\0';
    }
    else
    {
        _pstr = new char[std::strlen(str) + 1];
        std::strcpy(_pstr, str);
    }
}


// 拷贝构造函数
String::String(const String &rhs)
{
    _pstr = new char[std::strlen(rhs._pstr) + 1];
    std::strcpy(_pstr, rhs._pstr);
}


// 析构函数
String::~String()
{
    delete[] _pstr;
    _pstr = nullptr;
}


// 拷贝赋值运算符
String &String::operator=(const String &rhs)
{
    if (this != &rhs)
    {
        char *tmp = new char[std::strlen(rhs._pstr) + 1];
        std::strcpy(tmp, rhs._pstr);

        delete[] _pstr;
        _pstr = tmp;
    }

    return *this;
}


// C 风格字符串赋值
String &String::operator=(const char *str)
{
    if (str == nullptr)
    {
        str = "";
    }

    char *tmp = new char[std::strlen(str) + 1];
    std::strcpy(tmp, str);

    delete[] _pstr;
    _pstr = tmp;

    return *this;
}


// 拼接 String
String &String::operator+=(const String &rhs)
{
    std::size_t len1 = std::strlen(_pstr);
    std::size_t len2 = std::strlen(rhs._pstr);

    char *tmp = new char[len1 + len2 + 1];

    std::strcpy(tmp, _pstr);
    std::strcat(tmp, rhs._pstr);

    delete[] _pstr;
    _pstr = tmp;

    return *this;
}


// 拼接 C 风格字符串
String &String::operator+=(const char *str)
{
    if (str == nullptr)
    {
        return *this;
    }

    std::size_t len1 = std::strlen(_pstr);
    std::size_t len2 = std::strlen(str);

    char *tmp = new char[len1 + len2 + 1];

    std::strcpy(tmp, _pstr);
    std::strcat(tmp, str);

    delete[] _pstr;
    _pstr = tmp;

    return *this;
}


// 下标访问：可修改
char &String::operator[](std::size_t index)
{
    if (index >= size())
    {
        throw std::out_of_range("String index out of range");
    }

    return _pstr[index];
}


// 下标访问：只读
const char &String::operator[](std::size_t index) const
{
    if (index >= size())
    {
        throw std::out_of_range("String index out of range");
    }

    return _pstr[index];
}


// 返回字符串长度
std::size_t String::size() const
{
    return std::strlen(_pstr);
}


// 返回 C 风格字符串
const char* String::c_str() const
{
    return _pstr;
}


// 判断相等
bool operator==(const String &lhs, const String &rhs)
{
    return std::strcmp(lhs._pstr, rhs._pstr) == 0;
}


// 判断不相等
bool operator!=(const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}


// 小于比较
bool operator<(const String &lhs, const String &rhs)
{
    return std::strcmp(lhs._pstr, rhs._pstr) < 0;
}


// 大于比较
bool operator>(const String &lhs, const String &rhs)
{
    return rhs < lhs;
}


// 小于等于比较
bool operator<=(const String &lhs, const String &rhs)
{
    return !(rhs < lhs);
}


// 大于等于比较
bool operator>=(const String &lhs, const String &rhs)
{
    return !(lhs < rhs);
}


// 输出运算符
std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s._pstr;
    return os;
}


// 输入运算符
std::istream &operator>>(std::istream &is, String &s)
{
    char buffer[1024];

    if (is >> buffer)
    {
        s = buffer;
    }

    return is;
}


// String + String
String operator+(const String &lhs, const String &rhs)
{
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}


// String + const char *
String operator+(const String &lhs, const char *rhs)
{
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}


// const char * + String
String operator+(const char *lhs, const String &rhs)
{
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}
```

---

# 十二、完整测试用例

```cpp
int main()
{
    std::cout << "===== 1. 构造函数测试 =====" << std::endl;

    String s1;
    String s2("hello");
    String s3(s2);

    std::cout << "s1 = [" << s1 << "], size = " << s1.size() << std::endl;
    std::cout << "s2 = [" << s2 << "], size = " << s2.size() << std::endl;
    std::cout << "s3 = [" << s3 << "], size = " << s3.size() << std::endl;


    std::cout << "\n===== 2. 赋值运算符测试 =====" << std::endl;

    s1 = s2;
    std::cout << "执行 s1 = s2 后，s1 = " << s1 << std::endl;

    s1 = "world";
    std::cout << "执行 s1 = \"world\" 后，s1 = " << s1 << std::endl;

    s1 = s1;
    std::cout << "执行自赋值 s1 = s1 后，s1 = " << s1 << std::endl;


    std::cout << "\n===== 3. 拼接运算符 += 测试 =====" << std::endl;

    s1 += " ";
    s1 += s2;

    std::cout << "执行 s1 += \" \"; s1 += s2; 后，s1 = " << s1 << std::endl;


    std::cout << "\n===== 4. 加法运算符 + 测试 =====" << std::endl;

    String s4 = s2 + String(" cpp");
    String s5 = s2 + " language";
    String s6 = "say " + s2;

    std::cout << "s2 + String(\" cpp\") = " << s4 << std::endl;
    std::cout << "s2 + \" language\" = " << s5 << std::endl;
    std::cout << "\"say \" + s2 = " << s6 << std::endl;


    std::cout << "\n===== 5. 下标访问测试 =====" << std::endl;

    std::cout << "s2[0] = " << s2[0] << std::endl;

    s2[0] = 'H';
    std::cout << "修改 s2[0] = 'H' 后，s2 = " << s2 << std::endl;

    try
    {
        std::cout << "访问 s2[100]：" << std::endl;
        std::cout << s2[100] << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "捕获异常：" << e.what() << std::endl;
    }


    std::cout << "\n===== 6. 比较运算符测试 =====" << std::endl;

    String a("abc");
    String b("abd");
    String c("abc");

    std::cout << std::boolalpha;

    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a == c: " << (a == c) << std::endl;
    std::cout << "a != b: " << (a != b) << std::endl;
    std::cout << "a < b: " << (a < b) << std::endl;
    std::cout << "a > b: " << (a > b) << std::endl;
    std::cout << "a <= c: " << (a <= c) << std::endl;
    std::cout << "a >= c: " << (a >= c) << std::endl;


    std::cout << "\n===== 7. c_str 测试 =====" << std::endl;

    const char *p = s2.c_str();
    std::cout << "s2.c_str() = " << p << std::endl;


    std::cout << "\n===== 8. 输入运算符测试 =====" << std::endl;

    String input;
    std::cout << "请输入一个单词：";
    std::cin >> input;
    std::cout << "你输入的是：" << input << std::endl;

    return 0;
}
```

---

# 十三、建议你写作业报告时这样总结

可以这样写：

> 本题实现了一个简单的 String 类，内部使用 `char*` 管理字符串内容。为了避免浅拷贝带来的重复释放问题，拷贝构造函数和赋值运算符均采用深拷贝。默认构造函数将字符串初始化为空字符串，并保证 `_pstr` 始终指向合法内存。析构函数负责释放动态内存。通过重载 `operator+=` 和 `operator+` 实现字符串拼接，通过 `strcmp` 实现关系比较，通过 `operator[]` 实现下标访问，并加入越界检查以提高安全性。

---

# 十四、这份代码中的几个关键点

最核心的是这三件事：

```cpp
String(const String &);
String &operator=(const String &);
~String();
```

它们被称为 C++ 里的“三法则”。

因为你的类中手动管理了动态内存：

```cpp
char *_pstr;
```

所以你通常必须自己写：

```cpp
拷贝构造函数
赋值运算符
析构函数
```

否则编译器默认生成的版本可能会造成浅拷贝、重复释放、内存错误。

---

# 十五、可以进一步优化的地方

可以进一步添加：

```cpp
String(String &&);
String &operator=(String &&);
```

这叫移动构造和移动赋值，是 C++11 之后的优化写法。

但对于这道作业，目前实现“三法则”已经足够完整。
