#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

/**
 * 自定义的 String 类
 *
 * 这个类用来模拟 C++ 标准库中的 std::string。
 *
 * 本质上：
 * String 类内部使用一个 char * 指针，
 * 指向堆区申请的一段字符数组空间，
 * 用来保存字符串内容。
 *
 *
 * 为什么需要自己写这些函数？
 * 因为 String 类中有指针成员 m_pstr，
 * 这个指针管理的是堆区资源。
 *
 * 只要类中涉及堆区资源，
 * 通常就需要自己实现：
 *
 * 1. 构造函数
 *    负责申请资源。
 *
 * 2. 拷贝构造函数
 *    负责用一个已有对象创建新对象。
 *    这里必须进行深拷贝。
 *
 * 3. 赋值运算符函数
 *    负责两个已经存在的对象之间的赋值。
 *    这里也必须进行深拷贝。
 *
 * 4. 析构函数
 *    负责释放资源。
 *
 * 这几个函数也常被称为：
 * 拷贝控制函数。
 *
 * 如果没有正确实现深拷贝，
 * 多个对象可能会指向同一块堆空间，
 * 最终导致重复释放的问题。
 */
class String
{
public:
    // constructor

    /**
     * 无参构造函数
     *
     * 当创建 String 对象时，
     * 如果没有传入任何参数，
     * 就会调用这个构造函数。
     *
     * 例如：
     * String s1;
     *
     *
     * : m_pstr(new char[1]{})
     *
     * 这是构造函数初始化列表。
     *
     * new char[1]{} 表示：
     * 在堆区申请一个 char 数组，
     * 数组中只有 1 个字符空间。
     *
     * {} 表示进行初始化，
     * 对 char 来说会初始化为 '\0'。
     *
     * 所以这个空字符串中只有一个字符串结束符 '\0'。
     *
     *
     * 为什么空字符串也要申请一个字符空间？
     *
     * 因为 C 风格字符串必须以 '\0' 结尾。
     * 即使字符串内容为空，
     * 也需要一个 '\0' 来表示字符串结束。
     */
    String()
    : m_pstr(new char[1]{})
    {
        cout << "String()" << endl;
    }

    /**
     * 有参构造函数
     *
     * 参数：
     * const char * pstr
     *
     * 表示传入一个 C 风格字符串。
     *
     * 例如：
     * String s2{"abc"};
     *
     * 此时 pstr 指向字符串常量 "abc"。
     *
     *
     * strlen(pstr)
     *
     * 作用：
     * 计算字符串的有效字符个数，
     * 不包括末尾的 '\0'。
     *
     * 例如：
     * strlen("abc") 的结果是 3。
     *
     *
     * new char[strlen(pstr) + 1]{}
     *
     * 为什么要 + 1？
     *
     * 因为 C 风格字符串末尾必须保存 '\0'。
     *
     * "abc" 实际需要 4 个字符空间：
     * 'a' 'b' 'c' '\0'
     */
    String(const char * pstr)
    : m_pstr(new char[strlen(pstr) + 1]{})
    {
        cout << "String(const char *)" << endl;

        /**
         * strcpy(dest, src)
         *
         * 作用：
         * 将 src 指向的 C 风格字符串，
         * 拷贝到 dest 指向的空间中。
         *
         * 这里就是把 pstr 中的字符串内容，
         * 拷贝到 m_pstr 指向的堆空间中。
         *
         * 注意：
         * strcpy 会把字符串末尾的 '\0' 一起拷贝过去。
         */
        strcpy(m_pstr, pstr);
    }

    // copy constructor

    /**
     * 拷贝构造函数
     *
     * 作用：
     * 使用一个已经存在的 String 对象，
     * 初始化一个新的 String 对象。
     *
     * 例如：
     * String s3 = s2;
     *
     * 此时会调用拷贝构造函数。
     *
     *
     * 参数：
     * const String & rhs
     *
     * rhs 是被拷贝的对象。
     *
     * const 表示不会修改 rhs。
     * & 表示引用传递，避免拷贝。
     *
     *
     * 为什么不能直接写：
     * m_pstr = rhs.m_pstr;
     *
     * 因为这样只是浅拷贝。
     *
     * 浅拷贝会导致：
     * s3.m_pstr 和 s2.m_pstr 指向同一块堆空间。
     *
     * 当两个对象析构时，
     * 同一块堆空间会被 delete 两次，
     * 程序就会出错。
     *
     *
     * 所以这里必须进行深拷贝：
     * 1. 重新申请一块新的堆空间。
     * 2. 再把 rhs 中的字符串内容拷贝过来。
     */
    String(const String & rhs)
    : m_pstr(new char[strlen(rhs.m_pstr) + 1]{})
    {
        cout << "copy constructor" << endl;
        strcpy(m_pstr, rhs.m_pstr);
    }

    // operator=

    /**
     * 赋值运算符函数
     *
     * 作用：
     * 处理两个已经存在的 String 对象之间的赋值。
     *
     * 例如：
     * s4 = s3;
     *
     * 注意：
     * 赋值运算符函数和拷贝构造函数不一样。
     *
     * 拷贝构造：
     * 用一个已有对象创建一个新对象。
     *
     * 赋值运算符：
     * 两个对象都已经存在，
     * 然后把右操作数的内容赋值给左操作数。
     *
     *
     * 返回类型：
     * String &
     *
     * 返回当前对象本身，
     * 这样可以支持连续赋值：
     *
     * s1 = s2 = s3;
     */
    String & operator=(const String & rhs)
    {
        // 自赋值判断

        /**
         * this
         *
         * this 是一个指针，
         * 指向当前正在调用成员函数的对象。
         *
         * &rhs 表示右操作数对象的地址。
         *
         * this != &rhs 表示：
         * 当前对象和 rhs 不是同一个对象。
         *
         *
         * 为什么要进行自赋值判断？
         *
         * 如果出现：
         * s1 = s1;
         *
         * 如果不判断自赋值，
         * 先 delete [] m_pstr，
         * 就会把 s1 自己的数据释放掉。
         *
         * 后面再从 rhs.m_pstr 拷贝数据时，
         * rhs.m_pstr 其实也已经失效了。
         *
         * 所以自赋值判断非常重要。
         */
        if(this != &rhs){
            // 回收原本空间

            /**
             * 赋值前，当前对象可能已经管理了一块堆空间。
             *
             * 例如：
             * String s4{"hello"};
             * s4 = s3;
             *
             * s4 原来保存的是 "hello"。
             * 赋值时，需要先释放原来的空间，
             * 再重新申请空间保存 s3 的内容。
             */
            delete [] m_pstr;
            m_pstr = nullptr;

            // 深拷贝

            /**
             * 重新申请一块堆空间，
             * 大小为 rhs 字符串长度 + 1。
             *
             * +1 是为了存放字符串结束符 '\0'。
             */
            char * temp = new char[strlen(rhs.m_pstr) + 1]{};

            // 将 rhs 中的字符串内容拷贝到新空间中
            strcpy(temp, rhs.m_pstr);

            // 让当前对象的 m_pstr 指向这块新空间
            m_pstr = temp;
        }

        // 返回*this

        /**
         * *this 表示当前对象本身。
         *
         * 因为 this 是指针，
         * 所以 *this 就是这个指针指向的对象。
         *
         * 返回 *this 可以支持链式赋值。
         */
        return *this;
    }

    // destructor

    /**
     * 析构函数
     *
     * 当对象生命周期结束时，
     * 析构函数会自动调用。
     *
     * 作用：
     * 释放对象占用的资源。
     *
     * 对于这个 String 类来说，
     * 析构函数需要释放 m_pstr 指向的堆空间。
     *
     *
     * 什么时候会调用析构函数？
     *
     * 1. 局部对象离开作用域时。
     * 2. 临时对象生命周期结束时。
     * 3. delete 一个堆对象时。
     *
     *
     * 注意：
     * new char[] 申请的数组空间，
     * 必须使用 delete [] 释放。
     *
     * new 和 delete 要配对。
     * new [] 和 delete [] 要配对。
     */
    ~String()
    {
        cout << "~String()" << endl;

        /**
         * 判断 m_pstr 是否为空。
         *
         * 如果 m_pstr 不是 nullptr，
         * 说明它指向一块需要释放的堆空间。
         */
        if(m_pstr){
            delete [] m_pstr;

            /**
             * 释放之后将指针置为空。
             *
             * 好处：
             * 避免野指针。
             *
             * 野指针：
             * 指针保存的地址已经无效，
             * 但指针本身还不是 nullptr。
             */
            m_pstr = nullptr;
        }
    }

    // size()

    /**
     * size()
     *
     * 作用：
     * 返回字符串中有效字符的个数。
     *
     * 这里直接使用 strlen(m_pstr)。
     *
     * 注意：
     * strlen 统计的是 '\0' 之前的字符个数，
     * 不包含字符串结束符 '\0'。
     *
     * 例如：
     * "hello" 的 size 是 5。
     */
    int size()
    {
        return strlen(m_pstr);
    }

    // c_str()

    /**
     * c_str()
     *
     * 作用：
     * 返回内部保存的 C 风格字符串。
     *
     * 这里返回的是 m_pstr，
     * 也就是内部字符数组的首地址。
     *
     *
     * 注意：
     * 标准库 std::string 的 c_str() 返回值通常是 const char *，
     * 表示外部不能通过这个指针修改字符串内容。
     *
     * 这里为了学习和演示，
     * 返回的是 char *。
     */
    char * c_str()
    {
        return m_pstr;
    }

    /**
     * print()
     *
     * 作用：
     * 打印当前 String 对象保存的字符串内容。
     */
    void print()
    {
        /**
         * 如果 m_pstr 不为空，
         * 就输出它指向的字符串。
         */
        if(m_pstr){
            cout << m_pstr << endl;
        }
    }

private:
    /**
     * m_pstr
     *
     * 指向堆区字符数组的指针。
     *
     * String 对象真正保存的字符串内容，
     * 就存放在 m_pstr 指向的空间中。
     *
     *
     * 例如：
     * String s{"abc"};
     *
     * 那么 m_pstr 指向一块堆空间，
     * 里面保存：
     * 'a' 'b' 'c' '\0'
     */
    char * m_pstr;
};

void test1()
{
    // 构造测试

    /**
     * 调用无参构造函数。
     *
     * s1 表示一个空字符串。
     * 内部 m_pstr 指向一块只保存 '\0' 的堆空间。
     */
    String s1;

    /**
     * 调用有参构造函数。
     *
     * 使用 C 风格字符串 "abc" 初始化 s2。
     *
     * s2 内部会重新申请堆空间，
     * 然后把 "abc" 拷贝进去。
     */
    String s2{ "abc" };

    // 打印 s2 保存的字符串内容
    s2.print();

    cout << "--------" << endl;

    // 拷贝构造测试

    /**
     * 用 s2 初始化 s3。
     *
     * 这里是在创建新对象 s3，
     * 所以调用的是拷贝构造函数，
     * 不是赋值运算符函数。
     *
     * s3 和 s2 各自拥有独立的堆空间。
     */
    String s3 = s2;

    s3.print();

    cout << "----------" << endl;

    // operator=测试

    /**
     * 创建 s4，
     * 调用有参构造函数，
     * s4 内部保存 "hello"。
     */
    String s4 { "hello" };

    /**
     * s4 = s3;
     *
     * 这里 s4 和 s3 都已经存在，
     * 所以调用赋值运算符函数 operator=。
     *
     * 执行过程：
     * 1. 判断是否自赋值。
     * 2. 释放 s4 原来保存 "hello" 的堆空间。
     * 3. 根据 s3 的内容重新申请堆空间。
     * 4. 将 s3 的字符串内容拷贝给 s4。
     * 5. 返回当前对象 s4。
     */
    s4 = s3;

    s4.print();

    cout << "----------" << endl;

    // 输出 s4 中字符串的有效字符个数
    cout << s4.size() << endl;
}

int main(int argc, char *argv[])
{
    /**
     * main 函数是程序入口。
     *
     * 当前程序执行 test1()，
     * 用来测试自定义 String 类的：
     *
     * 1. 无参构造函数
     * 2. 有参构造函数
     * 3. 拷贝构造函数
     * 4. 赋值运算符函数
     * 5. 析构函数
     * 6. size()
     * 7. print()
     */
    test1();

    return 0;
}