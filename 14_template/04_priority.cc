#include <iostream>

using std::cout;
using std::endl;

/**
 * 匹配优先级问题：
 *
 * 1. 普通函数和函数模板之间
 *    当普通函数和函数模板都能匹配，并且匹配程度相同时，
 *    编译器会优先选择普通函数。
 *
 *    注意：
 *    普通函数不是任何情况下都优先。
 *    如果函数模板匹配程度更高，例如不需要类型转换，
 *    编译器也可能选择函数模板。
 *
 * 2. 函数模板之间重载
 *    编译器会根据匹配程度和模板的特化程度选择更合适的函数模板。
 *
 *    常见判断标准：
 *    1）需要类型转换越少，优先级越高
 *    2）参数约束越严格，优先级越高
 *    3）匹配程度越高，优先级越高
 *
 *    判断模板重载时，建议把模板参数替换成具体类型，
 *    写出实例化后的函数形式，再比较哪个更合适。
 */


// 模板一：两个参数必须是同一种类型
template <class T>
T add(T t1, T t2)
{
    cout << "模板一" << endl;
    return t1 + t2;
}


// 模板二：两个参数可以是不同类型
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

    // 显式指定两个模板参数，只能匹配模板二
    //
    // 模板一只有一个模板参数 T，不能写成 add<int, int>
    //
    // 对于模板二：
    // T1 = int, T2 = int
    // 实例化为：int add(int, int)
    //
    // 实参为：double, int
    // 第一个参数需要 double -> int 的类型转换
    cout << add<int, int>(x, y) << endl; // 模板二，结果为 19


    // 显式指定一个模板参数 int
    //
    // 对于模板一：
    // T = int
    // 实例化为：int add(int, int)
    // x 需要 double -> int 的类型转换
    //
    // 对于模板二：
    // T1 = int，T2 根据第二个实参 y 推导为 int
    // 实例化为：int add(int, int)
    // x 也需要 double -> int 的类型转换
    //
    // 两者匹配程度接近时，模板一的参数约束更严格：
    // 模板一要求两个参数必须是同一种类型 T
    // 模板二允许两个参数是不同类型 T1、T2
    //
    // 因此调用模板一
    cout << add<int>(x, y) << endl;     // 模板一，结果为 19


    // 显式指定一个模板参数 int
    //
    // 对于模板一：
    // T = int
    // 实例化为：int add(int, int)
    // 第二个参数 x 需要 double -> int 的类型转换
    //
    // 对于模板二：
    // T1 = int，T2 根据第二个实参 x 推导为 double
    // 实例化为：int add(int, double)
    // 两个参数都能精确匹配
    //
    // 模板二不需要额外类型转换，因此调用模板二
    cout << add<int>(y, x) << endl;     // 模板二，结果为 19
}


int main(int argc, char *argv[])
{
    test1();

    return 0;
}