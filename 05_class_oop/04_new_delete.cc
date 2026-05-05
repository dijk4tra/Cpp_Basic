#include <iostream>

using std::cout;
using std::endl;

class Point
{
public:
    Point(int x, int y)
    : m_x(x),
      m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    // 拷贝构造函数
    Point(const Point & rhs)
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    {
        cout << "Point(const Point &)" << endl;
    }

    // const 成员函数
    void show() const
    {
        cout << "show() const" << endl;
    }

    void show()
    {
        cout << "show()" << endl;
    }
    
    ~Point()
    {
        cout << "~Point()" << endl;
    }
    
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }
    
    // 重载 operator new
    void * operator new (size_t size)
    {
        cout << "operator new" << endl;

        // 底层通过 malloc 申请内存
        return malloc(size);
    }
    
    // 重载 operator delete
    void operator delete(void * p)
    {
        cout << "operator delete" << endl;

        // 底层通过 free 释放 operator new 申请的内存
        free(p);
    }


private:
    int m_x;
    int m_y;
};

void test1()
{
    Point * p = new Point{1, 2};
    delete p;
}

/*
 * 创建栈对象需要满足的条件：
 * 1. 构造函数具有 public 权限
 * 2. 析构函数具有 public 权限
 *
 * 创建堆对象需要满足的条件：
 * 1. 构造函数具有 public 权限
 * 2. operator new 具有 public 权限
 * 3. operator delete 具有 public 权限
 *
 * 只允许创建堆对象：
 * 将析构函数设置为 private
 *
 * 只允许创建栈对象：
 * 将 operator new 和 operator delete 设置为 private
 */
void test2()
{
    Point pt{1, 2};
}

void test3()
{
    Point * p = new Point{1, 2};
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}