#include <iostream>
#include <functional>

using namespace std;

class Calculator
{
public:
    int add(int x, int y){
        return x + y;
    }
};

int main()
{
    Calculator calc;

    // =================================================================
    // 任务 1：固定第一个参数为 10，第二个参数动态提供
    // =================================================================
    // 原函数签名：add(this, x, y)
    // 绑定关系：x 固定为 10，y 对应新函数的第一个参数 placeholders::_1
    function<int(int)> func1 = bind(&Calculator::add, &calc, 10, placeholders::_1);

    // =================================================================
    // 任务 2：固定第二个参数为 20，第一个参数动态提供
    // =================================================================
    // 原函数签名：add(this, x, y)
    // 绑定关系：x 对应新函数的第一个参数 placeholders::_1，y 固定为 20
    function<int(int)> func2 = bind(&Calculator::add, &calc, placeholders::_1, 20);

    cout << "--- 测试结果 ---" << endl;
    int result1 = func1(5);
    cout << "固定第一个参数(10)，传入5 后的计算结果: " << result1 << endl;

    // 传入 5，实际计算：5 + 20
    int result2 = func2(5);
    cout << "固定第二个参数(20)，传入5 后的计算结果: " << result2 << endl;

    return 0;
}