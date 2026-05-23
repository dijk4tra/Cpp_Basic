#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <queue>
#include <deque>        
#include <functional>   // std::greater

using namespace std;

/*
 * 容器适配器:
 *    1. stack          栈，后进先出 LIFO
 *    2. queue          队列，先进先出 FIFO
 *    3. priority_queue 优先级队列，默认大顶堆
 *
 * 容器适配器并不是新的容器，而是在已有容器的基础上，
 * 封装出特定的数据结构操作接口。
 */

// stack
void test1()
{
    // stack 默认底层容器是 deque
    stack<int> s;

    // 入栈：元素依次压入栈顶
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    // top() 获取栈顶元素，但不会删除元素
    // pop() 删除栈顶元素
    // cout << s.top() << endl;
    // s.pop();
    // cout << s.top() << endl;
    
    // 遍历栈中的所有元素
    // 注意：stack 不支持迭代器遍历，只能不断访问栈顶并弹出
    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }

    cout << "------" << endl;

    // 栈为空时，不能调用 top()，否则行为未定义
    // cout << s.top() << endl;
}


// stack
void test2()
{
    // 指定 stack 的底层容器为 vector
    // vector 支持 back()、push_back()、pop_back()，满足 stack 的要求
    stack<int, vector<int>> s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    // 遍历结束后，栈中元素会被全部弹出，容器为空
    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
}


// stack
void test3()
{
    // 指定 stack 的底层容器为 list
    // list 支持 back()、push_back()、pop_back()，满足 stack 的要求
    stack<int, list<int>> s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    
    // 遍历结束后，栈中元素会被全部弹出，容器为空
    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
}


// queue
void test4()
{
    // queue 默认底层容器是 deque
    queue<int> q;

    // 入队：元素从队尾进入
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);

    // 遍历队列中的所有元素
    // 注意：queue 不支持迭代器遍历，只能访问队头并弹出
    while(!q.empty())
    {
        // front() 获取队头元素
        cout << q.front() << endl;

        // pop() 弹出队头元素
        q.pop();
    }
}

// queue
void test5()
{
    // queue 的底层容器需要支持 front()、back()、push_back()、pop_front()
    // vector 不支持 pop_front()，因此不能作为 queue 的底层容器
    // queue<int, vector<int>> q; // error

    // list 支持 push_back() 和 pop_front()，可以作为 queue 的底层容器
    queue<int, list<int>> q;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    // 入队顺序：1 2 3 4

    // 出队顺序：1 2 3 4
    while (!q.empty())
    {
        cout << q.front() << endl;
        q.pop();
    }
}


// priority_queue
void test6()
{
    // priority_queue 默认底层容器是 vector
    // 默认比较规则是 less<T>，因此默认是大顶堆
    priority_queue<int> q;

    q.push(2);
    q.push(1);
    q.push(4);
    q.push(3);
    // 插入顺序：2 1 4 3
    
    // 遍历优先级队列
    // 注意：priority_queue 不支持迭代器遍历，只能不断访问堆顶并弹出
    while(!q.empty())
    {
        // top() 获取当前优先级最高的元素
        cout << q.top() << endl;
        q.pop();
    }

    // 默认大顶堆，输出顺序：4 3 2 1
}

// priority_queue
void test7()
{
    // 指定 priority_queue 的底层容器为 deque
    // priority_queue 的底层容器需要支持随机访问迭代器
    // deque 和 vector 都满足要求，list 不满足要求
    //
    // 第三个模板参数 std::greater<int> 表示使用“小顶堆”
    priority_queue<int, deque<int>, std::greater<int>> q;

    q.push(2);
    q.push(1);
    q.push(4);
    q.push(3);
    // 插入顺序：2 1 4 3

    // 遍历优先级队列
    while(!q.empty())
    {
        cout << q.top() << endl;
        q.pop();
    }

    // 小顶堆，输出顺序：1 2 3 4
}


int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    test7();

    return 0;
}