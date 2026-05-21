#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

/**
 * weak_ptr：弱引用智能指针
 *
 * 1. weak_ptr 是什么？
 *
 *    weak_ptr 是 shared_ptr 的辅助类型。
 *
 *    它可以观察 shared_ptr 管理的对象，
 *    但是不拥有该对象。
 *
 *    也就是说：
 *    weak_ptr 不会使资源的 shared_ptr 引用计数加 1。
 *
 *
 * 2. weak_ptr 的作用
 *
 *    1）观察资源是否还存在
 *
 *       weak_ptr 可以通过 expired() 判断资源是否已经释放。
 *
 *       如果 expired() 返回 true，
 *       表示资源已经不存在。
 *
 *       如果 expired() 返回 false，
 *       表示资源还存在。
 *
 *
 *    2）安全访问资源
 *
 *       weak_ptr 不能直接访问资源。
 *
 *       如果想访问资源，
 *       必须先调用 lock()。
 *
 *       lock() 会尝试将 weak_ptr 临时提升为 shared_ptr。
 *
 *       - 如果资源仍然存在，lock() 返回一个有效的 shared_ptr
 *       - 如果资源已经释放，lock() 返回一个空的 shared_ptr
 *
 *
 *    3）解决 shared_ptr 循环引用问题
 *
 *       当两个对象互相用 shared_ptr 持有对方时，
 *       引用计数无法归零，会导致内存泄漏。
 *
 *       可以将其中一方改为 weak_ptr，
 *       因为 weak_ptr 不增加引用计数，
 *       从而打破循环引用。
 *
 *
 * 3. weak_ptr 与 shared_ptr 的关系
 *
 *    shared_ptr 表示拥有资源。
 *
 *    weak_ptr 表示观察资源。
 *
 *    weak_ptr 不负责释放资源，
 *    资源的释放仍然由 shared_ptr 的引用计数决定。
 *
 *
 * 4. weak_ptr 不能直接解引用
 *
 *    weak_ptr 不重载 operator-> 和 operator* 来直接访问资源。
 *
 *    所以下面的写法是错误的：
 *
 *    weak_ptr<Point> wp;
 *    wp->print();     // error
 *
 *    正确方式：
 *
 *    if(auto sp = wp.lock())
 *    {
 *        sp->print();
 *    }
 *
 *    这样可以保证访问资源时，
 *    资源在当前作用域内仍然有效。
 */

class Point
{
public:
    /**
     * Point 的有参构造函数
     *
     * 使用 x 和 y 初始化两个坐标。
     */
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {

    }

    /**
     * Point 的析构函数
     *
     * 当 Point 对象被释放时调用。
     *
     * 这里打印 "~Point()"，
     * 方便观察 shared_ptr 释放资源的时机。
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

private:
    int m_x;
    int m_y;
};


// weak_ptr 的基本使用
void test1()
{
    /**
     * sp 是 shared_ptr。
     *
     * new Point{1,2} 在堆上创建一个 Point 对象。
     *
     * sp 接管该资源，
     * 拥有 Point{1,2} 的资源所有权。
     *
     * 此时只有 sp 一个 shared_ptr 管理该资源，
     * 所以 shared_ptr 引用计数为 1。
     */
    shared_ptr<Point> sp{new Point{1,2}};

    /**
     * weak_ptr 通常由 shared_ptr 初始化。
     *
     * weak_ptr<Point> wp = sp;
     *
     * 表示：
     * wp 观察 sp 管理的资源。
     *
     * 注意：
     * wp 不拥有资源，
     * 不会增加 shared_ptr 的引用计数。
     */
    weak_ptr<Point> wp = sp;

    /**
     * shared_ptr::use_count()
     *
     * 返回当前资源的 shared_ptr 引用计数。
     *
     * 因为目前只有 sp 一个 shared_ptr 拥有资源，
     * 所以结果是 1。
     */
    cout << sp.use_count() << endl;

    /**
     * weak_ptr::use_count()
     *
     * 返回它所观察资源的 shared_ptr 引用计数。
     *
     * 由于 weak_ptr 本身不增加引用计数，
     * 所以这里结果仍然是 1。
     */
    cout << wp.use_count() << endl;

    cout << "------" << endl;

    /**
     * weak_ptr 不能直接访问资源。
     *
     * 因为 weak_ptr 不拥有资源，
     * 它观察的对象可能已经被释放。
     *
     * 所以下面这种直接访问方式是错误的。
     */
    /* wp->print();//error */

    /**
     * 必须先通过 lock() 转换为 shared_ptr，
     * 才能安全访问资源。
     *
     * weak_ptr<Point> wp2;
     *
     * wp2 是一个空的 weak_ptr，
     * 没有观察任何 shared_ptr 控制块。
     *
     * 如果调用 wp2.lock()，
     * 会得到一个空的 shared_ptr。
     */
    weak_ptr<Point> wp2;

    /**
     * wp.lock()
     *
     * 尝试将 weak_ptr 临时提升为 shared_ptr。
     *
     * 如果 wp 观察的资源仍然存在，
     * lock() 返回一个有效的 shared_ptr。
     *
     * 如果资源已经释放，
     * lock() 返回一个空的 shared_ptr。
     *
     *
     * if(auto sp2 = wp.lock())
     *
     * 这里利用了 shared_ptr 可以转换为 bool 的特性：
     * - 如果 sp2 非空，条件为 true
     * - 如果 sp2 为空，条件为 false
     */
    if(auto sp2 = wp.lock())
    /* if(wp2.lock()) */
    {
        cout << "转换成功"<< endl;

        /**
         * sp2 是由 wp.lock() 得到的 shared_ptr。
         *
         * 在 sp2 存活期间，
         * 它也共享同一块 Point 资源，
         * 所以 shared_ptr 引用计数会临时增加。
         *
         * 因为 sp2 是 shared_ptr，
         * 所以可以通过 sp2->print() 安全访问资源。
         */
        sp2->print();

        /**
         * 当前 if 语句块结束时，
         * sp2 析构，
         * 引用计数会减 1。
         */
    }
    else
    {
        /**
         * 如果 lock() 返回空 shared_ptr，
         * 说明 weak_ptr 观察的资源已经不存在，
         * 或者 weak_ptr 本身就是空的。
         */
        cout << "转换失败" << endl;
    }

    cout << "----" << endl;

    /**
     * reset() 会让 sp 放弃原来管理的资源，
     * 并改为管理新的资源。
     *
     * sp.reset(new Point{3,4});
     *
     * 执行过程：
     *
     * 1. sp 先放弃原来管理的 Point{1,2}
     *
     *    原来的 Point{1,2} 没有其他 shared_ptr 拥有。
     *    weak_ptr wp 只是观察者，不增加引用计数。
     *
     *    因此原来的 shared_ptr 引用计数变为 0，
     *    Point{1,2} 会被立即释放。
     *
     * 2. sp 接管新的 Point{3,4}
     *
     *    此后 sp 管理的是新的资源。
     */
    sp.reset(new Point{3,4});

    /**
     * wp 仍然观察原来的控制块。
     *
     * 但是原来的 Point{1,2} 已经释放，
     * 所以 wp.expired() 返回 true。
     *
     * expired() 的含义：
     * - true：资源已经释放
     * - false：资源仍然存在
     *
     * cout 打印 bool 值时：
     * - true 通常打印为 1
     * - false 通常打印为 0
     */
    cout << wp.expired() << endl;

    /**
     * test1 结束时：
     *
     * sp 当前管理的是新的 Point{3,4}。
     * sp 析构后，
     * Point{3,4} 的引用计数变为 0，
     * 因此 Point{3,4} 被释放。
     *
     * wp 和 wp2 是 weak_ptr，
     * 它们析构时不会释放 Point 资源。
     */
}

int main(int argc, char * argv[])
{
    test1();

    return 0;
}