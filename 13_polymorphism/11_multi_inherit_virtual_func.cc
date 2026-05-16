#include <iostream>

using std::cout;
using std::endl;

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

