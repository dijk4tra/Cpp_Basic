#include <iostream>
#include <memory>

using namespace std;

/*
 * 智能指针的误用：
 *
 * 典型问题：
 *      将同一个原始指针交给多个彼此独立的 shared_ptr 管理。
 *
 * 后果：
 *      每个 shared_ptr 都会创建自己的控制块，
 *      每个控制块都认为自己拥有该资源。
 *      当这些 shared_ptr 析构时，同一块资源可能被释放多次，
 *      从而导致未定义行为。
 *
 * 正确方式：
 *      共享资源时，应通过已有 shared_ptr 进行拷贝或赋值，
 *      而不是重新用裸指针构造 shared_ptr。
 *
 * 如果需要在类的成员函数中返回管理当前对象 this 的 shared_ptr，
 * 应继承 std::enable_shared_from_this<T>，
 * 并使用 shared_from_this()。
 */

// 辅助类：enable_shared_from_this 用于安全地从 this 获取 shared_ptr
class Point : public enable_shared_from_this<Point>
{
public:
    // 构造函数：初始化 Point 的两个坐标
    Point(int x, int y)
        : m_x(x), m_y(y)
    {
    }

    // 析构函数：用于观察对象何时被释放
    ~Point()
    {
        cout << "~Point()" << endl;
    }

    // 打印 Point 对象的坐标
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

    // 将另一个 Point 的坐标累加到当前对象上，
    // 并返回一个共享当前对象所有权的 shared_ptr
    // Point *addPoint(Point *pt)
    shared_ptr<Point> addPoint(Point *pt)
    {
        m_x += pt->m_x;
        m_y += pt->m_y;

        // return this;
        // 如果返回裸指针 this，调用者可能再用它创建 shared_ptr，
        // 从而导致同一个对象被多个控制块管理。

        // return shared_ptr<Point>{this};
        // 错误：直接用 this 构造 shared_ptr 会创建新的控制块，
        // 与原来管理当前对象的 shared_ptr 不是同一个引用计数。

        // 正确：shared_from_this() 返回与已有 shared_ptr 共享控制块的 shared_ptr。
        // 前提：当前对象必须已经由 shared_ptr 管理。
        return shared_from_this();
    }

private:
    int m_x;
    int m_y;
};

void test5()
{
    // sp 管理 Point(1,2)，并建立对应的 shared_ptr 控制块
    shared_ptr<Point> sp(new Point(1,2));

    // sp2 管理另一个 Point(3,4)
    shared_ptr<Point> sp2(new Point(3,4));

    // addPoint 内部使用 shared_from_this()，
    // 因此返回的 shared_ptr 与 sp 共享同一个控制块
    shared_ptr<Point> sp3(sp->addPoint(sp2.get()));

    // sp 和 sp3 共享同一个 Point 对象，引用计数为 2
    cout << sp3.use_count() << endl;
    cout << sp.use_count() << endl;

    // 当前对象坐标已经累加了 sp2 指向对象的坐标
    sp3->print();
}


// shared_ptr 的错误用法示例
void test1()
{
    // up1 正确接管 new 出来的 Point 对象
    shared_ptr<Point> up1{new Point{1, 2}};

    // 错误：通过 get() 取出裸指针后，又用它创建新的 shared_ptr
    // up1 和 up2 会拥有不同的控制块，最终可能重复释放同一对象
    shared_ptr<Point> up2{up1.get()};

    up1->print();
    up2->print();
}

// shared_ptr 的错误用法示例
// 错误：使用 get() 获取原始指针后，用它创建另一个 shared_ptr
// 问题：同一个原始指针被两个独立的 shared_ptr 管理，每个都认为自己拥有该对象
// 后果：当两个智能指针生命周期结束时，会导致同一个对象被 delete 两次，引发未定义行为
void test2()
{
    // 创建第一个 shared_ptr，管理 Point 对象
    shared_ptr<Point> up1{new Point{1, 2}};

    // 错误：使用 up1.get() 获取原始指针，并以此创建第二个 shared_ptr
    // 这会导致 up1 和 up2 各自维护独立的引用计数，通常都为 1
    // 两个智能指针都认为自己是对象的唯一所有者
    shared_ptr<Point> up2{up1.get()};

    // 调用对象方法，此时对象还未被销毁
    up1->print();
    up2->print();

    // 函数结束时，up2 和 up1 都会尝试释放同一个 Point 对象，
    // 从而造成重复 delete，属于未定义行为
}

void test3()
{
    // 原始指针 p 指向一个 Point 对象
    Point *p = new Point{1, 2};

    // up1 接管 p，创建一个控制块
    shared_ptr<Point> up1{p};

    // 错误：up2 再次接管同一个裸指针 p，创建另一个控制块
    // 这不是共享所有权，而是两个 shared_ptr 分别独立管理同一资源
    shared_ptr<Point> up2{p};

    up1->print();
    up2->print();

    // 函数结束时会发生重复释放
}

void test4()
{
    // 与 test3 相同的错误模式：
    // 同一个裸指针 p 被两个独立的 shared_ptr 管理
    Point *p = new Point{1, 2};

    shared_ptr<Point> up1{p};
    shared_ptr<Point> up2{p};

    up1->print();
    up2->print();

    // 正确共享方式应当是：
    // shared_ptr<Point> up2 = up1;
    // 这样 up1 和 up2 才会共享同一个控制块和引用计数
}

int main(int argc, char const *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();
    return 0;
}