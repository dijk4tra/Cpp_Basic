#include <iostream>
#include <ostream>
#include <string.h>

using std::cout;
using std::endl;

// 自定义的String类
class String
{
public:
    // constructor
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

    // copy constructor
    String(const String & rhs)
    : m_pstr(new char[strlen(rhs.m_pstr) + 1]{})
    {
        cout << "copy constructor" << endl;
        strcpy(m_pstr, rhs.m_pstr);
    }

    // operator=
    String & operator=(const String & rhs)
    {
        // 自赋值判断
        if(this != &rhs){
            // 回收原本空间
            delete [] m_pstr;
            m_pstr = nullptr;
            // 深拷贝
            char * temp = new char[strlen(rhs.m_pstr) + 1]{};
            strcpy(temp, rhs.m_pstr);
            m_pstr = temp;
        }
        // 返回*this
        return *this;
    }

    // destructor
    ~String()
    {
        cout << "~String()" << endl;
        if(m_pstr){
            delete [] m_pstr;
            m_pstr = nullptr;
        }
    }

    // size()
    int size()
    {
        return strlen(m_pstr);
    }

    // c_str()
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
    // 构造测试
    String s1;
    String s2{ "abc" };
    s2.print();
    cout << "--------" << endl;
    // 拷贝构造测试
    String s3 = s2;
    s3.print();
    cout << "----------" << endl;
    // operator=测试
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

