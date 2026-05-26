#include <iostream>
#include <functional>

using namespace std;

/**
 * 引用折叠与万能引用
 *
 * 1. 引用折叠规则
 *
 *    T &  &   -> T &
 *    T && &   -> T &
 *    T &  &&  -> T &
 *    T && &&  -> T &&
 *
 *    规则总结：
 *    只要有左值引用参与，最终结果就是左值引用；
 *    只有两个都是右值引用时，最终结果才是右值引用。
 *
 * 2. 万能引用
 *
 *    template<typename T>
 *    void func(T && t)
 *
 *    当 T 是模板参数，并且形参写成 T&& 时，
 *    这里的 T&& 不是普通右值引用，而是万能引用。
 *
 *    万能引用既可以接收左值，也可以接收右值：
 *
 *    - 传入左值时，T 会被推导为左值引用类型；
 *    - 传入右值时，T 会被推导为普通类型。
 *
 * 3. 注意
 *
 *    template<typename T>
 *    void func(T & t)
 *
 *    这里的 T& 是普通左值引用形参，只能接收左值，不能接收右值。
 */

template<typename T>
void func(T & t)
{
    cout << "func(T & t)" << endl;
}

template<typename T>
void func2(T && t)
{
    cout << "func2(T && t)" << endl;
}

void test1()
{
    int num = 1; // num 是左值

    // func 的形参是 T&，只能接收左值
    func(num);   // T = int，形参类型为 int&

    // 1 是右值，不能绑定到普通左值引用 T&
    // func(1);  // 编译错误：非常量左值引用不能绑定到右值

    cout << "-------" << endl;

    // func2 的形参是 T&&，并且 T 是模板参数，因此这里是万能引用

    // 传入左值 num：
    // T 被推导为 int&
    // 形参类型 T&& -> int& && -> int&
    func2(num);

    // 传入右值 1：
    // T 被推导为 int
    // 形参类型 T&& -> int&&
    func2(1);
}

int main()
{
    test1();

    return 0;
}