#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

// 按单词读取
void test1()
{
    // 创建文件输入流对象ifs,并打开data.txt文件
    ifstream ifs {"data.txt"};
    // 用来保存每次从文件中读取的单词
    string word;
    // 循环按单词读取   
    while (ifs >> word) {
        cout << word << endl;
    }
    // 关闭文件
    ifs.close();
}

// 按行读取
void test2()
{
    // 创建文件输入流对象ifs,并打开data.txt文件
    ifstream ifs {"data.txt"};
    // 用来保存每次读取到的一整行内容
    string line;
    // 循环按行读取
    while (std::getline(ifs, line)) {
        cout << line << endl;
    }
    // 关闭文件
    ifs.close();

}


int main(int argc, char *argv[])
{
    /* test1(); */
    test2();
    return 0;
}

