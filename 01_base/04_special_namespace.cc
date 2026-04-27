#include <iostream>

using std::cout;
using std::endl;

/**
 * 特殊的命名空间:
 * 1.嵌套的命名空间
 * 2.匿名的命名空间
 */

// outer
namespace outer
{
int num1 = 1;
void func()
{
    cout << "outer::func()" << endl;
}
// inner
namespace inner{
    int num2 = 2;
    void func2()
    {
        cout << "inner::func2()" << endl;
    }
}// end of inner
}// end of outer

void test1()
{
    // 使用作用域限定符
    cout << outer::num1 << endl;
    cout << outer::inner::num2 << endl;
}

void test2()
{
    // 使用using声明机制
    using outer::num1;
    cout << num1 << endl;
    using outer::inner::num2;
    cout << num2 << endl;
}

void test3()
{
    using namespace outer::inner;
    cout << num2 << endl;
}

// 匿名的命名空间
namespace  {
    int number = 100;
}

void test4()
{
    // 访问匿名的命名空间的实体
    // 可以直接访问
    cout << number << endl;
    // 可以使用作用域限定符
    cout << ::number << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

