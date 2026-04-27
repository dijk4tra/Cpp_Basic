#include <iostream>

#define MAX 100
using std::cout;
using std::endl;

/**
 * 使用const修饰变量--->常量
 * const: 具有只读属性 read only
 */

void test1()
{
    const int num = 1;
    /* num = 2; //常量,不能修改 */
    cout << num << endl;

    int const num2 = 2;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

