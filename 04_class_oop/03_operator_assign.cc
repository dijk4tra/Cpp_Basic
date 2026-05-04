#include <iostream>

using std::cout;
using std::endl;

/**
 * 对象的赋值操作：赋值运算符函数
 *
 * 在 C++ 中，对象之间常见的复制相关操作主要有两类：
 *
 * 1. 拷贝构造
 *    用一个已经存在的对象，创建一个新的对象。
 *
 *    例如：
 *    Point pt1{1, 2};
 *    Point pt2 = pt1;
 *    Point pt3{pt1};
 *
 *    pt2 和 pt3 是新创建出来的对象，
 *    所以会调用拷贝构造函数。
 *
 * 2. 赋值操作
 *    两个对象都已经存在，
 *    然后把一个对象的内容赋值给另一个对象。
 *
 *    例如：
 *    Point pt1{1, 2};
 *    Point pt2{3, 4};
 *    pt2 = pt1;
 *
 *    pt1 和 pt2 在赋值之前都已经存在，
 *    所以这里不是拷贝构造，
 *    而是调用赋值运算符函数 operator=。
 *
 *
 * 赋值运算符函数 assignment operator：
 * 可以理解成：
 * 当对象之间使用 = 进行赋值时，
 * 自动调用的一个特殊成员函数。
 *
 * 语法：
 * 类名 & operator=(const 类名 & rhs)
 * {
 *     函数体
 *     return *this;
 * }
 *
 * 例如：
 * Point & operator=(const Point & rhs)
 * {
 *     ...
 *     return *this;
 * }
 *
 * rhs 是 right hand side 的缩写，
 * 表示赋值号右边的对象。
 *
 * 例如：
 * pt2 = pt1;
 * 其中：
 * pt2 是赋值号左边的对象，也是当前对象
 * pt1 是赋值号右边的对象，也就是 rhs
 *
 *
 * 赋值运算符函数的本质：
 * pt2 = pt1;
 * 本质上可以理解为：
 * pt2.operator=(pt1);
 * 所以 operator= 其实就是一个成员函数。
 *
 *
 * 形式上的几个问题：
 *
 * 1. 为什么返回值要设置为引用？
 *
 *    为了支持连续赋值。
 * 
 *    例如：
 *    pt3 = pt2 = pt1;
 *    赋值运算符是从右往左结合的，
 *    所以上面的代码等价于：
 *    pt3 = (pt2 = pt1);
 *
 *    pt2 = pt1 执行完成后，
 *    需要返回 pt2 本身，
 *    然后 pt3 才能继续接收这个返回结果。
 *
 *    如果 operator= 返回 void，
 *    那么 pt2 = pt1 没有返回值，
 *    就不能继续进行 pt3 = ... 的操作。
 *
 *
 * 2. 为什么返回类名 &，而不是类名？
 *
 *    如果返回 Point：
 *    Point operator=(const Point & rhs)
 *    那么 return *this 时，
 *    会用当前对象再拷贝构造出一个临时对象作为返回值，
 *    可能产生额外的拷贝。
 *
 *    如果返回 Point &：
 *    Point & operator=(const Point & rhs)
 *    就是直接返回当前对象本身，
 *    不会产生额外对象，
 *    效率更高，也更符合内置类型赋值的行为。
 *
 *
 * 3. 为什么参数要加 const？
 *
 *    因为赋值操作只需要读取右边对象的数据，
 *    不应该修改右边对象。
 *
 *    例如：
 *    pt2 = pt1;
 *    赋值之后：
 *    pt2 的值变成和 pt1 一样，
 *    但是 pt1 自己不应该发生变化。
 *
 *    const Point & rhs 表示：
 *    rhs 是只读的，
 *    不能通过 rhs 修改右边对象。
 *
 *
 * 4. 为什么参数要加 &？
 *
 *    为了避免传参时发生不必要的对象拷贝。
 *
 *    如果写成：
 *    Point & operator=(const Point rhs)
 *    那么调用 operator= 之前，
 *    还需要先把右边对象拷贝一份给形参 rhs，
 *    这样效率较低。
 *
 *    写成：
 *    Point & operator=(const Point & rhs)
 *    就可以直接引用右边对象，
 *    避免复制。
 *
 *
 * 5. 为什么要 return *this？
 *
 *    this 是一个指针，
 *    指向当前调用 operator= 的对象。
 *
 *    在：
 *    pt2 = pt1;
 *    中，当前对象是 pt2，
 *    所以 this 指向 pt2。
 *
 *    *this 表示当前对象本身，
 *    也就是 pt2。
 *    return *this;
 *    就是把赋值后的当前对象返回出去，
 *    用来支持连续赋值。
 */

class Point
{
public:
    // 有参构造函数
    //
    // 创建 Point 对象时调用：
    // Point pt{1, 2};
    //
    // x 用来初始化 m_x
    // y 用来初始化 m_y
    Point(int x ,int y)
    : m_x(x),
      m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    /**
     * 拷贝构造函数 copy constructor
     *
     * 作用：
     * 用一个已经存在的 Point 对象，
     * 初始化一个新的 Point 对象。
     *
     * 例如：
     * Point pt1{1, 2};
     * Point pt2{pt1};
     *
     * 此时 pt2 是新对象，
     * 所以调用拷贝构造函数。
     *
     * 参数：
     * const Point & rhs
     *
     * rhs 表示被拷贝的对象。
     */
    Point(const Point & rhs)
    : m_x(rhs.m_x),
      m_y(rhs.m_y)
    {
        cout << "Point(const Point&)" << endl;
    }

    /**
     * 赋值运算符函数 operator=
     *
     * 当两个已经存在的对象之间进行赋值时，
     * 会调用这个函数。
     *
     * 例如：
     * Point pt1{1, 2};
     * Point pt2{3, 4};
     * pt2 = pt1;
     *
     * 这里 pt1 和 pt2 都已经存在，
     * 所以不会调用拷贝构造函数，
     * 而是调用赋值运算符函数。
     *
     * pt2 = pt1;
     *
     * 本质上可以理解为：
     * pt2.operator=(pt1);
     *
     * 此时：
     * this 指向 pt2
     * rhs 引用 pt1
     *
     * const Point & rhs = pt1
     *
     * 调用这个函数的对象是 pt2，
     * 所以 pt2 就是当前对象。
     */
    Point & operator=(const Point & rhs)
    /* void operator=(const Point & rhs) */
    {
        cout << "operator=" << endl;

        /*
         * this 是当前对象的地址。
         *
         * 在：
         * pt2 = pt1;
         *
         * 中，当前对象是 pt2，
         * 所以：
         * this 指向 pt2
         * rhs 引用 pt1
         *
         * this->m_x = rhs.m_x;
         *
         * 可以理解为：
         * pt2.m_x = pt1.m_x;
         *
         * this->m_y = rhs.m_y;
         *
         * 可以理解为：
         * pt2.m_y = pt1.m_y;
         */
        this->m_x = rhs.m_x;
        this->m_y = rhs.m_y;

        /*
         * return *this;
         *
         * this 是指针，表示当前对象的地址。
         * *this 表示当前对象本身。
         *
         * 在：
         * pt2 = pt1;
         *
         * 中：
         * this 指向 pt2，
         * *this 就是 pt2。
         *
         * 所以 return *this;
         * 表示返回赋值后的 pt2。
         *
         * 这样可以支持连续赋值：
         *
         * pt3 = pt2 = pt1;
         *
         * 等价于：
         * pt3 = (pt2 = pt1);
         *
         * pt2 = pt1 执行结束后，
         * 返回 pt2 本身，
         * 然后 pt3 再接着赋值为 pt2。
         */
        return *this;
    }

    // 普通成员函数
    // 打印当前对象中的 m_x 和 m_y
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

private:
    int m_x;
    int m_y;
};

void test1()
{
    // 内置类型
    int a = 1;
    int b = 2;
    int c = 3;

    /**
     * 内置类型的连续赋值
     *
     * b = a = c;
     *
     * 赋值运算符 = 是从右往左结合的，
     * 所以这句代码等价于：
     *
     * b = (a = c);
     *
     * 执行过程：
     *
     * 1. 先执行 a = c
     *    c 的值是 3，
     *    所以 a 的值变成 3。
     *
     * 2. 表达式 a = c 的结果是 a 本身
     *
     * 3. 再执行 b = a
     *    此时 a 的值已经是 3，
     *    所以 b 的值也变成 3。
     */
    b = a = c;

    // 推广到自定义类型
    //
    // 创建三个 Point 对象
    //
    // pt1 的数据是 1, 2
    // pt2 的数据是 3, 4
    // pt3 的数据是 5, 6
    Point pt1{1,2};
    Point pt2{3,4};
    Point pt3{5,6};

    /**
     * 对象赋值
     *
     * pt2 = pt1;
     *
     * 注意：
     * pt1 和 pt2 在这行代码执行之前都已经存在。
     *
     * 所以这里不是用 pt1 创建 pt2，
     * 而是把 pt1 的内容赋值给已经存在的 pt2。
     *
     * 因此调用的是赋值运算符函数：
     *
     * Point & operator=(const Point & rhs)
     *
     * 而不是拷贝构造函数。
     */
    pt2 = pt1;// 调用一个赋值运算符函数

    // 赋值运算符函数的本质就是一个成员函数
    //
    // pt2 = pt1;
    //
    // 本质上可以写成：
    //
    // pt2.operator=(pt1);
    //
    // 此时：
    // this 指向 pt2
    // rhs 引用 pt1
    /* pt2.operator=(pt1); */

    // 赋值之后，pt2 的值变成和 pt1 一样，
    // 所以这里输出：
    // 1 2
    pt2.print();

    cout << "------" << endl;

    /**
     * 连续赋值
     *
     * pt3 = pt2 = pt1;
     *
     * 赋值运算符是从右往左结合的，
     * 所以它等价于：
     *
     * pt3 = (pt2 = pt1);
     *
     * 执行过程：
     *
     * 1. 先执行 pt2 = pt1
     *
     *    本质是：
     *    pt2.operator=(pt1);
     *
     *    执行后：
     *    pt2 的值变成 1, 2。
     *
     *    operator= 返回 *this，
     *    也就是返回 pt2 本身。
     *
     * 2. 再执行 pt3 = pt2
     *
     *    本质是：
     *    pt3.operator=(pt2);
     *
     *    执行后：
     *    pt3 的值也变成 1, 2。
     *
     * 所以连续赋值要求 operator= 必须返回当前对象的引用。
     */
    pt3 = pt2 = pt1;

    // 本质：连续的函数调用
    //
    // pt3 = pt2 = pt1;
    //
    // 可以理解为：
    //
    // pt3.operator=(pt2.operator=(pt1));
    //
    // 其中：
    //
    // pt2.operator=(pt1)
    // 返回的是 pt2 本身。
    //
    // 然后：
    //
    // pt3.operator=(pt2)
    //
    // 继续完成第二次赋值。
    pt3.operator=(pt2.operator=(pt1));
}

int main(int argc, char *argv[])
{
    // 调用 test1，测试自定义类型的赋值运算符函数
    test1();

    return 0;
}