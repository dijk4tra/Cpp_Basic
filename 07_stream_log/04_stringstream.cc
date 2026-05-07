#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;
using std::ostringstream;

/**
 * 字符串流: 数据类型之间进行转换
 * istringstream: string ---> 其它类型的数据
 * ostringstream: 其它类型的数据 ---> string
 */

void test1()
{
    // 基于string来创建一个字符串输入流
    string str = "123 456";
    // "123" ---> int
    // "3.14" ---> double
    istringstream iss {str};
    // 数据转换:利用输入运算符做转换
    int num1;
    int num2;
    iss >> num1 >> num2;
    cout << "num1:" << num1 << endl;
    cout << "num2:" << num2 << endl;
}


void test2()
{
    // 基于string来创建一个字符串输入流
    string str = "123 3.14";
    // "123" ---> int
    // "3.14" ---> double
    istringstream iss {str};
    // 数据转换:利用输入运算符
    int num1;
    double num2;
    iss >> num1 >> num2;
    cout << "num1:" << num1 << endl;
    cout << "num2:" << num2 << endl; 
}

// 通过istringstream解析数据
void test3()
{
    // 创建输入流对象
    ifstream ifs {"db.conf"};
    // 循环按行读取
    string line;
    while (std::getline(ifs, line)) {
        // 利用istringstream进行处理
        // 把字符串数据交给istringstream
        istringstream iss {line};
        string key; // 存属性名
        string value; // 存属性值
        iss >> key;
        iss >> value;
        cout << "key:" << key << " = " << "value:" << value << endl;
    }
}

void test4()
{
    // 创建字符串输出流对象
    ostringstream oss;
    int num1 = 123;
    double num2 = 3.14;
    // 123--->"123"  int--->string
    // 3.14--->"3.14" double--->strinh
    // 把数据交给oss
    // 利用输出运算符进行处理
    oss << num1 << " " << num2;
    // str()函数得到字符串数据
    string s = oss.str();
    cout << "s:" << s << endl;
}


int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    test4();
    return 0;
}

