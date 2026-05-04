#include <iostream>

using std::cout;
using std::endl;

/**
 * 函数的默认参数
 * 可以进行缺省的调用
 * 给函数设置默认值时,注意:从右往左进行设置!!!
 */

// 给函数的参数设置一个默认值
void print(int a=0, int b=0)
{
    cout << "print(int,int)" << endl;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
}

void test1()
{
    // 缺省调用,使用的是默认值
    print();
    cout << "------" << endl;
    print(1);
    cout << "------" << endl;
    print(1,2);

}

// 函数的声明和实现(定义)分开写
// 声明一个函数(设置默认值)
void func2(int a = 0, int b = 0);

// 函数实现时,就不需要再加默认值了
// 否则会有重复设置默认值的报错
/* void func2(int a = 0  , int b = 0 ) */
void func2(int a, int b)
{
   // do something 
}


int main(int argc, char *argv[])
{
    test1();
    return 0;
}

