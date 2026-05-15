#include <iostream>

using std::cout;
using std::endl;

/**
 * const 成员函数
 *
 * const 成员函数是在成员函数的形参列表后面加 const。
 *
 * 语法：
 * 返回值类型 函数名(形参列表) const
 * {
 *     函数体
 * }
 *
 *
 * const 成员函数的特点：
 * 1. const 和成员函数结合之后，
 *    该成员函数具有“只读属性”。
 *
 * 2. const 成员函数不能修改对象的状态。
 *    也就是说，不能修改对象中普通数据成员的值。
 *
 * 3. const 成员函数中可以读取成员变量，
 *    但是不能修改成员变量。
 *
 * 4. const 成员函数中 this 指针的类型发生了变化。
 *
 *
 * 普通成员函数中的 this：
 * Point * const this
 *
 * 含义：
 * this 本身不能改变指向，
 * 但是可以通过 this 修改对象内容。
 *
 *
 * const 成员函数中的 this：
 * const Point * const this
 *
 * 含义：
 * this 本身不能改变指向，
 * 也不能通过 this 修改对象内容。
 *
 *
 * const 成员函数的使用场景：
 * 当一个成员函数只负责访问数据，
 * 不希望它修改对象状态时，
 * 就可以将它定义成 const 成员函数。
 *
 * 常见例子：
 * getX()
 * getY()
 * show()
 * print()
 */

class A
{
public:
    /*
     * 普通成员变量
     *
     * m_num 属于 A 类对象。
     * 每个 A 类对象都有自己独立的一份 m_num。
     */
    int m_num = 1;
};

class Point
{
public:
    /*
     * 构造函数
     *
     * 用来创建 Point 对象时进行初始化。
     *
     * 这里接收两个参数 x 和 y，
     * 但是当前函数体中没有真正使用这两个参数。
     *
     * 更完整的写法通常是使用初始化列表：
     *
     * Point(int x, int y)
     * : m_x(x)
     * , m_y(y)
     * {}
     */
    Point(int x, int y)
    {}

    /**
     * const 成员函数
     *
     * 在成员函数形参列表后面加 const，
     * 表示该成员函数不能修改当前对象的成员变量。
     *
     * 注意：
     * const 修饰的是 this 指针指向的对象，
     * 不是函数返回值。
     */
    void show() const
    {
        /*
         * const 成员函数中的 this 指针是双重 const 限定的指针。
         *
         * 普通成员函数中的 this：
         * Point * const this
         *
         * const 成员函数中的 this：
         * const Point * const this
         *
         * 第一个 const：
         * 表示不能通过 this 修改对象内容。
         *
         * 第二个 const：
         * 表示 this 本身不能改变指向。
         */
        this;

        /*
         * m_x 是当前对象的普通成员变量。
         *
         * 在 const 成员函数中，
         * 不能修改普通成员变量的值。
         */
        /* this->m_x = 1; */

        /*
         * 读取成员变量是允许的。
         *
         * const 成员函数只是限制“修改”，
         * 并不限制“访问”。
         */
        m_y;

        /*
         * 下面两行本质上也是在修改当前对象的数据成员。
         *
         * 在 const 成员函数中不允许这样做。
         */
        /* m_x = 1; */
        /* m_y = 2; */

        /*
         * m_a 是 Point 类中的成员对象。
         *
         * 在 const 成员函数中，
         * 可以读取成员对象中的数据。
         */
        m_a.m_num;

        /*
         * 虽然 m_num 是 A 类中的普通成员变量，
         * 但是 m_a 是当前 Point 对象的一部分。
         *
         * 修改 m_a.m_num，
         * 就等价于修改当前 Point 对象的状态。
         *
         * 所以在 const 成员函数中不允许。
         */
        /* m_a.m_num = 10; */
    }

    /*
     * 普通成员函数
     *
     * 普通成员函数中的 this 指针类型是：
     * Point * const this
     *
     * this 本身不能改变指向，
     * 但是可以通过 this 修改对象内容。
     */
    void show()
    {}

    /*
     * const 成员函数和普通成员函数可以构成重载。
     *
     * 原因：
     * 两个函数中隐含的 this 指针类型不同。
     *
     * void show();
     * 隐含的 this 类型：
     * Point * const this
     *
     * void show() const;
     * 隐含的 this 类型：
     * const Point * const this
     *
     *
     * 调用规则：
     * 1. 普通对象优先调用普通成员函数。
     * 2. const 对象只能调用 const 成员函数。
     */

    /**
     * getX 函数
     *
     * 该函数只负责获取 m_x 的值，
     * 不需要修改对象状态。
     *
     * 所以可以将它定义为 const 成员函数。
     */
    int getX() const
    {
        /*
         * getX 是 const 成员函数，
         * 不能修改成员变量。
         */
        /* m_x = 10; */

        /*
         * 读取 m_x 的值并返回。
         *
         * 读取操作不会改变对象状态，
         * 所以在 const 成员函数中是允许的。
         */
        return m_x;
    }

private:
    /*
     * 普通成员变量
     *
     * m_x 和 m_y 表示 Point 对象的坐标信息。
     *
     * 在普通成员函数中可以修改它们，
     * 但是在 const 成员函数中不能修改。
     */
    int m_x;
    int m_y;

    /*
     * 成员对象
     *
     * m_a 是 A 类型的对象，
     * 它也是 Point 对象状态的一部分。
     *
     * 因此在 const 成员函数中，
     * 不能修改 m_a 内部的数据成员。
     */
    A m_a;
};

void test1()
{
    /*
     * 创建普通 Point 对象。
     *
     * pt 是普通对象，
     * 既可以调用普通成员函数，
     * 也可以调用 const 成员函数。
     */
    Point pt{1, 2};

    /*
     * getX 是 const 成员函数。
     *
     * 普通对象可以调用 const 成员函数。
     * 因为 const 成员函数只是承诺不修改对象，
     * 对普通对象来说也是安全的。
     */
    int x = pt.getX();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}
