#include <iostream>

using std::cout;
using std::endl;

/*
 * 布尔类型: bool 当成基本数据类型来对待
 *
 * true: 1
 * false: 0
 *  
 * bool可以和数值类型的数据进行转换
 */

void test1()
{
    bool flag1 = true;
    bool flag2 = false;
    cout << flag1 << endl; // 打印1,不会打印"true"
    cout << flag2 << endl; // 打印0,不会打印"false"
}


void test2()
{   
    // 数值类型和bool之间转换
    // 只有0是false,其他所有的正整数,负数,小数都是true
    bool b1 = 1;
    bool b2 = 0;
    bool b3 = 100;
    bool b4 = -100;
    bool b5 = 3.14;
    cout << b1 << endl;
    cout << b2 << endl;
    cout << b3 << endl;
    cout << b4 << endl;
    cout << b5 << endl;
}

void test3()
{   
    // 大小为一个字节
    bool flag = true;
    cout << sizeof(flag) << endl;
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

