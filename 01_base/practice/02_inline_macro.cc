#include <iostream>

using std::cout;
using std::endl;

// 1.使用宏定义计算平方
#define SQUARE(x) ((x)*(x))

// 2.使用内联函数计算平方
inline int square(int x)
{
    return x * x;
}

int main(int argc, char *argv[])
{
    int a = 5;
    cout << "--- 使用宏定义计算平方 ---" << endl;
    cout << "SQUARE(a) = " << SQUARE(a) << endl;
    cout << "SQUARE(5 + 1) = " << SQUARE(5 + 1) << endl;
    
    cout << endl;

    cout << "--- 使用内联函数计算平方 ---" << endl;
    cout << "square(a) = " << square(a) << endl;
    cout << "square(5 + 1) = " << square(5 + 1) << endl;

    return 0;
}

