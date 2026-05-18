#include <iostream>
#include <string>

using std::cout;
using std::endl;

/**
 * 成员函数模板：
 * 可以把模板应用在类的成员函数上。
 *
 * 这样成员函数就可以接收不同类型的参数，
 * 而不需要为每一种类型分别写一个重载函数。
 *
 * 注意：
 * 这里的 Point 不是类模板，只是普通类；
 * 只有它的部分成员函数是函数模板。
 */


class Point
{
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {}

    // 成员函数模板：在类内声明并实现
    template <typename T>
    void print(T t)
    {
        cout << t << endl;
    }

    // 成员函数模板：类内声明，类外实现
    template <typename T>
    void print2(T t);

private:
    int m_x;
    int m_y;
};


// 类外实现成员函数模板
// 注意：类外实现时，也需要重新写 template <typename T>
template <typename T>
void Point::print2(T t)
{
    cout << t << endl;
    cout << "print2" << endl;
}


void test1()
{
    // 创建 Point 对象
    Point pt{1, 2};

    // 成员函数模板的隐式实例化
    pt.print(100);      // T 推导为 int
    pt.print(3.14);     // T 推导为 double

    pt.print2(100);     // T 推导为 int

    // 成员函数模板的显式实例化
    pt.print2<std::string>("abc");
}


int main(int argc, char *argv[])
{
    test1();

    return 0;
}