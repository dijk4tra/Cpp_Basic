#include <string.h>
#include <iostream>
#include <string> // c++中的字符串

using std::cout;
using std::endl;
using std::string;

/*
 * C风格字符串的两种形式
 * 1.字符数组
 * 2.字符指针形式
 */

void test1()
{
    // 字符数组
    char str1[] = "hello";
    char str2[] = {'a','b','c','\0'};
    // 注意!!!对与字符数组或者字符指针,
    // cout可以直接输出其内容
    cout << str1 << endl;
    cout << str2 << endl;
    cout << sizeof(str1) << endl;
    cout << sizeof(str2) << endl;
    cout << strlen(str1) << endl;
    cout << strlen(str2) << endl;
}

void test2()
{
    // C++标准中规定:对与字符串常量,
    // 应该使用指向常量的指针去指向它
    const char * pstr = "hello";
    cout << pstr << endl;
    cout << sizeof(pstr) << endl; //指针的大小为8字节
    cout << strlen(pstr) << endl;
}

// 字符串的复制,拼接操作 
void test3()
{
    const char * s1 = "hello";
    // 开辟新的空间
    char * s2 = new char[strlen(s1) + 1]{};
    strcpy(s2, s1);
    cout << s2 << endl;
    delete [] s2;
    s2 = nullptr;
}

void test4()
{
    const char * s1 = "abc";
    const char * s2 = "def";
    /* s1 + s2; */
    //开辟新空间
    char * str = new char[strlen(s1) + strlen(s2) + 1]{};
    strcpy(str, s1);
    strcat(str, s2);
    cout << str << endl;
    delete [] str;
    str = nullptr;
}

void test5()
{
    string s1 = "abc";
    string s2 = "def";
    string s3 = s1 + s2;
    cout << s3 << endl;
    cout << s1.size() << endl;
    cout << s1[0] << endl;
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    test5();
    return 0;
}

