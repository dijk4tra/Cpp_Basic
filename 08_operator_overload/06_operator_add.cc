#include <iostream>
#include <iterator>

using std::cout;
using std::endl;

/**
 * 实现一个复数类，并重载 operator+ 运算符。
 * 加法规则：实部与实部相加，虚部与虚部相加。
 *
 * 运算符重载的常见形式：
 * 1. 普通函数形式
 * 2. 友元函数形式
 * 3. 成员函数形式
 */

class Complex
{
public:
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

    // 将普通函数声明为友元函数，使其可以访问类的私有成员
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

private:
    int m_real;
    int m_image;
};

/*
// 普通函数形式：返回的是临时对象，因此返回值不能写成引用
Complex operator+(const Complex & lhs, const Complex & rhs)
{
    return Complex{lhs.getReal() + rhs.getReal(), lhs.getImage() + rhs.getImage()};
}
*/

/*
// 友元函数形式：返回的是临时对象，因此返回值不能写成引用
Complex operator+(const Complex & lhs, const Complex & rhs)
{
    return Complex{lhs.m_real + rhs.m_real, lhs.m_image + rhs.m_image};
}
*/


void test1()
{
    int a = 1;
    int b = 2;
    a + b; // 运算结果是一个临时值，属于右值
    
    // 将内置类型的加法逻辑推广到自定义类型
    Complex cx1 {1,1};
    Complex cx2 {2,2};

    // 使用普通函数或友元函数形式重载的 operator+
    Complex cx3 = cx1 + cx2;

    // 本质：普通函数调用
    /* operator+(cx1, cx2); */

    cx3.print();
}

void test2()
{
    Complex cx1 {1,1};
    Complex cx2 {2,2};

    // 使用成员函数形式重载的 operator+
    Complex cx3 = cx1 + cx2;

    // 本质：成员函数调用
    /* cx1.operator+(cx2); */

    cx3.print();
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();
    return 0;
}