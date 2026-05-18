#include <iostream>

using std::cout;
using std::endl;

/**
 * 模板参数主要分为两类：
 *
 * 1. 类型参数
 *    用来表示一种类型，例如 T、K、U、V 等。
 *
 * 2. 非类型参数
 *    用来表示一个具体的值，常见类型有 int、size_t、bool、char 等。
 *    非类型模板参数的值需要在编译期确定。
 *
 * 模板参数也可以设置默认值。
 */


// T 是类型参数，N 是非类型参数
template <typename T, int N>
void print(T t)
{
    cout << t * N << endl;
}


void test1()
{
    // 显式实例化：明确指定 T = int，N = 10
    print<int, 10>(3);

    // 错误示例：
    // print(3);
    //
    // T 可以根据实参 3 推导为 int，
    // 但是 N 是非类型模板参数，不能从函数参数中推导出来，
    // 并且 N 没有默认值，所以必须显式指定。
}


// 给非类型模板参数 N 设置默认值 10
template <typename T, int N = 10>
void print2(T t)
{
    cout << t * N << endl;
}


void test2()
{
    // 隐式实例化：
    // T 根据实参 3 推导为 int，N 使用默认值 10
    print2(3);              // print2<int, 10>(3)

    // 显式指定 T = double，N 使用默认值 10
    print2<double>(3.14);   // print2<double, 10>(3.14)

    // 显式指定 T = double，N = 100
    print2<double, 100>(3.14);
}


int main(int argc, char *argv[])
{
    /* test1(); */
    test2();

    return 0;
}