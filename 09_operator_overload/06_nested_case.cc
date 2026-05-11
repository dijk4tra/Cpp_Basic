#include <iostream>

using std::cout;
using std::endl;


// 外部类：Line，相当于“寄居蟹的壳”
class Line
{
    // 内部类：Point，相当于“寄居蟹”
    // Point 只服务于 Line，因此定义为私有嵌套类，避免暴露到外部
    class Point
    {
    public:
        Point(int x, int y)
        : m_x(x)
        , m_y(y)
        {

        }

        void print()
        {
            cout << m_x << " " << m_y << endl;
        }

    private:
        int m_x;
        int m_y;
    };

public:
    Line() = default;

    Line(int x1, int y1, int x2, int y2)
    : m_pt1(x1,y1)
    , m_pt2(x2,y2)
    {

    }

    void print()
    {
        m_pt1.print();
        m_pt2.print();
    }

private:
    /* double m_data; */

    // Line 由两个 Point 对象组成
    Point m_pt1;
    Point m_pt2;
};

void test1()
{
    /* Line line; */
    /* cout << sizeof(line) << endl; // Line 中包含两个 Point 对象，每个 Point 包含两个 int */

    Line line{1,2,3,4};
    line.print();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}