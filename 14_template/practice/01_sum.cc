#include <iostream>

using namespace std;

// 递归终止函数: 只有一个参数时,直接返回这个参数
template<typename T>
T sum(T value)
{
    return value;
}

// 可变模板参数函数
template<typename T, typename ...Args>
auto sum(T first, Args ...rest)
{
    return first + sum(rest...);
}

int main()
{
    cout << sum(1, 2, 3, 4) << endl;
    cout << sum(1.5, 2.5, 3.0) << endl;
    cout << sum(1, 2.5, 3, 4.5) << endl;

    return 0;
}