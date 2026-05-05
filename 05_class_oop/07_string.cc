#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// string 的构造方式
void test1()
{
    // string();
    // 无参构造函数，创建一个空字符串 ""
    string s1;
    cout << "s1=" << s1 << endl;

    // string(const char * rhs);
    // 通过 C 风格字符串构造 string 对象
    string s2 {"hello"};
    cout << "s2=" << s2 << endl;

    // string(const char * rhs, size_type count);
    // 使用 rhs 的前 count 个字符构造 string 对象
    string s3 {"hello", 3};
    cout << "s3=" << s3 << endl;

    // string(const string & rhs);
    // 拷贝构造函数
    string s4 {s2};
    cout << "s4=" << s4 << endl;

    // string(const string & rhs, size_t pos, size_t count);
    // 使用 string 对象中从 pos 开始的 count 个字符构造新的 string 对象
    string s5 {s2, 1, 3};
    cout << "s5=" << s5 << endl;

    // string(size_type count, char ch);
    // 创建一个包含 count 个 ch 字符的 string 对象

    // 注意：
    // 使用花括号初始化时，可能优先匹配 initializer_list 构造方式
    string s6 {98, 'a'};
    cout << "s6=" << s6 << endl;

    string s8 {'a', 'b', 'c'};
    cout << "s8=" << s8 << endl;

    // 使用小括号初始化，明确调用 string(size_type count, char ch)
    string s7(97, 'a');
    cout << "s7=" << s7 << endl;

    // string(InputIt first, InputIt last);
    // 使用区间 [first, last) 内的字符构造 string 对象
    string s9 {"abcdef"};
    string s10 {s9.begin(), s9.end()};
    
    cout << "s10=" << s10 << endl;
}


// 迭代器：可以理解为广义上的指针
// 使用方式类似指针
void test2()
{
    string str {"abcdef"};

    // 获取首迭代器：指向第一个字符的位置
    /* auto itBegin = str.begin(); */

    string::iterator itBegin = str.begin();

    cout << *itBegin << endl;

    ++itBegin;

    cout << *itBegin << endl;

    // 获取尾迭代器：指向最后一个元素的下一个位置
    auto itEnd = str.end();

    // 尾迭代器不能直接解引用，需要先执行 -- 操作
    /* cout << *itEnd << endl; */
}


// string 中常见的操作
void test3()
{
    string str {"hello"};

    // 元素访问：at(index)
    cout << str.at(0) << endl;

    // 也可以通过 operator[] 下标访问运算符访问元素
    cout << str[1] << endl;

    // 访问首字符和尾字符
    cout << str.front() << endl;
    cout << str.back() << endl;

    // 获取 C 风格字符串
    const char * p = str.c_str();
    cout << p << endl;

    cout << "-------" << endl;

    // 容量相关操作
    cout << str.size() << endl;
    cout << str.length() << endl;
    cout << str.empty() << endl;
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}