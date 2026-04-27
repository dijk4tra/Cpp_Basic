/* #include "my_header.h" */
#include <string.h>
#include <iostream>
/* #include 第三方库头文件 */

using std::cout;
using std::endl;

namespace wd
{
    int num = 1;
    /* int num = 2; */
}
// 上下是同一个命名空间
namespace wd
{
    /* int num = 2; */
}

void test1()
{

}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

