#include <iostream>

using std::cout;
using std::endl;

void func()
{
    cout << "func()" << endl;
}

// 全局变量
int gNum = 100;

void test1()
{
    // 局部变量
    int num1 = 1;
    int num2 = 2;
    int *p = new int{10};
    cout << "&num1:" << &num1 << endl;
    cout << "&num2:" << &num2 << endl;
    cout << "&p:" << &p << endl;
    cout << "p:" << p << endl;
    
    // 静态变量
    static int num3 = 3;

    cout << "&gNum:" << &gNum << endl;
    cout << "&num3:" << &num3 << endl;
    cout << "&hello" << &"hello" << endl;

    // 函数指针-输出指针的指向
    void (*f)() = &func;
    f();
    // 指针是有效地址 1
    cout << "f:" << f << endl;
    printf("%p\n",f);
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

