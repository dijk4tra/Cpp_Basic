/*
编写程序：给定以下抽象类Figure，通过该图形类扩展生成3个不同的图形Rectangle、Circle、Triangle，体会使用纯虚函数的好处。

class Figure {
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

void display(Figure & fig) {
    cout << fig.getName() 
         << "的面积是:" 
         << fig.getArea() << endl ;
}

void test() {
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3, 4, 5);
    display(r);
    display(c);
    display(t);
}
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// 抽象类 Figure
class Figure {
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;

    // 虚析构函数
    virtual ~Figure() {}
};

// 矩形类
class Rectangle : public Figure
{
private:
    double m_length;
    double m_width;

public:
    Rectangle(double l, double w)
    : m_length(l), m_width(w)
    {}

    virtual string getName() const override 
    {
        return "Rectangle";
    }

    virtual double getArea() const override
    {
        return m_length * m_width;
    }
};

// 圆形类
class Circle : public Figure
{
private:
    double m_radius;

public:
    Circle(double r)
    : m_radius(r)
    {}

    virtual string getName() const override 
    {
        return "Circle";
    }

    virtual double getArea() const override
    {
        const double PI = 3.1415926;
        return PI * m_radius * m_radius;
    }
};

// 三角形类
class Triangle : public Figure 
{
private:
    double m_a;
    double m_b;
    double m_c;

public:
    Triangle(double x, double y, double z) : m_a(x), m_b(y), m_c(z) {}

    string getName() const override {
        return "Triangle";
    }

    double getArea() const override {
        // 使用海伦公式
        double p = (m_a + m_b + m_c) / 2;
        return sqrt(p * (p - m_a) * (p - m_b) * (p - m_c));
    }
};

// 显示图形面积
void display(Figure & fig) {
    cout << fig.getName()
         << "的面积是:"
         << fig.getArea() << endl;
}

void test1() {
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3, 4, 5);

    display(r);
    display(c);
    display(t);
}

int main() {
    test1();
    return 0;
}