#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

/**
 * 模板特化：
 * 针对某些特殊类型，通用函数模板的处理方式可能不合适，
 * 此时可以为该类型提供一个专门的实现。
 *
 * 语法：
 * template <>
 * 返回类型 函数名<特殊类型>(参数列表)
 * {
 *     // 针对特殊类型的专门处理
 * }
 *
 * 注意：
 * 模板特化不是“通用模板不能用时才使用”，
 * 而是当模板参数能够精确匹配特化版本时，
 * 编译器会优先选择特化版本。
 */


// 通用函数模板
template <typename T>
T add(T t1, T t2)
{
    return t1 + t2;
}
// 如果 T 是自定义类型，并且希望使用 add(t1, t2)，
// 该类型通常需要支持 operator+ 运算符重载。


// 函数模板特化：专门处理 const char * 类型
template <>
const char * add<const char *>(const char *c1, const char *c2)
{
    char *temp = new char[std::strlen(c1) + std::strlen(c2) + 1];

    std::strcpy(temp, c1);
    std::strcat(temp, c2);

    return temp;
}


// 这里只是前向声明。
// 如果真正使用 add<Complex>(cx1, cx2)，
// Complex 需要是完整类型，并且通常需要重载 operator+。
class Complex;


void test1()
{
    cout << add<int>(1, 2) << endl;
    cout << add<double>(1.1, 2.2) << endl;

    // 字符串字面值会退化为 const char *
    // 因此会匹配 add<const char *>(const char *, const char *) 这个特化版本
    const char *ret = add("ab", "cd");
    cout << ret << endl;

    // add<const char *> 内部使用 new[] 申请了空间，
    // 使用完后需要手动 delete[]，否则会造成内存泄漏。
    delete[] ret;

    /* add<Complex>(cx1, cx2); */
}


int main(int argc, char *argv[])
{
    test1();

    return 0;
}