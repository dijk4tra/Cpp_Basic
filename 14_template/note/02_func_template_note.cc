#include <iostream>

using std::cout;
using std::endl;

/**
 * 函数模板：
 * 把模板作用在函数上。
 *
 * 普通函数中，
 * 参数类型是固定的。
 *
 * 例如：
 * void print(int t);
 * 这个函数只能比较自然地处理 int 类型。
 *
 * 如果还想处理 double、char、string 等类型，
 * 就需要继续写多个重载函数。
 *
 * 使用函数模板以后，
 * 可以把参数类型抽象出来，
 * 用一个模板参数 T 表示。
 *
 *
 * 基本语法：
 * template <typename T>
 * template <class T>
 *
 * typename 和 class 在这里作用基本相同，
 * 都表示 T 是一个类型参数。
 *
 *
 * 多个模板参数：
 * template <typename T, typename U, typename K>
 *
 * T、U、K 都是模板参数，
 * 它们表示一种通用类型。
 *
 *
 * 模板参数的名字：
 * 模板参数名本质上只是一个代号，
 * 使用什么字母都可以。
 *
 * 但是为了增强可读性，
 * 通常会使用一些约定俗成的名字：
 *
 * T：type，表示普通类型
 * K：key，表示键的类型
 * V：value，表示值的类型
 * E：element，表示元素类型
 *
 * 不太建议随意使用 X、Y、Z，
 * 因为语义不够清楚。
 */


/**
 * 函数模板的声明和实现写在一起。
 *
 * template <typename T>
 * 表示下面定义的是一个函数模板，
 * 其中 T 是类型参数。
 *
 * void print(T t)
 * 表示 print 函数的参数类型暂时不确定，
 * 等到真正调用 print 时，
 * 编译器会根据传入的实参类型确定 T 的具体类型。
 */
template<typename T>
void print(T t)
{
    cout << "print(T)" << endl;

    /**
     * 这里直接输出 t。
     *
     * 要求：
     * T 类型的对象必须支持 cout << t 这种输出方式。
     *
     * 例如：
     * int、double、char 等内置类型可以直接输出。
     *
     * 如果 T 是自定义类型，
     * 但是没有重载 operator<<，
     * 那么实例化 print<T> 时就会编译报错。
     */
    cout << t << endl;
}

/**
 * 编译器会根据模板生成具体的函数。
 *
 * 模板本身不是最终被调用的函数，
 * 它更像是一份生成函数的规则。
 *
 * 例如：
 * print(100);
 * 编译器推导出 T 是 int，
 * 于是生成类似下面的函数：
 *
 * void print(int t)
 * {
 *     cout << "print(T)" << endl;
 *     cout << t << endl;
 * }
 *
 * print(3.14);
 * 编译器推导出 T 是 double，
 * 于是生成类似下面的函数：
 *
 * void print(double t)
 * {
 *     cout << "print(T)" << endl;
 *     cout << t << endl;
 * }
 */


/**
 * 函数模板的声明和实现也可以分开写。
 *
 * 注意：
 * 普通函数声明时只需要写函数原型。
 *
 * 但是函数模板声明时，
 * 需要在函数声明前面加上 template <typename T>。
 */

// 函数模板声明
template <typename T>
void print2(T t);


/**
 * 函数模板实现。
 *
 * 注意：
 * 即使前面已经写过函数模板声明，
 * 在实现函数模板时，
 * 仍然需要重新写一遍：
 *
 * template <typename T>
 *
 * 因为这里的 T 只在当前模板声明范围内有效。
 */
template <typename T>
void print2(T t)
{
    // do sth

    cout << "print2(T)" << endl;

    /**
     * 这里没有使用参数 t。
     *
     * 也就是说，
     * print2 只是通过参数 t 的类型来实例化不同版本的函数，
     * 但函数体内部并没有对 t 做具体操作。
     */
}

void test1()
{
    /**
     * 显式实例化 / 显式指定模板参数。
     *
     * 调用函数模板时，
     * 可以在函数名后面通过 <类型> 明确告诉编译器：
     * T 到底是什么类型。
     */

    // 指定 T 是 int
    // 因此生成并调用 print<int>(int)
    print<int>(100);

    // 指定 T 是 double
    // 因此生成并调用 print<double>(double)
    print<double>(3.14);

    cout << "---------" << endl;

    /**
     * 隐式实例化。
     *
     * 不手动指定模板参数，
     * 而是让编译器根据实参类型自动推导 T 的类型。
     */

    // 100 是 int 类型，
    // 所以编译器推导 T 是 int
    print(100);

    // 3.14 是 double 类型，
    // 所以编译器推导 T 是 double
    print(3.14);
}

void test2()
{
    /**
     * 调用声明和实现分开的函数模板。
     */

    // 显式指定 T 是 int
    print2<int>(100);

    // 隐式实例化
    // 编译器根据 3.14 推导出 T 是 double
    print2(3.14);
}

int main(int argc, char *argv[])
{
    // 测试 print 函数模板
    /* test1(); */

    // 测试 print2 函数模板
    test2();
    
    return 0;
}