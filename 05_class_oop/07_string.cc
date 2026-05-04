#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/**
 * string 的构建
 *
 * string 是 C++ 标准库中提供的字符串类型。
 *
 * 头文件：
 * #include <string>
 *
 * 命名空间：
 * std::string
 *
 *
 * string 和 C 风格字符串的区别：
 *
 * 1. C 风格字符串
 *    本质是字符数组，通常以 '\0' 结尾。
 *
 *    例如：
 *    const char * p = "hello";
 *
 * 2. string
 *    是一个类类型。
 *    它内部封装了字符数据和很多操作函数，
 *    使用起来比 C 风格字符串更方便、更安全。
 *
 *
 * 本函数主要测试 string 的常见构造方式。
 */

void test1()
{
    /*
     * string()
     * 无参构造函数。
     *
     * 创建一个空字符串。
     *
     * s1 中没有任何字符，
     * 等价于：
     * string s1 = "";
     */
    string s1;
    cout << "s1=" << s1 << endl;

    /*
     * string(const char * rhs)
     * 通过 C 风格字符串构造一个 string 对象。
     *
     * "hello" 是字符串字面值，
     * 类型可以看作 const char *。
     */
    string s2 { "hello" };
    cout << "s2=" << s2 << endl;

    /*
     * string(const char * rhs, size_type count)
     * 通过 C 风格字符串 rhs 的前 count 个字符
     * 构造一个 string 对象。
     *
     * 这里表示：
     * 取 "hello" 的前 3 个字符，
     * 得到 "hel"。
     */
    string s3 { "hello", 3 };
    cout << "s3=" << s3 << endl;

    /*
     * string(const string & rhs)
     * 拷贝构造函数。
     *
     * 使用已有的 string 对象 s2，
     * 构造一个新的 string 对象 s4。
     *
     * 构造完成后：
     * s4 和 s2 的内容相同，
     * 都是 "hello"。
     */
    string s4 { s2 };
    cout << "s4=" << s4 << endl;

    /*
     * string(const string & rhs, size_t pos, size_t count)
     * 通过已有 string 对象的一部分
     * 创建新的 string 对象。
     *
     * 参数含义：
     * rhs   原字符串
     * pos   起始下标
     * count 取多少个字符
     *
     * s2 的内容是：
     * "hello"
     *
     * 下标：
     * h  e  l  l  o
     * 0  1  2  3  4
     *
     * string s5{ s2, 1, 3 };
     *
     * 表示从下标 1 开始取 3 个字符，
     * 得到 "ell"。
     */
    string s5{ s2, 1, 3 };
    cout << "s5=" << s5 << endl;

    /*
     * string(size_type count, char ch)
     * 构造一个 string 对象，
     * 该对象包含 count 个 ch 字符。
     *
     * 注意：
     * 这里使用的是大括号初始化。
     *
     * string s6{ 98, 'a' };
     *
     * 在不同构造函数匹配时，
     * 大括号初始化可能优先匹配 initializer_list 版本，
     * 例如string(initializer_list<char> init);
     * 这会导致string s6{ 98, 'a' };不会被理解为98 个 'a'，
     * 而是被理解为一个包含两个字符的字符串，
     * 即用用字符列表 {98, 'a'} 创建字符串，
     * 其中的98会被当成字符的 ASCII 码，转换成 'b'，
     * 最终的输出是 "s6=ba"。
     *
     * 所以这里需要特别注意构造函数匹配问题。
     */
    string s6{ 98, 'a' };
    cout << "s6=" << s6 << endl;

    /*
     * 使用 initializer_list<char> 构造 string。
     *
     * string s8{'a','b','c'};
     *
     * 表示用字符列表构造字符串，
     * 结果是：
     * "abc"
     */
    string s8{'a','b','c'};
    cout << "s8=" << s8 << endl;

    /*
     * 使用小括号初始化。
     *
     * string s7(97, 'a');
     *
     * 这种写法会明确匹配：
     * string(size_type count, char ch)
     *
     * 表示构造一个包含 97 个 'a' 的字符串。
     *
     * 注意：
     * 小括号初始化和大括号初始化在构造函数匹配上
     * 可能存在差异。
     */
    string s7(97,'a');
    cout << "s7=" << s7 << endl;

    /*
     * string(InputIt first, InputIt last)
     *
     * 通过迭代器区间 [first, last)
     * 构造一个 string 对象。
     *
     * [first, last) 是左闭右开区间：
     * 包含 first 指向的元素，
     * 不包含 last 指向的元素。
     */

    string s9 { "abcdef" };

    /*
     * s9.begin()
     * 返回指向第一个字符的迭代器。
     *
     * s9.end()
     * 返回指向最后一个字符后一个位置的迭代器。
     *
     * string s10 { s9.begin(), s9.end() };
     *
     * 表示使用 s9 的完整字符区间
     * 构造一个新的字符串 s10。
     *
     * 所以 s10 的内容也是：
     * "abcdef"
     */
    string s10 { s9.begin(), s9.end() };

    cout << "s10=" << s10 << endl;
}

/**
 * 迭代器 iterator
 *
 * 迭代器可以理解为“广义的指针”。
 *
 * 它不一定是真正的指针，
 * 但是很多使用方式和指针类似。
 *
 * 常见操作：
 *
 * 1. 解引用
 *    *it
 *    获取迭代器当前指向的元素。
 *
 * 2. 自增
 *    ++it
 *    让迭代器向后移动一个位置。
 *
 * 3. 自减
 *    --it
 *    让迭代器向前移动一个位置。
 *
 *
 * string 中常见迭代器：
 *
 * 1. begin()
 *    返回首迭代器，
 *    指向第一个字符。
 *
 * 2. end()
 *    返回尾迭代器，
 *    指向最后一个字符的下一个位置。
 *
 * 注意：
 * end() 指向的位置不是有效字符，
 * 不能直接解引用。
 */

void test2()
{
    string str { "abcdef" };

    /*
     * 获取首迭代器。
     *
     * begin() 返回指向第一个字符的位置。
     *
     * 这里 str 的内容是：
     * "abcdef"
     *
     * str.begin() 指向字符 'a'。
     */
    /* auto itBegin = str.begin(); */

    /*
     * string::iterator 是 string 的迭代器类型。
     *
     * itBegin 当前指向 str 中的第一个字符。
     */
    string::iterator itBegin = str.begin();

    /*
     * *itBegin 表示解引用迭代器，
     * 获取当前迭代器指向的字符。
     *
     * 当前 itBegin 指向 'a'，
     * 所以输出：
     * a
     */
    cout << *itBegin << endl;

    /*
     * ++itBegin 表示迭代器向后移动一个位置。
     *
     * 原来指向 'a'，
     * 移动后指向 'b'。
     */
    ++itBegin;

    /*
     * 此时 itBegin 指向字符 'b'。
     */
    cout << *itBegin << endl;

    /*
     * 获取尾迭代器。
     *
     * end() 返回的迭代器指向最后一个元素的下一个位置。
     *
     * 对于字符串 "abcdef" 来说：
     *
     * begin() 指向 'a'
     * end()   指向 'f' 后面的那个位置
     *
     * 注意：
     * end() 本身不指向有效字符。
     */
    auto itEnd = str.end();

    /*
     * 不能直接解引用尾迭代器。
     *
     * 因为 itEnd 指向的是最后一个元素的下一个位置，
     * 不是有效字符。
     *
     * 如果想访问最后一个字符，
     * 可以先执行：
     *
     * --itEnd;
     * cout << *itEnd << endl;
     */
    /* cout << *itEnd << endl; */
}

/**
 * string 中常见的操作
 *
 * 1. 元素访问
 *    at(index)
 *    operator[]
 *    front()
 *    back()
 *    c_str()
 *
 * 2. 容量相关
 *    size()
 *    length()
 *    empty()
 */

void test3()
{
    string str { "hello" };

    /*
     * at(index)
     *
     * 根据下标访问字符串中的字符。
     *
     * 下标从 0 开始。
     *
     * str 的内容是：
     * h  e  l  l  o
     * 0  1  2  3  4
     *
     * str.at(0) 访问第 0 个字符，
     * 结果是 'h'。
     *
     * 特点：
     * at 会进行越界检查。
     * 如果下标越界，会抛出异常。
     */
    cout << str.at(0) << endl;

    /*
     * operator[]
     *
     * 下标访问运算符函数。
     *
     * str[1] 表示访问下标为 1 的字符，
     * 结果是 'e'。
     *
     * 注意：
     * operator[] 通常不进行越界检查。
     * 如果下标越界，可能导致未定义行为。
     */
    cout << str[1] << endl;

    /*
     * front()
     *
     * 访问字符串的首字符。
     *
     * str.front() 等价于访问 str[0]。
     *
     * 当前结果是 'h'。
     */
    cout << str.front() << endl;

    /*
     * back()
     *
     * 访问字符串的尾字符。
     *
     * 当前 str 的最后一个字符是 'o'。
     */
    cout << str.back() << endl;

    /*
     * c_str()
     *
     * 返回 string 内部字符数据对应的 C 风格字符串。
     *
     * 返回值类型：
     * const char *
     *
     * 作用：
     * 当某些函数需要 C 风格字符串参数时，
     * 可以使用 str.c_str()。
     *
     * 例如：
     * const char * p = str.c_str();
     *
     * 注意：
     * 返回的是 const char *，
     * 不应该通过 p 修改字符串内容。
     */
    const char * p = str.c_str();
    cout << p << endl;

    cout << "-------" << endl;

    /*
     * size()
     *
     * 返回字符串中字符的个数。
     *
     * 对于 "hello" 来说，
     * size() 返回 5。
     */
    cout << str.size() << endl;

    /*
     * length()
     *
     * 返回字符串长度。
     *
     * 对 string 来说，
     * length() 和 size() 基本等价。
     *
     * 对于 "hello" 来说，
     * length() 也返回 5。
     */
    cout << str.length() << endl;

    /*
     * empty()
     *
     * 判断字符串是否为空。
     *
     * 返回值：
     * true   表示字符串为空
     * false  表示字符串不为空
     *
     * cout 输出 bool 值时：
     * false 通常输出 0
     * true  通常输出 1
     *
     * 当前 str 是 "hello"，
     * 所以 empty() 返回 false，
     * 输出 0。
     */
    cout << str.empty() << endl;
}

int main(int argc, char * argv[])
{
    /*
     * 当前只调用 test3。
     *
     * 可以取消下面对应函数的注释，
     * 分别测试：
     *
     * test1：string 的构造方式
     * test2：string 迭代器
     * test3：string 常见操作
     */
    test1();
    /* test2(); */
    /* test3(); */

    return 0;
}


/*
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void test1()
{
    string s1;
    cout << "s1=" << s1 << endl;

    string s2{"hello"};
    cout << "s2=" << s2 << endl;

    string s3{"hello", 3};
    cout << "s3=" << s3 << endl;

    string s4{s2};
    cout << "s4=" << s4 << endl;

    string s5{s2, 1, 3};
    cout << "s5=" << s5 << endl;

    string s6{98, 'a'};
    cout << "s6=" << s6 << endl;

    string s8{'a', 'b', 'c'};
    cout << "s8=" << s8 << endl;

    string s7(97, 'a');
    cout << "s7=" << s7 << endl;

    string s9{"abcdef"};
    string s10{s9.begin(), s9.end()};

    cout << "s10=" << s10 << endl;
}

void test2()
{
    string str{"abcdef"};

    // auto itBegin = str.begin();

    string::iterator itBegin = str.begin();

    cout << *itBegin << endl;

    ++itBegin;

    cout << *itBegin << endl;

    auto itEnd = str.end();

    // cout << *itEnd << endl;
}

void test3()
{
    string str{"hello"};

    cout << str.at(0) << endl;
    cout << str[1] << endl;

    cout << str.front() << endl;
    cout << str.back() << endl;

    const char * p = str.c_str();
    cout << p << endl;

    cout << "-------" << endl;

    cout << str.size() << endl;
    cout << str.length() << endl;
    cout << str.empty() << endl;
}

int main(int argc, char * argv[])
{
    // test1();
    // test2();
    test3();

    return 0;
}
*/