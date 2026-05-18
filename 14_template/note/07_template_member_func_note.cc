#include <iostream>

using std::cout;
using std::endl;

/**
 * 把模板作用于成员函数中：
 *
 * 模板不仅可以作用在普通函数上，
 * 也可以作用在类的成员函数上。
 *
 *
 * 普通成员函数：
 * 参数类型通常是固定的。
 *
 * 例如：
 * void print(int t);
 *
 * 这个函数主要用于处理 int 类型。
 *
 *
 * 成员函数模板：
 * 可以把成员函数的参数类型写成模板参数。
 *
 * 例如：
 * template <typename T>
 * void print(T t);
 *
 * 这里的 T 是类型参数，
 * 具体类型由调用成员函数时传入的实参决定。
 *
 *
 * 注意：
 * 成员函数模板不是说整个类都是模板。
 *
 * 当前代码中：
 * class Point
 *
 * Point 是一个普通类，
 * 不是类模板。
 *
 * 只是 Point 类里面的某些成员函数是模板函数。
 *
 *
 * 成员函数模板也可以：
 * 1. 在类内直接实现
 * 2. 在类内声明，类外实现
 *
 * 如果类外实现成员函数模板，
 * 需要在类外实现时重新写一遍：
 *
 * template <typename T>
 */

class Point
{
public:
    /**
     * 构造函数。
     *
     * 参数：
     * int x
     * int y
     *
     * 作用：
     * 创建 Point 对象时，
     * 使用 x 和 y 初始化数据成员 m_x 和 m_y。
     */
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {}

    /**
     * 成员函数模板。
     *
     * template <typename T>
     * 表示 print 是一个函数模板，
     * T 是类型参数。
     *
     * void print(T t)
     * 表示：
     * print 函数的参数类型暂时不固定，
     * 由调用时传入的实参决定。
     *
     * 例如：
     * pt.print(100);
     *
     * 100 是 int 类型，
     * 所以编译器推导：
     * T = int
     *
     * 相当于生成：
     * void print(int t);
     *
     *
     * pt.print(3.14);
     *
     * 3.14 是 double 类型，
     * 所以编译器推导：
     * T = double
     *
     * 相当于生成：
     * void print(double t);
     */
    template<typename T>
    void print(T t)
    {
        /**
         * 输出 t。
         *
         * 要求：
         * T 类型必须支持 cout << t。
         *
         * int、double、const char *、std::string 等常见类型
         * 通常都可以直接输出。
         *
         * 如果 T 是自定义类型，
         * 但是没有重载 operator<<，
         * 这里就会编译报错。
         */
        cout << t << endl;
    }

    /**
     * 成员函数模板的声明。
     *
     * 这里只声明 print2，
     * 不在类内写具体实现。
     *
     * 注意：
     * 因为 print2 是成员函数模板，
     * 所以声明前面也要写：
     * template <typename T>
     */
    template<typename T>
    void print2(T t);

private:
    /**
     * Point 类的数据成员。
     *
     * 当前类本身不是模板类，
     * 所以 m_x 和 m_y 的类型是固定的 int。
     */
    int m_x;
    int m_y;
};


/**
 * 类外实现成员函数模板。
 *
 * 注意：
 * 虽然在类内声明时已经写过 template <typename T>，
 * 但在类外实现时仍然需要重新写一遍。
 *
 * 原因：
 * template <typename T> 的作用范围只覆盖紧跟着的声明或定义。
 *
 *
 * Point::print2
 *
 * 表示：
 * 这是 Point 类作用域中的 print2 成员函数。
 *
 * 因为 Point 本身不是类模板，
 * 所以这里只需要写：
 * void Point::print2(T t)
 *
 * 不需要写成 Point<T>::print2。
 */
template <typename T>
void Point::print2(T t)
{
    /**
     * 输出参数 t。
     *
     * 和 print 一样，
     * T 类型需要支持 cout << t。
     */
    cout << t << endl;

    cout << "print2" << endl;
}

void test1()
{
    /**
     * 创建 Point 对象。
     *
     * 使用大括号初始化：
     * Point pt { 1, 2 };
     *
     * 会调用构造函数：
     * Point(int x, int y)
     *
     * 其中：
     * x = 1
     * y = 2
     */
    Point pt { 1, 2 };

    /**
     * 调用成员函数模板 print。
     *
     * pt.print(100);
     *
     * 编译器根据实参 100 推导：
     * T = int
     *
     * 相当于调用：
     * print<int>(100);
     */
    pt.print(100);

    /**
     * 编译器根据实参 3.14 推导：
     * T = double
     *
     * 相当于调用：
     * print<double>(3.14);
     */
    pt.print(3.14);

    /**
     * 调用类外实现的成员函数模板 print2。
     *
     * pt.print2(100);
     *
     * 编译器根据实参 100 推导：
     * T = int
     *
     * 相当于调用：
     * pt.print2<int>(100);
     */
    pt.print2(100);

    /**
     * 显式指定模板参数。
     *
     * pt.print2<std::string>("abc");
     *
     * 这里明确指定：
     * T = std::string
     *
     * 字符串字面值 "abc" 原本是 const char[4]，
     * 调用时可以转换成 std::string。
     *
     * 所以这里相当于：
     * void print2(std::string t);
     *
     * 注意：
     * 当前代码没有写：
     * #include <string>
     *
     * 有些编译环境可能因为其他头文件间接包含了 string 而能通过，
     * 但更规范的写法是补充：
     *
     * #include <string>
     */
    pt.print2<std::string>("abc");
}

int main(int argc, char *argv[])
{
    // 测试普通类中的成员函数模板
    test1();

    return 0;
}