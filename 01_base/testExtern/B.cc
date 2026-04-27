#include <iostream>

using std::cout;
using std::endl;

// 全局变量
int num = 1;

void funcA()
{
    cout << "A::funcA()" << endl;
}

// 有名字的命名空间
namespace wd
{
int number = 100;
void func()
{
    cout << "A::wd::func()" << endl;
}
}//end of wd
