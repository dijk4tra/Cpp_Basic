#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/*
 * 移动构造函数：
 *      使用右值引用参数，接管临时对象中的资源，
 *      避免重新申请空间和拷贝数据。
 *
 * 移动赋值运算符函数：
 *      当前对象先释放自己原有资源，
 *      再接管右值对象中的资源。
 *
 * 特殊成员函数：
 *      默认构造函数
 *      拷贝构造函数
 *      拷贝赋值运算符函数
 *      析构函数
 *      移动构造函数
 *      移动赋值运算符函数
 *
 * 注意：
 *      移动构造和移动赋值并不是任何情况下都会自动生成。
 *      如果类中显式定义了拷贝构造、拷贝赋值或析构函数等，
 *      编译器通常不会再自动生成移动构造和移动赋值。
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

    // 移动构造函数：参数是右值引用，用于绑定临时对象
    String(String && rhs)
    : m_pstr(rhs.m_pstr) // 直接接管 rhs 的资源，本质上是指针层面的“浅拷贝”
    {
        cout << "move constructor" << endl;

        // 将 rhs 的指针置空，避免 rhs 析构时释放已经转移出去的资源
        rhs.m_pstr = nullptr;
    }

    // 移动赋值运算符函数：用右值对象给当前对象赋值
    String& operator=(String && rhs)
    {
        cout <<"move operator=" << endl;

        // 防止自身移动赋值
        if(this != &rhs){

            // 先释放当前对象原本持有的资源
            delete [] m_pstr;

            // 接管 rhs 的资源，避免重新申请空间和拷贝字符串内容
            m_pstr = rhs.m_pstr;

            // 将 rhs 置为空状态，避免 rhs 析构时重复释放资源
            rhs.m_pstr = nullptr;
        }

        // 返回当前对象本身
        return  *this;
    }

private:
    char * m_pstr;  // 指向堆区字符数组，表示当前 String 对象管理的字符串资源
};


// 测试移动构造函数
void test1()
{
    // 字符串字面值先构造临时 String 对象，
    // 再用该临时对象初始化 s；
    // 如果关闭拷贝省略，可以观察到移动构造函数的调用。
    String s = "world";
}


// 测试移动赋值运算符函数
void test2()
{
    String s1{"hello"};

    // String{"abc"} 是临时对象，属于右值；
    // 因此这里会优先调用移动赋值运算符函数。
    s1 = String{"abc"};
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}