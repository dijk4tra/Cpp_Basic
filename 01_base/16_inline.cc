#include <iostream>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

using std::cout;
using std::endl;

/**
 * inline函数: 内联函数
 * 使用函数体来替代函数调用
 *
 * 使用inline函数修饰普通函数,相当于向编译器
 * 发出内联的建议,至于编译器是否采纳,不一定,取决于编译器
 *
 * 宏函数 VS 内联函数
 * 1.发生的时机
 * 2.是否方便调试
 * 
 * 什么情况下适合内联函数,什么情况下不适合?
 * 1.函数体比较简短,逻辑简单--->适合内联
 * 2.函数中有递归调用,有内联函数--->不适合内联
 *
 */

void test1()
{
    int result = MAX(20,10) + 20;
    // result的值是多少? // 40,如果宏定义不加大括号,就是20

    int result2 = MAX(10,20) + 20;
    // result2的值是多少? // 40
    
    cout << result << endl;
    cout << result2 << endl;
}

// 内联函数,声明和实现写在一起的情况
inline 
int getMax(int a, int b)
{
    return a > b ? a : b;
}

void test2()
{
    int a = 1;
    int b = 2;
    // 内联函数的作用,使用函数体替代函数调用
    int max = getMax(a, b);
}


// 内联函数,声明和实现分开写
// 声明
inline void print();
// 实现
inline void print()
{
    // do sth;
}



int main(int argc, char *argv[])
{
    test1();
    return 0;
}

