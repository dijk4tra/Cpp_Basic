#include <iostream>

using std::cout;
using std::endl;

/**
 * 纯虚函数：
 * 使用 = 0 声明的虚函数，称为纯虚函数。
 *
 * 抽象类：
 * 类中只要含有至少一个纯虚函数，这个类就是抽象类。
 * 抽象类不能实例化，也就是不能直接创建对象。
 *
 * 抽象类一般作为接口或标准存在，
 * 具体的功能实现交给子类完成。
 *
 * 如果子类没有实现父类中的所有纯虚函数，
 * 那么这个子类仍然是抽象类，也不能实例化。
 *
 * 注意：
 * 纯虚函数并不一定完全没有函数体，
 * 它也可以在类外提供实现。
 * 但是只要声明时写了 = 0，该函数就是纯虚函数，
 * 对应的类就是抽象类。
 */

// 抽象类
class AbstractClass
{
public:
    virtual ~AbstractClass() = default;

    // 纯虚函数
    virtual void func() = 0;
};

void test1()
{
    // 抽象类不能实例化
    /* AbstractClass obj; */
}

class Animal
{
public:
    // 多态基类建议提供虚析构函数
    virtual ~Animal() = default;

    // 纯虚函数
    // Animal 只规定动物必须具有 eat 行为，
    // 具体怎么吃，由子类决定
    virtual void eat() = 0;
};

class Dog : public Animal
{
public:
    // 子类实现父类中的纯虚函数
    // virtual：表示该函数仍然是虚函数
    // override：明确表示该函数重写了父类中的虚函数
    virtual void eat() override
    {
        cout << "eat meat!" << endl;
    }
};

class Cat : public Animal
{
public:
    // 子类实现父类中的纯虚函数
    virtual void eat() override
    {
        cout << "eat fish!" << endl;
    }
};

void test2()
{
    // 抽象类不能实例化
    /* Animal animal; */

    Dog dog;
    Cat cat;

    // 父类指针指向 Dog 对象
    Animal *p = &dog;

    // 通过父类指针调用虚函数，实际执行 Dog::eat()
    p->eat();

    // 父类指针指向 Cat 对象
    p = &cat;

    // 通过父类指针调用虚函数，实际执行 Cat::eat()
    p->eat();
}

// 使用父类指针作为函数参数，可以统一处理 Animal 的所有子类对象
void handle(Animal *p)
{
    p->eat();
}

// A 是抽象类
class A
{
public:
    virtual ~A() = default;

    // 纯虚函数
    virtual void func1() = 0;
    virtual void func2() = 0;
    virtual void func3() = 0;
};

// B 只实现了 func1 和 func2，
// 还有纯虚函数 func3 没有实现，
// 所以 B 仍然是抽象类，不能实例化
class B : public A
{
public:
    virtual void func1() override {}
    virtual void func2() override {}
};

// C 实现了剩下的纯虚函数 func3，
// 此时 A 中声明的所有纯虚函数都已经被实现，
// 所以 C 不再是抽象类，可以实例化
class C : public B
{
public:
    virtual void func3() override {}
};

void test3()
{
    /* A a; // 抽象类不能创建对象 */
    /* B b; // B 仍然是抽象类，不能创建对象 */

    C c; // C 已经实现所有纯虚函数，可以创建对象
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();
    /* test3(); */

    return 0;
}