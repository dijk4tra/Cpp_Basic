#include <iostream>

using std::cout;
using std::endl;

/**
 * 虚函数与多继承：
 *
 * 当一个子类同时继承多个带有虚函数的父类时，
 * 子类对象中通常会包含多个父类子对象部分。
 *
 * 在主流编译器实现中：
 * 1. 每个含有虚函数的父类部分通常都会有自己的虚函数指针 vfptr；
 * 2. 每个 vfptr 分别指向对应的虚函数表 vtable；
 * 3. 如果子类重写了某个父类的虚函数，对应虚函数表中的函数地址会被替换为子类版本；
 * 4. 如果子类没有重写某个父类的虚函数，则仍然调用父类版本。
 *
 * 注意：
 * vfptr 和 vtable 是主流编译器常见的实现方式，
 * C++ 标准并没有强制规定对象内部必须这样实现。
 */

class Father1
{
public:
    virtual void func1()
    {
        cout << "Father1::func1()" << endl;
    }

    double m_f1 = 1;
};

class Father2
{
public:
    virtual void func2()
    {
        cout << "Father2::func2()" << endl;
    }

    double m_f2 = 1;
};

class Son : public Father1, public Father2
{
public:
    // 子类重写 Father1 中的虚函数 func1
    // virtual：表示该函数仍然是虚函数
    // override：明确表示该函数重写了父类中的虚函数
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }

    double m_s = 3;
};

void test1()
{
    Father1 father1;
    Father2 father2;
    Son son;

    // Father1 中有虚函数，通常对象中会包含一个 vfptr
    cout << sizeof(father1) << endl;

    // Father2 中有虚函数，通常对象中也会包含一个 vfptr
    cout << sizeof(father2) << endl;

    // Son 同时继承 Father1 和 Father2
    // 在主流编译器实现中，Son 对象中通常包含：
    // 1. Father1 子对象部分：vfptr + m_f1
    // 2. Father2 子对象部分：vfptr + m_f2
    // 3. Son 自己的成员：m_s
    //
    // 所以 Son 对象大小通常会比单继承时更大。
    // 具体大小与编译器、平台位数、内存对齐规则有关。
    cout << sizeof(son) << endl;

    // 父类 Father1 指针接收子类对象地址
    Father1 *f1 = &son;

    // func1 在 Son 中被重写，因此通过 Father1 指针调用时，
    // 实际执行的是 Son::func1()
    f1->func1();

    // Father1 类型的指针只能访问 Father1 这部分接口
    /* f1->func2(); */

    // 父类 Father2 指针接收子类对象地址
    Father2 *f2 = &son;

    // func2 没有在 Son 中重写，因此调用 Father2::func2()
    f2->func2();
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}