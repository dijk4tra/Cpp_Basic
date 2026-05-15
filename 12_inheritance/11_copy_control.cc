#include <iostream>

using std::cout;
using std::endl;

/*
 * 子类对象的复制控制操作：
 *
 * 1. 拷贝构造函数
 *    使用一个已有对象创建新对象时调用。
 *
 *    例如：
 *    Son s2 = s1;
 *
 * 2. 赋值运算符函数
 *    两个已经存在的对象之间赋值时调用。
 *
 *    例如：
 *    s2 = s1;
 *
 * 对于子类对象：
 * 无论是拷贝构造还是赋值，
 * 都需要同时处理两个部分：
 *
 * 1. 从父类继承来的父类部分；
 * 2. 子类自己定义的成员部分。
 *
 * 如果没有显式定义拷贝构造函数，
 * 编译器会自动生成默认拷贝构造函数。
 * 默认拷贝构造函数会自动拷贝：
 * 1. 父类部分；
 * 2. 子类自己的成员。
 *
 * 如果在子类中显式定义了拷贝构造函数，
 * 那么需要在初始化列表中显式调用父类的拷贝构造函数，
 * 否则父类部分可能不会按照预期进行拷贝。
 *
 * 如果没有显式定义赋值运算符函数，
 * 编译器会自动生成默认赋值运算符函数。
 * 默认赋值运算符函数会自动赋值：
 * 1. 父类部分；
 * 2. 子类自己的成员。
 *
 * 如果在子类中显式定义了赋值运算符函数，
 * 那么需要在函数体中显式调用父类的赋值运算符函数，
 * 否则父类部分可能不会按照预期进行赋值。
 */

class Father
{
public:
    Father(int f)
    : m_f(f)
    {
    }

    // 父类拷贝构造函数
    // 使用已有的 Father 对象创建新的 Father 对象时调用
    Father(const Father &rhs)
    : m_f(rhs.m_f)
    {
        cout << "Father copy constructor called" << endl;
    }

    // 父类赋值运算符函数
    // 两个已经存在的 Father 对象之间赋值时调用
    Father &operator=(const Father &rhs)
    {
        cout << "Father operator= called" << endl;

        // 防止自赋值
        if (this != &rhs) {
            this->m_f = rhs.m_f;
        }

        // 返回当前对象本身，支持连续赋值
        return *this;
    }

    int m_f;
};

class Son : public Father
{
public:
    Son(int f, int s)
    : Father(f)
    , m_s(s)
    {
    }

    // 子类拷贝构造函数
    Son(const Son &rhs)
    /*
     * 显式调用父类的拷贝构造函数，
     * 用 rhs 中的父类部分初始化当前对象的父类部分。
     *
     * rhs 是 Son 对象，
     * 但可以作为 Father 引用传给 Father 的拷贝构造函数，
     * 这属于向上转型。
     */
    : Father(rhs)
    , m_s(rhs.m_s)
    {
        cout << "Son copy constructor called" << endl;
    }

    // 子类赋值运算符函数
    Son &operator=(const Son &rhs)
    {
        cout << "Son operator= called" << endl;

        // 防止自赋值
        if (this != &rhs) {
            /*
             * 显式调用父类的赋值运算符函数，
             * 完成父类部分的赋值。
             *
             * rhs 是 Son 对象，
             * 但可以作为 Father 引用传给 Father::operator=，
             * 这同样属于向上转型。
             */
            Father::operator=(rhs);

            // 再完成子类自己成员的赋值
            this->m_s = rhs.m_s;
        }

        // 返回当前对象本身，支持连续赋值
        return *this;
    }

    int m_s;
};

void test1()
{
    Son s1{1, 2};

    cout << s1.m_f << endl;
    cout << s1.m_s << endl;

    cout << "-----" << endl;

    /*
     * 使用已有对象 s1 创建新对象 s2，
     * 会调用 Son 的拷贝构造函数。
     *
     * 如果 Son 中没有手动定义拷贝构造函数，
     * 编译器会生成默认拷贝构造函数。
     *
     * 默认拷贝构造会自动拷贝：
     * 1. 父类 Father 部分中的 m_f；
     * 2. 子类 Son 自己的成员 m_s。
     *
     * 如果 Son 中手动定义了拷贝构造函数，
     * 就需要在初始化列表中显式调用 Father 的拷贝构造函数，
     * 否则 Father 部分会尝试走默认构造。
     *
     * 但本例中 Father 没有无参构造函数，
     * 如果 Son 的拷贝构造函数中不写 Father(rhs)，
     * 代码会编译失败。
     */
    Son s2 = s1;

    cout << s2.m_f << endl;
    cout << s2.m_s << endl;
}

void test2()
{
    Son s1{1, 2};
    Son s2{3, 4};

    /*
     * s1 和 s2 都已经存在，
     * 此时执行赋值操作，会调用 Son 的赋值运算符函数。
     *
     * 在 Son::operator= 中：
     * 1. 先调用 Father::operator= 完成父类部分赋值；
     * 2. 再给 Son 自己的成员 m_s 赋值。
     */
    s2 = s1;

    cout << s2.m_f << endl;
    cout << s2.m_s << endl;
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();

    return 0;
}
