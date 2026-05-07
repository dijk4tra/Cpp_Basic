#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

// 输出流对象的创建
void test1()
{
    // 无参构造,默认打开模式为out
    ofstream ofs;
    ofs.open("data.txt");

    // 有参构造
    ofstream ofs2 {"data.txt"};
    string fileName = "data.txt";
    ofstream ofs3 {fileName};
}

/*
 * 写数据到文件的步骤
 * 1.创建输出流对象
 * 2.利用write函数活着输出运算符写数据
 * 3.close
 */

void test2()
{
    // 有参构造
    // 如果目标文件不存在,则创建
    // 如果目标文件已存在,默认打开模式为out,文件内容会被清空!
    ofstream ofs {"data2.txt"};
    ofs << "abc";
    ofs << 123 << " ";
    ofs << 3.14;

    ofs.close();
}

// 利用write函数写数据
void test3()
{
    ofstream ofs {"data.txt"};
    string msg = "hello world";
    ofs.write(msg.c_str(), msg.size());
    ofs.close();
}

// 追加写入
void test4()
{
    // 默认模式out ---> app
    ofstream ofs {"data.txt", std::ios::app};
    string msg = "abcdef";
    ofs.write(msg.c_str(), msg.size());
    ofs.close();
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    test4();
    return 0;
}

