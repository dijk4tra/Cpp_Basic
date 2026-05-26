#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

class Printer {
public:
    // const 成员函数，输出字符串 s
    void print(const string& s) const {
        cout << s << endl;
    }
};

int main()
{
    // 创建 vector<Printer> 并包含 3 个 Printer 对象
    vector<Printer> printers(3);

    cout << "--- 组合调用开始 ---" << endl;

    // 使用 for_each + mem_fn + bind 让每个对象输出 "Hello"
    //
    // 核心原理拆解：
    // a. mem_fn(&Printer::print) 
    //    将成员函数指针包装成一个普通的函数对象，此时它需要的签名是：f(Printer对象, "Hello")
    //
    // b. bind(..., placeholders::_1, "Hello")
    //    由于 for_each 只能给它一个参数（Printer对象），我们用 bind 把第二个参数死死固定为 "Hello"。
    //    placeholders::_1 代表 for_each 遍历到的每一个具体 Printer 对象。
    //
    // c. 最终 bind 生成了一个只需接收一个 Printer 对象的一元函数对象，完美适配 for_each。

    for_each(printers.begin(), printers.end(),
             bind(mem_fn(&Printer::print), placeholders::_1, "Hello"));

    return 0;
}

/**
 * std::mem_fn 的本质作用：
 * std::mem_fn 是 C++11 引入的成员函数包装器。
 * 它的作用是把一个必须依赖类对象才能调用的成员函数，变成一个可以像普通独立函数一样调用的函数对象。
 *     原生调用: obj.print("Hello");
 *     mem_fn 包装后的调用: auto f = mem_fn(&Printer::print); 
 *                         f(obj, "Hello");
 * 
 * 在 for_each 执行时，它在底层做的事情等价于：
 * for (auto& item : printers) {
 *     // 调用我们用 bind 组装好的“大招”
 *     表达形式(item); 
 * }
 * 
 * 第一步转化 (mem_fn)：将 void Printer::print(string) 转化为可以脱离对象语法的 void(Printer, string)。
 * 第二步降维 (bind)：把 void(Printer, string) 的第二个参数填入固定值 "Hello"，使其降维成 void(Printer)。
 * 第三步消费 (for_each)：for_each 遍历并依次把 item 送入 void(Printer) 中，大功告成！
 */