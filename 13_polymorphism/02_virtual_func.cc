#include <iostream>

using std::cout;
using std::endl;

/**
 * 虚函数：使用 virtual 修饰的类成员函数。
 *
 * 虚函数的作用：
 * 当父类指针或引用指向子类对象时，
 * 通过父类指针或引用调用虚函数，
 * 程序会根据实际指向的对象类型，执行对应子类中的函数版本。
 */

class Father
{
public:
    virtual // 虚函数
    void func1()
    {
        cout << "Father::func1()" << endl;
    }

    // 普通成员函数，不是虚函数
    void func2()
    {

    }

    // 声明虚函数
    virtual void func3();
};

// 类外给出虚函数的具体实现
/* virtual // 类外实现虚函数时不要再加 virtual */
void Father::func3()
{

}

class Son : public Father
{
public:
    // 子类中重写父类的虚函数
    // virtual：表示该函数仍然是虚函数
    // override：用来标记该函数重写了父类中的虚函数
    // 在子类中 virtual 和 override 都可以省略，但不建议省略
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }

    // 这里不是 override，因为父类中的 func2 不是虚函数
    // 这是子类定义了与父类同名的普通成员函数，属于隐藏/重定义
    // override 只能用于重写父类中的虚函数
    void func2()
    {

    }
};

void test1()
{
    Son son;

    // 使用子类对象直接调用 func1，执行的是子类重写后的版本
    // 这种写法没有通过父类指针或引用调用，因此还不是多态
    son.func1();

    // 使用作用域限定符，明确调用父类中的 func1
    son.Father::func1();

    // 下面的代码才体现多态
    Father *f = &son;

    // 父类指针调用虚函数，实际执行的是子类重写后的版本
    f->func1();

    // 多态的条件：
    // 1. 以继承关系为前提；
    // 2. 父类中定义虚函数；
    // 3. 子类中重写父类的虚函数；
    // 4. 父类指针或引用接收子类对象；
    // 5. 通过父类指针或引用调用同名虚函数。
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}