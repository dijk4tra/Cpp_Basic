#include <iostream>

using std::cout;
using std::endl;

/**
 * 引用: 一个已经存在的变量或者对象的别名
 * 语法: 数据类型 & 引用名 = 变量/对象
 *
 * 引用本质: 是一个特殊的指针
 * 引用一经绑定就不能再修改, 即常量指针
 */

void test1()
{
    // num是本体
    int num = 1;
    // ref是别名
    int & ref = num;

    cout << ref << endl;

    // 通过别名进行修改
    ref = 2;
    cout << "------" << endl;
    cout << num << endl;

    int num2 = 10;
    ref = num2;
}

// 引用 VS 指针
void test2()
{
    int num = 1;
    int *p; // 声明了一个指针
    p = &num;
    
    // 引用定义的时候必须要进行初始化
    /* int & ref; */
    int & ref = num;

    cout << &num << endl;
    cout << p << endl;
    cout << &p << endl;
    // 对引用取地址, 取到的是所绑定的变量的地址
    cout << &ref << endl;
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();

    return 0;
}

