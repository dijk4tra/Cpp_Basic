#include <iostream>

using std::cout;
using std::endl;

/**
 * 类型转换：
 *
 * C++ 中常见的类型转换可以分为几种：
 *
 * 1. 基本类型转换成自定义类型
 *    例如：
 *    int ---> A
 *
 * 2. 自定义类型转换成基本类型
 *    例如：
 *    Point ---> int
 *
 * 3. 自定义类型转换成另一个自定义类型
 *    例如：
 *    Complex ---> Point
 *
 * 基本类型转换成自定义类型：
 *
 * 通常可以通过构造函数完成。
 *
 * 自定义类型转换成其他类型：
 *
 * 通常可以通过类型转换函数完成。
 *
 * 类型转换函数的语法：
 *
 * operator 目标类型()
 * {
 *     return 目标类型的数据或者对象;
 * }
 *
 * 注意：
 * 类型转换函数没有返回值类型的位置。
 *
 * 例如：
 * operator int()
 *
 * 表示把当前对象转换成 int 类型。
 */

class A
{
public:
    /**
     * explicit 修饰构造函数。
     *
     * explicit 表示该构造函数只能用于显式构造，
     * 禁止编译器使用它进行隐式类型转换。
     *
     * 如果没有 explicit，
     * 那么下面这种写法可能成立：
     *
     * A a2 = 10;
     *
     * 编译器会把 int 类型的 10，
     * 隐式转换成 A 类型对象。
     *
     * 加上 explicit 之后，
     * A a2 = 10; 这种隐式转换写法会被禁止。
     */
    explicit
    A(int data)
    : m_data(data)
    {
        cout << "A(int)" << endl;
    }

    // 保存传入的数据
    int m_data;
};


void test1()
{
    /**
     * 一般的使用情况。
     *
     * 直接使用 int 参数构造 A 对象。
     *
     * 这是显式构造对象，
     * explicit 不会阻止这种写法。
     */
    /* A a{ 1 }; */
    /* cout << a.m_data << endl; */

    /**
     * 类型转换的情况。
     *
     * A a2 = 10;
     *
     * 这表示希望把 int 类型的 10，
     * 隐式转换成 A 类型对象。
     *
     * 如果 A(int) 构造函数没有 explicit，
     * 编译器会自动调用 A(int)，
     * 完成 int ---> A 的隐式类型转换。
     *
     * 但是当前构造函数加了 explicit，
     * 所以下面这行代码如果打开，
     * 会编译报错。
     */
    // A a2 = 10; // int ---> A，自定义类型，隐式类型转换
                 // 编译器会自动调用 A(int) 构造函数

    // cout << a2.m_data << endl;
}


class Complex;

class Point
{
public:
    /**
     * 有参构造函数。
     *
     * 用 x 初始化横坐标，
     * 用 y 初始化纵坐标。
     */
    Point(int x, int y)
    : m_x(x), m_y(y)
    {}

    /**
     * 特殊参数的构造函数。
     *
     * 参数是 Complex 类型对象。
     *
     * 作用：
     * 可以通过 Complex 对象构造 Point 对象。
     *
     * 也就是实现：
     * Complex ---> Point
     *
     * 注意：
     * 这里只能先写函数声明。
     *
     * 因为此时 Complex 只是前向声明，
     * 编译器还不知道 Complex 类中有哪些成员。
     * 所以函数实现要放到 Complex 完整定义之后。
     */
    Point(const Complex & rhs);

    /**
     * 类型转换函数。
     *
     * operator int()
     *
     * 表示：
     * 可以把 Point 对象转换成 int 类型。
     *
     * 表达式：
     * int sum = pt;
     *
     * 本质上会调用：
     * pt.operator int();
     *
     * 返回值：
     * 这里返回 m_x + m_y，
     * 表示把 Point 对象的两个坐标相加后，
     * 得到一个 int 值。
     */
    operator int()
    {
        cout << "operator int()" << endl;
        return m_x + m_y;
    }

    /**
     * 也可以通过赋值运算符完成类型之间的赋值。
     *
     * 例如：
     * Point & operator=(const Point &);
     * Point & operator=(const Complex &);
     *
     * 当前代码中没有展开实现。
     */
    /* Point & operator=(const Point &); */
    /* Point & operator=(const Complex &); */

private:
    // 横坐标
    int m_x;

    // 纵坐标
    int m_y;
};

// 自定义类型 ---> 基本类型
void test2()
{
    /**
     * 创建 Point 对象。
     */
    Point pt{1,2};

    /**
     * Point ---> int 的隐式类型转换。
     *
     * int sum = pt;
     *
     * 左边需要的是 int，
     * 右边给的是 Point 对象。
     *
     * 编译器会尝试寻找 Point 类中
     * 是否存在可以转换成 int 的类型转换函数。
     *
     * 当前 Point 中定义了：
     * operator int()
     *
     * 所以这里会自动调用 operator int()。
     */
    int sum = pt; // Point ---> int，隐式类型转换
                  // 编译器会自动调用 operator int() 函数

    cout << sum << endl;
}

class Complex
{
public:
    /**
     * 有参构造函数。
     *
     * real 初始化实部，
     * image 初始化虚部。
     */
    Complex(int real, int image)
    : m_real(real)
    , m_image(image)
    {}

    /**
     * 类型转换函数。
     *
     * operator Point()
     *
     * 表示：
     * 可以把 Complex 对象转换成 Point 对象。
     *
     * 表达式：
     * pt = cx;
     *
     * 当左边需要 Point，
     * 右边是 Complex 时，
     * 编译器可以调用该类型转换函数，
     * 先把 cx 转换成 Point 临时对象，
     * 再赋值给 pt。
     *
     * 返回值：
     * Point{m_real, m_image}
     *
     * 表示用复数的实部和虚部，
     * 构造一个 Point 对象。
     */
    operator Point()
    {
        cout << "Complex:: Complex-->Point" << endl;
        return Point{m_real, m_image};
    }

    /**
     * 把 Point 声明为 Complex 的友元类。
     *
     * 这样 Point 的成员函数，
     * 可以访问 Complex 的 private 成员：
     * m_real 和 m_image。
     *
     * 这里是为了让 Point(const Complex & rhs)
     * 能够直接访问 rhs.m_real 和 rhs.m_image。
     */
    friend class Point;

private:
    // 复数的实部
    int m_real;

    // 复数的虚部
    int m_image;
};

/**
 * 特殊参数构造函数的实现。
 *
 * Point::Point(const Complex & rhs)
 *
 * 表示：
 * 使用 Complex 对象构造 Point 对象。
 *
 * 因为 Complex 已经把 Point 声明为 friend，
 * 所以这里可以直接访问 rhs 的 private 成员：
 * rhs.m_real
 * rhs.m_image
 */
Point::Point(const Complex & rhs)
: m_x(rhs.m_real)
, m_y(rhs.m_image)
{};

// 测试自定义类型 ---> 另一个自定义类型转换
void test3()
{
    /**
     * 创建 Point 对象。
     */
    Point pt{ 1, 2 };

    /**
     * 创建 Complex 对象。
     */
    Complex cx { 3, 4 };

    /**
     * Complex 对象 ---> Point 类型对象。
     *
     * 表达式：
     * pt = cx;
     *
     * 左边 pt 是 Point 类型，
     * 右边 cx 是 Complex 类型。
     *
     * 两个类型不同，不能直接赋值。
     *
     * 编译器会尝试寻找可用的类型转换方式：
     *
     * 1. 在 Complex 类中查找：
     *    operator Point()
     *
     * 2. 在 Point 类中查找：
     *    Point(const Complex & rhs)
     *
     * 3. 或者查找：
     *    Point & operator=(const Complex &)
     *
     * 当前代码中同时提供了：
     * 1. Complex::operator Point()
     * 2. Point::Point(const Complex &)
     *
     * 这两个都能完成 Complex ---> Point。
     *
     * 注意：
     * 如果多个转换路径同时可用，
     * 有些场景可能会产生二义性。
     */
    pt = cx;

    /**
     * 扩展：
     *
     * 除了使用类型转换函数外，
     * 自定义类型之间转换还可以通过：
     *
     * 1. 使用参数特殊的构造函数
     *    Point(const Complex & rhs);
     *
     * 2. 使用赋值运算符函数
     *    Point & operator=(const Complex & rhs);
     *
     * 到底在哪个类里面写类型转换函数？
     *
     * 如果是：
     * Complex ---> Point
     *
     * 可以在 Complex 类中写：
     * operator Point()
     *
     * 表示 Complex 知道如何把自己转换成 Point。
     *
     * 也可以在 Point 类中写：
     * Point(const Complex &)
     *
     * 表示 Point 知道如何根据 Complex 构造自己。
     */
}

int main(int argc, char *argv[])
{
    /**
     * test1 测试基本类型 ---> 自定义类型。
     *
     * test2 测试自定义类型 ---> 基本类型。
     *
     * test3 测试自定义类型 ---> 另一个自定义类型。
     */
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}