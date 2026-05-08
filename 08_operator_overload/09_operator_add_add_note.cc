#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>

using namespace std;

/**
 * operator++ 的重载：
 *
 * ++ 运算符有两种形式：
 * 1. 前置++
 *    ++a;
 *
 * 2. 后置++
 *    a++;
 *
 * 对于内置类型 int 来说：
 * int a = 1;
 * ++a;
 * a++;
 *
 * 编译器已经知道应该如何执行。
 *
 * 但是对于自定义类型 Complex，
 * 如果希望 Complex 对象也可以使用 ++，
 * 就需要自己重载 operator++。
 *
 * 注意：
 * 前置++ 和 后置++ 的函数名都是 operator++，
 * 所以 C++ 通过参数来区分它们。
 *
 * 前置++：
 * operator++()
 * 无参数。
 *
 * 后置++：
 * operator++(int)
 * 有一个 int 类型的占位参数。
 *
 * 这个 int 参数只是为了区分前置和后置，
 * 在函数体中没有实际意义。
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
     * operator+ 不修改原对象，
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
     * 声明普通函数 operator>> 为友元函数。
     *
     * 这样可以直接使用：
     * cin >> cx;
     *
     * 输入 Complex 对象的实部和虚部。
     */
    friend
    istream & operator>>(istream & is, Complex & cx);

    /**
     * 成员函数形式重载 operator+=。
     *
     * cx1 += cx2;
     *
     * 本质上等价于：
     * cx1.operator+=(cx2);
     *
     * += 会修改左操作数本身，
     * 所以返回当前对象自身的引用。
     */
    Complex & operator+=(const Complex & rhs)
    {
        cout << "成员函数形式的 operator+=() 重载" << endl;

        this->m_real += rhs.m_real;
        this->m_image += rhs.m_image;

        // 返回当前对象的引用
        return *this;
    }

    /**
     * 前置++ 运算符重载。
     *
     * 表达式：
     * ++cx;
     *
     * 本质上等价于：
     * cx.operator++();
     *
     * 前置++ 的特点：
     * 先自增，再返回自增之后的对象。
     *
     * 参数：
     * 前置++ 没有参数。
     *
     * 返回值：
     * Complex &
     *
     * 因为前置++ 返回的是当前对象本身，
     * 当前对象在函数结束后仍然存在，
     * 所以可以返回引用。
     */
    Complex & operator++()
    {
        cout << "前置++：形式上使用成员函数(值有变化)" << endl;

        /**
         * 对当前对象进行 ++ 操作。
         *
         * 这里规定 Complex 对象的 ++ 逻辑是：
         * 实部加 1，
         * 虚部加 1。
         */
        this->m_real += 1;
        this->m_image += 1;

        /**
         * 返回当前对象自身。
         *
         * *this 表示当前对象。
         *
         * 这样 ++cx 的结果仍然是一个左值，
         * 可以继续参与某些需要左值的操作。
         */
        return *this;
    }

    /**
     * 后置++ 运算符重载。
     *
     * 表达式：
     * cx++;
     *
     * 本质上等价于：
     * cx.operator++(0);
     *
     * 后置++ 的特点：
     * 先保存原来的值，
     * 再对当前对象自增，
     * 最后返回自增之前保存的旧值。
     *
     * 参数：
     * int 是占位参数。
     *
     * 注意：
     * C++ 规定，后置++ 的参数必须是 int 类型的占位参数，
     * 不能有默认值。
     *
     * 这个 int 参数只是为了区分前置++ 和后置++，
     * 在函数体内没有实际意义，可以不使用。
     *
     * 返回值：
     * Complex
     *
     * 后置++ 返回的是自增之前的旧状态，
     * 这个旧状态通常是函数内部保存的临时对象，
     * 所以返回值不能写成引用。
     */
    Complex operator++(int)
    {
        cout << "后置++：形式上使用成员函数(值有变化)" << endl;

        /**
         * 先记录当前对象自增之前的状态。
         *
         * temp 是一个新的 Complex 对象，
         * 保存的是当前对象原来的值。
         */
        Complex temp = *this;

        /**
         * 再对当前对象进行 ++ 操作。
         *
         * 这里让实部和虚部都加 1。
         */
        this->m_real += 1;
        this->m_image += 1;

        /**
         * 返回自增之前保存的状态。
         *
         * 注意：
         * 返回的是 temp 这个临时对象的值，
         * 不是当前对象自身。
         */
        return temp;
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
 * 普通函数不是 Complex 的成员函数，
 * 如果没有声明为 friend，
 * 就不能直接访问 private 成员。
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

/**
 * Complex 对象的实部、虚部通过键盘输入。
 */

/**
 * 重载 operator>>。
 *
 * 让 Complex 对象可以直接使用 cin 输入。
 */
istream & operator>>(istream & is, Complex & cx)
{
    is >> cx.m_real >> cx.m_image;

    // 返回流对象，支持连续输入
    return is;
}

void test1()
{
    /**
     * 对于内置类型 int：
     *
     * ++a 是前置++。
     * a++ 是后置++。
     *
     * 前置++ 返回自增之后的对象本身，
     * 通常是左值。
     *
     * 后置++ 返回自增之前的临时值，
     * 通常是右值。
     */
    /* int a = 1; */
    /* &(++a); // 左值 */
    /* &(a++); // 右值 */

    Complex cx {1, 1};

    /**
     * 前置++：
     *
     * ++cx;
     *
     * 本质上等价于：
     * cx.operator++();
     *
     * 执行之后，cx 自身的值发生变化。
     *
     * 原来：
     * 1 + 1i
     *
     * 执行 ++cx 后：
     * 2 + 2i
     */
    ++cx; // cx.operator++();

    /**
     * 输出前置++ 之后的 cx。
     */
    cout << cx << endl;
}

void test2()
{
    Complex cx {1, 1};

    /**
     * 后置++：
     *
     * cx++;
     *
     * 本质上等价于：
     * cx.operator++(0);
     *
     * 后置++ 会先保存 cx 原来的值，
     * 然后让 cx 自身加 1，
     * 最后返回原来的旧值。
     */
    Complex cx2 = cx++;

    // 本质：cx.operator++(0);

    /**
     * 输出 cx。
     *
     * cx 是执行后置++ 之后的对象，
     * 所以结果为：
     * 2 + 2i
     */
    cout << cx << endl;

    /**
     * 输出 cx2。
     *
     * cx2 接收的是 cx++ 返回的旧值，
     * 所以结果为：
     * 1 + 1i
     */
    cout << cx2 << endl;
}


int main(int argc, char *argv[])
{
    /**
     * test1 测试前置++。
     *
     * 如果要测试后置++，
     * 可以改为调用 test2。
     */
    test1();

    return 0;
}