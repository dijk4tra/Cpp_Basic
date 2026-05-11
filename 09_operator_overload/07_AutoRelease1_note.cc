#include <iostream>

using std::cout;
using std::endl;

/**
 * 单例的自动释放：
 *
 * 单例模式中，通常会在堆上创建唯一对象，
 * 并通过静态成员指针保存这个对象的地址。
 *
 * 但是如果只创建不释放，
 * 就会造成资源泄漏。
 *
 * 自动释放方式一：
 * 利用栈对象的生命周期进行自动释放。
 *
 * 核心思想：
 * 把单例对象当作一种资源，
 * 交给另一个栈对象管理。
 *
 * 这个负责管理资源的对象，
 * 这里叫做 AutoRelease。
 *
 * 当 AutoRelease 对象生命周期结束时，
 * 会自动调用它的析构函数。
 *
 * 在 AutoRelease 的析构函数中，
 * 释放 Singleton 单例对象。
 *
 * 这也是 RAII 思想：
 * Resource Acquisition Is Initialization
 * 资源获取即初始化。
 */

class Singleton
{
public:
    /**
     * 提供静态成员函数，
     * 返回唯一的 Singleton 对象。
     *
     * 因为构造函数是 private 的，
     * 类外部不能直接创建 Singleton 对象。
     *
     * 所以只能通过 getInstance 获取唯一对象。
     */
    static Singleton * getInstance()
    {
        /**
         * 如果 m_pInstance 为空，
         * 说明当前还没有创建单例对象。
         *
         * 此时在堆上创建一个 Singleton 对象，
         * 并让 m_pInstance 保存它的地址。
         */
        if(!m_pInstance){
            m_pInstance = new Singleton{};
        }

        /**
         * 如果 m_pInstance 不为空，
         * 说明单例对象已经存在，
         * 直接返回原来的对象地址。
         *
         * 这样可以保证多次调用 getInstance，
         * 得到的是同一个对象。
         */
        return m_pInstance;
    }

    /**
     * 手动回收单例对象的方式。
     *
     * 如果不使用 AutoRelease 管理资源，
     * 也可以提供一个静态函数 destroyInstance，
     * 专门负责释放单例对象。
     *
     * 当前代码中注释掉了这个函数，
     * 因为这里演示的是通过管理者对象自动释放。
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
     * 单例对象应该只有一个，
     * 不能通过拷贝构造创建新的 Singleton 对象。
     */
    Singleton(const Singleton &) = delete;

    /**
     * 删除赋值运算符函数。
     *
     * 防止两个 Singleton 对象之间进行赋值。
     *
     * 虽然外部无法直接创建 Singleton 对象，
     * 但为了保证单例语义完整，
     * 一般仍然会删除复制控制相关函数。
     */
    Singleton& operator=(const Singleton &) = delete;

    /**
     * 把 AutoRelease 声明为 Singleton 的友元类。
     *
     * 因为 Singleton 的析构函数是 private 的，
     * 类外部不能直接 delete Singleton 对象。
     *
     * 但是 AutoRelease 需要在析构函数中释放 Singleton 对象，
     * 所以必须让 AutoRelease 拥有访问 Singleton 私有析构函数的权限。
     */
    friend class AutoRelease;

private:
    /**
     * 构造函数私有化。
     *
     * 这样类外部不能直接写：
     * Singleton s;
     * new Singleton;
     *
     * 只能通过 getInstance 获取唯一对象。
     */
    Singleton(){}

    /**
     * 析构函数私有化。
     *
     * 这样类外部不能随意 delete Singleton 对象，
     * 避免破坏单例对象的生命周期管理。
     *
     * 因为 AutoRelease 是友元类，
     * 所以 AutoRelease 可以调用这个私有析构函数。
     */
    ~Singleton(){}

    /**
     * 静态成员指针。
     *
     * 用来保存唯一 Singleton 对象的地址。
     *
     * static 成员属于类本身，
     * 不属于某一个具体对象。
     */
    static Singleton * m_pInstance;
};

/**
 * 静态成员变量需要在类外进行定义和初始化。
 *
 * 这里初始化为空指针，
 * 表示程序开始时还没有创建单例对象。
 */
Singleton * Singleton::m_pInstance = nullptr;


/**
 * 管理者类。
 *
 * AutoRelease 用来管理 Singleton 单例对象。
 *
 * 它本身是一个栈对象，
 * 当 AutoRelease 对象离开作用域时，
 * 析构函数会自动执行，
 * 从而释放它管理的 Singleton 对象。
 */
class AutoRelease
{
public:
    /**
     * 构造函数。
     *
     * 参数 p 是 Singleton 对象的指针。
     *
     * AutoRelease 接收这个指针后，
     * 就负责管理它指向的资源。
     */
    AutoRelease(Singleton * p)
    : m_p(p)
    {
        cout << "AutoRelease(Singleton*)" << endl;
    }

    /**
     * 析构函数。
     *
     * 当 AutoRelease 栈对象生命周期结束时，
     * 自动调用析构函数释放单例对象。
     */
    ~AutoRelease()
    {
        cout << "~AutoRelease()" << endl;

        /**
         * 如果 m_p 不为空，
         * 说明当前管理着 Singleton 对象，
         * 需要释放。
         *
         * 因为 AutoRelease 是 Singleton 的友元类，
         * 所以这里可以 delete 一个析构函数为 private 的 Singleton 对象。
         */
        if(m_p){
            delete m_p;
            m_p = nullptr;
        }
    }

private:
    /**
     * 保存被管理资源的地址。
     *
     * 这里 m_p 指向 Singleton 的唯一对象。
     */
    Singleton * m_p;
};

void test1()
{
    /**
     * 创建管理者对象 ar。
     *
     * ar 是一个栈对象，
     * 它负责管理 Singleton::getInstance() 返回的单例对象。
     *
     * 当 test1 函数结束时，
     * ar 会自动销毁，
     * 从而调用 AutoRelease 的析构函数，
     * 释放 Singleton 单例对象。
     */
    AutoRelease ar { Singleton::getInstance() };

    /**
     * 多次调用 getInstance。
     *
     * 因为 Singleton 是单例，
     * 所以下面三次输出的地址应该相同。
     */
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;

    /**
     * test1 结束时：
     *
     * 1. ar 生命周期结束
     * 2. 自动调用 ~AutoRelease()
     * 3. delete m_p
     * 4. 调用 Singleton 的私有析构函数
     * 5. 单例对象被释放
     *
     * 注意：
     * 当前 AutoRelease 析构函数中只把自己的 m_p 置空，
     * 但是没有把 Singleton::m_pInstance 置空。
     *
     * 如果单例对象释放之后，
     * 后续再次调用 Singleton::getInstance()，
     * m_pInstance 仍然保存着已经释放的地址，
     * 可能产生悬空指针问题。
     *
     * 更稳妥的写法是：
     * delete 之后同时把 Singleton::m_pInstance 也置为 nullptr。
     */
}

int main(int argc, char * argv[])
{
    test1();

    return 0;
}