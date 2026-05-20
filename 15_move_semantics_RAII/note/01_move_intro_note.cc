#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/**
 * 复制语义与移动语义：
 *
 * 1. 复制语义 copy semantics
 *    对象之间通过“复制资源”的方式完成初始化或赋值。
 *
 *    复制控制相关的函数主要包括：
 *    - 拷贝构造函数
 *    - 拷贝赋值运算符函数
 *    - 析构函数
 *
 *    对于管理堆资源的类来说，
 *    复制语义一般需要进行“深拷贝”。
 *    也就是：
 *    不能只复制指针的值，
 *    而是要重新申请一块堆空间，
 *    再把原对象指向的内容复制过去。
 *
 *
 * 2. 移动语义 move semantics
 *    对象之间通过“转移资源所有权”的方式完成初始化或赋值。
 *
 *    移动相关的函数主要包括：
 *    - 移动构造函数
 *    - 移动赋值运算符函数
 *
 *    移动语义通常用于处理临时对象，也就是右值对象。
 *    临时对象马上就要被销毁，
 *    如果还能把它内部管理的资源直接“拿过来”，
 *    就可以避免不必要的深拷贝。
 *
 *
 * 当前这个 String 类暂时只实现了：
 * - 构造函数
 * - 拷贝构造函数
 * - 拷贝赋值运算符函数
 * - 析构函数
 *
 * 还没有实现移动构造函数和移动赋值运算符函数。
 * 所以当右值对象参与初始化或赋值时，
 * 目前仍然会优先使用拷贝构造或拷贝赋值。
 */

class String
{
public:
    /**
     * 默认构造函数
     *
     * 作用：
     * 创建一个空字符串对象。
     *
     * 这里没有让 m_pstr 指向 nullptr，
     * 而是申请了一个长度为 1 的字符数组：
     * new char[1]()
     *
     * char[1] 用来存放字符串结束符 '\0'。
     * 后面的 () 表示对这块空间进行值初始化，
     * 对 char 来说就是初始化为 '\0'。
     *
     * 所以这个对象表示的是一个空字符串：
     * ""
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
     * 作用：
     * 使用一个 C 风格字符串创建 String 对象。
     *
     * 参数：
     * const char *pstr
     * pstr 指向一个以 '\0' 结尾的 C 风格字符串。
     *
     * strlen(pstr) 计算字符串有效字符个数，
     * 不包含结尾的 '\0'。
     *
     * 所以申请空间时需要 + 1，
     * 用来存放字符串结束符 '\0'。
     */
    String(const char *pstr)
    : m_pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;

        // 将 pstr 指向的字符串内容复制到 m_pstr 指向的堆空间中
        strcpy(m_pstr, pstr);
    }

    /**
     * 拷贝构造函数 copy constructor
     *
     * 作用：
     * 使用一个已经存在的 String 对象，
     * 初始化一个新的 String 对象。
     *
     * 参数：
     * const String & rhs
     * rhs 表示被拷贝的对象。
     *
     * 例如：
     * String s1("hello");
     * String s2 = s1;
     * String s3{s1};
     *
     * s2 和 s3 都是新对象，
     * 它们会通过 s1 拷贝构造出来。
     *
     *
     * 注意：
     * String 类中有裸指针成员 m_pstr，
     * 并且 m_pstr 指向堆空间。
     *
     * 如果这里只是简单写成：
     * m_pstr = rhs.m_pstr;
     * 那么两个对象会指向同一块堆空间，
     * 析构时会发生 double free 问题。
     *
     * 所以这里必须进行深拷贝：
     * 1. 根据 rhs.m_pstr 的内容长度重新申请堆空间
     * 2. 再把 rhs.m_pstr 指向的字符串内容复制过来
     */
    String(const String & rhs)
    : m_pstr(new char[strlen(rhs.m_pstr) + 1]())
    {
        cout << "String(const String &)" << endl;
        strcpy(m_pstr, rhs.m_pstr);
    }

    /**
     * 拷贝赋值运算符函数 copy assignment operator
     *
     * 作用：
     * 两个 String 对象都已经存在，
     * 将 rhs 对象的内容赋值给当前对象。
     *
     * 例如：
     * String s1("hello");
     * String s2("world");
     * s2 = s1;
     *
     * 这里 s2 已经存在，
     * 所以调用的是赋值运算符函数，
     * 而不是拷贝构造函数。
     *
     *
     * 返回值：
     * String &
     * 返回当前对象本身，
     * 这样可以支持连续赋值：
     * s1 = s2 = s3;
     *
     *
     * 参数：
     * const String & rhs
     * rhs 是赋值操作右边的对象。
     *
     *
     * 注意：
     * 赋值运算符函数中一般要考虑：
     * 1. 自赋值问题
     * 2. 释放旧资源
     * 3. 申请新资源
     * 4. 复制新内容
     * 5. 返回 *this
     */
    String & operator=(const String & rhs)
    {
        cout << "String &operator=(const String &)" << endl;

        // 防止自赋值
        // 例如：
        // s1 = s1;
        // 如果不判断自赋值，可能会先释放自己的资源，
        // 然后再从已经被释放的资源中复制数据，导致错误。
        if(this != &rhs)
        {
            // 当前对象原来可能已经管理了一块堆空间，
            // 赋新值之前，需要先释放旧资源，避免内存泄漏。
            if(m_pstr)
            {
                delete [] m_pstr;
            }

            // 重新申请一块足够大的堆空间
            m_pstr = new char[strlen(rhs.m_pstr) + 1]();

            // 将 rhs 中的字符串内容复制到当前对象中
            strcpy(m_pstr, rhs.m_pstr);
        }

        // 返回当前对象本身
        return *this;
    }

    /**
     * 获取字符串长度
     *
     * length() 只是读取对象内容，
     * 不会修改成员变量，
     * 所以后面加 const。
     *
     * size_t 是无符号整数类型，
     * 常用于表示大小、长度、下标等。
     */
    size_t length() const
    {
        size_t len = 0;

        // 如果 m_pstr 不为空，就计算字符串长度
        if(m_pstr)
        {
            len = strlen(m_pstr);
        }

        return len;
    }

    /**
     * 返回 C 风格字符串
     *
     * c_str() 只是读取对象内容，
     * 不修改成员变量，
     * 所以后面加 const。
     *
     * 返回值类型是 const char *，
     * 表示调用者可以读取字符串内容，
     * 但是不应该通过返回的指针修改字符串内容。
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
     * 析构函数 destructor
     *
     * 作用：
     * 对象生命周期结束时自动调用，
     * 用来释放对象管理的资源。
     *
     * 当前 String 类中，
     * m_pstr 指向的是通过 new [] 申请的堆空间，
     * 所以析构函数中要使用 delete [] 释放。
     *
     * 注意：
     * new [] 和 delete [] 要配套使用。
     */
    ~String()
    {
        cout << "~String()" << endl;

        if(m_pstr)
        {
            delete [] m_pstr;

            // 释放资源之后将指针置空，
            // 可以避免野指针。
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

private:
    // 指向堆空间的字符指针
    // 这个类自己负责申请和释放这块资源
    char * m_pstr;
};

void test1()
{
    /*
    String s1("hello");

    // 用已经存在的对象 s1 初始化新对象 s2
    // 这里会调用拷贝构造函数：
    // String(const String & rhs)
    String s2 = s1;
    */

    cout << "---------" << endl;

    /**
     * String s3 = "hello";
     *
     * 这行代码属于拷贝初始化。
     *
     * "hello" 是字符串字面值，
     * 它的类型可以转换成 const char *。
     *
     * 理论上可以理解为：
     * 1. 先调用 String(const char *) 构造一个临时 String 对象
     * 2. 再用这个临时对象拷贝构造 s3
     *
     * 也就是类似于：
     * String temp("hello");
     * String s3 = temp;
     *
     *
     * 但是注意：
     * 现代 C++ 编译器通常会进行拷贝省略 copy elision，
     * 可能直接用 "hello" 构造 s3，
     * 从而看不到拷贝构造函数被调用。
     *
     * 如果想观察临时对象和拷贝构造的过程，
     * 可以尝试添加编译选项：
     * -fno-elide-constructors --std=c++11
     *
     *
     * 当前 String 类还没有移动构造函数，
     * 所以即使中间产生的是临时对象，
     * 也不会调用移动构造。
     */
    String s3 = "hello";

    cout << "---------" << endl;

    /**
     * s3 = String{"bcd"};
     *
     * 这行代码属于赋值操作。
     *
     * s3 已经是一个存在的对象，
     * String{"bcd"} 会创建一个临时 String 对象，
     * 然后把这个临时对象赋值给 s3。
     *
     * 理论过程：
     * 1. 调用 String(const char *) 创建临时对象
     * 2. 调用赋值运算符函数，把临时对象的内容赋给 s3
     * 3. 临时对象生命周期结束，调用析构函数
     *
     *
     * 当前类中只实现了：
     * String & operator=(const String & rhs)
     *
     * 参数是 const String &，
     * const 引用可以绑定右值，
     * 所以临时对象 String{"bcd"} 可以作为 rhs 传入。
     *
     * 但是这里仍然是“拷贝赋值”，
     * 会重新申请堆空间并复制字符串内容。
     *
     * 如果后面实现了移动赋值运算符：
     * String & operator=(String && rhs)
     * 那么这类右值赋值场景就可以优先调用移动赋值，
     * 直接转移临时对象中的资源，避免深拷贝。
     */
    s3 = String{"bcd"};
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}