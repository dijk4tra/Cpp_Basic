#include <iostream>

using std::cout;
using std::endl;

/**
 * 特殊的成员函数：
 * 1. 静态成员函数
 * 2. const 成员函数
 *
 *
 * 静态成员函数 static member function：
 * 使用 static 修饰的成员函数。
 *
 * 语法：
 * class 类名
 * {
 * public:
 *     static 返回类型 函数名(参数列表)
 *     {
 *         函数体
 *     }
 * };
 *
 *
 * 静态成员函数的特点：
 * 1. 不依赖具体对象
 *    普通成员函数依赖某个对象调用，
 *    静态成员函数属于类本身，
 *    因此可以通过类名作用域方式调用。
 *
 * 2. 静态成员函数中没有 this 指针
 *    this 指针表示当前对象的地址。
 *    但是静态成员函数不依赖对象，
 *    所以它内部没有 this。
 *
 * 3. 静态成员函数可以直接访问静态成员
 *    因为静态成员也属于类本身。
 *
 * 4. 静态成员函数不能直接访问非静态成员
 *    因为非静态成员依赖具体对象。
 *    没有对象，就无法确定访问的是哪一个对象的数据。
 *
 *
 * 静态成员函数 VS 普通成员函数：
 *
 * 1. 静态成员函数
 *    可以直接访问静态成员变量和静态成员函数。
 *    不能直接访问非静态成员变量和非静态成员函数。
 *
 * 2. 普通成员函数
 *    既可以访问静态成员，
 *    也可以访问非静态成员。
 *    因为普通成员函数调用时一定依赖某个对象，
 *    内部存在 this 指针。
 *
 *
 * 小结：
 * 静态成员函数中可以直接访问静态的东西，
 * 但是不能直接访问非静态的东西。
 *
 * 如果一定要在静态成员函数中访问非静态成员，
 * 需要先创建对象，
 * 再通过对象访问。
 *
 *
 * 静态成员函数的常见应用场景：
 * 1. 工具类中的函数
 *    工具类通常不需要创建对象，
 *    只需要通过类名直接调用函数。
 *
 * 例如：
 * class DBUtils
 * {
 * public:
 *     // 获取数据库连接
 *     static Connection getConnection(string user, string password)
 *     {
 *
 *     }
 *
 *     // 释放数据库连接
 *     static void close()
 *     {
 *
 *     }
 * };
 *
 * 常见工具类：
 * class ThreadUtils {}
 * class StringUtils {}
 * class DateUtils {}
 * class FileUtils {}
 */

class MyClass
{
public:
    /**
     * 静态成员函数
     *
     * static 修饰成员函数后，
     * 这个函数就不再依赖某一个具体对象，
     * 而是属于整个类。
     *
     * 因此它既可以通过对象调用，
     * 也可以通过类名作用域调用。
     *
     * 推荐写法：
     * MyClass::func();
     */
    static void func()
    {
        cout << "static func()" << endl;
    }

    /**
     * 静态成员函数访问测试
     *
     * 重点：
     * 静态成员函数中没有 this 指针，
     * 所以不能直接访问非静态成员。
     */
    static void func2()
    {
        /*
         * m_data1 是非静态成员变量。
         * 非静态成员变量属于具体对象，
         * 必须通过对象访问。
         *
         * 当前 func2 是静态成员函数，
         * 内部没有 this 指针，
         * 所以不能直接写 m_data1。
         */
        /* m_data1; */

        /*
         * normalFunc 是非静态成员函数。
         * 调用普通成员函数也需要具体对象。
         *
         * 静态成员函数中没有 this，
         * 所以不能直接调用 normalFunc。
         */
        /* normalFunc(); */

        /*
         * 静态成员函数中没有 this 指针。
         * this 只存在于非静态成员函数中。
         */
        /* this; */

        /*
         * 如果一定要在静态成员函数中访问非静态成员，
         * 可以先创建一个对象，
         * 再通过这个对象访问。
         *
         * obj 是 MyClass 类型的对象，
         * 所以可以访问 obj.m_data1，
         * 也可以调用 obj.normalFunc()。
         */
        MyClass obj;
        obj.m_data1;
        obj.normalFunc();

        /*
         * m_data2 是静态成员变量。
         * 静态成员变量属于类，
         * 不依赖某一个具体对象，
         * 所以静态成员函数可以直接访问。
         */
        m_data2; // ok

        /*
         * func 是静态成员函数。
         * 静态成员函数内部可以直接调用其他静态成员函数。
         */
        func(); // ok
    }

    // 普通成员函数
    void normalFunc()
    {

    }

    /**
     * 普通成员函数访问测试
     *
     * 普通成员函数依赖对象调用，
     * 内部存在 this 指针。
     *
     * 所以普通成员函数既可以访问静态成员，
     * 也可以访问非静态成员。
     */
    void normalFunc2()
    {
        // 访问静态成员函数
        func();

        // 访问静态成员变量
        m_data2;

        // 访问普通成员函数
        normalFunc();

        // 访问普通成员变量
        m_data1;
    }

    /*
     * 普通成员变量
     *
     * m_data1 属于具体对象。
     * 每创建一个 MyClass 对象，
     * 这个对象中都会有自己独立的一份 m_data1。
     */
    int m_data1;

    /*
     * 静态成员变量
     *
     * static 修饰成员变量后，
     * 该成员变量属于类本身，
     * 所有对象共享同一份 m_data2。
     *
     * 注意：
     * 这里只是在类中声明静态成员变量。
     * 如果程序中真正使用它，
     * 通常还需要在类外进行定义：
     *
     * int MyClass::m_data2 = 0;
     */
    static int m_data2;
};

void test1()
{
    /*
     * 静态成员函数一般推荐通过类名作用域方式调用。
     *
     * 这种写法能清楚地表示：
     * func 是属于 MyClass 这个类的，
     * 而不是属于某一个具体对象的。
     */
    MyClass::func();

    /*
     * 静态成员函数也可以通过对象调用。
     *
     * 但是这种写法容易让人误以为 func 依赖 obj，
     * 实际上 func 并不依赖对象。
     *
     * 所以静态成员函数更推荐使用：
     * MyClass::func();
     */
    MyClass obj;
    obj.func();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}


/*
#include <iostream>

using std::cout;
using std::endl;

class MyClass
{
public:
    static void func()
    {
        cout << "static func()" << endl;
    }

    static void func2()
    {
        // m_data1;
        // normalFunc();
        // this;

        MyClass obj;
        obj.m_data1;
        obj.normalFunc();

        m_data2;
        func();
    }

    void normalFunc()
    {

    }

    void normalFunc2()
    {
        func();
        m_data2;

        normalFunc();
        m_data1;
    }

    int m_data1;
    static int m_data2;
};

void test1()
{
    MyClass::func();

    MyClass obj;
    obj.func();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}
*/