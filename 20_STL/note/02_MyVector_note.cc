#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/**
 * MyVector
 *
 * 这是一个简化版本的 vector。
 *
 * 主要目的：
 * 通过自己实现 MyVector，
 * 理解 STL vector 底层空间管理的大致过程。
 *
 *
 * vector 底层通常会维护三根指针：
 *
 * 1. m_start
 *    指向底层连续空间的起始位置。
 *
 * 2. m_finish
 *    指向最后一个有效元素的下一个位置。
 *
 * 3. m_endOfStorage
 *    指向当前已分配空间的末尾位置。
 *
 *
 * 三个指针之间的关系：
 *
 * [m_start, m_finish)
 * 表示当前已经构造好的有效元素区间。
 *
 * [m_finish, m_endOfStorage)
 * 表示已经申请了内存，
 * 但是还没有构造对象的备用空间。
 *
 * [m_start, m_endOfStorage)
 * 表示当前 vector 拥有的整块底层空间。
 *
 *
 * size 和 capacity 的区别：
 *
 * size：
 * 当前有效元素的个数。
 *
 * capacity：
 * 当前底层空间最多能够容纳的元素个数。
 *
 * 所以：
 * size = m_finish - m_start
 * capacity = m_endOfStorage - m_start
 *
 *
 * 注意：
 * vector 为了避免每次插入元素都重新申请内存，
 * 通常会一次性申请比当前需要更多的空间。
 *
 * 因此：
 * size <= capacity
 */

template<typename T>
class MyVector
{
public:
    MyVector();
    ~MyVector();

    // 在尾部插入元素
    void push_back(const T&);

    // 删除尾部元素
    void pop_back();

    // 返回当前有效元素个数
    int size() const;

    // 返回当前底层空间容量
    int capacity() const;

private:
    /**
     * reallocate
     *
     * 重新分配底层空间，用于动态扩容。
     *
     * 当当前有效元素已经占满底层空间时，
     * 再插入新元素就没有位置可以构造对象了，
     * 此时需要重新申请一块更大的空间。
     *
     * 扩容的大致步骤：
     * 1. 计算新的容量
     * 2. 申请新的原始内存
     * 3. 将旧空间中的有效元素复制构造到新空间
     * 4. 销毁旧空间中的对象
     * 5. 释放旧空间的原始内存
     * 6. 更新三个指针
     */
    void reallocate();

    /**
     * 空间配置器对象
     *
     * allocator<T> 用于管理 T 类型对象的空间。
     *
     * 它将“内存申请/释放”和“对象构造/销毁”分离：
     *
     * 1. allocate
     *    只申请原始内存，不构造对象。
     *
     * 2. deallocate
     *    只释放原始内存。
     *
     * 3. construct
     *    在已经申请好的内存上构造对象。
     *
     * 4. destroy
     *    销毁已经构造好的对象，但不释放内存。
     *
     * 这里使用 static 的原因：
     * 对于同一种 T 类型的 MyVector 来说，
     * allocator<T> 对象可以共享一份。
     */
    static allocator<T> m_alloc;
    
    /**
     * m_start
     *
     * 指向当前底层存储空间的起始位置。
     *
     * 如果 MyVector 还没有申请空间，
     * 则 m_start 为 nullptr。
     */
    T * m_start;

    /**
     * m_finish
     *
     * 指向最后一个有效元素的下一个位置。
     *
     * 注意：
     * m_finish 指向的位置不一定有对象。
     *
     * 例如：
     * 当前有 3 个有效元素时，
     * m_finish 指向第 4 个位置，
     * 也就是下一个可以构造新元素的位置。
     */
    T * m_finish;

    /**
     * m_endOfStorage
     *
     * 指向当前已分配空间的末尾位置。
     *
     * 注意：
     * 它也是一个“尾后指针”，
     * 指向整块空间最后一个位置的下一个位置。
     */
    T * m_endOfStorage;
};


/**
 * 静态成员变量的定义
 *
 * 类中的 static 成员变量需要在类外单独定义。
 *
 * 因为 m_alloc 是类模板中的静态成员，
 * 所以这里也要写成模板形式。
 *
 * 对于不同的 T 类型，
 * 会分别生成不同的 allocator 对象。
 *
 * 例如：
 * MyVector<int>::m_alloc
 * MyVector<double>::m_alloc
 * 是两份不同的静态成员。
 */
template<class T>
allocator<T> MyVector<T>::m_alloc; // 调用 allocator 的默认构造函数


/**
 * MyVector 构造函数
 *
 * 初始状态下不申请底层空间，
 * 三个指针都置为空。
 *
 * 此时：
 * size() == 0
 * capacity() == 0
 */
template<typename T>
MyVector<T>::MyVector()
: m_start(nullptr)
, m_finish(nullptr)
, m_endOfStorage(nullptr)
{
}


/**
 * MyVector 析构函数
 *
 * 析构函数需要完成两件事：
 *
 * 1. 销毁当前已经构造好的所有对象
 * 2. 释放底层已经申请的原始内存
 *
 * 注意：
 * allocator 中 destroy 和 deallocate 是分开的。
 *
 * destroy：
 * 只销毁对象。
 *
 * deallocate：
 * 只释放内存。
 *
 * 所以析构函数中需要先 destroy，
 * 再 deallocate。
 */
template<typename T>
MyVector<T>::~MyVector()
{
    /**
     * 依次销毁当前有效元素区间 [m_start, m_finish) 中的对象。
     *
     * [m_start, m_finish) 是左闭右开区间：
     * 包含 m_start 指向的位置，
     * 不包含 m_finish 指向的位置。
     *
     * 因为 m_finish 指向的是最后一个有效元素的下一个位置。
     */
    for(T * p = m_start; p != m_finish; ++p)
    {
        m_alloc.destroy(p);
    }

    /**
     * 如果申请过空间，则释放底层原始内存。
     *
     * 注意：
     * deallocate 的第二个参数必须和当初 allocate 时申请的容量一致。
     *
     * 这里调用 capacity()，
     * 得到当前底层空间能够容纳的元素个数。
     */
    if(m_start)
    {
        m_alloc.deallocate(m_start, capacity());
    }
}


/**
 * size
 *
 * 返回当前有效元素个数。
 *
 * 有效元素区间为：
 * [m_start, m_finish)
 *
 * 所以元素个数为：
 * m_finish - m_start
 *
 * 注意：
 * 指针相减得到的是两个指针之间相隔的元素个数，
 * 不是字节数。
 */
template<typename T>
int MyVector<T>::size() const
{
    // m_start 为空时，说明当前没有分配空间，元素个数为 0
    return m_start ? m_finish - m_start : 0;
}


/**
 * capacity
 *
 * 返回当前底层空间容量。
 *
 * 当前整块底层空间区间为：
 * [m_start, m_endOfStorage)
 *
 * 所以容量为：
 * m_endOfStorage - m_start
 */
template<typename T>
int MyVector<T>::capacity() const
{
    // m_start 为空时，说明当前没有分配空间，容量为 0
    return m_start ? m_endOfStorage - m_start : 0;
}


/**
 * push_back
 *
 * 在 MyVector 尾部添加一个元素。
 *
 * 插入元素时需要考虑两种情况：
 *
 * 1. 当前还有备用空间
 *    直接在 m_finish 指向的位置构造新对象。
 *
 * 2. 当前空间已经满了
 *    需要先调用 reallocate 进行扩容，
 *    再构造新对象。
 */
template<typename T>
void MyVector<T>::push_back(const T& value)
{   
    /**
     * 如果 m_finish == m_endOfStorage，
     * 说明当前有效元素已经占满了整块底层空间。
     *
     * 此时没有多余位置可以构造新元素，
     * 所以需要先扩容。
     *
     * 注意：
     * 初始状态下三个指针都是 nullptr，
     * 所以第一次调用 push_back 时：
     * m_finish == m_endOfStorage
     * 条件也成立，
     * 会进入 reallocate 申请第一块空间。
     */
    if(m_finish == m_endOfStorage)
    {
        reallocate();
    }

    /**
     * 在 m_finish 指向的未构造空间上构造一个对象。
     *
     * 注意：
     * m_finish 当前指向的是备用空间中的第一个位置，
     * 该位置已经有内存，
     * 但是还没有对象。
     *
     * construct 会在这块内存上构造一个值为 value 的 T 类型对象。
     */
    m_alloc.construct(m_finish, value);

    /**
     * 新元素构造完成后，
     * m_finish 要向后移动一个位置。
     *
     * 这样 m_finish 仍然保持语义：
     * 指向最后一个有效元素的下一个位置。
     */
    ++m_finish;
}


/**
 * reallocate
 *
 * 重新分配底层空间，实现动态扩容。
 *
 * vector 的扩容通常不是每次只增加 1 个空间，
 * 而是按照一定倍数增长。
 *
 * 这样可以减少频繁申请内存和释放内存带来的开销。
 *
 * 本实现中采用 2 倍扩容策略：
 * 0 -> 1 -> 2 -> 4 -> 8 -> 16 ...
 */
template<typename T>
void MyVector<T>::reallocate()
{
    /**
     * 记录旧容量。
     *
     * 后面释放旧空间时，
     * deallocate 需要知道当初申请了多少个元素空间。
     */
    int oldCapacity = capacity();

    /**
     * 计算新容量。
     *
     * 如果当前容量为 0，
     * 说明这是第一次申请空间，
     * 新容量设置为 1。
     *
     * 如果当前容量不为 0，
     * 则按 2 倍进行扩容。
     */
    int newCapacity = oldCapacity == 0 ? 1 : oldCapacity * 2;

    /**
     * 申请新的原始内存空间。
     *
     * newCapacity 表示可以存放 newCapacity 个 T 类型对象。
     *
     * 注意：
     * allocate 只是申请原始内存，
     * 并不会构造对象。
     *
     * 所以 newStart 指向的是一块未初始化的原始空间。
     */
    T * newStart = m_alloc.allocate(newCapacity);

    /**
     * uninitialized_copy
     *
     * 将旧空间中的有效元素复制到新空间。
     *
     * 旧空间的有效元素区间是：
     * [m_start, m_finish)
     *
     * 新空间的起始位置是：
     * newStart
     *
     * 注意：
     * newStart 指向的是未初始化空间，
     * 不能使用普通的赋值操作。
     *
     * uninitialized_copy 的作用是：
     * 在未初始化空间上逐个复制构造对象。
     *
     * 返回值 newFinish 指向新空间中最后一个有效元素的下一个位置。
     */
    T * newFinish = uninitialized_copy(m_start, m_finish, newStart);

    /**
     * 如果旧空间存在，
     * 则需要销毁旧空间中的对象，
     * 并释放旧空间的原始内存。
     *
     * 第一次扩容时 m_start 为 nullptr，
     * 此时没有旧对象，也没有旧空间需要释放。
     */
    if (m_start)
    {
        /**
         * 从后往前销毁旧空间中的对象。
         *
         * 当前有效元素区间为：
         * [m_start, m_finish)
         *
         * 因为 m_finish 指向最后一个有效元素的下一个位置，
         * 所以要先 --m_finish，
         * 让它指向真正的最后一个有效元素。
         */
        while (m_start != m_finish)
        {   
            --m_finish;
            m_alloc.destroy(m_finish);
        }
        
        /**
         * 释放旧的原始内存空间。
         *
         * 注意：
         * 这里释放的是旧空间，
         * 所以第二个参数要传 oldCapacity。
         *
         * deallocate 只释放内存，
         * 不负责销毁对象。
         *
         * 因此前面必须先 destroy 旧对象，
         * 再 deallocate 旧空间。
         */
        m_alloc.deallocate(m_start, oldCapacity);
    }
    
    /**
     * 更新三个指针，
     * 让 MyVector 管理新的底层空间。
     *
     * newStart：
     * 指向新空间的起始位置。
     *
     * newFinish：
     * 指向新空间中最后一个有效元素的下一个位置。
     *
     * newStart + newCapacity：
     * 指向新空间末尾的下一个位置。
     */
    m_start = newStart;
    m_finish = newFinish;
    m_endOfStorage = newStart + newCapacity;
}


/**
 * pop_back
 *
 * 删除尾部元素。
 *
 * 注意：
 * pop_back 只销毁最后一个有效元素，
 * 不释放底层空间。
 *
 * 所以调用 pop_back 后：
 * size 会减小，
 * capacity 不会改变。
 */
template<typename T>
void MyVector<T>::pop_back()
{   
    /**
     * 如果 m_finish != m_start，
     * 说明当前至少有一个有效元素。
     *
     * 如果二者相等，
     * 说明当前没有有效元素，
     * 不能继续删除。
     */
    if(m_finish != m_start)
    {   
        /**
         * m_finish 指向的是最后一个有效元素的下一个位置。
         *
         * 所以要删除尾元素，
         * 需要先让 m_finish 向前移动一个位置，
         * 此时 m_finish 才指向真正的尾元素。
         */
        --m_finish;

        /**
         * 销毁尾元素对象。
         *
         * 注意：
         * destroy 只会销毁对象，
         * 不会释放底层空间。
         *
         * 因此 pop_back 之后，
         * capacity 保持不变。
         */
        m_alloc.destroy(m_finish);
    }
}


void test1()
{
    // 创建一个 MyVector<int> 对象
    // 初始状态下没有申请空间：
    // size 为 0，capacity 为 0。
    MyVector<int> vec;

    /**
     * 连续插入 10 个元素，
     * 观察 size 和 capacity 的变化。
     *
     * size 表示有效元素个数，
     * 每 push_back 一次都会加 1。
     *
     * capacity 表示底层空间容量，
     * 只有在空间不足发生扩容时才会变化。
     *
     * 由于当前实现采用 2 倍扩容策略，
     * capacity 的变化大致为：
     * 1, 2, 4, 8, 16 ...
     */
    for(int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
        cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << endl;
    }

    /**
     * 连续删除 5 个尾部元素。
     *
     * pop_back 只销毁尾部对象，
     * 不释放底层空间。
     *
     * 所以：
     * size 会逐渐减小，
     * capacity 保持不变。
     */
    for(int i = 0; i < 5; ++i)
    {
        vec.pop_back();
        cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << endl;
    }
}

int main()
{
    // 测试 MyVector 的 push_back、pop_back、
    // size、capacity 以及动态扩容过程。
    test1();

    return 0;
}