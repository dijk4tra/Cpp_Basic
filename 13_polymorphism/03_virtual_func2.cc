#include <iostream>

using std::cout;
using std::endl;

/**
 * 虚函数的原理：
 * 当类中存在虚函数时，对象的内部结构通常会发生变化。
 *
 * 主流编译器一般会在对象中增加一个虚函数指针 vfptr，
 * 该指针指向当前类对应的虚函数表 vtable。
 *
 * 虚函数表中保存的是虚函数的入口地址。
 * 当通过父类指针或引用调用虚函数时，
 * 程序会根据对象中的 vfptr 找到对应的虚函数表，
 * 再调用实际对象类型对应的虚函数。
 *
 * 注意：
 * 1. vfptr 和 vtable 是主流编译器常见的实现方式，
 *    C++ 标准并没有强制规定必须这样实现。
 * 2. 通常只有含有虚函数的类才会有虚函数表。
 */

class Father
{
public:
    virtual // 虚函数
    void func1()
    {
        cout << "Father::func1()" << endl;
    }

    virtual void display()
    {
        cout << "Father::display()" << endl;
    }

    double m_f = 1;
};

class Son : public Father
{
public:
    // 子类重写了父类中的 display 虚函数
    // virtual：表示该函数仍然是虚函数
    // override：明确表示该函数重写了父类中的虚函数
    virtual void display() override
    {
        cout << "Son::display()" << endl;
    }

    // 子类中定义了和父类同名的数据成员
    // 这是成员隐藏，不是多态；成员变量不会发生虚函数那样的动态绑定
    double m_f = 2;
};

void test1()
{
    Father father;

    // 对象中通常会多出一个虚函数指针 vfptr
    // 所以对象大小可能会变大
    // 例如在 64 位环境下：
    // 原本只有 double 成员时可能是 8 字节；
    // 加入虚函数后，由于多了 vfptr，可能变成 16 字节。
    cout << sizeof(father) << endl;

    Son son;

    // Son 对象中包含 Father 子对象部分：
    // Father 部分通常包含 vfptr 和 Father::m_f；
    // Son 自己又增加了一个 Son::m_f。
    //
    // 例如在 64 位环境下，大小可能是 24 字节。
    // 具体结果与编译器、平台和内存对齐规则有关。
    cout << sizeof(son) << endl;
}

// 使用多态
void test2()
{
    Son son;

    // 父类指针接收子类对象地址
    Father *f = &son;

    // func1 没有在子类中重写，因此调用父类版本
    f->func1();

    // display 在子类中被重写
    // 通过父类指针调用虚函数时，会根据实际对象类型调用子类版本
    f->display();
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();

    return 0;
}