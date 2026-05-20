#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

/*
 * shared_ptr 的循环引用问题：
 *
 * 当两个对象内部都使用 shared_ptr 指向对方时，
 * 双方的引用计数都不会降为 0，
 * 即使外部的 shared_ptr 已经销毁，资源也无法被释放，
 * 从而造成内存泄漏。
 *
 * 解决方式：
 *      使用 weak_ptr 打破循环引用。
 *
 * weak_ptr 的特点：
 *      - 不拥有资源
 *      - 不会使 shared_ptr 的引用计数加 1
 *      - 不能直接访问资源，需要先通过 lock() 转换为 shared_ptr
 *
 * 常见设计：
 *      在双向关系中，一方使用 shared_ptr 表示拥有关系，
 *      另一方使用 weak_ptr 表示观察关系。
 */

class Child;

class Parent
{
public:
    /* shared_ptr<Child> m_spChild; */
    // 如果这里使用 shared_ptr<Child>，
    // Parent 和 Child 会互相持有 shared_ptr，形成循环引用。
    //
    // 改用 weak_ptr<Child> 后，Parent 只是观察 Child，
    // 不会增加 Child 对象的引用计数。
    weak_ptr<Child> m_spChild;
};

class Child
{
public:
    // Child 使用 shared_ptr 持有 Parent，
    // 表示 Child 对 Parent 具有共享所有权。
    shared_ptr<Parent> m_spParent;
};

void test1()
{
    // parentPtr 管理 Parent 对象，引用计数为 1
    shared_ptr<Parent> parentPtr{new Parent{}};

    // childPtr 管理 Child 对象，引用计数为 1
    shared_ptr<Child> childPtr{ new Child{} };

    // 获取初始引用计数
    cout << "ParentPtr count:" << parentPtr.use_count() << endl;
    cout << "childPtr count:" << childPtr.use_count() << endl;

    cout << "-----" << endl;

    // 建立 Parent 到 Child 的关联
    // m_spChild 是 weak_ptr，因此不会增加 childPtr 的引用计数
    parentPtr->m_spChild = childPtr;

    // 建立 Child 到 Parent 的关联
    // m_spParent 是 shared_ptr，因此会增加 parentPtr 的引用计数
    childPtr->m_spParent = parentPtr;

    // parentPtr 的引用计数变为 2：
    //      一个来自局部变量 parentPtr
    //      一个来自 childPtr->m_spParent
    //
    // childPtr 的引用计数仍为 1：
    //      只有局部变量 childPtr 持有它
    //      parentPtr->m_spChild 是 weak_ptr，不增加引用计数
    cout << "ParentPtr count:" << parentPtr.use_count() << endl;
    cout << "childPtr count:" << childPtr.use_count() << endl;

    // test1 结束时：
    //      childPtr 先后析构时，Child 的引用计数归零，Child 被释放；
    //      Child 释放时，它内部的 m_spParent 析构，使 Parent 引用计数减 1；
    //      最终 Parent 的引用计数归零，Parent 也能被正常释放。
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}