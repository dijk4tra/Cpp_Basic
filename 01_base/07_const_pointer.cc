#include <iostream>

using std::cout;
using std::endl;

/**
 * const 修饰指针类型:
 * 1.指向常量的指针
 *     pointer to constant
 *
 * 2.常量指针
 *     指针本身是个常量
 *     constant pointer
 *
 * 写法: 通过const和*的位置
 * 指向常量的指针(const在*前面):
 *     const int *p;
 *     int const *p;
 *
 * 常量指针(const在*后面):
 * int * const p;
 *
 */

void test1()
{   
    //指向常量的指针
    int num = 1;
    const int *p = &num;
    /* *p = 2; //报错: read only 不能修改*/
    // 特点: 不能通过指向去修改内容
    cout << *p << endl;

    int num2 = 10;
    p = &num2; // 可以修改指向
}

void test2()
{
    // 常量指针
    int num = 1;
    int * const p = &num;
    *p = 2;
    // 可以通过指向去修改内容
    cout << *p << endl;

    int num2 = 10;
    /* p = &num2; // 不能修改指向 */
}

// 特殊情况: 双重const限定的指针
void test3()
{
    int num = 1;
    const int * const p = &num;
    /* *p = 2; */
    int num2 = 10;
    /* p = &num2; */
    // 既不能通过指向修改内容,又不能修改指针的指向
}

// 用法: 一般可以用来修饰形参
void fun(const int num)
{
    /* num = 10; */
    cout << num << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

