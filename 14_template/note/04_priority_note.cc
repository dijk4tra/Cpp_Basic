#include <iostream>

using std::cout;
using std::endl;

/**
 * 匹配优先级的问题：
 *
 * 1. 普通函数和函数模板之间
 *
 *    当普通函数和函数模板都可以匹配时，
 *    一般情况下：
 *    普通函数的优先级更高。
 *
 *    例如：
 *    void print(int);
 *
 *    template <typename T>
 *    void print(T);
 *
 *    print(100);
 *
 *    普通函数 void print(int) 可以直接匹配；
 *    函数模板也可以实例化出 void print<int>(int)。
 *
 *    此时优先调用普通函数。
 *
 *
 * 2. 函数模板和函数模板之间重载
 *
 *    函数模板之间发生重载时，
 *    编译器会根据匹配程度选择更合适的模板。
 *
 *    一般来说：
 *
 *    1）不需要付出额外代价的函数模板优先级更高。
 *
 *       这里的“额外代价”主要指类型转换。
 *
 *       如果一个模板实例化后可以直接匹配实参类型，
 *       另一个模板需要进行类型转换，
 *       那么优先选择不需要类型转换的模板。
 *
 *
 *    2）参数约束更严格的函数模板优先级更高。
 *
 *       例如：
 *       template <class T>
 *       T add(T t1, T t2);
 *
 *       这个模板要求两个参数必须是同一种类型。
 *
 *       template <class T1, class T2>
 *       T1 add(T1 t1, T2 t2);
 *
 *       这个模板允许两个参数是不同类型。
 *
 *       当两个实参本身就是同一种类型时，
 *       第一个模板的约束更严格，
 *       通常会优先匹配第一个模板。
 *
 *
 *    3）匹配程度更高的函数模板优先级更高。
 *
 *       可以理解为：
 *       谁需要的类型转换更少，
 *       谁的参数约束更明确，
 *       谁就更容易被选中。
 *
 *
 * 分析模板重载时的建议：
 *
 * 不要只看模板声明本身，
 * 最好把模板参数代入进去，
 * 写出实例化之后的具体函数形式，
 * 再判断哪个函数更匹配。
 */ 


/**
 * 模板一。
 *
 * 只有一个模板参数 T。
 *
 * 两个函数参数 t1 和 t2 都是 T 类型。
 *
 * 也就是说：
 * 这个模板要求两个参数的类型相同。
 *
 * 返回值类型也是 T。
 */
template <class T> // 模板一
T add(T t1, T t2)
{
    cout << "模板一" << endl;
    return t1 + t2;
}

/**
 * 模板二。
 *
 * 有两个模板参数：
 * T1 和 T2。
 *
 * 第一个函数参数类型是 T1，
 * 第二个函数参数类型是 T2。
 *
 * 也就是说：
 * 这个模板允许两个参数的类型不同。
 *
 * 返回值类型是 T1。
 */
template <class T1, class T2>
T1 add(T1 t1, T2 t2)
{
    cout << "模板二" << endl;
    return t1 + t2;
}

void test1()
{
    double x = 9.1;
    int y = 10;

    /**
     * add<int, int>(x, y)
     *
     * 显式指定了两个模板参数：
     * <int, int>
     *
     * 模板一：
     * template <class T>
     * T add(T t1, T t2);
     *
     * 模板一只有一个模板参数 T，
     * 不能接收 <int, int> 两个模板参数。
     *
     * 所以模板一不匹配。
     *
     *
     * 模板二：
     * template <class T1, class T2>
     * T1 add(T1 t1, T2 t2);
     *
     * T1 = int
     * T2 = int
     *
     * 实例化后得到：
     * int add(int, int);
     *
     * 调用时传入：
     * x, y
     * 也就是：
     * double, int
     *
     * 其中 x 会从 double 转换成 int，
     * y 本来就是 int。
     *
     * 因此这里调用模板二。
     *
     * 注意：
     * 9.1 转成 int 会丢失小数部分，
     * 变成 9。
     */
    cout << add<int, int>(x, y) << endl; // 模板二

    /**
     * add<int>(x, y)
     *
     * 显式指定一个模板参数：
     * <int>
     *
     * 此时两个模板都可能参与匹配。
     *
     *
     * 对于模板一：
     *
     * T = int
     *
     * 实例化后得到：
     * int add(int, int);
     *
     * 调用时传入：
     * x, y
     * 也就是：
     * double, int
     *
     * x 需要从 double 转换成 int，
     * y 可以直接匹配 int。
     *
     *
     * 对于模板二：
     *
     * T1 = int
     * T2 可以由第二个实参 y 自动推导为 int
     *
     * 实例化后得到：
     * int add(int, int);
     *
     * 调用时传入：
     * double, int
     *
     * x 也需要从 double 转换成 int。
     *
     *
     * 两个模板实例化之后的参数形式都相同：
     * int add(int, int)
     *
     * 但是模板一对参数的约束更严格：
     * 它要求两个参数必须是同一个 T 类型。
     *
     * 所以这里调用模板一。
     */
    cout << add<int>(x, y) << endl;     // 模板一

    /**
     * add<int>(y, x)
     *
     * 显式指定一个模板参数：
     * <int>
     *
     *
     * 对于模板一：
     *
     * T = int
     *
     * 实例化后得到：
     * int add(int, int);
     *
     * 调用时传入：
     * y, x
     * 也就是：
     * int, double
     *
     * y 可以直接匹配 int，
     * x 需要从 double 转换成 int。
     *
     *
     * 对于模板二：
     *
     * T1 = int
     * T2 由第二个实参 x 自动推导为 double
     *
     * 实例化后得到：
     * int add(int, double);
     *
     * 调用时传入：
     * int, double
     *
     * 两个参数都可以直接匹配，
     * 不需要类型转换。
     *
     *
     * 虽然模板一的参数约束更严格，
     * 但是模板二在这次调用中匹配程度更高，
     * 因为它不需要把 double 转成 int。
     *
     * 所以这里调用模板二。
     */
    cout << add<int>(y, x) << endl;     // 模板二
}

int main(int argc, char *argv[])
{
    // 测试函数模板之间重载时的匹配优先级
    test1();

    return 0;
}