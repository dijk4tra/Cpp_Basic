#include <iostream>
#include <memory>

using namespace std;

/*
 * 智能指针和多态结合：
 *
 * 多态的基本形式：
 *      父类指针或父类引用指向子类对象，
 *      通过虚函数实现动态绑定。
 *
 * 与智能指针结合：
 *      可以使用 unique_ptr<父类类型> 管理子类对象，
 *      既能自动释放资源，又能通过虚函数表现多态行为。
 *
 * 注意：
 *      当使用父类指针管理子类对象时，
 *      实际工程中父类通常应当定义虚析构函数，
 *      以保证通过父类指针释放子类对象时析构过程正确。
 */

class Father
{
public:
    // 纯虚函数：Father 是抽象类，不能直接创建对象
    virtual void func() = 0;
};

class Son : public Father
{
public:
    // 重写父类中的虚函数
    virtual void func() override
    {
        cout << "Son::func()" << endl;
    }
};

void test1()
{
    // 原始指针形式的多态：
    // Father * f = new Son{};
    // f->func();

    // 使用 unique_ptr 管理子类对象：
    // unique_ptr<Father> 表示智能指针的静态类型是 Father，
    // new Son{} 表示实际管理的对象类型是 Son。
    //
    // 这体现了“父类指针指向子类对象”的多态用法。
    unique_ptr<Father> up { new Son{} };

    // 通过智能指针调用虚函数：
    // 虽然 up 的类型是 unique_ptr<Father>，
    // 但实际对象是 Son，因此会调用 Son::func()
    up->func();

    // 先通过 operator* 得到 Father 引用，
    // 再调用虚函数，同样会发生动态绑定
    (*up).func();
}

int main(int argc, char const *argv[])
{
    test1();
    return 0;
}