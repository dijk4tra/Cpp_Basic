#include <iostream>
#include <stack>
#include <list>
#include <queue>
#include <string>

// stack
void test1()
{
    std::stack<int, std::list<int>> my_stack;
    my_stack.push(1);
    my_stack.push(2);
    my_stack.push(3);
    
    // 打印栈中的数据
    std::cout << "Stack 输出顺序: ";
    while(!my_stack.empty())
    {
        std::cout << my_stack.top() << " ";
        my_stack.pop();
    }
    std::cout << std::endl;
}

// queue
void test2()
{
    std::queue<std::string, std::list<std::string>> my_queue;

    my_queue.push("a");
    my_queue.push("b");
    my_queue.push("c");

    // 打印队列中的数据
    std::cout << "Queue 输出顺序: ";
    while(!my_queue.empty())
    {
        std::cout << my_queue.front() << " "; // 输出队首
        my_queue.pop(); // 弹出队列首元素
    }
    std::cout << std::endl;
}


int main()
{
    test1();
    test2();

    return 0;
}