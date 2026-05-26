#include <iostream>
#include <functional>
#include <map>
#include <string>

using namespace std;

// ==========================================
// 1. 定义具体的操作独立函数（无任何继承关系）
// ==========================================
int add(int x, int y)
{
    return x + y;
}

int substract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

// ==========================================
// 2. 主函数：建立映射并处理输入
// ==========================================
int main()
{
    // 创建一个 map 容器
    // Key 为运算符字符串（如 "+", "-"），
    // Value 为统一的函数包装器容器 function<int(int, int)>
    map<string, function<int(int, int)>> calculator;

    // 使用 std::bind 绑定普通函数，并通过占位符完全转发参数
    // placeholders::_1 代表将来调用时的第一个实参，_2 代表第二个实参
    calculator["+"] = bind(&add, placeholders::_1, placeholders::_2);
    calculator["-"] = bind(&substract, placeholders::_1, placeholders::_2);
    calculator["*"] = bind(&multiply, placeholders::_1, placeholders::_2);

    // 交互界面
    cout << "========================================" << endl;
    cout << "       基于 std::bind 的函数式计算器     " << endl;
    cout << "========================================" << endl;
    cout << "请输入计算表达式 (格式为: 数字 运算符 数字，如: 12 * 5): " << endl;

    int num1, num2;
    string op;

    // 循环读取输入，直到用户输入非法或结束
    while (cout << "\n请输入 > " && cin >> num1 >> op >> num2) {
        // 在 map 中查找对应的运算符
        auto it = calculator.find(op);

        if (it != calculator.end()){
            // 通过迭代器找到对应的 std::function，并执行回调
            // it->second 拿到的就是对应的绑定的可调用对象
            int result = it->second(num1, num2);

            cout << "【计算成功】: " << num1 << " " << op << " " << num2 << " = " << result << endl;
        } else {
            cout << "【错误提示】: 不支持的运算符 '" << op << "'，目前仅支持 +, -, *" << endl;
        }
    }

    cout << "\n感谢使用，程序已退出。" << endl;
    return 0;
}
