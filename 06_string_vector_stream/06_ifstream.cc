#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;

/**
 * 读取文件数据:
 * 1.创建文件输入流对象
 * 2.利用输入运算符或者函数读取数据
 * 3.close释放资源
 *
 */

// 文件流对象的创建
void test1()
{
    // 无参构造函数创建
    ifstream ifs;
    // 通过open打开文件,并于其关联
    ifs.open("data.txt");

    // 有参构造
    ifstream ifs2 {"data.txt"};
    
    std::string fileName = "data.txt";
    ifstream ifs3{ fileName };
}

// 读取单个字符
void test2()
{
    ifstream ifs {"data.txt"};
    // get()读取单个字符
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
    // get()读取单个字符
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

