#include <cstddef>
#include <iostream>
#include <cstring>
#include <new>
#include <ostream>

using namespace std;

class String
{
private:
    char * m_pstr;

public:
    // 默认构造函数
    String()
    : m_pstr(new char[1]())
    {
        cout << "String()" << endl;
    }
    
    // 有参构造函数
    String(const char * pstr)
    : m_pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(m_pstr, pstr);
    }
    
    // 拷贝构造函数
    String(const String & rhs)
    : m_pstr(new char[strlen(rhs.m_pstr) + 1]())
    {
        cout << "String(const String &)" << endl;
        strcpy(m_pstr, rhs.m_pstr);
    }

    // 拷贝赋值运算符函数
    // 用一个已有对象给另一个已有对象赋值
    String & operator=(const String & rhs)
    {
        cout << "String &operator=(const String &)" << endl;

        // 判断是否自赋值
        if(this != &rhs)
        {   
            // 先释放当前对象原来管理的堆空间
            if(m_pstr)
            {
                delete [] m_pstr;
            }
            m_pstr = new char[strlen(rhs.m_pstr) + 1]();
            strcpy(m_pstr, rhs.m_pstr);
        }
        // 返回当前对象本身，支持连续赋值
        // 例如：s3 = s2 = s1;
        return *this;
    }

    // 移动构造函数
    // 使用一个右值对象初始化新对象
    // 例如：String s2 = std::move(s1);
    //
    // 移动构造不会重新申请堆空间，也不会复制字符串内容
    // 而是直接接管 rhs 所管理的资源
    String(String && rhs)
    : m_pstr(rhs.m_pstr)
    {
        cout << "String(String &&)" << endl;
        // 将 rhs 的指针置空
        // 防止 rhs 析构时释放已经转移给当前对象的空间
        rhs.m_pstr = nullptr;
    }

    // 移动赋值运算符函数
    // 使用一个右值对象给已有对象赋值
    // 例如：s2 = std::move(s1);
    //
    // 移动赋值也不会复制字符串内容
    // 而是释放当前对象原资源后，接管 rhs 的资源
    String & operator=(String && rhs)
    {
        cout << "String &operator=(String &&)" << endl;

        // 防止自移动赋值
        if(this != &rhs)
        {
            // 先释放当前对象原来管理的堆空间
            if(m_pstr)
            {
                delete [] m_pstr;
            }

            // 直接接管 rhs 的资源
            m_pstr = rhs.m_pstr;

            // 将 rhs 置空
            // 防止 rhs 析构时重复释放同一块堆空间
            rhs.m_pstr = nullptr;
        }
        // 返回当前对象本身，支持连续赋值
        return *this;
    }

    // 获取字符串长度
    size_t length() const
    {
        size_t len = 0;
        // 如果 m_pstr 不为空，则调用 strlen 计算长度
        if(m_pstr)
        {
            len = strlen(m_pstr);
        }
        return len;
    }

    // 返回 C 风格字符串
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

    // 析构函数
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
        }
        else
        {
            cout << "m_pstr = nullptr" << endl;
        }
    }

};

// 测试拷贝构造函数
void test1()
{
    cout << "====== test1: copy constructor ======" << endl;
    // 调用有参构造函数
    String s1("hello");
    // s1是左值,因此这里调用拷贝构造函数
    String s2 = s1;
    
    cout << "s1: ";
    s1.print();

    cout << "s2: ";
    s2.print();

}

// 测试移动构造函数
void test2()
{
    cout << "====== test2: move constructor ======" << endl;
    // 调用有参构造函数
    String s1("hello");

    // std::move(s1) 将 s1 转换为右值
    // 因此这里调用移动构造函数
    String s2 = std::move(s1);

    // 移动之后，s1 的资源已经转移给 s2
    // s1.m_pstr 被置为 nullptr
    cout << "s1: ";
    s1.print();

    cout << "s2: ";
    s2.print();
}

// 测试移动赋值函数
void test3()
{
    cout << "====== test3: move assignment ======" << endl;

    // 调用有参构造函数
    String s1("hello");
    String s2("world");

    // std::move(s1) 将 s1 转换为右值
    // 因此这里调用移动赋值运算符函数
    s2 = std::move(s1);

    // 移动之后，s1 的资源已经转移给 s2
    cout << "s1: ";
    s1.print();

    cout << "s2: ";
    s2.print();
}

// 测试临时对象触发移动赋值
void test4()
{
    cout << "====== test4: temporary object move assignment ======" << endl;

    // 调用有参构造函数
    String s1("hello");

    // String("world") 是临时对象，属于右值
    // 因此这里优先调用移动赋值运算符函数
    s1 = String("world");

    cout << "s1: ";
    s1.print();
}

int main()
{
    test1();
    cout << endl;

    test2();
    cout << endl;

    test3();
    cout << endl;

    test4();

    return 0;
}
