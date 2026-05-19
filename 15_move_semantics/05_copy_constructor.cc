#include <string.h>
#include <utility>
#include <iostream>

using std::cout;
using std::endl;

/*
 * 拷贝构造函数调用时机的补充：
 *
 * 1. 用一个已经存在的对象初始化一个新对象
 *      String s2 = s1;
 *
 * 2. 对象作为函数参数，且函数形参是值传递
 *      void func(String str);
 *
 * 3. 对象作为函数返回值
 *      String func();
 *
 * 注意：
 *      在对象作为返回值时，编译器可能会进行返回值优化，
 *      因此实际运行时不一定能观察到拷贝构造或移动构造。
 *      观察这个过程时可加编译选项：-fno-elide-constructors --std=c++11
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

    // 移动构造函数：参数是右值引用，用于绑定临时对象或将亡值
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


// 值传递参数：调用函数时需要用实参初始化形参 str
void func(String str)
{
    str.print();
}

// 值传递参数：如果传入左值会调用拷贝构造，如果传入右值会调用移动构造
void func2(String str)
{
    str.print();
}

String func3()
{
    // 局部对象
    String s{"hello"};

    // 返回局部对象：
    // 编译器可能直接做返回值优化；
    // 如果关闭优化，在 C++11 中通常会优先尝试移动构造。
    return s;
}

String str { "aaa" };

String func4()
{
    // 返回全局对象 str：
    // str 是左值，不是即将销毁的局部对象，
    // 因此通常会调用拷贝构造，而不是移动构造。
    return str;
}

// 测试对象作为函数参数
void test1()
{
    String s{"abc"};

    /* func(s); */
    // s 是左值，值传递给形参 str 时会调用拷贝构造。

    func2(std::move(s));
    // std::move(s) 将 s 转换为右值，
    // 值传递给形参 str 时会调用移动构造。
    //
    // 注意：移动后 s 仍然是有效对象，
    // 但其内部资源已经被转移，当前实现中 s.m_pstr 被置为 nullptr。
}

// 测试对象作为函数返回值
void test2()
{
    /* func3(); */
    // 返回局部对象时，可能发生返回值优化；
    // 若关闭拷贝省略，通常可以观察到移动构造。

    func4();
    // 返回全局对象 str 时，str 是左值，
    // 因此通常调用拷贝构造。
}



int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}