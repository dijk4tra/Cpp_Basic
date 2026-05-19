#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

class Point
{
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {}

    ~Point()
    {
        cout << "~Point()" << endl;
    }

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
    unique_ptr<Point> up {new Point{1,2}};
    
    // 通过 operator-> 访问资源成员
    up->print();
    // 通过 operator* 获取资源对象本身
    (*up).print();

    // 通过 get() 获取底层原始指针
    up.get()->print();

}

// 测试 unique_ptr 的独占所有权
void test2()
{
    unique_ptr<Point> up {new Point{1,2}};
    
    // unique_ptr 不允许拷贝构造
    // 因为拷贝会导致两个 unique_ptr 管理同一块资源
    /* unique_ptr<Point> up2 = up; */
    
    unique_ptr<Point> up3 {new Point{3,4}};

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
    
    // 将 unique_ptr 移动进 vector
    v.push_back(std::move(up1));
    v.push_back(std::move(up2));
    v.push_back(std::move(up3));

    cout << "遍历 vector<unique_ptr<Point>>：" << endl;

    // 方式一：范围for循环
    // 依次取出 v 里面的每一个元素，临时命名为 up，然后执行循环体
    for (const auto & up : v)
    {
        up->print();
    }

    cout << "------" << endl;

    // 方式二：下标遍历
    for (size_t i = 0; i < v.size(); ++i)
    {
        v[i]->print();
    }

    cout << "------" << endl;

    // 方式三：迭代器遍历
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        (*it)->print();
    }
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


int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    /* test4(); */

    return 0;
}

