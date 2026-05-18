#include <iostream>

using std::cout;
using std::endl;

/**
 * 可变参数模板：
 * 适用于模板参数个数不确定、类型也不确定的情况。
 *
 * 基本语法：
 * template <typename... Args>
 * void func(Args... args)
 * {
 *     // ...
 * }
 *
 * 如何理解：
 * Args 可以理解为一个“类型包”，里面保存的是一组类型参数，
 * 例如 int、double、const char* 等。
 *
 * args 可以理解为一个“函数参数包”，里面保存的是一组函数实参，
 * 例如 1、3.14、"abc" 等。
 *
 * typename... Args：
 * 声明模板参数包 Args。
 *
 * Args... args：
 * 根据 Args 中的一组类型，声明对应的一组函数参数 args。
 *
 * sizeof...(Args)：
 * 获取模板参数包中类型参数的个数。
 *
 * sizeof...(args)：
 * 获取函数参数包中函数实参的个数。
 *
 * args...：
 * 对函数参数包进行展开，通常用于函数调用。
 *
 * 使用可变参数模板时，常见做法是递归处理参数包：
 * 1. 递归体：每次取出第一个参数并处理
 * 2. 递归出口：定义一个无参函数，用于结束递归
 */


template <typename... Args>
void print(Args... args)
{
    // 获取模板参数包中类型参数的个数
    cout << sizeof...(Args) << endl;

    // 获取函数参数包中函数实参的个数
    cout << sizeof...(args) << endl;
}


void test1()
{
    print();                 // Args 为空，参数个数为 0
    print(1);                // Args = <int>
    print(1, 3.14);          // Args = <int, double>

    // Args = <int, double, const char*, int>
    print(1, 3.14, "abc", 1);

    // 注意：
    // 即使两个实参类型相同，也会分别对应参数包中的两个位置。
    // 例如 print(1, 2) 中 Args = <int, int>，
    // 不会因为类型相同就合并成一个 T。
}


// 需求：打印可变参数模板中的所有数据

// 递归出口：当参数包被处理完后，调用这个普通函数结束递归
void show()
{
    cout << endl;
}


// 递归体：至少接收一个参数
template <typename First, typename... Args>
void show(First first, Args... args)
{
    // 先处理第一个参数
    cout << first << " ";

    // 再处理剩余参数
    // args... 表示展开函数参数包
    show(args...);

    /*
     * 调用 show(1, 3.14, "abc", 100) 的过程大致如下：
     *
     * cout << 1 << " ";
     * show(3.14, "abc", 100);
     *
     * cout << 3.14 << " ";
     * show("abc", 100);
     *
     * cout << "abc" << " ";
     * show(100);
     *
     * cout << 100 << " ";
     * show();
     *
     * 最后 show() 作为递归出口，输出换行并结束递归。
     */
}


void test2()
{
    show(1, 3.14, "abc", 100);
}


int main(int argc, char *argv[])
{
    /* test1(); */
    test2();

    return 0;
}