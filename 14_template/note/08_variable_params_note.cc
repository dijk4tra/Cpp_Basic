#include <iostream>
#include <type_traits>

using std::cout;
using std::endl;

/**
 * 可变参数模板 variadic template：
 *
 * 适用于模板参数的个数不确定，
 * 并且参数类型也不确定的情况。
 *
 *
 * 普通函数模板：
 *
 * template <typename T>
 * void print(T t);
 *
 * 这种写法只能接收一个参数，
 * 并且只有一个模板类型参数 T。
 *
 *
 * 如果想接收多个参数：
 *
 * template <typename T, typename U>
 * void print(T t, U u);
 *
 * 这种写法可以接收两个参数。
 *
 * 但是问题是：
 * 如果参数个数不确定，
 * 比如可能是 0 个、1 个、2 个、10 个，
 * 就不适合提前写死模板参数个数。
 *
 *
 * 可变参数模板可以解决这个问题。
 *
 *
 * 基本语法：
 *
 * template <typename ...Args>
 * void func(Args ...args)
 * {
 *
 * }
 *
 *
 * Args：
 * 可以理解为一个“类型参数包”。
 *
 * 它里面可以装多个类型：
 * int、double、const char *、string 等。
 *
 *
 * args：
 * 可以理解为一个“函数参数包”。
 *
 * 它里面装的是函数调用时传入的所有实参。
 *
 *
 * 例如：
 * print(1, 3.14, "abc", 100);
 *
 * 此时：
 * Args 中包含的类型大致是：
 * int、double、const char *、int
 *
 * args 中包含的实参是：
 * 1、3.14、"abc"、100
 *
 *
 * 关于 ... 的位置：
 *
 * typename ...Args
 * 表示 Args 是一个模板参数包。
 *
 * Args ...args
 * 表示 args 是一个函数参数包。
 *
 *
 * ...Args / Args...
 * ...args / args...
 *
 * 初学时可以先这样理解：
 *
 * 1. 在定义模板参数包、函数参数包时，
 *    ... 表示“打包”。
 *
 * 2. 在使用参数包时，
 *    ... 表示“展开”或“解包”。
 *
 *
 * 可变参数模板通常需要递归处理。
 *
 * 因为参数包里面可能有多个数据，
 * 我们需要一个一个取出来处理。
 *
 *
 * 递归处理一般包含两部分：
 *
 * 1. 递归体
 *
 *    每次从参数包中取出第一个数据，
 *    处理完第一个数据后，
 *    再把剩余的数据继续传给自己。
 *
 * 2. 递归出口
 *
 *    当参数包中没有数据时，
 *    调用一个无参版本的普通函数，
 *    用来结束递归。
 */ 


/**
 * 可变参数函数模板。
 *
 * template <typename ...Args>
 *
 * Args 是模板参数包，
 * 可以接收任意个类型参数。
 *
 *
 * void print(Args ...args)
 *
 * args 是函数参数包，
 * 可以接收任意个函数实参。
 */
template<typename ...Args>
void print(Args ...args)
{   
    /**
     * sizeof...(Args)
     *
     * 获取模板参数包 Args 中类型参数的个数。
     *
     * 例如：
     * print(1, 3.14, "abc");
     *
     * Args 中有：
     * int、double、const char *
     *
     * 所以 sizeof...(Args) 的结果是 3。
     */
    cout << sizeof...(Args) << endl;

    /**
     * sizeof...(args)
     *
     * 获取函数参数包 args 中函数实参的个数。
     *
     * 一般情况下，
     * sizeof...(Args) 和 sizeof...(args) 的值是一样的。
     *
     * 前者统计类型参数个数，
     * 后者统计函数实参个数。
     */
    cout << sizeof...(args) << endl;
}


void test1()
{
    /**
     * print()
     *
     * 没有传入任何参数。
     *
     * Args 中没有类型；
     * args 中没有实参。
     *
     * 所以两个 sizeof... 的结果都是 0。
     */
    print();

    /**
     * print(1)
     *
     * 传入一个 int 类型参数。
     *
     * Args：
     * int
     *
     * args：
     * 1
     *
     * 两个 sizeof... 的结果都是 1。
     */
    print(1);

    /**
     * print(1, 3.14)
     *
     * 传入两个参数：
     * int
     * double
     *
     * Args：
     * int、double
     *
     * args：
     * 1、3.14
     *
     * 两个 sizeof... 的结果都是 2。
     */
    print(1, 3.14);

    /**
     * print(1, 3.14, "abc", 1)
     *
     * 可以理解成编译器推导出了：
     *
     * print<int, double, const char *, int>(1, 3.14, "abc", 1);
     *
     * 注意：
     * 第一个 1 和最后一个 1 都是 int。
     *
     * 但是它们仍然分别对应参数包中的两个位置。
     *
     * 也就是说：
     * 类型相同不代表只记录一次。
     *
     * Args 中仍然是：
     * int、double、const char *、int
     *
     * 参数个数是 4。
     */
    // <T1, T2, T3, T4>
    // print<int, double, const char *, int>
    print(1, 3.14, "abc", 1);
    // 注意：参数的类型是一样的，不会认为你的类型参数是同一个
    // 还是会把它当作新的类型来对待
}


// 需求：打印可变参数模板中的所有数据

/**
 * 递归出口。
 *
 * 这是一个普通函数，
 * 不是函数模板。
 *
 * 当参数包中的所有参数都已经处理完后，
 * 最终会调用 show()。
 *
 * show() 中不需要继续处理数据，
 * 只负责结束递归。
 */
void show()
{
    // do nothing

    /**
     * 输出换行。
     *
     * 这样前面递归过程中输出的所有数据，
     * 最后可以以换行结束。
     */
    cout << endl;
}


/**
 * 递归体。
 *
 * template <typename First, typename ...Args>
 *
 * First：
 * 表示当前参数包中的第一个参数类型。
 *
 * Args：
 * 表示剩余参数的类型参数包。
 *
 *
 * void show(First first, Args ...args)
 *
 * first：
 * 当前取出来的第一个实参。
 *
 * args：
 * 剩余的函数参数包。
 *
 *
 * 这种写法相当于：
 * 每次从参数包中拆出一个参数 first，
 * 然后把剩余的参数继续交给 show 处理。
 */
template <typename First, typename ...Args>
void show(First first, Args ...args)
{
    // 递归体

    /**
     * 先处理第一个数据 first。
     *
     * 要求：
     * First 类型必须支持 cout << first。
     *
     * 如果传入的是自定义类型，
     * 并且没有重载 operator<<，
     * 这里会编译报错。
     */
    cout << first << " ";

    /**
     * 再处理剩余数据。
     *
     * show(args...);
     *
     * args... 表示把函数参数包展开。
     *
     * 例如：
     * args 中如果保存的是：
     * 3.14、"abc"、100
     *
     * 那么：
     * show(args...);
     *
     * 就相当于：
     * show(3.14, "abc", 100);
     */
    show(args...); // 解包

    /**
     * 模拟递归过程：
     *
     * show(1, 3.14, "abc", 100);
     *
     * 第一次：
     * first = 1
     * args = 3.14, "abc", 100
     * 输出 1
     * 调用 show(3.14, "abc", 100)
     *
     * 第二次：
     * first = 3.14
     * args = "abc", 100
     * 输出 3.14
     * 调用 show("abc", 100)
     *
     * 第三次：
     * first = "abc"
     * args = 100
     * 输出 abc
     * 调用 show(100)
     *
     * 第四次：
     * first = 100
     * args 为空
     * 输出 100
     * 调用 show()
     *
     * 第五次：
     * 调用无参普通函数 show()
     * 输出换行，递归结束。
     */
    // cout << 1
    // show(3,14,"abc", 100)
    // cout << 3.14
    // show("abc", 100)
    // cout << "abc"
    // show(100)
    // cout << 100
    // show();
}

void test2()
{
    /**
     * 调用可变参数模板 show。
     *
     * 传入 4 个参数：
     * int
     * double
     * const char *
     * int
     *
     * 最终输出：
     * 1 3.14 abc 100
     */
    show(1, 3.14, "abc", 100);
}


int main(int argc, char *argv[])
{
    // 测试可变参数模板中参数包的数量
    /* test1(); */

    // 测试递归方式打印参数包中的所有数据
    test2();
    
    return 0;
}