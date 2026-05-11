下面按“能完成作业 + 理解 pimpl 思想”的方式指导你整理代码、编译、打包静态库并测试。

## 一、目录结构建议

建议放 3 个文件：

```bash
Line.hpp
LineImpl.cc
Test.cc
```

---

## 二、`Line.hpp`

头文件只暴露 `Line` 的接口，不暴露 `Point`、`LineImpl` 的具体实现。

```cpp
#ifndef __LINE_HPP__
#define __LINE_HPP__

class Line
{
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();

    void printLine() const;

private:
    class LineImpl;        // 内部实现类的前向声明
    LineImpl * m_pimpl;    // 指向实现类对象的指针
};

#endif
```

这里的重点是：

```cpp
class LineImpl;
LineImpl * m_pimpl;
```

外界只知道 `Line` 里面有一个 `LineImpl` 指针，但不知道 `LineImpl` 具体长什么样。

---

## 三、`LineImpl.cc`

具体实现全部放在 `.cc` 文件里。

```cpp
#include "Line.hpp"
#include <iostream>

using std::cout;
using std::endl;

// Line 的内部实现类
class Line::LineImpl
{
    class Point
    {
    public:
        Point(int x, int y)
        : m_x(x)
        , m_y(y)
        {
            cout << "Point constructor" << endl;
        }

        ~Point()
        {
            cout << "Point destructor" << endl;
        }

        void print() const
        {
            cout << "(" << m_x << ", " << m_y << ")";
        }

    private:
        int m_x;
        int m_y;
    };

public:
    LineImpl(int x1, int y1, int x2, int y2)
    : m_pt1(x1, y1)
    , m_pt2(x2, y2)
    {
        cout << "LineImpl constructor" << endl;
    }

    ~LineImpl()
    {
        cout << "LineImpl destructor" << endl;
    }

    void print() const
    {
        cout << "Line: ";
        m_pt1.print();
        cout << " -> ";
        m_pt2.print();
        cout << endl;
    }

private:
    Point m_pt1;
    Point m_pt2;
};

Line::Line(int x1, int y1, int x2, int y2)
: m_pimpl(new LineImpl(x1, y1, x2, y2))
{
    cout << "Line constructor" << endl;
}

Line::~Line()
{
    cout << "Line destructor" << endl;

    if (m_pimpl)
    {
        delete m_pimpl;
        m_pimpl = nullptr;
    }
}

void Line::printLine() const
{
    m_pimpl->print();
}
```

---

## 四、`Test.cc`

```cpp
#include "Line.hpp"

void test0()
{
    Line line(10, 20, 30, 40);
    line.printLine();
}

int main()
{
    test0();
    return 0;
}
```

---

## 五、直接编译测试

先不打包库，直接编译：

```bash
g++ LineImpl.cc Test.cc -o test
```

运行：

```bash
./test
```

可能输出类似：

```text
Point constructor
Point constructor
LineImpl constructor
Line constructor
Line: (10, 20) -> (30, 40)
Line destructor
LineImpl destructor
Point destructor
Point destructor
```

析构顺序是反过来的：先析构 `Line`，再 `delete m_pimpl`，然后析构 `LineImpl`，最后析构 `LineImpl` 的两个成员 `Point`。

---

## 六、打包静态库

先编译 `LineImpl.cc`：

```bash
g++ -c LineImpl.cc
```

会生成：

```bash
LineImpl.o
```

然后打包成静态库：

```bash
ar rcs libLine.a LineImpl.o
```

会生成：

```bash
libLine.a
```

静态库命名规则：

```text
lib + 库名 + .a
```

所以：

```text
libLine.a
```

对应链接参数就是：

```bash
-lLine
```

---

## 七、使用静态库编译测试文件

```bash
g++ Test.cc -L. -lLine -o test
```

解释：

```bash
-L.
```

表示在当前目录查找库文件。

```bash
-lLine
```

表示链接 `libLine.a`。

运行：

```bash
./test
```

---

## 八、交给第三方时需要给什么？

你只需要给第三方：

```bash
Line.hpp
libLine.a
```

第三方不需要拿到：

```bash
LineImpl.cc
LineImpl.o
```

第三方测试代码只需要：

```cpp
#include "Line.hpp"

int main()
{
    Line line(10, 20, 30, 40);
    line.printLine();
    return 0;
}
```

然后编译：

```bash
g++ Test.cc -L. -lLine -o test
```

这就是 pimpl 的一个核心好处：**隐藏实现细节，只暴露接口。**

---

## 九、pimpl 思想总结

pimpl 是 “pointer to implementation” 的缩写，也叫“编译防火墙”。

在这个例子中：

```cpp
class Line
{
private:
    class LineImpl;
    LineImpl * m_pimpl;
};
```

`Line.hpp` 中只声明了 `LineImpl`，没有暴露它的具体实现。

真正的数据成员：

```cpp
Point m_pt1;
Point m_pt2;
```

都藏在 `LineImpl.cc` 中。

所以外部用户只知道：

```cpp
Line line(10, 20, 30, 40);
line.printLine();
```

但不知道 `Line` 内部到底用了几个 `Point`，也不知道 `Point` 类怎么实现。

它的好处主要有三个：

1. **隐藏实现细节**
   用户只能看到 `Line.hpp`，看不到 `Point` 和 `LineImpl` 的具体实现。

2. **降低编译依赖**
   如果以后修改 `Point` 或 `LineImpl`，只需要重新编译库文件，不需要让用户修改自己的代码。

3. **保持接口稳定**
   只要 `Line.hpp` 不变，第三方代码通常不需要重新适配。

---

## 十、注意点

你现在这个版本有一个问题：只写了析构函数，但没有写拷贝构造函数和赋值运算符。

例如：

```cpp
Line line1(10, 20, 30, 40);
Line line2 = line1;
```

默认拷贝会导致两个对象的 `m_pimpl` 指向同一块堆空间，析构时会发生二次释放。

更完整的写法要么禁止拷贝：

```cpp
Line(const Line &) = delete;
Line & operator=(const Line &) = delete;
```

要么实现深拷贝。

如果暂时只要求完成基础 pimpl，上面的代码已经可以满足要求。
