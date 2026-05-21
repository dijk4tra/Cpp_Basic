#include <iostream>
#include <memory>

using namespace std;

/**
 * 智能指针的误用
 *
 * 1. 常见错误本质
 *
 *    很多智能指针误用形式看起来不同，
 *    但是本质类似：
 *
 *    将同一个原始指针交给多个独立的智能指针对象管理。
 *
 *    例如：
 *
 *    Point *p = new Point{1, 2};
 *    shared_ptr<Point> sp1{p};
 *    shared_ptr<Point> sp2{p};
 *
 *    或者：
 *
 *    shared_ptr<Point> sp1{new Point{1, 2}};
 *    shared_ptr<Point> sp2{sp1.get()};
 *
 *
 * 2. 为什么会出错？
 *
 *    shared_ptr 正确共享资源的前提是：
 *    多个 shared_ptr 必须共享同一个控制块。
 *
 *    控制块中保存引用计数。
 *
 *    如果通过 shared_ptr 的拷贝构造或拷贝赋值共享资源：
 *
 *    shared_ptr<Point> sp2 = sp1;
 *
 *    那么 sp1 和 sp2 会共享同一个控制块，
 *    引用计数会正确增加。
 *
 *
 *    但是如果用同一个裸指针分别构造多个 shared_ptr：
 *
 *    shared_ptr<Point> sp1{p};
 *    shared_ptr<Point> sp2{p};
 *
 *    那么 sp1 和 sp2 会分别创建自己的控制块。
 *
 *    结果就是：
 *    - sp1 认为自己独占资源
 *    - sp2 也认为自己独占资源
 *    - 两个 shared_ptr 的引用计数都为 1
 *    - 析构时会对同一块资源 delete 两次
 *
 *    这会导致 double free，属于未定义行为。
 *
 *
 * 3. get() 的风险
 *
 *    get() 只能用于“观察”智能指针内部的裸指针。
 *
 *    get() 返回的指针：
 *    - 不应该手动 delete
 *    - 不应该再交给另一个智能指针管理
 *
 *    否则就会破坏智能指针的所有权管理。
 *
 *
 * 4. enable_shared_from_this
 *
 *    有时需要在类的成员函数中返回一个指向当前对象的 shared_ptr。
 *
 *    错误写法：
 *
 *    return shared_ptr<Point>{this};
 *
 *    这样会用 this 创建一个新的 shared_ptr 控制块，
 *    与原来管理当前对象的 shared_ptr 不是同一个控制块。
 *    最终仍然可能导致重复释放。
 *
 *
 *    正确做法：
 *
 *    class Point : public enable_shared_from_this<Point>
 *
 *    然后在成员函数中调用：
 *
 *    return shared_from_this();
 *
 *    shared_from_this() 会返回一个与原有 shared_ptr 共享控制块的 shared_ptr，
 *    这才是合法共享。
 *
 *
 * 5. 使用 shared_from_this() 的前提
 *
 *    当前对象必须已经被 shared_ptr 管理。
 *
 *    也就是说，
 *    不能对一个栈对象直接调用 shared_from_this()。
 *
 *    例如下面这样是错误的：
 *
 *    Point pt{1, 2};
 *    pt.shared_from_this();     // error，运行时可能抛异常
 *
 *    正确场景是：
 *
 *    shared_ptr<Point> sp{new Point{1, 2}};
 *    sp->shared_from_this();
 */


// 辅助类：enable_shared_from_this
//
// 如果一个类希望在成员函数内部安全地获得
// “共享当前对象所有权”的 shared_ptr，
// 就可以继承 enable_shared_from_this<T>。
class Point : public enable_shared_from_this<Point>
{
public:
    /**
     * Point 的有参构造函数
     *
     * 使用 x 和 y 初始化两个坐标。
     */
    Point(int x, int y)
        : m_x(x), m_y(y)
    {
    }

    /**
     * Point 的析构函数
     *
     * 打印 "~Point()"，
     * 用来观察对象什么时候被释放。
     *
     * 如果智能指针误用导致 double free，
     * 可能会看到异常行为，甚至程序崩溃。
     */
    ~Point()
    {
        cout << "~Point()" << endl;
    }

    /**
     * 打印 Point 对象的坐标。
     */
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

    /**
     * addPoint
     *
     * 参数：
     * Point *pt
     *
     * pt 是一个裸指针，
     * 这里只是用它访问另一个 Point 对象的坐标。
     *
     * 注意：
     * addPoint 并不接管 pt 指向的资源，
     * 也不会释放 pt。
     *
     * 当前函数的作用：
     * 将 pt 的坐标加到当前对象上，
     * 然后返回一个 shared_ptr<Point>，
     * 让返回值与当前对象共享所有权。
     */
    // Point *addPoint(Point *pt)
    shared_ptr<Point> addPoint(Point *pt)
    {
        /**
         * 修改当前对象的坐标。
         *
         * 当前对象就是调用该成员函数的对象。
         *
         * 例如：
         * sp->addPoint(sp2.get());
         *
         * 那么当前对象就是 sp 管理的 Point。
         */
        m_x += pt->m_x;
        m_y += pt->m_y;

        /**
         * 早期可能会考虑返回 this：
         *
         * return this;
         *
         * 如果返回类型是 Point*，
         * 这只是返回当前对象地址，
         * 不涉及智能指针所有权。
         *
         * 但是调用者如果再用这个裸指针构造 shared_ptr，
         * 就可能导致重复释放。
         */
        // return this;

        /**
         * 错误写法：
         *
         * return shared_ptr<Point>{this};
         *
         * this 指向当前对象。
         *
         * 如果当前对象本来已经由某个 shared_ptr 管理，
         * 再用 this 构造新的 shared_ptr，
         * 就会创建一个新的控制块。
         *
         * 这样返回的 shared_ptr 与原来的 shared_ptr
         * 并没有共享引用计数。
         *
         * 最终两个控制块都会尝试释放同一个对象，
         * 导致 double free。
         */
        // return shared_ptr<Point>{this};

        /**
         * 正确写法：
         *
         * shared_from_this()
         *
         * 该函数来自 enable_shared_from_this<Point>。
         *
         * 它会返回一个 shared_ptr<Point>，
         * 并且这个 shared_ptr 与当前对象已有的 shared_ptr
         * 共享同一个控制块。
         *
         * 因此这是合法共享，
         * 不会产生多个控制块。
         */
        return shared_from_this();
    }

private:
    int m_x;
    int m_y;
};

void test5()
{
    /**
     * sp 管理一个 Point{1,2}。
     *
     * 因为 Point 继承了 enable_shared_from_this<Point>，
     * 所以当 Point 对象被 shared_ptr 管理后，
     * 它内部就可以通过 shared_from_this()
     * 返回共享同一控制块的 shared_ptr。
     */
    shared_ptr<Point> sp(new Point(1,2));

    /**
     * sp2 管理另一个 Point{3,4}。
     */
    shared_ptr<Point> sp2(new Point(3,4));

    /**
     * sp->addPoint(sp2.get())
     *
     * sp2.get() 返回 sp2 管理的裸指针。
     *
     * 这里只是把裸指针作为参数传进去，
     * 用来读取 Point{3,4} 的坐标。
     *
     * 注意：
     * addPoint 不会保存这个裸指针，
     * 也不会用它创建新的智能指针，
     * 所以这里使用 get() 是安全的观察行为。
     *
     *
     * addPoint 内部调用 shared_from_this()，
     * 返回一个 shared_ptr<Point>。
     *
     * 这个返回值与 sp 共享同一个 Point{1,2} 对象，
     * 并共享同一个控制块。
     *
     * 所以 sp3 是合法共享。
     */
    shared_ptr<Point> sp3(sp->addPoint(sp2.get()));

    /**
     * 此时 sp 和 sp3 共享同一个 Point 对象。
     *
     * 所以二者的 use_count() 都应该是 2。
     */
    cout << sp3.use_count() << endl;
    cout << sp.use_count() << endl;

    /**
     * addPoint 已经把 sp2 的坐标加到了 sp 管理的对象上。
     *
     * 原来 sp 管理的是 Point{1,2}，
     * sp2 管理的是 Point{3,4}。
     *
     * 执行 addPoint 后，
     * sp 管理的对象变为 Point{4,6}。
     *
     * sp3 与 sp 共享同一个对象，
     * 所以 sp3->print() 打印 4 6。
     */
    sp3->print();

    /**
     * test5 结束时：
     *
     * sp3 析构，Point{4,6} 的引用计数从 2 变成 1。
     *
     * sp2 析构，Point{3,4} 的引用计数变成 0，
     * Point{3,4} 被释放。
     *
     * sp 析构，Point{4,6} 的引用计数变成 0，
     * Point{4,6} 被释放。
     */
}


// shared_ptr 误用示例一
void test1()
{
    /**
     * up1 管理一个 Point{1,2}。
     *
     * up1 内部创建了一个控制块，
     * 引用计数为 1。
     */
    shared_ptr<Point> up1{new Point{1, 2}};

    /**
     * 错误：
     *
     * up1.get() 返回 up1 内部保存的裸指针。
     *
     * 然后用这个裸指针构造 up2。
     *
     * 这会导致 up2 创建一个新的控制块，
     * 而不是共享 up1 的控制块。
     *
     * 结果：
     * - up1 的引用计数是 1
     * - up2 的引用计数也是 1
     * - 二者都认为自己独占同一个 Point 对象
     */
    shared_ptr<Point> up2{up1.get()};

    /**
     * 此时对象暂时还存在，
     * 所以下面访问可能看起来正常。
     *
     * 但是函数结束时会发生重复释放。
     */
    up1->print();
    up2->print();

    /**
     * test1 结束时：
     *
     * up2 先析构，delete Point{1,2}。
     * up1 再析构，再次 delete 同一块内存。
     *
     * 这是未定义行为。
     */
}


// shared_ptr 误用示例二
//
// 错误示例：使用 get() 获取原始指针后，用它创建另一个 shared_ptr
//
// 问题：
// 同一个原始指针被两个独立的 shared_ptr 管理，
// 每个 shared_ptr 都认为自己拥有该对象。
//
// 当两个智能指针生命周期结束时，
// 会导致同一个对象被 delete 两次，引发未定义行为。
void test2()
{
    /**
     * 创建第一个 shared_ptr，
     * 管理 Point 对象。
     */
    shared_ptr<Point> up1{new Point{1, 2}};

    /**
     * 错误：
     *
     * 使用 up1.get() 获取原始指针，
     * 并以此创建第二个 shared_ptr。
     *
     * 这会导致 up1 和 up2 各自维护独立的控制块。
     *
     * 它们的引用计数都为 1，
     * 并没有形成真正的共享。
     */
    shared_ptr<Point> up2{up1.get()};

    /**
     * 调用对象方法。
     *
     * 此时对象还未被销毁，
     * 因此这两行代码可能暂时可以运行。
     *
     * 但是这掩盖了真正的问题：
     * 两个 shared_ptr 正在错误地管理同一块资源。
     */
    up1->print();
    up2->print();

    /**
     * 函数结束时：
     *
     * up2 先析构，将对象 delete。
     * 然后 up1 析构，再次 delete 同一个对象。
     *
     * 最终导致程序崩溃或其他未定义行为。
     */
}

void test3()
{
    /**
     * 创建裸指针 p，
     * 指向堆上的 Point{1,2}。
     */
    Point *p = new Point{1, 2};

    /**
     * 错误：
     *
     * 用同一个裸指针 p 构造 up1 和 up2。
     *
     * up1 会创建自己的控制块。
     * up2 也会创建自己的控制块。
     *
     * 两个控制块彼此独立，
     * 都认为自己拥有 p 指向的 Point 对象。
     */
    shared_ptr<Point> up1{p};
    shared_ptr<Point> up2{p};

    /**
     * 此时对象还存在，
     * 下面访问可能看起来正常。
     */
    up1->print();
    up2->print();

    /**
     * test3 结束时：
     *
     * up2 析构，释放 p 指向的对象。
     * up1 析构，再次释放同一个对象。
     *
     * 导致 double free。
     */
}

void test4()
{
    /**
     * test4 与 test3 本质相同。
     *
     * 都是将同一个裸指针 p
     * 分别交给两个 shared_ptr 管理。
     *
     * 这不是合法共享。
     */
    Point *p = new Point{1, 2};

    /**
     * up1 和 up2 分别创建独立控制块。
     */
    shared_ptr<Point> up1{p};
    shared_ptr<Point> up2{p};

    up1->print();
    up2->print();

    /**
     * 函数结束时同样会重复释放。
     */
}

int main(int argc, char const *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();

    /**
     * test5 是正确示例：
     *
     * 通过 enable_shared_from_this
     * 和 shared_from_this()
     * 在成员函数内部安全返回 shared_ptr。
     */
    test5();

    return 0;
}