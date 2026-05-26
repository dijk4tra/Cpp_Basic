#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * lambda 表达式：
 *
 * lambda 表达式可以理解成一种匿名函数。
 *
 * 所谓匿名函数，就是：
 * 不需要提前定义函数名，
 * 可以直接在需要函数的位置写一段函数逻辑。
 *
 *
 * lambda 表达式的基本语法：
 *
 * [捕获列表](参数列表) 可选说明符 -> 返回类型
 * {
 *     // 函数体
 * };
 *
 *
 * 1. 捕获列表 Capture clause
 *
 *    写在 [] 中。
 *
 *    作用：
 *    用于捕获 lambda 表达式所在作用域中的局部变量。
 *
 *    常见写法：
 *
 *    []：
 *    不捕获任何外部变量。
 *
 *    [=]：
 *    按值捕获当前作用域中用到的局部变量。
 *
 *    [&]：
 *    按引用捕获当前作用域中用到的局部变量。
 *
 *    [a]：
 *    只按值捕获变量 a。
 *
 *    [&a]：
 *    只按引用捕获变量 a。
 *
 *    [=, &a]：
 *    默认按值捕获，
 *    但是变量 a 单独按引用捕获。
 *
 *    [&, a]：
 *    默认按引用捕获，
 *    但是变量 a 单独按值捕获。
 *
 *
 * 2. 参数列表 Parameter list
 *
 *    写在 () 中。
 *
 *    作用类似普通函数的参数列表，
 *    用于接收调用 lambda 时传入的参数。
 *
 *    例如：
 *    [](int num)
 *    {
 *        cout << num << endl;
 *    };
 *
 *
 * 3. 可选说明符
 *
 *    常见的是 mutable。
 *
 *    默认情况下，
 *    按值捕获的变量在 lambda 内部不能被修改。
 *
 *    如果加上 mutable，
 *    则可以修改按值捕获变量的副本。
 *
 *    注意：
 *    修改的是副本，
 *    不会影响 lambda 外部的原变量。
 *
 *
 * 4. -> 返回类型
 *
 *    用于显式指定 lambda 表达式的返回类型。
 *
 *    例如：
 *    [](int a, int b)->int
 *    {
 *        return a + b;
 *    };
 *
 *    如果编译器能够根据 return 语句自动推导返回类型，
 *    可以省略 -> 返回类型。
 *
 *
 * 5. 函数体 Function body
 *
 *    写在 {} 中。
 *
 *    lambda 真正要执行的代码。
 *
 *
 * 本质：
 *
 * lambda 表达式本质上是一个匿名的函数对象，
 * 也就是一个重载了 operator() 的临时对象。
 *
 * 所以 lambda 可以像普通函数一样被调用。
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
    /**
     * 无参数、无返回值的 lambda 表达式。
     *
     * []：
     * 捕获列表为空，
     * 表示不捕获外部变量。
     *
     * ()：
     * 参数列表为空，
     * 表示这个 lambda 不需要参数。
     *
     * ->void：
     * 返回值类型是 void，
     * 表示不返回数据。
     *
     * {
     *     cout << "lambda1" << endl;
     * }
     *
     * 是函数体。
     *
     *
     * 最后面的 ()：
     * 表示定义完 lambda 后立即调用。
     *
     * 这种写法相当于：
     * 定义了一个无参函数，
     * 然后马上执行它。
     */
    []()->void{
        cout << "lambda1" << endl;
    }();

    cout << "-----------" << endl;

    /**
     * 有参数、无返回值的 lambda 表达式。
     *
     * [](int num)->void
     *
     * 表示：
     * 1. 不捕获外部变量
     * 2. 接收一个 int 类型参数 num
     * 3. 没有返回值
     *
     *
     * 最后的 (100)：
     * 表示调用 lambda 时传入实参 100。
     */
    [](int num)->void{
        cout << "num = " << num << endl;
        cout << "lambda2" << endl;
    }(100);

    cout << "-----------" << endl;

    /**
     * 有参数、有返回值的 lambda 表达式。
     *
     * [](int a, int b)->int
     *
     * 表示：
     * 1. 不捕获外部变量
     * 2. 接收两个 int 类型参数
     * 3. 返回 int 类型结果
     *
     *
     * return a + b;
     *
     * 表示返回两个参数的和。
     *
     *
     * 最后的 (1, 2)：
     * 表示调用 lambda，并传入 1 和 2。
     *
     * 返回值会赋值给 sum。
     */
    int sum = [](int a, int b)->int{
        cout << "lambda3" << endl;
        return a + b;
    }(1, 2);

    cout << sum << endl;

    cout << "-----------" << endl;

    /**
     * 返回值类型可以省略。
     *
     * 编译器会根据 return a + b;
     * 自动推导出返回值类型是 int。
     *
     * 所以下面写法中省略了：
     * ->int
     */
    int sum2 = [](int a, int b){
        cout << "lambda4" << endl;
        return a + b;
    }(1, 2);

    cout << sum2 << endl;

    cout << "-----------" << endl;

    /**
     * 捕获列表：
     *
     * lambda 默认不能直接访问所在函数中的局部变量。
     *
     * 如果想在 lambda 内部使用外部局部变量，
     * 就需要通过捕获列表进行捕获。
     */
    int num1 = 10;
    int num2 = 20;

    /**
     * [num1, num2]
     *
     * 表示按值捕获 num1 和 num2。
     *
     * 按值捕获的含义：
     * lambda 内部使用的是外部变量的一份副本。
     *
     * 在 lambda 内部可以读取 num1 和 num2，
     * 但是默认不能修改它们。
     */
    [num1, num2]()->void{
        cout << "lambda5" << endl;
        cout << "num1 = " << num1 << endl;
        cout << "num2 = " << num2 << endl; 
    }();
}


// 捕获规则
void test2()
{
    int a = 1;
    int b = 2;

    /**
     * [&]
     *
     * 表示按引用捕获当前作用域中用到的局部变量。
     *
     * 当前 lambda 内部用到了 a 和 b，
     * 所以 a 和 b 都会被按引用捕获。
     *
     *
     * 按引用捕获的特点：
     * lambda 内部使用的是外部变量本身，
     * 不是副本。
     *
     * 因此在 lambda 内部修改 a、b，
     * 会影响外部原变量。
     */
    [&]()->void{
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;

        ++a;
        ++b;
    }();

    /**
     * 因为前面 lambda 中修改的是外部原变量，
     * 所以这里输出：
     *
     * a = 2
     * b = 3
     */
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}


void test3()
{
    int a = 1;
    int b = 2;

    /**
     * [=]
     *
     * 表示按值捕获当前作用域中用到的局部变量。
     *
     * 当前 lambda 内部用到了 a 和 b，
     * 所以 a 和 b 都会被按值捕获。
     *
     *
     * 按值捕获的特点：
     * lambda 内部使用的是外部变量的一份副本。
     *
     * 因此在 lambda 内部读取 a、b 是可以的，
     * 但是默认不能修改它们。
     */
    [=]()->void{
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;

        /**
         * 默认情况下，
         * 按值捕获的变量在 lambda 内部是只读的。
         *
         * 所以下面代码会报错。
         */
        // ++a; // error
        // ++b;
    }();

    /**
     * 因为 lambda 内部只是读取副本，
     * 没有修改外部原变量，
     * 所以这里仍然输出：
     *
     * a = 1
     * b = 2
     */
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}


void test4()
{
    int a = 1;
    int b = 2;
    int c = 3;

    /**
     * [=, &a]
     *
     * 表示混合捕获：
     *
     * 1. 默认按值捕获所有用到的外部变量
     * 2. 但是变量 a 单独按引用捕获
     *
     *
     * 当前 lambda 内部用到了 a、b、c。
     *
     * 捕获方式分别是：
     *
     * a：
     * 按引用捕获。
     *
     * b：
     * 按值捕获。
     *
     * c：
     * 按值捕获。
     */
    [=, &a]()->void{
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;

        /**
         * a 是按引用捕获，
         * 所以可以修改外部原变量 a。
         */
        ++a; 

        /**
         * b 和 c 是按值捕获，
         * 默认不能修改。
         */
        // ++b; // error
        // ++c;
    }();

    /**
     * a 被 lambda 修改了，
     * 所以变成 2。
     *
     * b 和 c 没有被修改，
     * 仍然是 2 和 3。
     */
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
}


void test5()
{
    int a = 1;
    int b = 2;
    int c = 3;

    /**
     * [b]
     *
     * 表示只按值捕获变量 b。
     *
     * 也就是说：
     * lambda 内部只能直接使用 b，
     * 不能直接使用 a 和 c。
     *
     * 如果在 lambda 内部写 cout << a;
     * 就会报错，因为 a 没有被捕获。
     */
    [b]()->void{
        cout << "b = " << b << endl;

        /**
         * b 是按值捕获，
         * 默认不能修改。
         */
        // ++b; // error
    }();

    cout << "-----------" << endl;

    /**
     * [&b]
     *
     * 表示只按引用捕获变量 b。
     *
     * lambda 内部使用的是外部变量 b 本身，
     * 所以修改 b 会影响外部的 b。
     */
    [&b]()->void{
        cout << "b = " << b << endl;
        ++b;
    }();

    /**
     * 因为 b 被按引用捕获并修改，
     * 所以这里输出：
     *
     * b = 3
     */
    cout << "b = " << b << endl;
}


void test6()
{
    int a = 1;
    int b = 2;
    int c = 3;

    /**
     * [&, b]
     *
     * 表示混合捕获：
     *
     * 1. 默认按引用捕获所有用到的外部变量
     * 2. 但是变量 b 单独按值捕获
     *
     *
     * 当前 lambda 内部用到了 a、b、c。
     *
     * 捕获方式分别是：
     *
     * a：
     * 按引用捕获。
     *
     * b：
     * 按值捕获。
     *
     * c：
     * 按引用捕获。
     */
    [&, b]()->void{
        /**
         * b 是按值捕获，
         * 默认不能修改。
         */
        cout << "b = " << b << endl;
        // ++b; // error

        /**
         * a 和 c 是按引用捕获，
         * 可以修改外部原变量。
         */
        cout << "a = " << a << endl;
        cout << "c = " << c << endl;

        ++a;
        ++c;
    }();

    /**
     * a 和 c 被修改。
     *
     * b 是按值捕获，
     * 外部 b 不受影响。
     *
     * 所以输出：
     * a = 2
     * b = 2
     * c = 4
     */
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
}


class MyClass
{
public:
    // 成员函数
    void func()
    {
        /**
         * a 是成员函数 func 内部的局部变量。
         *
         * 它不是成员变量，
         * 需要通过捕获列表捕获后，
         * lambda 内部才能使用。
         */
        int a = 10;

        /**
         * 在成员函数中使用 lambda：
         *
         * 如果 lambda 内部要访问成员变量 m_data，
         * 本质上需要通过 this 指针访问。
         *
         * 因为成员变量不属于局部变量，
         * 它属于当前对象。
         *
         *
         * 常见写法：
         *
         * 1. 显式捕获 this
         *
         *    [this]()->void
         *    {
         *        cout << this->m_data << endl;
         *    };
         *
         *
         * 2. 使用 [&]
         *
         *    [&] 会按引用捕获局部变量。
         *
         *    当 lambda 内部访问成员变量时，
         *    编译器会让 lambda 可以通过 this 指针访问成员。
         *
         *
         * 3. 使用 [=]
         *
         *    [=] 会按值捕获局部变量。
         *
         *    在 C++11/C++14 中，
         *    如果 lambda 内部使用成员变量，
         *    也会捕获 this 指针。
         *
         *    注意：
         *    捕获的是 this 指针本身，
         *    不是把整个对象完整拷贝一份。
         */
        [&]()->void{
            /**
             * a 是局部变量，
             * 通过 [&] 按引用捕获。
             */
            cout << a << endl;

            /**
             * m_data 是成员变量。
             *
             * 它需要通过当前对象的 this 指针访问。
             */
            cout << this->m_data << endl;

            /**
             * 修改成员变量。
             *
             * 因为访问的是当前对象中的 m_data，
             * 所以会影响对象本身。
             */
            this->m_data = 100;
        }();
    }

    /**
     * 成员变量。
     *
     * 每个 MyClass 对象都有自己的一份 m_data。
     */
    int m_data = 1;
};


void test7()
{
    int a = 1;
    int b = 2;

    /**
     * [=]() mutable -> void
     *
     * [=]：
     * 按值捕获外部变量 a 和 b。
     *
     * mutable：
     * 允许在 lambda 内部修改按值捕获变量的副本。
     *
     * -> void：
     * 返回值类型为 void。
     *
     *
     * 注意：
     * mutable 只允许修改 lambda 内部保存的副本，
     * 不会影响外部原变量。
     */
    [=]()mutable -> void{
        ++a;
        ++b;

        /**
         * 这里输出的是副本被修改后的值：
         *
         * a = 2
         * b = 3
         */
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
    }(); 
    
    /**
     * 外部变量 a、b 不受影响。
     *
     * 所以这里输出：
     *
     * a = 1
     * b = 2
     */
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}


// 如果想多次调用 lambda 表达式，
// 可以使用 auto 定义一个变量接收 lambda 表达式
void test8()
{
    /**
     * lambda 表达式本质上是一个匿名函数对象。
     *
     * 如果只写：
     *
     * []()
     * {
     *     cout << "lambda8" << endl;
     * }();
     *
     * 那么它会定义后立即调用一次。
     *
     *
     * 如果想后面反复调用同一个 lambda，
     * 可以使用 auto 保存这个 lambda 对象。
     *
     * auto f = []()->void{
     *     cout << "lambda8" << endl;
     * };
     *
     * 这里 f 的类型由编译器自动推导。
     *
     * 注意：
     * 每一个 lambda 表达式都有自己独一无二的类型，
     * 这个类型通常写不出来，
     * 所以一般用 auto 接收。
     */
    auto f = []()->void{
        cout << "lambda8" << endl;
    };

    /**
     * f 保存了 lambda 对象。
     *
     * 所以可以像调用普通函数一样多次调用 f。
     */
    f();
    f();
    f();

    cout << "-----------------" << endl;

    /**
     * 带参数的 lambda 表达式。
     *
     * auto f1 = [](const int& num)->void
     *
     * 含义：
     * 1. 不捕获外部变量
     * 2. 接收一个 const int& 类型参数
     * 3. 返回值为 void
     *
     *
     * const int& num：
     *
     * 表示以常量引用方式接收参数。
     *
     * 对 int 这种小类型来说，
     * 直接写 int num 也可以。
     *
     * 对较大的对象，
     * 使用 const 引用可以避免不必要的拷贝，
     * 同时又能保证函数内部不会修改实参。
     */
    auto f1 = [](const int& num)->void{
        cout << "num = " << num << endl;
    };

    /**
     * 多次调用同一个 lambda，
     * 每次传入不同的参数。
     */
    f1(100);
    f1(200);
    f1(300);
}


int main()
{
    /**
     * test1：
     * lambda 的基本语法：
     * 无参、带参、返回值、捕获列表。
     *
     * test2：
     * [&] 按引用捕获所有用到的外部局部变量。
     *
     * test3：
     * [=] 按值捕获所有用到的外部局部变量。
     *
     * test4：
     * [=, &a] 默认按值捕获，a 单独按引用捕获。
     *
     * test5：
     * [b] 只按值捕获 b，
     * [&b] 只按引用捕获 b。
     *
     * test6：
     * [&, b] 默认按引用捕获，b 单独按值捕获。
     *
     * test7：
     * mutable 允许修改按值捕获变量的副本。
     *
     * test8：
     * 使用 auto 保存 lambda，
     * 便于后续多次调用。
     */
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