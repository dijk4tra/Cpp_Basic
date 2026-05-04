#include <iostream>

using std::cout;
using std::endl;

/**
 * 构造函数 constructor: 一种特殊的成员函数
 * 
 * 作用：
 * 在创建对象时自动调用，通常用于给对象的数据成员做初始化
 * 
 * 语法；
 * 类名(形参列表)
 * {
 *   构造函数体 
 * }
 * 
 * 特点：
 * 1.构造函数没有返回值类型，连void也不能写
 * 2.构造函数的函数名必须和类名完全相同
 * 3.构造函数可以有参数，也可以没有参数
 *   -无参构造函数
 *   -有参构造函数
 * 4.一个类中可以有多个构造函数
 *   只要参数列表不同，就构成函数重载
 * 5.构造函数通常用于初始化成员变量
 * 
 * 注意：
 * 1.如果类中没有写任何构造函数，编译器会自动生成一个默认无参构造函数
 * 2.如果类中写了任意一个构造函数，编译器就不会再自动生成默认无参构造函数
 */

class Point
{
public:
    // 无参构造函数
    // 当使用 Point pt; 或 Point pt{}; 创建对象时，会调用这个构造函数
    Point()
    {
        cout << "Point()" << endl;
        // 在构造函数体中给成员变量赋初值
        m_x = 1;
        m_y = 2;
    }

    // 有参构造函数
    // 当使用 Point pt(10, 20); 或 Point pt{10, 20}; 创建对象时，会调用它
    Point(int x, int y)
    {
        cout << "Point(int, int)" << endl;
        m_x = x;
        m_y = y;
    }

    // 只有一个参数的构造函数
    // 当使用 Point pt(10); 或 Point pt{10}; 创建对象时，会调用它
    Point(int x)
    {
        m_x = x;
        m_y = 0;
    }
    
    /*
    // 下面这两个函数是普通成员函数，不是构造函数
    // 它们可以在对象创建完成之后修改成员变量
    void setX(int x)
    {
        m_x = x;
    }
    void setY(int y)
    {
        m_y = y;
    }
    */

    // 普通成员函数
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

private:
    // private 表示私有成员
    // 类外不能直接访问 m_x 和 m_y
    // 只能通过类中的 public 成员函数间接访问或修改
    int m_x;
    int m_y;
};


void test1()
{   
    // 注意：调用无参构造函数创建对象时，不要写成 Point pt();
    //
    // Point pt(); 的含义不是创建对象，
    // 而是声明了一个函数 pt，这个函数没有参数，返回值类型是 Point。
    //
    // 这在 C++ 中被称为“最令人困惑的解析”。
    /* Point pt(); // error：这里不是创建对象 */

    // 正确写法一：
    /* Point pt; // ok，调用 Point() */

    // 正确写法二：
    // 使用大括号初始化，也会调用无参构造函数 Point()
    Point pt{};

    // 因为 m_x 和 m_y 是 private，类外不能直接访问
    /* pt.m_x = 1; */
    /* pt.m_y = 2; */

    // 如果类中提供了 public 的 setX / setY 函数，就可以通过函数间接修改
    /* pt.setX(1); */
    /* pt.setY(2); */

    // 调用成员函数打印 pt 对象中的 m_x 和 m_y
    pt.print();
    
    cout << "------" << endl;
    
    // 创建对象时传入两个参数，会调用 Point(int, int)
    /* Point pt2(10,20); */
    // 使用大括号初始化，效果类似，也会调用 Point(int, int)
    Point pt2{10, 20};
    // 打印 pt2 的成员变量
    pt2.print();
}


class MyClass
{
public:
    // 可以显式地把无参构造函数写出来
    //
    // 普通写法：
    /* MyClass(){} */

    // = default 表示让编译器生成默认的无参构造函数
    // 这是一种更简洁的写法
    MyClass() = default;

    // 增加一个有参构造函数
    MyClass(int data)
    {
        m_data = data;
    }

    // 这里是 public 成员变量
    // 所以类外可以直接访问
    int m_data;
};

void test2()
{   
    // 如果类中没有写任何构造函数，编译器会自动生成无参构造函数
    //
    // 但是如果类中已经写了一个有参构造函数，
    // 编译器就不会再自动生成无参构造函数。
    //
    // 所以如果没有写 MyClass() = default;
    // 下面这行代码就会报错。
    MyClass obj; // 会调用无参构造函数 MyClass()
    
    // 使用一个整数创建对象，会调用 MyClass(int)
    MyClass obj2{10};
}


int main(int argc, char *argv[])
{
    // test1();
    test2();
    return 0;
}

