#include <iostream>

using std::cout;
using std::endl;

/**
 * 单例的自动释放：
 *
 * 方式三：
 * 利用 atexit() + destroyInstance()。
 *
 * atexit 是 C/C++ 标准库提供的函数，
 * 作用是：
 * 把一个函数注册到程序正常结束时自动调用。
 *
 * atexit 的参数是函数指针。
 *
 * 例如：
 * atexit(&func);
 *
 * 表示把 func 函数注册到 atexit 中。
 *
 * 当程序正常结束时，
 * 被注册到 atexit 中的函数会被自动调用。
 *
 * 注意：
 * 如果注册了多个函数，
 * 执行顺序是：
 * 后注册的先执行，
 * 先注册的后执行。
 *
 * 单例的两种创建模式：
 *
 * 1. 懒加载 / 懒汉模式
 *    不使用时不创建对象，
 *    第一次调用 getInstance 时才创建对象。
 *
 * 2. 立即加载 / 饿汉模式
 *    不管后面用不用，
 *    程序开始时就先把单例对象创建出来。
 */

class Singleton
{
public:
    /**
     * 提供静态成员函数，
     * 返回唯一的 Singleton 对象。
     *
     * 当前写法属于懒加载：
     * 第一次调用 getInstance 时才创建对象。
     */
    static Singleton * getInstance()
    {
        /**
         * 如果 m_pInstance 为空，
         * 说明当前还没有创建单例对象。
         */
        if(!m_pInstance){
            /**
             * 在堆上创建 Singleton 对象，
             * 并让 m_pInstance 保存这个对象的地址。
             */
            m_pInstance = new Singleton{};

            /**
             * 把 destroyInstance 函数注册到 atexit 中。
             *
             * 当程序正常结束时，
             * destroyInstance 会被自动调用，
             * 从而释放单例对象。
             *
             * 注意：
             * 这里放在 if 里面，
             * 可以保证 destroyInstance 只注册一次。
             */
            atexit(&destroyInstance);
        }

        /**
         * 返回唯一对象的地址。
         *
         * 多次调用 getInstance，
         * 返回的都是同一个地址。
         */
        return m_pInstance;
    }

    /**
     * 立即加载 / 饿汉模式时，
     * getInstance 可以直接返回已经创建好的对象。
     *
     * 对应的静态成员初始化方式是：
     * Singleton * Singleton::m_pInstance = new Singleton{};
     */
    /* static Singleton * getInstance() */
    /* { */
    /*     return m_pInstance; */
    /* } */

    /**
     * 提供回收资源的操作。
     *
     * destroyInstance 是静态成员函数，
     * 可以直接通过函数指针注册到 atexit 中。
     *
     * 程序结束时，
     * atexit 会自动调用这个函数。
     */
    static void destroyInstance()
    {
        cout << "destroyInstance" << endl;

        /**
         * 如果 m_pInstance 不为空，
         * 说明单例对象存在，
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
     * 不能通过拷贝构造产生新对象。
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
     * 当前代码使用 atexit + destroyInstance 自动释放，
     * 不再需要 AutoRelease 管理者类。
     *
     * 如果后续改回管理者类释放单例对象，
     * 并且 Singleton 析构函数是 private，
     * 就需要把管理者类声明为 friend。
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
     * 只能通过 getInstance 获取唯一对象。
     */
    Singleton(){}

    /**
     * 析构函数私有化。
     *
     * 类外部不能随意 delete Singleton 对象。
     *
     * 当前由类自己的静态成员函数 destroyInstance 负责释放。
     */
    ~Singleton(){}

    /**
     * 静态成员指针。
     *
     * 用来保存唯一 Singleton 对象的地址。
     */
    static Singleton * m_pInstance;
};

/**
 * 静态成员类外初始化。
 *
 * 懒加载写法：
 * m_pInstance 初始为空。
 *
 * 只有第一次调用 getInstance 时，
 * 才会真正 new Singleton。
 */
Singleton * Singleton::m_pInstance = nullptr;

/**
 * 立即加载 / 饿汉模式写法：
 *
 * 程序开始时就创建 Singleton 对象。
 *
 * 注意：
 * 如果使用这种方式，
 * getInstance 中就不需要再判断和 new，
 * 可以直接返回 m_pInstance。
 */
/* Singleton * Singleton::m_pInstance = new Singleton{}; */


/**
 * 普通函数 func。
 *
 * 用来演示 atexit 注册普通函数。
 */
void func()
{
    cout << "func()" << endl;
}

/**
 * 普通函数 func2。
 */
void func2()
{
    cout << "func2()" << endl;
}

void test0()
{
    cout << "test0 start" << endl;

    /**
     * 直接调用 func，
     * 会立即执行 func 函数。
     */
    /* func(); */

    /**
     * 把 func 注册到 atexit 中。
     *
     * 注意：
     * 注册并不会立即执行 func，
     * 而是等程序正常结束时再执行。
     */
    atexit(&func);

    /**
     * 同一个函数可以被注册多次。
     *
     * 注册几次，
     * 程序结束时就会执行几次。
     */
    atexit(&func);

    /**
     * 把 func2 也注册到 atexit 中。
     */
    atexit(&func2);

    /**
     * atexit 的执行顺序：
     *
     * 先注册的后执行，
     * 后注册的先执行。
     *
     * 当前注册顺序：
     * 1. func
     * 2. func
     * 3. func2
     *
     * 程序结束时执行顺序：
     * 1. func2
     * 2. func
     * 3. func
     */
    cout << "test0 end" << endl;
}

void test1()
{
    /**
     * 多次调用 getInstance。
     *
     * 第一次调用：
     * 1. m_pInstance 为空
     * 2. 创建 Singleton 对象
     * 3. 注册 destroyInstance 到 atexit
     * 4. 返回对象地址
     *
     * 后续调用：
     * m_pInstance 不为空，
     * 直接返回同一个地址。
     *
     * 所以三次输出的地址相同。
     */
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
}

int main(int argc, char * argv[])
{
    cout << "main statr" << endl;

    /**
     * test0 用来测试 atexit 注册普通函数。
     *
     * test1 用来测试 atexit 自动释放单例对象。
     */
    /* test0(); */
    test1();

    cout << "main end" << endl;

    /**
     * main 函数 return 之后，
     * 程序正常结束。
     *
     * 此时 atexit 中注册的 destroyInstance 会被自动调用，
     * 释放 Singleton 单例对象。
     */
    return 0;
}