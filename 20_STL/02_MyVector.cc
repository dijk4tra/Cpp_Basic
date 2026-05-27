#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<typename T>
class MyVector
{
public:
    MyVector();
    ~MyVector();

    void push_back(const T&);
    void pop_back();
    int size() const;
    int capacity() const;

private:
    // 重新分配底层空间，用于动态扩容
    void reallocate();

    /**
     * 空间配置器对象：
     * 用于将“内存分配/释放”和“对象构造/销毁”分离。
     *
     * allocate/deallocate：只负责原始内存的申请与释放；
     * construct/destroy：只负责在已有内存上构造对象、销毁对象。
     */
    static allocator<T> m_alloc;
    
    T * m_start;        // 指向当前存储空间的起始位置
    T * m_finish;       // 指向最后一个有效元素的下一个位置
    T * m_endOfStorage; // 指向当前已分配空间的末尾位置
};


// 静态成员需要在类外定义并初始化
template<class T>
allocator<T> MyVector<T>::m_alloc; // 调用 allocator 的默认构造函数


// 构造函数：初始状态下不申请空间，三个指针均置为空
template<typename T>
MyVector<T>::MyVector()
: m_start(nullptr)
, m_finish(nullptr)
, m_endOfStorage(nullptr)
{
}

// 析构函数：销毁已构造的对象，并释放已分配的原始内存
template<typename T>
MyVector<T>::~MyVector()
{
    // 依次销毁当前有效元素区间 [m_start, m_finish) 中的对象
    for(T * p = m_start; p != m_finish; ++p)
    {
        m_alloc.destroy(p);
    }

    // 如果申请过空间，则释放底层原始内存
    if(m_start)
    {
        m_alloc.deallocate(m_start, capacity());
    }
}


// 返回当前有效元素个数
template<typename T>
int MyVector<T>::size() const
{
    // m_start 为空时，说明当前没有分配空间，元素个数为 0
    return m_start ? m_finish - m_start : 0;
}


// 返回当前底层空间容量
template<typename T>
int MyVector<T>::capacity() const
{
    // m_start 为空时，说明当前没有分配空间，容量为 0
    return m_start ? m_endOfStorage - m_start : 0;
}


// 在尾部添加元素
template<typename T>
void MyVector<T>::push_back(const T& value)
{   
    // 如果当前有效元素已经占满底层空间，则需要先扩容
    if(m_finish == m_endOfStorage)
    {
        reallocate();
    }

    // 在 m_finish 指向的未构造空间上构造一个值为 value 的对象
    m_alloc.construct(m_finish, value);

    // m_finish 始终指向最后一个有效元素的下一个位置
    ++m_finish;
}


// 重新分配底层空间，实现动态扩容
template<typename T>
void MyVector<T>::reallocate()
{
    // 记录旧容量，释放旧空间时需要用到
    int oldCapacity = capacity();

    // 按 2 倍扩容；如果当前容量为 0，则第一次扩容为 1
    int newCapacity = oldCapacity == 0 ? 1 : oldCapacity * 2;

    // 申请一块新的原始内存空间，可存放 newCapacity 个 T 类型对象
    // 注意：这里只是申请内存，还没有构造对象
    T * newStart = m_alloc.allocate(newCapacity);

    // 将旧空间中的有效元素复制构造到新空间中
    // uninitialized_copy 会在未初始化空间上逐个构造对象
    T * newFinish = uninitialized_copy(m_start, m_finish, newStart);

    // 如果旧空间存在，则需要销毁旧对象并释放旧空间
    if (m_start)
    {
        // 从后往前销毁旧空间中的对象
        // 区间为 [m_start, m_finish)
        while (m_start != m_finish)
        {   
            --m_finish;
            m_alloc.destroy(m_finish);
        }
        
        // 释放旧的原始内存空间
        // 第二个参数必须与当初 allocate 时的容量一致
        m_alloc.deallocate(m_start, oldCapacity);
    }
    
    // 更新三个指针，使其指向新的底层空间
    m_start = newStart;
    m_finish = newFinish;
    m_endOfStorage = newStart + newCapacity;
}


// 删除尾部元素
template<typename T>
void MyVector<T>::pop_back()
{   
    // 如果当前存在有效元素，则销毁最后一个元素
    if(m_finish != m_start)
    {   
        // m_finish 指向的是最后一个有效元素的下一个位置，
        // 所以需要先向前移动一个位置，才能指向真正的尾元素。
        --m_finish;

        // 销毁尾元素对象，但不释放底层空间
        // 因此 pop_back 只会减少 size，不会改变 capacity
        m_alloc.destroy(m_finish);
    }
}


void test1()
{
    MyVector<int> vec;

    // 连续插入元素，观察 size 和 capacity 的变化
    for(int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
        cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << endl;
    }

    // 连续删除尾部元素，观察 size 减小但 capacity 不变
    for(int i = 0; i < 5; ++i)
    {
        vec.pop_back();
        cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << endl;
    }
}

int main()
{
    test1();
    return 0;
}