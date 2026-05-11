**如何让 `Complex` 对象接收一个 `Point` 对象的赋值**。

```cpp
Point pt(8, 9);
Complex cx(4, 6);
cx = pt;
cx.print();
```

假设：

* `Point` 表示平面点，有 `x, y`
* `Complex` 表示复数，有 `real, imag`
* 希望 `cx = pt;` 后，`cx` 变成 `8 + 9i`

可以用三种方式实现。

---

## 方式一：在 `Complex` 中重载赋值运算符

这是最直接、最推荐理解的一种方式。

```cpp
#include <iostream>
using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }
};

class Complex {
private:
    int real, imag;

public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}

    Complex& operator=(const Point& pt) {
        real = pt.getX();
        imag = pt.getY();
        return *this;
    }

    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Point pt(8, 9);
    Complex cx(4, 6);

    cx = pt;
    cx.print();

    return 0;
}
```

输出：

```cpp
8 + 9i
```

### 意义

这表示：**Complex 类主动规定自己如何接收一个 Point 对象赋值。**

也就是说，`cx = pt;` 被解释为：

```cpp
cx.operator=(pt);
```

这种方式最符合“赋值操作”的语义。

---

## 方式二：在 `Complex` 中定义转换构造函数

让 `Point` 可以先被转换成一个临时的 `Complex` 对象，然后再赋值给 `cx`。

```cpp
#include <iostream>
using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }
};

class Complex {
private:
    int real, imag;

public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}

    Complex(const Point& pt) {
        real = pt.getX();
        imag = pt.getY();
    }

    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Point pt(8, 9);
    Complex cx(4, 6);

    cx = pt;
    cx.print();

    return 0;
}
```

### 意义

这里 `cx = pt;` 的过程大致是：

```cpp
cx = Complex(pt);
```

也就是：

1. 先用 `pt` 构造一个临时的 `Complex` 对象；
2. 再调用 `Complex` 默认的赋值运算符，把临时对象赋给 `cx`。

这种方式表达的是：**Point 可以被看作一种 Complex。**

---

## 方式三：在 `Point` 中定义类型转换函数

让 `Point` 自己知道如何转换成 `Complex`。

```cpp
#include <iostream>
using namespace std;

class Complex {
private:
    int real, imag;

public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}

    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

class Point {
private:
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}

    operator Complex() const {
        return Complex(x, y);
    }
};

int main() {
    Point pt(8, 9);
    Complex cx(4, 6);

    cx = pt;
    cx.print();

    return 0;
}
```

### 意义

这里 `cx = pt;` 的过程大致是：

```cpp
cx = pt.operator Complex();
```

也就是 `Point` 对象主动把自己转换成一个 `Complex` 对象。

这种方式表达的是：**Point 知道如何把自己变成 Complex。**

---

## 三种方式对比

| 实现方式                               | 写在哪里         | 核心思想                    | 推荐程度 |
| ---------------------------------- | ------------ | ----------------------- | ---- |
| 重载 `Complex::operator=(Point)`     | `Complex` 类中 | Complex 知道如何接收 Point 赋值 | 很推荐  |
| 转换构造函数 `Complex(Point)`            | `Complex` 类中 | Point 可以构造出 Complex     | 推荐   |
| 类型转换函数 `Point::operator Complex()` | `Point` 类中   | Point 知道如何变成 Complex    | 谨慎使用 |

---

## 建议你重点体会

这三种方式都能让下面代码成立：

```cpp
cx = pt;
```

但是它们的含义不同：

```cpp
// 方式一
Complex 接收 Point

// 方式二
Point 被用来构造 Complex

// 方式三
Point 主动转换成 Complex
```

学习时建议你分别运行三份代码，并在关键函数里加输出：

```cpp
cout << "调用 Complex::operator=(Point)" << endl;
```

或者：

```cpp
cout << "调用 Complex(Point)" << endl;
```

这样你能清楚看到编译器到底选择了哪一种方式。
