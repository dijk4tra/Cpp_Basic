#include <iostream>

using std::cout;
using std::endl;

/**
 * 单例设计模式 Singleton
 *
 * 单例模式的作用：
 * 保证某个类型的对象在整个系统中只有一份。
 *
 * 不管获取多少次，
 * 拿到的始终都是同一个对象。
 *
 *
 * 单例模式的典型应用场景：
 *
 * 1. 配置管理器
 *    整个程序中只需要一份配置对象。
 *
 * 2. 日志系统
 *    多处代码写日志时，
 *    可以共享同一个日志对象。
 *
 * 3. 线程池
 *    线程池通常是全局共享资源，
 *    不希望随意创建多个。
 *
 * 4. 数据库连接池
 *    统一管理数据库连接资源。
 *
 *
 * 单例设计模式的实现步骤：
 *
 * 1. 构造函数私有化
 *
 *    使用 private 修饰构造函数。
 *
 *    目的：
 *    禁止类外直接创建对象。
 *
 *    例如：
 *    Singleton s1;
 *    Singleton s2;
 *
 *    如果构造函数是 private，
 *    上面的写法在类外就会报错。
 *
 *
 * 2. 提供一个 public 函数返回唯一对象
 *
 *    这个函数通常写成静态成员函数。
 *
 *    原因：
 *    构造函数私有后，类外无法先创建对象，
 *    所以不能通过对象调用普通成员函数。
 *
 *    因此需要通过类名直接调用：
 *
 *    Singleton::getInstance();
 *
 *
 * 3. 在函数中保证对象唯一
 *
 *    可以在 getInstance 函数内部定义一个 static 局部对象。
 *
 *    static 局部对象的特点：
 *    1. 只初始化一次。
 *    2. 生命周期从第一次执行到该定义语句开始，
 *       一直到程序结束。
 *    3. 多次调用函数时，
 *       使用的是同一个 static 局部对象。
 *
 *
 * 4. 通常删除拷贝构造函数和赋值运算符函数
 *
 *    原因：
 *    即使不能直接调用构造函数创建对象，
 *    仍然可能通过拷贝的方式创建新对象。
 *
 *    例如：
 *    Singleton s1 = Singleton::getInstance();
 *
 *    如果拷贝构造函数没有被禁止，
 *    这会创建出一个新的 Singleton 对象，
 *    破坏单例。
 *
 *    所以通常使用 = delete 删除复制控制函数。
 *
 *
 * 实现方式一：
 * 单例对象创建在静态区。
 *
 * 这里使用函数内部的 static 局部对象实现。
 */

class Singleton
{
public:
    /**
     * 获取单例对象
     *
     * static 成员函数：
     * 不依赖具体对象，
     * 可以直接通过类名调用。
     *
     * 调用方式：
     * Singleton::getInstance();
     *
     *
     * 返回类型：
     * Singleton &
     *
     * 这里返回引用，
     * 表示返回的是唯一对象本身，
     * 而不是返回对象的副本。
     *
     * 如果返回值不是引用，
     * 就可能发生拷贝，
     * 破坏单例模式。
     */
    static Singleton & getInstance()
    {
        /*
         * static 局部对象
         *
         * instance 是函数内部的静态局部对象。
         *
         * 特点：
         * 1. 第一次调用 getInstance 时初始化。
         * 2. 后续再次调用 getInstance 时，
         *    不会重新创建对象。
         * 3. 程序结束时自动销毁。
         *
         * 因此 instance 可以保证整个程序中只有一份。
         *
         *
         * C++11 以后：
         * 函数内部 static 局部对象的初始化是线程安全的。
         */
        static Singleton instance;

        /*
         * 返回唯一对象。
         *
         * 这里返回的是 instance 的引用。
         *
         * 多次调用 getInstance，
         * 返回的都是同一个 instance 对象。
         */
        return instance;
    }

    /*
     * 删除拷贝构造函数
     *
     * Singleton(const Singleton &) = delete;
     *
     * 表示禁止使用一个 Singleton 对象
     * 拷贝构造另一个 Singleton 对象。
     *
     * 例如下面的代码会报错：
     *
     * Singleton s1 = Singleton::getInstance();
     */
    Singleton(const Singleton &) = delete;

    /*
     * 删除赋值运算符函数
     *
     * Singleton & operator=(const Singleton &) = delete;
     *
     * 表示禁止两个 Singleton 对象之间进行赋值。
     *
     * 例如下面的代码会报错：
     *
     * Singleton & s1 = Singleton::getInstance();
     * Singleton & s2 = Singleton::getInstance();
     * s1 = s2;
     *
     * 虽然 s1 和 s2 实际上是同一个对象，
     * 但是为了防止误用，
     * 通常也会删除赋值运算符函数。
     */
    Singleton & operator = (const Singleton &) = delete;

private:
    /*
     * 构造函数私有化
     *
     * 构造函数放在 private 区域，
     * 类外就不能直接创建 Singleton 对象。
     *
     * 也就是说，下面的写法在类外都会报错：
     *
     * Singleton s1;
     * Singleton s2;
     *
     *
     * 只能通过 public 的 getInstance 函数
     * 获取唯一的 Singleton 对象。
     */
    Singleton(){}
};

void test1()
{
    /*
     * 因为 Singleton 的构造函数是 private，
     * 所以类外不能直接创建对象。
     *
     * 下面这些写法都会报错。
     */
    /* Singleton s1; */
    /* Singleton s2; */
    /* Singleton s3; */

    /*
     * 通过类名作用域调用静态成员函数 getInstance。
     *
     * getInstance 返回唯一的 Singleton 对象。
     *
     * 这里使用 & 取地址，
     * 用来观察多次获取到的对象地址是否相同。
     *
     * 如果三次输出的地址完全相同，
     * 说明三次拿到的是同一个对象。
     */
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
}

int main(int argc, char *argv[])
{
    /*
     * 测试单例对象是否唯一。
     */
    test1();

    return 0;
}


/*
#include <iostream>

using std::cout;
using std::endl;

class Singleton
{
public:
    static Singleton & getInstance()
    {
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;

private:
    Singleton()
    {}
};

void test1()
{
    // Singleton s1;
    // Singleton s2;
    // Singleton s3;

    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}
*/