#include <iostream>

using std::cout;
using std::endl;

/*
 * 单例对象的自动释放
 *
 * 方式二：利用嵌套类 + 静态内部类对象实现自动释放。
 *
 * 思路：
 * 1. 将资源管理类 AutoRelease 定义为 Singleton 的内部类；
 * 2. 在 Singleton 中定义一个 static AutoRelease 对象；
 * 3. 程序结束时，静态对象 m_autoRelease 会自动析构；
 * 4. 在 AutoRelease 的析构函数中释放单例对象。
 */

class Singleton
{
    // 内部类：负责自动释放 Singleton 单例对象
    class AutoRelease
    {
    public:
        AutoRelease()
        {
            cout << "AutoRelease()" << endl;
        }

        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;

            if(m_pInstance){
                delete m_pInstance;
                m_pInstance = nullptr;
            }
        }
    };

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

    // 静态内部类对象：
    // 生命周期贯穿整个程序，在程序结束时自动析构
    static AutoRelease m_autoRelease;
};

// 静态成员需要在类外定义并初始化
Singleton * Singleton::m_pInstance = nullptr;

// 定义静态内部类对象，默认调用 AutoRelease 的无参构造函数
// 程序结束时，该对象会自动析构，从而释放 Singleton 单例对象
Singleton::AutoRelease  Singleton::m_autoRelease;


void test1()
{
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