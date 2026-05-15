#include <iostream>
#include <string>
#include <string.h>

using std::cout;
using std::endl;
using std::string;

/**
 * operator[] 下标运算符重载：
 *
 * 对于数组、string 这类类型来说，
 * 可以通过 [] 下标访问某个位置的元素。
 *
 * 例如：
 * str[0];
 *
 * 但是 CharArray 是自定义类型，
 * 如果希望 CharArray 对象也可以像数组一样使用 []，
 * 就需要重载 operator[]。
 *
 * 表达式：
 * ch[0];
 *
 * 本质上等价于：
 * ch.operator[](0);
 *
 * 注意：
 * operator[] 通常采用成员函数形式重载。
 *
 * 因为下标运算符左边必须是当前对象，
 * 下标值作为参数传入。
 */

// 定义一个字符数组类 CharArray
class CharArray
{
public:
    /**
     * 构造函数。
     *
     * 参数 pstr 是一个 C 风格字符串。
     *
     * 构造 CharArray 对象时：
     * 1. 根据字符串长度申请堆空间
     * 2. 保存字符串长度
     * 3. 把 pstr 中的内容拷贝到堆空间中
     */
    CharArray(const char * pstr)
    : m_pstr(new char[strlen(pstr) + 1])
    , m_size(strlen(pstr))
    {
        cout << "Constructor" << endl;

        /**
         * 将 pstr 指向的字符串内容，
         * 拷贝到 m_pstr 指向的堆空间中。
         *
         * 注意：
         * new char[strlen(pstr) + 1]
         * 多申请的 1 个空间，
         * 是为了存放字符串结束符 '\0'。
         */
        strcpy(m_pstr, pstr);
    }

    /**
     * 析构函数。
     *
     * CharArray 内部使用了 new[] 申请堆空间，
     * 所以对象销毁时需要使用 delete[] 释放。
     */
    ~CharArray()
    {
        cout << "Destructor" << endl;

        /**
         * 释放 m_pstr 指向的字符数组空间。
         *
         * new[] 和 delete[] 要配套使用。
         */
        delete [] m_pstr;

        // 避免野指针
        m_pstr = nullptr;
    }

    /**
     * 重载下标运算符 operator[]。
     *
     * 表达式：
     * ch[index]
     *
     * 本质上等价于：
     * ch.operator[](index);
     *
     * 参数：
     * index 表示要访问的下标位置。
     *
     * 返回值：
     * char &
     *
     * 返回引用的原因：
     * 1. 可以避免拷贝
     * 2. 可以支持修改对应位置的字符
     *
     * 例如：
     * ch[0] = 'A';
     *
     * 如果返回 char，
     * 那么 ch[0] 得到的是一个临时值，
     * 就不能作为左值被修改。
     */
    char & operator[](int index)
    {
        /**
         * 判断 index 是否合法。
         *
         * 合法范围：
         * 0 <= index < m_size
         *
         * 如果 index 小于 0，
         * 或者 index 大于等于字符串长度，
         * 都属于非法下标。
         */
        if (index < 0 || index >= m_size)
        {
            cout << "Index is illegal!" << endl;

            /**
             * 下标非法时的处理方式：
             *
             * 这里没有直接抛出异常，
             * 而是返回一个静态局部变量 nullChar。
             *
             * 因为函数返回值类型是 char &，
             * 必须返回一个真实存在的 char 对象。
             *
             * 不能返回普通局部变量的引用，
             * 因为普通局部变量在函数结束后会被销毁。
             */
            /* throw "Index is illegal!"; */

            static char nullChar = '\0';
            return nullChar;
        }

        /**
         * 返回指定下标位置的字符引用。
         *
         * 因为返回的是引用，
         * 所以既可以读取字符，
         * 也可以修改字符。
         */
        return m_pstr[index];
    }

    /**
     * 打印字符数组中的字符串内容。
     */
    void print()
    {
        cout << m_pstr << endl;
    }

private:
    // 指向堆空间中的字符数组
    char * m_pstr;

    // 字符串的有效字符个数，不包含 '\0'
    int m_size;
};

void test1()
{
    string str = "abc";

    /**
     * string 类型已经重载了 operator[]，
     * 所以可以通过下标访问字符串中的字符。
     */
    cout << str[0] << endl;
    cout << str[1] << endl;
    cout << str[2] << endl;

    cout << "----------" << endl;

    /**
     * str[0] 的本质：
     *
     * 调用了 string 类中的 operator[] 成员函数。
     *
     * str[0]
     *
     * 等价于：
     * str.operator[](0)
     */
    cout << str.operator[](0) << endl;
    cout << str.operator[](1) << endl;
    cout << str.operator[](2) << endl;
}

void test2()
{
    /**
     * 创建 CharArray 对象，
     * 内部保存字符串 "abcd"。
     */
    CharArray ch {"abcd"};

    // 打印整个字符串
    ch.print();

    /**
     * 通过下标访问对应位置的元素。
     *
     * ch[0]
     *
     * 本质上等价于：
     * ch.operator[](0);
     */
    cout << ch[0] << endl;

    // ch.operator[](0);
}

int main(int argc, char *argv[])
{
    /**
     * test1 用来观察 string 的 operator[] 调用形式。
     *
     * test2 用来测试自定义 CharArray 的 operator[]。
     */
    /* test1(); */
    test2();

    return 0;
}