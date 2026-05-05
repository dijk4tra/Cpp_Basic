#include <iostream>

using std::cout;
using std::endl;

/*
 * const 成员函数：在成员函数的形参列表后添加 const
 *
 * 语法：
 * 返回值类型 函数名(形参列表) const {}
 *
 * 特点：
 * const 与成员函数结合后，该成员函数具有只读属性，
 * 不能修改对象的状态，即不能修改数据成员的值。
 */

class A
{
public:
    int m_num = 1;
};

class Point
{
public:
    Point(int x, int y)
    {}

    // const 成员函数
    void show() const
    {
        // const 成员函数中的 this 指针具有双重 const 限定
        // 既不能改变 this 的指向，也不能通过 this 修改对象内容
        this;

        /* this->m_x = 1; */

        m_y;

        /* m_x = 1; */
        /* m_y = 2; */

        m_a.m_num;

        /* m_a.m_num = 10; */
    }

    void show(){} // this 是常量指针

    // 这里可以构成成员函数重载
    // 因为两个版本函数中隐含的 this 类型不同

    // 什么时候使用 const 成员函数？
    // 当函数只需要访问成员数据，而不允许修改对象状态时使用
    int getX() const
    {
        /* m_x = 10; */
        return m_x;
    }

private:
    int m_x;
    int m_y;
    A m_a;
};

void test1()
{
    Point pt{1, 2};
    int x = pt.getX();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}