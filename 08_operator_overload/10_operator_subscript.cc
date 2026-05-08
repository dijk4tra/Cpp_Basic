#include <iostream>
#include <string>
#include <string.h>

using std::cout;
using std::endl;
using std::string;

// 定义一个字符数组类 CharArray
class CharArray
{
public:
    // 构造函数
    CharArray(const char * pstr)
    : m_pstr(new char[strlen(pstr) + 1])
    , m_size(strlen(pstr))
    {   
        cout << "Constructor" << endl;
        strcpy(m_pstr, pstr);
    }

    // 析构函数
    ~CharArray()
    {
        cout << "Destructor" << endl;
        delete [] m_pstr;
        m_pstr = nullptr;
    }

    // 重载 operator[]，用于通过下标访问字符数组中的元素
    char & operator[](int index)
    {
        // 判断下标是否合法
        if (index < 0 || index >= m_size)
        {
            cout << "Index is illegal!" << endl;

            // 下标非法时，可以选择返回默认值，也可以抛出异常
            /* throw "Index is illegal!"; */

            static char nullChar = '\0';
            return nullChar;
        }

        return m_pstr[index];
    }

    void print()
    {
        cout << m_pstr << endl;
    }

private:
    char * m_pstr;
    int m_size;
};

void test1()
{
    string str = "abc";
    cout << str[0] << endl;
    cout << str[1] << endl;
    cout << str[2] << endl;
    cout << "----------" << endl;

    // 本质：调用 string 类重载的 operator[] 函数
    cout << str.operator[](0) << endl;
    cout << str.operator[](1) << endl;
    cout << str.operator[](2) << endl;    
}

void test2()
{
    CharArray ch {"abcd"};
    ch.print();

    // 通过下标访问对应位置的字符
    cout << ch[0] << endl;

    // 本质：成员函数调用
    // ch.operator[](0);
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();
    
    return 0;
}