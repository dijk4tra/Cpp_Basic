#include <iostream>

using std::cout;
using std::endl;

/**
 * 多继承中的虚函数表：
 *
 * 当一个类继承多个带有虚函数的基类时，派生类对象中通常会包含多个
 * 基类子对象。每个含虚函数的基类子对象，通常都会有各自的虚函数指针
 * vfptr，分别指向与该基类子对象对应的虚函数表。
 *
 * 在主流编译器实现中：
 * 1. 每个含虚函数的基类子对象通常对应一个 vfptr；
 * 2. 不同的 vfptr 可能指向不同的虚函数表；
 * 3. 如果派生类重写了多个基类中签名兼容的虚函数，那么派生类中的
 *    一个 override 可以同时覆盖这些基类虚函数；
 * 4. 通过不同基类指针或引用调用虚函数时，会根据该基类子对象对应的
 *    虚函数表进行动态绑定；
 * 5. 在多继承场景下，虚函数表项中可能并不直接保存目标函数地址，
 *    也可能通过 thunk 等机制调整 this 指针后再调用实际函数。
 *
 * 注意：
 * vfptr、虚函数表、thunk 以及对象内存布局都属于编译器实现细节，
 * C++ 标准只规定虚函数调用的语义，不规定对象内部必须如何存储。
 */

class Father1
{
public:
    virtual void func1()
    {
        cout << "Father1::func1()" << endl; 
    }
    virtual void func2()
    {
        cout << "Father1::func2()" << endl; 
    }
    virtual void func3()
    {
        cout << "Father1::func3()" << endl; 
    }
};

class Father2
{
public:
    virtual void func1()
    {
        cout << "Father2::func1()" << endl; 
    }
    virtual void func2()
    {
        cout << "Father2::func2()" << endl; 
    }
    virtual void func3()
    {
        cout << "Father2::func3()" << endl; 
    }
};

class Father3
{
public:
    virtual void func1()
    {
        cout << "Father3::func1()" << endl; 
    }
    virtual void func2()
    {
        cout << "Father3::func2()" << endl; 
    }
    virtual void func3()
    {
        cout << "Father3::func3()" << endl; 
    }
};

class Son
: public Father1
, public Father2
, public Father3
{
public:
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }
};


void test1()
{
    Son son;
    cout << sizeof(son) << endl; // 24: 3个vfptr
    Father1 * f1 = &son;
    f1->func1();
    f1->func2();
    f1->func3();
    cout << "---------" << endl;
    Father2 * f2 = &son;
    f2->func1();
    f2->func2();
    f2->func3();
    cout << "---------" << endl;
    Father3 * f3 = &son;
    f3->func1();
    f3->func2();
    f3->func3();
    cout << "---------" << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

