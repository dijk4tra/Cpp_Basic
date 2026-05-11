#include <iostream>

using std::cout;
using std::endl;

/*
 * 单例对象的自动释放
 *
 * 方式一：利用栈对象的生命周期自动释放资源。
 *
 * 思路：
 * 将单例对象看作一种资源，
 * 再交给另一个栈对象进行管理。
 * 当管理者对象生命周期结束时，
 * 由其析构函数负责释放单例对象。
 */

class Singleton
{
public:
    // 提供静态成员函数，返回唯一的 Singleton 对象
    static Singleton * getInstance()
    {
        if(!m_pInstance){
            m_pInstance = new Singleton{};
        }
        return m_pInstance;
    }

    // 提供手动回收资源的接口
    /* static void destroyInstance() */
    /* { */
    /*     if(m_pInstance){ */
    /*         delete m_pInstance; */
    /*         m_pInstance = nullptr; */
    /*     } */
    /* } */

    // 删除复制控制函数，防止通过拷贝或赋值产生新的对象
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;

    // 将管理者类声明为友元类，使其可以访问 Singleton 的私有析构函数
    friend class AutoRelease;

private:
    Singleton(){}
    ~Singleton(){}

    static Singleton * m_pInstance;
};

// 静态成员需要在类外定义并初始化
Singleton * Singleton::m_pInstance = nullptr;


// 管理者类：负责释放 Singleton 对象
class AutoRelease
{
public:
    AutoRelease(Singleton * p)
    : m_p(p)
    {
        cout << "AutoRelease(Singleton*)" << endl;
    }

    // 析构函数：管理者对象销毁时，自动释放其管理的资源
    ~AutoRelease()
    {
        cout << "~AutoRelease()" << endl;
        if(m_p){
            delete m_p;
            m_p = nullptr;
        }
    }

private:
    // 指向被管理资源的指针
    Singleton * m_p;
};

void test1()
{
    // 创建栈上的管理者对象，由它负责管理 Singleton 单例资源
    AutoRelease ar { Singleton::getInstance() };

    // 多次调用 getInstance()，返回的都是同一个 Singleton 对象
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}