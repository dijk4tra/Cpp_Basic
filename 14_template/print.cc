/* #include "print.hpp" */
#include <iostream>

using std::cout;
using std::endl;

// 给出具体实现
template <typename T>
void print(T t)
{
    cout << t << endl;
    cout << "print..." << endl;
}