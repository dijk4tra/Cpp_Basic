#include <iostream>

using std::cout;
using std::endl;

/*
 * 如果类中同时提供 const 版本和非 const 版本的成员函数：
 * 1. 普通对象优先调用非 const 版本成员函数
 * 2. const 对象只能调用 const 版本成员函数
 *
 * 如果类中只有非 const 版本成员函数：
 * 1. 普通对象可以调用非 const 版本成员函数
 * 2. const 对象无法调用，因为隐含的 this 类型不匹配
 *
 * 如果类中只有 const 版本成员函数：
 * 1. 普通对象可以调用
 * 2. const 对象也可以调用
 */

class Point
{
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    // 拷贝构造函数
    Point(const Point & rhs)
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    {
        cout << "Point(const Point &)" << endl;
    }

    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

    // const 成员函数
    void show() const
    {
        cout << "show() const" << endl;
    }

    /* void show() */
    /* { */
    /*     cout << "show()" << endl; */
    /* } */ 
    
/* private: */
    int m_x;
    int m_y;
};

void test1()
{
    int num = 1;
    const int num2 = 2;

    Point pt{1, 2};
    pt.show();

    cout << "--------" << endl;

    const Point pt2{3, 4};
    pt2.show();
}


// 对象数组
// 构建对象数组的方式：
// 1. 通过左值对象构建数组
// 2. 通过右值对象构建数组
// 3. 通过初始化列表简写构建数组
void test2()
{
    // int arr[3] = {1, 2, 3};

    Point pt1{1, 1};
    Point pt2{2, 2};
    Point pt3{3, 3};

    // 左值对象作为数组元素时，会调用拷贝构造函数
    Point pts[3] = {pt1, pt2, pt3};

    /* pts[0].m_x = 10; */

    pts[0].print();
}

// 使用右值对象构建数组
void test3()
{
    Point pts[] = {
        Point{1, 1},
        Point{2, 2},
        Point{3, 3}
    };

    pts[0].print();
}

void test4()
{
    // 使用初始化列表进行简写
    Point pts[] = {
        {1, 1},
        {2, 2},
        {3, 3}
    };

    pts[0].print();

    cout << "----->" << endl;

    for(int i = 0; i < 3; ++i){
        pts[i].print();
    }

    cout << "----->" << endl;

    // foreach 遍历，也称增强 for 循环或范围 for 循环
    for(Point pt : pts){
        pt.print();
    }

    cout << "----->" << endl;

    // 使用 auto 关键字进行类型自动推导
    for(auto pt : pts){
        pt.print();
    }

    cout << "----->" << endl;

    // 使用引用遍历，避免拷贝对象
    for(auto & pt : pts){
        pt.print();
    }
}

// 栈对象与堆对象
void test5()
{
    // 栈对象
    Point pt1{1, 1};

    // 通过“对象.成员”的方式访问
    pt1.print();

    Point* p = &pt1;

    // 通过“指针->成员”的方式访问
    p->print();


    // 堆对象
    // new int{1}
    // new int[]{1}
    Point * p2 = new Point{1, 2};

    p2->print();

    delete p2;
    p2 = nullptr;
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    test5();

    return 0;
}