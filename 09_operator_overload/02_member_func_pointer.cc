#include <iostream>

using std::cout;
using std::endl;

void func1()
{
    cout << "func1() " << endl;
};

void func2()
{
    cout << "func2() " << endl;
}

void func3()
{
    cout << "func3() " << endl;
}

void test1()
{
    func1();
    func2();
    func3();
    cout << "---------" << endl;

    // 函数指针的简写形式：函数名可以隐式转换为函数地址
    void (*f)() = func1;
    f();

    // 函数指针的完整写法：显式取函数地址，并通过解引用调用
    f = &func2;
    (*f)(); // 调用 func2()
    cout << "---------" << endl;

    // 使用 typedef 为函数指针类型定义别名
    typedef void (*F)();
    int a = 1;
    F ff = &func1;
    ff();
    cout << "---------" << endl;

    // C++11 之后可以使用 using 定义类型别名
    // using 别名 = 被命名的类型
    using FFF = void(*)();
    int b = 1;
    FFF fff = &func3;
    fff();
}

class FFF
{
public:
    // 成员函数
    void f1()
    {
        cout << "FFF::f1()" << endl;
    }

    void f2()
    {
        cout << "FFF::f2()" << endl;
    }

    void f3()
    {
        cout << "FFF::f3()" << endl;
        cout << "m_data: " << m_data << endl;
    }

    int m_data = 1;
};

void test2()
{
    FFF obj;

    // 通过对象或对象指针调用成员函数
    obj.f1();
    obj.f2();
    obj.f3();

    FFF *ptr = &obj;
    ptr->f1();
    ptr->f2();
    ptr->f3();
    cout << "---------" << endl;

    // 成员函数指针需要带上类名作用域
    // 对成员函数指针而言，通常需要使用完整写法
    void (FFF::*fptr)() = &FFF::f1;

    // 通过对象调用成员函数指针
    (obj.*fptr)();

    // 通过对象指针调用成员函数指针
    (ptr->*fptr)();
}

// 空指针调用成员函数测试
void test3()
{   
    // 此时没有实际对象存在
    FFF *ptr = nullptr;

    ptr->f1();
    ptr->f2();
    ptr->f3();

    // 是否可以通过空指针调用成员函数？
    // 语法上可以通过编译，但运行时属于未定义行为，不应这样使用。
    //
    // 如果成员函数内部没有访问成员变量，某些情况下可能“看起来能运行”；
    // 但一旦访问成员变量，就需要依赖 this 指针定位对象数据。
    // 空指针没有指向有效对象，因此无法正确访问成员变量。
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}