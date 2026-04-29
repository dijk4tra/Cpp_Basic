#include <iostream>

using std::cout;
using std::endl;

/**
 * 构造函数初始化列表
 * 
 * 在C++中，规范的成员变量初始化方式一般是：
 * 
 * 构造函数名(形参列表)
 *     : 成员变量1(初始值1),
 *       成员变量2(初始值2)
 * {
 *     构造函数体
 * }
 *
 * 这种写法叫做“初始化列表”。
 * 
 * 注意：
 * 1.初始化列表写在构造函数参数列表和函数体之间
 * 2.如果有多个成员变量要初始化，中间用逗号分隔
 * 3.初始化列表是真正的“初始化”
 * 4.构造函数体内部的赋值是“先默认初始化，再赋值”
 *
 * 例如：
 *
 * Point(int x, int y)
 *     : m_x(x), m_y(y)
 * {
 * }
 *
 * 比下面这种写法更规范：
 *
 * Point(int x, int y)
 * {
 *     m_x = x;
 *     m_y = y;
 * }
 *
 * 重要规则：
 * 数据成员的初始化顺序只和它们在类中声明的顺序有关，
 * 和初始化列表中书写的顺序无关。
 */

class Point
{
public:
    // 无参构造函数
    Point()
    {
        cout << "Point()" << endl;
        // 注意：
        // 这里没有在初始化列表中初始化 m_y 和 m_x
        // 如果创建 Point pt; 或 Point pt{};
        // 那么 m_y 和 m_x 都是内置类型 int，
        // 它们的值是不确定的。
    }
    // 有参构造函数
    Point(int x, int y) 
    : m_x(x),  // m_x后初始化,因为它在m_y之后声明
      m_y(m_x) // m_y先声明,其先初始化
    {
        cout << "Point(int, int)" << endl;
    }
    /*
     * 上面的初始化列表看起来像是：
     *
     * 1. 先初始化 m_x = x
     * 2. 再初始化 m_y = m_x
     *
     * 但这是错误理解。
     *
     * 实际初始化顺序由成员变量在 private 中的声明顺序决定：
     *
     * private:
     *     int m_y; // 先声明，所以先初始化
     *     int m_x; // 后声明，所以后初始化
     *
     * 因此实际顺序是：
     *
     * 1. 先初始化 m_y(m_x)
     * 2. 再初始化 m_x(x)
     *
     * 问题：
     * 当初始化 m_y 时，m_x 还没有被初始化，
     * 所以 m_y(m_x) 使用的是一个不确定的值。
     *
     * 因此 Point pt{1, 2}; 之后，
     * m_x 的值通常是 1，
     * 但 m_y 的值是不确定的。
     *
     * 另外：
     * 形参 y 在这个构造函数中没有被使用。
     */


    void print()
    {
        cout << m_x << " " << m_y << endl;
    }
private:
    int m_y; // m_y 先声明，所以一定先初始化
    int m_x; // m_x 后声明，所以一定后初始化
};


void test1()
{   
    // 创建 Point 对象，传入两个参数
    // 会调用 Point(int, int)
    Point pt{1, 2};
    pt.print();
    // 由于 Point(int, int) 中 m_y 使用了尚未初始化的 m_x，
    // 所以这里打印结果中：
    //
    // m_x 通常是 1
    // m_y 是不确定值
    //
    // 输出可能类似：
    // Point(int, int)
    // 1 随机值
}


class MyClass
{
public:
    // 构造函数带有默认参数
    //
    // data1 默认值是 1
    // data2 默认值是 1
    //
    // 所以下面几种写法都可以：
    //
    // MyClass obj;          // data1 = 1,  data2 = 1
    // MyClass obj{10};      // data1 = 10, data2 = 1
    // MyClass obj{10, 20};  // data1 = 10, data2 = 20
    //
    // 注意：
    // 如果构造函数已经通过默认参数支持无参调用，
    // 就尽量不要再重载一个真正的无参构造函数。
    MyClass(int data1 = 1, int data2 = 1)
    : m_data1(data1),
      m_data2(data2)
    {

    }
    
    /*
     * 不建议再写这个无参构造函数
     * MyClass(){}
     * 
     * 原因：
     * 上面的 MyClass(int data1 = 1, int data2 = 1)
     * 本身就可以无参调用：
     *
     * MyClass obj;
     *
     * 如果再写一个 MyClass()，
     * 编译器就不知道应该调用哪一个：
     *
     * 1. MyClass()
     * 2. MyClass(int data1 = 1, int data2 = 1)
     *
     * 两个都能匹配无参创建对象，
     * 会造成调用二义性，导致编译报错。
     */

    // C++11 之后，可以直接在类内给非静态数据成员设置默认值
    // 这叫做“类内成员初始化”。
    // 它的作用类似于给成员变量提供默认值。
    int m_data1 = 10;
    int m_data2 = 20;

    /*
     * 注意：
     *
     * 如果构造函数初始化列表中显式初始化了成员变量，
     * 那么初始化列表中的值优先。
     *
     * 例如：
     *
     * MyClass obj;
     *
     * 会调用：
     *
     * MyClass(int data1 = 1, int data2 = 1)
     *
     * 初始化列表中写了：
     *
     * m_data1(data1),
     * m_data2(data2)
     *
     * 所以最终：
     *
     * m_data1 = 1
     * m_data2 = 1
     *
     * 而不是类内默认值 10 和 20。
     *
     * 类内默认值只有在构造函数没有显式初始化该成员时才会生效。
     */
};

void test2()
{
    // 虽然这里看起来是在调用无参构造函数，
    // 但实际上调用的是：
    // MyClass(int data1 = 1, int data2 = 1)
    // 因为两个参数都有默认值，所以可以不传参数。
    MyClass obj;
}


int main(int argc, char *argv[])
{
    // test1();
    test2();
    return 0;
}

