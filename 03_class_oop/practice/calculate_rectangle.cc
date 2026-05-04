#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Rectangle
{
private:
    double m_length;
    double m_width;

public:
    // 构造函数
    Rectangle(double l, double w)
    {
        m_length = l;
        m_width = w;
    }

    // 计算周长
    double getPerimeter()
    {
        return 2 * (m_length + m_width);
    }

    // 计算面积
    double getArea()
    {
        return m_length * m_width;
    }

    // 打印结果
    void print_result()
    {
        cout << "长方形的长为: " << m_length << endl;
        cout << "长方形的宽为: " << m_width << endl;
        cout << "长方形的周长为: " << getPerimeter() << endl;
        cout << "长方形的面积为: " << getArea() << endl;
    }
};


int main(int argc, char *argv[])
{
    double l, w;
    
    cout << "请输入长方形的长: ";
    cin >> l;

    cout << "请输入长方形的宽: ";
    cin >> w;

    Rectangle rect(l, w);
    rect.print_result();

    return 0;
}

