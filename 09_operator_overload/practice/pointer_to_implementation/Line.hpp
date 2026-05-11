#ifndef __LINE_HPP__
#define __LINE_HPP__

class Line
{
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();

    void printLine() const;

private:
    class LineImpl;        // 内部实现类的前向声明
    LineImpl * m_pimpl;    // 指向实现类对象的指针
};

#endif