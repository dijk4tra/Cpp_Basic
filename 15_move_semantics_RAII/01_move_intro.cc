#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/*
 * 复制语义：对象之间进行“深拷贝”，各自拥有独立资源。
 *      拷贝构造函数
 *      拷贝赋值运算符函数
 *
 * 移动语义：将临时对象或即将失效对象中的资源“转移”给新对象，
 *          避免不必要的资源申请与数据拷贝。
 *      移动构造函数
 *      移动赋值运算符函数
 *
 * 当前类中只实现了复制语义，尚未实现移动语义。
 */
class String
{
public:
    // 无参构造函数：创建一个空字符串
    String()
    /* : _pstr(nullptr) */
    : m_pstr(new char[1]())
    {
        cout << "String()" << endl;
    }

    // 有参构造函数：根据 C 风格字符串创建 String 对象
    String(const char *pstr)
    : m_pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(m_pstr, pstr);
    }

    // 拷贝构造函数：用已有对象初始化新对象，执行深拷贝
    String(const String & rhs)
    : m_pstr(new char[strlen(rhs.m_pstr) + 1]())
    {
        cout << "String(const String &)" << endl;
        strcpy(m_pstr, rhs.m_pstr);
    }

    // 拷贝赋值运算符函数：用已有对象给当前对象赋值，执行深拷贝
    String & operator=(const String & rhs)
    {
        cout << "String &operator=(const String &)" << endl;
        if(this != &rhs)
        {
            if(m_pstr)
            {
                delete [] m_pstr;
            }
            m_pstr = new char[strlen(rhs.m_pstr) + 1]();
            strcpy(m_pstr, rhs.m_pstr);
        }
        return *this;
    }

    // 获取字符串长度
    size_t length() const
    {
        size_t len = 0;
        if(m_pstr)
        {
            len = strlen(m_pstr);
        }

        return len;
    }

    // 获取底层 C 风格字符串
    const char * c_str() const
    {
        if(m_pstr)
        {
            return m_pstr;
        }
        else
        {
            return nullptr;
        }
    }

    // 析构函数：释放对象持有的堆内存资源
    ~String()
    {
        cout << "~String()" << endl;
        if(m_pstr)
        {
            delete [] m_pstr;
            m_pstr = nullptr;
        }
    }

    // 打印字符串内容
    void print() const
    {
        if(m_pstr)
        {
            cout << "m_pstr = " << m_pstr << endl;
        }else{
            cout << endl;
        }
    }

private:
    char * m_pstr;  // 指向堆区字符数组，表示当前 String 对象管理的字符串资源
};

void test1()
{
    /* String s1("hello"); */
    // 使用 s1 初始化 s2，会调用拷贝构造函数
    /* String s2 = s1; */

    cout << "---------" << endl;

    // 使用字符串字面值初始化 s3：
    // 先通过 String(const char *) 构造临时对象，
    // 再用该临时对象初始化 s3。
    // 在 C++11 中可通过 -fno-elide-constructors 关闭拷贝省略，观察完整过程。
    String s3 = "hello";

    cout << "---------" << endl;

    // 创建一个临时 String 对象，再将其赋值给 s3。
    // 当前类未实现移动赋值，因此这里会调用拷贝赋值运算符函数。
    s3 = String{"bcd"};
}


int main(int argc, char *argv[])
{
    test1();
    return 0;
}