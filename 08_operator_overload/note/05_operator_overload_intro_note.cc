#include <iostream>

using std::cout;
using std::endl;

/**
 * 运算符重载：
 *
 * C++ 中大多数运算符都可以重载，
 * 但是有些运算符不能重载。
 *
 * 例如：
 * 1. 成员访问运算符 .
 * 2. 成员指针访问运算符 .*
 * 3. 作用域限定符 ::
 * 4. 条件运算符 ?:
 * 5. sizeof 运算符
 *
 * 运算符重载的本质：
 * 本质上仍然是函数调用。
 *
 * 例如：
 * pt2 = pt1;
 *
 * 表面上看是赋值运算，
 * 实际上会调用：
 * pt2.operator=(pt1);
 *
 * 函数调用的形式：
 * 1. 普通函数调用
 *    test1();
 *
 * 2. 成员函数调用
 *    对象.func();
 *    指针->func();
 *
 * 只有自定义类型才需要考虑运算符重载。
 *
 * 内置类型本身已经支持常见运算符，
 * 例如 int、double 等类型可以直接使用 +、-、=。
 *
 * 但是自定义类型，例如 Point，
 * 编译器并不知道两个 Point 对象应该如何相加、如何输出，
 * 所以需要程序员自己定义对应的运算符重载函数。
 *
 * 重载一个运算符时需要考虑：
 * 1. 采用什么形式
 *    普通函数形式 or 成员函数形式
 *
 * 2. 函数的返回值
 *    例如赋值运算符通常返回当前对象本身的引用
 *
 * 3. 函数的参数
 *    例如赋值运算符需要接收右操作数
 *
 * 4. 函数体的代码逻辑
 *    运算符重载之后的行为，
 *    应该尽量和这个运算符本身的语义保持一致。
 */

class Point
{
public:
    /**
     * 构造函数
     *
     * 用两个 int 类型的数据，
     * 初始化 Point 对象中的横坐标和纵坐标。
     */
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {}

    /**
     * 赋值运算符重载函数
     *
     * operator= 是赋值运算符函数的函数名。
     *
     * 当执行：
     * pt2 = pt1;
     *
     * 本质上会调用：
     * pt2.operator=(pt1);
     *
     * 左操作数 pt2 是调用该成员函数的对象，
     * 右操作数 pt1 会作为参数 rhs 传入。
     */
    Point & operator=(const Point & rhs)
    {
        /**
         * this 指针指向当前对象。
         *
         * 在表达式：
         * pt2 = pt1;
         *
         * 中，this 指向 pt2，
         * rhs 表示 pt1。
         *
         * 所以下面的代码表示：
         * 把 rhs 对象中的 m_x 和 m_y，
         * 赋值给当前对象的 m_x 和 m_y。
         */
        this->m_x = rhs.m_x;
        this->m_y = rhs.m_y;

        /**
         * 返回当前对象本身。
         *
         * *this 表示当前对象。
         *
         * 赋值运算符返回 Point &，
         * 是为了支持连续赋值：
         *
         * pt3 = pt2 = pt1;
         *
         * pt2 = pt1 执行完之后会返回 pt2，
         * 然后再把 pt2 赋值给 pt3。
         */
        return *this;
    }

private:
    // private 成员变量，表示 Point 对象的横坐标
    int m_x;

    // private 成员变量，表示 Point 对象的纵坐标
    int m_y;
};


void test1()
{
    int a = 1;
    int b = 1;

    /**
     * int 是内置类型。
     *
     * 内置类型本身支持 + 运算符，
     * 所以 a + b 可以直接使用。
     */
    a + b;

    /**
     * Point 是自定义类型。
     *
     * 编译器不知道两个 Point 对象应该如何相加，
     * 所以如果想写 pt1 + pt2，
     * 就需要自己重载 operator+。
     */
    Point pt1{1,2};
    Point pt2{3,4};

    /**
     * 当前 Point 类中没有重载 operator+，
     * 所以下面这行代码如果打开，
     * 会编译报错。
     */
    /* pt1 + pt2; // operator+ */

    /**
     * 简写形式：
     *
     * 看起来是在使用 = 运算符，
     * 实际上会调用赋值运算符重载函数 operator=。
     */
    pt2 = pt1; // 调用运算符赋值函数 operator=

    /**
     * 本质：
     *
     * 运算符重载的本质是函数调用。
     *
     * pt2 = pt1;
     *
     * 等价于：
     *
     * pt2.operator=(pt1);
     */
    pt2.operator=(pt1);

    /**
     * cout 可以直接输出 int 类型，
     * 因为标准库已经支持 int 类型的输出。
     */
    cout << a << endl;

    /**
     * Point 是自定义类型。
     *
     * 如果没有重载输出运算符 operator<<，
     * cout 不知道应该如何输出 Point 对象。
     *
     * 所以下面这行代码如果打开，
     * 会编译报错。
     */
    /* cout << pt1 << endl; // error: 不能直接输出一个对象 */
}

int main(int argc, char *argv[])
{
    test1();

    return 0;
}