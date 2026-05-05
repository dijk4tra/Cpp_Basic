#include <iostream>
#include <unistd.h>

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;

/**
 * 通用输入输出流：istream / ostream
 *
 * cin：标准输入流，默认输入设备是键盘
 *    本质：istream 类型的全局对象
 *    Point pt;
 *    istream cin;
 *
 * cout：标准输出流，默认输出设备是终端控制台
 *    本质：ostream 类型的全局对象
 *    ostream cout;
 *
 * 缓冲区：
 * 1. 行缓冲：遇到换行时刷新缓冲区
 * 2. 全缓冲：缓冲区满时刷新
 * 3. 无缓冲：不使用缓冲区
 */


void test1()
{
    cout << "input nums: " << endl;

    int num1;
    int num2;

    cin >> num1;
    cin >> num2;

    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
}

void test2()
{
    cout << "input nums: " << endl;

    int num1;
    int num2;

    cin >> num1 >> num2;

    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;

    // 能够连续输入、连续输出，原理类似于连续赋值
    /**
     * Point pt1;
     * Point pt2;
     * Point pt3;
     *
     * pt3 = pt2 = pt1; // 连续调用 operator= 函数
     *
     * operator= 的返回值类型通常为 Point &
     * Point & operator=();
     *
     * pt3.operator=(pt2.operator=(pt1));
     *
     * << 和 >>
     * ostream & operator<<();
     * cout.operator<<(数据);
     */
}

// cin 可以作为 if 判断条件
void test3()
{
    cout << "input a num:" << endl;

    int num;

    /* if(cin.good()){ */

    // good 状态为 true
    // 非 good 状态为 false
    if(cin){
        cin >> num;
    }

    cout << num << endl;
}


// 测试缓冲区
void test4()
{
    for(int i = 0; i < 100; ++i){
        cout << 'a';
    }

    // 程序结束时会刷新缓冲区
}

void test5()
{
    for(int i = 0; i < 100; ++i){
        cout << 'a';
    }

    // 暂停程序执行 5 秒
    sleep(5);

    cout << "test5 end";
}

// 全缓冲
void test6()
{
    for(int i = 0; i < 1030; ++i){
        cout << 'a';
    }

    // 暂停程序执行 5 秒
    sleep(5);

    cout << "test6 end";
}

// 行缓冲
void test7()
{
    for(int i = 0; i < 100; ++i){
        cout << 'a' << endl;
    }

    // 暂停程序执行 5 秒
    sleep(5);

    cout << "test7 end";
}

void test8()
{
    for(int i = 0; i < 100; ++i){
        // 标准错误流，不带缓冲区
        std::cerr << 'a';
    }

    // 暂停程序执行 5 秒
    sleep(5);

    cout << "test8 end";
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    /* test6(); */
    /* test7(); */
    test8();

    return 0;
}