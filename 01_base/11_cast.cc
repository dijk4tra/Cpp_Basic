#include <iostream>

using std::cout;
using std::endl;

/**
 * C++中提供强制类型转换表达式
 *
 * 1.基本类型之间的转换
 * 2.void* ---> 其他类型指针的转换
 *
 * static_cast<目标类型>(待转换的目标)
 *
 */

void test1()
{
    double d = 3.14;
    // C中的强转
    int a = (int)d;
    cout << a << endl;
}

void test2()
{
    double d = 3.14;
    int * p = (int *)&d;
    cout << *p << endl;
}

void test3()
{
    double d = 3.14;
    /* int * p = static_cast<int *>(&d); */
    // 基本类型之间的转换
    int num = static_cast<int>(d);
    cout << num << endl;

    // void*---->其它指针类型的转换
    int *p1 = static_cast<int *>(malloc(4));

}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}

