#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

/**
 * 模板的特化 specialisation：
 *
 * 函数模板通常用于处理一类通用逻辑。
 *
 * 例如：
 * template <typename T>
 * T add(T t1, T t2)
 * {
 *     return t1 + t2;
 * }
 *
 * 这个模板要求：
 * T 类型的对象必须支持 operator+。
 *
 * 对于 int、double、string 等类型，
 * t1 + t2 可以正常工作。
 *
 *
 * 但是有些特殊类型，
 * 通用模板不能直接正确处理。
 *
 * 例如：
 * const char *
 *
 * C 风格字符串本质上是字符指针。
 * 两个 const char * 不能直接用 + 拼接字符串。
 *
 * 如果写：
 * c1 + c2
 *
 * 这不是字符串拼接，
 * 而且两个指针也不能直接相加。
 *
 * 所以对于 const char * 这种特殊类型，
 * 需要单独写一份特殊处理逻辑。
 *
 *
 * 模板特化：
 * 针对某一种特殊类型，
 * 为函数模板提供一个专门版本。
 *
 * 可以理解成：
 * 通用模板处理大多数类型；
 * 特化模板处理某些特殊类型。
 *
 *
 * 函数模板特化的语法：
 *
 * template <>
 * 返回值类型 函数名<特殊类型>(参数列表)
 * {
 *     // 针对特殊类型的专门处理
 * }
 *
 *
 * 注意：
 * 只有在通用模板不适合某种类型时，
 * 才需要使用模板特化。
 *
 * 如果通用模板已经能够正确处理，
 * 一般不需要特化。
 */


// 普通的通用函数模板
template <typename T>
T add(T t1, T t2)
{
    /**
     * 这里直接使用 t1 + t2。
     *
     * 所以要求：
     * T 类型必须支持 operator+。
     *
     * 例如：
     * int + int
     * double + double
     * string + string
     *
     * 这些都可以正常工作。
     *
     * 如果 T 是自定义类型，
     * 通常需要自己重载 operator+，
     * 否则这里会编译报错。
     */
    return t1 + t2;
}
// 自定义类型在需要 operator+ 重载


/**
 * 函数模板的全特化。
 *
 * template <>
 * 表示这是一个模板特化版本，
 * 尖括号中没有模板参数，
 * 因为具体类型已经被确定下来了。
 *
 *
 * const char * add<const char *>(const char *c1, const char *c2)
 *
 * 表示：
 * 专门针对 T = const char * 的情况，
 * 提供一个 add 函数的特殊实现。
 *
 *
 * 为什么需要特化 const char *？
 *
 * 因为 const char * 是 C 风格字符串。
 * 它本质上是指针，
 * 不是 C++ 的 string 对象。
 *
 * 通用模板中的：
 * return t1 + t2;
 *
 * 不能用于拼接两个 const char * 字符串。
 *
 * 所以这里使用 strlen、strcpy、strcat
 * 手动完成字符串拼接。
 */
template <>
const char * add<const char *>(const char *c1, const char *c2)
{
    /**
     * strlen(c1)：
     * 计算 c1 指向的字符串长度，
     * 不包含字符串结尾的 '\0'。
     *
     * strlen(c2)：
     * 计算 c2 指向的字符串长度。
     *
     * + 1：
     * 为字符串结尾的 '\0' 预留空间。
     *
     * new char[...]：
     * 在堆区申请一段字符数组，
     * 用来存放拼接后的新字符串。
     */
    char * temp = new char[strlen(c1) + strlen(c2) + 1];

    /**
     * strcpy(temp, c1)：
     * 把 c1 指向的字符串复制到 temp 中。
     *
     * 执行后：
     * temp 中先保存了 c1 的内容。
     */
    strcpy(temp, c1);

    /**
     * strcat(temp, c2)：
     * 把 c2 指向的字符串追加到 temp 后面。
     *
     * 执行后：
     * temp 中保存的是 c1 和 c2 拼接后的结果。
     */
    strcat(temp, c2);

    /**
     * 返回拼接后的字符串。
     *
     * 注意：
     * temp 是通过 new[] 在堆区申请的内存。
     *
     * 调用者使用完返回值后，
     * 理论上应该使用 delete[] 释放这块内存，
     * 否则会造成内存泄漏。
     *
     * 例如：
     * const char *p = add("ab", "cd");
     * cout << p << endl;
     * delete[] p;
     *
     * 当前代码中直接 cout << add("ab", "cd")，
     * 没有保存返回的指针，
     * 因此无法 delete[]，
     * 会产生内存泄漏。
     *
     * 更推荐的现代 C++ 写法：
     * 使用 std::string 来处理字符串拼接。
     */
    return temp;
}


// 类的前向声明
// 表示 Complex 是一个类，后面可能会定义它
class Complex;

void test1()
{
    /**
     * 显式指定模板参数为 int。
     *
     * T = int
     *
     * 调用通用模板：
     * int add(int, int)
     *
     * 执行整数加法。
     */
    cout << add<int>(1, 2) << endl;

    /**
     * 显式指定模板参数为 double。
     *
     * T = double
     *
     * 调用通用模板：
     * double add(double, double)
     *
     * 执行浮点数加法。
     */
    cout << add<double>(1.1, 2.2) << endl;

    /**
     * add("ab", "cd")
     *
     * "ab" 和 "cd" 是字符串字面值。
     *
     * 在函数调用时，
     * 字符串字面值通常会退化为 const char *。
     *
     * 因此编译器推导：
     * T = const char *
     *
     * 这时不会使用通用模板，
     * 而是使用我们专门写的特化版本：
     *
     * const char * add<const char *>(const char *, const char *)
     *
     * 所以这里可以完成 C 风格字符串拼接。
     *
     * 输出结果：
     * abcd
     *
     * 注意：
     * 当前写法存在内存泄漏问题，
     * 因为 add 内部 new[] 出来的内存没有被释放。
     */
    cout << add("ab", "cd") << endl;

    /**
     * 如果 T 是自定义类型 Complex，
     * 通用模板中会执行：
     * cx1 + cx2
     *
     * 所以 Complex 必须支持 operator+。
     *
     * 如果 Complex 没有重载 operator+，
     * 那么下面这种调用会编译失败。
     *
     * 解决方式：
     * 1. 给 Complex 重载 operator+
     * 2. 或者针对 Complex 写 add 的模板特化版本
     */
    /* add<Complex>(cx1, cx2); */
}

int main(int argc, char *argv[])
{
    // 测试函数模板的通用版本和特化版本
    test1();

    return 0;
}