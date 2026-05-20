#include <string.h>
#include <vector>
#include <utility>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

/*
 * std::move()
 *
 * 主要作用：
 *      将一个左值强制转换为右值引用。
 *
 * 注意：
 *      std::move 本身只是类型转换，不会移动任何资源；
 *      真正的资源转移发生在移动构造函数或移动赋值运算符函数中。
 *
 * 使用场景：
 *      当一个对象后续不再需要原有资源时，可以使用 std::move
 *      将其转换为右值，从而触发移动语义。
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


// 使用 std::move 触发移动赋值
void test1()
{
    String s{"hello"}; // s 是有名字的对象，因此是左值
    &s;

    /* &std::move(s); */
    // std::move(s) 将左值 s 转换为右值引用表达式；
    // 转换后的表达式是右值，通常不能再取地址。

    String s2  {"world"};

    /* s2 = s; */
    // s 是左值，如果直接赋值，会调用拷贝赋值运算符函数。

    s2 = std::move(s);
    // std::move(s) 将 s 转换为右值，
    // 因此这里会优先调用移动赋值运算符函数。
    //
    // 注意：移动后 s 仍然是一个有效对象，
    // 但其内部资源已经被转移，当前实现中 s.m_pstr 被置为 nullptr。
}

// vector 的拷贝构造
void test2()
{
    vector<int> v1{1,2,3};

    // v1 是左值，因此这里调用 vector 的拷贝构造函数
    // v2 会拥有一份与 v1 内容相同但独立的资源
    vector<int> v2 = v1;

    // 拷贝后 v1 的内容保持不变
    cout << "v1 size:" << v1.size() << endl;
    cout << "v2 size:" << v2.size() << endl;
}

// vector 的移动构造
void test3()
{
    vector<int> v1{1,2,3};

    // std::move(v1) 将 v1 转换为右值，
    // 因此这里调用 vector 的移动构造函数。
    //
    // v2 接管 v1 原本管理的动态数组资源，
    // 避免重新申请空间和拷贝元素。
    vector<int> v2 = std::move(v1);

    // 移动后 v1 仍然是有效对象，可以析构、重新赋值或调用成员函数；
    // 但它的具体状态是“有效但未指定”的，不应依赖其原有内容。
    cout << "v1 size:" << v1.size() << endl;
    cout << "v2 size:" << v2.size() << endl;
}


int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}