#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

// 按字符读取
void test1()
{
    // 创建文件输入流对象
    ifstream ifs {"data.txt"};
    // get()函数读取字符
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
    cout << "-------" << endl;
    // 判断文件是否读取到末尾
    cout << ifs.eof() << endl;

    ifs.close();
}

// 循环读取
void test2()
{
    // 创建文件输入流对象
    ifstream ifs {"data.txt"};
    int ch;
    while ((ch = ifs.get()) != -1) {
        cout << (char)ch << endl;
    }
    ifs.close();
}

void test3()
{
    // 创建文件输入流对象
    ifstream ifs { "data.txt" };
    // get函数读取字符
    char ch;
    ifs.get(ch);
    cout << ch << endl;
    ifs.get(ch);
    cout << ch << endl;
    ifs.get(ch);
    cout << ch << endl;

    ifs.close();
}

// 按单词进行读取 利用输入运算符
void test4()
{
    ifstream ifs { "data.txt" };
    // 输入运算符提取数据
    string word;
    ifs >> word;
    cout << word << endl;
    ifs >> word;
    cout << word << endl;
    ifs >> word;
    cout << word << endl;
    ifs >> word;
    cout << word << endl;
    ifs >> word;
    cout << word << endl;
    cout << ifs.eof() << endl;
    ifs.close();
}

// 循环按单词读取
void test5()
{
    ifstream ifs { "data.txt" };
    // 输入运算符提取数据
    string word;
    while(!ifs.eof()){
        ifs >> word;
        cout << word << endl;
    }
    ifs.close();
}

void test6()
{
    ifstream ifs { "data.txt" };
    // 输入运算符提取数据
    string word;
    while(ifs >> word){

        cout << word << endl;
    }
    ifs.close();
}


int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    test6();

    return 0;
}

