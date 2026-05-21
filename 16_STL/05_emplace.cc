#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

class Point
{
public:
    // 有参构造函数
    Point(int x, int y)
        : m_x(x), m_y(y)
    {
        cout << "Point(int x, int y)" << endl;
    }

    // 拷贝构造函数
    Point(const Point & p)
        : m_x(p.m_x), m_y(p.m_y)
    {
        cout << "Point(const Point & p)" << endl;
    }

    // 析构函数
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

// emplace_back 和 push_back 的区别
// push_back    : 需要传入一个已经创建好的对象，再将对象拷贝或移动到容器中
// emplace_back : 直接传入构造函数参数，在容器内部直接构造对象

// emplace 和 insert 的区别
// insert  : 在指定位置插入一个已经创建好的对象，通常会调用拷贝构造或移动构造
// emplace : 在指定位置直接构造对象，可以减少临时对象和拷贝/移动的开销
void test1()
{
    list<Point> box;

    // 创建一个 Point 对象 pt，调用有参构造函数
    Point pt{ 1, 2 };

    cout << "------" << endl;

    // push_back 需要传入一个已有对象
    // 这里把 pt 插入到 list 尾部，会调用拷贝构造函数
    box.push_back(pt);

    cout << "------" << endl;

    // emplace_back 直接传入 Point 构造函数所需的参数
    // 容器会在尾部直接构造 Point 对象，调用有参构造函数
    box.emplace_back(3, 4);

    cout << "------" << endl;

    // 创建另一个 Point 对象 pt2，调用有参构造函数
    Point pt2{ 5, 6 };

    // 获取 list 的起始位置
    auto it = box.begin();

    // insert 在指定位置前插入一个已有对象
    // 这里把 pt2 插入到 it 指向的位置前面，会调用拷贝构造函数
    box.insert(it, pt2);

    cout << "------" << endl;

    // emplace 在指定位置前直接构造对象
    // 这里在 it 指向的位置前面直接构造 Point(3, 4)
    // 调用的是有参构造函数，而不是拷贝构造函数
    box.emplace(it, 3, 4);
}

int main(int argc, char * argv[])
{
    test1();

    return 0;
}