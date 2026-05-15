#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

/**
 * 单例的自动释放：
 *
 * 方式四：
 * 利用 atexit() + destroyInstance() + pthread_once。
 *
 * 这种方式是在方式三的基础上，
 * 进一步解决多线程环境下的安全问题。
 *
 * 方式三中：
 *
 * if(!m_pInstance){
 *     m_pInstance = new Singleton{};
 * }
 *
 * 在单线程环境下没有问题。
 *
 * 但是在多线程环境下，
 * 如果多个线程同时调用 getInstance，
 * 就可能同时进入 if 判断，
 * 从而创建出多个 Singleton 对象。
 *
 * 所以需要保证：
 * 初始化单例对象的操作只能执行一次。
 *
 * pthread_once 的作用：
 *
 * pthread_once 可以保证某个初始化函数
 * 在整个程序运行过程中只会被执行一次。
 *
 * 即使多个线程同时调用 pthread_once，
 * 也只有一个线程会真正执行初始化函数，
 * 其他线程会等待或者直接跳过。
 *
 * 因此：
 * pthread_once 可以用来实现线程安全的单例初始化。
 */

class Singleton
{
public:
    /**
     * 提供静态成员函数，
     * 返回唯一的 Singleton 对象。
     *
     * 外部通过 Singleton::getInstance()
     * 获取单例对象。
     */
    static Singleton * getInstance()
    {
        /**
         * pthread_once 用来保证 initRoutine 只执行一次。
         *
         * 参数说明：
         *
         * 第一个参数：
         * &m_once_control
         * 表示 once 控制变量，
         * 用来记录初始化函数是否已经执行过。
         *
         * 第二个参数：
         * &initRoutine
         * 表示要执行一次的初始化函数。
         *
         * 无论 getInstance 被调用多少次，
         * 甚至在多线程环境下同时调用，
         * initRoutine 都只会执行一次。
         */
        pthread_once(&m_once_control, &initRoutine);

        /**
         * initRoutine 执行完成之后，
         * m_pInstance 已经指向唯一的 Singleton 对象。
         *
         * 后续再调用 getInstance，
         * pthread_once 不会再次执行 initRoutine，
         * 直接返回同一个对象地址。
         */
        return m_pInstance;
    }

    /**
     * 用来初始化单例对象的函数。
     *
     * 这个函数会被 pthread_once 调用。
     *
     * 注意：
     * pthread_once 要求传入的函数类型是：
     * void (*)(void)
     *
     * 所以这里 initRoutine 必须是：
     * 1. 静态成员函数
     * 2. 无参数
     * 3. 返回值为 void
     *
     * 普通成员函数不能直接传给 pthread_once，
     * 因为普通成员函数依赖 this 指针。
     */
    static void initRoutine()
    {
        /**
         * 初始化函数只会被执行一次。
         *
         * 在这里创建 Singleton 单例对象。
         */
        m_pInstance = new Singleton{};

        /**
         * 把 destroyInstance 注册到 atexit 中。
         *
         * 当程序正常结束时，
         * destroyInstance 会自动被调用，
         * 从而释放单例对象。
         */
        atexit(&destroyInstance);
    }

    /**
     * 提供回收资源的操作。
     *
     * 程序正常结束时，
     * atexit 会自动调用 destroyInstance。
     */
    static void destroyInstance()
    {
        cout << "destroyInstance" << endl;

        /**
         * 如果 m_pInstance 不为空，
         * 说明单例对象已经创建，
         * 需要释放。
         */
        if(m_pInstance){
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

    /**
     * 删除拷贝构造函数。
     *
     * 单例对象只能有一个，
     * 不能通过拷贝构造创建新的对象。
     */
    Singleton(const Singleton &) = delete;

    /**
     * 删除赋值运算符函数。
     *
     * 防止 Singleton 对象之间进行赋值，
     * 保证单例语义。
     */
    Singleton& operator=(const Singleton &) = delete;

    /**
     * 这里保留友元声明。
     *
     * 当前代码中没有定义 AutoRelease 类，
     * 释放操作由 destroyInstance 完成。
     *
     * 如果后续改成管理者类释放单例对象，
     * 并且 Singleton 析构函数是 private，
     * 就需要把管理者类声明为 friend。
     */
    friend class AutoRelease;

private:
    /**
     * 构造函数私有化。
     *
     * 类外部不能直接创建 Singleton 对象。
     *
     * 只能通过 getInstance 获取唯一对象。
     */
    Singleton(){}

    /**
     * 析构函数私有化。
     *
     * 类外部不能随意 delete Singleton 对象。
     *
     * 当前由 Singleton 自己的静态成员函数
     * destroyInstance 负责释放对象。
     */
    ~Singleton(){}

    /**
     * 静态成员指针。
     *
     * 保存 Singleton 唯一对象的地址。
     */
    static Singleton * m_pInstance;

    /**
     * pthread_once_t 类型的静态控制变量。
     *
     * 它配合 pthread_once 使用，
     * 用来保证 initRoutine 只执行一次。
     *
     * 该变量必须使用 PTHREAD_ONCE_INIT 初始化。
     */
    static pthread_once_t m_once_control;
};

/**
 * 静态成员变量类外初始化。
 *
 * m_pInstance 初始化为空指针，
 * 表示程序开始时还没有创建单例对象。
 */
Singleton * Singleton::m_pInstance = nullptr;

/**
 * pthread_once 控制变量的初始化。
 *
 * PTHREAD_ONCE_INIT 是 pthread 库提供的宏，
 * 用来初始化 pthread_once_t 类型的变量。
 */
pthread_once_t Singleton::m_once_control = PTHREAD_ONCE_INIT;


void test1()
{
    /**
     * 多次调用 getInstance。
     *
     * 第一次调用时：
     * 1. pthread_once 执行 initRoutine
     * 2. initRoutine 创建 Singleton 对象
     * 3. 注册 destroyInstance 到 atexit
     *
     * 后续调用时：
     * pthread_once 不会再次执行 initRoutine，
     * 直接返回之前创建好的对象。
     *
     * 所以下面三次输出的地址应该相同。
     */
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
}

int main(int argc, char * argv[])
{
    /**
     * 测试线程安全版本的单例获取。
     */
    test1();

    /**
     * main 函数结束后，
     * 程序正常退出。
     *
     * atexit 中注册的 destroyInstance 会被调用，
     * 释放 Singleton 单例对象。
     */
    return 0;
}