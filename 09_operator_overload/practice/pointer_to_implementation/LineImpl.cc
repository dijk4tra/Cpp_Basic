#include "Line.hpp"
#include <iostream>

using std::cout;
using std::endl;

// Line 的内部实现类
class Line::LineImpl
{
    class Point
    {
    public:
        Point(int x, int y)
        : m_x(x)
        , m_y(y)
        {
            cout << "Point constructor" << endl;
        }

        ~Point()
        {
            cout << "Point destructor" << endl;
        }

        void print() const
        {
            cout << "(" << m_x << ", " << m_y << ")";
        }

    private:
        int m_x;
        int m_y;
    };

public:
    LineImpl(int x1, int y1, int x2, int y2)
    : m_pt1(x1, y1)
    , m_pt2(x2, y2)
    {
        cout << "LineImpl constructor" << endl;
    }

    ~LineImpl()
    {
        cout << "LineImpl destructor" << endl;
    }

    void print() const
    {
        cout << "Line: ";
        m_pt1.print();
        cout << " -> ";
        m_pt2.print();
        cout << endl;
    }

private:
    Point m_pt1;
    Point m_pt2;
};

Line::Line(int x1, int y1, int x2, int y2)
: m_pimpl(new LineImpl(x1, y1, x2, y2))
{
    cout << "Line constructor" << endl;
}

Line::~Line()
{
    cout << "Line destructor" << endl;

    if (m_pimpl)
    {
        delete m_pimpl;
        m_pimpl = nullptr;
    }
}

void Line::printLine() const
{
    m_pimpl->print();
}