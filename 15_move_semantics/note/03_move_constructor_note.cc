#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/**
 * 移动构造函数与移动赋值运算符函数：
 *
 * 1. 移动构造函数
 *
 *    作用：
 *    使用一个右值对象初始化一个新对象。
 *
 *    典型形式：
 *    类名(类名 && rhs);
 *
 *    例如：
 *    String s = String{"hello"};
 *
 *    其中 String{"hello"} 是一个临时对象，
 *    可以被右值引用 String && rhs 绑定。
 *
 *
 * 2. 移动赋值运算符函数
 *
 *    作用：
 *    使用一个右值对象给一个已经存在的对象赋值。
 *
 *    典型形式：
 *    类名 & operator=(类名 && rhs);
 *
 *    例如：
 *    String s1{"hello"};
 *    s1 = String{"abc"};
 *
 *    s1 已经存在，
 *    String{"abc"} 是临时对象，
 *    所以可以调用移动赋值运算符函数。
 *
 *
 * 3. 移动语义的核心思想
 *
 *    对于管理堆资源的类来说，
 *    拷贝构造和拷贝赋值需要进行深拷贝：
 *
 *    - 重新申请堆空间
 *    - 复制字符串内容
 *
 *    而移动构造和移动赋值并不复制资源，
 *    而是直接接管临时对象内部已有的资源。
 *
 *    也就是：
 *    - 当前对象直接拿到 rhs.m_pstr 指向的堆空间
 *    - 再把 rhs.m_pstr 设置为 nullptr
 *
 *    这样 rhs 析构时就不会释放这块空间，
 *    资源的所有权就成功转移给了当前对象。
 *
 *
 * 4. 编译器自动生成的特殊成员函数
 *
 *    类中如果没有显式定义这些特殊成员函数，
 *    编译器在满足条件时可能会自动生成：
 *
 *    - 默认构造函数
 *    - 拷贝构造函数
 *    - 拷贝赋值运算符函数
 *    - 析构函数
 *    - 移动构造函数
 *    - 移动赋值运算符函数
 *
 *    但是注意：
 *    对于管理裸指针资源的类，
 *    不能依赖编译器默认生成的拷贝或移动函数。
 *
 *    因为默认生成的版本通常只会逐成员拷贝，
 *    对指针成员来说就是浅拷贝，
 *    容易造成多个对象指向同一块堆空间，
 *    最终出现 double free 等问题。
 *
 *    所以资源管理类一般需要自己实现：
 *    - 析构函数
 *    - 拷贝构造函数
 *    - 拷贝赋值运算符函数
 *    - 移动构造函数
 *    - 移动赋值运算符函数
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
     * 其中多出来的 1 个字符用于存放字符串结束符 '\0'。
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
     * 这里进行深拷贝：
     * 1. 重新申请堆空间
     * 2. 复制 rhs 中的字符串内容
     *
     * 深拷贝可以避免两个对象共用同一块堆空间。
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
     * 当前对象原来可能已经管理了一块堆空间，
     * 所以赋值前需要先释放旧资源，
     * 然后重新申请空间并复制内容。
     */
    String & operator=(const String & rhs)
    {
        cout << "String &operator=(const String &)" << endl;

        // 防止自赋值，例如 s1 = s1;
        if(this != &rhs)
        {
            // 释放当前对象原来的堆空间，避免内存泄漏
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
     * 但不应该通过返回值修改字符串内容。
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
     * 对象生命周期结束时自动调用。
     *
     * m_pstr 指向的是通过 new [] 申请的堆空间，
     * 所以这里要通过 delete [] 释放。
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
     * 移动构造函数 move constructor
     *
     * 作用：
     * 使用一个右值对象初始化一个新的 String 对象。
     *
     * 参数：
     * String && rhs
     *
     * rhs 是右值引用，
     * 可以绑定临时对象。
     *
     * 例如：
     * String s = String{"world"};
     *
     * String{"world"} 是临时对象，
     * 如果没有移动构造函数，
     * 就可能调用拷贝构造函数进行深拷贝。
     *
     * 有了移动构造函数之后，
     * 可以直接把临时对象中的资源转移给新对象。
     *
     *
     * 初始化列表：
     * : m_pstr(rhs.m_pstr)
     *
     * 这里不是深拷贝，
     * 而是浅拷贝指针值。
     *
     * 也就是说：
     * 当前对象的 m_pstr 和 rhs.m_pstr
     * 暂时指向同一块堆空间。
     *
     * 但是马上会执行：
     * rhs.m_pstr = nullptr;
     *
     * 这样 rhs 就不再管理这块堆空间，
     * 当前对象成为这块资源唯一的管理者。
     */
    String(String && rhs)
    : m_pstr(rhs.m_pstr)
    {
        cout << "move constructor" << endl;

        /**
         * 将临时对象的指针置空。
         *
         * 目的：
         * 防止 rhs 析构时释放这块已经转移出去的堆空间。
         *
         * 如果不置空，
         * 当前对象和 rhs 会指向同一块堆空间，
         * 两个对象析构时都会 delete []，
         * 导致 double free。
         */
        rhs.m_pstr = nullptr;
    }

    /**
     * 移动赋值运算符函数 move assignment operator
     *
     * 作用：
     * 使用一个右值对象给已经存在的对象赋值。
     *
     * 参数：
     * String && rhs
     *
     * rhs 可以绑定右值对象或临时对象。
     *
     * 例如：
     * String s1{"hello"};
     * s1 = String{"abc"};
     *
     * 其中 String{"abc"} 是临时对象，
     * 可以调用移动赋值运算符函数。
     *
     *
     * 移动赋值与移动构造的区别：
     *
     * 移动构造：
     * 当前对象是新创建的对象，
     * 之前没有管理旧资源。
     *
     * 移动赋值：
     * 当前对象已经存在，
     * 可能已经管理了一块旧资源。
     *
     * 所以移动赋值前，
     * 必须先释放当前对象原来的资源，
     * 再接管 rhs 的资源。
     */
    String& operator=(String && rhs)
    {
        cout <<"move operator=" << endl;

        /**
         * 自赋值判断
         *
         * 理论上右值引用通常绑定临时对象，
         * 但仍然可能出现类似下面的情况：
         *
         * s1 = std::move(s1);
         *
         * 此时 rhs 引用的其实就是 s1 自己。
         *
         * 如果不做自赋值判断，
         * 可能会先释放自己的资源，
         * 然后又把已经释放的指针赋回来，
         * 导致错误。
         */
        if(this != &rhs)
        {
            /**
             * 释放当前对象原本管理的堆空间。
             *
             * 这里 delete [] m_pstr;
             * 即使 m_pstr 是 nullptr 也是安全的，
             * 所以没有必须写 if(m_pstr)。
             */
            delete [] m_pstr;

            /**
             * 接管 rhs 的资源。
             *
             * 这里不是深拷贝，
             * 不会重新申请空间，也不会复制字符串内容。
             *
             * 只是把 rhs.m_pstr 的指针值赋给当前对象。
             *
             * 这一步之后，
             * 当前对象和 rhs 暂时指向同一块堆空间。
             */
            m_pstr = rhs.m_pstr;

            /**
             * 将 rhs 的指针置空。
             *
             * 这样 rhs 就不再管理这块资源。
             *
             * 当 rhs 之后析构时，
             * delete [] nullptr 是安全的，
             * 不会影响当前对象已经接管的资源。
             */
            rhs.m_pstr = nullptr;
        }

        /**
         * 返回当前对象本身。
         *
         * 这样可以支持连续赋值：
         * s1 = s2 = String{"abc"};
         */
        return  *this;
    }

private:
    // 指向堆空间的字符指针
    // String 对象负责管理这块资源
    char * m_pstr;
};


// 测试移动构造函数
void test1()
{
    /**
     * String s = "world";
     *
     * 这行代码属于拷贝初始化。
     *
     * 理论上可以理解为：
     * 1. 先调用 String(const char *) 创建临时对象
     * 2. 再使用这个临时对象初始化 s
     *
     * 如果没有移动构造函数，
     * 可能会调用拷贝构造函数。
     *
     * 如果有移动构造函数，
     * 临时对象是右值，
     * 就可以调用移动构造函数，
     * 将临时对象中的资源转移给 s。
     *
     *
     * 注意：
     * 编译器可能会进行拷贝省略 copy elision，
     * 直接用 "world" 构造 s，
     * 从而看不到移动构造函数调用。
     *
     * 如果想观察移动构造函数的调用，
     * 可以尝试添加编译选项：
     * -fno-elide-constructors --std=c++11
     */
    String s = "world";
}


// 测试移动赋值运算符函数
void test2()
{
    /**
     * 调用有参构造函数，
     * 创建普通对象 s1。
     */
    String s1{"hello"};

    /**
     * s1 = String{"abc"};
     *
     * 赋值号左边：
     * s1 是已经存在的对象，是左值。
     *
     * 赋值号右边：
     * String{"abc"} 是临时对象，是右值。
     *
     *
     * 执行过程：
     *
     * 1. 调用 String(const char *) 创建临时对象
     *
     * 2. 因为右边是右值，
     *    并且类中定义了：
     *    String& operator=(String && rhs)
     *
     *    所以优先调用移动赋值运算符函数，
     *    而不是拷贝赋值运算符函数。
     *
     * 3. 移动赋值中：
     *    - 释放 s1 原来保存 "hello" 的堆空间
     *    - 让 s1.m_pstr 指向临时对象保存 "abc" 的堆空间
     *    - 将临时对象的 m_pstr 置为 nullptr
     *
     * 4. 语句结束后，
     *    临时对象生命周期结束，调用析构函数。
     *    因为它的 m_pstr 已经是 nullptr，
     *    所以不会释放 s1 已经接管的资源。
     */
    s1 = String{"abc"};
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();

    return 0;
}