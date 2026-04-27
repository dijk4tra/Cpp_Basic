#include <iostream>

using std::cout;
using std::endl;

/*
 * 命名空间的使用:
 * 1.使用作用域限定符::
 * 2.使用using声明机制
 * 3.使用using编译指令
 *
 * 推荐使用第二种方式
 *
 */

namespace wd
{
int num = 1;
void func()
{
    cout << "wd::func()" << endl;
}
}//end of wd

namespace zs
{
int num = 2;
void func()
{
    cout << "zs::func()" << endl;
}
}//end of zs


void test1()
{
    // 使用作用域限定符
    cout << wd::num << endl;
    cout << zs::num << endl;
}

void test2()
{
    // 使用using声明机制
    using wd::num;
    cout << num << endl;
    using wd::func;
    func();
}

void test3()
{
    // 使用using编译指令
    using namespace wd;
    // 一口气把wd命名空间中的所有实体引入到当前作用域
    cout << num << endl;
    func();
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

