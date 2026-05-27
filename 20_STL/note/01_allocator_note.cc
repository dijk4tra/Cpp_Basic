#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/**
 * allocator 空间配置器
 *
 * allocator 是 C++ 标准库中的空间配置器模板类，
 * 主要负责“内存分配”和“内存释放”。
 *
 * 在 STL 容器中，容器内部需要频繁申请和释放内存。
 * 例如：
 * vector<int> vec;
 * 当 vector 容量不够时，
 * 就需要重新申请更大的内存空间。
 *
 * STL 将“内存管理”这一部分抽象出来，
 * 交给 allocator 来完成。
 *
 *
 * allocator 和 new/delete 的区别：
 *
 * 1. new
 *    new 会完成两件事：
 *    ·申请内存
 *    ·在这块内存上构造对象
 *
 *    例如：
 *    int * p = new int(1);
 *    可以理解为：
 *    1. 申请一块能存放 int 的内存
 *    2. 在这块内存上构造一个值为 1 的 int 对象
 *
 * 2. delete
 *    delete 也会完成两件事：
 *    ·调用对象的析构函数
 *    ·释放对象占用的内存
 *
 *
 * allocator 将这几个步骤拆开：
 *
 * 1. allocate
 *    只申请原始内存，
 *    不会构造对象。
 *
 * 2. construct
 *    在已经申请好的原始内存上构造对象。
 *
 * 3. destroy
 *    销毁已经构造好的对象，
 *    但不会释放内存。
 *
 * 4. deallocate
 *    释放之前申请的原始内存。
 *
 *
 * 注意：
 * allocate 得到的只是“原始内存”，
 * 此时内存中还没有真正的对象。
 *
 * 所以：
 * allocator<int> alloc;
 * int * p = alloc.allocate(1);
 *
 * 这之后不能直接使用 *p，
 * 因为 p 指向的内存中还没有构造 int 对象。
 *
 * 必须先调用：
 * alloc.construct(p, 2);
 *
 * 这之后，p 指向的内存中才有一个真正的 int 对象。
 */

void test1()
{
    // 使用 new 创建一个 int 对象
    // new int(1) 会完成两件事：
    // 1. 先申请一块能存放 int 的内存
    // 2. 再在该内存上构造一个值为 1 的 int 对象
    int * p1 = new int(1);

    // 输出 p1 指向对象的值
    cout << *p1 << endl;

    // 输出 p1 保存的地址
    // p1 是一个指针变量，
    // 它保存的是 new 申请到的那块内存的起始地址。
    cout << "p1:" << p1 << endl;
    
    cout << "----------" << endl;

    // 创建 int 类型的空间配置器对象
    // allocator<int> 表示：
    // 这个空间配置器将来申请和释放的内存，
    // 是用来存放 int 类型对象的。
    allocator<int> alloc;

    /**
     * allocate
     *
     * allocate(1) 只申请 1 个 int 大小的原始内存空间。
     *
     * 注意：
     * 此时只是申请了内存，
     * 还没有在这块内存上构造 int 对象。
     *
     * 所以此时不能直接写：
     * cout << *p2 << endl;
     *
     * 因为 p2 指向的内存中还没有一个真正可用的 int 对象。
     */
    int * p2 = alloc.allocate(1);

    /**
     * construct
     *
     * construct(p2, 2) 的作用是：
     * 在 p2 指向的原始内存上构造一个 int 对象，
     * 并且把这个 int 对象初始化为 2。
     *
     * 这一步之后，
     * p2 才指向一个真正可用的 int 对象。
     */
    alloc.construct(p2, 2); 

    // 输出 p2 指向对象的值
    // 因为前面已经调用 construct 构造了对象，
    // 所以这里可以正常解引用 p2。
    cout << *p2 << endl;

    // 输出 p2 保存的地址
    cout << "p2:" << p2 << endl;

    /**
     * destroy
     *
     * destroy(p2) 只负责调用 p2 指向对象的析构过程。
     *
     * 注意：
     * destroy 只是“销毁对象”，
     * 不会释放 p2 指向的内存。
     *
     * 对于 int 这种内置类型来说，
     * 析构动作非常简单，
     * 甚至可以理解成没有明显效果。
     *
     * 但是从流程上要理解：
     * 只要对象是通过 construct 构造出来的，
     * 使用完之后就应该通过 destroy 销毁对象。
     */
    alloc.destroy(p2);

    /**
     * delete
     *
     * delete p1 会完成两件事：
     * 1. 销毁 p1 指向的对象
     * 2. 释放 p1 指向的内存
     *
     * 这也是 delete 和 allocator::destroy 的区别：
     * destroy 只销毁对象，不释放内存；
     * delete 会销毁对象并释放内存。
     */
    delete p1;

    /**
     * deallocate
     *
     * deallocate(p2, 1) 释放之前 allocate(1) 申请的原始内存。
     *
     * 注意：
     * 第二个参数 1 必须和 allocate 时申请的元素个数一致。
     *
     * 也就是说：
     * alloc.allocate(1);
     * 对应：
     * alloc.deallocate(p2, 1);
     *
     * 如果 allocate 时申请的是 n 个元素空间，
     * deallocate 时第二个参数也应该传 n。
     */
    alloc.deallocate(p2, 1);
}


int main(int argc, char const *argv[])
{
    // 测试 allocator 的基本使用：
    // 对比 new/delete 和 allocator 的区别。
    test1();

    return 0;
}