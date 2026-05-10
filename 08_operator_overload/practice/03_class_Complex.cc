#include <iostream>

using std::cout;
using std::endl;

class Complex
{
private:
    double real; // 实部
    double imag; // 虚部

public:
    // 构造函数
    Complex(double r = 0, double i = 0)
    {
        real = r;
        imag = i;
    }
    
    // 重载 + 运算符
    Complex operator+(const Complex& rhs) const
    {
        return Complex(real + rhs.real, imag + rhs.imag);
    }

    // 重载 - 运算符
    Complex operator-(const Complex& rhs) const
    {
        return Complex(real - rhs.real, imag - rhs.imag);
    }

    // 重载 += 运算符
    Complex& operator+=(const Complex& rhs)
    {
        real += rhs.real;
        imag += rhs.imag;
        return *this;
    }

    // 重载 -= 运算符
    Complex& operator-=(const Complex& rhs)
    {
        real -= rhs.real;
        imag -= rhs.imag;
        return *this;
    }

    // 前置自增 ++c
    Complex& operator++()
    {
        real++;
        imag++;
        return *this;
    }

    // 后置自增 c++
    Complex operator++(int)
    {
        Complex temp = *this;
        real++;
        imag++;
        return temp;
    }

    // 前置自减 --c
    Complex& operator--() {
        real--;
        imag--;
        return *this;
    }

    // 后置自减 c--
    Complex operator--(int) {
        Complex temp = *this;
        real--;
        imag--;
        return temp;
    }

    // 显示复数
    void display() const
    {
        if(imag >= 0)
        {
            cout << real << " + " << imag << "i" << endl;
        }else{
            cout << real << " - " << -imag << "i" << endl;
        }
    }
};


int main(int argc, char *argv[])
{
    Complex c1(3, 4);
    Complex c2(1, 2);

    Complex c3;

    cout << "c1 = ";
    c1.display();

    cout << "c2 = ";
    c2.display();

    c3 = c1 + c2;
    cout << "c1 + c2 = ";
    c3.display();

    c3 = c1 - c2;
    cout << "c1 - c2 = ";
    c3.display();

    c1 += c2;
    cout << "c1 += c2 后，c1 = ";
    c1.display();

    c1 -= c2;
    cout << "c1 -= c2 后，c1 = ";
    c1.display();

    ++c1;
    cout << "++c1 后，c1 = ";
    c1.display();

    c1++;
    cout << "c1++ 后，c1 = ";
    c1.display();

    --c1;
    cout << "--c1 后，c1 = ";
    c1.display();

    c1--;
    cout << "c1-- 后，c1 = ";
    c1.display();

    return 0;
}

