#include <iostream>

using std::cout;
using std::endl;

/*
 * 继承的意义之一：
 * 可以把子类对象当作父类对象来使用，
 * 前提是满足“子类 is a 父类”的关系。
 *
 * 逻辑层面：
 * 狗是动物
 * 猫是动物
 *
 * 代码层面：
 * 可以使用父类引用或父类指针接收子类对象。
 *
 * 例如：
 * Animal &ref = dog;
 * Animal *ptr = &dog;
 *
 * 注意：
 * 一般不建议用父类对象直接接收子类对象，
 * 因为会发生对象切片，只保留父类部分。
 *
 * 反过来不一定成立：
 * 动物不一定是狗
 * 动物不一定是猫
 *
 * 在继承关系中，父子类之间常见的转换：
 * 1. 向上转型：子类类型 -> 父类类型，通常可以自动完成；
 * 2. 向下转型：父类类型 -> 子类类型，通常需要强制转换。
 *
 * 注意：
 * 向下转型时，对象的真实类型很重要。
 */

class Animal
{
public:

};

class Dog : public Animal
{

};

class Cat : public Animal
{

};

void test1()
{
    // 常规做法：用对应类型的变量接收对应类型的对象
    Animal animal;
    Dog dog;
    Cat cat;

    Dog &dog2 = dog;
    Cat &cat2 = cat;

    cout << "---------" << endl;

    /*
     * 使用继承后，如果满足“子类 is a 父类”的关系，
     * 就可以使用父类引用或父类指针接收子类对象。
     *
     * 这叫向上转型，通常可以自动完成。
     */
    Animal &animal2 = dog;
    Animal *p = &dog;

    Animal &animal3 = cat;
    Animal *p2 = &cat;

    /*
     * 反过来不行：
     * 父类对象不能直接当作子类对象使用。
     */
    /* Dog dog3 = animal; // error：动物不一定是狗 */

    /*
     * 没有继承关系的两个类之间，也不能直接转换。
     */
    /* Dog dog4 = cat; // error：Dog 和 Cat 之间没有直接继承关系 */
}

void handleDog(Dog &dog)
{
    // 只能处理 Dog 对象
}

void handleCat(Cat &cat)
{
    // 只能处理 Cat 对象
}

// 使用父类引用作为参数，可以同时接收 Dog、Cat 等 Animal 的子类对象
void handleAnimal(Animal &animal)
{
    // 可以处理所有 Animal 类型及其子类对象
}

void test2()
{
    Dog dog;
    Cat cat;

    handleAnimal(dog); // Dog is a Animal
    handleAnimal(cat); // Cat is a Animal
}

class GrandFather
{
public:
    /*
     * dynamic_cast 用于父子类指针/引用转换时，
     * 通常要求基类是多态类型。
     *
     * 类中只要有虚函数，就是多态类型。
     */
    virtual void func()
    {

    }

    virtual ~GrandFather()
    {

    }
};

class Father : public GrandFather
{
public:
    int m_f = 1;
};

class Son : public Father
{
public:
    int m_s = 2;
};

class GrandSon : public Son
{

};

void test3()
{
    Son son;
    Son *ps = &son;

    /*
     * 向上转型：
     * Son* -> Father*
     *
     * 子类指针可以自动转换为父类指针。
     */
    Father *pf = ps;

    pf->m_f; // 可以访问 Father 中的成员

    /*
     * 不能通过 Father* 直接访问 Son 自己定义的成员。
     * 因为 pf 的静态类型是 Father*。
     */
    /* pf->m_s; // error */

    /*
     * 向下转型：
     * Father* -> Son*
     *
     * 向下转型时，需要判断对象的真实类型。
     */
    Father father;
    Father *f = &father;

    /*
     * f 实际指向的是 Father 对象，不是 Son 对象，
     * 因此转换为 Son* 会失败，返回 nullptr。
     */
    Son *s = dynamic_cast<Son *>(f);

    if (s)
    {
        cout << "Father* ---> Son* success" << endl;
    }
    else
    {
        cout << "Father* ---> Son* failed" << endl;
    }
}

void test4()
{
    Son son;

    /*
     * gf 的静态类型是 GrandFather*，
     * 但它实际指向的是 Son 对象。
     */
    GrandFather *gf = &son;

    /*
     * 向下转型：
     * GrandFather* -> Father*
     *
     * 因为 gf 实际指向的是 Son 对象，
     * 而 Son 是 Father 的子类，
     * 所以转换可以成功。
     */
    Father *f = dynamic_cast<Father *>(gf);

    if (f)
    {
        cout << "GrandFather* ---> Father*" << endl;
    }

    /*
     * 向下转型：
     * Father* -> Son*
     *
     * f 实际指向的仍然是 Son 对象，
     * 所以转换可以成功。
     */
    Son *s = dynamic_cast<Son *>(f);

    if (s)
    {
        cout << "Father* ------> Son*" << endl;
    }

    /*
     * 继续向下转型：
     * Son* -> GrandSon*
     *
     * 虽然 GrandSon 是 Son 的子类，
     * 但当前对象的真实类型是 Son，不是 GrandSon，
     * 所以转换失败，返回 nullptr。
     */
    GrandSon *gs = dynamic_cast<GrandSon *>(s);

    if (gs)
    {
        cout << "Son* ----> GrandSon*" << endl;
    }
    else
    {
        cout << "Son* ----> GrandSon* failed" << endl;
    }
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test4();

    return 0;
}