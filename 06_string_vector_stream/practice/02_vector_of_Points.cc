#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Point
{
private:
    int m_x;
    int m_y;

public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {}

    void print() const
    {
        cout << "(" << m_x << ", " << m_y << ")" << endl;    
    }
};


int main(int argc, char *argv[])
{   
    vector<Point> points;
    
    Point pt1 = Point{1,2};
    Point pt2 = Point{3,4};
    Point pt3 = Point{5,6};

    points.push_back(pt1);
    points.push_back(pt2);
    points.push_back(pt3);

    cout << "遍历 vector<Point> 并调用 print()：" << endl;

    for(int i = 0; i < points.size(); i++){
        points[i].print();
    }

    cout << endl;

    cout << "使用范围 for 遍历：" << endl;

    for(const Point & p : points){
        p.print();
    }

    return 0;
}

