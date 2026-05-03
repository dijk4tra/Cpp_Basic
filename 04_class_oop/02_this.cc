#include <iostream>

using std::cout;
using std::endl;

/**
 * this 指针
 *
 * 在 C++ 中，每一个非静态成员函数中，
 * 都隐含了一个特殊的指针：this。
 *
 * this 的作用：
 * 指向当前调用该成员函数的对象。
 * 哪个对象调用成员函数，
 * this 就指向哪个对象。
 *
 * 例如：
 * Point pt{1, 2};
 * pt.print();
 * 此时 print 函数内部的 this，
 * 指向的就是对象 pt。
 *
 * this 的本质：
 * this 是一个指针。
 * 在普通成员函数中，可以简单理解为：
 * Point * const this
 *
 * 含义：
 * 1.this 是一个指针
 * 2.this 指向当前对象
 * 3.this 本身不能改变指向
 * 4.但是可以通过 this 修改当前对象的数据成员
 *
 * 注意：
 * this 不是普通变量，不能手动声明。
 * 它由编译器自动提供。
 *
 *
 * 普通成员函数为什么能直接访问成员变量？
 * 在成员函数内部写：
 * m_x
 * 编译器会自动理解为：
 * this->m_x
 * 所以：
 * cout << m_x << endl;
 * 等价于：
 * cout << this->m_x << endl;
 */

class Point
{
public:
    // 有参构造函数
    // 创建 Point 对象时调用：
    // Point pt{1, 2};
    // x 初始化 m_x
    // y 初始化 m_y
    Point(int x, int y)
        : m_x(x),
          m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    // 拷贝构造函数
    // 用一个已经存在的 Point 对象创建新对象时调用：
    // Point pt1{1, 2};
    // Point pt2{pt1};
    // rhs 表示被拷贝的对象
    Point(const Point & rhs)
        : m_x(rhs.m_x),
          m_y(rhs.m_y)
    {
        cout << "Point(const Point&)" << endl;
    }

    // 所有“非静态成员函数”中，
    // 形参列表里实际上都有一个隐藏参数 this。
    // 也就是说，下面这个函数：
    // void print()
    // 编译器可以理解成类似：
    // void print(Point * const this)
    // 当然，这只是帮助理解，实际代码不能这样写。
    void print()
    {
        // 直接访问成员变量
        // m_x 和 m_y 实际上等价于：
        // this->m_x
        // this->m_y
        cout << m_x << " " << m_y << endl;

        // this 表示当前对象的地址
        // 这里单独写 this 没有实际效果，
        // 只是为了说明 this 在成员函数中存在。
        this;

        // 通过 this 指针访问当前对象的数据成员
        this->m_x;
        this->m_y;

        // 因为当前函数不是 const 成员函数，
        // 所以可以通过 this 修改当前对象的数据成员。
        // 等价于：
        // m_x = 10;
        this->m_x = 10;
    }

    void show()
    {
        // 打印 this 指针保存的地址
        // this 指向当前对象，
        // 所以这里输出的是当前对象的地址。
        cout << this << endl;
    }

private:
    int m_x;
    int m_y;
};

void test1()
{
    // 创建一个 Point 对象 pt
    // 调用构造函数 Point(int, int)
    Point pt{1, 2};

    // pt 调用 show 函数
    // 此时 show 函数中的 this 指向 pt
    // 所以 pt.show() 内部：
    // this == &pt
    pt.show();

    // 打印对象 pt 的地址
    // 这个地址应该和 show 函数中打印的 this 相同。
    cout << &pt << endl;
}

int main(int argc, char *argv[])
{
    // 调用 test1，验证 this 指针和对象地址的关系
    test1();

    return 0;
}