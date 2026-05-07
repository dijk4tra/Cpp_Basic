#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

// 循环读取单词
void test1()
{
    // 创建输入输出流对象
    ifstream ifs {"data.txt"};
    string word;
    while (ifs >> word) {
        cout << word << endl;
    }
    ifs.close();
}

//按行读取string中的getline
void test2()
{
    // 创建输入流对象
    ifstream ifs {"data.txt"};
    string line;
    // getline(流对象,要存储的数据的变量)
    std::getline(ifs, line);
    cout << line << endl;

    std::getline(ifs, line);
    cout << line << endl;

    std::getline(ifs, line);
    cout << line << endl;

    ifs.close();
}

// 按行读取string中的getline
void test3()
{
    // 创建输入流对象
    ifstream ifs {"data.txt"};
    string line;
    // 循环读取
    while(std::getline(ifs, line)){
        cout << line << endl;
    }
    ifs.close();
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}

