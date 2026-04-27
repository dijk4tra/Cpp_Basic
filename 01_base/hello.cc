#include <iostream> // 标准输入输出头文件,没有.h

// using声明机制
using std::cout; // 标准输出流
using std::endl; // 换行
using std::cin;  // 标准输入流

void test1()
{
    // C中使用的printf / scanf
    // 数据 << 交给了cout
    cout << "hello world" << endl;

    cout << "input a num:" << endl;
    // 使用cin接收键盘输入
    int num;
    // 输入的数据 >> 传输给num
    cin >> num;
    cout << "num=" << num << endl;
}

// int argc: 命令行参数个数
// argv : 具体的命令行参数
int main(int argc, char *argv[])
{   
    cout << argc << endl;
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    test1();
    return 0;
}

