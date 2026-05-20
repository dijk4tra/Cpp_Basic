#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/*
 * 左值：通常是有名字、可持久存在的对象，一般可以取地址。
 *      例如：变量、对象、字符串字面值等。
 *
 * 右值：通常是临时产生、即将销毁的值，一般不能取地址。
 *      例如：表达式结果、匿名对象、字面值常量等。
 *
 * 引用分类：
 * 1. 左值引用
 *      - 非 const 左值引用：只能绑定左值
 *      - const 左值引用：既能绑定左值，也能绑定右值
 *
 * 2. 右值引用
 *      - 形式：数据类型 && 引用名 = 右值;
 *      - 只能绑定右值，用于区分临时对象，常用于移动语义
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


class Point{};

void test1()
{
    // 常见的左值：有名字、可取地址
    int a = 1;
    int b = 2;
    &a;
    &b;

    // 对象 pt 是左值，可以取地址
    Point pt;
    &pt;

    // 字符串字面值具有静态存储期，可以取地址
    &"hello";

    // 常见的右值：临时结果、临时对象、字面值常量等，通常不能取地址
    /* &(a + b); */   // 表达式 a + b 的结果是右值
    /* &a++; */       // 后置 ++ 的结果是右值
    /* &Point{}; */   // 匿名临时对象是右值
    /* &100; */       // 字面值常量是右值
}

void test2()
{
    int a = 1;

    // 非 const 左值引用：只能绑定左值，不能绑定右值
    int & ref = a;
    ref = 2;
    /* int & ref2 = 1; */

    // const 左值引用：既能绑定左值，也能绑定右值
    const int & ref3 = a;
    /* ref3 = 2; */       // const 引用不能通过引用修改绑定对象
    const int & ref4 = 1; // 绑定右值时，可以延长临时对象的生命周期

    // const 左值引用过于宽泛，无法区分绑定的是左值还是右值
    // 因此 C++11 引入右值引用，用于识别和处理右值

    // 右值引用：只能绑定右值
    /* int && ref5 = a; */ // a 是左值，不能绑定到右值引用
    int && ref6 = 1;       // 1 是右值，可以绑定到右值引用
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}