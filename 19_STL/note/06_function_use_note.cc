#include <iostream>
#include <functional>
#include <cmath>
#include <string>

using namespace std;

/**
 * 使用 std::function + std::bind 实现函数式多态
 *
 * 1. 继承式多态
 *
 *    通过父类指针或引用指向子类对象，
 *    再调用虚函数，根据实际对象类型执行对应的函数版本。
 *
 *    例如：
 *
 *    Figure * p = &rect;
 *    p->area();
 *
 * 2. 函数式多态
 *
 *    使用 std::function 保存统一的调用形式，
 *    使用 std::bind 绑定不同对象的成员函数。
 *
 *    虽然 Rectangle::area 和 Circle::area 属于不同类，
 *    但它们最终都可以被 bind 成 double() 这种统一的调用形式。
 *
 *    这样 std::function<double()> 就可以在不同函数对象之间切换，
 *    从而达到类似“多态”的效果。
 *
 * 3. 本例核心
 *
 *    Circle::area 原始调用形式：
 *    double(Circle*)
 *
 *    Rectangle::area 原始调用形式：
 *    double(Rectangle*)
 *
 *    通过 bind 绑定具体对象后：
 *    double()
 */

 // 父类：抽象类
class Figure
{
public:
    // 纯虚函数：用于计算面积
    // 包含纯虚函数的类不能直接创建对象，只能作为抽象基类使用
    virtual double area() = 0;
};

class Rectangle : public Figure
{
public:
    Rectangle(double l, double w)
    : m_l(l)
    , m_w(w)
    {}

    // 重写父类的 area 函数，计算矩形面积
    double area() override
    {   
        cout << "Rectangle area" << endl;
        return m_l * m_w;
    }

    double m_l; // 矩形长度
    double m_w; // 矩形宽度
};

class Circle : public Figure
{
public:
    Circle(double r)
    : m_r(r)
    {}

    // 重写父类的 area 函数，计算圆形面积
    double area() override
    {   
        cout << "Circle area" << endl;
        return M_PI * m_r * m_r;
    }

    double m_r; // 圆形半径
};

void test1()
{
    Rectangle rect(1, 2);
    Circle circle(3);

    // 继承式多态：
    // 父类指针指向子类对象，通过虚函数实现动态绑定
    Figure * p = &rect;
    cout << p->area() << endl;

    // 同一个父类指针指向不同子类对象时，
    // 调用的是不同子类重写后的 area 函数
    p = &circle;
    cout << p->area() << endl;
}

void test2()
{
    Rectangle rect(1, 2);
    Circle circle(3);

    // 函数式多态：
    // 使用 std::function 保存统一的调用形式 double()
    std::function<double()> f;

    // &Circle::area 是成员函数指针
    //
    // 成员函数本身需要依赖对象调用：
    // double(Circle*)
    //
    // 使用 bind 绑定对象地址 &circle 后，
    // 调用形式变为：
    // double()
    f = bind(&Circle::area, &circle);
    cout << f() << endl;

    cout << "---------" << endl;

    // 同一个 std::function<double()>，
    // 可以继续保存 Rectangle::area 绑定后的结果
    //
    // &Rectangle::area 原始调用形式可以理解为：
    // double(Rectangle*)
    //
    // bind 绑定对象地址 &rect 后，
    // 调用形式同样变为：
    // double()
    f = bind(&Rectangle::area, &rect);
    cout << f() << endl;
}

int main()
{
    // test1();
    test2();

    return 0;
}