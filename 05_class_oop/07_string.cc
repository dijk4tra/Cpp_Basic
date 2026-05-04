#include <asm-generic/errno.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void test1()
{
// string(); //无参构造函数,生成一个空字符串""
    string s1;
    cout << "s1=" << s1 << endl;

// string(const char *rhs); // 通过C风格字符串构造一个string对象
    string s2 {"hello"};
    cout << "s2=" << s2 << endl;

// string(const char * rhs, size_type count);
    string s3 {"hello", 3};
    cout << "s3=" << s3 << endl;
}


void test2()
{
    string str {"abcdef"};
    // 获取首迭代器
    /* auto itBegin = str.begin(); //简略写法 */
    string::iterator itBegin = str.begin();
    cout << *itBegin << endl;
    ++itBegin;
    cout << *itBegin << endl;
    // 尾迭代器:指向的是最后一个元素的下个位置
    auto itEnd = str.end();
    // 需要对尾迭代器做--操作
    /* cout << *itEnd << endl; */
    
}


//string中常见的操作
void test3()
{
    string str {"hello"};
    // 元素访问 at(index);
    cout << str.at(0) << endl;
    // 还可以通过operator[]下标访问运算符函数
    cout << str[1] << endl;
    // 访问首字符,尾字符
    cout << str.front() << endl;
    cout << str.back() << endl;
    const char *p = str.c_str();
    cout << p << endl;

    cout << "-------" << endl;
    // 容量
    cout << str.size() << endl;
    cout << str.length() << endl;
    
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

