#include <iostream>

using std::cout;
using std::endl;

/**
 * 函数模板：把模板应用在函数上。
 *
 * 基本语法：
 * template <typename T>
 * template <class T>
 *
 * typename 和 class 在声明类型模板参数时作用相同。
 *
 * 多个模板参数的写法：
 * template <typename T, typename U, typename K>
 *
 * template：定义模板的关键字。
 * T / U / K：模板参数，也叫类型参数，表示一种通用类型。
 *
 * 模板参数名本质上只是一个代号，使用什么字母都可以，
 * 但通常会使用有含义的大写字母，例如：
 *
 * T：type，类型
 * K：key，键
 * V：value，值
 * E：element，元素
 *
 * 建议尽量使用有含义的命名，不要随意使用 X、Y、Z。
 */


// 函数模板的声明和实现写在一起
template <typename T>
void print(T t)
{
    cout << "print(T)" << endl;
    cout << t << endl;
}


// 编译器会根据使用时的具体类型，实例化出对应的函数
/*
 * 例如：
 *
 * void print(int t)
 * {
 *     cout << "print(T)" << endl;
 *     cout << t << endl;
 * }
 *
 * void print(double t)
 * {
 *     cout << "print(T)" << endl;
 *     cout << t << endl;
 * }
 */


// 函数模板的声明和实现分开

// 函数模板声明
template <typename T>
void print2(T t);


// 函数模板实现
// 注意：实现部分也需要重新写 template <typename T>
template <typename T>
void print2(T t)
{
    cout << "print2(T)" << endl;
    cout << t << endl;
}


void test1()
{
    // 显式实例化：明确指定模板参数类型
    print<int>(100);
    print<double>(3.14);

    cout << "---------" << endl;

    // 隐式实例化：不指定模板参数类型，由编译器根据实参自动推导
    print(100);     // 推导出 print<int>(int)
    print(3.14);    // 推导出 print<double>(double)
}


void test2()
{
    // 显式实例化
    print2<int>(100);

    // 隐式实例化
    print2(3.14);   // 推导出 print2<double>(double)
}


int main(int argc, char *argv[])
{
    /* test1(); */
    test2();

    return 0;
}