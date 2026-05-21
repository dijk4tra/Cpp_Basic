#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

/**
 * shared_ptr 的循环引用问题
 *
 * 1. 什么是循环引用？
 *
 *    当两个对象内部都使用 shared_ptr 指向对方时，
 *    就会形成循环引用。
 *
 *    例如：
 *
 *    class Parent
 *    {
 *    public:
 *        shared_ptr<Child> m_spChild;
 *    };
 *
 *    class Child
 *    {
 *    public:
 *        shared_ptr<Parent> m_spParent;
 *    };
 *
 *    如果 Parent 对象中保存 shared_ptr<Child>，
 *    Child 对象中又保存 shared_ptr<Parent>，
 *    那么二者会互相持有对方。
 *
 *
 * 2. 循环引用带来的问题
 *
 *    shared_ptr 通过引用计数判断资源是否应该释放。
 *
 *    只有当某块资源的引用计数变为 0 时，
 *    资源才会被释放。
 *
 *    如果两个对象互相使用 shared_ptr 持有对方，
 *    即使外部的 shared_ptr 已经销毁，
 *    两个对象内部的 shared_ptr 仍然互相维持对方的引用计数。
 *
 *    结果就是：
 *    - Parent 的引用计数无法变为 0
 *    - Child 的引用计数无法变为 0
 *    - 两个对象都不会析构
 *    - 最终造成内存泄漏
 *
 *
 * 3. 如何解决循环引用？
 *
 *    使用 weak_ptr 打破循环引用。
 *
 *    weak_ptr 是一种弱引用：
 *    - 不拥有资源
 *    - 不会增加 shared_ptr 的引用计数
 *    - 不能直接访问资源
 *    - 需要通过 lock() 转换成 shared_ptr 后才能访问资源
 *
 *
 * 4. 常见设计方式
 *
 *    在双向关系中，
 *    一方使用 shared_ptr 表示拥有关系，
 *    另一方使用 weak_ptr 表示观察关系。
 *
 *    例如：
 *    - Child 使用 shared_ptr<Parent> 表示持有 Parent
 *    - Parent 使用 weak_ptr<Child> 表示观察 Child
 *
 *    这样可以避免双方互相拥有，
 *    从而避免循环引用。
 */

class Child;

/**
 * Parent 类
 *
 * 注意：
 * 这里先声明 Child 类，
 * 再在 Parent 中使用 weak_ptr<Child>。
 *
 * 这是因为 Parent 和 Child 之间存在互相引用关系，
 * 需要先做前向声明：
 *
 * class Child;
 */
class Parent
{
public:
    /**
     * 如果这里写成：
     *
     * shared_ptr<Child> m_spChild;
     *
     * 那么 Parent 会通过 shared_ptr 持有 Child。
     *
     * 而 Child 中又有：
     * shared_ptr<Parent> m_spParent;
     *
     * 这样 Parent 和 Child 就会互相持有 shared_ptr，
     * 形成循环引用。
     */
    /* shared_ptr<Child> m_spChild; */

    /**
     * 改成 weak_ptr<Child> 后：
     *
     * Parent 只是“观察” Child，
     * 不拥有 Child。
     *
     * 因此：
     * parentPtr->m_spChild = childPtr;
     *
     * 这句代码不会增加 Child 对象的引用计数。
     *
     * weak_ptr 的作用：
     * 1. 可以观察 shared_ptr 管理的资源
     * 2. 不增加资源的引用计数
     * 3. 可以用来打破 shared_ptr 循环引用
     */
    weak_ptr<Child> m_spChild;
};

class Child
{
public:
    /**
     * Child 中使用 shared_ptr<Parent>。
     *
     * 这里表示 Child 对 Parent 具有共享所有权。
     *
     * 当执行：
     * childPtr->m_spParent = parentPtr;
     *
     * m_spParent 会和 parentPtr 共享同一个 Parent 对象，
     * 因此 Parent 对象的引用计数会加 1。
     */
    shared_ptr<Parent> m_spParent;
};

void test1()
{
    /**
     * 创建 shared_ptr<Parent> 对象 parentPtr。
     *
     * new Parent{} 在堆上创建一个 Parent 对象。
     * parentPtr 接管这个 Parent 对象。
     *
     * 此时只有 parentPtr 管理 Parent 对象，
     * 所以 Parent 对象的引用计数为 1。
     */
    shared_ptr<Parent> parentPtr{new Parent{}};

    /**
     * 创建 shared_ptr<Child> 对象 childPtr。
     *
     * new Child{} 在堆上创建一个 Child 对象。
     * childPtr 接管这个 Child 对象。
     *
     * 此时只有 childPtr 管理 Child 对象，
     * 所以 Child 对象的引用计数为 1。
     */
    shared_ptr<Child> childPtr{ new Child{} };

    /**
     * 获取初始引用计数。
     *
     * parentPtr.use_count() 表示：
     * 当前有多少个 shared_ptr 共享 Parent 对象。
     *
     * childPtr.use_count() 表示：
     * 当前有多少个 shared_ptr 共享 Child 对象。
     */
    cout << "ParentPtr count:" << parentPtr.use_count() << endl;
    cout << "childPtr count:" << childPtr.use_count() << endl;

    cout << "-----" << endl;

    /**
     * 建立 Parent 到 Child 的关联。
     *
     * parentPtr->m_spChild = childPtr;
     *
     * m_spChild 是 weak_ptr<Child>。
     *
     * weak_ptr 可以由 shared_ptr 赋值而来，
     * 表示 weak_ptr 观察 shared_ptr 所管理的资源。
     *
     * 但是 weak_ptr 不拥有资源，
     * 不会增加 Child 对象的引用计数。
     *
     * 所以这句执行后：
     * childPtr.use_count() 仍然是 1。
     */
    parentPtr->m_spChild = childPtr;

    /**
     * 建立 Child 到 Parent 的关联。
     *
     * childPtr->m_spParent = parentPtr;
     *
     * m_spParent 是 shared_ptr<Parent>。
     *
     * 这表示 Child 对 Parent 也持有一份共享所有权。
     *
     * 所以这句执行后：
     * Parent 对象的引用计数会从 1 变成 2。
     *
     * 两份引用分别来自：
     * 1. 局部变量 parentPtr
     * 2. childPtr 对象内部的 m_spParent
     */
    childPtr->m_spParent = parentPtr;

    /**
     * 再次查看引用计数。
     *
     * ParentPtr count 应该为 2：
     * - parentPtr 持有一份
     * - childPtr->m_spParent 持有一份
     *
     * childPtr count 应该仍然为 1：
     * - 只有局部变量 childPtr 持有一份
     * - parentPtr->m_spChild 是 weak_ptr，不增加引用计数
     */
    cout << "ParentPtr count:" << parentPtr.use_count() << endl;
    cout << "childPtr count:" << childPtr.use_count() << endl;

    /**
     * test1 结束时的释放过程：
     *
     * 局部对象会按照创建顺序的逆序析构。
     *
     * 1. childPtr 先析构
     *
     *    Child 对象的引用计数从 1 变成 0。
     *    因为没有其他 shared_ptr 持有 Child，
     *    所以 Child 对象被释放。
     *
     * 2. Child 对象释放时，
     *    它的成员 m_spParent 也会析构。
     *
     *    m_spParent 析构后，
     *    Parent 对象的引用计数从 2 变成 1。
     *
     * 3. parentPtr 再析构
     *
     *    Parent 对象的引用计数从 1 变成 0。
     *    Parent 对象被释放。
     *
     * 4. Parent 对象释放时，
     *    它的成员 m_spChild 也会析构。
     *
     *    m_spChild 是 weak_ptr，
     *    它本来就不拥有 Child，
     *    所以不会影响 Child 的释放。
     *
     * 因此使用 weak_ptr 后，
     * Parent 和 Child 都可以正常析构，
     * 不会产生循环引用导致的内存泄漏。
     */
}

int main(int argc, char * argv[])
{
    test1();

    return 0;
}