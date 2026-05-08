#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>

using namespace std;

/**
 * 输入、输出运算符的重载
 */

class Complex
{
public:
    Complex() = default;

    Complex(int real, int image)
    : m_real(real)
    , m_image(image)
    {}

    int getReal() const
    {
        return m_real;
    }

    int getImage() const
    {
        return m_image;
    }
    
    void print()
    {
        cout << m_real << "+" << m_image << "i" << endl;
    }
    
    // 将普通函数 operator+ 声明为友元函数
    friend
    Complex operator+(const Complex & lhs, const Complex & rhs);
    
    // 成员函数形式重载 operator+
    // 返回值：Complex 对象
    // 参数：右操作数 rhs
    // this 指向当前对象，也就是左操作数
    Complex operator+(const Complex & rhs)
    {
        return Complex{this->m_real + rhs.m_real, this->m_image + rhs.m_image};
    }

    // 将普通函数 operator<< 声明为友元函数
    friend
    ostream & operator<<(ostream & os, const Complex & cx);
    
    // 将普通函数 operator>> 声明为友元函数
    friend
    istream & operator>>(istream & is, Complex & cx);

private:
    int m_real;
    int m_image;
};

/*
// 普通函数形式
Complex operator+(const Complex & lhs, const Complex & rhs)
{
    return Complex{lhs.getReal() + rhs.getReal(), lhs.getImage() + rhs.getImage()};
}
*/

/*
// 友元函数形式
Complex operator+(const Complex & lhs, const Complex & rhs)
{
    return Complex{lhs.m_real + rhs.m_real, lhs.m_image + rhs.m_image};
}
*/

// 使用友元函数形式重载 operator<<
ostream & operator<<(ostream & os, const Complex & cx)
{
    os << cx.m_real << "+" << cx.m_image << "i";

    // 返回流对象，以支持链式输出
    return os;
}

void test1()
{
    Complex cx {1, 1};
    cout << cx << endl;

    // 本质：普通函数调用
    /* operator<<(cout, cx); */
}


/**
 * 通过键盘输入 Complex 对象的实部和虚部
 */
// 重载 operator>>
istream & operator>>(istream & is, Complex & cx)
{
    is >> cx.m_real >> cx.m_image;

    // 返回流对象，以支持链式输入
    return is;
}

void test2()
{
    Complex cx;
    cout << "input real image: " << endl;
    cin >> cx;

    // 本质：普通函数调用
    // operator>>(cin, cx);

    cout << cx << endl;
}

/**
 * 思考题：
 *
 * class A
 * {
 * private:
 *     int m_dataA;
 * };
 *
 * class B
 * {
 * private:
 *     int m_dataB;
 *     A m_a;
 * };
 * 
 * B b;
 * cout << b << endl;
 *
 * ostream & operator<<(ostream & os, const B & b)
 * {
 *     os << b.m_dataB << b.m_a;
 *     return os;
 * }
 *
 * ostream & operator<<(ostream & os, const A & a)
 * {
 *     os << a.m_dataA;
 *     return os;
 * }
 *
 * 如果 B 类中包含 A 类对象，那么输出 B 对象时，
 * 可以在 B 的 operator<< 中继续调用 A 的 operator<<。
 */

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();
    return 0;
}