#include <iostream>
#include <functional>

using namespace std;

/**
 * std::ref / std::cref：引用包装器
 *
 * 1. std::bind 默认会按值保存绑定的参数
 *
 *    auto f = bind(func, a, b, c);
 *
 *    上面这种写法中，a、b、c 都会被拷贝一份保存到 bind 内部。
 *    后续执行 f() 时，func 使用的是 bind 内部保存的副本，
 *    而不是 test1 中原来的变量。
 *
 * 2. 如果希望 bind 保存引用，需要使用 std::ref 或 std::cref
 *
 *    std::ref(x)  ：包装为普通引用，允许通过函数修改原变量；
 *    std::cref(x) ：包装为 const 引用，不允许通过函数修改原变量。
 *
 * 3. 本例中
 *
 *    func(int a, int & b, const int c)
 *
 *    a 是值传递，修改的是副本；
 *    b 是引用传递，修改的是原变量；
 *    c 是值传递，并且在函数内部是 const，不能被修改。
 */

void func(int a, int & b, const int c)
{   
    // a 是值传递，修改的是 a 的副本，不影响 test1 中的变量 a
    a++;

    // b 是引用传递，修改的是 test1 中的原变量 b
    b++;

    // c 是 const 值传递，在函数内部不能修改
    // c++;

    cout << "a:" << a << " b:" << b << " c:" << c << endl;
}

void test1()
{
    int a = 1;
    int b = 2;
    int c = 3;

    // bind 默认按值保存参数：
    // a、b、c 都会被拷贝到 bind 内部
    // auto f = bind(func, a, b, c);

    // 使用 std::ref(b) 后，bind 内部保存的是 b 的引用包装器
    // 执行 f() 时，func 的第二个参数 int& b 会绑定到原变量 b
    auto f = bind(func, a, std::ref(b), c);

    f();

    // 执行结果说明：
    // a 没有变化，因为 func 中的 a 是值传递
    // b 被修改，因为 func 中的 b 是引用传递，并且 bind 时使用了 std::ref(b)
    // c 没有变化，因为 func 中的 c 是 const 值传递
    cout << "a:" << a << " b:" << b << " c:" << c << endl;
}

int main()
{
    test1();

    return 0;
}