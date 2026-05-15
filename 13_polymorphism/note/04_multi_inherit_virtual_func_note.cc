#include <iostream>

using std::cout;
using std::endl;

/**
 * 虚函数多继承：
 *
 * 当一个子类同时继承多个父类，
 * 并且这些父类中都含有虚函数时，
 * 子类对象的结构会更复杂。
 *
 *
 * 单继承中：
 * 如果父类有虚函数，
 * 子类对象中通常只有一份从父类继承来的 vfptr。
 *
 *
 * 多继承中：
 * 如果多个父类都有虚函数，
 * 那么子类对象中通常会包含多个父类子对象。
 *
 * 每个含有虚函数的父类子对象中，
 * 通常都有自己的 vfptr。
 *
 *
 * 本例中：
 * class Son : public Father1, public Father2
 *
 * Son 对象中大致包含：
 * 1. Father1 子对象
 *    - Father1 的 vfptr
 *    - Father1::m_f1
 *
 * 2. Father2 子对象
 *    - Father2 的 vfptr
 *    - Father2::m_f2
 *
 * 3. Son 自己的数据成员
 *    - Son::m_s
 *
 *
 * 注意：
 * sizeof 的结果和平台、编译器、内存对齐规则有关。
 * 在 64 位环境下，指针通常占 8 字节。
 */

class Father1
{
public:
    /**
     * Father1 中定义了虚函数 func1。
     *
     * 因为类中有虚函数，
     * 所以 Father1 对象中通常会有一个隐藏的 vfptr，
     * 指向 Father1 的虚函数表。
     */
    virtual void func1()
    {
        cout << "Father1::func1()" << endl;
    }

    /**
     * 普通数据成员。
     *
     * 在多数 64 位环境下：
     * vfptr 占 8 字节，
     * double m_f1 占 8 字节，
     * 所以 sizeof(Father1) 通常是 16。
     */
    double m_f1 = 1;
};

class Father2
{
public:
    /**
     * Father2 中也定义了虚函数 func2。
     *
     * 因为 Father2 也有虚函数，
     * 所以 Father2 对象中通常也会有一个隐藏的 vfptr。
     */
    virtual void func2()
    {
        /**
         * 这里输出的是 "Father2::func1()"，
         * 但当前函数名是 func2。
         *
         * 从语义上看，
         * 这里更可能想写成：
         * cout << "Father2::func2()" << endl;
         *
         * 不过这不影响虚函数和多继承的语法演示。
         */
        cout << "Father2::func1()" << endl;
    }

    /**
     * 普通数据成员。
     *
     * Father2 对象中通常包含：
     * 1. vfptr
     * 2. m_f2
     *
     * 所以 sizeof(Father2) 通常也是 16。
     */
    double m_f2 = 1;
};

class Son : public Father1, public Father2
{
public:
    /**
     * Son 重写了 Father1 中的虚函数 func1。
     *
     * 因为 Father1::func1() 是虚函数，
     * Son 中定义了同名、同参数列表的 func1()，
     * 所以这里构成虚函数重写。
     *
     * 调用时如果父类指针 Father1 * 指向 Son 对象，
     * 再调用 func1()，
     * 会触发多态，执行 Son::func1()。
     */
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }

    /**
     * Son 自己的数据成员。
     *
     * Son 对象中除了继承来的 Father1 子对象
     * 和 Father2 子对象之外，
     * 还会有自己的成员 m_s。
     */
    double m_s = 3;
};

void test1()
{
    Father1 father1;
    Father2 father2;
    Son son;

    /**
     * Father1 中有虚函数，
     * 所以对象中通常包含：
     * 1. vfptr
     * 2. double m_f1
     *
     * 在 64 位环境下通常输出 16。
     */
    cout << sizeof(father1) << endl;

    /**
     * Father2 中也有虚函数，
     * 所以对象中通常包含：
     * 1. vfptr
     * 2. double m_f2
     *
     * 在 64 位环境下通常输出 16。
     */
    cout << sizeof(father2) << endl;

    /**
     * Son 是多继承类。
     *
     * Son 对象中大致包含：
     * 1. Father1 子对象
     *    - Father1 对应的 vfptr
     *    - Father1::m_f1
     *
     * 2. Father2 子对象
     *    - Father2 对应的 vfptr
     *    - Father2::m_f2
     *
     * 3. Son 自己的成员
     *    - Son::m_s
     *
     *
     * 在 64 位环境下：
     * Father1 子对象通常占 16 字节
     * Father2 子对象通常占 16 字节
     * Son::m_s 通常占 8 字节
     *
     * 所以 sizeof(son) 通常是 40。
     *
     * 实际结果仍然要以当前编译器和平台为准。
     */
    cout << sizeof(son) << endl;

    /**
     * 父类指针 Father1 * 接收子类对象地址。
     *
     * f1 指向的是 son 对象中的 Father1 子对象部分。
     *
     * 也就是说：
     * Father1 * 只能看到 Son 对象中
     * 属于 Father1 的那一部分接口。
     */
    Father1 * f1 = &son;

    /**
     * func1 是 Father1 中的虚函数，
     * 并且 Son 中重写了 func1。
     *
     * 所以通过 Father1 * 调用 func1() 时，
     * 会发生动态绑定，
     * 最终调用 Son::func1()。
     */
    f1->func1();

    /**
     * f1 的类型是 Father1 *。
     *
     * Father1 中没有 func2()，
     * func2() 是 Father2 中的成员函数。
     *
     * 所以 f1 不能直接调用 func2()。
     *
     * 父类型指针只能访问自己类型中声明过的成员。
     */
    /* f1->func2(); // 父类型指针只能访问自己那部分 */ 

    /**
     * Father2 * 也可以接收 Son 对象地址。
     *
     * 但这里的 f2 指向的是 son 对象中的 Father2 子对象部分。
     *
     * 在多继承中，
     * 同一个 Son 对象转换成不同的父类指针时，
     * 指针保存的地址可能会发生偏移。
     *
     * 例如：
     * Father1 * 指向 Son 对象中的 Father1 部分；
     * Father2 * 指向 Son 对象中的 Father2 部分。
     */
    Father2 * f2 = &son;

    /**
     * func2 是 Father2 中的虚函数。
     *
     * 但是 Son 中没有重写 Father2::func2()，
     * 所以这里调用的仍然是 Father2::func2()。
     *
     * 如果 Son 中重写 func2：
     *
     * virtual void func2() override
     * {
     *     cout << "Son::func2()" << endl;
     * }
     *
     * 那么 f2->func2() 就会执行 Son::func2()。
     */
    f2->func2();
}

int main(int argc, char *argv[])
{
    /**
     * test1 演示：
     * 1. 多继承下对象大小的变化
     * 2. 多个父类中有虚函数时，子类对象中的 vfptr 情况
     * 3. 父类指针只能访问对应父类接口
     * 4. 通过不同父类指针调用虚函数时的多态表现
     */
    test1();

    return 0;
}