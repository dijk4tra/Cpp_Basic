#include <iostream>
#include <functional>

using namespace std;

// ==================== 准备工作：定义各种可调用实体 ====================

// 普通函数
void normalFunction(int x) {
    cout << "普通函数调用，参数: " << x << endl;
}

// 定义一个类，用于演示成员函数和函数对象
class MyClass
{
public:
    // 成员函数
    void memberFunction(int x){
        cout << "成员函数调用，参数: " << x << endl;
    }

    // 函数对象（仿函数：重载了 operator()）
    void operator()(int x) const {
        cout << "函数对象 (Functor) 调用，参数: " << x << endl;
    }
};

// ==================== 主函数：使用 std::function 接收 ====================
int main()
{
    // 声明一个标准包装器，目标签名是 void(int)
    function<void(int)> func_wrapper;

    MyClass obj;
    // ----------------------------------------------------
    // ① 接收：普通函数
    // ----------------------------------------------------
    func_wrapper = normalFunction;
    func_wrapper(10);

    // ----------------------------------------------------
    // ② 接收：函数指针
    // ----------------------------------------------------
    void (*func_ptr)(int) = normalFunction;
    func_wrapper = func_ptr;
    func_wrapper(20);

    // ----------------------------------------------------
    // ③ & ④ 接收：成员函数指针
    // 注：由于成员函数隐式包含 this 指针，直接包装需要改变 function 的签名，
    // 如下所示（显式将类对象/指针作为第一个参数）：
    // ----------------------------------------------------
    function<void(MyClass&, int)> mem_func_wrapper = &MyClass::memberFunction;
    mem_func_wrapper(obj, 30);

    // ----------------------------------------------------
    // ⑤ 接收：函数对象 (仿函数 / Functor)
    // ----------------------------------------------------
    func_wrapper = obj; //或者传临时对象 MyClass()
    func_wrapper(40);

    // ----------------------------------------------------
    // ⑥ 接收：Lambda 表达式
    // ----------------------------------------------------
    func_wrapper = [](int x) {
        std::cout << "Lambda 表达式调用，参数: " << x << std::endl;
    };
    func_wrapper(50);
    
    // ----------------------------------------------------
    // ⑦ 接收：std::bind 表达式
    // 注：通过 bind 绑定对象实例和占位符，可以将【成员函数】完美转化为 `void(int)` 签名
    // ----------------------------------------------------
    func_wrapper = bind(&MyClass::memberFunction, &obj, std::placeholders::_1);
    func_wrapper(60);

    return 0;
}