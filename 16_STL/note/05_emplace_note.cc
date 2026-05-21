#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

/**
 * Point 类：
 * 用来观察对象在容器中插入时，
 * 构造函数、拷贝构造函数和析构函数的调用情况。
 *
 * 通过输出语句可以看到：
 * 1. 对象什么时候被创建。
 * 2. 对象什么时候发生拷贝。
 * 3. 对象什么时候被销毁。
 */
class Point
{
public:
    /**
     * 有参构造函数
     *
     * Point(int x, int y)
     *
     * 当创建 Point 对象时，
     * 如果传入两个 int 类型参数，
     * 就会调用这个构造函数。
     *
     * 初始化列表：
     * : m_x(x), m_y(y)
     *
     * 表示使用参数 x 初始化成员变量 m_x，
     * 使用参数 y 初始化成员变量 m_y。
     */
    Point(int x, int y)
        : m_x(x), m_y(y)
    {
        cout << "Point(int x, int y)" << endl;
    }

    /**
     * 拷贝构造函数
     *
     * Point(const Point & p)
     *
     * 当使用一个已经存在的 Point 对象
     * 创建另一个 Point 对象时，
     * 会调用拷贝构造函数。
     *
     * const：
     * 表示在拷贝过程中不能修改 p。
     *
     * &：
     * 表示引用传参，
     * 避免再次拷贝对象。
     */
    Point(const Point & p)
        : m_x(p.m_x), m_y(p.m_y)
    {
        cout << "Point(const Point & p)" << endl;
    }

    /**
     * 析构函数
     *
     * ~Point()
     *
     * 当 Point 对象生命周期结束时，
     * 会自动调用析构函数。
     *
     * 例如：
     * 1. 局部对象离开作用域。
     * 2. 容器销毁时，容器中的元素也会被销毁。
     */
    ~Point()
    {
        cout << "~Point()" << endl;
    }

    /**
     * print 成员函数：
     * 用来打印 Point 对象的两个成员变量。
     */
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

private:
    int m_x;
    int m_y;
};

/**
 * emplace_back VS push_back
 * emplace VS insert
 *
 * push_back(value)：
 * 向容器尾部插入一个已经创建好的对象。
 * 插入时通常需要拷贝或移动对象。
 *
 * emplace_back(args...)：
 * 向容器尾部直接构造一个对象。
 * 参数 args... 会直接传给对象的构造函数。
 *
 *
 * insert(pos, value)：
 * 在 pos 位置之前插入一个已经创建好的对象。
 * 插入时通常需要拷贝或移动对象。
 *
 * emplace(pos, args...)：
 * 在 pos 位置之前直接构造一个对象。
 * 参数 args... 会直接传给对象的构造函数。
 *
 *
 * 简单理解：
 * push_back / insert：
 * 先有对象，再把对象放进容器。
 *
 * emplace_back / emplace：
 * 直接在容器中创建对象。
 */
void test1()
{
    // 创建一个 list 容器
    // 容器中存放 Point 类型对象
    list<Point> box;

    // 创建一个 Point 对象 pt
    // 调用 Point(int x, int y)
    Point pt{ 1, 2 };

    cout << "------" << endl;

    // push_back 会把已经存在的对象 pt
    // 插入到容器尾部。
    //
    // 因为 pt 已经是一个对象，
    // 所以插入到容器时需要调用拷贝构造函数，
    // 在容器中拷贝出一个新的 Point 对象。
    box.push_back(pt);

    cout << "------" << endl;

    // emplace_back 直接在容器尾部构造对象。
    //
    // 3 和 4 会作为参数，
    // 直接传给 Point(int x, int y)。
    //
    // 所以这里调用的是有参构造函数，
    // 不需要先创建临时对象再拷贝到容器中。
    box.emplace_back(3, 4);

    cout << "------" << endl;

    // 创建一个新的 Point 对象 pt2
    // 调用有参构造函数
    Point pt2{ 5, 6 };

    // 获取指向容器第一个元素的迭代器
    auto it = box.begin();

    // insert 在 it 指向的位置之前插入对象 pt2。
    //
    // 因为 pt2 是已经存在的对象，
    // 所以会调用拷贝构造函数，
    // 在容器中拷贝出一个新的 Point 对象。
    box.insert(it, pt2);

    cout << "------" << endl;

    // emplace 在 it 指向的位置之前直接构造对象。
    //
    // 3 和 4 会直接传给 Point(int x, int y)，
    // 在容器对应位置直接创建 Point 对象。
    //
    // 所以这里调用的是有参构造函数。
    box.emplace(it, 3, 4);
}

int main(int argc, char * argv[])
{
    // 调用 test1，
    // 观察 push_back、emplace_back、insert、emplace
    // 在插入对象时调用构造函数的区别。
    test1();

    return 0;
}