#include <iostream>

using std::cout;
using std::endl;

/*
 * 子类对象的复制控制操作：
 *
 * 1. 拷贝构造函数
 *    使用一个已有对象创建新对象时调用。
 *
 * 2. 赋值运算符函数
 *    两个已经存在的对象之间赋值时调用。
 *
 * 对于子类对象：
 * 拷贝构造时，不仅会拷贝子类自己定义的成员，
 * 也会拷贝从父类继承来的成员。
 *
 * 如果没有手动定义拷贝构造函数，
 * 编译器会自动生成默认拷贝构造函数，
 * 默认行为是逐成员拷贝。
 */

class Father
{
public:
    Father(int f)
    : m_f(f)
    {
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
     * 由于这里没有手动定义拷贝构造函数，
     * 编译器会生成默认拷贝构造函数。
     *
     * 默认拷贝构造会拷贝：
     * 1. 父类 Father 部分中的 m_f；
     * 2. 子类 Son 自己的成员 m_s。
     */
    Son s2 = s1;

    cout << s2.m_f << endl;
    cout << s2.m_s << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}