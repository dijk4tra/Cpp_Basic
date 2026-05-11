#include <iostream>

using std::cout;
using std::endl;

/*
 * 单例对象的自动释放
 *
 * 方式三：利用 atexit() + destroyInstance() 实现自动释放。
 *
 * atexit(函数指针)：
 * 将函数指针指向的函数注册到 atexit 中。
 * 被注册的函数称为回调函数，
 * 当程序正常结束时，这些回调函数会被自动调用。
 *
 * 单例的两种创建模式：
 * 1. 懒加载，也称懒汉模式：
 *    不使用时不创建，第一次使用时才创建。
 *
 * 2. 立即加载，也称饿汉模式：
 *    无论是否使用，程序启动时就先创建单例对象；
 *    后续需要使用时，直接返回已经创建好的对象。
 */
class Singleton
{
public:
    // 提供静态成员函数，返回唯一的 Singleton 对象
    static Singleton * getInstance()
    {
        if(!m_pInstance){
            m_pInstance = new Singleton{};

            // 将 destroyInstance 注册到 atexit 中
            // 程序正常结束时会自动调用该函数释放单例对象
            atexit(&destroyInstance);
        }
        return m_pInstance;
    }

    /* static Singleton * getInstance() */
    /* { */
    /*     return m_pInstance; */
    /* } */

    // 提供回收单例对象的接口
    static void destroyInstance()
    {
        cout << "destroyInstance" << endl;

        if(m_pInstance){
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

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

// 懒加载：程序启动时先置空，第一次调用 getInstance() 时再创建对象
Singleton * Singleton::m_pInstance = nullptr;

// 立即加载：程序启动时就创建 Singleton 对象
/* Singleton * Singleton::m_pInstance = new Singleton{}; */


void func()
{
    cout << "func()" << endl;
}

void func2()
{
    cout << "func2()" << endl;
}

void test0()
{
    cout << "test0 start" << endl;

    /* func(); */

    // 将 func、func2 注册到 atexit 中
    atexit(&func);
    atexit(&func);
    atexit(&func2);

    // atexit 中的函数按注册顺序的逆序执行：
    // 后注册的先执行，先注册的后执行
    cout << "test0 end" << endl;
}

void test1()
{
    // 多次调用 getInstance()，返回的都是同一个 Singleton 对象
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
}

int main(int argc, char * argv[])
{
    cout << "main statr" << endl;

    /* test0(); */
    test1();

    cout << "main end" << endl;
    return 0;
}