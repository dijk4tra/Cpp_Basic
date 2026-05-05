#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

// 自定义 String 类
class String
{
public:
    // 构造函数
    String()
    : m_pstr(new char[1]{})
    {
        cout << "String()" << endl;
    }

    String(const char * pstr)
    : m_pstr(new char[strlen(pstr) + 1]{})
    {
        cout << "String(const char *)" << endl;
        strcpy(m_pstr, pstr);
    }

    // 拷贝构造函数
    String(const String & rhs)
    : m_pstr(new char[strlen(rhs.m_pstr) + 1]{})
    {
        cout << "copy constructor" << endl;
        strcpy(m_pstr, rhs.m_pstr);
    }

    // 赋值运算符重载
    String & operator=(const String & rhs)
    {
        // 判断是否为自赋值
        if(this != &rhs){
            // 释放原有空间
            delete [] m_pstr;
            m_pstr = nullptr;

            // 深拷贝 rhs 中的数据
            char * temp = new char[strlen(rhs.m_pstr) + 1]{};
            strcpy(temp, rhs.m_pstr);
            m_pstr = temp;
        }

        // 返回当前对象本身
        return *this;
    }

    // 析构函数
    ~String()
    {
        cout << "~String()" << endl;

        if(m_pstr){
            delete [] m_pstr;
            m_pstr = nullptr;
        }
    }

    // 获取字符串长度
    int size()
    {
        return strlen(m_pstr);
    }

    // 获取 C 风格字符串
    char * c_str()
    {
        return m_pstr;
    }

    void print()
    {
        if(m_pstr){
            cout << m_pstr << endl;
        }
    }

private:
    char * m_pstr;
};

void test1()
{
    // 测试构造函数
    String s1;
    String s2{ "abc" };
    s2.print();

    cout << "--------" << endl;

    // 测试拷贝构造函数
    String s3 = s2;
    s3.print();

    cout << "----------" << endl;

    // 测试赋值运算符重载
    String s4 { "hello" };
    s4 = s3;
    s4.print();

    cout << "----------" << endl;

    cout << s4.size() << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}