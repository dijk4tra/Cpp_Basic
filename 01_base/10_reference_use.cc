#include <iostream>

using std::cout;
using std::endl;

/**
 * 函数调用时,进行参数传递
 * 1.值传递
 * 2.地址传递
 * 3.引用传递: 可以起到和指针一样的效果,
 *             又比使用指针简单,且不会进行复制
 * 
 * 引用使用的场景:
 * 1.作为函数参数
 * 2.作为函数的返回值类型
 *
 */

// 希望在函数内部进行函数参数的交换
// 形参的交换 ---> 实参的交换

// 值传递
void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

// 地址传递
void swap2(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 引用传递
// int & a = a , int & b = b
void swap3(int & a, int & b)
{
    int temp = a;
    a = b;
    b = temp;
}

void test1()
{
    int a = 1;
    int b = 2;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    //a,b是实参
    /* swap(a, b); */
    /* swap2(&a, &b); */
    swap3(a, b);
    cout << "------" << endl;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
}

/**
 * struct Student{
 *     char[] name;
 *     int id;
 *     xxxxx;
 *     int age;
 * }
 *
 * void func(Student stu){
 *     
 * }
 *
 */


/**
 * Student func1()
 * {
 *     return Student{1,"zs"};
 * }
 *
 */

int fun2()
{
    // return 也会进行复制操作
    return 10;
}

int gNum = 100;
// 返回值类型为int&, return时不会进行数据的复制
int & func3()
{
    return gNum;
}

// 不要返回一个局部变量的引用
int & func4()
{
    int a = 10;
    return a;
}

void test4()
{
    int & ref = func4();
    // 定义的引用绑定到了一个已经被干掉的局部变量上
    // error 段错误
    cout << "ref=" << ref << endl;
}

int * func5()
{
    int * p = new int {100};
    return p;
}

void test5()
{
    // 如果函数返回的是一个堆空间地址,
    // 最好接收一下,然后通过指针进行释放
    int * p1 = func5();
    int * p2 = func5();
    delete p1;
    delete p2;
    p1 = nullptr;
    p2 = nullptr;
}

void test6()
{
    int num = 1;
    // 常引用
    const int & ref = num;
    cout << ref << endl;
    /* ref = 2; //error: read only  */
}

void func6(const int & ref)
{
    // read only
    /* ref = 10 */
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test4(); */
    test5();
    return 0;
}

