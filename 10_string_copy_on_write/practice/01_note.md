# 一、这个 CowString 要解决什么问题？

你的 `CowString` 实现的是一个支持 **COW 技术** 的字符串类。

COW 是 **Copy On Write** 的缩写，意思是：

> 写时复制。

它的核心思想是：

> 多个字符串对象内容相同时，先共享同一块堆空间，不急着深拷贝。
> 只有当某个对象要修改字符串内容时，才复制一份新的空间出来。

例如：

```cpp
CowString s1("abc");
CowString s2 = s1;
```

如果是普通深拷贝，那么 `s2` 会重新申请一块堆空间，里面也存一份 `"abc"`。

但是 COW 的做法是：

```text
s1 ----\
       ---> "abc"
s2 ----/
```

也就是说，`s1` 和 `s2` 暂时共享同一块空间。

这样可以减少不必要的内存申请和字符串拷贝。

只有当出现写操作时：

```cpp
s1[0] = 'A';
```

才让 `s1` 从共享空间中分离出来：

```text
s1 ---> "Abc"

s2 ---> "abc"
```

这样既节省内存，又不会让 `s1` 的修改影响到 `s2`。

---

# 二、你的内存结构是怎么设计的？

你的 `CowString` 里面只有一个数据成员：

```cpp
char * m_pStr;
```

但是你并不是只申请字符串需要的空间，而是额外多申请了 4 个字节：

```cpp
m_pStr(new char[4 + std::strlen(pStr) + 1]() + 4)
```

这 4 个字节用来保存 **引用计数**。

假设构造：

```cpp
CowString s("abc");
```

实际申请的堆空间大概是这样：

```text
低地址                                      高地址
+----------------+--------------------------+
| 引用计数 int   | 字符串内容 'a' 'b' 'c' '\0' |
+----------------+--------------------------+
^                ^
|                |
m_pStr - 4       m_pStr
```

也就是说：

```cpp
m_pStr
```

指向的是字符串内容的首地址，也就是 `'a'`。

而：

```cpp
m_pStr - 4
```

指向引用计数所在的位置。

所以引用计数可以通过：

```cpp
*(int *)(m_pStr - 4)
```

访问。

这就是你下面几个函数的作用。

---

# 三、引用计数相关函数

## 1. 初始化引用计数

```cpp
void initRefCount()
{
    *(int *)(m_pStr - 4) = 1;
}
```

刚申请一块新空间时，只有当前对象使用它，所以引用计数初始化为 `1`。

比如：

```cpp
CowString s1("abc");
```

此时：

```text
s1 ---> [refCount = 1]["abc"]
```

---

## 2. 引用计数加一

```cpp
void incrementRefCount()
{
    ++*(int *)(m_pStr - 4);
}
```

当有新的对象共享这块空间时，引用计数加一。

例如：

```cpp
CowString s1("abc");
CowString s2 = s1;
```

拷贝构造函数中：

```cpp
CowString(const CowString & rhs)
: m_pStr(rhs.m_pStr)
{
    incrementRefCount();
}
```

这里没有重新申请空间，而是让：

```cpp
s2.m_pStr = s1.m_pStr;
```

然后引用计数加一。

此时：

```text
s1 ----\
       ---> [refCount = 2]["abc"]
s2 ----/
```

---

## 3. 引用计数减一

```cpp
void decrementRefCount()
{
    --*(int *)(m_pStr - 4);
}
```

当某个对象不再使用当前空间时，需要引用计数减一。

常见场景有三个：

```cpp
析构函数中
赋值运算符释放旧空间时
写时复制 detach 时
```

---

## 4. 获取引用计数

```cpp
int getRefCount() const
{
    return *(int *)(m_pStr - 4);
}
```

这个函数用于查看当前字符串空间被多少个对象共享。

例如：

```cpp
CowString s1("abc");
CowString s2 = s1;

cout << s1.getRefCount() << endl;
cout << s2.getRefCount() << endl;
```

输出应该都是：

```text
2
2
```

因为 `s1` 和 `s2` 指向同一块空间，所以它们看到的是同一个引用计数。

---

# 四、构造函数解析

## 1. 默认构造函数

```cpp
CowString()
: m_pStr(new char[4 + 1]() + 4)
{
    initRefCount();
}
```

默认构造函数创建一个空字符串。

这里申请：

```cpp
4 + 1
```

个字节。

其中：

```text
4 字节：保存引用计数
1 字节：保存 '\0'
```

`new char[4 + 1]()` 后面的 `()` 表示把申请到的空间初始化为 `0`。

所以字符串部分天然就是：

```cpp
""
```

也就是空字符串。

---

## 2. 有参构造函数

```cpp
CowString(const char * pStr)
: m_pStr(new char[4 + std::strlen(pStr) + 1]() + 4)
{
    initRefCount();
    std::strcpy(m_pStr, pStr);
}
```

例如：

```cpp
CowString s1("abc");
```

这里申请的空间大小是：

```cpp
4 + strlen("abc") + 1
```

也就是：

```cpp
4 + 3 + 1
```

其中：

```text
4：引用计数
3：字符 a b c
1：字符串结束符 '\0'
```

然后：

```cpp
initRefCount();
```

把引用计数设为 `1`。

最后：

```cpp
std::strcpy(m_pStr, pStr);
```

把 `"abc"` 拷贝到字符串区域。

---

# 五、拷贝构造函数为什么是浅拷贝？

```cpp
CowString(const CowString & rhs)
: m_pStr(rhs.m_pStr)
{
    incrementRefCount();
}
```

这里没有写：

```cpp
new char[...]
strcpy(...)
```

而是直接：

```cpp
m_pStr(rhs.m_pStr)
```

这说明新对象和旧对象共享同一块空间。

例如：

```cpp
CowString s1("abc");
CowString s2 = s1;
```

调用拷贝构造之后：

```text
s1 ----\
       ---> [refCount = 2]["abc"]
s2 ----/
```

这是 COW 的基础。

如果拷贝构造一上来就深拷贝，那么就不叫写时复制了，而是普通字符串类。

---

# 六、赋值运算符解析

```cpp
CowString & operator=(const CowString & rhs)
{
    if(this != &rhs)
    {
        release();

        m_pStr = rhs.m_pStr;
        incrementRefCount();
    }

    return *this;
}
```

赋值运算符处理的是这种情况：

```cpp
CowString s1("hello");
CowString s2("world");

s1 = s2;
```

它的过程分为两步。

---

## 第一步：释放自己原来管理的空间

```cpp
release();
```

`s1` 原来指向 `"hello"`，现在要改为指向 `s2` 的 `"world"`，所以要先放弃原来的空间。

但是这个释放不是立刻 `delete`。

因为可能还有别的对象也在共享 `"hello"` 这块空间。

所以 `release()` 会先让引用计数减一，只有引用计数变成 `0`，才真正释放堆空间。

---

## 第二步：共享 rhs 的空间

```cpp
m_pStr = rhs.m_pStr;
incrementRefCount();
```

现在让当前对象和 `rhs` 指向同一块空间。

引用计数加一。

例如：

```text
赋值前：

s1 ---> [refCount = 1]["hello"]

s2 ---> [refCount = 1]["world"]

执行 s1 = s2 后：

s1 ----\
       ---> [refCount = 2]["world"]
s2 ----/
```

---

# 七、析构函数与 release

析构函数很简单：

```cpp
~CowString()
{
    release();
}
```

真正重要的是 `release()`：

```cpp
void release()
{
    if(m_pStr)
    {
        decrementRefCount();

        if(getRefCount() == 0)
        {
            delete [] (m_pStr - 4);
            cout << "release heap" << endl;
        }

        m_pStr = nullptr;
    }
}
```

它的逻辑是：

1. 判断 `m_pStr` 是否为空。
2. 如果不为空，引用计数减一。
3. 如果减完之后引用计数为 `0`，说明没有对象使用这块空间了。
4. 释放整块堆空间。
5. 把 `m_pStr` 置空，避免野指针。

这里一定要注意：

```cpp
delete [] (m_pStr - 4);
```

不能写成：

```cpp
delete [] m_pStr;
```

因为当初申请空间时，真正由 `new[]` 返回的地址是：

```cpp
new char[4 + len + 1]()
```

但是你把它整体偏移了 4 个字节：

```cpp
m_pStr = new char[...] + 4;
```

所以 `m_pStr` 不是整块堆空间的起始地址。

释放时必须回到起始地址：

```cpp
m_pStr - 4
```

---

# 八、为什么 `operator[]` 要返回 CharProxy？

这是整个作业最关键的地方。

如果你写成普通版本：

```cpp
char & operator[](int index)
{
    return m_pStr[index];
}
```

那么下面两种代码都只会调用 `operator[]`：

```cpp
cout << s1[0];   // 读操作
s1[0] = 'A';     // 写操作
```

问题在于：

> `operator[]` 内部无法知道返回之后，外部到底是要读还是要写。

如果你在 `operator[]` 中直接做 COW 检查：

```cpp
char & operator[](int index)
{
    if(getRefCount() > 1)
    {
        detach();
    }

    return m_pStr[index];
}
```

那么即使只是读：

```cpp
cout << s1[0];
```

也会触发 `detach()`。

这就违背了 COW 的目的。

COW 要求：

```text
读操作：不复制
写操作：才复制
```

所以你的代码用了代理类：

```cpp
CharProxy operator[](int index)
{
    return CharProxy(*this, index);
}
```

`operator[]` 不直接返回字符，而是返回一个代理对象。

---

# 九、CharProxy 是怎么工作的？

你的 `CharProxy` 内部保存两个信息：

```cpp
CowString & m_self;
int m_index;
```

含义是：

```cpp
m_self
```

表示代理对象属于哪个 `CowString` 对象。

```cpp
m_index
```

表示代理的是哪个下标。

例如：

```cpp
CowString s1("abc");
s1[0];
```

调用：

```cpp
s1.operator[](0)
```

返回：

```cpp
CharProxy(s1, 0)
```

也就是说，这个代理对象代表：

```cpp
s1 的第 0 个字符
```

---

# 十、读操作如何被识别？

你的 `CharProxy` 中定义了类型转换函数：

```cpp
operator char() const
{
    if(m_index < 0 || m_index >= m_self.size())
    {
        cout << "index is illegal" << endl;
        return '\0'; 
    }
    return m_self.m_pStr[m_index];
}
```

这个函数表示：

> 当需要把 `CharProxy` 当成 `char` 使用时，就调用这个函数。

例如：

```cpp
char ch = s2[1];
```

执行过程是：

```cpp
s2[1]
```

先调用：

```cpp
CowString::operator[](1)
```

返回一个 `CharProxy` 对象。

然后：

```cpp
char ch = CharProxy对象;
```

需要把 `CharProxy` 转成 `char`，于是调用：

```cpp
operator char() const
```

这就是读操作。

读操作只返回字符，不调用 `detach()`，所以不会触发深拷贝。

---

# 十一、`cout << s1[0]` 为什么也是读操作？

你的代码中有这个输出运算符：

```cpp
ostream & operator<<(ostream & os, const CowString::CharProxy & rhs)
{
    os << static_cast<char>(rhs);
    return os;
}
```

当执行：

```cpp
cout << s1[0] << endl;
```

过程是：

```cpp
s1[0]
```

返回 `CharProxy`。

然后匹配到：

```cpp
operator<<(ostream &, const CowString::CharProxy &)
```

这个函数内部：

```cpp
os << static_cast<char>(rhs);
```

显式调用：

```cpp
CharProxy::operator char() const
```

于是读取对应字符。

这个设计很好，因为它把读操作统一交给了 `operator char()`。

这样越界检查也只需要在 `operator char()` 里写一份。

---

# 十二、写操作如何被识别？

写操作对应的是：

```cpp
s1[0] = 'A';
```

执行过程是：

```cpp
s1.operator[](0).operator=('A');
```

也就是说：

1. `s1[0]` 先返回 `CharProxy(s1, 0)`。
2. 因为右边是赋值操作，所以调用 `CharProxy::operator=(char)`。

你的写操作函数是：

```cpp
CharProxy & operator=(char ch)
{
    if(m_index < 0 || m_index >= m_self.size())
    {
        cout << "index is illegal" << endl;
        return *this; 
    }

    if(m_self.getRefCount() > 1)
    {
        m_self.detach();
    }

    m_self.m_pStr[m_index] = ch;

    return *this;
}
```

这就是 COW 的核心。

它先判断越界。

如果下标合法，再判断引用计数：

```cpp
if(m_self.getRefCount() > 1)
```

如果引用计数大于 `1`，说明当前字符串空间被多个对象共享。

此时不能直接修改。

所以调用：

```cpp
m_self.detach();
```

让当前对象拥有一份独立空间。

然后再执行：

```cpp
m_self.m_pStr[m_index] = ch;
```

这样修改的就是当前对象自己的空间，不会影响其他对象。

---

# 十三、detach 函数详细解析

你的 `detach()` 函数如下：

```cpp
void detach()
{   
    char * old = m_pStr;

    decrementRefCount();

    m_pStr = new char[4 + std::strlen(old) + 1]() + 4;

    initRefCount();

    std::strcpy(m_pStr, old);
}
```

假设当前情况是：

```cpp
CowString s1("abc");
CowString s2 = s1;
```

此时：

```text
s1 ----\
       ---> [refCount = 2]["abc"]
s2 ----/
```

执行：

```cpp
s1[0] = 'A';
```

会进入 `detach()`。

---

## 第一步：保存旧空间地址

```cpp
char * old = m_pStr;
```

此时 `old` 指向原来的字符串内容：

```text
old ---> "abc"
```

要先保存它，因为后面 `m_pStr` 会指向新空间。

---

## 第二步：旧空间引用计数减一

```cpp
decrementRefCount();
```

原来旧空间的引用计数是 `2`。

现在 `s1` 准备离开旧空间，所以旧空间引用计数减为 `1`。

此时旧空间仍然不能释放，因为 `s2` 还在使用它。

```text
s2 ---> [refCount = 1]["abc"]
```

---

## 第三步：给当前对象申请新空间

```cpp
m_pStr = new char[4 + std::strlen(old) + 1]() + 4;
```

这里给 `s1` 申请一块新的独立空间。

大小和旧字符串一样。

---

## 第四步：初始化新空间引用计数

```cpp
initRefCount();
```

新空间只有 `s1` 一个对象使用，所以引用计数为 `1`。

---

## 第五步：复制旧字符串内容

```cpp
std::strcpy(m_pStr, old);
```

把旧空间中的 `"abc"` 拷贝到新空间。

此时还没有真正修改字符，只是完成了“分离”。

然后回到：

```cpp
m_self.m_pStr[m_index] = ch;
```

把 `s1` 的第 `0` 个字符改成 `'A'`。

最终结果：

```text
s1 ---> [refCount = 1]["Abc"]

s2 ---> [refCount = 1]["abc"]
```

这就是写时复制。

---

# 十四、为什么还要有 `operator=(const CharProxy & rhs)`？

你的代码中有：

```cpp
CharProxy & operator=(const CharProxy & rhs)
{
    return *this = static_cast<char>(rhs);
}
```

它是为了支持这种写法：

```cpp
s1[1] = s2[2];
```

注意：

```cpp
s1[1]
```

返回的是 `CharProxy`。

```cpp
s2[2]
```

返回的也是 `CharProxy`。

如果没有：

```cpp
operator=(const CharProxy & rhs)
```

编译器不一定能很好地处理：

```cpp
CharProxy = CharProxy
```

所以你主动提供这个版本。

它内部做了两件事：

```cpp
static_cast<char>(rhs)
```

先把右边的 `CharProxy` 转成普通字符。

然后：

```cpp
*this = 普通字符
```

复用已有的：

```cpp
operator=(char ch)
```

也就是说：

```cpp
s1[1] = s2[2];
```

本质上等价于：

```cpp
s1[1] = static_cast<char>(s2[2]);
```

这样写很好，因为真正的写时复制逻辑只保留在 `operator=(char)` 里面，避免代码重复。

---

# 十五、为什么需要 const 版本的 operator[]？

你写了两个下标运算符：

```cpp
CharProxy operator[](int index)
```

和：

```cpp
char operator[](int index) const
```

它们的区别很重要。

---

## 非 const 对象调用这个版本

```cpp
CharProxy operator[](int index)
{
    return CharProxy(*this, index);
}
```

例如：

```cpp
CowString s("abc");

cout << s[0]; 
s[0] = 'A';
```

非 const 对象既可能读，也可能写，所以返回 `CharProxy`。

---

## const 对象调用这个版本

```cpp
char operator[](int index) const
{
    if(index < 0 || index >= size())
    {
        cout << "index is illegal" << endl;
        return '\0';
    }

    return m_pStr[index];
}
```

例如：

```cpp
const CowString s("abc");

cout << s[0];   // 可以
s[0] = 'A';     // 不可以
```

const 对象不允许修改，所以直接返回 `char`。

这样可以从语义上保证：

```text
const CowString 只能读，不能写
```

如果没有这个 const 版本，那么当你写：

```cpp
const CowString s("abc");
cout << s[0] << endl;
```

编译器会发现：

```cpp
CharProxy operator[](int index)
```

不是 const 成员函数，不能被 const 对象调用。

于是会报错。

所以这个 const 版本很有必要。

---

# 十六、为什么 c_str 返回 const char *？

你的代码是：

```cpp
const char * c_str() const
{
    return m_pStr;
}
```

这个设计是正确的。

如果你返回：

```cpp
char * c_str()
```

那么外部就可以这样写：

```cpp
CowString s1("abc");
CowString s2 = s1;

char * p = s1.c_str();
p[0] = 'A';
```

这会绕过 `CharProxy::operator=`，直接修改底层共享空间。

结果就会导致：

```cpp
s1
s2
```

一起被改掉，COW 机制被破坏。

所以返回：

```cpp
const char *
```

可以避免外部直接修改底层字符数组。

如果外部想修改，必须通过：

```cpp
s1[0] = 'A';
```

这样才能走 COW 流程。

---

# 十七、测试函数 test1 执行过程

你的测试函数设计得比较清楚。我们逐段看。

---

## 1. 创建 s1

```cpp
CowString s1("abc");
```

此时：

```text
s1 ---> [refCount = 1]["abc"]
```

输出：

```cpp
s1 = abc
s1 refCount = 1
```

---

## 2. 拷贝构造 s2

```cpp
CowString s2 = s1;
```

调用拷贝构造函数：

```cpp
CowString(const CowString & rhs)
: m_pStr(rhs.m_pStr)
{
    incrementRefCount();
}
```

此时 `s1` 和 `s2` 共享同一块空间：

```text
s1 ----\
       ---> [refCount = 2]["abc"]
s2 ----/
```

所以输出：

```cpp
s1 = abc
s2 = abc
s1 refCount = 2
s2 refCount = 2
```

注意，`s1.getRefCount()` 和 `s2.getRefCount()` 读到的是同一个引用计数。

---

## 3. 读操作

```cpp
cout << "s1[0] = " << s1[0] << endl;
```

执行流程：

```text
s1[0]
  -> CowString::operator[](0)
  -> 返回 CharProxy(s1, 0)

cout << CharProxy
  -> operator<<(ostream &, const CowString::CharProxy &)
  -> static_cast<char>(rhs)
  -> CharProxy::operator char()
  -> 返回 'a'
```

这个过程只是读，不调用 `detach()`。

所以读完后依然共享同一块空间：

```text
s1 ----\
       ---> [refCount = 2]["abc"]
s2 ----/
```

引用计数仍然是：

```cpp
2
```

---

## 4. 写操作

```cpp
s1[0] = 'A';
```

执行流程：

```text
s1[0]
  -> 返回 CharProxy(s1, 0)

CharProxy = 'A'
  -> CharProxy::operator=(char)
  -> 检查 refCount
  -> refCount > 1，调用 detach()
  -> 修改新空间中的第 0 个字符
```

写操作前：

```text
s1 ----\
       ---> [refCount = 2]["abc"]
s2 ----/
```

写操作后：

```text
s1 ---> [refCount = 1]["Abc"]

s2 ---> [refCount = 1]["abc"]
```

所以输出：

```cpp
s1 = Abc
s2 = abc
s1 refCount = 1
s2 refCount = 1
```

这说明 COW 成功。

---

## 5. 支持 `char ch = s2[1]`

```cpp
char ch = s2[1];
```

执行流程：

```text
s2[1]
  -> 返回 CharProxy(s2, 1)

CharProxy 转 char
  -> operator char()
  -> 返回 'b'
```

所以：

```cpp
ch = b
```

这里仍然是读操作，不触发写时复制。

---

## 6. 支持 `s1[1] = s2[2]`

```cpp
s1[1] = s2[2];
```

执行流程：

```text
s1[1]
  -> CharProxy(s1, 1)

s2[2]
  -> CharProxy(s2, 2)

CharProxy = CharProxy
  -> operator=(const CharProxy & rhs)
  -> static_cast<char>(rhs)
  -> 得到 'c'
  -> 调用 operator=(char)
  -> s1[1] = 'c'
```

此时前面已经执行过：

```cpp
s1[0] = 'A';
```

所以：

```cpp
s1 = "Abc"
s2 = "abc"
```

执行：

```cpp
s1[1] = s2[2];
```

就是把 `s2[2]` 的 `'c'` 赋给 `s1[1]`。

所以：

```cpp
s1
```

从：

```cpp
"Abc"
```

变成：

```cpp
"Acc"
```

而：

```cpp
s2
```

仍然是：

```cpp
"abc"
```

---

# 十八、这份代码中几个容易被问到的点

## 1. 为什么 `CharProxy` 要放在 public 里面？

因为你在类外写了：

```cpp
ostream & operator<<(ostream & os, const CowString::CharProxy & rhs)
```

这意味着类外代码需要知道：

```cpp
CowString::CharProxy
```

这个类型。

如果 `CharProxy` 是 private 嵌套类，那么类外函数在声明参数类型时可能无法访问这个类型。

所以你现在把它放在：

```cpp
public:
    class CharProxy
```

是合理的。

---

## 2. 为什么 `operator<<` 里面用 `static_cast<char>(rhs)`？

你的版本：

```cpp
ostream & operator<<(ostream & os, const CowString::CharProxy & rhs)
{
    os << static_cast<char>(rhs);
    return os;
}
```

比手动访问：

```cpp
rhs.m_self.m_pStr[rhs.m_index]
```

更简洁。

好处是：

```text
读逻辑统一放在 operator char() 里面。
越界检查也统一放在 operator char() 里面。
operator<< 不需要重复判断下标是否合法。
```

也就是说，所有读操作都走同一个入口：

```cpp
operator char() const
```

这是比较好的封装。

---

## 3. 为什么写操作中 `detach()` 后还能继续使用 `m_index`？

例如：

```cpp
s1[0] = 'A';
```

调用写操作时，`CharProxy` 保存的是：

```cpp
m_self = s1
m_index = 0
```

当执行：

```cpp
m_self.detach();
```

变化的是：

```cpp
s1.m_pStr
```

也就是 `s1` 指向了新的空间。

但是：

```cpp
m_index
```

仍然是 `0`。

所以之后：

```cpp
m_self.m_pStr[m_index] = ch;
```

就是修改新空间中的第 `0` 个字符。

这正是我们想要的行为。

---

## 4. 为什么 `detach()` 里要先保存 `old`？

```cpp
char * old = m_pStr;
```

因为后面马上要改变：

```cpp
m_pStr = new char[...]
```

如果不先保存旧地址，就找不到旧字符串内容了。

而新空间需要从旧空间复制字符串：

```cpp
std::strcpy(m_pStr, old);
```

所以必须先保存旧地址。

---

## 5. 为什么 `detach()` 里只减引用计数，不 delete 旧空间？

因为 `detach()` 只在：

```cpp
getRefCount() > 1
```

时调用。

也就是说，旧空间至少被两个对象共享。

当前对象离开旧空间后，旧空间引用计数至少还剩 `1`。

例如原来是 `2`，减完之后是 `1`。

说明还有其他对象正在使用旧空间，所以不能释放。

因此 `detach()` 中只需要：

```cpp
decrementRefCount();
```

不需要判断 `delete`。

当然，如果写得更通用，也可以在 `detach()` 里判断是否为 `0`，但在你当前逻辑中没有必要，因为调用前已经保证引用计数大于 `1`。

---

# 十九、总结

> `CowString` 类使用 COW 技术实现字符串共享和写时复制。每块字符串堆空间前面额外保存 4 个字节作为引用计数，`m_pStr` 指向真正的字符串内容，引用计数通过 `m_pStr - 4` 访问。
>
> 构造新字符串时引用计数初始化为 1；拷贝构造和赋值运算符采用浅拷贝，只共享底层字符串空间，并将引用计数加一；析构或者重新赋值时调用 `release()`，先将引用计数减一，如果引用计数变成 0，才真正释放堆空间。
>
> 为了区分下标访问中的读操作和写操作，非 const 版本的 `operator[]` 不返回 `char&`，而是返回代理类 `CharProxy`。
>
> 当执行 `cout << s[0]` 或 `char ch = s[0]` 时，会调用 `CharProxy::operator char()`，这属于读操作，不触发深拷贝。
>
> 当执行 `s[0] = 'A'` 时，会调用 `CharProxy::operator=(char)`，这属于写操作。写之前会检查引用计数，如果引用计数大于 1，说明底层空间被多个对象共享，就调用 `detach()` 分离出一块独立空间，然后再修改字符。
>
> 因此，这个实现既避免了无意义的深拷贝，又保证了修改一个对象时不会影响其他共享对象。

---

# 二十、整体评价

这版代码已经完成了作业要求：

```text
实现自定义字符串类型 CowString
使用引用计数管理共享内存
拷贝构造和赋值运算符采用浅拷贝
写操作时触发深拷贝
下标访问能区分读操作和写操作
支持 const 对象读访问
支持 cout << s[0]
支持 char ch = s[0]
支持 s1[0] = s2[1]
```

其中最核心的设计就是这三处：

```cpp
CharProxy operator[](int index)
{
    return CharProxy(*this, index);
}
```

```cpp
operator char() const
{
    return m_self.m_pStr[m_index];
}
```

```cpp
CharProxy & operator=(char ch)
{
    if(m_self.getRefCount() > 1)
    {
        m_self.detach();
    }

    m_self.m_pStr[m_index] = ch;
    return *this;
}
```

这三者配合起来，就完成了“读不复制，写才复制”的 COW 语义。
