#include <iostream>

using std::cout;
using std::endl;

/**
 * 直接通过子类对象调用虚函数：这不是多态。
 *
 * 多态通常指：
 * 父类指针或父类引用指向子类对象，
 * 再通过父类指针或引用调用被子类重写的虚函数。
 *
 * 如果直接使用子类对象调用函数，
 * 编译器能够明确知道调用者是 Son 类型对象，
 * 因此这只是普通的对象调用，不体现多态。
 */

class Father
{
public:
    virtual void func()
    {
        cout << "Father::func()" << endl;
    }
};

class Son : public Father
{
public:
    // 子类重写父类中的虚函数
    // virtual：表示该函数仍然是虚函数
    // override：明确表示该函数重写了父类中的虚函数
    virtual void func() override
    {
        cout << "Son::func()" << endl;
    }
};

void test1()
{
    // 创建子类对象
    Son son;

    // 通过子类对象直接调用虚函数
    // 执行的是子类重写后的版本，但这不是多态
    son.func();

    // 使用作用域限定符，明确调用父类中的 func
    son.Father::func();

    // 下面这种写法才体现多态：
    // 父类指针指向子类对象
    Father *p = &son;

    // 通过父类指针调用虚函数，实际执行子类重写后的版本
    p->func();
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}