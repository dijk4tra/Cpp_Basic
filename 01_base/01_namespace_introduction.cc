/* #include "zs.h" */
/* #include "ls.h" */
#include <iostream>

using std::cout;
using std::endl;

/*
 * 命名空间的语法
 * namespace 命名空间的名字{
 *   定义实体: 程序中的这些结构
 *   变量, 函数, 类, 命名空间...
 * }
 *
 */

int num = 1;
/* int num = 2; */

void test1()
{
    // 如果包含了其他人写的代码, 可能会有命名冲突问题
    /* print(); */
}

namespace wd
{
int number = 1;
    
void func(){
    cout << "wd:func()" << endl;
}
}//end of wd

namespace zs
{
int number = 2;

void func(){
    cout << "zs:func()" << endl;
}
}//end of zs

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

