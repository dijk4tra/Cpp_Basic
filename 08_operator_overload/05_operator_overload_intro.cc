#include <iostream>

using std::cout;
using std::endl;

/**
 * 不能被重载的运算符：
 * 1. 成员访问运算符：.
 * 2. 成员指针访问运算符：.*
 * 3. 作用域运算符：::
 * 4. 条件运算符：?:
 * 5. sizeof 运算符
 *
 * 运算符重载的本质：函数调用。
 * 1. 普通函数形式：test1()
 * 2. 成员函数形式：对象.func() 或 指针->func()
 *
 * 通常只有自定义类型才需要进行运算符重载。
 *
 * 重载一个运算符时，需要重点考虑：
 * 1. 采用哪种形式：普通函数还是成员函数
 * 2. 函数的返回值类型
 * 3. 函数的参数列表
 * 4. 函数体的实现逻辑是否符合该运算符原本的语义
 */

class Point
{
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {}

    Point & operator=(const Point & rhs)
    {
        this->m_x = rhs.m_x;
        this->m_y = rhs.m_y;

        return *this;
    }

private:
    int m_x;
    int m_y;
};


void test1()
{
    int a = 1;
    int b = 1;
    a + b;

    Point pt1{1,2};
    Point pt2{3,4};
    /* pt1 + pt2; // 若要支持 Point 对象相加，需要重载 operator+ */

    // 赋值运算符的简写形式
    pt2 = pt1; // 调用赋值运算符重载函数 operator=

    // 赋值运算符的本质：成员函数调用
    pt2.operator=(pt1);

    cout << a << endl;
    /* cout << pt1 << endl; // error：未重载输出运算符，不能直接输出 Point 对象 */
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}