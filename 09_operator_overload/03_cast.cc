#include <iostream>

using std::cout;
using std::endl;

/*
 * 类型转换：
 * 1. 基本类型 ----> 自定义类型
 * 2. 自定义类型 ----> 基本类型
 * 3. 自定义类型 ----> 另一个自定义类型
 *
 * 自定义类型转换为其他类型时，可以使用类型转换函数。
 *
 * 语法：
 * operator 目标类型()
 * {
 *     返回目标类型的数据或对象;
 * }
 */

class A
{
public:
    explicit // 显式构造函数：禁止通过该构造函数进行隐式类型转换
    A(int data)
    : m_data(data)
    {
        cout << "A(int)" << endl;
    }

    int m_data;
};


void test1()
{
    // 普通构造方式
    /* A a{ 1 }; */
    /* cout << a.m_data << endl; */

    // 类型转换场景
    // A a2 = 10; // int ----> A，自定义类型的隐式转换
                  // 编译器会自动调用 A(int) 构造函数
                  // 但由于 A(int) 被 explicit 修饰，因此该写法会报错
    // cout << a2.m_data << endl;
}


class Complex;

class Point
{
public:
    Point(int x, int y)
    : m_x(x), m_y(y)
    {}

    // 提供一个特殊参数的构造函数，用于支持 Complex ----> Point 的转换
    Point(const Complex & rhs);

    // 类型转换函数：Point ----> int
    operator int()
    {
        cout << "operator int()" << endl;
        return m_x + m_y;
    }

    // 也可以通过重载赋值运算符支持不同类型之间的赋值
    /* Point & operator=(const Point &); */
    /* Point & operator=(const Complex &); */

private:
    int m_x;
    int m_y;
};

// 测试自定义类型 ----> 基本类型
void test2()
{
    Point pt{1,2};

    int sum = pt; // Point ----> int，隐式类型转换
                  // 编译器会自动调用 operator int() 类型转换函数

    cout << sum << endl;
}

class Complex
{
public:
    Complex(int real, int image)
    : m_real(real)
    , m_image(image)
    {}

    // 类型转换函数：Complex ----> Point
    operator Point()
    {
        cout << "Complex:: Complex ----> Point" << endl;
        return Point{m_real, m_image};
    }

    // 将 Point 声明为友元类，使 Point 可以访问 Complex 的私有成员
    friend class Point;

private:
    int m_real;
    int m_image;
};

// 特殊参数构造函数的实现：Complex ----> Point
Point::Point(const Complex & rhs)
: m_x(rhs.m_real)
, m_y(rhs.m_image)
{};

// 测试自定义类型 ----> 另一个自定义类型
// 即 Complex 对象 ----> Point 对象
// 类型转换函数应该写在哪个类中，需要根据转换方向和设计需求决定
void test3()
{
    Point pt{ 1, 2 };
    Complex cx { 3, 4 };

    pt = cx;

    // 扩展：
    // 除了使用类型转换函数，还可以通过以下方式实现类型转换：
    // 1. 使用特殊参数的构造函数
    // 2. 重载赋值运算符
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}