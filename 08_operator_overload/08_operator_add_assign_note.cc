#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>

using namespace std;

/**
 * operator+= 的重载：
 *
 * += 是复合赋值运算符。
 *
 * 对于内置类型来说：
 * b += a;
 *
 * 等价于：
 * b = b + a;
 *
 * 但是对于自定义类型 Complex，
 * 编译器不知道两个 Complex 对象应该如何进行 += 操作，
 * 所以需要自己重载 operator+=。
 *
 * 注意：
 * operator+= 通常采用成员函数形式重载。
 *
 * 因为 += 会修改左操作数本身，
 * 而成员函数中的 this 指针正好指向左操作数。
 *
 * 表达式：
 * cx1 += cx2;
 *
 * 本质上等价于：
 * cx1.operator+=(cx2);
 */

class Complex
{
public:
    /**
     * 默认构造函数。
     *
     * 允许创建一个没有显式初始化的 Complex 对象。
     */
    Complex() = default;

    /**
     * 有参构造函数。
     *
     * real 初始化实部，
     * image 初始化虚部。
     */
    Complex(int real, int image)
    : m_real(real)
    , m_image(image)
    {}

    // 获取实部，const 表示不会修改当前对象
    int getReal() const
    {
        return m_real;
    }

    // 获取虚部，const 表示不会修改当前对象
    int getImage() const
    {
        return m_image;
    }

    /**
     * 普通打印函数。
     *
     * 如果没有重载 operator<<，
     * 可以通过 cx.print() 输出对象内容。
     */
    void print()
    {
        cout << m_real << "+" << m_image << "i" << endl;
    }

    /**
     * 把普通函数 operator+ 声明为友元函数。
     *
     * 这样普通函数形式的 operator+ 可以直接访问 private 成员。
     */
    friend
    Complex operator+(const Complex & lhs, const Complex & rhs);

    /**
     * 成员函数形式重载 operator+。
     *
     * cx1 + cx2
     *
     * 本质上等价于：
     * cx1.operator+(cx2);
     *
     * operator+ 不会修改 cx1 和 cx2，
     * 而是返回一个新的 Complex 临时对象。
     */
    Complex operator+(const Complex & rhs)
    {
        return Complex{this->m_real + rhs.m_real,
                       this->m_image + rhs.m_image};
    }

    /**
     * 声明普通函数 operator<< 为友元函数。
     *
     * 这样可以直接使用：
     * cout << cx;
     *
     * 输出 Complex 对象。
     */
    friend
    ostream & operator<<(ostream & os, const Complex & cx);

    /**
     * 成员函数形式重载 operator+=。
     *
     * 表达式：
     * cx1 += cx2;
     *
     * 本质上等价于：
     * cx1.operator+=(cx2);
     *
     * this 指向左操作数 cx1，
     * rhs 表示右操作数 cx2。
     *
     * += 的语义是：
     * 在左操作数原有数据的基础上进行累加，
     * 并修改左操作数本身。
     *
     * 所以这里需要修改 this 指向的当前对象。
     *
     * 返回值使用 Complex &：
     * 是为了返回当前对象本身，
     * 并支持连续操作。
     *
     * 例如：
     * cx1 += cx2 += cx3;
     */
    Complex & operator+=(const Complex & rhs)
    {
        cout << "成员函数形式的 operator+=() 重载" << endl;

        /**
         * 实部相加，并保存回当前对象的实部。
         *
         * this->m_real 表示左操作数 cx1 的实部，
         * rhs.m_real 表示右操作数 cx2 的实部。
         */
        this->m_real += rhs.m_real;

        /**
         * 虚部相加，并保存回当前对象的虚部。
         */
        this->m_image += rhs.m_image;

        /**
         * 返回当前对象的引用。
         *
         * *this 表示当前对象 cx1。
         *
         * 因为当前对象在函数结束后仍然存在，
         * 所以可以返回引用。
         */
        return *this;
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
 * 普通函数不能直接访问 private 成员，
 * 所以通过 getReal 和 getImage 获取数据。
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
 * operator+ 被 Complex 声明为 friend 后，
 * 可以直接访问 m_real 和 m_image。
 */
/*
Complex operator+(const Complex & lhs, const Complex & rhs)
{
    return Complex{lhs.m_real + rhs.m_real,
                   lhs.m_image + rhs.m_image};
}
*/

/**
 * 采用友元函数形式重载 operator<<。
 *
 * 让 Complex 对象可以直接使用 cout 输出。
 */
ostream & operator<<(ostream & os, const Complex & cx)
{
    os << cx.m_real << "+" << cx.m_image << "i";

    // 返回流对象，支持 cout << cx << endl;
    return os;
}

void test1()
{
    /**
     * 对于内置类型 int，
     * += 运算符可以直接使用。
     *
     * b += a;
     *
     * 等价于：
     * b = b + a;
     */
    int a = 1;
    int b = 2;
    b += a;

    /**
     * 对于自定义类型 Complex，
     * 如果希望使用 +=，
     * 就需要重载 operator+=。
     */
    Complex cx1 {1, 1};
    Complex cx2 {2, 2};

    /**
     * 调用成员函数形式的 operator+=。
     *
     * cx1 += cx2;
     *
     * 本质上等价于：
     * cx1.operator+=(cx2);
     *
     * 执行之后，cx1 本身会被修改为：
     * 3 + 3i
     */
    cx1 += cx2;

    // 形式上选择成员函数
    // cx1.operator+=(cx2);

    /**
     * 输出 cx1。
     *
     * 因为已经重载了 operator<<，
     * 所以可以直接使用 cout 输出 Complex 对象。
     */
    cout << cx1 << endl;
}

int main(int argc, char *argv[])
{
    test1();

    return 0;
}