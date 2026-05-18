#include <iostream>

using std::cout;
using std::endl;

/**
 * 模板的参数：
 *
 * 模板参数不只可以是“类型”，
 * 也可以是“普通的值”。
 *
 *
 * 1. 类型参数
 *
 *    例如：
 *    template <typename T>
 *
 *    这里的 T 表示一种类型。
 *
 *    T 可以被替换成：
 *    int、double、char、string、自定义类类型等。
 *
 *
 * 2. 非类型参数
 *
 *    例如：
 *    template <typename T, int N>
 *
 *    这里的 T 是类型参数；
 *    N 是非类型参数。
 *
 *    非类型参数表示：
 *    模板参数不是某种类型，
 *    而是一个具体的值。
 *
 *    常见的非类型参数类型：
 *    int、size_t、bool、char、指针、引用等。
 *
 *    在初学阶段，
 *    可以先重点理解整数类型的非类型参数。
 *
 *
 * 注意：
 * 非类型模板参数的值必须在编译期就能确定。
 *
 * 例如：
 * print<int, 10>(3);
 *
 * 这里的 10 是编译期常量，
 * 可以作为模板参数。
 *
 *
 * 模板参数也可以设置默认值。
 *
 * 类似于函数参数默认值：
 * 如果调用时没有显式指定模板参数，
 * 编译器可以使用默认模板参数。
 */


template <typename T, int N>
void print(T t)
{
    /**
     * T 是类型参数。
     *
     * N 是非类型参数，
     * 它是一个 int 类型的编译期常量。
     *
     * t * N 表示：
     * 把传入的数据 t 和模板参数 N 相乘。
     *
     * 当调用：
     * print<int, 10>(3);
     *
     * T = int
     * N = 10
     *
     * 实例化后的函数类似于：
     * void print(int t)
     * {
     *     cout << t * 10 << endl;
     * }
     */
    cout << t * N << endl;
}

void test1()
{
    /**
     * 显式实例化 / 显式指定模板参数。
     *
     * print<int, 10>(3);
     *
     * T = int
     * N = 10
     *
     * 其中：
     * int 是类型参数；
     * 10 是非类型参数。
     *
     * 输出：
     * 30
     */
    print<int, 10>(3); // T = int, N = 10

    /**
     * 隐式实例化失败。
     *
     * print(3);
     *
     * 编译器可以根据实参 3 推导出：
     * T = int
     *
     * 但是 N 不是函数参数的一部分，
     * 只是模板参数。
     *
     * 编译器无法根据 print(3) 推导出 N 的值。
     *
     * 所以如果 N 没有默认值，
     * 就必须显式指定 N。
     */
    /* print(3); // error：没有指定 N 的值 */
}


// 设置 N 的默认值为 10
template <typename T, int N = 10>
void print2(T t)
{
    /**
     * 这里和 print 类似。
     *
     * 区别在于：
     * N 有默认值 10。
     *
     * 如果调用时没有指定 N，
     * 编译器就使用默认值：
     * N = 10。
     */
    cout << t * N << endl;
}

void test2()
{
    /**
     * 隐式实例化成功。
     *
     * print2(3);
     *
     * 编译器根据实参 3 推导出：
     * T = int
     *
     * 因为 N 设置了默认值 10，
     * 所以：
     * N = 10
     *
     * 实例化后的函数类似于：
     * void print2(int t)
     * {
     *     cout << t * 10 << endl;
     * }
     *
     * 输出：
     * 30
     */
    print2(3);

    /**
     * 显式指定 T = double。
     *
     * 但是没有指定 N。
     *
     * 因为 N 有默认值，
     * 所以：
     * N = 10
     *
     * 实例化后类似于：
     * void print2(double t)
     * {
     *     cout << t * 10 << endl;
     * }
     *
     * 输出：
     * 31.4
     */
    print2<double>(3.14);

    /**
     * 显式指定两个模板参数。
     *
     * T = double
     * N = 100
     *
     * 此时不会使用 N 的默认值 10，
     * 而是使用我们显式指定的 100。
     *
     * 实例化后类似于：
     * void print2(double t)
     * {
     *     cout << t * 100 << endl;
     * }
     *
     * 输出：
     * 314
     */
    print2<double, 100>(3.14);
}


int main(int argc, char *argv[])
{
    // 测试没有默认非类型模板参数的情况
    /* test1(); */

    // 测试带默认非类型模板参数的情况
    test2();
    
    return 0;
}