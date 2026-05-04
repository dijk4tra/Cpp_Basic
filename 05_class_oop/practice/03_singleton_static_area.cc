#include <iostream>

using std::cout;
using std::endl;

/* 实现将Point类型的单例对象创建在静态区 */

class Singleton
{
public:
    static Singleton & getInstance()
    {   
        // static 局部对象：
        // 1. 存储在静态区
        // 2. 只会初始化一次
        // 3. 生命周期从第一次执行到这里开始，一直到程序结束
        static Singleton instance(10,20);
        // 返回一个唯一的对象
        return instance;
    }

    // 删除复制控制的函数
    // 禁止拷贝构造，防止通过已有对象复制出新的对象
    Singleton(const Singleton &) = delete;
    // 禁止赋值运算，防止两个对象之间进行赋值操作
    Singleton & operator=(const Singleton &) = delete;

    void print() const
    {
        cout << "(" << m_x << ", " << m_y << ")" << endl;
    }

private:
    // 构造函数私有化:
    // 从而使外部不能直接创建Singleton对象
    Singleton(int x, int y)
    : m_x(x) 
    , m_y(y)
    {
        cout << "Singleton(int, int)" << endl;
    }

    // 析构函数也可以私有化
    // 但如果对象是 static 局部对象，程序结束时需要自动调用析构函数
    // 因此这里一般不私有化析构函数，或者需要额外处理
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }

private:
    int m_x;
    int m_y;
};

void test1()
{
    /* Singleton p1; */ 
    // 错误：构造函数是 private，外部不能创建对象

    Singleton & p1 = Singleton::getInstance();
    Singleton & p2 = Singleton::getInstance();
    Singleton & p3 = Singleton::getInstance();

    p1.print();

    cout << &p1 << endl;
    cout << &p2 << endl;
    cout << &p3 << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

