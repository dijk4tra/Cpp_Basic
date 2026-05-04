#include <cstddef>
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;

/**
 * 如果类中有const版本和非const版本的成员函数
 * 1.普通对象 ---> 非const版本的成员函数
 * 2.const对象 ---> const版本的成员函数
 *
 * 如果类中只有非const版本的成员函数
 * 1.普通对象 ---> 可以调用非const版本的成员函数
 * 2.const对象 ---> error 因为this类型不一样
 *
 * 如果类中只有const版本的成员函数
 * 1.普通对象 ---> 都可以调用
 * 2.const对象 ---> 都可以调用
 */

class Point
{
public:
    Point(int x, int y)
    : m_x(x),
      m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    // copy constructor
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
    
    // operator new
    void * operator new (size_t size)
    {
        cout << "operator new" << endl;
        // 底层使用malloc
        return malloc(size);
    }
    
    // operator delete
    void operator delete(void * p)
    {
        cout << "operator delete" << endl;
        free(p);
    }


private:
    int m_x;
    int m_y;
};

void test1()
{
    Point * p = new Point{1,2};
    delete p;
}

// 创建栈对象需要什么条件?
//     public权限的构造函数,public权限的析构函数
// 创建堆上的对象需要什么条件?
//     public权限的构造函数,operator new,operator delete
// 只允许创建堆对象
//     把operator new,operator delete设置为private
// 只允许创建栈对象
//     把析构函数设置为private
void test2()
{
    Point pt{1,2};
}

void test3()
{
    Point * p = new Point{1,2};
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

