#include <iostream>

using std::cout;
using std::endl;

/**
 * 多继承中的虚函数表：
 *
 * 当一个子类同时继承多个父类，
 * 并且这些父类中都含有虚函数时，
 * 子类对象中通常会包含多个父类子对象。
 *
 *
 * 每个带虚函数的父类子对象中，
 * 通常都会有自己的虚函数指针 vfptr。
 *
 *
 * 本例中：
 *
 * class Son
 * : public Father1
 * , public Father2
 * , public Father3
 *
 * Son 同时继承 Father1、Father2、Father3。
 *
 * 这三个父类中都有虚函数，
 * 所以 Son 对象中通常会有 3 个 vfptr：
 *
 * 1. Father1 子对象中的 vfptr
 * 2. Father2 子对象中的 vfptr
 * 3. Father3 子对象中的 vfptr
 *
 *
 * 在 64 位环境下：
 * 一个指针通常占 8 字节。
 *
 * 所以如果三个父类中都没有普通数据成员，
 * Son 对象中主要就是 3 个 vfptr，
 * sizeof(son) 通常是：
 *
 * 8 + 8 + 8 = 24
 *
 *
 * 注意：
 * sizeof 的具体结果仍然和编译器、平台、内存对齐规则有关。
 */

class Father1
{
public:
    /**
     * Father1 中定义了虚函数 func1。
     *
     * 因为 Father1 中有虚函数，
     * 所以 Father1 对象中通常会有一个隐藏的 vfptr。
     */
    virtual void func1()
    {
        cout << "Father1::func1()" << endl; 
    }

    /**
     * Father1 中的第二个虚函数。
     *
     * 多个虚函数通常放在同一张虚函数表中。
     */
    virtual void func2()
    {
        cout << "Father1::func2()" << endl; 
    }

    /**
     * Father1 中的第三个虚函数。
     */
    virtual void func3()
    {
        cout << "Father1::func3()" << endl; 
    }
};

class Father2
{
public:
    /**
     * Father2 中也有虚函数 func1。
     *
     * 虽然 Father1 和 Father2 中都有 func1，
     * 但是它们属于不同的父类作用域。
     */
    virtual void func1()
    {
        cout << "Father2::func1()" << endl; 
    }

    virtual void func2()
    {
        cout << "Father2::func2()" << endl; 
    }

    virtual void func3()
    {
        cout << "Father2::func3()" << endl; 
    }
};

class Father3
{
public:
    /**
     * Father3 中同样定义了虚函数 func1。
     */
    virtual void func1()
    {
        cout << "Father3::func1()" << endl; 
    }

    virtual void func2()
    {
        cout << "Father3::func2()" << endl; 
    }

    virtual void func3()
    {
        cout << "Father3::func3()" << endl; 
    }
};

class Son
: public Father1
, public Father2
, public Father3
{
public:
    /**
     * Son 中重写 func1。
     *
     * Father1、Father2、Father3 中都有：
     *
     * virtual void func1()
     *
     * 它们的函数名、参数列表、返回类型都相同。
     *
     * Son 中定义：
     *
     * virtual void func1() override
     *
     * 会重写这三个父类中的同名虚函数 func1。
     *
     *
     * 因此：
     *
     * Father1 * f1 = &son;
     * f1->func1();  // 调用 Son::func1()
     *
     * Father2 * f2 = &son;
     * f2->func1();  // 调用 Son::func1()
     *
     * Father3 * f3 = &son;
     * f3->func1();  // 调用 Son::func1()
     *
     *
     * 但是 Son 没有重写 func2 和 func3，
     * 所以通过不同父类指针调用 func2 / func3 时，
     * 仍然调用对应父类自己的版本。
     */
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }
};


void test1()
{
    Son son;

    /**
     * Son 对象中通常包含：
     *
     * 1. Father1 子对象
     *    - Father1 对应的 vfptr
     *
     * 2. Father2 子对象
     *    - Father2 对应的 vfptr
     *
     * 3. Father3 子对象
     *    - Father3 对应的 vfptr
     *
     *
     * 三个父类都没有普通数据成员，
     * 所以在 64 位环境下，
     * sizeof(son) 通常是 24。
     */
    cout << sizeof(son) << endl; // 24: 3个vfptr

    /**
     * Father1 * 指针接收 Son 对象地址。
     *
     * f1 指向的是 son 对象中的 Father1 子对象部分。
     *
     * Father1 * 只能访问 Father1 中声明过的成员函数。
     */
    Father1 * f1 = &son;

    /**
     * func1 是虚函数，
     * 并且 Son 重写了 func1。
     *
     * 所以这里发生动态绑定，
     * 最终调用 Son::func1()。
     */
    f1->func1();

    /**
     * Son 没有重写 Father1::func2()。
     *
     * 所以这里调用 Father1::func2()。
     */
    f1->func2();

    /**
     * Son 没有重写 Father1::func3()。
     *
     * 所以这里调用 Father1::func3()。
     */
    f1->func3();

    cout << "---------" << endl;

    /**
     * Father2 * 指针也可以接收 Son 对象地址。
     *
     * 但是 f2 指向的是 son 对象中的 Father2 子对象部分。
     *
     * 在多继承中，
     * 不同父类子对象在子类对象中的位置可能不同，
     * 所以 Father2 * 指针中的地址
     * 可能和 Father1 * 指针中的地址不同。
     */
    Father2 * f2 = &son;

    /**
     * Son::func1() 同时重写了 Father2 中的 func1。
     *
     * 所以这里调用 Son::func1()。
     */
    f2->func1();

    /**
     * Son 没有重写 Father2::func2()，
     * 所以调用 Father2::func2()。
     */
    f2->func2();

    /**
     * Son 没有重写 Father2::func3()，
     * 所以调用 Father2::func3()。
     */
    f2->func3();

    cout << "---------" << endl;

    /**
     * Father3 * 指针接收 Son 对象地址。
     *
     * f3 指向 son 对象中的 Father3 子对象部分。
     */
    Father3 * f3 = &son;

    /**
     * Son::func1() 同时重写了 Father3 中的 func1。
     *
     * 所以这里也调用 Son::func1()。
     */
    f3->func1();

    /**
     * Son 没有重写 Father3::func2()，
     * 所以调用 Father3::func2()。
     */
    f3->func2();

    /**
     * Son 没有重写 Father3::func3()，
     * 所以调用 Father3::func3()。
     */
    f3->func3();

    cout << "---------" << endl;

    /**
     * 本例输出结果大致为：
     *
     * 24
     * Son::func1()
     * Father1::func2()
     * Father1::func3()
     * ---------
     * Son::func1()
     * Father2::func2()
     * Father2::func3()
     * ---------
     * Son::func1()
     * Father3::func2()
     * Father3::func3()
     * ---------
     *
     *
     * 其中：
     * func1 都调用 Son 版本，
     * 因为 Son 重写了 func1。
     *
     * func2 和 func3 调用各自父类版本，
     * 因为 Son 没有重写 func2 和 func3。
     */
}

int main(int argc, char *argv[])
{
    /**
     * test1 演示：
     *
     * 1. 多继承中多个父类都有虚函数时，
     *    子类对象中通常会有多个 vfptr。
     *
     * 2. Son 同时继承 Father1、Father2、Father3。
     *
     * 3. Son 重写 func1 后，
     *    通过三个不同的父类指针调用 func1，
     *    都会动态绑定到 Son::func1()。
     *
     * 4. Son 没有重写 func2 和 func3，
     *    所以通过不同父类指针调用时，
     *    执行的是对应父类自己的版本。
     */
    test1();

    return 0;
}