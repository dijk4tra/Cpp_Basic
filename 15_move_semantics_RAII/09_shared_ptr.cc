#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;

/*
 * shared_ptr 智能指针：
 *      共享资源所有权。
 *
 * 特点：
 *      多个 shared_ptr 可以共同管理同一块资源。
 *      内部通过引用计数记录当前有多少个 shared_ptr 共享该资源。
 *      当引用计数变为 0 时，资源会被自动释放。
 *
 * 合法的共享：
 *      通过 shared_ptr 的拷贝构造或拷贝赋值进行共享。
 *      这样多个 shared_ptr 会使用同一个控制块和同一个引用计数。
 *
 * 非法的共享：
 *      将同一个裸指针分别交给多个 shared_ptr 管理。
 *      这样会产生多个控制块，每个控制块都认为自己独立拥有该资源，
 *      最终可能导致重复释放。
 */

class Point
{
public:
    // 构造函数：初始化 Point 的两个坐标
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {

    }

    // 析构函数：用于观察 Point 对象何时被释放
    ~Point()
    {
        cout << "~Point()" << endl;
    }

    // 打印 Point 对象的坐标
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
    // 方式一：使用裸指针构造 shared_ptr
    shared_ptr<Point> sp { new Point{1,2} };

    // 方式二：使用 std::make_shared 创建 shared_ptr
    // make_shared 会同时创建资源对象和控制块，通常更推荐
    shared_ptr<Point> sp2 = std::make_shared<Point>(3,4);
}


// shared_ptr 的基本使用
void test2()
{
    shared_ptr<Point> sp { new Point{1,2} };

    // 通过 operator-> 访问资源成员
    sp->print();

    // 通过 operator* 获取资源对象本身
    (*sp).print();

    // 通过 get() 获取底层原始指针
    // 注意：get() 不释放资源，也不转移所有权
    sp.get()->print();
}

// 测试 shared_ptr 的共享所有权
// 合法共享：通过 shared_ptr 自身的拷贝或赋值实现
void test3()
{
    shared_ptr<Point> sp1 { new Point{1,2} };

    // 此时只有 sp1 管理资源，引用计数为 1
    cout << "sp1:count :" << sp1.use_count()<< endl;

    // 拷贝构造：sp2 与 sp1 共享同一资源
    // 二者共用同一个控制块，引用计数增加
    shared_ptr<Point> sp2 = sp1;

    sp1->print();
    sp2->print();

    cout << "-----" << endl;

    // use_count() 获取当前资源的引用计数
    cout << "sp1:count :" << sp1.use_count()<< endl;
    cout << "sp2:count :" << sp2.use_count()<< endl;

    cout << "------" << endl;

    // sp3 先单独管理 Point{3,4}
    shared_ptr<Point> sp3 { new Point{3,4} };

    // 拷贝赋值：
    // sp3 原来管理的资源引用计数减为 0 后会被释放；
    // 然后 sp3 与 sp1 共享 Point{1,2}
    sp3 = sp1;

    cout << "sp1:count :" << sp1.use_count()<< endl;
    cout << "sp2:count :" << sp2.use_count()<< endl;
    cout << "sp3:count :" << sp3.use_count()<< endl;
}

// 非法共享：同一个裸指针被多个 shared_ptr 分别接管
void test4()
{
    // 原始指针暴露出来
    Point * p = new Point{1,2};

    // sp1 创建自己的控制块，认为自己独占管理 p 指向的资源
    shared_ptr<Point> sp1 { p };
    sp1->print();

    cout << "-----" << endl;

    // 错误：同一个裸指针 p 又交给 sp2 管理
    // sp2 会创建另一个独立控制块，也认为自己拥有同一资源
    shared_ptr<Point> sp2 { p };
    sp2->print();

    cout << "-----" << endl;

    // 两个 shared_ptr 的引用计数都为 1，
    // 说明它们并没有真正共享同一个控制块
    cout << "sp1 count:" << sp1.use_count() << endl;
    cout << "sp2 count:" << sp2.use_count() << endl;

    // test4 结束时，sp1 和 sp2 都会尝试释放同一块资源，导致重复 delete
}

// 另一种非法共享
void test5()
{
    shared_ptr<Point> sp1 { new Point{1,2} };

    // 错误：通过 sp1.get() 取出裸指针，再交给另一个 shared_ptr 管理
    // 这会让 sp2 创建新的控制块，而不是共享 sp1 的控制块
    shared_ptr<Point> sp2 { sp1.get() };

    sp1->print();
    sp2->print();

    // 两个引用计数都为 1，说明不是合法共享
    cout << "sp1 count:" << sp1.use_count() << endl;
    cout << "sp2 count:" << sp2.use_count() << endl;

    // test5 结束时，同一资源会被释放两次
}

void test6()
{
    vector<shared_ptr<Point>> v;

    shared_ptr<Point> sp1 { new Point{1,2} };
    shared_ptr<Point> sp2 { new Point{3,4} };
    shared_ptr<Point> sp3 { new Point{5,6} };

    // shared_ptr 允许拷贝，因此可以直接 push_back 左值
    // vector 中的元素会与 sp1、sp2、sp3 分别共享资源所有权
    v.push_back(sp1);
    v.push_back(sp2);
    v.push_back(sp3);

    // v[0] 与 sp1 共享同一个 Point{1,2}
    v[0]->print();

    // test6 结束时，vector 和局部 shared_ptr 依次析构；
    // 当每个资源的引用计数归零时，对应 Point 对象被释放
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