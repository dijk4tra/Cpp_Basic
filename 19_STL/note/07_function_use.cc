#include <iostream>
#include <functional>
#include <vector>

using namespace std;

/**
 * 使用 std::function + std::bind 实现函数式多态
 *
 * 1. 核心思想
 *
 *    std::function 可以保存统一调用形式的可调用对象；
 *    std::bind 可以把不同类的成员函数和具体对象绑定起来，
 *    使它们最终变成相同的调用形式。
 *
 * 2. 本例中
 *
 *    Rectangle::area 原始调用形式可以理解为：
 *    double(Rectangle*)
 *
 *    Circle::area 原始调用形式可以理解为：
 *    double(Circle*)
 *
 *    使用 bind 绑定具体对象后：
 *    double()
 *
 *    因此可以统一保存到 function<double()> 中。
 *
 * 3. 回调函数
 *
 *    Figure 类中并没有使用继承和虚函数，
 *    而是通过保存一个 function<double()> 类型的回调函数，
 *    在需要时调用这个回调函数来计算面积。
 */

class Figure
{
public:
    // 定义一种函数包装器类型：
    // AreaCall 表示返回值为 double、无参数的可调用对象
    //
    // 这里相当于把 function<double()> 起了一个别名，
    // 后续可以把它作为统一的“接口”使用
    using AreaCall = function<double()>;

    // 注册回调函数：
    // 外部把一个符合 double() 调用形式的可调用对象传进来，
    // Figure 内部保存起来，之后需要时再调用
    void setAreaCall(AreaCall areaCall)
    {
        m_areaCall = areaCall;
    }

    // 调用已经注册的回调函数
    void handleAreaCall()
    {
        // std::function 可以转换为 bool
        // 用于判断当前是否保存了有效的可调用对象
        if(m_areaCall)
        {
            cout << "invoke....." << endl;

            // 调用回调函数，得到面积结果
            cout << "area:" << m_areaCall() << endl;
        }
    }

    // 保存回调函数对象
    AreaCall m_areaCall;
};

class Rectangle
{
public:
    Rectangle(double l, double w)
    : m_l(l)
    , m_w(w)
    {
    }

    // 计算矩形面积
    double area()
    {
        cout << "Rectangle area" << endl;
        return m_l * m_w;
    }

    double m_l; // 矩形长度
    double m_w; // 矩形宽度
};

class Circle 
{
public:
    Circle(double r)
    : m_r(r)
    {
    }

    // 计算圆形面积
    double area()
    {
        cout << "Circle area" << endl;
        return m_r * m_r * 3.14;
    }

    double m_r; // 圆形半径
};

void test1()
{
    Rectangle r(1, 2); // Rectangle::area 原始调用形式可以理解为 double(Rectangle*)
    Circle c(3);       // Circle::area 原始调用形式可以理解为 double(Circle*)

    Figure figure;

    // bind 绑定 Rectangle 对象地址 &r 后，
    // &Rectangle::area 的调用形式从 double(Rectangle*) 变为 double()
    //
    // setAreaCall 接收 function<double()>，
    // 因此可以保存 bind 之后的结果
    figure.setAreaCall(bind(&Rectangle::area, &r));
    figure.handleAreaCall();

    cout << "-------" << endl;

    // 同一个 Figure 对象中保存的回调函数可以被替换
    //
    // bind 绑定 Circle 对象地址 &c 后，
    // &Circle::area 的调用形式从 double(Circle*) 变为 double()
    figure.setAreaCall(bind(&Circle::area, &c));
    figure.handleAreaCall();
}

/**
 * 注意：
 *
 * lambda 捕获局部变量引用时，要特别注意生命周期问题。
 *
 * 如果 lambda 被保存起来，并且在局部变量销毁之后才调用，
 * 那么 lambda 中引用的局部变量已经失效，
 * 此时继续访问会产生未定义行为。
 */

// 保存多个无参数、无返回值的可调用对象
vector<function<void()>> functions;

void func()
{
    // 局部变量：
    // func 执行结束后，num1 和 num2 的生命周期结束
    double num1 = 3.14;
    int num2 = 2;

    functions.push_back(
        // [&] 表示以引用方式捕获当前作用域中的局部变量
        //
        // 注意：
        // 这里 lambda 被保存到了全局 vector 中，
        // 当 func 结束后，num1 和 num2 已经销毁。
        //
        // 后续再调用这个 lambda 时，
        // 访问 num1 和 num2 会产生未定义行为。
        [&]()->void{
            cout << "num1:" << num1 << endl;
            cout << "num2:" << num2 << endl;
        }
    );
}

void test2()
{
    func();

    for(auto & f : functions)
    {
        // 调用 function 对象
        //
        // 注意：
        // 当前示例中，f 内部保存的 lambda 引用了 func 中的局部变量，
        // 而这些局部变量在 func 返回后已经销毁。
        // 因此这里调用 f() 存在生命周期问题。
        f();
    }
}

int main(int argc, char const *argv[])
{
    // test1();
    test2();

    return 0;
}