#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;

/**
 * shared_ptr 智能指针
 *
 * 1. shared_ptr 的特点
 *
 *    shared_ptr 表示共享资源所有权。
 *
 *    也就是说：
 *    多个 shared_ptr 可以共同管理同一块资源。
 *
 *    shared_ptr 内部通过引用计数记录：
 *    当前有多少个 shared_ptr 正在共享这块资源。
 *
 *    当引用计数变为 0 时，
 *    说明已经没有 shared_ptr 管理该资源了，
 *    资源会被自动释放。
 *
 *
 * 2. shared_ptr 的控制块
 *
 *    shared_ptr 除了管理资源指针之外，
 *    还会关联一个控制块。
 *
 *    控制块中通常保存：
 *    - 强引用计数，也就是 shared_ptr 的数量
 *    - 弱引用计数，也就是 weak_ptr 的数量
 *    - 删除器等管理信息
 *
 *    多个 shared_ptr 想要真正共享同一块资源，
 *    必须共享同一个控制块。
 *
 *
 * 3. 合法共享
 *
 *    合法的共享方式是：
 *    通过 shared_ptr 的拷贝构造或拷贝赋值来共享资源。
 *
 *    例如：
 *    shared_ptr<Point> sp1 { new Point{1,2} };
 *    shared_ptr<Point> sp2 = sp1;
 *
 *    此时：
 *    - sp1 和 sp2 指向同一块资源
 *    - sp1 和 sp2 共用同一个控制块
 *    - 引用计数变为 2
 *
 *
 * 4. 非法共享
 *
 *    错误方式：
 *    将同一个裸指针分别交给多个 shared_ptr 管理。
 *
 *    例如：
 *    Point * p = new Point{1,2};
 *    shared_ptr<Point> sp1 { p };
 *    shared_ptr<Point> sp2 { p };
 *
 *    这不是共享。
 *
 *    因为 sp1 和 sp2 会分别创建自己的控制块，
 *    每个控制块都认为自己独立拥有 p 指向的资源。
 *
 *    最终 sp1 和 sp2 析构时，
 *    会对同一块堆空间释放两次，
 *    导致 double free。
 *
 *
 * 5. make_shared
 *
 *    创建 shared_ptr 时，更推荐使用 std::make_shared。
 *
 *    例如：
 *    shared_ptr<Point> sp = std::make_shared<Point>(1, 2);
 *
 *    make_shared 通常可以一次性分配资源对象和控制块，
 *    效率更高，也更安全。
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
     * 用来观察 shared_ptr 什么时候真正释放资源。
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


// 创建 shared_ptr 对象
void test1()
{
    /**
     * 方式一：
     * 使用裸指针构造 shared_ptr。
     *
     * new Point{1,2} 创建了一个堆上的 Point 对象。
     * sp 接管这块资源。
     *
     * 当没有 shared_ptr 管理这块资源时，
     * 该 Point 对象会被自动释放。
     *
     * 注意：
     * 虽然这种写法可以使用，
     * 但实际开发中更推荐 make_shared。
     */
    shared_ptr<Point> sp { new Point{1,2} };

    /**
     * 方式二：
     * 使用 std::make_shared 创建 shared_ptr。
     *
     * make_shared<Point>(3,4)
     * 会创建一个 Point 对象，
     * 并返回管理该对象的 shared_ptr。
     *
     * make_shared 的优点：
     * 1. 写法更简洁
     * 2. 通常效率更高
     * 3. 可以避免裸指针暴露出来，减少误用风险
     */
    shared_ptr<Point> sp2 = std::make_shared<Point>(3,4);

    /**
     * test1 结束时：
     *
     * sp2 和 sp 都会作为局部对象析构。
     *
     * 它们各自管理不同的 Point 对象，
     * 引用计数都会变为 0，
     * 所以两个 Point 对象都会被释放。
     */
}


// shared_ptr 的基本使用
void test2()
{
    /**
     * 创建 shared_ptr 对象 sp，
     * 管理一个堆上的 Point{1,2}。
     */
    shared_ptr<Point> sp { new Point{1,2} };

    /**
     * shared_ptr 重载了 operator->。
     *
     * 所以可以像裸指针一样，
     * 通过 -> 调用资源对象的成员函数。
     */
    sp->print();

    /**
     * shared_ptr 重载了 operator*。
     *
     * 所以可以通过 *sp 获取它管理的对象本身。
     */
    (*sp).print();

    /**
     * get() 获取 shared_ptr 内部保存的原始指针。
     *
     * 注意：
     * get() 只是返回裸指针，
     * 不释放资源，
     * 不转移资源所有权，
     * 也不会增加引用计数。
     *
     * 外部拿到 get() 返回的指针后，
     * 不应该手动 delete，
     * 也不应该再用它构造新的 shared_ptr。
     */
    sp.get()->print();

    /**
     * test2 结束时，
     * sp 析构，引用计数变为 0，
     * 它管理的 Point 对象会被释放。
     */
}


// 测试 shared_ptr 的共享所有权
// 合法共享：通过 shared_ptr 自身的拷贝或赋值实现
void test3()
{
    /**
     * sp1 管理一个 Point{1,2} 对象。
     *
     * 此时只有 sp1 管理这块资源，
     * 所以引用计数为 1。
     */
    shared_ptr<Point> sp1 { new Point{1,2} };

    /**
     * use_count()
     *
     * 返回当前资源的强引用计数，
     * 也就是有多少个 shared_ptr 正在共享该资源。
     */
    cout << "sp1:count :" << sp1.use_count()<< endl;

    /**
     * shared_ptr<Point> sp2 = sp1;
     *
     * 这里调用 shared_ptr 的拷贝构造函数。
     *
     * 注意：
     * shared_ptr 的拷贝不是深拷贝资源对象，
     * 而是共享同一块资源。
     *
     * 执行之后：
     * - sp1 和 sp2 指向同一个 Point{1,2}
     * - sp1 和 sp2 共用同一个控制块
     * - 引用计数从 1 变为 2
     */
    shared_ptr<Point> sp2 = sp1;

    /**
     * sp1 和 sp2 共享同一个 Point 对象，
     * 所以两者打印结果相同。
     */
    sp1->print();
    sp2->print();

    cout << "-----" << endl;

    /**
     * 因为 sp1 和 sp2 共享同一个控制块，
     * 所以通过它们调用 use_count()，
     * 得到的引用计数相同。
     */
    cout << "sp1:count :" << sp1.use_count()<< endl;
    cout << "sp2:count :" << sp2.use_count()<< endl;

    cout << "------" << endl;

    /**
     * sp3 先单独管理一个新的 Point{3,4}。
     *
     * 此时：
     * - sp1 和 sp2 共享 Point{1,2}
     * - sp3 单独管理 Point{3,4}
     */
    shared_ptr<Point> sp3 { new Point{3,4} };

    /**
     * sp3 = sp1;
     *
     * 这里调用 shared_ptr 的拷贝赋值运算符函数。
     *
     * 执行过程：
     *
     * 1. sp3 放弃原来管理的 Point{3,4}
     *    因为 Point{3,4} 只有 sp3 一个 shared_ptr 管理，
     *    所以引用计数减为 0 后会立即释放该资源。
     *
     * 2. sp3 开始和 sp1 共享 Point{1,2}
     *
     * 3. Point{1,2} 的引用计数增加。
     *
     * 执行之后：
     * sp1、sp2、sp3 都共享同一个 Point{1,2}，
     * 引用计数为 3。
     */
    sp3 = sp1;

    cout << "sp1:count :" << sp1.use_count()<< endl;
    cout << "sp2:count :" << sp2.use_count()<< endl;
    cout << "sp3:count :" << sp3.use_count()<< endl;

    /**
     * test3 结束时：
     *
     * sp3、sp2、sp1 会依次析构。
     *
     * 每析构一个 shared_ptr，
     * 引用计数减 1。
     *
     * 当最后一个 shared_ptr 析构后，
     * 引用计数变为 0，
     * Point{1,2} 被释放。
     */
}


// 非法共享：同一个裸指针被多个 shared_ptr 分别接管
void test4()
{
    /**
     * 创建一个裸指针 p，
     * 指向堆上的 Point{1,2}。
     *
     * 注意：
     * 裸指针本身不具备资源管理能力。
     */
    Point * p = new Point{1,2};

    /**
     * sp1 接管 p 指向的资源。
     *
     * 此时 sp1 会创建一个控制块，
     * 该控制块记录引用计数为 1。
     */
    shared_ptr<Point> sp1 { p };
    sp1->print();

    cout << "-----" << endl;

    /**
     * 错误示例：
     *
     * 又使用同一个裸指针 p 创建 sp2。
     *
     * 这里 sp2 不知道 p 已经被 sp1 管理。
     * 所以 sp2 会创建另一个独立的控制块。
     *
     * 结果：
     * - sp1 有自己的控制块，引用计数为 1
     * - sp2 也有自己的控制块，引用计数为 1
     *
     * 它们并没有真正共享资源，
     * 而是两个 shared_ptr 都以为自己独占同一块资源。
     */
    shared_ptr<Point> sp2 { p };
    sp2->print();

    cout << "-----" << endl;

    /**
     * 两个 use_count() 都为 1，
     * 说明 sp1 和 sp2 没有共享同一个控制块。
     *
     * 如果是合法共享，
     * 那么二者的 use_count() 应该都是 2。
     */
    cout << "sp1 count:" << sp1.use_count() << endl;
    cout << "sp2 count:" << sp2.use_count() << endl;

    /**
     * test4 结束时：
     *
     * sp2 析构，释放 p 指向的资源。
     * sp1 析构，又再次释放同一块资源。
     *
     * 这会导致重复 delete，
     * 是未定义行为，程序可能崩溃。
     */
}


// 另一种非法共享
void test5()
{
    /**
     * sp1 正确接管一个新的 Point{1,2}。
     *
     * 此时 sp1 拥有一个控制块，
     * 引用计数为 1。
     */
    shared_ptr<Point> sp1 { new Point{1,2} };

    /**
     * 错误示例：
     *
     * sp1.get() 返回内部裸指针。
     *
     * 然后又用这个裸指针创建 sp2。
     *
     * 这和 test4 中的问题一样：
     * sp2 会创建一个新的控制块，
     * 而不是共享 sp1 的控制块。
     *
     * 所以不要用 get() 返回的裸指针
     * 再去构造新的 shared_ptr。
     */
    shared_ptr<Point> sp2 { sp1.get() };

    sp1->print();
    sp2->print();

    /**
     * 两个引用计数都为 1，
     * 说明它们不是合法共享。
     *
     * 合法写法应该是：
     * shared_ptr<Point> sp2 = sp1;
     *
     * 那样 sp1 和 sp2 才会共享同一个控制块。
     */
    cout << "sp1 count:" << sp1.use_count() << endl;
    cout << "sp2 count:" << sp2.use_count() << endl;

    /**
     * test5 结束时，
     * 同一块资源会被释放两次，
     * 导致未定义行为。
     */
}

void test6()
{
    /**
     * 创建一个 vector 容器。
     *
     * 容器元素类型是 shared_ptr<Point>。
     *
     * 也就是说：
     * vector 中保存的是智能指针对象，
     * 这些智能指针对象可以共享 Point 资源。
     */
    vector<shared_ptr<Point>> v;

    /**
     * 创建三个 shared_ptr，
     * 分别管理三个不同的 Point 对象。
     */
    shared_ptr<Point> sp1 { new Point{1,2} };
    shared_ptr<Point> sp2 { new Point{3,4} };
    shared_ptr<Point> sp3 { new Point{5,6} };

    /**
     * shared_ptr 允许拷贝。
     *
     * 所以可以直接将左值 shared_ptr 放入 vector。
     *
     * v.push_back(sp1)
     *
     * 会拷贝 shared_ptr 对象本身，
     * 不是拷贝 Point 对象。
     *
     * 执行之后：
     * - v[0] 和 sp1 共享 Point{1,2}
     * - Point{1,2} 的引用计数增加
     *
     * 这一点和 unique_ptr 不同。
     *
     * unique_ptr 表示独占所有权，
     * 不能拷贝，只能通过 std::move 放入容器。
     */
    v.push_back(sp1);
    v.push_back(sp2);
    v.push_back(sp3);

    /**
     * v[0] 与 sp1 共享同一个 Point{1,2}，
     * 所以可以正常访问。
     */
    v[0]->print();

    /**
     * 可以观察引用计数：
     *
     * 此时每个资源都有两个 shared_ptr 管理：
     * - 一个是 sp1 / sp2 / sp3
     * - 一个是 vector 中的元素
     *
     * 所以它们的 use_count() 通常为 2。
     */
    cout << "sp1 count:" << sp1.use_count() << endl;
    cout << "sp2 count:" << sp2.use_count() << endl;
    cout << "sp3 count:" << sp3.use_count() << endl;

    /**
     * test6 结束时：
     *
     * 局部变量会按照创建顺序的逆序析构。
     *
     * v 析构时，
     * vector 中保存的 shared_ptr 元素也会析构，
     * 对应资源的引用计数减少。
     *
     * sp1、sp2、sp3 析构时，
     * 引用计数继续减少。
     *
     * 当某个 Point 资源的引用计数变为 0 时，
     * 对应的 Point 对象才会真正被释放。
     */
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    test6();

    return 0;
}