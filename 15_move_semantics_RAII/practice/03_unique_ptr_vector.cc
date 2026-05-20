#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

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

// unique_ptr作为容器元素
void test1()
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
    
    // 方式一: 范围for循环
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

int main(int argc, char *args[])
{
    test1();

    return 0;
}
