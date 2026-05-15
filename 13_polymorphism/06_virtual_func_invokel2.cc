#include <iostream>

using std::cout;
using std::endl;

/**
 * 在构造函数、析构函数中调用虚函数：
 *
 * 结论：
 * 在构造函数和析构函数中调用虚函数，不会体现多态。
 *
 * 原因：
 * 1. 构造父类对象时，子类部分还没有构造完成；
 * 2. 析构父类对象时，子类部分已经先析构完成；
 * 3. 因此在构造函数或析构函数中调用虚函数时，
 *    调用的是当前类自己的函数版本，而不是子类重写后的版本。
 */

class GrandFather
{
public:
    GrandFather()
    {
        cout << "GrandFather()" << endl;
    }

    // 多态基类建议使用虚析构函数
    virtual ~GrandFather()
    {
        cout << "~GrandFather()" << endl;
    }

    virtual void func1()
    {
        cout << "GrandFather::func1()" << endl;
    }

    virtual void func2()
    {
        cout << "GrandFather::func2()" << endl;
    }
};

class Father : public GrandFather
{
public:
    Father()
    {
        cout << "Father()" << endl;

        // 在构造函数中调用虚函数
        // 不会调用 Son::func1()
        // 此时调用的是当前类 Father 中的 func1()
        func1();
    }

    virtual ~Father() override
    {
        cout << "~Father()" << endl;

        // C++标准中规定，在构造、析构函数在调用虚函数，体现的是当前类的版本
        
        // 在析构函数中调用虚函数
        // 不会调用 Son::func2()
        // 此时调用的是当前类 Father 中的 func2()
        func2();
    }

    // 在 Father 类中重写 GrandFather 的虚函数
    virtual void func1() override
    {
        cout << "Father::func1()" << endl;
    }

    virtual void func2() override
    {
        cout << "Father::func2()" << endl;
    }
};

class Son : public Father
{
public:
    Son()
    {
        cout << "Son()" << endl;
    }

    virtual ~Son() override
    {
        cout << "~Son()" << endl;
    }

    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }

    virtual void func2() override
    {
        cout << "Son::func2()" << endl;
    }
};

void test1()
{
    Son son;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}