#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/**
 * allocator 是 C++ 标准库中的空间配置器模板类，
 * 主要负责“内存分配”和“内存释放”。
 *
 * 注意：
 * 1. allocator::allocate 只分配原始内存，不会构造对象。
 * 2. allocator::construct 会在已分配的内存上构造对象。
 * 3. allocator::destroy 会销毁对象，但不会释放内存。
 * 4. allocator::deallocate 才会释放之前申请的原始内存。
 *
 * new/delete 则同时完成了对象构造/销毁和内存申请/释放：
 * - new  = 分配内存 + 构造对象
 * - delete = 析构对象 + 释放内存
 */

void test1()
{
    // 使用 new 创建一个 int 对象：
    // 1. 先申请一块能存放 int 的内存
    // 2. 再在该内存上构造一个值为 1 的 int 对象
    int * p1 = new int(1);

    cout << *p1 << endl;
    cout << "p1:" << p1 << endl;
    
    cout << "----------" << endl;

    // 创建 int 类型的空间配置器对象
    allocator<int> alloc;

    // allocate(1) 只申请 1 个 int 大小的原始内存空间，
    // 此时该内存中还没有真正构造 int 对象，不能直接解引用使用。
    int * p2 = alloc.allocate(1);

    // 在 p2 指向的原始内存上构造一个 int 对象，并初始化为 2。
    // 这一步之后，p2 才指向一个真正可用的 int 对象。
    alloc.construct(p2, 2); 

    cout << *p2 << endl;
    cout << "p2:" << p2 << endl;

    // destroy(p2) 只负责调用 p2 指向对象的析构过程，
    // 对于 int 这种内置类型来说析构动作很简单，但流程上仍然需要理解。
    // 注意：destroy 不会释放内存。
    alloc.destroy(p2);

    // delete p1 会完成两件事：
    // 1. 销毁 p1 指向的对象
    // 2. 释放 p1 指向的内存
    delete p1;

    // deallocate(p2, 1) 释放之前 allocate(1) 申请的原始内存。
    // 第二个参数必须与 allocate 时申请的元素个数一致。
    alloc.deallocate(p2, 1);
}


int main(int argc, char const *argv[])
{
    test1();

    return 0;
}