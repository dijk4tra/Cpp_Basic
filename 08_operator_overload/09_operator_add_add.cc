#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>

using namespace std;

/**
 * operator++ 运算符的重载
 * 
 * int a = 1;
 * a++;  // 后置++
 * ++a;  // 前置++
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

    // 成员函数形式重载 operator+=
    // 返回值：当前对象自身的引用
    // 参数：右操作数 rhs
    Complex & operator+=(const Complex & rhs)
    {
        cout << "成员函数形式重载 operator+=" << endl;

        this->m_real += rhs.m_real;
        this->m_image += rhs.m_image;

        // 返回当前对象自身
        return *this;
    }

    // 前置++：operator++()
    // 参数：无参数
    // 返回值：当前对象自身的引用
    Complex & operator++()
    {   
        cout << "前置++：成员函数形式，对象的值会发生变化" << endl;

        this->m_real += 1;
        this->m_image += 1;

        return *this;
    }

    // 后置++：operator++(int)
    // 参数：int 类型的占位参数，用于区分前置++和后置++
    // 返回值：自增前状态的临时对象
    // C++ 规定：后置++必须带一个 int 类型的占位参数，且该参数不能设置默认值
    // 该占位参数只用于语法区分，函数体内通常不使用
    Complex operator++(int)
    {
        cout << "后置++：成员函数形式，对象的值会发生变化" << endl;

        // 保存当前对象自增前的状态
        Complex temp = *this;

        // 当前对象执行自增操作
        this->m_real += 1;
        this->m_image += 1;

        // 返回自增前保存的状态
        return temp;
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

void test1()
{
    /* int a = 1; */
    /* &(++a); // 前置++返回左值 */
    /* &(a++); // 后置++返回右值 */

    Complex cx {1, 1};

    // 前置++：成员函数形式，对象的值会发生变化
    // 返回值：当前对象自身的引用，因此可以作为左值使用
    // 本质：cx.operator++();
    ++cx;

    cout << cx << endl; 
}

void test2()
{
    Complex cx {1, 1};

    // 后置++：成员函数形式，对象的值会发生变化
    // 返回值：自增前状态的临时对象，因此不能作为左值使用
    Complex cx2 = cx++; 

    // 本质：cx.operator++(0);
    cout << cx << endl;
    cout << cx2 << endl;
}


int main(int argc, char *argv[])
{
    test1();

    return 0;
}