#include <iostream>

using std::cout;
using std::endl;

/**
 * RAII
 *
 * 全称：
 * Resource Acquisition Is Initialization
 *
 * 中文常翻译为：
 * 资源获取即初始化。
 *
 *
 * 1. RAII 的核心思想
 *
 *    将资源的生命周期和对象的生命周期绑定在一起。
 *
 *    对象构造时：
 *    获取资源。
 *
 *    对象析构时：
 *    释放资源。
 *
 *
 * 2. 为什么需要 RAII？
 *
 *    在 C++ 中，很多资源都需要手动释放，例如：
 *    - new 申请的堆内存，需要 delete
 *    - new [] 申请的数组空间，需要 delete []
 *    - fopen 打开的文件，需要 fclose
 *    - mutex 加锁后，需要 unlock
 *    - socket、数据库连接等系统资源，也需要关闭
 *
 *    如果程序员忘记释放资源，
 *    就可能造成资源泄漏。
 *
 *    RAII 的做法是：
 *    把资源交给一个对象管理，
 *    让对象析构函数自动释放资源。
 *
 *
 * 3. 当前代码的作用
 *
 *    这里模拟实现一个简单的 RAII 类模板，
 *    用来管理任意类型 T 的堆对象资源。
 *
 *    例如：
 *    RAII<int> 管理 int *
 *    RAII<Point> 管理 Point *
 *
 *
 * 4. 注意
 *
 *    当前 RAII 类只适合管理通过 new 创建的单个对象。
 *
 *    也就是：
 *    new T
 *
 *    不适合直接管理 new T[] 创建的数组，
 *    因为析构函数中使用的是 delete，
 *    而不是 delete []。
 */

template <typename T>
class RAII
{
public:
    /**
     * 构造函数
     *
     * 参数：
     * T * p
     *
     * p 是外部传入的原始指针，
     * 指向一块通过 new 创建出来的堆对象。
     *
     * 构造 RAII 对象时，
     * 将这块资源交给 RAII 对象管理。
     *
     *
     * 例如：
     * RAII<int> raii{ new int{100} };
     *
     * new int{100} 创建出来的 int 对象，
     * 之后就由 raii 负责释放。
     */
    RAII(T * p)
    : m_p(p)
    {
        cout << "init resource..." << endl;
    }

    /**
     * 析构函数
     *
     * 当 RAII 对象生命周期结束时自动调用。
     *
     * 析构函数中释放 m_p 指向的资源。
     *
     * 这就是 RAII 的关键：
     * 用户不需要手动 delete，
     * 只要 RAII 对象正常离开作用域，
     * 析构函数就会自动释放资源。
     */
    ~RAII()
    {
        cout << "release resource..." << endl;

        if(m_p)
        {
            delete m_p;

            // 释放资源后将指针置空，
            // 避免野指针。
            m_p = nullptr;
        }
    }

    /**
     * 禁止拷贝构造函数
     *
     * 当前 RAII 对象独占管理一块资源。
     *
     * 如果允许拷贝构造：
     *
     * RAII<int> p1{new int{10}};
     * RAII<int> p2 = p1;
     *
     * 那么 p1 和 p2 可能会同时管理同一块堆资源。
     * 当两个对象析构时，
     * 会对同一块空间 delete 两次，
     * 导致 double free 问题。
     *
     * 所以这里使用 = delete 禁止拷贝。
     */
    RAII(const RAII &) = delete;

    /**
     * 禁止拷贝赋值运算符函数
     *
     * 原因与禁止拷贝构造相同：
     * 防止多个 RAII 对象管理同一块资源。
     *
     * 当前这个 RAII 类的语义是“独占资源所有权”。
     */
    RAII& operator=(const RAII &) = delete;


    /**
     * 提供访问资源的操作
     *
     * RAII 对象本身是一个管理者，
     * 真正的数据对象在 m_p 指向的堆空间中。
     *
     * 为了让 RAII 对象使用起来像普通指针，
     * 通常会重载：
     * - operator->
     * - operator*
     *
     * 这也是智能指针常见的设计方式。
     */

    /**
     * operator->
     *
     * 作用：
     * 让 RAII 对象可以像指针一样访问资源对象的成员。
     *
     * 例如：
     * RAII<Point> raii2 { new Point{1,2} };
     * raii2->print();
     *
     * 编译器会把 raii2->print()
     * 理解为：
     * raii2.operator->()->print();
     *
     * operator-> 返回 m_p，
     * 然后通过 m_p 调用 Point::print()。
     */
    T * operator->()
    {
        return m_p;
    }

    /**
     * operator*
     *
     * 作用：
     * 让 RAII 对象可以像指针一样解引用。
     *
     * 例如：
     * RAII<int> raii{ new int{100} };
     * cout << *raii << endl;
     *
     * 这里的 *raii 会调用：
     * raii.operator*()
     *
     * 返回 m_p 指向的对象本身。
     */
    T & operator*()
    {
        return *m_p;
    }

    /**
     * get()
     *
     * 作用：
     * 获取 RAII 对象内部保存的原始指针。
     *
     * 有些场景下，
     * 可能需要把原始指针传给其他接口使用。
     *
     * 例如：
     * raii2.get()->print();
     *
     *
     * 注意：
     * get() 只是返回原始指针，
     * 并不会释放资源，
     * 也不会转移资源所有权。
     *
     * 因此外部拿到 get() 返回的指针后，
     * 不应该手动 delete，
     * 否则 RAII 对象析构时还会再次 delete。
     */
    T * get()
    {
        return m_p;
    }

private:
    /**
     * m_p 是底层指针，也叫裸指针、原始指针。
     *
     * 它指向当前 RAII 对象管理的资源。
     *
     * 当前类的设计中，
     * m_p 指向的是通过 new 创建出来的单个对象，
     * 所以析构函数中使用 delete m_p 释放。
     */
    T * m_p;
};

class Point
{
public:
    /**
     * Point 的有参构造函数
     *
     * 使用 x 和 y 初始化点的两个坐标。
     */
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {

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

void test1()
{
    /**
     * raii 是一个栈对象。
     *
     * new int{100} 创建了一个堆上的 int 对象，
     * 初始值为 100。
     *
     * 这块堆资源交给 raii 管理。
     *
     * 当 test1 函数执行结束时，
     * raii 作为局部对象会自动析构，
     * 析构函数中会 delete 这块 int 资源。
     */
    RAII<int> raii{ new int{100} };

    /**
     * *raii 会调用 RAII<int>::operator*()
     *
     * operator* 返回 m_p 指向的 int 对象本身，
     * 所以这里可以打印出 100。
     */
    cout << *raii << endl;

    cout << "------" << endl;

    /**
     * raii2 也是一个栈对象。
     *
     * new Point{1,2} 创建了一个堆上的 Point 对象，
     * 并用 1 和 2 初始化它的坐标。
     *
     * 这块 Point 资源由 raii2 管理。
     */
    RAII<Point> raii2 { new Point{1,2} };

    /**
     * raii2->print()
     *
     * 会调用 operator->，
     * 得到内部保存的 Point *，
     * 再通过该指针调用 Point::print()。
     */
    raii2->print();

    /**
     * (*raii2).print()
     *
     * *raii2 会调用 operator*，
     * 得到 m_p 指向的 Point 对象本身，
     * 然后通过 . 调用 print()。
     */
    (*raii2).print();

    /**
     * raii2.get()->print()
     *
     * get() 返回内部原始指针 m_p，
     * 然后通过该指针调用 Point::print()。
     *
     * 注意：
     * get() 只是访问资源，
     * 不转移资源所有权。
     */
    raii2.get()->print();

    /**
     * test1 结束时：
     *
     * 局部对象按照创建顺序的逆序析构。
     *
     * 所以 raii2 会先析构，
     * 释放它管理的 Point 对象。
     *
     * 然后 raii 析构，
     * 释放它管理的 int 对象。
     */
}

int main(int argc, char * argv[])
{
    test1();

    return 0;
}