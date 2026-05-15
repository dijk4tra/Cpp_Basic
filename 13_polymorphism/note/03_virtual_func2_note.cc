#include <iostream>

using std::cout;
using std::endl;

/**
 * 虚函数的原理：
 * 当一个类中定义了虚函数以后，
 * 这个类的对象结构会发生变化。
 *
 * 对象中会多出一个隐藏的指针：
 * 虚函数指针 virtual function pointer
 * 简称 vfptr。
 *
 *
 * vfptr 的作用：
 * 指向虚函数表 virtual function table，
 * 简称 vtable。
 *
 * 虚函数表中存放的是虚函数的入口地址。
 *
 *
 * 注意：
 * 1. vfptr 是存在于对象中的
 *    每个对象里面都有自己的 vfptr。
 *
 * 2. vtable 是存在于类层面的
 *    同一个类的多个对象通常共用同一张虚函数表。
 *
 * 3. 对象通过 vfptr 找到 vtable，
 *    再通过 vtable 找到最终应该调用的虚函数版本。
 *
 *
 * 多态底层大致过程：
 * 父类指针 -> 子类对象 -> 对象中的 vfptr
 * -> 子类的虚函数表 -> 对应的虚函数入口地址
 *
 *
 * 注意：
 * sizeof 的结果和平台有关。
 * 当前注释中的 8、16、24 一般是在 64 位环境下的结果。
 */

class Father
{
public:
    /**
     * func1 是虚函数。
     *
     * 只要类中有虚函数，
     * 这个类的对象中通常就会多一个隐藏的 vfptr。
     *
     * 在 64 位环境下：
     * 指针大小通常是 8 字节。
     */
    virtual // 虚函数
    void func1()
    {
       cout << "Father::func1()" << endl;
    }

    /**
     * display 也是虚函数。
     *
     * 一个类中可以有多个虚函数，
     * 但是对象中通常只需要一个 vfptr。
     *
     * 这个 vfptr 指向一张虚函数表，
     * 虚函数表中保存多个虚函数的地址。
     */
    virtual void display()
    {
        cout << "Father::display()" << endl;
    }

    /**
     * 普通数据成员。
     *
     * m_f 是 double 类型，
     * 在大多数 64 位环境下占 8 字节。
     *
     * Father 对象中大致包含：
     * 1. vfptr，8 字节
     * 2. m_f，8 字节
     *
     * 所以 sizeof(Father) 通常是 16。
     */
    double m_f = 1;
};

class Son : public Father
{
public:
    /**
     * 子类重写了父类中的 display 虚函数。
     *
     * Father::display() 是虚函数，
     * Son 中定义了同名、同参数列表的 display()，
     * 所以这里构成虚函数重写。
     *
     * 建议写成：
     * virtual void display() override
     *
     * override 可以让编译器帮我们检查：
     * 当前函数是否真的重写了父类中的虚函数。
     */
    // 子类中重写了其中一个虚函数
    virtual void display()
    {
        cout << "Son::display()" << endl;
    }

    /**
     * 这里的 m_f 和 Father 中的 m_f 同名，
     * 但是数据成员不存在虚函数那样的多态机制。
     *
     * 子类中定义同名数据成员，
     * 会隐藏父类中的同名数据成员。
     *
     * Son 对象中实际上有两份 m_f：
     * 1. Father::m_f
     * 2. Son::m_f
     *
     * 可以通过作用域区分：
     * son.m_f          // 访问 Son::m_f
     * son.Father::m_f  // 访问 Father::m_f
     */
    double m_f = 2;
};


void test1()
{
    Father father;

    /**
     * 如果 Father 中没有虚函数：
     * Father 对象中只有一个 double m_f，
     * sizeof(father) 通常是 8。
     *
     * 当 Father 中出现虚函数以后：
     * 对象中会多一个隐藏的 vfptr。
     *
     * 在 64 位环境下：
     * vfptr 占 8 字节
     * double m_f 占 8 字节
     *
     * 所以 sizeof(father) 通常是 16。
     */
    cout << sizeof(father) << endl; // 8--->16(将func1设置为虚函数后)
     
    Son son;

    /**
     * 如果 Father 中没有虚函数：
     * Son 对象中包含：
     * 1. Father 继承下来的 double m_f
     * 2. Son 自己的 double m_f
     *
     * sizeof(son) 通常是 16。
     *
     *
     * 当 Father 中出现虚函数以后：
     * Son 对象中包含：
     * 1. 从 Father 继承来的 vfptr
     * 2. Father::m_f
     * 3. Son::m_f
     *
     * 在 64 位环境下：
     * vfptr 占 8 字节
     * Father::m_f 占 8 字节
     * Son::m_f 占 8 字节
     *
     * 所以 sizeof(son) 通常是 24。
     *
     *
     * 注意：
     * Son 自己没有额外再多出一个 vfptr。
     * 因为它继承自 Father，
     * Father 这个基类子对象中已经有 vfptr。
     */
    cout << sizeof(son) << endl; // 16--->24(将func1设置为虚函数后)
}

// 使用多态
void test2()
{
    Son son;

    /**
     * 父类指针接收子类对象地址。
     *
     * f 的静态类型是 Father *，
     * 但是 f 实际指向的是 Son 对象。
     *
     * 这是多态成立的条件之一。
     */
    Father * f = &son;

    /**
     * func1 是虚函数，
     * 但是 Son 中没有重写 func1。
     *
     * 所以通过父类指针调用 func1() 时，
     * 最终只能调用 Father::func1()。
     *
     * 输出：
     * Father::func1()
     */
    f->func1();   // 父类的结果

    /**
     * display 是虚函数，
     * 并且 Son 中重写了 display。
     *
     * f 虽然是 Father *，
     * 但是实际指向的是 Son 对象。
     *
     * 所以调用 display() 时，
     * 会通过 Son 对象中的 vfptr 找到 Son 的虚函数表，
     * 最终调用 Son::display()。
     *
     * 输出：
     * Son::display()
     */
    f->display(); // 子类的结果
}

int main(int argc, char *argv[])
{
    // test1 演示：
    // 虚函数会影响对象大小，
    // 因为对象中会多出隐藏的 vfptr。
    /* test1(); */

    // test2 演示：
    // 父类指针指向子类对象，
    // 调用被子类重写的虚函数时，
    // 体现出运行时多态。
    test2();
    
    return 0;
}