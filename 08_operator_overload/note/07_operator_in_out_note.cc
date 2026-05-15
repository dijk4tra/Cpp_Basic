#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>

using namespace std;

/**
 * 输入、输出运算符的重载：
 *
 * 对于内置类型来说，cin 和 cout 可以直接使用：
 * cin >> a;
 * cout << a;
 *
 * 但是 Complex 是自定义类型，
 * 标准库并不知道应该如何输入、输出一个 Complex 对象。
 *
 * 所以如果希望下面的代码可以使用：
 * cin >> cx;
 * cout << cx;
 *
 * 就需要重载输入运算符 operator>>
 * 和输出运算符 operator<<。
 *
 * 注意：
 * 输入、输出运算符通常采用普通函数形式重载，
 * 一般不写成成员函数形式。
 *
 * 因为：
 * cout << cx;
 *
 * 左操作数是 cout，
 * 它的类型是 ostream，
 * 不是 Complex 对象。
 *
 * 如果写成 Complex 的成员函数形式，
 * 调用形式会变成：
 * cx.operator<<(cout);
 *
 * 这就不符合 cout << cx 的使用习惯。
 *
 * 所以 operator<< 和 operator>> 一般写成普通函数，
 * 如果需要访问类的 private 成员，
 * 再把它们声明为 friend 友元函数。
 */

class Complex
{
public:
    /**
     * 默认构造函数。
     *
     * 因为 test2 中需要先创建一个空的 Complex 对象：
     * Complex cx;
     *
     * 然后再通过 cin >> cx;
     * 从键盘输入实部和虚部。
     */
    Complex() = default;

    /**
     * 有参构造函数。
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
     * const 表示该成员函数不会修改当前对象。
     */
    int getReal() const
    {
        return m_real;
    }

    /**
     * 获取虚部。
     */
    int getImage() const
    {
        return m_image;
    }

    /**
     * 普通成员函数，用来打印 Complex 对象。
     *
     * 这种方式可以输出对象内容，
     * 但是调用形式是：
     * cx.print();
     *
     * 如果希望写成：
     * cout << cx;
     *
     * 就需要重载 operator<<。
     */
    void print()
    {
        cout << m_real << "+" << m_image << "i" << endl;
    }

    /**
     * 把普通函数 operator+ 声明为友元函数。
     *
     * 这样 operator+ 可以直接访问 Complex 的 private 成员。
     */
    friend
    Complex operator+(const Complex & lhs, const Complex & rhs);

    /**
     * 成员函数形式重载 operator+。
     *
     * 表达式：
     * cx1 + cx2
     *
     * 本质上等价于：
     * cx1.operator+(cx2);
     *
     * this 指向左操作数 cx1，
     * rhs 表示右操作数 cx2。
     */
    Complex operator+(const Complex & rhs)
    {
        return Complex{this->m_real + rhs.m_real,
                       this->m_image + rhs.m_image};
    }

    /**
     * 声明普通函数 operator<< 为友元函数。
     *
     * operator<< 用来实现 Complex 对象的输出。
     *
     * 表达式：
     * cout << cx;
     *
     * 本质上等价于：
     * operator<<(cout, cx);
     *
     * 参数说明：
     * ostream & os
     * 表示输出流对象，比如 cout。
     *
     * const Complex & cx
     * 表示要输出的 Complex 对象。
     *
     * cx 使用 const 引用：
     * 1. 避免拷贝对象
     * 2. 输出操作不应该修改 cx
     *
     * 返回值使用 ostream &：
     * 是为了支持连续输出。
     *
     * 例如：
     * cout << cx << endl;
     */
    friend
    ostream & operator<<(ostream & os, const Complex & cx);

    /**
     * 声明普通函数 operator>> 为友元函数。
     *
     * operator>> 用来实现 Complex 对象的输入。
     *
     * 表达式：
     * cin >> cx;
     *
     * 本质上等价于：
     * operator>>(cin, cx);
     *
     * 参数说明：
     * istream & is
     * 表示输入流对象，比如 cin。
     *
     * Complex & cx
     * 表示要被输入数据修改的 Complex 对象。
     *
     * 注意：
     * 这里 cx 不能加 const，
     * 因为输入操作需要修改 cx 的实部和虚部。
     *
     * 返回值使用 istream &：
     * 是为了支持连续输入。
     *
     * 例如：
     * cin >> cx1 >> cx2;
     */
    friend
    istream & operator>>(istream & is, Complex & cx);

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
 *
 * 所以这里通过 public 成员函数 getReal 和 getImage
 * 获取实部和虚部。
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
 * operator+ 虽然是普通函数，
 * 但是被 Complex 声明为了 friend，
 * 所以可以直接访问 m_real 和 m_image。
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
 * 作用：
 * 让 Complex 对象可以直接使用 cout 输出。
 *
 * 例如：
 * cout << cx;
 *
 * 本质上是调用：
 * operator<<(cout, cx);
 */
ostream & operator<<(ostream & os, const Complex & cx)
{
    /**
     * 因为 operator<< 是 Complex 的友元函数，
     * 所以这里可以直接访问 private 成员：
     * cx.m_real
     * cx.m_image
     */
    os << cx.m_real << "+" << cx.m_image << "i";

    /**
     * 返回输出流对象。
     *
     * 这样可以支持链式调用：
     * cout << cx << endl;
     *
     * 如果不返回 os，
     * 那么 cout << cx 的结果就不能继续 << endl。
     */
    return os;
}

void test1()
{
    Complex cx {1, 1};

    /**
     * 这里可以直接输出 Complex 对象，
     * 是因为已经重载了 operator<<。
     *
     * cout << cx << endl;
     *
     * 先执行：
     * operator<<(cout, cx);
     *
     * operator<< 返回 cout，
     * 然后继续执行：
     * cout << endl;
     */
    cout << cx << endl;

    // 本质：普通函数调用
    /* operator<<(cout, cx); */
}


/**
 * Complex 对象的实部、虚部通过键盘输入。
 *
 * 例如输入：
 * 3 4
 *
 * 就表示：
 * 实部为 3，
 * 虚部为 4。
 */

/**
 * 重载 operator>>。
 *
 * 作用：
 * 让 Complex 对象可以直接使用 cin 输入。
 *
 * 例如：
 * cin >> cx;
 *
 * 本质上是调用：
 * operator>>(cin, cx);
 */
istream & operator>>(istream & is, Complex & cx)
{
    /**
     * 从输入流中依次读取两个整数，
     * 分别赋值给复数的实部和虚部。
     *
     * 因为 operator>> 是 Complex 的友元函数，
     * 所以可以直接访问 private 成员。
     */
    is >> cx.m_real >> cx.m_image;

    /**
     * 返回输入流对象。
     *
     * 这样可以支持链式输入：
     * cin >> cx1 >> cx2;
     */
    return is;
}

void test2()
{
    /**
     * 创建 Complex 对象。
     *
     * 这里使用默认构造函数，
     * 后面再通过 cin 输入实部和虚部。
     */
    Complex cx;

    cout << "input real image: " << endl;

    /**
     * 因为重载了 operator>>，
     * 所以可以直接通过 cin 给 Complex 对象输入数据。
     */
    cin >> cx;

    // 本质：普通函数调用
    // operator>>(cin, cx);

    /**
     * 因为重载了 operator<<，
     * 所以可以直接通过 cout 输出 Complex 对象。
     */
    cout << cx << endl;
}

/**
 * 思考题：
 *
 * class A
 * {
 * private:
 *     int m_dataA;
 * };
 *
 * class B
 * {
 * private:
 *     int m_dataB;
 *     A m_a;
 * };
 *
 * B b;
 * cout << b << endl;
 *
 * 如果希望 cout << b 可以正常输出，
 * 需要重载 B 类的 operator<<。
 *
 * 但是 B 中又包含了一个 A 类型的成员 m_a。
 * 如果在输出 B 的时候还想输出 m_a，
 * 那么 A 类型也应该支持 operator<<。
 *
 * 也就是说：
 * 自定义类型中如果包含另一个自定义类型对象，
 * 输出外层对象时，内层对象也要知道如何输出。
 *
 * ostream & operator<<(ostream& os, const B & b)
 * {
 *    os << b.m_dataB << b.m_a;
 *    return os;
 * }
 *
 * ostream & operator<<(ostream& os, const A & a)
 * {
 *    os << a.m_dataA;
 *    return os;
 * }
 *
 * 注意：
 * 如果 operator<< 需要访问 A 或 B 的 private 成员，
 * 也需要在对应类中把 operator<< 声明为 friend。
 */

int main(int argc, char *argv[])
{
    /**
     * test1 测试输出运算符 operator<<。
     *
     * test2 测试输入运算符 operator>>
     * 和输出运算符 operator<<。
     */
    /* test1(); */
    test2();

    return 0;
}