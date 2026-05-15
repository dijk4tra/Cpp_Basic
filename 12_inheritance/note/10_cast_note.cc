#include <iostream>

using std::cout;
using std::endl;

/**
 * 继承的实质：
 *
 * 把子类对象当成父类对象来使用。
 *
 * 继承关系需要满足：
 * 子类 is a 父类。
 *
 *
 * 逻辑层面：
 *
 * 狗是动物。
 * 苹果是水果。
 *
 * 所以：
 * Dog 可以看作 Animal。
 * Apple 可以看作 Fruit。
 *
 *
 * 代码层面：
 *
 * 如果 Dog public 继承 Animal，
 * 那么可以使用 Animal 类型去接收 Dog 对象。
 *
 * 例如：
 * Animal & animal = dog;
 * Animal * p = &dog;
 *
 *
 * 但是反过来不行：
 *
 * 动物不一定是狗。
 * 水果不一定是苹果。
 *
 * 所以不能直接用 Dog 类型去接收 Animal 对象。
 *
 *
 * 继承前提下，父子类之间的转换：
 *
 * 1. 向上转型 upcasting
 *
 *    子类类型转换成父类类型。
 *
 *    例如：
 *    Dog * ---> Animal *
 *    Dog & ---> Animal &
 *
 *    向上转型是安全的，
 *    可以自动完成。
 *
 *
 * 2. 向下转型 downcasting
 *
 *    父类类型转换成子类类型。
 *
 *    例如：
 *    Animal * ---> Dog *
 *    Animal & ---> Dog &
 *
 *    向下转型不一定安全，
 *    通常需要强制类型转换。
 *
 *
 * 注意：
 * 转换的是“接收的类型”，
 * 也就是指针或者引用的类型。
 *
 * 对象本身的真实类型不会因为指针或者引用类型改变而改变。
 */

class Animal
{
public:

};

class Dog : public Animal
{
    /**
     * Dog public 继承 Animal。
     *
     * 所以 Dog is a Animal。
     * 狗是动物。
     *
     * 因此 Dog 对象可以当作 Animal 对象来使用。
     */
};

class Cat : public Animal
{
    /**
     * Cat public 继承 Animal。
     *
     * 所以 Cat is a Animal。
     * 猫是动物。
     */
};

void test1()
{
    // 之前的做法：
    // 用哪个类型的对象，就使用同类型的变量接收。
    Animal animal;
    Dog dog;
    Cat cat;

    // Dog 类型的引用接收 Dog 对象
    Dog &dog2 = dog;

    // Cat 类型的引用接收 Cat 对象
    Cat &cat2 = cat;

    cout << "---------" << endl;

    /**
     * 使用继承后：
     *
     * 因为 Dog 和 Cat 都 public 继承 Animal，
     * 满足子类 is a 父类关系。
     *
     * 所以子类对象可以当作父类对象来使用。
     */

    // Animal 引用接收 Dog 对象
    // Dog ---> Animal
    // 这是向上转型，自动类型转换
    Animal &animal2 = dog;

    // Animal 指针指向 Dog 对象
    Animal *p = &dog;

    // Animal 引用接收 Cat 对象
    Animal &animal3 = cat;

    // Animal 指针指向 Cat 对象
    Animal *p2 = &cat;

    /**
     * 如果反过来就不行。
     *
     * 因为动物不一定是狗。
     * Animal 对象不能直接当作 Dog 对象来使用。
     */

    /* Dog dog3 = animal; // error，动物是狗，这个逻辑不成立 */

    /**
     * 如果两个类之间没有继承关系，
     * 也不能互相转换。
     *
     * Dog 和 Cat 都是 Animal，
     * 但是 Dog 不是 Cat，
     * Cat 也不是 Dog。
     */

    /* Dog dog4 = cat; // error，Dog 和 Cat 之间没有父子关系 */
}

void handleDog(Dog &dog)
{
    // 只能处理 Dog 类型对象
    // do sth
}

void handleCat(Cat &cat)
{
    // 只能处理 Cat 类型对象
    // do sth
}

// 可以复用的函数
void handleAnimal(Animal &animal)
{
    /**
     * handleAnimal 的参数是 Animal 引用。
     *
     * 因为 Dog 和 Cat 都是 Animal 的子类，
     * 所以 Dog 对象和 Cat 对象都可以传进来。
     *
     * 这样就提高了函数的复用性。
     */

    // do sth
}

void test2()
{
    Dog dog;
    Cat cat;

    /**
     * Dog 和 Cat 都可以向上转型为 Animal。
     *
     * 所以 handleAnimal 可以同时处理 Dog 对象和 Cat 对象。
     */

    handleAnimal(dog); // Dog ---> Animal
    handleAnimal(cat); // Cat ---> Animal
}

class GrandFather
{
public:
    /**
     * virtual 表示虚函数。
     *
     * 如果想使用 dynamic_cast 在父子类指针之间安全转换，
     * 父类中通常需要至少有一个虚函数。
     *
     * 有虚函数的类称为多态类型。
     */
    virtual void func(){}
};

class Father : public GrandFather
{
public:
    // Father 自己定义的成员
    int m_f = 1;
};

class Son : public Father
{
public:
    // Son 自己定义的成员
    int m_s = 2;
};

class GrandSon : public Son
{

};

void test3()
{
    // 使用父类型接收子对象
    Son son;

    // Son 类型指针指向 Son 对象
    Son *ps = &son;

    /**
     * 向上转型：
     *
     * 子类类型转换成父类类型。
     *
     * Son public 继承 Father，
     * 所以 Son is a Father。
     *
     * 因此 Son * 可以自动转换成 Father *。
     */

    /* Father *pf = &son; */

    Father *pf = ps; // 接收的类型 Son * ---> Father *
                     // 等价于 Father *pf = &son;

    /**
     * pf 的类型是 Father *。
     *
     * 虽然 pf 实际指向的是 Son 对象，
     * 但是通过 pf 只能访问 Father 类型中能够看到的成员。
     */

    pf->m_f; // 可以访问 Father 中的成员

    /* pf->m_s; // error，Father 类型指针看不到 Son 自己定义的成员 */

    /**
     * 通过父类指针访问子类对象时：
     *
     * 只能访问子类对象中继承自父类的那一部分数据。
     *
     * 不能访问子类自己新增的成员。
     *
     * 因为编译器是根据指针类型 Father * 来决定能访问哪些成员的。
     */

    /**
     * 向下转型：
     *
     * 父类类型转换成子类类型。
     *
     * Father * ---> Son *
     *
     * 向下转型不一定安全。
     */

    Father father;
    Father *f = &father;

    /**
     * 这里使用 C 风格强制类型转换：
     *
     * Father * ---> Son *
     *
     * 语法上可以通过，
     * 但是逻辑上不安全。
     *
     * 因为 f 实际指向的是 Father 对象，
     * 并不是 Son 对象。
     *
     * 如果后续通过 s 访问 Son 自己的成员 m_s，
     * 可能会产生未定义行为。
     */

    Son *s = (Son*)f; // Father * ---> Son *
}

// 转换的是接收的类型，跟对象是什么类型有关，跟变量名无关
void test4()
{
    /**
     * new Son{} 创建出来的真实对象是 Son。
     *
     * 但是使用 GrandFather * 来接收。
     *
     * 这里发生了向上转型：
     *
     * Son * ---> GrandFather *
     */

    GrandFather *gf = new Son{};

    /**
     * 向下转型：
     *
     * 使用 dynamic_cast 进行安全的向下转型。
     *
     * dynamic_cast 会在运行时检查对象的真实类型。
     *
     * 如果转换成功，返回有效指针。
     * 如果转换失败，返回 nullptr。
     */

    Father *f = dynamic_cast<Father*>(gf);

    /**
     * gf 的静态类型是 GrandFather *，
     * 但是 gf 实际指向的是 Son 对象。
     *
     * Son 继承 Father，
     * Father 继承 GrandFather。
     *
     * 所以 Son 对象中包含 Father 部分。
     *
     * 因此：
     * GrandFather * ---> Father *
     * 可以转换成功。
     */

    if(f){
        cout << "GrandFather * ---> Father *" << endl;
    }

    /**
     * f 实际指向的仍然是那个 Son 对象中的 Father 部分。
     *
     * 因为真实对象是 Son，
     * 所以 Father * ---> Son *
     * 也可以转换成功。
     */

    Son *s = dynamic_cast<Son*>(f);

    if(s){
        cout << "Father * ------> Son *" << endl;
    }

    /**
     * 继续向下转型：
     *
     * Son * ---> GrandSon *
     *
     * 但是当前真实对象是 Son，
     * 并不是 GrandSon。
     *
     * GrandSon 是 Son 的子类，
     * 但不是所有 Son 对象都是 GrandSon 对象。
     *
     * 所以这次 dynamic_cast 转换失败，
     * 返回 nullptr。
     */

    GrandSon *gs = dynamic_cast<GrandSon*>(s);

    // 此时转换失败了
    if(gs){
        cout << "Son*---->GrandSon*" << endl;
    }

    /**
     * 注意：
     * 这里使用 new 创建了对象，
     * 正常情况下需要 delete 释放。
     *
     * 但是如果通过父类指针 delete 子类对象，
     * 父类析构函数通常应该写成 virtual。
     *
     * 本例主要演示 dynamic_cast，
     * 所以暂时没有展开析构函数问题。
     */
}


int main(int argc, char *argv[])
{
    /* test1(); */

    // 测试父子类之间的 dynamic_cast 转换
    test4();

    return 0;
}