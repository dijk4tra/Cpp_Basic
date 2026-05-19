#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Stack {
private:
    T* data;        // 动态数组，用来存放栈元素
    int capacity;   // 栈的最大容量
    int count;      // 当前栈中元素个数

public:
    // 构造函数
    Stack(int cap = 10) {
        capacity = cap;
        count = 0;
        data = new T[capacity];
    }

    // 析构函数
    ~Stack() {
        delete[] data;
    }

    // 入栈
    bool push(T value) {
        if (full()) {
            cout << "栈已满，无法入栈！" << endl;
            return false;
        }

        data[count] = value;
        count++;
        return true;
    }

    // 出栈
    bool pop() {
        if (empty()) {
            cout << "栈为空，无法出栈！" << endl;
            return false;
        }

        count--;
        return true;
    }

    // 查看栈顶元素
    T top() {
        if (empty()) {
            cout << "栈为空，没有栈顶元素！" << endl;
            return T();
        }

        return data[count - 1];
    }

    // 判断栈是否为空
    bool empty() {
        return count == 0;
    }

    // 判断栈是否已满
    bool full() {
        return count == capacity;
    }

    // 返回栈中元素个数
    int size() {
        return count;
    }

    // 显示栈中所有元素
    void show() {
        if (empty()) {
            cout << "栈为空！" << endl;
            return;
        }

        cout << "栈中元素：";
        for (int i = 0; i < count; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // 测试 int 类型栈
    cout << "测试 int 类型栈：" << endl;
    Stack<int> s1(5);

    s1.push(10);
    s1.push(20);
    s1.push(30);

    s1.show();

    cout << "栈顶元素：" << s1.top() << endl;
    cout << "栈中元素个数：" << s1.size() << endl;

    s1.pop();
    s1.show();

    cout << endl;

    // 测试 double 类型栈
    cout << "测试 double 类型栈：" << endl;
    Stack<double> s2(5);

    s2.push(1.1);
    s2.push(2.2);
    s2.push(3.3);

    s2.show();

    cout << "栈顶元素：" << s2.top() << endl;

    s2.pop();
    s2.show();

    cout << endl;

    // 测试 string 类型栈
    cout << "测试 string 类型栈：" << endl;
    Stack<string> s3(5);

    s3.push("C++");
    s3.push("Template");
    s3.push("Stack");

    s3.show();

    cout << "栈顶元素：" << s3.top() << endl;

    s3.pop();
    s3.show();

    return 0;
}