#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

/**
 * unique_ptr 智能指针
 *
 * 1. unique_ptr 的特点
 *
 *    unique_ptr 表示独占资源所有权。
 *
 *    也就是说：
 *    同一时间只能有一个 unique_ptr 对象管理某一块资源。
 *
 *    当 unique_ptr 对象生命周期结束时，
 *    它会自动释放自己管理的资源。
 *
 *
 * 2. unique_ptr 不允许拷贝
 *
 *    unique_ptr 的拷贝构造函数和拷贝赋值运算符函数被删除了。
 *
 *    所以下面的操作是不允许的：
 *
 *    unique_ptr<Point> up1 { new Point{1,2} };
 *    unique_ptr<Point> up2 = up1;   // error
 *    up2 = up1;                     // error
 *
 *    原因：
 *    如果允许拷贝，
 *    就会出现多个 unique_ptr 同时管理同一块资源，
 *    最终可能导致 double free。
 *
 *
 * 3. unique_ptr 允许移动
 *
 *    虽然 unique_ptr 不能拷贝，
 *    但它可以移动。
 *
 *    移动的含义是：
 *    将资源所有权从一个 unique_ptr 转移给另一个 unique_ptr。
 *
 *    例如：
 *    unique_ptr<Point> up2 = std::move(up1);
 *
 *    执行后：
 *    - up2 接管资源
 *    - up1 变成空指针
 *
 *
 * 4. unique_ptr 作为容器元素
 *
 *    vector<unique_ptr<Point>> v;
 *
 *    vector 可以保存 unique_ptr，
 *    但是向 vector 中插入 unique_ptr 时，
 *    不能直接传左值。
 *
 *    因为 push_back(up1) 需要拷贝 up1，
 *    而 unique_ptr 禁止拷贝。
 *
 *    所以需要写成：
 *    v.push_back(std::move(up1));
 *
 *    通过移动语义将资源所有权转移到 vector 中。
 *
 *
 * 5. reset()
 *
 *    reset() 可以替换 unique_ptr 当前管理的资源。
 *
 *    例如：
 *    up1.reset(new Point{3,4});
 *
 *    执行时：
 *    - 先释放 up1 原来管理的资源
 *    - 再接管新的资源
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
     * 方便观察智能指针是否自动释放了资源。
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


// 基本使用
void test1()
{
    /**
     * unique_ptr<Point> up { new Point{1,2} };
     *
     * new Point{1,2} 在堆上创建一个 Point 对象。
     *
     * up 是 unique_ptr 智能指针对象，
     * 它接管这块堆资源。
     *
     * 当 up 离开作用域时，
     * 它会自动调用 delete 释放 Point 对象。
     *
     * 这就是 RAII 思想：
     * 用对象管理资源，
     * 对象析构时自动释放资源。
     */
    unique_ptr<Point> up { new Point{1,2} };

    /**
     * unique_ptr 重载了 operator->。
     *
     * 所以可以像裸指针一样通过 -> 访问 Point 成员函数。
     */
    up->print();

    /**
     * unique_ptr 重载了 operator*。
     *
     * 所以可以像裸指针一样解引用。
     */
    (*up).print();

    /**
     * get() 返回 unique_ptr 内部保存的裸指针。
     *
     * 注意：
     * get() 只是观察资源，
     * 不释放资源，也不转移资源所有权。
     *
     * 外部拿到 get() 返回的指针后，
     * 不应该手动 delete。
     */
    up.get()->print();

    /**
     * test1 结束时，
     * up 自动析构，
     * 它管理的 Point 对象也会被释放。
     */
}


// 测试独占所有权
void test2()
{
    /**
     * up 独占管理一个 Point 对象。
     */
    unique_ptr<Point> up { new Point{1,2} };

    /**
     * 测试拷贝构造
     *
     * unique_ptr 的拷贝构造函数被删除了。
     *
     * 因为 unique_ptr 表示独占所有权，
     * 不允许两个 unique_ptr 同时管理同一块资源。
     *
     * 所以下面这行代码会编译报错。
     */
    /* unique_ptr<Point> up2 = up; */

    /**
     * up3 独占管理另一个 Point 对象。
     */
    unique_ptr<Point> up3 { new Point{3,4} };

    /**
     * 测试拷贝赋值
     *
     * unique_ptr 的拷贝赋值运算符函数也被删除了。
     *
     * 所以下面这行代码也会编译报错。
     */
    /* up3 = up; */

    /**
     * 如果确实想让 up3 接管 up 管理的资源，
     * 需要使用 std::move：
     *
     * up3 = std::move(up);
     *
     * 执行后：
     * - up3 原来管理的 Point{3,4} 会被释放
     * - up3 接管 up 原来管理的 Point{1,2}
     * - up 变成空指针
     */
}


// 作为容器的元素
void test3()
{
    /**
     * vector<unique_ptr<Point>> v;
     *
     * 创建一个 vector 容器，
     * 容器中的元素类型是 unique_ptr<Point>。
     *
     * 也就是说：
     * 这个 vector 中保存的不是 Point 对象本身，
     * 而是管理 Point 对象的 unique_ptr。
     */
    vector<unique_ptr<Point>> v;

    /**
     * 创建三个 unique_ptr 对象，
     * 分别管理三个不同的 Point 对象。
     */
    unique_ptr<Point> up1 { new Point{1,1} };
    unique_ptr<Point> up2 { new Point{2,2}};
    unique_ptr<Point> up3 { new Point{3,3} };

    // 此时 up1 仍然持有资源，可以正常访问
    up1->print();

    cout << "------" << endl;

    /**
     * 直接 push_back 左值 unique_ptr 会报错。
     *
     * 例如：
     * v.push_back(up1);
     *
     * 原因：
     * up1 是有名字的对象，是左值。
     *
     * push_back(up1) 需要把 up1 拷贝一份放进 vector。
     * 但是 unique_ptr 禁止拷贝。
     *
     * 所以下面这些代码都会编译失败。
     */
    /* v.push_back(up1); */
    /* v.push_back(up2); */
    /* v.push_back(up3); */

    /**
     * 使用 std::move 将左值转换成右值。
     *
     * std::move(up1) 本身不移动资源，
     * 它只是把 up1 转换成右值。
     *
     * 真正的资源转移发生在 unique_ptr 的移动构造函数中。
     *
     * 执行之后：
     * - vector 中的元素接管 Point 资源
     * - up1、up2、up3 变成空指针
     */
    v.push_back(std::move(up1));
    v.push_back(std::move(up2));
    v.push_back(std::move(up3));

    /**
     * v[0] 是 vector 中的第一个 unique_ptr。
     *
     * 它已经接管了原来 up1 管理的 Point{1,1}。
     *
     * 所以可以通过 v[0]->print() 正常访问资源。
     */
    v[0]->print();

    cout << "-----" << endl;

    /**
     * 此时 up1 已经不再管理资源，
     * 内部指针为空。
     *
     * 如果继续使用 up1->print()，
     * 就相当于对空指针解引用，
     * 会导致未定义行为。
     */
    /* up1->print(); // error up1 已经不管理该资源了 */

    /**
     * test3 结束时：
     *
     * vector v 析构，
     * vector 中的 unique_ptr 元素也会依次析构。
     *
     * 每个 unique_ptr 析构时，
     * 都会释放自己管理的 Point 对象。
     */
}

void test4()
{
    /**
     * up1 管理一个 Point{1,1} 对象。
     */
    unique_ptr<Point> up1 { new Point{1,1} };

    // 此时 up1 指向 Point{1,1}
    up1->print();

    /**
     * reset() 替换被管理的对象。
     *
     * up1.reset(new Point{3,4});
     *
     * 执行过程：
     * 1. unique_ptr 先释放原来管理的 Point{1,1}
     *    因此会看到 Point{1,1} 的析构函数被调用。
     *
     * 2. unique_ptr 再接管新的 Point{3,4}
     *
     * reset 之后，
     * up1 管理的就是新的 Point{3,4}。
     */
    up1.reset(new Point{3,4});

    // 此时打印的是新的 Point{3,4}
    up1->print();

    /**
     * test4 结束时，
     * up1 自动析构，
     * 它当前管理的 Point{3,4} 会被释放。
     */
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test3(); */
    test4();

    return 0;
}