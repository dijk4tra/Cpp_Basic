#include <iostream>

using std::cout;
using std::endl;

/*
 * 类中权限修饰符
 * 1.public : 可以任意访问
 * 2.private: 在类外部不可以访问,类的内部可以访问
 * 3.protected(后面讲)
 *
 */

class MyClass
{
public:
    int data1;
public:
    void func1()
    {
        cout << "func1()" << endl;
        cout << data2;
    }
private:
    int data2;
    void func2()
    {
        cout << "func2()" << endl;
    }
};


void test1()
{
    MyClass obj;
    // 通过对象.方式访问成员
    obj.data1;
    /* obj.data2; //private*/
    obj.func1();
    /* obj.func2();//private */
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

