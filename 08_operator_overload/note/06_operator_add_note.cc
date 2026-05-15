#include <iostream>
#include <iterator>

using std::cout;
using std::endl;

/**
 * 实现一个复数类，重载 operator+ 运算符。
 *
 * 复数相加的规则：
 * 实部和实部相加，
 * 虚部和虚部相加。
 *
 * 例如：
 * (1 + 1i) + (2 + 2i)
 *
 * 结果为：
 * 3 + 3i
 *
 * 运算符重载的形式：
 * 1. 普通函数形式
 * 2. 普通函数的友元形式
 * 3. 成员函数形式
 *
 * 注意：
 * operator+ 的结果通常是一个新的对象，
 * 所以返回值一般不写引用。
 */

class Complex
{
public:
    /**
     * 构造函数
     *
     * 用 real 初始化复数的实部，
     * 用 image 初始化复数的虚部。
     */
    Complex(int real, int image)
    : m_real(real)
    , m_image(image)
    {}

    /**
     * 获取实部。
     *
     * const 表示该成员函数不会修改当前对象的数据成员。
     */
    int getReal() const
    {
        return m_real;
    }

    /**
     * 获取虚部。
     *
     * 普通函数形式重载 operator+ 时，
     * 因为不能直接访问 private 成员，
     * 所以可以通过 getReal 和 getImage 获取数据。
     */
    int getImage() const
    {
        return m_image;
    }

    /**
     * 打印复数。
     *
     * 这里简单按照：
     * 实部 + 虚部 i
     *
     * 的形式输出。
     */
    void print()
    {
        cout << m_real << "+" << m_image << "i" << endl;
    }

    /**
     * 把普通函数 operator+ 声明为友元函数。
     *
     * 这样 operator+ 虽然不是 Complex 的成员函数，
     * 但是也可以直接访问 Complex 的 private 成员：
     * m_real 和 m_image。
     *
     * 友元函数形式常用于：
     * 运算符左操作数不是当前类对象，
     * 或者希望两个操作数地位对等的情况。
     */
    friend
    Complex operator+(const Complex & lhs, const Complex & rhs);

    /**
     * 采用成员函数形式重载 operator+。
     *
     * 表达式：
     * cx1 + cx2
     *
     * 如果调用的是成员函数形式，
     * 本质上等价于：
     * cx1.operator+(cx2);
     *
     * 其中：
     * cx1 是调用者对象，this 指向 cx1；
     * cx2 是参数对象，对应 rhs。
     *
     * 返回值：
     * Complex
     *
     * 因为加法运算的结果是一个新的复数对象，
     * 是函数内部创建的临时对象，
     * 所以不能返回引用。
     */
    Complex operator+(const Complex & rhs)
    {
        /**
         * this->m_real 表示左操作数的实部。
         * rhs.m_real 表示右操作数的实部。
         *
         * this->m_image 表示左操作数的虚部。
         * rhs.m_image 表示右操作数的虚部。
         *
         * 复数相加：
         * 实部相加，虚部相加。
         */
        return Complex{this->m_real + rhs.m_real,
                       this->m_image + rhs.m_image};
    }

private:
    // 复数的实部
    int m_real;

    // 复数的虚部
    int m_image;
};

/*
 * 普通函数形式重载 operator+。
 *
 * 这种形式下，operator+ 不是 Complex 的成员函数，
 * 所以不能直接访问 Complex 的 private 成员。
 *
 * 因此需要通过 public 成员函数：
 * getReal()
 * getImage()
 *
 * 来获取实部和虚部。
 *
 * 返回的是临时对象，
 * 所以返回值不能写成 Complex &。
 */
/*
Complex operator+(const Complex & lhs, const Complex & rhs)
{
    return Complex{lhs.getReal() + rhs.getReal(),
                   lhs.getImage() + rhs.getImage()};
}
*/

/*
 * 友元函数形式重载 operator+。
 *
 * 这种形式本质上仍然是普通函数，
 * 只不过它被 Complex 类声明为了 friend。
 *
 * 因此可以直接访问 Complex 的 private 成员：
 * lhs.m_real
 * rhs.m_real
 * lhs.m_image
 * rhs.m_image
 *
 * 返回的是临时对象，
 * 所以返回值不能写成 Complex &。
 */
/*
Complex operator+(const Complex & lhs, const Complex & rhs)
{
    return Complex{lhs.m_real + rhs.m_real,
                   lhs.m_image + rhs.m_image};
}
*/


void test1()
{
    int a = 1;
    int b = 2;

    /**
     * int 是内置类型，
     * 可以直接使用 + 运算符。
     *
     * a + b 的结果是一个临时值，
     * 也就是右值。
     */
    a + b; // 结果为临时的变量，右值

    /**
     * 推广到自定义类型上。
     *
     * Complex 是自定义类型，
     * 如果希望两个 Complex 对象可以使用 + 运算符，
     * 就需要重载 operator+。
     */
    Complex cx1 {1,1};
    Complex cx2 {2,2};

    /**
     * 采用普通函数或者友元函数形式重载时：
     *
     * cx1 + cx2
     *
     * 本质上等价于：
     * operator+(cx1, cx2);
     *
     * lhs 对应 cx1，
     * rhs 对应 cx2。
     */
    Complex cx3 = cx1 + cx2;

    // 本质是一个普通函数调用
    /* operator+(cx1, cx2); */

    // 输出相加之后的复数结果
    cx3.print();
}

void test2()
{
    Complex cx1 {1,1};
    Complex cx2 {2,2};

    /**
     * 采用成员函数形式重载 operator+。
     *
     * cx1 + cx2
     *
     * 本质上等价于：
     * cx1.operator+(cx2);
     *
     * 其中：
     * this 指向 cx1，
     * rhs 表示 cx2。
     */
    Complex cx3 = cx1 + cx2;

    // 本质：成员函数调用
    /* cx1.operator+(cx2); */

    // 输出相加之后的复数结果
    cx3.print();
}

int main(int argc, char *argv[])
{
    /**
     * test1 用来测试普通函数形式或者友元函数形式。
     *
     * 当前代码中真正生效的是成员函数形式的 operator+，
     * 所以这里调用 test2。
     */
    /* test1(); */
    test2();

    return 0;
}