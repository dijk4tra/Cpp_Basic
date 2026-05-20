#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/**
 * 拷贝构造函数调用时机的补充
 *
 * 拷贝构造函数通常在“用一个对象初始化另一个新对象”时调用。
 *
 * 常见调用时机：
 *
 * 1. 用一个已经存在的对象初始化一个新对象
 *
 *    例如：
 *    String s1{"hello"};
 *    String s2 = s1;
 *
 *    s2 是新对象，
 *    s1 是已经存在的对象，
 *    所以这里会调用拷贝构造函数。
 *
 *
 * 2. 对象作为函数参数，按值传递
 *
 *    例如：
 *    void func(String str);
 *
 *    String s{"abc"};
 *    func(s);
 *
 *    形参 str 是一个新的 String 对象，
 *    需要用实参 s 来初始化，
 *    所以会调用拷贝构造函数。
 *
 *    如果传入的是右值：
 *    func(std::move(s));
 *
 *    并且类中定义了移动构造函数，
 *    那么可以调用移动构造函数。
 *
 *
 * 3. 对象作为函数返回值
 *
 *    例如：
 *    String func()
 *    {
 *        String s{"hello"};
 *        return s;
 *    }
 *
 *    函数返回值需要用函数内部对象进行初始化。
 *
 *    在 C++11 之后，
 *    如果返回的是局部对象，
 *    编译器可以进行返回值优化，
 *    或者在不能省略时优先使用移动构造。
 *
 *    如果返回的是全局对象或静态对象这类左值，
 *    则通常调用拷贝构造。
 *
 *
 * 注意：
 * 实际运行时是否能看到拷贝构造或移动构造的打印，
 * 会受到编译器优化影响。
 *
 * 如果想观察构造过程，
 * 可以尝试添加编译选项：
 * -fno-elide-constructors --std=c++11
 */

class String
{
public:
    /**
     * 默认构造函数
     *
     * 创建一个空字符串对象。
     * m_pstr 指向一块只存放 '\0' 的堆空间。
     */
    String()
    /* : _pstr(nullptr) */
    : m_pstr(new char[1]())
    {
        cout << "String()" << endl;
    }

    /**
     * 有参构造函数
     *
     * 根据 C 风格字符串 pstr 创建 String 对象。
     * 申请 strlen(pstr) + 1 个字符空间，
     * 多出的 1 个字符用于保存字符串结束符 '\0'。
     */
    String(const char *pstr)
    : m_pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(m_pstr, pstr);
    }

    /**
     * 拷贝构造函数
     *
     * 使用一个已经存在的 String 对象初始化新对象。
     *
     * 因为 String 类中管理堆资源，
     * 所以这里需要进行深拷贝：
     * 1. 重新申请堆空间
     * 2. 复制 rhs 中的字符串内容
     */
    String(const String & rhs)
    : m_pstr(new char[strlen(rhs.m_pstr) + 1]())
    {
        cout << "String(const String &)" << endl;
        strcpy(m_pstr, rhs.m_pstr);
    }

    /**
     * 拷贝赋值运算符函数
     *
     * 用一个已经存在的 String 对象给当前对象赋值。
     *
     * 注意：
     * 当前对象已经存在，
     * 所以需要先释放旧资源，
     * 再申请新资源并复制内容。
     */
    String & operator=(const String & rhs)
    {
        cout << "String &operator=(const String &)" << endl;

        // 防止自赋值
        if(this != &rhs)
        {
            // 释放当前对象原来管理的堆资源
            if(m_pstr)
            {
                delete [] m_pstr;
            }

            // 重新申请空间并复制 rhs 的字符串内容
            m_pstr = new char[strlen(rhs.m_pstr) + 1]();
            strcpy(m_pstr, rhs.m_pstr);
        }

        return *this;
    }

    /**
     * 获取字符串长度
     *
     * const 成员函数表示不会修改当前对象。
     */
    size_t length() const
    {
        size_t len = 0;

        if(m_pstr)
        {
            len = strlen(m_pstr);
        }

        return len;
    }

    /**
     * 返回 C 风格字符串
     *
     * 返回 const char *，
     * 表示外部只能读取字符串内容，
     * 不应该通过返回值修改内部数据。
     */
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

    /**
     * 析构函数
     *
     * 对象生命周期结束时自动调用，
     * 释放 m_pstr 指向的堆空间。
     */
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
            cout << endl;
        }
    }

    /**
     * 移动构造函数
     *
     * 使用右值对象初始化新对象。
     *
     * 这里不进行深拷贝，
     * 而是直接接管 rhs 中的堆资源。
     */
    String(String && rhs)
    : m_pstr(rhs.m_pstr)
    {
        cout << "move constructor" << endl;

        // 将 rhs 的指针置空，
        // 防止 rhs 析构时释放已经转移出去的资源。
        rhs.m_pstr = nullptr;
    }

    /**
     * 移动赋值运算符函数
     *
     * 使用右值对象给已经存在的对象赋值。
     *
     * 移动赋值中：
     * 1. 释放当前对象原来的资源
     * 2. 接管 rhs 的资源
     * 3. 将 rhs 的指针置空
     */
    String& operator=(String && rhs)
    {
        cout <<"move operator=" << endl;

        // 防止自移动赋值，例如 s = std::move(s);
        if(this != &rhs)
        {
            // 回收当前对象原本管理的堆空间
            delete [] m_pstr;

            // 接管 rhs 的资源
            m_pstr = rhs.m_pstr;

            // rhs 不再管理这块资源
            rhs.m_pstr = nullptr;
        }

        return  *this;
    }

private:
    // 指向堆空间的字符指针
    // String 对象负责管理这块资源
    char * m_pstr;
};


/**
 * func 的参数是按值传递：
 *
 * void func(String str)
 *
 * 形参 str 是一个新的 String 对象。
 * 调用函数时，需要用实参初始化 str。
 *
 * 如果实参是左值：
 * func(s);
 *
 * 会调用拷贝构造函数。
 *
 * 如果实参是右值：
 * func(std::move(s));
 *
 * 会调用移动构造函数。
 */
void func(String str)
{
    str.print();
}

/**
 * 与 func 类似，
 * 这里也是按值传参。
 *
 * 保留两个类似函数是为了分别测试不同调用场景。
 */
void func2(String str)
{
    str.print();
}

/**
 * func3 的返回值类型是 String。
 *
 * 函数内部创建了一个局部对象 s。
 *
 * return s;
 *
 * s 是有名字的局部对象，
 * 从表达式分类上看，s 本身是左值。
 *
 * 但是在返回局部对象时，
 * 编译器会把它当作可以被移动的对象处理。
 *
 * 因此：
 * 1. 编译器可能直接进行返回值优化 RVO / NRVO，
 *    省略拷贝或移动构造。
 *
 * 2. 如果没有进行优化，
 *    在 C++11 之后通常会调用移动构造函数。
 *
 * 所以这里常用于观察：
 * 对象作为函数返回值时，
 * 拷贝构造、移动构造以及返回值优化之间的关系。
 */
String func3()
{
    // 局部对象
    String s{"hello"};

    // 返回局部对象
    // 如果没有返回值优化，通常会调用移动构造
    return s;
}

/**
 * 全局对象 str
 *
 * 这个对象在全局作用域中定义，
 * 生命周期从程序开始附近持续到程序结束。
 *
 * str 是有名字的对象，
 * 所以表达式 str 是左值。
 */
String str { "aaa" };

/**
 * func4 的返回值类型是 String。
 *
 * return str;
 *
 * str 是全局对象，不是函数内部即将销毁的局部对象。
 *
 * 因此编译器不能像处理局部对象那样直接移动它，
 * 否则会破坏全局对象 str 的内容。
 *
 * 所以这里通常调用拷贝构造函数，
 * 用全局对象 str 初始化函数返回值。
 */
String func4()
{
    return str;
}


// 测试对象作为函数参数
void test1()
{
    /**
     * 调用有参构造函数，
     * 创建普通对象 s。
     *
     * s 是有名字的对象，
     * 所以表达式 s 是左值。
     */
    String s{"abc"};

    /**
     * func(s);
     *
     * func 的参数是按值传递。
     *
     * 形参 str 是新对象，
     * 需要用实参 s 初始化。
     *
     * s 是左值，
     * 所以调用拷贝构造函数。
     */
    /* func(s); */

    /**
     * func2(std::move(s));
     *
     * s 本来是左值。
     *
     * std::move(s) 将 s 转换成右值，
     * 所以可以调用移动构造函数，
     * 用 s 的资源初始化形参 str。
     *
     * 注意：
     * std::move 本身不移动资源，
     * 资源转移发生在移动构造函数中。
     *
     * 函数调用结束后，
     * 形参 str 被析构。
     *
     * 此时 s 仍然是合法对象，
     * 但是它原来的资源已经被移动走，
     * 不应该再依赖它原来的内容。
     */
    func2(std::move(s));
}


// 测试对象作为函数返回值类型
void test2()
{
    /**
     * func3();
     *
     * func3 内部返回局部对象 s。
     *
     * 可能发生：
     * 1. 返回值优化，直接构造返回值
     * 2. 如果不优化，则调用移动构造函数
     *
     * 如果想观察移动构造，
     * 可以尝试添加编译选项：
     * -fno-elide-constructors --std=c++11
     */
    /* func3(); */

    /**
     * func4();
     *
     * func4 返回的是全局对象 str。
     *
     * str 是左值，
     * 并且不能被默认当作即将销毁的对象处理。
     *
     * 因此这里通常调用拷贝构造函数。
     */
    func4();
}



int main(int argc, char * argv[])
{
    /* test1(); */
    test2();

    return 0;
}