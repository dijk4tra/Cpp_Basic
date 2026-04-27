#include <iostream>

using std::cout;
using std::endl;

/**
 * 函数重载(overload): 同义作用域内,函数名相同,
 *                     形参列表不同的一组函数
 * 构成函数重载的条件: 形参列表不同
 * 1.可以通过函数的参数个数的不同进行区分
 * 2.参数个数相同,可以通过参数类型的不同进行区分
 * 3.参数个数相同,类型也相同,可以通过参数位置的不同来区分
 *
 * 特别注意:
 * 函数重载和返回值没有任何关系!!!!!!
 */

void addInt(int a, int b)
{
    cout << a + b << endl;
}

void addDouble(double a, double b)
{
    cout << a + b << endl;
}

void add(int a, int b)
{
    cout << "add(int,int)" << endl;
}

void add(double a, double b)
{
    cout << "add(double,double)" << endl;
}


void test1()
{
    add(1,2);
    add(3.14,2.1);
}



void print2()
{
    cout << "print2()" << endl;
}

void print2(int a)
{
    cout << "print2(int)" << endl;
}

void test2()
{
    // 通过函数从参数个数进行区分
    print2();
    print2(100);
}



void print3()
{
    cout << "print3(int)" << endl;
}

void print3(double a)
{
    cout << "print3(double)" << endl;
}

 void test3()
{
    print3(100);
    print3(3.14);
}



void print4(int a, double b)
{
    cout << "print4(int,double)" << endl;
}

void print4(double a, int b)
{
    cout << "print4(double,int)" << endl;
}

void test4()
{
    print4(100, 3.14);
    print4(3.14, 100);
}


// 特殊的二义性问题
void test5()
{
    /* print4(100,100); //error:模糊匹配 */
}



// 如果某个代码希望以C的方式编译
extern "C" {
    // C中不支持函数重载
    void func(){}
    /* void func(int a){} */
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    test4();
    return 0;
}

