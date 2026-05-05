#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

// 自定义 String 类
class String
{
private:
    char *_pstr;

public:
    // 默认构造函数
    // 创建一个空字符串，注意不是 nullptr，而是指向 '\0'
    String()
    : _pstr(new char[1]{'\0'})
    {
        cout << "String()" << endl;
    }

    // 使用 C 风格字符串构造 String 对象
    String(const char * pstr)
    : _pstr(new char[strlen(pstr) + 1]{})
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
    }

    // 拷贝构造函数
    // 使用深拷贝，避免多个对象共用同一块堆空间
    String(const String & rhs)
    : _pstr(new char[strlen(rhs._pstr) + 1]{})
    {
        cout << "String(const String &)" << endl;
        strcpy(_pstr, rhs._pstr);
    }

    // 赋值运算符重载
    String &operator=(const String &rhs)
    {
        cout << "operator=(const String &)" << endl;

        // 防止自赋值，例如 str = str;
        if(this != &rhs) {
            // 先申请新空间
            char *temp = new char[strlen(rhs._pstr) + 1]{};
            strcpy(temp, rhs._pstr);

            // 释放原来的空间
            delete [] _pstr;

            // 指向新空间
            _pstr = temp;
        }

        // 返回当前对象本身，支持连续赋值
        return *this;
    }

    // 析构函数
    ~String()
    {
        cout << "~String()" << endl;

        delete [] _pstr;
        _pstr = nullptr;
    }

    // 打印字符串内容
    void print()
    {
        cout << _pstr << endl;
    }

    // 追加另一个 String 对象
    String &append(const String &rhs)
    {
        return append(rhs._pstr);
    }

    // 追加一个 C 风格字符串
    String &append(const char *pstr)
    {
        // 如果传入空指针，直接返回当前对象
        if(pstr == nullptr) {
            return *this;
        }

        // 计算拼接后的长度
        size_t oldLen = strlen(_pstr);
        size_t addLen = strlen(pstr);
        size_t newLen = oldLen + addLen;

        // 申请新空间
        char *temp = new char[newLen + 1]{};

        // 复制原字符串
        strcpy(temp, _pstr);

        // 拼接新字符串
        strcat(temp, pstr);

        // 释放原空间
        delete [] _pstr;

        // 指向新空间
        _pstr = temp;

        return *this;
    }

    // 获取字符串长度
    size_t length() const
    {
        return strlen(_pstr);
    }

    // 获取 C 风格字符串
    const char *c_str() const
    {
        return _pstr;
    }

};

void test_append()
{
    String s1("Hello");
    String s2(", world");

    s1.append(s2);
    s1.print();

    s1.append("!");
    s1.print();

    cout << s1.length() << endl;
    cout << s1.c_str() << endl;
}

int main(int argc, char *argv[])
{   
    String str1;
    str1.print();

    String str2 = "Hello,world";
    String str3("wangdao");

    str2.print();
    str3.print();

    String str4 = str3;
    str4.print();

    str4 = str2;
    str4.print();
    
    /* test_append(); */

    return 0;
}

