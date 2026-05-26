#include <iostream>
#include <functional>
#include <vector>
#include <string>

using namespace std;

// ==========================================
// 1. 接口包装类（基于对象的多态核心）
// ==========================================
class Figure
{
public:
    // 将 function<double()> 作为一个通用的“面积计算”接口
    using AreaCall = function<double()>;

    // 【注册回调函数】：接收任何符合 double() 签名的可调用对象
    void setAreaCall(AreaCall areaCall)
    {
        m_areaCall = areaCall;
    }

    // 【执行回调函数】：负责统一的调用逻辑
    void handleAreaCall()
    {
        if (m_areaCall)
        {
            cout << "[Figure] 准备调用注册的面积回调函数..." << endl;
            cout << "计算结果 area: " << m_areaCall() << endl;
        }
        else
        {
            cout << "[Warning] 未注册任何面积回调函数！" << endl;
        }
    }

private:
    // 让新类型作为数据成员（组合胜于继承）
    AreaCall m_areaCall;
};

// ==========================================
// 2. 两个完全独立的业务类（没有任何继承关系）
// ==========================================
class Rectangle
{
public:
    Rectangle(double l, double w) : m_l(l), m_w(w) {}

    double area()
    {
        cout << "-> 正在调用 Rectangle::area()" << endl;
        return m_l * m_w;
    }

private:
    double m_l;
    double m_w;
};

class Circle 
{
public:
    Circle(double r) : m_r(r) {}

    double area()
    {
        cout << "-> 正在调用 Circle::area()" << endl;
        return m_r * m_r * 3.14; // 此处 3.14 为简化计算
    }

private:
    double m_r;
};

// ==========================================
// 测试 1：演示 std::bind + std::function 实现基于对象的多态
// ==========================================
void test1()
{
    cout << "=== test1() 开始（基于对象的多态演示） ===" << endl;
    
    Rectangle r(3.0, 4.0);
    Circle c(2.0);
    Figure figure;
    
    // 1. 绑定并注册矩形的面积函数
    // &Rectangle::area 需要一个隐式的 this 指针，所以把对象地址 &r 传进去
    figure.setAreaCall(bind(&Rectangle::area, &r));
    figure.handleAreaCall();

    cout << "---------------------------------------" << endl;

    // 2. 动态切换：绑定并注册圆形的面积函数
    figure.setAreaCall(bind(&Circle::area, &c));
    figure.handleAreaCall();

    cout << "=== test1() 结束 ===\n" << endl;
}


// ==========================================
// 测试 2：Lambda 表达式捕获局部变量的生命周期陷阱
// ==========================================
vector<function<void()>> functions;

void func()
{
    double num1 = 3.14;
    int num2 = 2;

    // ❌ 核心Bug修改：原代码使用 [&] 引用捕获
    // 因为 num1 和 num2 是栈上的局部变量，出了 func() 作用域就被销毁了。
    // 如果用引用捕获，后续在 test2 中调用时会访问悬空引用，导致未定义行为（打印乱码或崩溃）。
    // 【修复方案】：改用 [=] 值捕获，将变量副本拷贝一份存入 Lambda 闭包中。
    functions.push_back(
        [=]() -> void {
            cout << "捕获的 num1: " << num1 << endl;
            cout << "捕获的 num2: " << num2 << endl;
        }
    );
}

void test2()
{
    cout << "=== test2() 开始（Lambda 生命周期安全演示） ===" << endl;
    func();
    for (auto &f : functions)
    {
        f(); // 安全调用值捕获的 Lambda
    }
    cout << "=== test2() 结束 ===" << endl;
}

// ==========================================
// 主函数
// ==========================================
int main(int argc, char const *argv[])
{
    test1(); // 运行基于对象的多态例子
    test2(); // 运行 Lambda 安全闭包例子
    
    return 0;
}