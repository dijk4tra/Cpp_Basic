#include <iostream>

using std::cout;
using std::endl;

class Stack
{
private:
    static const int MAX_SIZE = 5;  // 栈的最大容量
    int data[MAX_SIZE];             // 存放栈元素
    int topIndex;                   // 栈顶下标

public:
    Stack()
    {
        topIndex = -1;
    }

    // 判断栈是否为空
    bool empty()
    {
        return topIndex == -1;
    }

    // 判断栈是否已满
    bool full()
    {
        return topIndex == MAX_SIZE - 1;
    }

    // 元素入栈
    void push(int x)
    {
        if(full())
        {
            cout << "栈已满，无法入栈: " << x << endl;
            return;
        }
        topIndex++;
        data[topIndex] = x;
    }

    // 元素出栈
    void pop()
    {
        if(empty())
        {
            cout << "栈为空，无法出栈" << endl;
            return;
        }
        topIndex--;
    }

    // 获取栈顶元素
    int top()
    {
        if(empty())
        {
            cout << "栈为空，没有栈顶元素" << endl;
            return -1;
        }
        return data[topIndex];
    }
};

void test1(Stack & s)
{
    cout << "===== 测试 empty() =====" << endl;
    if (s.empty()) {
        cout << "测试通过：初始栈为空" << endl;
    } else {
        cout << "测试失败：初始栈应为空" << endl;
    }
}

void test2(Stack & s)
{
    cout << "===== 测试 push() 和 top() =====" << endl;
    s.push(10);
    if (!s.empty() && s.top() == 10) {
        cout << "测试通过：10 入栈后，栈顶元素为 10" << endl;
    } else {
        cout << "测试失败：push() 或 top() 出错" << endl;
    }

    s.push(20);
    if (s.top() == 20) {
        cout << "测试通过：20 入栈后，栈顶元素为 20" << endl;
    } else {
        cout << "测试失败：栈顶元素应为 20" << endl;
    }
}

void test3(Stack & s)
{
    cout << "===== 测试 pop() =====" << endl;
    s.pop();
    if (s.top() == 10) {
        cout << "测试通过：弹出 20 后，栈顶元素为 10" << endl;
    } else {
        cout << "测试失败：pop() 出错" << endl;
    }

    s.pop();
    if (s.empty()) {
        cout << "测试通过：弹出所有元素后，栈为空" << endl;
    } else {
        cout << "测试失败：栈应为空" << endl;
    }
}

void test4(Stack & s)
{
cout << "===== 测试空栈 pop() 和 top() =====" << endl;
    s.pop();  // 测试空栈出栈
    s.top();  // 测试空栈取栈顶
}

void test5(Stack & s)
{
    cout << "===== 测试 full() =====" << endl;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    if (s.full()) {
        cout << "测试通过：压入 5 个元素后，栈已满" << endl;
    } else {
        cout << "测试失败：栈应已满" << endl;
    }
}

void test6(Stack & s)
{
    cout << "===== 测试满栈 push() =====" << endl;
    s.push(6);  // 测试满栈入栈

    if (s.top() == 5) {
        cout << "测试通过：满栈继续入栈失败，栈顶仍为 5" << endl;
    } else {
        cout << "测试失败：满栈 push() 处理错误" << endl;
    }
}

int main(int argc, char *argv[])
{
    Stack s;
    
    test1(s);
    cout << endl;
    test2(s);
    cout << endl;
    test3(s);
    cout << endl;
    test4(s);
    cout << endl;
    test5(s);
    cout << endl;
    test6(s);

    return 0;
}

