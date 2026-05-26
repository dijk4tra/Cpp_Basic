#include <iostream>
#include <functional>

using namespace std;

/**
 * std::function 与 std::bind
 *
 * 1. 函数指针
 *
 *    函数指针只能指向普通函数，不能接收 std::bind 的返回结果。
 *
 *    std::bind 返回的是一个可调用对象，也就是函数对象，
 *    它不是普通函数指针。
 *
 * 2. std::function
 *
 *    std::function 是一个通用的函数包装器，
 *    可以保存各种可调用对象，例如：
 *
 *    - 普通函数
 *    - 函数指针
 *    - 函数对象
 *    - lambda 表达式
 *    - 成员函数
 *    - std::bind 的返回结果
 *
 * 3. 函数签名
 *
 *    std::function<返回值类型(参数类型列表)>
 *
 *    例如：
 *    std::function<int(int, int)>
 *    表示可以保存返回值为 int，参数为两个 int 的可调用对象。
 *
 * 4. std::bind
 *
 *    std::bind 可以提前绑定部分参数，
 *    从而改变一个可调用对象的调用形式。
 *
 *    例如：
 *    int(int, int)  --->  int()
 *    int(int, int)  --->  int(int)
 */

int func(int a, int b)
{
    cout << "a:" << a << " b:" << b << endl;
    return a + b;
}

// 函数指针能否接收 bind 的返回结果
void test1()
{
    // 直接调用普通函数
    func(1, 2);

    cout << "-------" << endl;

    // 定义函数指针类型：
    // F 表示一个函数指针，指向返回值为 int，参数为 int、int 的函数
    using F = int(*)(int, int);

    // 函数名可以隐式转换为函数指针
    F f = func;
    f(1, 2);

    // 上下两种写法是等价的

    cout << "-------" << endl;

    // 也可以显式取函数地址
    int (*f1)(int, int) = &func; 
    f1(3, 4);

    // 使用 auto 接收 bind 的返回结果
    // bind(func, 10, 20) 会把 func 的两个参数都提前绑定好
    // 因此 f2 调用时不需要再传参
    auto f2 = bind(func, 10, 20);
    f2();

    cout << "-------" << endl;
    
    // f1 = bind(func, 100, 200); 
    // 错误：
    // bind 返回的是函数对象，不是普通函数指针，
    // 所以不能用函数指针接收 bind 的返回结果。

    // 如果想统一接收 bind 的返回结果，可以使用 std::function
}

// std::function 存储普通函数
void test2()
{
    // func 的函数签名是：
    // int func(int, int)
    //
    // 因此可以使用 std::function<int(int, int)> 接收
    // 要保持返回值类型和参数列表一致
    std::function<int(int, int)> f3 = func;
    f3(1, 2);

    cout << "----------" << endl;

    // 使用 bind 绑定 func 的两个参数
    //
    // 原来的调用形式：
    // int(int, int)
    //
    // 绑定两个参数之后：
    // int()
    std::function<int()> f4 = bind(func, 1, 2);
    f4();
}

// std::function 存储函数指针
void test3()
{
    // &func 是函数地址，也可以赋值给 std::function
    //
    // func 的函数签名是：
    // int(int, int)
    std::function<int(int, int)> f3 = &func;
    f3(1, 2);

    cout << "----------" << endl;
    
    // bind 也可以绑定函数地址
    //
    // 原来的调用形式：
    // int(int, int)
    //
    // 绑定两个参数之后：
    // int()
    std::function<int()> f4 = bind(&func, 1, 2);
    f4();
}

struct Callable
{
    // 重载函数调用运算符，使对象可以像函数一样被调用
    int operator()(int a, int b)
    {
        cout << "a:" << a << " b:" << b << endl;
        return a + b;
    }
};

// std::function 存储函数对象
void test4()
{
    // Callable() 是一个临时函数对象
    //
    // Callable::operator() 的返回值是 int，
    // 这里用 function<void(int, int)> 接收时，
    // 返回值会被忽略，只关注调用参数
    function<void(int, int)> f1 = Callable();
    f1(1, 2);

    // 使用 bind 改变函数对象的调用形式
    //
    // 原来的调用形式：
    // int(int, int)
    //
    // 绑定第一个参数为 1 后：
    // int(int)
    //
    // std::placeholders::_1 表示调用 f2 时传入的第一个参数
    function<void(int)> f2 = bind(Callable(), 1, std::placeholders::_1);
    f2(100);
}

// std::function 存储 lambda 表达式
void test5()
{
    // lambda 的调用形式是：
    // void(int)
    function<void(int)> f1 = [](int num)->void{
        cout << "Hello, Lambda!" << endl;
        cout << num << endl;
    };
    f1(100);

    // 使用 bind 绑定 lambda 的参数
    //
    // 原来的调用形式：
    // void(int)
    //
    // 绑定参数 200 后：
    // void()
    function<void()> f2 = bind([](int num)->void{
        cout << "Hello, Lambda!" << endl;
        cout << num << endl;
    }, 200);
    f2();
}

class MyClass
{
public:
    // 普通成员函数
    // 成员函数调用时必须依赖某个对象
    void func(int a, int b)
    {
        cout << "a = " << a << " b = " << b << endl;
    }
};

// std::function 存储成员函数
void test6()
{
    MyClass obj;

    // 方式一：对象调用成员函数
    obj.func(1, 2);

    // 方式二：对象指针调用成员函数
    MyClass * p = &obj;
    p->func(3, 4);

    cout << "----------" << endl; 

    // 成员函数指针需要额外传入对象
    //
    // 第一种形式：
    // void(MyClass&, int, int)
    //
    // 第一个参数是对象引用，
    // 后两个参数才是成员函数本身需要的参数
    function<void(MyClass&, int, int)> f1 = &MyClass::func;
    f1(obj, 10, 20);

    // 第二种形式：
    // void(MyClass*, int, int)
    //
    // 第一个参数也可以是对象指针
    function<void(MyClass*, int, int)> f2 = &MyClass::func;
    f2(&obj, 30, 40);

    // 使用 bind 绑定成员函数所属的对象
    //
    // 原来的调用形式：
    // void(MyClass&, int, int)
    //
    // 绑定对象 obj 后：
    // void(int, int)
    function<void(int, int)> f3 = bind(&MyClass::func, obj, std::placeholders::_1, std::placeholders::_2);
    f3(100, 200);

    // 也可以绑定对象指针
    //
    // 原来的调用形式：
    // void(MyClass*, int, int)
    //
    // 绑定对象地址 &obj 后：
    // void(int, int)
    function<void(int, int)> f4 = bind(&MyClass::func, &obj, std::placeholders::_1, std::placeholders::_2);
    f4(300, 400);
}

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}