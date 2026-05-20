#include <iostream>

using std::cout;
using std::endl;

/*
 * RAII：Resource Acquisition Is Initialization
 *      资源获取即初始化。
 *
 * 核心思想：
 *      在对象构造时获取资源，
 *      在对象析构时释放资源。
 *
 * 作用：
 *      利用栈对象的生命周期自动管理资源，
 *      避免手动释放资源导致的内存泄漏。
 *
 * 当前 RAII 类用于模拟智能指针：
 *      - 构造函数接管裸指针资源
 *      - 析构函数自动释放资源
 *      - 禁止拷贝，避免多个对象管理同一块资源导致重复释放
 *      - 提供 operator->、operator*、get() 访问底层资源
 */

template <typename T>
class RAII
{
public:
    // 构造函数：接管传入的堆资源
    RAII(T * p)
    : m_p(p)
    {
        cout << "init resource..." << endl;
    }

    // 析构函数：对象生命周期结束时自动释放资源
    ~RAII()
    {
        cout << "release resource..." << endl;
        if(m_p){
            delete m_p;
            m_p = nullptr;
        }
    }

    // 禁止拷贝构造和拷贝赋值
    // 防止多个 RAII 对象持有同一个裸指针，造成重复 delete
    RAII(const RAII &) = delete;
    RAII& operator=(const RAII &) = delete;

    // 提供类似指针的访问方式

    // 重载 operator->：通过 raii->member 的形式访问资源成员
    T * operator->()
    {
        return m_p;
    }

    // 重载 operator*：通过 *raii 的形式访问资源对象本身
    T & operator*()
    {
        return *m_p;
    }

    // get()：获取底层原始指针
    // 注意：这里只是返回指针，不转移资源所有权
    T * get()
    {
        return m_p;
    }

private:
    // 指向被管理资源的原始指针，也称裸指针或底层指针
    T * m_p;
};

class Point
{
public:
    // 构造函数：初始化 Point 的两个坐标
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {

    }

    // 打印 Point 对象的坐标
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

private:
    int m_x;
    int m_y;
};

void test1()
{
    // 创建栈上的 RAII 对象，管理堆上的 int 资源
    // 当 raii 离开作用域时，会自动释放 new int{100}
    RAII<int> raii{ new int{100} };

    // 通过 operator* 获取被管理的 int 对象
    cout << *raii << endl;

    cout << "------" << endl;

    // 创建栈上的 RAII 对象，管理堆上的 Point 资源
    RAII<Point> raii2 { new Point{1,2} };

    // 通过 operator-> 访问 Point 的成员函数
    raii2->print();

    // 通过 operator* 获取 Point 对象，再调用成员函数
    (*raii2).print();

    // 通过 get() 获取原始指针，再调用成员函数
    // 注意：get() 不释放资源，也不转移资源所有权
    raii2.get()->print();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}