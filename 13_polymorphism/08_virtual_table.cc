#include <iostream>

using std::cout;
using std::endl;

/**
 * 通过对象内存观察虚函数表：
 *
 * 当一个类中含有虚函数时，主流编译器通常会在对象中保存一个虚函数指针 vfptr。
 * vfptr 指向该类对应的虚函数表 vtable。
 *
 * 对象的大致结构：
 *
 * Father 对象：
 * ------------------------------------------------
 * | vfptr | m_f |
 * ------------------------------------------------
 *
 * Son 对象：
 * ------------------------------------------------
 * | vfptr | Father::m_f | Son::m_s |
 * ------------------------------------------------
 *
 * 注意：
 * 1. vfptr 和 vtable 是主流编译器常见的实现方式，
 *    C++ 标准并没有强制规定对象必须这样布局。
 *
 * 2. 虚函数表中的函数地址直接调用时，实际还需要传入 this 指针。
 *    不同编译器、不同平台的虚函数表布局可能不同。
 */

class Father
{
public:
    virtual void func1()
    {
        cout << "Father::func1()" << endl;
    }

    virtual void func2()
    {
        cout << "Father::func2()" << endl;
    }

    virtual void func3()
    {
        cout << "Father::func3()" << endl;
    }

    long m_f = 1;
};

class Son : public Father
{
public:
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }

    virtual void func2() override
    {
        cout << "Son::func2()" << endl;
    }

    virtual void func3() override
    {
        cout << "Son::func3()" << endl;
    }

    long m_s = 2;
};

void test1()
{
    // 验证 Father 对象的内存布局
    Father father;

    // 将 Father 对象的地址强制转换为 long*，
    // 目的是按 long 类型逐段查看对象内存中的内容
    long * f = (long*)&father;

    // 通常情况下，含有虚函数的对象开头会存放虚函数指针 vfptr。
    // f[0] 表示对象中的第一个 long 大小的数据，
    // 在常见实现中，它就是虚函数指针 vfptr 的值，
    // 也就是虚函数表 vftable 的地址
    cout << f[0] << endl; 

    cout << f[1] << endl; // f[1] 通常对应 Father 类中的成员变量 m_f。

    // 将 f[0] 中保存的地址再次转换为 long*，
    // 目的是把虚函数表当作一个地址数组来访问
    long * vftable_f = (long*)f[0];

    // 定义函数指针类型 F，
    // 该类型表示：无参数、无返回值的函数指针
    typedef void(*F)();
    F f1 = (F)vftable_f[0]; // 取出虚函数表中的第 1 个函数地址
    f1();
    F f2 = (F)vftable_f[1]; // 取出虚函数表中的第 2 个函数地址
    f2();
    F f3 = (F)vftable_f[2]; // 取出虚函数表中的第 3 个函数地址
    f3();

    cout << "---------" << endl;

    // 验证 Son 对象的内存布局
    Son son;
    long * s = (long*)&son;
    cout << s[0] << endl; // 虚函数指针指向的虚函数表的地址
    cout << s[1] << endl; // 从Father类继承来的成员变量 m_f
    cout << s[2] << endl; // Son类自己定义的成员变量 m_s
    long * vftable_s = (long*)s[0];
    typedef void(*S)();
    S s1 = (S)vftable_s[0];
    s1();
    S s2 = (S)vftable_s[1];
    s2();
    S s3 = (S)vftable_s[2];
    s3();

}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

