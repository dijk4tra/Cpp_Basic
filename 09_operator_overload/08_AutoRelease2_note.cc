#include <iostream>

using std::cout;
using std::endl;

/**
 * 单例的自动释放：
 *
 * 方式二：
 * 利用嵌套类 + 静态的内部类对象。
 *
 * 核心思想：
 *
 * 1. Singleton 类中定义一个内部类 AutoRelease。
 *    AutoRelease 专门负责释放 Singleton 的单例对象。
 *
 * 2. 在 Singleton 类中定义一个 static AutoRelease 对象。
 *    这个静态对象的生命周期会持续到程序结束。
 *
 * 3. 程序结束时，静态对象 m_autoRelease 会自动销毁，
 *    从而调用 AutoRelease 的析构函数。
 *
 * 4. 在 AutoRelease 的析构函数中释放 Singleton 的单例对象。
 *
 * 这样就不需要用户手动调用 destroyInstance。
 */

class Singleton
{
    /**
     * 内部类 AutoRelease。
     *
     * 这个类只为 Singleton 服务，
     * 用来释放 Singleton 的单例对象。
     *
     * 因此把它定义成 Singleton 的内部类，
     * 可以减少全局命名空间污染，
     * 也能体现它和 Singleton 的从属关系。
     *
     * 注意：
     * 这里没有写 public/private，
     * 因为 class 默认访问权限是 private。
     *
     * 所以 AutoRelease 是 Singleton 的 private 内部类，
     * 类外部不能直接使用：
     * Singleton::AutoRelease
     */
    class AutoRelease
    {
    public:
        /**
         * AutoRelease 构造函数。
         *
         * 静态成员对象 m_autoRelease 初始化时，
         * 会自动调用该构造函数。
         */
        AutoRelease()
        {
            cout << "AutoRelease()" << endl;
        }

        /**
         * AutoRelease 析构函数。
         *
         * 程序结束时，
         * 静态成员对象 m_autoRelease 会被自动销毁，
         * 从而调用这个析构函数。
         *
         * 在这里释放 Singleton 的单例对象。
         */
        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;

            /**
             * 如果 m_pInstance 不为空，
             * 说明单例对象已经创建，
             * 需要释放。
             *
             * AutoRelease 是 Singleton 的内部类，
             * 可以访问 Singleton 的 private 静态成员 m_pInstance。
             */
            if(m_pInstance){
                delete m_pInstance;
                m_pInstance = nullptr;
            }
        }
    };

public:
    /**
     * 提供静态函数返回唯一的 Singleton 对象。
     *
     * 因为构造函数是 private 的，
     * 类外部不能直接创建 Singleton 对象。
     *
     * 所以只能通过 getInstance 获取单例对象。
     */
    static Singleton * getInstance()
    {
        /**
         * 如果 m_pInstance 为空，
         * 说明当前还没有创建单例对象。
         *
         * 此时在堆上创建 Singleton 对象，
         * 并让 m_pInstance 保存它的地址。
         */
        if(!m_pInstance){
            m_pInstance = new Singleton{};
        }

        /**
         * 返回 Singleton 的唯一对象地址。
         *
         * 多次调用 getInstance，
         * 返回的都是同一个地址。
         */
        return m_pInstance;
    }

    /**
     * 手动释放单例对象的方式。
     *
     * 如果不使用自动释放机制，
     * 可以提供 destroyInstance 函数手动释放资源。
     *
     * 当前代码使用 AutoRelease 自动释放，
     * 所以这里注释掉。
     */
    /* static void destroyInstance() */
    /* { */
    /*     if(m_pInstance){ */
    /*         delete m_pInstance; */
    /*         m_pInstance = nullptr; */
    /*     } */
    /* } */

    /**
     * 删除拷贝构造函数。
     *
     * 单例对象只能有一个，
     * 不能通过拷贝构造产生新的 Singleton 对象。
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
     * 把 AutoRelease 设置为 Singleton 的友元类。
     *
     * 因为 Singleton 的析构函数是 private 的，
     * 如果 AutoRelease 要 delete m_pInstance，
     * 就需要有权限调用 Singleton 的私有析构函数。
     *
     * 注意：
     * AutoRelease 是嵌套在 Singleton 里面的内部类。
     * 在当前代码中，它已经可以访问 Singleton 的 private 静态成员。
     *
     * 这里声明 friend class AutoRelease，
     * 主要是为了强调 AutoRelease 是管理者类，
     * 它有权限释放 Singleton 对象。
     */
    friend class AutoRelease;

private:
    /**
     * 构造函数私有化。
     *
     * 类外部不能直接创建 Singleton 对象：
     * Singleton s;
     * new Singleton;
     *
     * 只能通过 getInstance 创建和获取唯一对象。
     */
    Singleton(){}

    /**
     * 析构函数私有化。
     *
     * 类外部不能随意 delete Singleton 对象。
     *
     * 单例对象的释放交给 AutoRelease 统一管理。
     */
    ~Singleton(){}

    /**
     * 静态成员指针。
     *
     * 保存 Singleton 唯一对象的地址。
     *
     * static 成员属于类本身，
     * 不属于某个具体对象。
     */
    static Singleton * m_pInstance;

    /**
     * 静态 AutoRelease 对象。
     *
     * m_autoRelease 是 Singleton 类的静态成员对象。
     *
     * 它的作用：
     * 在程序结束时自动调用析构函数，
     * 从而释放 m_pInstance 指向的单例对象。
     *
     * 因为它是 static 成员，
     * 所以需要在类外进行定义。
     */
    static AutoRelease m_autoRelease;
};

/**
 * 静态成员变量类外初始化。
 *
 * m_pInstance 初始化为空指针，
 * 表示程序开始时还没有创建单例对象。
 */
Singleton * Singleton::m_pInstance = nullptr;

/**
 * 静态内部类对象的类外定义。
 *
 * Singleton::AutoRelease 表示：
 * AutoRelease 是定义在 Singleton 内部的类。
 *
 * Singleton::m_autoRelease 表示：
 * m_autoRelease 是 Singleton 的静态成员对象。
 *
 * 这一行会调用 AutoRelease 的默认构造函数。
 *
 * 因为 m_autoRelease 是静态对象，
 * 它会在程序结束时自动析构。
 */
Singleton::AutoRelease Singleton::m_autoRelease; // 默认调用无参构造函数
                                                 // 默认初始化


void test1()
{
    /**
     * 多次调用 getInstance。
     *
     * 第一次调用时会创建 Singleton 对象。
     * 后面再次调用时，直接返回之前创建好的对象。
     *
     * 因此三次输出的地址应该相同。
     */
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;

    /**
     * test1 结束时并不会释放 Singleton 对象。
     *
     * 因为本例中负责释放资源的是静态成员对象 m_autoRelease。
     *
     * m_autoRelease 的生命周期到程序结束才结束，
     * 所以 Singleton 对象会在程序结束阶段被释放。
     */
}

int main(int argc, char * argv[])
{
    test1();

    /**
     * main 函数结束后，
     * 程序进入静态对象销毁阶段。
     *
     * 此时 Singleton::m_autoRelease 被销毁，
     * 调用 ~AutoRelease()，
     * 在析构函数中 delete m_pInstance，
     * 完成单例对象的自动释放。
     */
    return 0;
}