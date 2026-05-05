#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;

/**
 * 读取文件数据：
 * 1. 创建文件输入流对象
 * 2. 使用输入运算符或相关函数读取数据
 * 3. 调用 close 释放资源
 */

 // 文件流对象的创建
void test1()
{
    // 使用无参构造函数创建文件输入流对象
    ifstream ifs;

    // 通过 open 打开文件，并将文件与流对象关联
    ifs.open("data.txt");

    // 使用有参构造函数创建文件输入流对象，并直接关联文件
    ifstream ifs2 {"data.txt"};
    
    std::string fileName = "data.txt";
    ifstream ifs3{ fileName };
}

// 读取单个字符
void test2()
{
    ifstream ifs {"data.txt"};

    // get()：读取单个字符
    char ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;
}

void test3()
{
    ifstream ifs {"data.txt"};

    // get()：读取单个字符，并以 int 类型接收
    // 这样可以区分普通字符和 EOF
    int ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}