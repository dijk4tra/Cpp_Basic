#include <iostream>
#include <memory>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

/*
 * unique_ptr 智能指针：
 *      独占资源所有权。
 *
 * 特点：
 *      同一时刻只能有一个 unique_ptr 管理某个资源。
 *      不允许拷贝构造和拷贝赋值，因为拷贝会导致多个指针管理同一资源。
 *      允许移动构造和移动赋值，通过移动转移资源所有权。
 *
 * 注意：
 *      unique_ptr 可以作为容器元素，
 *      但向容器中插入 unique_ptr 时，通常需要使用 std::move 转移所有权。
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

// unique_ptr 的基本使用
void test1()
{
    // 将 new 出来的 Point 资源交给 unique_ptr 管理
    // 当 up 离开作用域时，Point 资源会被自动释放
    unique_ptr<Point> up { new Point{1,2} };

    // 通过 operator-> 访问资源成员
    up->print();

    // 通过 operator* 获取资源对象本身
    (*up).print();

    // 通过 get() 获取底层原始指针
    // 注意：get() 不释放资源，也不转移所有权
    up.get()->print();
}

// 测试 unique_ptr 的独占所有权
void test2()
{
    unique_ptr<Point> up { new Point{1,2} };

    // unique_ptr 不允许拷贝构造
    // 因为拷贝会导致两个 unique_ptr 管理同一块资源
    /* unique_ptr<Point> up2 = up; */

    unique_ptr<Point> up3 { new Point{3,4} };

    // unique_ptr 不允许拷贝赋值
    // 只能通过移动语义转移资源所有权
    /* up3 = up; */
}

// unique_ptr 作为容器元素
void test3()
{
    vector<unique_ptr<Point>> v;

    unique_ptr<Point> up1 { new Point{1,1} };
    unique_ptr<Point> up2 { new Point{2,2} };
    unique_ptr<Point> up3 { new Point{3,3} };

    up1->print();

    cout << "------" << endl;

    // 直接把左值 unique_ptr 放入 vector 会报错
    // 因为 push_back(up1) 需要拷贝 unique_ptr，
    // 但 unique_ptr 的拷贝构造函数已经被删除
    /* v.push_back(up1); */
    /* v.push_back(up2); */
    /* v.push_back(up3); */

    // 使用 std::move 将左值转换为右值，
    // 从而调用 unique_ptr 的移动构造函数，将资源所有权转移到 vector 中
    v.push_back(std::move(up1));
    v.push_back(std::move(up2));
    v.push_back(std::move(up3));

    // 此时 v[0] 管理原来 up1 管理的 Point 资源
    v[0]->print();

    cout << "-----" << endl;

    // 移动之后，up1 不再管理原来的资源，通常为空
    // 继续通过 up1 访问资源会出错
    /* up1->print(); // error up1 已经不管理该资源了 */
}

void test4()
{
    // up1 管理一个 Point{1,1} 对象
    unique_ptr<Point> up1 { new Point{1,1} };
    up1->print();

    // reset() 用于替换当前管理的资源
    // 原来的 Point{1,1} 会先被释放，再接管新的 Point{3,4}
    up1.reset(new Point{3,4});

    up1->print();

    // test4 结束时，up1 当前管理的 Point{3,4} 会被自动释放
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test3(); */
    test4();
    return 0;
}
