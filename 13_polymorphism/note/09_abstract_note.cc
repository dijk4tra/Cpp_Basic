#include <iostream>

using std::cout;
using std::endl;

/**
 * 纯虚函数 pure virtual function：
 *
 * 纯虚函数本质上也是虚函数，
 * 但是它只声明接口，不给出具体实现。
 *
 * 语法：
 * virtual 返回类型 函数名(参数列表) = 0;
 *
 * 例如：
 * virtual void func() = 0;
 *
 *
 * 抽象类 abstract class：
 *
 * 只要一个类中含有至少一个纯虚函数，
 * 这个类就是抽象类。
 *
 * 抽象类不能实例化，
 * 也就是不能直接创建对象。
 *
 * 例如：
 * AbstractClass obj; // error
 *
 *
 * 抽象类的作用：
 *
 * 1. 作为接口或者标准存在
 *    抽象类只规定“必须有什么功能”，
 *    不关心“功能具体怎么实现”。
 *
 * 2. 强制子类实现某些函数
 *    子类如果想变成普通类，
 *    就必须实现父类中所有没有实现的纯虚函数。
 *
 * 3. 方便多态
 *    可以使用抽象类指针或者引用接收子类对象，
 *    通过统一接口调用不同子类的实现。
 *
 *
 * 特殊情况：
 *
 * 如果子类没有实现父类中所有的纯虚函数，
 * 那么这个子类仍然是抽象类，
 * 也不能实例化。
 */


// 抽象类
class AbstractClass
{
public:
    /**
     * 纯虚函数。
     *
     * func 是虚函数，
     * 但是没有函数体，
     * 后面写了 = 0。
     *
     * 所以 AbstractClass 是抽象类，
     * 不能直接创建对象。
     */
    // 纯虚函数
    virtual void func() = 0 ;
};

void test1()
{
    /**
     * AbstractClass 中有纯虚函数 func，
     * 所以 AbstractClass 是抽象类。
     *
     * 抽象类不能实例化。
     */
    // 不能进行实例化
    /* AbstractClass obj; */
}

class Animal
{
public:
    /**
     * Animal 中定义了纯虚函数 eat。
     *
     * 这表示：
     * 所有 Animal 的子类都应该具有 eat 这个行为。
     *
     * 但是 Animal 本身不规定具体怎么吃，
     * 具体实现交给不同的子类。
     *
     * 所以 Animal 是抽象类。
     */
    // 纯虚函数
    virtual void eat() = 0;
};

class Dog : public Animal
{
public:
    /**
     * Dog 继承 Animal。
     *
     * Animal 中有纯虚函数 eat，
     * Dog 如果想成为可以创建对象的普通类，
     * 就必须实现 eat。
     *
     * Dog 对 eat 的实现是：
     * eat meat!
     *
     * 建议写成：
     * virtual void eat() override
     *
     * override 可以让编译器检查当前函数
     * 是否真的重写了父类中的虚函数。
     */
    // 强制子类去实现纯虚函数
    virtual void eat()
    {
        cout << "eat meat!" << endl;
    }
};

class Cat : public Animal
{
public:
    /**
     * Cat 也继承 Animal。
     *
     * Cat 实现了 Animal 中的纯虚函数 eat，
     * 所以 Cat 也可以创建对象。
     *
     * Cat 对 eat 的实现是：
     * eat fish!
     */
    // 强制子类去实现纯虚函数
    virtual void eat()
    {
        cout << "eat fish!" << endl;
    }
};

void test2()
{
    /**
     * Animal 是抽象类，
     * 因为其中有纯虚函数 eat。
     *
     * 所以不能直接创建 Animal 对象。
     */
    /* Animal animal; */

    /**
     * Dog 和 Cat 都实现了 Animal 中的 eat，
     * 所以 Dog 和 Cat 都可以创建对象。
     */
    Dog dog;
    Cat cat;

    /**
     * 抽象类虽然不能直接创建对象，
     * 但是可以定义抽象类的指针或者引用。
     *
     * Animal * p = &dog;
     *
     * p 的静态类型是 Animal *，
     * 但是实际指向 Dog 对象。
     *
     * 通过父类指针调用虚函数 eat，
     * 会发生动态绑定，
     * 最终调用 Dog::eat()。
     */
    Animal * p = &dog;
    p->eat();

    /**
     * p 改为指向 Cat 对象。
     *
     * 同样调用 eat，
     * 但是这次实际执行的是 Cat::eat()。
     *
     * 这就是多态：
     * 同一个接口 eat，
     * 针对不同子类对象，
     * 表现出不同的行为。
     */
    p = &cat;
    p->eat();
}

/**
 * 使用抽象类指针作为函数参数。
 *
 * 好处：
 * handle 不需要关心传入的具体动物类型。
 *
 * 只要传入的是 Animal 的子类对象，
 * 并且实现了 eat 这个接口，
 * 就可以通过 handle 统一处理。
 *
 * 这也是抽象类常用作接口的原因。
 */
void handle(Animal * p)
{
    p->eat();
}


// A是抽象类
class A
{
public:
    /**
     * A 中有三个纯虚函数：
     * func1
     * func2
     * func3
     *
     * 所以 A 是抽象类，
     * 不能创建对象。
     */
    // 纯虚函数
    virtual void func1() = 0 ;
    virtual void func2() = 0 ;
    virtual void func3() = 0 ;
};

// B只实现了func1和func2,还有纯虚函数func3没有实现
// 所以B也是抽象类
class B : public A
{
public:
    /**
     * B 继承 A。
     *
     * A 中有三个纯虚函数。
     *
     * B 只实现了 func1 和 func2，
     * 但是没有实现 func3。
     *
     * 所以 B 中仍然存在没有实现的纯虚函数，
     * 因此 B 仍然是抽象类。
     *
     * 抽象类不能实例化。
     */
    virtual void func1(){};
    virtual void func2(){};
};

// 对于C来说，所有的纯虚函数都实现了
// 所以C可以实例化
class C : public B
{
public:
    /**
     * C 继承 B。
     *
     * B 中已经实现了：
     * func1
     * func2
     *
     * 但是还缺少 func3。
     *
     * C 实现了 func3 以后，
     * A 中所有的纯虚函数都已经被实现。
     *
     * 所以 C 不再是抽象类，
     * 可以创建对象。
     *
     * 注意：
     * 从父类继承下来的虚函数仍然是虚函数。
     * 所以这里也可以写成：
     * virtual void func3() override {}
     */
    virtual void func3(){};
};

void test3()
{
    /**
     * A 是抽象类，
     * 因为 A 中有纯虚函数。
     */
    /* A a; // 抽象类不可创建对象 */

    /**
     * B 也是抽象类，
     * 因为 B 没有实现 func3。
     */
    /* B b; // 抽象类不可创建对象 */

    /**
     * C 实现了所有纯虚函数，
     * 所以 C 可以创建对象。
     */
    C c;
}


int main(int argc, char *argv[])
{
    /**
     * test1 演示：
     * 抽象类不能实例化。
     */
    /* test1(); */

    /**
     * test2 演示：
     * 1. 抽象类作为父类接口
     * 2. 子类实现纯虚函数
     * 3. 通过抽象类指针实现多态
     */
    test2();

    return 0;
}