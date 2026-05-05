#include <iostream>

using std::cout;
using std::endl;

/**
 * 单例实现方式二：
 * 单例对象创建在堆上。
 *
 * 注意：
 * 当前这种写法是线程不安全的。
 *
 *
 * 单例模式的目标：
 * 保证某个类在整个程序中只有一个对象。
 *
 * 不管调用 getInstance 多少次，
 * 获取到的都应该是同一个对象。
 *
 *
 * 实现步骤：
 *
 * 1. 构造函数私有化
 *
 *    防止类外直接创建对象。
 *
 *    例如：
 *    Singleton s1;
 *
 *    如果构造函数是 private，
 *    上面的写法在类外会报错。
 *
 *
 * 2. 提供一个 public static 函数
 *
 *    因为构造函数私有后，
 *    类外无法先创建对象，
 *    所以需要通过静态成员函数作为访问入口。
 *
 *    调用方式：
 *    Singleton::getInstance();
 *
 *
 * 3. 在 getInstance 函数中保证对象唯一
 *
 *    如果对象还没有创建，
 *    就使用 new 创建一个对象。
 *
 *    如果对象已经创建，
 *    就直接返回之前创建好的对象地址。
 *
 *
 * 4. 提供一个自身类型的 static 指针
 *
 *    static Singleton * m_pInstance;
 *
 *    这个指针属于类本身，
 *    所有调用者共享同一个指针。
 *
 *    它用来保存堆上唯一对象的地址。
 *
 *
 * 5. 提供释放资源的函数
 *
 *    因为对象是通过 new 创建在堆上的，
 *    不会像栈对象一样自动销毁。
 *
 *    所以需要手动 delete。
 *
 *
 * 和“静态局部对象版本”的区别：
 *
 * 1. 静态局部对象版本
 *    对象创建在静态区，
 *    程序结束时自动销毁。
 *
 * 2. 堆对象版本
 *    对象创建在堆区，
 *    需要手动释放。
 *
 *
 * 当前写法的主要问题：
 *
 * 线程不安全。
 *
 * 如果多个线程同时第一次调用 getInstance，
 * 可能会创建出多个 Singleton 对象，
 * 从而破坏单例。
 */

class Singleton
{
public:
    /**
     * 获取单例对象
     *
     * 返回类型：
     * Singleton *
     *
     * 表示返回唯一 Singleton 对象的地址。
     *
     * 因为对象创建在堆上，
     * 所以这里使用指针保存和返回对象。
     */
    static Singleton * getInstance()
    {
        /*
         * 假设有两个线程：
         * A 线程和 B 线程。
         *
         * 初始状态：
         * m_pInstance == nullptr
         *
         * 也就是说，单例对象还没有被创建。
         */

        /*
         * 判断单例对象是否已经创建。
         *
         * if(!m_pInstance)
         *
         * 等价于：
         * if(m_pInstance == nullptr)
         *
         *
         * 如果 m_pInstance 为空，
         * 说明还没有创建 Singleton 对象。
         */
        if(!m_pInstance){
            /*
             * 这里存在线程安全问题。
             *
             * 假设执行过程如下：
             *
             * 1. A 线程先进入 getInstance。
             * 2. A 线程判断 m_pInstance 为空，
             *    进入 if 语句。
             * 3. A 线程还没来得及执行 new Singleton{}，
             *    就发生了线程切换。
             * 4. B 线程进入 getInstance。
             * 5. B 线程也判断 m_pInstance 为空，
             *    也进入 if 语句。
             * 6. B 线程 new 了一个 Singleton 对象。
             * 7. 线程切回 A。
             * 8. A 线程继续执行，
             *    又 new 了一个 Singleton 对象。
             *
             * 结果：
             * 堆上可能出现两个 Singleton 对象，
             * 单例被破坏。
             */
            m_pInstance = new Singleton{};
        }

        /*
         * 返回唯一对象的地址。
         *
         * 正常情况下，
         * 多次调用 getInstance 返回的地址应该相同。
         */
        return m_pInstance;
    }

    /**
     * 释放单例对象
     *
     * 因为当前单例对象是通过 new 创建在堆上的，
     * 所以程序结束前需要使用 delete 释放。
     *
     * destroyInstance 通常在程序退出前调用。
     */
    static void destroyInstance()
    {
        /*
         * 判断指针是否为空。
         *
         * 如果 m_pInstance 不是 nullptr，
         * 说明堆上的单例对象还存在，
         * 可以 delete。
         *
         * 如果 m_pInstance 已经是 nullptr，
         * 说明对象不存在，
         * 不需要释放。
         */
        if(m_pInstance){
            /*
             * delete 会完成两件事情：
             *
             * 1. 调用 Singleton 的析构函数。
             * 2. 释放对象占用的堆内存。
             *
             * 当前类中没有显式写析构函数，
             * 编译器会自动生成默认析构函数。
             */
            delete m_pInstance;

            /*
             * delete 之后，
             * m_pInstance 原来保存的地址已经失效。
             *
             * 为了避免野指针问题，
             * 将它置为 nullptr。
             */
            m_pInstance = nullptr;
        }
    }

    /*
     * 删除拷贝构造函数
     *
     * 禁止通过已有 Singleton 对象
     * 再拷贝出一个新的 Singleton 对象。
     *
     * 例如：
     *
     * Singleton s = *Singleton::getInstance();
     *
     * 上面这种写法会尝试拷贝构造，
     * 如果不删除拷贝构造函数，
     * 就可能破坏单例。
     */
    Singleton(const Singleton &) = delete;

    /*
     * 删除赋值运算符函数
     *
     * 禁止 Singleton 对象之间进行赋值操作。
     *
     * 这是单例模式中常见的保护措施，
     * 用来防止误用。
     */
    Singleton& operator=(const Singleton &) = delete;

private:
    /*
     * 构造函数私有化
     *
     * 类外不能直接创建 Singleton 对象。
     *
     * 下面这种写法会报错：
     *
     * Singleton s1;
     *
     * 外部只能通过 getInstance 获取对象。
     */
    Singleton(){}

    /*
     * 自身类型的静态指针
     *
     * static Singleton * m_pInstance;
     *
     * 作用：
     * 保存堆上唯一 Singleton 对象的地址。
     *
     *
     * 为什么要写成 static？
     *
     * 因为 m_pInstance 不应该属于某一个对象，
     * 而应该属于 Singleton 这个类。
     *
     * 所有地方调用 getInstance，
     * 都应该访问同一个 m_pInstance。
     *
     *
     * 注意：
     * 这里只是类内声明。
     *
     * 静态成员变量通常还需要在类外定义和初始化。
     */
    static Singleton * m_pInstance;
};

/*
 * 类外定义并初始化静态成员变量
 *
 * 语法：
 * 类型 类名::静态成员变量名 = 初始值;
 *
 * 这里表示：
 * Singleton 类中的静态成员变量 m_pInstance
 * 初始值为 nullptr。
 *
 * nullptr 表示当前还没有创建单例对象。
 */
Singleton * Singleton::m_pInstance = nullptr;

void test1()
{
    /*
     * 多次调用 getInstance。
     *
     * 如果单例实现正确，
     * 三次输出的地址应该相同。
     *
     * 第一次调用：
     * m_pInstance 为空，
     * new 一个 Singleton 对象，
     * 然后返回该对象地址。
     *
     * 后两次调用：
     * m_pInstance 已经不为空，
     * 直接返回之前保存的地址。
     */
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;

    /*
     * 释放堆上的单例对象。
     *
     * 因为该对象是通过 new 创建的，
     * 所以需要手动调用 destroyInstance 释放。
     *
     * 如果不释放，
     * 就会造成内存泄漏。
     */
    Singleton::destroyInstance();
}

int main(int argc, char * argv[])
{
    /*
     * 测试堆对象版本的单例。
     */
    test1();

    return 0;
}
