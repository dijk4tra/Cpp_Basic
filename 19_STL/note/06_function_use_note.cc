#include <iostream>
#include <functional>
#include <cmath>
#include <string>

using namespace std;


/**
 * 使用 std::function + std::bind 实现函数式多态
 *
 * 本例对比两种“多态”方式：
 *
 * 1. 继承式多态
 *
 * 继承式多态依赖：
 * 1. 父类
 * 2. 子类
 * 3. 虚函数
 * 4. 父类指针或父类引用
 *
 * 通过父类指针或引用指向不同子类对象，
 * 再调用虚函数，
 * 程序会根据对象的真实类型，
 * 执行对应子类重写后的函数版本。
 *
 *
 * 例如：
 *
 * Figure * p = &rect;
 * p->area();
 *
 * 此时 p 指向 Rectangle 对象，
 * 所以调用 Rectangle::area。
 *
 * 如果：
 *
 * p = &circle;
 * p->area();
 *
 * 此时 p 指向 Circle 对象，
 * 所以调用 Circle::area。
 *
 *
 * 这种方式称为动态多态，
 * 也就是运行时多态。
 *
 *
 * 2. 函数式多态
 *
 * 函数式多态不一定依赖继承体系。
 *
 * 它的核心是：
 *
 * 使用 std::function 保存统一的调用形式，
 * 使用 std::bind 把不同对象的不同成员函数，
 * 适配成同一种调用形式。
 *
 *
 * 在本例中：
 *
 * Circle::area 和 Rectangle::area 属于不同类。
 *
 * 它们原本的调用方式不同：
 *
 * circle.area();
 * rect.area();
 *
 * 如果直接看成员函数指针，
 * 它们的类型也不同：
 *
 * &Circle::area
 * &Rectangle::area
 *
 *
 * 但是使用 bind 绑定具体对象之后，
 * 二者都可以变成统一的调用形式：
 *
 * double()
 *
 * 也就是：
 *
 * 不需要参数，
 * 返回 double。
 *
 *
 * 因此：
 *
 * std::function<double()> f;
 *
 * 既可以保存：
 *
 * bind(&Circle::area, &circle)
 *
 * 也可以保存：
 *
 * bind(&Rectangle::area, &rect)
 *
 *
 * 这样同一个 std::function<double()> 对象 f，
 * 就可以在不同的函数对象之间切换，
 * 达到类似“多态”的效果。
 *
 *
 * 3. 二者区别
 *
 * 继承式多态：
 * 通过“对象真实类型 + 虚函数表”决定调用哪个函数。
 *
 * 函数式多态：
 * 通过“std::function 保存的具体可调用对象”决定调用哪个函数。
 *
 *
 * 继承式多态强调：
 * 不同类之间有共同父类和统一接口。
 *
 * 函数式多态强调：
 * 不同可调用对象能被适配成统一调用形式。
 */


/**
 * Figure
 *
 * 图形类。
 *
 * 这是一个抽象基类。
 *
 * 抽象基类：
 * 含有纯虚函数的类。
 *
 * 抽象基类不能直接创建对象，
 * 通常用于作为父类，
 * 为子类提供统一接口。
 */
class Figure
{
public:
    /**
     * 纯虚函数 area
     *
     * virtual 表示虚函数。
     *
     * = 0 表示纯虚函数。
     *
     * 纯虚函数没有在父类中给出具体实现，
     * 而是要求子类必须重写这个函数。
     *
     *
     * area 的作用：
     * 计算图形面积。
     *
     * 返回值：
     * double 类型的面积。
     */
    virtual double area() = 0;
};


/**
 * Rectangle
 *
 * 矩形类。
 *
 * public Figure 表示：
 * Rectangle 公开继承 Figure。
 *
 * Rectangle 是 Figure 的子类。
 *
 * 因为 Figure 中有纯虚函数 area，
 * 所以 Rectangle 必须重写 area，
 * 否则 Rectangle 仍然是抽象类。
 */
class Rectangle : public Figure
{
public:
    /**
     * 构造函数
     *
     * Rectangle(double l, double w)
     *
     * 参数：
     * l 表示矩形长度。
     * w 表示矩形宽度。
     *
     * 初始化列表：
     *
     * : m_l(l)
     * , m_w(w)
     *
     * 表示用参数 l 初始化成员变量 m_l，
     * 用参数 w 初始化成员变量 m_w。
     */
    Rectangle(double l, double w)
    : m_l(l)
    , m_w(w)
    {}

    /**
     * 重写父类的 area 函数
     *
     * override 表示该函数重写了父类中的虚函数。
     *
     * 好处：
     * 编译器会帮忙检查函数签名是否真的匹配父类虚函数。
     *
     * 如果函数名、参数列表、const 属性等写错，
     * 编译器会直接报错。
     *
     *
     * 矩形面积公式：
     *
     * 面积 = 长 × 宽
     */
    double area() override
    {
        cout << "Rectangle area" << endl;
        return m_l * m_w;
    }

    // 矩形长度
    double m_l;

    // 矩形宽度
    double m_w;
};


/**
 * Circle
 *
 * 圆形类。
 *
 * Circle 也公开继承 Figure，
 * 因此也必须重写 Figure 中的纯虚函数 area。
 */
class Circle : public Figure
{
public:
    /**
     * 构造函数
     *
     * Circle(double r)
     *
     * 参数：
     * r 表示圆形半径。
     *
     * 初始化列表：
     *
     * : m_r(r)
     *
     * 表示用参数 r 初始化成员变量 m_r。
     */
    Circle(double r)
    : m_r(r)
    {}

    /**
     * 重写父类的 area 函数
     *
     * 圆形面积公式：
     *
     * 面积 = π × 半径 × 半径
     *
     * M_PI 是 <cmath> 中常见的圆周率宏。
     *
     * 注意：
     * M_PI 并不是 C++ 标准强制要求提供的宏。
     * 在部分编译器或平台上可能需要额外开启宏定义，
     * 或者自己定义 π。
     */
    double area() override
    {
        cout << "Circle area" << endl;
        return M_PI * m_r * m_r;
    }

    // 圆形半径
    double m_r;
};


/**
 * test1
 *
 * 演示继承式多态。
 *
 * 通过父类指针 Figure* 指向不同的子类对象，
 * 调用同名虚函数 area。
 *
 * 程序运行时会根据实际指向的对象类型，
 * 执行对应子类的 area 函数。
 */
void test1()
{
    // 创建矩形对象
    Rectangle rect(1, 2);

    // 创建圆形对象
    Circle circle(3);

    /**
     * 父类指针指向子类对象
     *
     * Figure * p = &rect;
     *
     * p 的静态类型是 Figure*，
     * 但它实际指向的是 Rectangle 对象。
     *
     * 因为 area 是虚函数，
     * 所以通过 p 调用 area 时，
     * 会发生动态绑定。
     *
     * 实际执行：
     *
     * Rectangle::area()
     */
    Figure * p = &rect;
    cout << p->area() << endl;

    /**
     * 同一个父类指针可以指向另一个子类对象。
     *
     * 此时 p 指向 Circle 对象。
     *
     * 再次调用：
     *
     * p->area()
     *
     * 实际执行：
     *
     * Circle::area()
     */
    p = &circle;
    cout << p->area() << endl;
}


/**
 * test2
 *
 * 演示函数式多态。
 *
 * 核心思路：
 *
 * 使用 std::function<double()> 作为统一接口。
 *
 * 只要某个可调用对象满足：
 *
 * 1. 不需要参数
 * 2. 返回 double
 *
 * 就可以保存到 f 中。
 *
 *
 * Circle::area 和 Rectangle::area
 * 原本是不同类中的成员函数。
 *
 * 通过 std::bind 绑定具体对象之后，
 * 都可以适配成 double() 形式。
 */
void test2()
{
    // 创建矩形对象
    Rectangle rect(1, 2);

    // 创建圆形对象
    Circle circle(3);

    /**
     * 定义 std::function 对象
     *
     * std::function<double()> f;
     *
     * 表示：
     * f 可以保存任意满足下面调用形式的可调用对象：
     *
     * double()
     *
     * 也就是：
     * 不需要参数，
     * 返回 double。
     */
    std::function<double()> f;

    /**
     * 绑定 Circle::area
     *
     * &Circle::area 是成员函数指针。
     *
     * 成员函数必须依赖对象调用。
     *
     * &Circle::area 原始调用形式可以理解为：
     *
     * double(Circle*)
     *
     * 其中 Circle* 用来说明：
     * 调用哪个 Circle 对象的 area 函数。
     *
     *
     * bind(&Circle::area, &circle)
     *
     * 表示：
     * 把成员函数所属对象固定为 &circle。
     *
     * 绑定之后，
     * 新的调用形式变成：
     *
     * double()
     *
     * 所以可以赋值给：
     *
     * std::function<double()> f
     *
     *
     * 调用：
     *
     * f()
     *
     * 等价于：
     *
     * circle.area()
     */
    f = bind(&Circle::area, &circle);

    cout << f() << endl;

    cout << "---------" << endl;

    /**
     * 绑定 Rectangle::area
     *
     * 同一个 std::function<double()> f，
     * 可以重新保存另一个满足 double() 调用形式的可调用对象。
     *
     *
     * &Rectangle::area 原始调用形式可以理解为：
     *
     * double(Rectangle*)
     *
     *
     * bind(&Rectangle::area, &rect)
     *
     * 表示：
     * 把成员函数所属对象固定为 &rect。
     *
     * 绑定之后，
     * 新的调用形式同样变成：
     *
     * double()
     *
     *
     * 因此它也可以赋值给 f。
     *
     * 调用：
     *
     * f()
     *
     * 等价于：
     *
     * rect.area()
     */
    f = bind(&Rectangle::area, &rect);

    cout << f() << endl;
}


int main()
{
    // test1();

    // 当前测试 std::function + std::bind 实现函数式多态
    test2();

    return 0;
}