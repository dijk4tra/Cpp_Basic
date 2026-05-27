#include <iostream>
#include <functional>
#include <vector>

using namespace std;


/**
 * 使用 std::function + std::bind 实现函数式多态
 *
 * 1. 核心思想
 *
 * std::function 可以保存统一调用形式的可调用对象。
 *
 * std::bind 可以把不同类的成员函数和具体对象绑定起来，
 * 使它们最终变成相同的调用形式。
 *
 *
 * 例如：
 *
 * Rectangle::area 原始调用形式可以理解为：
 *
 * double(Rectangle*)
 *
 * Circle::area 原始调用形式可以理解为：
 *
 * double(Circle*)
 *
 *
 * 使用 bind 绑定具体对象后：
 *
 * bind(&Rectangle::area, &r)
 * bind(&Circle::area, &c)
 *
 * 二者都会变成：
 *
 * double()
 *
 *
 * 因此：
 *
 * function<double()> f;
 *
 * 既可以保存绑定后的 Rectangle::area，
 * 也可以保存绑定后的 Circle::area。
 *
 *
 * 2. 回调函数 callback
 *
 * 回调函数可以理解为：
 *
 * “先把某个函数保存起来，
 *  等到合适的时候再调用。”
 *
 *
 * 本例中的 Figure 类并没有使用继承和虚函数。
 *
 * Figure 内部保存了一个：
 *
 * function<double()>
 *
 * 类型的回调函数。
 *
 * 外部可以把不同图形的 area 函数绑定后传进来，
 * Figure 内部在需要时调用这个回调函数。
 *
 *
 * 这种方式不要求 Rectangle 和 Circle 继承 Figure。
 *
 * 只要它们的成员函数经过 bind 后，
 * 都能适配成 double() 调用形式，
 * 就可以统一交给 Figure 使用。
 *
 *
 * 3. 和继承式多态的区别
 *
 * 继承式多态：
 * 通过父类指针或引用调用虚函数。
 * 要求子类和父类之间有继承关系。
 *
 * 函数式多态：
 * 通过 std::function 保存统一调用形式。
 * 不要求类之间有继承关系。
 *
 *
 * 4. 本例第二部分
 *
 * 还演示了 lambda 引用捕获局部变量时的生命周期问题。
 *
 * 如果 lambda 通过引用捕获局部变量，
 * 并且这个 lambda 被保存到更长生命周期的对象中，
 * 那么当局部变量销毁后再调用 lambda，
 * 就会访问已经失效的引用。
 *
 * 这种行为是未定义行为。
 */


class Figure
{
public:
    /**
     * 类型别名 AreaCall
     *
     * using AreaCall = function<double()>;
     *
     * 表示：
     * AreaCall 是 function<double()> 的别名。
     *
     *
     * function<double()> 表示一种统一的调用形式：
     *
     * double()
     *
     * 即：
     * 不需要参数，
     * 返回 double。
     *
     *
     * 后续只要某个可调用对象满足这种调用形式，
     * 就可以保存到 AreaCall 中。
     */
    using AreaCall = function<double()>;


    /**
     * setAreaCall
     *
     * 注册回调函数。
     *
     * 参数 areaCall 的类型是 AreaCall，
     * 也就是 function<double()>。
     *
     *
     * 外部可以传入任意满足 double() 调用形式的可调用对象。
     *
     * 例如：
     *
     * bind(&Rectangle::area, &r)
     *
     * 或：
     *
     * bind(&Circle::area, &c)
     *
     *
     * setAreaCall 会把传进来的可调用对象保存到成员变量 m_areaCall 中。
     *
     * 之后 Figure 就可以在合适的时候调用它。
     */
    void setAreaCall(AreaCall areaCall)
    {
        m_areaCall = areaCall;
    }


    /**
     * handleAreaCall
     *
     * 执行已经注册的回调函数。
     */
    void handleAreaCall()
    {
        /**
         * std::function 可以转换为 bool。
         *
         * 如果 std::function 内部保存了有效的可调用对象，
         * 转换结果为 true。
         *
         * 如果 std::function 为空，
         * 转换结果为 false。
         *
         *
         * 因此：
         *
         * if (m_areaCall)
         *
         * 可以用来判断当前是否已经注册了回调函数。
         */
        if (m_areaCall)
        {
            cout << "invoke....." << endl;

            /**
             * 调用回调函数。
             *
             * m_areaCall 的类型是 function<double()>。
             *
             * 所以：
             *
             * m_areaCall()
             *
             * 表示调用它内部保存的可调用对象。
             *
             * 返回值是 double 类型的面积。
             */
            cout << "area:" << m_areaCall() << endl;
        }
    }


    /**
     * 保存回调函数对象
     *
     * m_areaCall 可以保存任意满足 double() 调用形式的可调用对象。
     */
    AreaCall m_areaCall;
};


/**
 * Rectangle
 *
 * 矩形类。
 *
 * 注意：
 * 这里的 Rectangle 没有继承 Figure。
 *
 * 它只是提供了一个 area 成员函数。
 *
 * 后续通过 bind 绑定对象后，
 * Rectangle::area 会被适配成 double() 形式，
 * 再保存到 Figure 的回调函数中。
 */
class Rectangle
{
public:
    /**
     * 构造函数
     *
     * 初始化矩形的长度和宽度。
     */
    Rectangle(double l, double w)
    : m_l(l)
    , m_w(w)
    {
    }

    /**
     * 计算矩形面积
     *
     * 成员函数 area 原始调用时，
     * 必须依赖某个 Rectangle 对象。
     *
     * 因此成员函数指针：
     *
     * &Rectangle::area
     *
     * 原始调用形式可以理解为：
     *
     * double(Rectangle*)
     *
     * 使用 bind 绑定具体对象之后，
     * 才可以变成：
     *
     * double()
     */
    double area()
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
 * 同样没有继承 Figure。
 *
 * 只要它的 area 成员函数经过 bind 后，
 * 能够适配成 double() 调用形式，
 * 就可以保存到 Figure 的回调函数中。
 */
class Circle
{
public:
    /**
     * 构造函数
     *
     * 初始化圆的半径。
     */
    Circle(double r)
    : m_r(r)
    {
    }

    /**
     * 计算圆形面积
     *
     * 圆形面积公式：
     *
     * 面积 = 半径 × 半径 × 3.14
     */
    double area()
    {
        cout << "Circle area" << endl;
        return m_r * m_r * 3.14;
    }

    // 圆形半径
    double m_r;
};


/**
 * test1
 *
 * 演示通过 std::function + std::bind 实现函数式多态。
 *
 * Rectangle 和 Circle 之间没有共同父类。
 *
 * 但是它们的 area 成员函数都可以通过 bind 绑定对象，
 * 变成统一的 double() 调用形式。
 *
 * 因此 Figure 可以通过 function<double()> 统一保存和调用。
 */
void test1()
{
    /**
     * 创建矩形对象。
     *
     * Rectangle::area 原始调用形式可以理解为：
     *
     * double(Rectangle*)
     */
    Rectangle r(1, 2);

    /**
     * 创建圆形对象。
     *
     * Circle::area 原始调用形式可以理解为：
     *
     * double(Circle*)
     */
    Circle c(3);

    // 创建 Figure 对象，用来保存回调函数
    Figure figure;

    /**
     * 注册矩形面积回调函数
     *
     * bind(&Rectangle::area, &r)
     *
     * 表示：
     * 把成员函数 Rectangle::area
     * 和具体对象地址 &r 绑定起来。
     *
     *
     * 原始调用形式：
     *
     * double(Rectangle*)
     *
     * 绑定对象之后：
     *
     * double()
     *
     *
     * setAreaCall 接收的是：
     *
     * function<double()>
     *
     * 因此可以保存 bind 之后的结果。
     */
    figure.setAreaCall(bind(&Rectangle::area, &r));

    // 调用已经注册的回调函数
    figure.handleAreaCall();

    cout << "-------" << endl;

    /**
     * 替换回调函数
     *
     * 同一个 Figure 对象中的 m_areaCall
     * 可以先保存矩形面积计算函数，
     * 再保存圆形面积计算函数。
     *
     *
     * bind(&Circle::area, &c)
     *
     * 表示：
     * 把成员函数 Circle::area
     * 和具体对象地址 &c 绑定起来。
     *
     * 绑定之后也得到：
     *
     * double()
     *
     *
     * 因此它也可以传给 setAreaCall。
     */
    figure.setAreaCall(bind(&Circle::area, &c));

    // 调用新的回调函数
    figure.handleAreaCall();
}


/**
 * lambda 引用捕获局部变量的生命周期问题
 *
 * lambda 捕获方式：
 *
 * [&]
 *
 * 表示以引用方式捕获当前作用域中用到的局部变量。
 *
 *
 * 引用捕获的特点：
 *
 * lambda 内部不会保存变量副本，
 * 而是保存对外部变量的引用。
 *
 *
 * 风险：
 *
 * 如果 lambda 的生命周期短于或等于被引用变量，
 * 通常没有问题。
 *
 * 但是如果 lambda 被保存起来，
 * 并且在局部变量销毁之后才调用，
 * 那么 lambda 内部保存的引用就会失效。
 *
 *
 * 继续访问已经失效的引用，
 * 会产生未定义行为。
 *
 *
 * 本例中：
 *
 * 1. func 函数内部定义了局部变量 num1 和 num2。
 * 2. lambda 使用 [&] 以引用方式捕获它们。
 * 3. lambda 被保存到全局 vector functions 中。
 * 4. func 执行结束后，num1 和 num2 被销毁。
 * 5. test2 中再次调用这个 lambda。
 *
 * 此时 lambda 访问的已经是失效引用，
 * 程序行为未定义。
 */


/**
 * 全局容器
 *
 * functions 用来保存多个无参数、无返回值的可调用对象。
 *
 * function<void()> 表示：
 * 不需要参数，
 * 没有返回值。
 */
vector<function<void()>> functions;


void func()
{
    /**
     * 局部变量
     *
     * num1 和 num2 都是 func 函数中的局部变量。
     *
     * 当 func 执行结束后，
     * 它们的生命周期结束，
     * 对应的内存不再属于这两个变量。
     */
    double num1 = 3.14;
    int num2 = 2;

    /**
     * 保存 lambda 到全局 vector 中
     *
     * functions 是全局变量，
     * 生命周期比 func 中的局部变量更长。
     *
     * 因此这个 lambda 很可能会在 func 返回之后才被调用。
     */
    functions.push_back(
        /**
         * lambda 表达式
         *
         * [&] 表示以引用方式捕获当前作用域中用到的局部变量。
         *
         * 这里 lambda 中使用了 num1 和 num2，
         * 所以 num1 和 num2 都会被引用捕获。
         *
         *
         * 注意：
         * lambda 被保存到了全局 vector 中。
         *
         * 当 func 执行结束后，
         * num1 和 num2 已经销毁。
         *
         * 后续再调用这个 lambda 时，
         * 访问 num1 和 num2 会产生未定义行为。
         */
        [&]()->void {
            cout << "num1:" << num1 << endl;
            cout << "num2:" << num2 << endl;
        }
    );
}


void test2()
{
    /**
     * 调用 func
     *
     * func 内部会创建局部变量 num1、num2，
     * 并把引用捕获它们的 lambda 保存到全局 vector 中。
     *
     * func 返回后，
     * num1 和 num2 的生命周期结束。
     */
    func();

    /**
     * 遍历全局 vector 中保存的 function 对象。
     */
    for (auto & f : functions)
    {
        /**
         * 调用 function 对象。
         *
         * 注意：
         * 当前示例中，
         * f 内部保存的 lambda 引用了 func 中的局部变量。
         *
         * 而这些局部变量在 func 返回后已经销毁。
         *
         * 因此这里调用 f() 存在生命周期问题，
         * 程序行为是未定义的。
         *
         *
         * 修正方式：
         *
         * 如果希望 lambda 在 func 返回后仍然安全调用，
         * 可以改为值捕获：
         *
         * [=]()->void {
         *     cout << "num1:" << num1 << endl;
         *     cout << "num2:" << num2 << endl;
         * }
         *
         * 值捕获会把 num1 和 num2 的副本保存到 lambda 内部。
         *
         * 即使 func 返回，
         * lambda 内部仍然有自己的副本可以使用。
         */
        f();
    }
}


int main(int argc, char const *argv[])
{
    // test1();

    // 当前测试 lambda 引用捕获局部变量的生命周期问题
    test2();

    return 0;
}