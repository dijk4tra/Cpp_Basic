#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;


// 普通函数
void normal_func(int a, int b) {
    cout << "普通函数/函数指针 | 结果: " << a + b << endl;
}

class MyClass
{
    public:
    // 成员函数
    void mem_func(int a, int b) {
        cout << "成员函数/成员函数指针 | 结果: " << a + b << endl;
    }
};

// 函数对象（仿函数）
struct Functor {
    void operator()(int a, int b) const {
        cout << "函数对象 (Functor) | 结果: " << a + b << endl;
    }
};

// bind 绑定
int main(int argc, char * args[])
{   
    cout << "--- 开始执行 std::bind 6 种对象绑定测试 ---" << endl;
    
    // ----------------------------------------------------
    // 1. 普通函数 (Normal Function)
    // 直接传入函数名即可
    // ----------------------------------------------------
    // auto bind_normal = bind(normal_func, std::placeholders::_1, 10);
    auto bind_normal = bind(normal_func, _1, 10);
    bind_normal(100); // 相当于 normal_func(100, 10)

    // ----------------------------------------------------
    // 2. 函数指针 (Function Pointer)
    // 声明一个显式的函数指针，然后将其传给 bind
    // ----------------------------------------------------
    void (*func_ptr)(int, int) = normal_func;
    auto bind_func_ptr = bind(func_ptr, _1, 10);
    bind_func_ptr(100); // 相当于 normal_func(100, 10)

    // ----------------------------------------------------
    // 3. 成员函数 (Member Function)
    // 需要配合具体的“对象实例”来绑定。语法：&类名::函数名，后面紧跟对象地址
    // ----------------------------------------------------
    MyClass obj;
    auto bind_mem_func = bind(&MyClass::mem_func, &obj, _1, 10);
    bind_mem_func(100);

    // ----------------------------------------------------
    // 4. 成员函数指针 (Member Function Pointer)
    // 将类成员函数的地址先赋值给一个“成员函数指针变量”，再进行绑定
    // 注意：要获取成员函数的指针，必须显式、毫无歧义地使用 & 加上类名限定符！
    // ----------------------------------------------------
    void (MyClass::*mem_func)(int, int) = &MyClass::mem_func; // 这里必须加上&
    auto bind_mem_ptr = bind(mem_func, &obj, _1, 10);
    bind_mem_ptr(100);

    // ----------------------------------------------------
    // 5. 函数对象 / 仿函数 (Functor)
    // 实例化一个重载了 operator() 的结构体/类对象，传给 bind
    // ----------------------------------------------------
    Functor f;
    auto bind_functor = bind(f, _1, 10);
    bind_functor(100);

    // ----------------------------------------------------
    // 6. Lambda 表达式 (Lambda Expression)
    // 可以直接把匿名 Lambda 传进去，或者传存储了 Lambda 的变量
    // ----------------------------------------------------
    auto my_lambda = [](int a, int b) {
        cout << "Lambda 表达式 | 结果: " << a + b << endl;
    };
    auto bind_lambda = bind(my_lambda, _1, 10);
    bind_lambda(100);
    
    cout << "------------------------------------------" << endl;
    return 0;
}