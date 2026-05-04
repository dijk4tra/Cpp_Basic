#include <iostream>

using std::cout;
using std::endl;

/* 实现将Point类型的单例对象创建在堆区，并完善：
    1.提供回收单例对象的方法
    2.修改单例对象的数据成员，让它们可以有不同的值
    3.析构函数私有化，禁止外部直接 delete 单例对象
*/

class Singleton
{
public:
    // 获取单例对象
    // 第一次调用时，在堆区创建对象
    static Singleton & getInstance(int x=0, int y=0)
    {
        // 如果指针为空，说明还没有创建对象
        if(nullptr == m_pInstance)
        {
            // 在堆区创建 Singleton 对象
            m_pInstance = new Singleton(x, y);
        }

        // 返回唯一的单例对象
        return * m_pInstance;
    }

    // 回收单例对象
    static void destroy()
    {
        // 如果对象已经创建，则释放堆空间
        if(m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

    // 删除复制控制的函数
    // 禁止拷贝构造，防止通过已有对象复制出新的对象
    Singleton(const Singleton &) = delete;
    // 禁止赋值运算，防止两个对象之间进行赋值操作
    Singleton & operator=(const Singleton &) = delete;

    // 修改单例对象中的数据成员
    // 这样可以灵活使用单例对象，让 m_x 和 m_y 有不同的值
    void setValue(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    
    void print() const
    {
        cout << "(" << m_x << ", " << m_y << ")" << endl;
    }


private:
    // 构造函数私有化：
    // 外部不能直接创建 Singleton 对象
    Singleton(int x, int y)
    : m_x(x)
    , m_y(y)
    {
        cout << "Singleton(int, int)" << endl;
    }

    // 析构函数私有化：
    // 外部不能直接 delete 单例对象
    // 只能通过 destroy() 进行回收
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }

private:
    int m_x;
    int m_y;

    // 保存堆区单例对象的地址
    static Singleton * m_pInstance;
};

// 静态数据成员需要在类外初始化
Singleton * Singleton::m_pInstance = nullptr;


void test1()
{
    Singleton & p1 = Singleton::getInstance(10,20);
    Singleton & p2 = Singleton::getInstance();
    Singleton & p3 = Singleton::getInstance();

    p1.print();

    cout << &p1 << endl;
    cout << &p2 << endl;
    cout << &p3 << endl;

    // 修改单例对象的数据成员
    p1.setValue(30, 40);
    p2.print();

    p2.setValue(100, 200);
    p3.print();

    // 回收堆区的单例对象
    Singleton::destroy(); 
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

