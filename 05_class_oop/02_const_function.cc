#include <iostream>

using std::cout;
using std::endl;

/**
 * const成员函数: 在成员函数的形参列表后加const
 *
 * 语法:
 * 返回值类型 函数名(形参列表) const {}
 * 特点:
 * const和成员函数结合,具有只读属性,不能修改对象状态
 * 即数据成员的取值不能改
 *
 */

class A
{
public:
    int m_num;
}

class Point
{
public:
    Point(int x, int y)
    {}

    // const 成员函数
    void show() const
    {   
        // const成员函数中的this指针变成了双重const限定的指针
        // 既不能改指向也不能改内容!
        this;
        /* this->m_x = 1; */
        m_x;
        m_y;
        /* m_x = 1; */
        /* m_y = 1; */
        m_a.m_num;
        /* m_a.m_num = 10; */
    }
    
    void show(){} // 这里的this是常量指针
    // 这里可以构成成员函数的重载
    // 两个版本的函数中隐含的this类型不一样
    
    // 什么时候使用const函数?
    // 只让访问不让修改的时候
    int getX() const
    {
        /* m_x = 10; */
        return m_x;
    }

private:
    int m_x;
    int m_y;
    A m_a;
}

void test1()
{
    Point pt{1,2};
    int x = pt.getX();
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

