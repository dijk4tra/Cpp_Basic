#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>

using namespace std;

/**
 * operator+= 运算符的重载
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

    // 成员函数形式重载 operator+=
    // 返回值：当前对象自身的引用，便于支持连续赋值或链式操作
    // 参数：右操作数 rhs
    Complex & operator+=(const Complex & rhs)
    {
        cout << "成员函数形式重载 operator+=" << endl;

        this->m_real += rhs.m_real;
        this->m_image += rhs.m_image;

        // 返回当前对象自身
        return *this;
    }

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
    // 内置类型的 += 运算
    int a = 1;
    int b = 2;
    b += a; 

    Complex cx1 {1, 1};
    Complex cx2 {2, 2};

    // 自定义类型的 += 运算
    cx1 += cx2; 

    // 本质：成员函数调用
    // cx1.operator+=(cx2);

    cout << cx1 << endl;
}

int main(int argc, char *argv[])
{
    test1();

    return 0;
}