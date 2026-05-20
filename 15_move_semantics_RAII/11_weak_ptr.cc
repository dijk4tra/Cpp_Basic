#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

/**
 * weak_ptr：弱引用智能指针。
 *
 * weak_ptr 是 shared_ptr 的辅助类型：
 *      它可以观察 shared_ptr 管理的对象，
 *      但不拥有该对象，也不会增加引用计数。
 *
 * 作用：
 *      1. 配合 shared_ptr 使用，观察资源是否还存在。
 *      2. 通过 lock() 临时提升为 shared_ptr，从而安全访问资源。
 *      3. 用于解决 shared_ptr 之间的循环引用问题。
 *
 * 注意：
 *      weak_ptr 不能直接访问资源，
 *      必须先通过 lock() 转换为 shared_ptr。
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

    // 析构函数：用于观察 Point 对象何时被释放
    ~Point()
    {
        cout << "~Point()" << endl;
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


// weak_ptr 的基本使用
void test1()
{
    // sp 是 shared_ptr，拥有 Point{1,2} 的资源所有权
    shared_ptr<Point> sp{new Point{1,2}};

    // weak_ptr 通常由 shared_ptr 初始化
    // wp 只观察 sp 管理的资源，不会增加引用计数
    weak_ptr<Point> wp = sp;

    // shared_ptr 的引用计数仍然是 1
    cout << sp.use_count() << endl;

    // weak_ptr::use_count() 返回它所观察资源的 shared_ptr 引用计数
    // 这里仍然是 1，说明 weak_ptr 不增加引用计数
    cout << wp.use_count() << endl;

    cout << "------" << endl;

    // weak_ptr 不能直接访问资源
    /* wp->print();//error */

    // 必须先通过 lock() 转换为 shared_ptr，才能访问资源
    // 如果资源仍然存在，lock() 返回有效的 shared_ptr；
    // 如果资源已经释放，lock() 返回空的 shared_ptr。
    weak_ptr<Point> wp2;
    if(auto sp2 = wp.lock()){
    /* if(wp2.lock()){ */
        cout << "转换成功"<< endl;

        // sp2 是由 wp.lock() 得到的 shared_ptr，
        // 在 sp2 存活期间，资源引用计数会临时增加
        sp2->print();
    }else{
        cout << "转换失败" << endl;
    }

    cout << "----" << endl;

    // reset() 会让 sp 放弃原来管理的 Point{1,2}，
    // 并改为管理新的 Point{3,4}。
    //
    // 原来的 Point{1,2} 没有其他 shared_ptr 拥有，
    // 因此会被立即释放。
    sp.reset(new Point{3,4});

    // wp 仍然观察原来的控制块，
    // 由于原来的资源已经释放，所以 expired() 返回 true。
    cout << wp.expired() << endl;
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}