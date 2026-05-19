#include <string.h>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

/**
 * std::move()
 *
 * 1. std::move 的主要作用
 *
 *    std::move 的作用是：
 *    将一个左值强制转换成右值引用类型。
 *
 *    简单理解：
 *    std::move 可以把一个左值“伪装成右值”，
 *    从而让编译器优先匹配移动构造函数或移动赋值运算符函数。
 *
 *
 * 2. std::move 本身不会移动资源
 *
 *    std::move 只是一次类型转换，
 *    它本身不申请资源、不释放资源、不转移资源。
 *
 *    真正完成资源转移的是：
 *    - 移动构造函数
 *    - 移动赋值运算符函数
 *
 *
 * 3. 为什么需要 std::move？
 *
 *    有名字的对象都是左值。
 *
 *    例如：
 *    String s{"hello"};
 *
 *    虽然 s 内部可能管理着堆资源，
 *    但是表达式 s 本身是左值。
 *
 *    如果直接写：
 *    s2 = s;
 *
 *    会调用拷贝赋值运算符函数。
 *
 *    如果写：
 *    s2 = std::move(s);
 *
 *    std::move(s) 会把 s 转成右值，
 *    从而可以调用移动赋值运算符函数。
 *
 *
 * 4. 使用 std::move 之后的对象
 *
 *    被 std::move 作用过的对象并不会立刻销毁。
 *
 *    但是如果它的资源真的被移动走了，
 *    那么它会处于“有效但未指定状态”。
 *
 *    有效：
 *    对象仍然可以析构、可以重新赋值。
 *
 *    未指定：
 *    不应该继续依赖它原来的值。
 *
 *    例如：
 *    vector<int> v2 = std::move(v1);
 *
 *    移动之后 v1 仍然是一个合法 vector，
 *    但是它里面还剩多少元素不应该依赖。
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
     * 因为 String 类管理堆资源，
     * 所以这里必须进行深拷贝。
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
     * 参数是 const String &，
     * 所以它可以绑定左值，
     * 也可以绑定右值。
     *
     * 但是当类中同时存在移动赋值运算符函数时，
     * 对于右值实参，编译器会优先选择移动赋值。
     */
    String & operator=(const String & rhs)
    {
        cout << "String &operator=(const String &)" << endl;

        // 防止自赋值
        if(this != &rhs)
        {
            // 释放旧资源
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
     * 表示外部可以读取字符串内容，
     * 但不应该通过返回值修改内容。
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
     * 移动构造不会重新申请空间并复制内容，
     * 而是直接接管 rhs 内部的堆资源。
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
     * 当前对象已经存在，
     * 所以需要先释放自己原来管理的资源，
     * 再接管 rhs 的资源。
     */
    String& operator=(String && rhs)
    {
        cout <<"move operator=" << endl;

        // 防止类似 s = std::move(s); 的自移动赋值
        if(this != &rhs)
        {
            // 释放当前对象原来的资源
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


// 使用 std::move
void test1()
{
    /**
     * s 是一个有名字的对象。
     *
     * 只要对象有名字，
     * 表达式 s 就是左值。
     */
    String s{"hello"};
    &s;

    /**
     * std::move(s)
     *
     * 作用：
     * 将左值 s 强制转换成右值引用类型。
     *
     * 注意：
     * std::move(s) 的结果是右值，
     * 因此不能直接对它取地址。
     *
     * 下面这行代码是错误的：
     */
    /* &std::move(s); */

    String s2  {"world"};

    /**
     * s2 = s;
     *
     * s 是左值。
     *
     * 如果执行这行代码，
     * 会调用拷贝赋值运算符函数：
     * String & operator=(const String & rhs)
     *
     * 拷贝赋值会进行深拷贝：
     * 1. 释放 s2 原来的资源
     * 2. 重新申请空间
     * 3. 复制 s 中的字符串内容
     */
    /* s2 = s; */

    /**
     * s2 = std::move(s);
     *
     * s 本来是左值，
     * 但是 std::move(s) 将它转换成右值。
     *
     * 因为类中定义了移动赋值运算符函数：
     * String& operator=(String && rhs)
     *
     * 所以这里会优先调用移动赋值运算符函数。
     *
     * 执行过程：
     * 1. 释放 s2 原来保存 "world" 的堆空间
     * 2. 让 s2.m_pstr 指向 s 原来保存 "hello" 的堆空间
     * 3. 将 s.m_pstr 设置为 nullptr
     *
     * 注意：
     * std::move 本身没有移动资源。
     * 资源转移发生在 operator=(String && rhs) 内部。
     *
     *
     * 移动之后：
     * s 仍然是一个合法对象，
     * 后续可以析构，也可以重新赋值。
     *
     * 但是 s 原来保存的 "hello" 已经被 s2 接管，
     * 所以不应该再依赖 s 原来的内容。
     */
    s2 = std::move(s);
}


// 拷贝构造
void test2()
{
    /**
     * 创建 vector 对象 v1，
     * 其中保存 1、2、3 三个元素。
     */
    vector<int> v1{1,2,3};

    /**
     * vector<int> v2 = v1;
     *
     * v1 是有名字的对象，是左值。
     *
     * 所以这里调用 vector 的拷贝构造函数，
     * 用 v1 初始化 v2。
     *
     * 拷贝构造会复制元素：
     * v1 和 v2 分别拥有各自的存储空间，
     * 但是内容相同。
     */
    vector<int> v2 = v1;

    /**
     * 拷贝之后：
     *
     * v1 没有被改变，
     * v2 中也有一份和 v1 相同的数据。
     *
     * 所以通常二者 size 都是 3。
     */
    cout << "v1 size:" << v1.size() << endl;
    cout << "v2 size:" << v2.size() << endl;
}


// 移动构造
void test3()
{
    /**
     * 创建 vector 对象 v1，
     * 其中保存 1、2、3 三个元素。
     */
    vector<int> v1{1,2,3};

    /**
     * vector<int> v2 = std::move(v1);
     *
     * v1 是左值。
     *
     * std::move(v1) 将 v1 转换成右值，
     * 从而可以调用 vector 的移动构造函数。
     *
     *
     * 移动构造通常不会逐个复制元素，
     * 而是直接转移 v1 内部管理的动态数组资源。
     *
     * 因此移动 vector 通常比拷贝 vector 更高效。
     */
    vector<int> v2 = std::move(v1);

    /**
     * 移动之后：
     *
     * v2 接管了原来 v1 内部的资源，
     * 所以 v2 通常保存原来的 3 个元素。
     *
     * v1 仍然是一个合法对象，
     * 可以析构、可以重新赋值、可以调用 size()。
     *
     * 但是标准只保证 v1 处于“有效但未指定状态”。
     *
     * 对于很多标准库实现来说，
     * 移动后的 v1.size() 可能是 0，
     * 但不要把这一点写成必须成立的逻辑。
     */
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