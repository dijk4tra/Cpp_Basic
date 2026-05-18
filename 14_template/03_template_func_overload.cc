#include <iostream>

using std::cout;
using std::endl;

/**
 * 普通函数和函数模板之间也可以形成重载。
 *
 * 当普通函数和函数模板都能匹配，并且匹配程度相同时，
 * 编译器会优先选择普通函数。
 *
 * 注意：
 * 不是任何情况下普通函数优先级都更高。
 * 如果函数模板的匹配程度更高，例如不需要类型转换，
 * 编译器也可能选择函数模板。
 *
 * 函数模板和函数模板之间也可以形成重载。
 *
 * 常见区分方式：
 * 1. 通过函数参数个数区分，例如：
 *    print2(T)
 *    print2(T, U)
 *
 * 2. 通过函数参数类型或位置区分，例如：
 *    print4(T, U)
 *    print4(U, T)
 *
 * 判断模板重载时，最好把模板参数替换成具体类型，
 * 写出实例化后的函数形式，这样更容易分析调用的是哪一个。
 */


void print(int a)
{
    cout << "普通函数" << endl;
    cout << a << endl;
}


template <typename T>
void print(T t)
{
    cout << "使用了模板" << endl;
    cout << t << endl;
}


void test1()
{
    // 普通函数和函数模板都能匹配 print(100)
    // 普通函数：void print(int)
    // 函数模板：void print<int>(int)
    //
    // 二者匹配程度相同，因此优先调用普通函数
    print(100);
}


// 通过函数参数个数形成函数模板重载
template <typename T>
void print2(T t)
{
    cout << "使用了模板一" << endl;
    cout << t << endl;
}


template <typename T, typename U>
void print2(T t, U u)
{
    cout << "使用了模板二" << endl;
    cout << t << ", " << u << endl;
}


void test2()
{
    // 显式指定 T 为 int，函数实参个数为 1 个
    // 调用：print2<int>(int)
    print2<int>(100);

    // 显式指定 T 为 int，U 由第二个实参自动推导为 int
    // 调用：print2<int, int>(int, int)
    print2<int>(100, 200);

    // 显式指定 T 和 U 都为 int
    // 调用：print2<int, int>(int, int)
    print2<int, int>(300, 400);

    cout << "----------" << endl;
}


// 尽量避免写下面这种过于相似的函数模板重载，容易混淆
template <typename T>
void print3(T t1, T t2)
{
    cout << "使用了模板一" << endl;
    cout << t1 << ", " << t2 << endl;
}


template <typename T, typename U>
void print3(T t, U u)
{
    cout << "使用了模板二" << endl;
    cout << t << ", " << u << endl;
}


void test3()
{
    // 两个实参类型相同，模板一更加特化，优先调用模板一
    print3(1, 2);          // 使用了模板一

    // 显式指定 T 为 int，两个实参都可以匹配模板一
    print3<int>(1, 2);     // 使用了模板一

    // 显式指定两个模板参数，只能匹配模板二
    // 因为模板一只有一个模板参数 T
    print3<int, int>(1, 2); // 使用了模板二
}


// 通过函数参数类型的位置形成函数模板重载
template <typename T, typename U>
T print4(T t, U u)
{
    cout << "使用了模板一" << endl;
    cout << t << ", " << u << endl;
    return t;
}


template <typename T, typename U>
T print4(U u, T t)
{
    cout << "使用了模板二" << endl;
    cout << u << ", " << t << endl;
    return t;
}


void test4()
{
    int x = 1;
    double y = 3.14;

    /*
     * print4(x, y);
     *
     * 不建议直接这样调用，因为可能产生二义性。
     *
     * 对于模板一：
     * T = int, U = double
     * 实例化为：int print4(int, double)
     *
     * 对于模板二：
     * T = double, U = int
     * 实例化为：double print4(int, double)
     *
     * 两个函数的参数列表都可以精确匹配 int, double。
     * 返回值不能作为函数重载的区分依据，因此会产生二义性。
     */

    // 显式指定 T = int, U = double
    //
    // 对于模板一：
    // int print4(int, double)      // 精确匹配
    //
    // 对于模板二：
    // int print4(double, int)      // 需要类型转换
    //
    // 因此调用模板一
    print4<int, double>(x, y);

    // 显式指定 T = double, U = int
    //
    // 对于模板一：
    // double print4(double, int)   // 需要类型转换
    //
    // 对于模板二：
    // double print4(int, double)   // 精确匹配
    //
    // 因此调用模板二
    print4<double, int>(x, y);
}


int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    test4();

    return 0;
}