#include <iostream>
#include <set>

using namespace std;

class Point
{
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {}

    ~Point()
    {
        // cout << "~Point()" << endl;
    }

    // 注意：在 set 中遍历时元素是 const 的，所以 print 也需要是 const 函数
    void print() const 
    {
        cout << "(" << m_x << ", " << m_y << ")" << endl;
    }

    // 提供 getter 函数，方便外部比较器访问私有成员
    int getX() const { return m_x; }
    int getY() const { return m_y; }

    // ==========================================
    // 写法一：在自定义类型中重载 operator<
    // ==========================================
    // 规则：先比 x，x 相同再比 y
    /* bool operator<(const Point& rhs) const
    {
        if (m_x != rhs.m_x)
        {
            return m_x < rhs.m_x;
        }
        return m_y < rhs.m_y;
    } */

private:
    int m_x;
    int m_y;    
};


// ==========================================
// 写法二：使用函数对象（仿函数）作为自定义比较器
// ==========================================
struct PointComparator
{
    bool operator()(const Point& lhs, const Point& rhs) const
    {
        if (lhs.getX() != rhs.getX())
        {
            return lhs.getX() < rhs.getX();
        }
        return lhs.getY() < rhs.getY();
    }
};

// ==========================================
// 写法三：对 std::less 做特化处理
// ==========================================
// 需要注意：特化 std 命名空间中的模板，必须在 std 命名空间内或者使用全局命名空间特化
namespace std
{
    template <>
    struct less<Point>
    {
        bool operator()(const Point& lhs, const Point& rhs) const
        {
            if (lhs.getX() != rhs.getX())
            {
                return lhs.getX() < rhs.getX();
            }
            return lhs.getY() < rhs.getY();
        }
    };
}

int main() 
{
    // ------------------------------------------
    // 测试写法一：默认使用 Point 的 operator<
    // ------------------------------------------
    cout << "--- 写法一：重载 operator< ---" << endl;
    set<Point> s1;
    s1.insert(Point(1, 2));
    s1.insert(Point(3, 4));
    s1.insert(Point(1, 2)); // 重复元素，不会被插入
    s1.insert(Point(1, 1)); 
    for (const auto& p : s1) {
        p.print();
    }

    // ------------------------------------------
    // 测试写法二：传入自定义函数对象作为第二个模板参数
    // ------------------------------------------
    cout << "\n--- 写法二：自定义仿函数比较器 ---" << endl;
    set<Point, PointComparator> s2;
    s2.insert(Point(5, 6));
    s2.insert(Point(2, 3));
    s2.insert(Point(5, 6)); // 重复元素
    for (const auto& p : s2) {
        p.print();
    }

    // ------------------------------------------
    // 测试写法三：默认会调用 std::less<Point>，此时已被我们特化
    // ------------------------------------------
    // 注意：为了演示写法三，需要把写法一的 operator< 注释掉，
    // 或者用一个没有重载 operator< 的新类。
    // 如果同时存在 operator< 和 std::less 特化，set 在不指定第二个参数时
    // 默认走 std::less，而 std::less 内部会优先调用我们的特化版本。
    cout << "\n--- 写法三：特化 std::less ---" << endl;
    set<Point> s3; // 此时默认走特化后的 std::less<Point>
    s3.insert(Point(10, 20));
    s3.insert(Point(5, 5));
    s3.insert(Point(10, 20)); // 重复元素
    for (const auto& p : s3) {
        p.print();
    }

    return 0;
}