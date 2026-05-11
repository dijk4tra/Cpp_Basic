#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

/*
 * 单例对象的自动释放
 *
 * 方式四：利用 atexit() + destroyInstance() + pthread_once 实现。
 *
 * 特点：
 * 1. atexit() 负责在程序正常结束时自动释放单例对象；
 * 2. destroyInstance() 负责具体的资源回收逻辑；
 * 3. pthread_once 保证初始化函数只执行一次，从而实现线程安全的懒加载。
 */

class Singleton
{
public:
    // 提供静态成员函数，返回唯一的 Singleton 对象
    static Singleton * getInstance()
    {
        // pthread_once 保证 initRoutine 只会被执行一次
        pthread_once(&m_once_control, &initRoutine);

        return m_pInstance;
    }

    // 初始化函数：只会被 pthread_once 调用一次
    static void initRoutine()
    {
        // 创建唯一的 Singleton 对象
        m_pInstance = new Singleton{};

        // 将 destroyInstance 注册到 atexit 中
        // 程序正常结束时会自动调用该函数释放单例对象
        atexit(&destroyInstance);
    }

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

    // pthread_once 的控制变量，用于保证初始化函数只执行一次
    static pthread_once_t m_once_control;
};

// 静态成员需要在类外定义并初始化
Singleton * Singleton::m_pInstance = nullptr;

// pthread_once 控制变量必须使用 PTHREAD_ONCE_INIT 进行初始化
pthread_once_t Singleton::m_once_control = PTHREAD_ONCE_INIT;


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