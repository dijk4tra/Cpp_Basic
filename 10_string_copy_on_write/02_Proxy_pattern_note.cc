#include <iostream>

using std::cout;
using std::endl;

/**
 * 代理设计模式：Proxy Pattern
 *
 * 代理模式中一般有两个角色：
 *
 * 1. 委托类
 *    真正做事情的类。
 *
 * 2. 代理类
 *    不直接完成核心功能，
 *    而是帮助委托类完成事情。
 *
 *
 * 例如：
 *
 * 景天类：委托类
 * 真正要买包子的人。
 *
 * 空灵类：代理类
 * 帮景天去买包子的人。
 *
 *
 * 常见的代理实现方式：
 *
 * 1. 将委托对象作为代理类的数据成员
 *
 *    代理类中保存一个委托对象，
 *    当代理类需要完成某件事情时，
 *    内部再调用委托对象的成员函数。
 *
 * 2. 将委托类作为代理类的父类
 *
 *    代理类通过继承得到委托类的功能，
 *    然后在自己的成员函数中调用父类的成员函数。
 *
 *
 * 代理模式的核心思想：
 *
 * 客户端不直接找委托对象做事，
 * 而是通过代理对象间接完成。
 *
 * 代理对象可以在真正执行功能之前或之后，
 * 添加一些额外操作。
 *
 * 例如：
 * cout << "帮景天" << endl;
 */

// 委托类
// 真正负责买早餐的类
class JingTian
{
public:
    // 买早餐的行为
    // 这个函数表示真正要完成的核心功能
    void buyBreakfast()
    {
        cout << "买两个包子" << endl;
    }
};

// 代理类
// KongLing 负责帮 JingTian 调用买早餐的功能
class KongLing
{
public:
    /**
     * 代理类中的买早餐函数
     *
     * 从外部看：
     * 是 KongLing 对象在执行 buyBreakfast。
     *
     * 实际上：
     * KongLing 只是代理，
     * 真正买早餐的操作仍然交给 JingTian 对象完成。
     */
    void buyBreakfast()
    {   
        // 代理类可以在调用委托对象之前，
        // 添加一些额外的逻辑。
        cout << "帮景天" << endl;

        // 通过数据成员 m_jingtian，
        // 调用委托对象的 buyBreakfast 函数。
        m_jingtian.buyBreakfast();
    }

    // 将委托对象设置为代理类的数据成员
    //
    // 这里使用引用作为数据成员：
    // JingTian & m_jingtian;
    //
    // 含义：
    // 代理对象 KongLing 内部并不重新创建一个 JingTian 对象，
    // 而是绑定外部已经存在的 JingTian 对象。
    //
    // 注意：
    // 引用数据成员必须在对象创建时完成初始化，
    // 不能等到构造函数体里面再赋值。
    //
    // 本例中：
    // KongLing kl{ jingtian };
    //
    // 使用聚合初始化的方式，
    // 将 m_jingtian 绑定到 jingtian 对象上。
    JingTian & m_jingtian;
};


void test1()
{
    // 创建委托对象
    // 真正负责买早餐的是 jingtian
    JingTian jingtian;

    // 创建代理对象
    // kl 内部的引用成员 m_jingtian 绑定到 jingtian
    KongLing kl{ jingtian };

    // 通过代理对象调用 buyBreakfast
    //
    // 实际执行流程：
    // 1. 先调用 KongLing::buyBreakfast()
    // 2. 输出 "帮景天"
    // 3. 再调用 JingTian::buyBreakfast()
    kl.buyBreakfast();
}


// 使用方式二实现代理模式
// 方式二：通过继承实现代理

// 委托类
// 仍然是真正提供买早餐功能的类
class JingTian2
{
public:
    void buyBreakfast()
    {
        cout << "买两个包子" << endl;
    }
};

// 代理类
//
// 将 JingTian2 设置为 KongLing2 的父类
//
// 也就是说：
// JingTian2 是父类，KongLing2 是子类。
//
// KongLing2 通过 public 继承 JingTian2，
// 可以得到 JingTian2 中 public 成员函数的访问权限。
class KongLing2 : public JingTian2
{
public:
    /**
     * 子类中重新定义 buyBreakfast 函数
     *
     * 父类 JingTian2 中已经有一个 buyBreakfast 函数，
     * 子类 KongLing2 中又定义了一个同名函数。
     *
     * 此时子类的 buyBreakfast 会隐藏父类的同名函数。
     *
     * 如果在子类函数内部想调用父类版本，
     * 就需要通过类名作用域限定符来指定：
     *
     * JingTian2::buyBreakfast();
     */
    void buyBreakfast()
    {   
        // 代理类额外添加的逻辑
        cout << "帮景天" << endl;

        // 调用父类中的同名成员函数
        //
        // 如果直接写：
        // buyBreakfast();
        //
        // 那么调用的是 KongLing2 自己的 buyBreakfast，
        // 会造成无限递归调用。
        //
        // 所以这里必须写成：
        // JingTian2::buyBreakfast();
        //
        // 明确告诉编译器调用父类版本。
        JingTian2::buyBreakfast();
    }
};

void test2()
{
    // 创建代理对象
    //
    // 因为 KongLing2 继承了 JingTian2，
    // 所以 KongLing2 对象内部本身就包含一个 JingTian2 的父类子对象。
    KongLing2 kl;

    // 调用子类自己的 buyBreakfast 函数
    //
    // 执行流程：
    // 1. 先输出 "帮景天"
    // 2. 再通过 JingTian2::buyBreakfast()
    //    调用父类中的买早餐功能。
    kl.buyBreakfast();
}


int main(int argc, char *argv[])
{
    /* test1(); */

    // 当前测试的是通过继承实现代理模式
    test2();

    return 0;
}