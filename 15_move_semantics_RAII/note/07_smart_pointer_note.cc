#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;

/**
 * 智能指针 smart pointer
 *
 * 1. 智能指针是什么？
 *
 *    智能指针是一个类模板，
 *    它内部封装了一个裸指针，
 *    并在析构函数中自动释放指针指向的资源。
 *
 *    智能指针是 RAII 思想的重要应用。
 *
 *    也就是：
 *    - 构造智能指针对象时接管资源
 *    - 智能指针对象析构时自动释放资源
 *
 *
 * 2. 为什么需要智能指针？
 *
 *    如果直接使用裸指针：
 *
 *    Point * p = new Point{1, 2};
 *
 *    使用结束后必须手动 delete：
 *
 *    delete p;
 *
 *    如果忘记 delete，
 *    就会造成内存泄漏。
 *
 *    如果 delete 多次，
 *    就会造成 double free。
 *
 *    智能指针可以减少手动管理资源带来的风险。
 *
 *
 * 3. 常见智能指针
 *
 *    auto_ptr
 *
 *    - 早期标准库中的智能指针
 *    - C++11 中已经弃用
 *    - C++17 中已经移除
 *    - 仅作为历史知识了解即可
 *
 *    unique_ptr
 *
 *    - 独占所有权
 *    - 同一时间只能有一个 unique_ptr 管理某个资源
 *    - 不能拷贝，只能移动
 *
 *    shared_ptr
 *
 *    - 共享所有权
 *    - 多个 shared_ptr 可以共同管理同一块资源
 *    - 内部使用引用计数
 *    - 最后一个 shared_ptr 析构时释放资源
 *
 *    weak_ptr
 *
 *    - 弱引用
 *    - 不拥有资源
 *    - 不增加 shared_ptr 的引用计数
 *    - 常用于解决 shared_ptr 循环引用问题
 *
 *
 * 4. auto_ptr 的问题
 *
 *    auto_ptr 表面上支持拷贝：
 *
 *    auto_ptr<Point> ap2 = ap;
 *
 *    但它的“拷贝”并不是真正的拷贝，
 *    而是资源所有权转移。
 *
 *    也就是：
 *    ap2 接管资源，
 *    ap 变成空指针。
 *
 *    这会导致代码行为很不直观，
 *    也是 auto_ptr 被弃用的重要原因。
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


// auto_ptr 基本使用
void test1()
{
    /**
     * auto_ptr<Point> ap { new Point{1,2} };
     *
     * new Point{1,2} 创建了一个堆上的 Point 对象。
     *
     * ap 是一个 auto_ptr 智能指针对象，
     * 它接管这块堆资源。
     *
     * 当 ap 离开作用域时，
     * ap 的析构函数会自动 delete 这块资源。
     *
     * 注意：
     * auto_ptr 已经被弃用，
     * 实际开发中不要再使用。
     */
    auto_ptr<Point> ap { new Point{1,2} };

    /**
     * auto_ptr 重载了 operator->。
     *
     * 所以可以像裸指针一样通过 -> 访问 Point 成员函数。
     */
    ap->print();

    /**
     * auto_ptr 重载了 operator*。
     *
     * 所以可以像裸指针一样解引用，
     * 得到它管理的 Point 对象本身。
     */
    (*ap).print();

    /**
     * get() 用来获取 auto_ptr 内部保存的裸指针。
     *
     * 注意：
     * get() 只是返回裸指针，
     * 不会释放资源，
     * 也不会转移资源所有权。
     *
     * 外部拿到 get() 返回的指针后，
     * 不应该手动 delete。
     */
    ap.get()->print();

    /**
     * test1 结束时，
     * ap 作为局部对象自动析构，
     * 它管理的 Point 资源会被自动释放。
     */
}

void test2()
{
    /**
     * 创建 auto_ptr 对象 ap，
     * 管理一个堆上的 Point 对象。
     */
    auto_ptr<Point> ap { new Point{3,4} };

    /**
     * 此时 ap 持有资源，
     * 可以正常访问 Point 对象。
     */
    ap->print();

    cout << "-----" << endl;

    /**
     * auto_ptr<Point> ap2 = ap;
     *
     * 这行代码看起来像是拷贝构造。
     *
     * 但 auto_ptr 的拷贝语义非常特殊：
     * 它会转移资源所有权。
     *
     * 执行之后：
     * - ap2 接管原来 ap 管理的 Point 对象
     * - ap 变成空指针
     *
     * 也就是说，
     * 资源不再属于 ap，
     * 而是属于 ap2。
     *
     * 这种“拷贝后原对象失效”的行为很容易出错，
     * 所以后来的 C++ 标准用 unique_ptr 取代了 auto_ptr。
     */
    auto_ptr<Point> ap2 = ap;

    /**
     * ap2 已经接管资源，
     * 所以可以正常访问 Point 对象。
     */
    ap2->print();

    cout << "-----" << endl;

    /**
     * 此时 ap 已经不再管理资源，
     * 内部指针为空。
     *
     * 如果继续通过 ap 访问 Point 对象，
     * 就相当于对空指针解引用，
     * 会导致未定义行为，程序可能崩溃。
     *
     * 所以下面这行代码是错误示例。
     */
    ap->print(); // error 资源已经转移给其他智能指针
}


int main(int argc, char * argv[])
{
    /* test1(); */
    test2();

    return 0;
}