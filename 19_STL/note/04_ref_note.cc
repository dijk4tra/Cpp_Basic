#include <iostream>
#include <functional>

using namespace std;


/**
 * std::ref / std::cref：引用包装器
 *
 * std::ref 和 std::cref 定义在头文件 <functional> 中。
 *
 * 作用：
 * 把一个对象包装成“引用包装器”，
 * 让某些默认按值保存参数的工具，
 * 可以按照引用的方式保存和传递参数。
 *
 *
 * 典型使用场景：
 *
 * std::bind 默认会按值保存绑定的参数。
 *
 * 例如：
 *
 * auto f = bind(func, a, b, c);
 *
 * 上面这种写法中，
 * a、b、c 都会被拷贝一份保存到 bind 内部。
 *
 * 后续调用 f() 时，
 * func 使用的是 bind 内部保存的副本，
 * 而不是 test1 中原来的变量。
 *
 *
 * 如果希望 bind 保存引用，
 * 就需要使用：
 *
 * std::ref(x)
 *
 * 或：
 *
 * std::cref(x)
 *
 *
 * std::ref(x)：
 * 把 x 包装成普通引用。
 *
 * 通过这个引用传递给函数后，
 * 如果函数形参允许修改，
 * 就可以修改原变量。
 *
 *
 * std::cref(x)：
 * 把 x 包装成 const 引用。
 *
 * 通过这个引用传递给函数后，
 * 只能读取原变量，
 * 不能修改原变量。
 *
 *
 * 注意：
 * std::ref / std::cref 本身并不是创建一个新对象，
 * 而是创建一个引用包装器 std::reference_wrapper。
 *
 * 它的目的不是拷贝对象，
 * 而是告诉 bind：
 *
 * “这里不要按值保存副本，
 *  而是按照引用的方式使用原对象。”
 */


/**
 * func
 *
 * 用来演示值传递、引用传递、const 值传递的区别。
 *
 * 形参：
 *
 * 1. int a
 *    值传递。
 *
 *    调用函数时，
 *    实参会拷贝一份给形参 a。
 *
 *    函数内部修改 a，
 *    修改的是副本，
 *    不会影响外部原变量。
 *
 *
 * 2. int & b
 *    引用传递。
 *
 *    形参 b 是实参的引用，
 *    b 和外部原变量是同一个对象。
 *
 *    函数内部修改 b，
 *    会影响外部原变量。
 *
 *
 * 3. const int c
 *    const 值传递。
 *
 *    c 仍然是值传递，
 *    调用函数时也会拷贝一份。
 *
 *    只不过这个副本在函数内部是 const 的，
 *    所以函数内部不能修改 c。
 */
void func(int a, int & b, const int c)
{
    /**
     * a 是值传递。
     *
     * 这里执行 a++，
     * 修改的是 func 函数内部的局部副本 a，
     * 不会影响 test1 中的变量 a。
     */
    a++;

    /**
     * b 是引用传递。
     *
     * 这里执行 b++，
     * 修改的是绑定到 b 上的原变量。
     *
     * 如果调用 func 时，
     * b 绑定的是 test1 中的变量 b，
     * 那么 test1 中的 b 也会被修改。
     */
    b++;

    /**
     * c 是 const 值传递。
     *
     * c 是 func 内部的一个只读副本。
     *
     * 因为它有 const 修饰，
     * 所以不能执行 c++。
     */
    // c++;

    // 打印函数内部看到的 a、b、c
    cout << "a:" << a << " b:" << b << " c:" << c << endl;
}


void test1()
{
    // 定义三个普通变量
    int a = 1;
    int b = 2;
    int c = 3;

    /**
     * bind 默认按值保存参数
     *
     * 如果写成：
     *
     * auto f = bind(func, a, b, c);
     *
     * 那么 a、b、c 都会被拷贝一份，
     * 保存到 bind 返回的函数对象内部。
     *
     *
     * 但是 func 的第二个参数是：
     *
     * int & b
     *
     * 它需要绑定到一个可以修改的 int 左值上。
     *
     * bind 内部保存的 b 副本可以作为这个引用的绑定对象，
     * 因此函数内部修改的只是 bind 内部的 b 副本，
     * 不会影响 test1 中的原变量 b。
     *
     *
     * 也就是说：
     *
     * auto f = bind(func, a, b, c);
     * f();
     *
     * 修改的是 bind 内部保存的 b，
     * 不是 test1 中的 b。
     */
    // auto f = bind(func, a, b, c);

    /**
     * 使用 std::ref(b)
     *
     * std::ref(b) 会把 test1 中的变量 b
     * 包装成一个引用包装器。
     *
     * bind 看到 std::ref(b) 后，
     * 不会把 b 当成普通值拷贝使用，
     * 而是在调用 func 时，
     * 把原变量 b 传给 func 的第二个参数。
     *
     *
     * 因此：
     *
     * auto f = bind(func, a, std::ref(b), c);
     *
     * 表示：
     * 1. 第一个参数 a 仍然按值保存
     * 2. 第二个参数 b 按引用保存
     * 3. 第三个参数 c 仍然按值保存
     *
     *
     * 调用 f() 时，
     * func 的第二个形参 int& b
     * 会绑定到 test1 中的原变量 b。
     *
     * 所以 func 内部执行 b++，
     * 会修改 test1 中的 b。
     */
    auto f = bind(func, a, std::ref(b), c);

    // 调用 bind 返回的新函数对象
    f();

    /**
     * 执行结果说明：
     *
     * 1. a 没有变化
     *
     *    因为 func 中的 a 是值传递，
     *    并且 bind 中保存的 a 也是副本。
     *
     *    func 内部执行 a++，
     *    修改的是函数内部的局部副本，
     *    不会影响 test1 中的 a。
     *
     *
     * 2. b 发生变化
     *
     *    因为 bind 时使用了 std::ref(b)，
     *    func 的第二个参数 int& b
     *    会绑定到 test1 中的原变量 b。
     *
     *    func 内部执行 b++，
     *    修改的是 test1 中的 b。
     *
     *
     * 3. c 没有变化
     *
     *    因为 func 中的 c 是 const 值传递，
     *    本质上仍然是拷贝一份。
     *
     *    并且 c 是 const，
     *    在 func 内部不能被修改。
     *
     *
     * 所以输出顺序大致为：
     *
     * 第一次输出来自 func：
     * a:2 b:3 c:3
     *
     * 第二次输出来自 test1：
     * a:1 b:3 c:3
     */
    cout << "a:" << a << " b:" << b << " c:" << c << endl;
}


int main()
{
    // 调用测试函数
    test1();

    return 0;
}