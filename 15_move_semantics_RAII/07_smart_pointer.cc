#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;

/*
 * 智能指针：
 *      用对象的生命周期管理堆资源，避免手动 delete。
 *
 * 常见智能指针：
 *      auto_ptr：
 *          早期标准库中的智能指针，仅作了解；
 *          拷贝时会转移资源所有权，容易造成原指针失效；
 *          C++11 中已废弃，C++17 中被移除。
 *
 *      unique_ptr：
 *          独占所有权，同一时刻只能有一个 unique_ptr 管理资源；
 *          不允许拷贝，只允许移动。
 *
 *      shared_ptr：
 *          共享所有权，多个 shared_ptr 可以共同管理同一资源；
 *          内部通过引用计数判断何时释放资源。
 *
 *      weak_ptr：
 *          弱引用，不拥有资源；
 *          常用于配合 shared_ptr，解决循环引用问题。
 */

class Point
{
public:
    // 构造函数：初始化 Point 的两个坐标
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {

    }

    // 打印 Point 对象的坐标
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

private:
    int m_x;
    int m_y;
};


// auto_ptr 的基本使用
void test1()
{
    // auto_ptr 接管 new 出来的 Point 对象
    // 当 ap 离开作用域时，会自动释放该资源
    auto_ptr<Point> ap { new Point{1,2} };

    // 通过 operator-> 访问资源成员
    ap->print();

    // 通过 operator* 获取资源对象本身
    (*ap).print();

    // 通过 get() 获取底层原始指针
    // 注意：get() 不释放资源，也不转移所有权
    ap.get()->print();
}

void test2()
{
    // ap 独自管理 Point 资源
    auto_ptr<Point> ap { new Point{3,4} };
    ap->print();

    cout << "-----" << endl;

    // auto_ptr 的拷贝行为比较特殊：
    // 这里不是深拷贝资源，而是将资源所有权从 ap 转移给 ap2
    auto_ptr<Point> ap2 = ap;

    // ap2 现在拥有原来的 Point 资源
    ap2->print();

    cout << "-----" << endl;

    // 此时 ap 已经失去资源所有权，内部指针通常变为 nullptr
    // 再通过 ap 访问资源会出错，可能导致程序崩溃
    ap->print();// error 资源已经转移给其他智能指针
}


int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}