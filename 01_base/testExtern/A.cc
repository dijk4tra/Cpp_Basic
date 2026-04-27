#include <iostream>

using std::cout;
using std::endl;

// 引入其他模块中的实体
// 使用extern关键字
extern int num;
extern void funcA();

// 定义同名的命名空间
namespace wd
{
// 使用extern
extern int number;
extern void func();
}

void test1()
{
    cout << num << endl;
    funcA();
}

void test2()
{
    cout << wd::number << endl;
    wd::func();
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();
    return 0;
}

