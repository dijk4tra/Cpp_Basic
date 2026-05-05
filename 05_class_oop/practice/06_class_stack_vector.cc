#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Stack
{
private:
    vector<int> data; // 使用vector存储栈元素
    int maxSize;      // 栈的最大容量

public:
    Stack(int size = 5)
    {
        maxSize = size;
    }

    // 判断栈是否为空
    bool empty()
    {
        return data.empty();
    }

    // 判断栈是否已满
    bool full()
    {
        return data.size() == maxSize;
    }

    // 元素入栈
    void push(int x)
    {
        if(full()){
            cout << "栈已满,无法入栈: " << x << endl;
            return;
        }
        data.push_back(x);
    }
    
    // 元素出栈
    void pop()
    {
        if(empty()){
            cout << "栈为空，无法出栈" << endl;
            return;
        }
        data.pop_back();
    }

    // 获取栈顶元素
    int top()
    {
        if(empty()){
            cout << "栈为空,没有栈顶元素" << endl;
            return -1;
        }
        return data.back();
    }



};

int main(int argc, char *argv[])
{   
    Stack s(3);   // 创建一个最大容量为 3 的栈

    cout << "===== 测试 empty() =====" << endl;
    cout << (s.empty() ? "测试通过：初始栈为空" : "测试失败") << endl;

    cout << "\n===== 测试 push() 和 top() =====" << endl;
    s.push(10);
    cout << (s.top() == 10 ? "测试通过：栈顶为 10" : "测试失败") << endl;

    s.push(20);
    cout << (s.top() == 20 ? "测试通过：栈顶为 20" : "测试失败") << endl;

    cout << "\n===== 测试 pop() =====" << endl;
    s.pop();
    cout << (s.top() == 10 ? "测试通过：弹出后栈顶为 10" : "测试失败") << endl;

    s.pop();
    cout << (s.empty() ? "测试通过：弹空后栈为空" : "测试失败") << endl;

    cout << "\n===== 测试空栈 pop() 和 top() =====" << endl;
    s.pop();
    s.top();

    cout << "\n===== 测试 full() =====" << endl;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << (s.full() ? "测试通过：栈已满" : "测试失败") << endl;

    cout << "\n===== 测试满栈 push() =====" << endl;
    s.push(4);

    cout << (s.top() == 3 ? "测试通过：满栈入栈失败，栈顶仍为 3" : "测试失败") << endl;

    return 0;
}

