#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * lambda 表达式
 *
 * 基本语法：
 * [捕获列表](参数列表) 可选说明符 -> 返回类型
 * {
 *     // 函数体
 * }
 *
 * 1. 捕获列表(Capture clause)
 *    用于捕获 lambda 表达式所在作用域中的局部变量。
 *
 * 2. 参数列表(Parameter list)
 *    类似普通函数的参数列表，用于接收调用 lambda 时传入的参数。
 *
 * 3. 可选说明符(Mutable/Exception)
 *    常见的是 mutable。
 *    默认情况下，按值捕获的变量在 lambda 内部不能被修改。
 *    如果加上 mutable，则可以修改按值捕获变量的副本，
 *    但不会影响 lambda 外部的原变量。
 *
 * 4. -> 返回类型(Return type)
 *    用于显式指定 lambda 表达式的返回类型。
 *    如果编译器能够自动推导返回类型，可以省略。
 *
 * 5. 函数体(Function body)
 *    lambda 表达式真正执行的代码。
 *
 * 本质：
 * lambda 表达式本质上是一个匿名的函数对象，
 * 可以像普通函数一样调用。
 */

void func()
{
    cout << "func" << endl;
}

void func(int num)
{
    cout << num << endl;
    cout << "func" << endl;
}

// lambda 基本语法使用
void test1()
{
    // 无参数、无返回值的 lambda 表达式
    []()->void{
        cout << "lambda1" << endl;
    }();  // 定义后立即调用，相当于调用一个无参函数

    cout << "-----------" << endl;

    // 有参数、无返回值的 lambda 表达式
    [](int num)->void{
        cout << "num = " << num << endl;
        cout << "lambda2" << endl;
    }(100); // 定义后立即调用，并传入参数 100

    cout << "-----------" << endl;

    // 有参数、有返回值的 lambda 表达式
    int sum = [](int a, int b)->int{
        cout << "lambda3" << endl;
        return a + b;
    }(1, 2); // 调用 lambda，并将返回值赋给 sum

    cout << sum << endl;

    cout << "-----------" << endl;

    // 有参数、有返回值
    // 返回值类型 -> int 可以省略，由编译器根据 return 语句自动推导
    int sum2 = [](int a, int b){
        cout << "lambda4" << endl;
        return a + b;
    }(1, 2);

    cout << sum2 << endl;

    cout << "-----------" << endl;

    // 捕获列表
    int num1 = 10; // test1 函数中的局部变量
    int num2 = 20;

    // [num1, num2] 表示按值捕获 num1 和 num2
    // lambda 内部使用的是 num1、num2 的副本
    [num1, num2]()->void{
        cout << "lambda5" << endl;
        cout << "num1 = " << num1 << endl;
        cout << "num2 = " << num2 << endl; 
    }();
}

// 捕获规则
// [&]：按引用捕获当前作用域中用到的局部变量
void test2()
{
    int a = 1;
    int b = 2;

    // [&] 表示按引用捕获外部变量
    // lambda 内部修改变量，会影响外部原变量
    [&]()->void{
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        ++a;
        ++b;
    }();

    cout << "a = " << a << endl; // 2
    cout << "b = " << b << endl; // 3
}

// [=]：按值捕获当前作用域中用到的局部变量
void test3()
{
    int a = 1;
    int b = 2;

    // [=] 表示按值捕获外部变量
    // lambda 内部使用的是外部变量的副本
    [=]()->void{
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;

        // 默认情况下，按值捕获的变量在 lambda 内部不能修改
        // ++a; // error
        // ++b;
    }();

    cout << "a = " << a << endl; // 1
    cout << "b = " << b << endl; // 2
}

void test4()
{
    int a = 1;
    int b = 2;
    int c = 3;

    // [=, &a] 表示：
    // 默认按值捕获所有用到的外部变量
    // 但变量 a 单独按引用捕获
    [=, &a]()->void{
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;

        // a 是按引用捕获，可以修改外部原变量
        ++a; 

        // b 和 c 是按值捕获，默认不能修改
        // ++b; // error
        // ++c;
    }();

    cout << "a = " << a << endl; // 2
    cout << "b = " << b << endl; // 2
    cout << "c = " << c << endl; // 3
}

void test5()
{
    int a = 1;
    int b = 2;
    int c = 3;

    // [b] 表示只按值捕获变量 b
    // lambda 内部使用的是 b 的副本
    [b]()->void{
        cout << "b = " << b << endl;

        // 默认情况下，按值捕获的变量不能修改
        // ++b; // error
    }();

    cout << "-----------" << endl;

    // [&b] 表示只按引用捕获变量 b
    // lambda 内部修改 b，会影响外部原变量
    [&b]()->void{
        cout << "b = " << b << endl;
        ++b;
    }();

    cout << "b = " << b << endl; // 3
}

void test6()
{
    int a = 1;
    int b = 2;
    int c = 3;

    // [&, b] 表示：
    // 默认按引用捕获所有用到的外部变量
    // 但变量 b 单独按值捕获
    [&, b]()->void{
        // b 是按值捕获，默认不能修改
        cout << "b = " << b << endl;
        // ++b; // error

        // a 和 c 是按引用捕获，可以修改外部原变量
        cout << "a = " << a << endl;
        cout << "c = " << c << endl;

        ++a;
        ++c;
    }();

    cout << "a = " << a << endl; // 2
    cout << "b = " << b << endl; // 2
    cout << "c = " << c << endl; // 4
}


class MyClass
{
public:
    // 成员函数
    void func()
    {
        int a = 10;

        // 在成员函数中使用 lambda
        //
        // 如果 lambda 内部要访问成员变量 m_data，
        // 实际上需要通过 this 指针访问。
        //
        // 可以显式捕获 this：
        // [this]()->void{
        //
        // 也可以使用 [=] 或 [&]，
        // 当 lambda 内部使用成员变量时，会捕获 this 指针。
        //
        // [=]()->void{
        [&]()->void{
            // a 是局部变量，通过 [&] 按引用捕获
            cout << a << endl;

            // m_data 是成员变量，通过 this 指针访问
            cout << this->m_data << endl;

            // 修改成员变量
            this->m_data = 100;
        }();
    }

    int m_data = 1;
};

void test7()
{
    int a = 1;
    int b = 2;

    // [=] 表示按值捕获所有用到的局部变量
    //
    // mutable 表示 lambda 内部可以修改按值捕获变量的副本
    // 注意：修改的是副本，不会影响外部的 a 和 b
    [=]()mutable -> void{
        ++a;
        ++b;

        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
    }(); 
    
    // 外部变量 a、b 不受影响
    cout << "a = " << a << endl; // 1
    cout << "b = " << b << endl; // 2
}

// 如果想多次调用 lambda 表达式，
// 可以使用 auto 定义一个变量接收 lambda 表达式
void test8()
{
    // f 保存 lambda 表达式对应的匿名函数对象
    auto f = []()->void{
        cout << "lambda8" << endl;
    };

    // 多次调用同一个 lambda 表达式
    f();
    f();
    f();

    cout << "-----------------" << endl;

    // 带参数的 lambda 表达式
    // const int& num 表示以常量引用的方式接收参数
    auto f1 = [](const int& num)->void{
        cout << "num = " << num << endl;
    };

    f1(100);
    f1(200);
    f1(300);
}


int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    // test7();
    test8();

    return 0;
}