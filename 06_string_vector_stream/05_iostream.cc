#include <iostream>
#include <unistd.h>

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;

/**
 * 通用输入输出流istream/ ostream
 *
 * cin: 标准输入流 默认输入设备 键盘
 *    本质: istream类型的一个全局对象
 *    Point pt;
 *    istream cin;
 * cout: 标准输出流 默认输出设备 终端控制台
 *    本质: ostream类型的一个全局对象
 *    ostream cout;
 *  缓冲区:
 *  行缓冲: 遇到换行进行刷新
 *  全缓冲: 缓冲区满了会进行刷新
 *  非缓冲: 没有缓冲区
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
    // 能够连续的输入输出,和能够连续赋值是类似的(重点理解)
    /**
     * Point pt1;
     * Point pt2;
     * Point pt3;
     * pt3 = pt2 = pt1; //连续调用operator=这个函数
     * 返回值类型为Point &
     * Point & operator=();
     * pt3.operator=(p2.operator=(pt1));
     *
     * << >>
     * ostream & operator<<();
     * cout.operator<<(数据)
     */

}

// cin 可以作为if判断的条件
void test3()
{
    cout << "input a num:" << endl;
    int num;
    /* if(cin.good()){ */
    // good状态 ---> true
    // 非good状态---> false
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
    // 程序结束时进行刷新
}

void test5()
{
    for(int i = 0; i < 100; ++i){
        cout << 'a';
    }
    // 让程序暂停执行5s
    sleep(5);
    cout << "test5 end";
}

// 全缓冲
void test6()
{
    for(int i = 0; i < 1030; ++i){
        cout << 'a';
    }
    // 让程序暂停执行5s
    sleep(5);
    cout << "test6 end";
}

// 行缓冲
void test7()
{
    for(int i = 0; i < 100; ++i){
        cout << 'a' << endl;
    }
    // 让程序暂停执行5s
    sleep(5);
    cout << "test7 end";
}

void test8()
{
    for(int i = 0; i < 100; ++i){
        // 标准错误流,不带缓冲区
        std::cerr << 'a';
    }
    // 让程序暂停执行5s
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

