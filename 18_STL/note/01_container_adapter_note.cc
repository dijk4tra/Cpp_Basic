#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <queue>

using namespace std;

/**
 * 容器适配器 container adapter：
 *
 * 容器适配器不是一种新的底层数据结构，
 * 而是在已有容器的基础上，
 * 对外提供一种受限制的接口。
 *
 * 可以理解成：
 * 它把某些容器“包装”起来，
 * 只暴露符合特定数据结构语义的操作。
 *
 * STL 中常见的容器适配器：
 * 1. stack
 *    栈，后进先出 LIFO。
 *    只能在栈顶进行插入、删除、访问。
 *
 * 2. queue
 *    队列，先进先出 FIFO。
 *    从队尾插入元素，从队头删除元素。
 *
 * 3. priority_queue
 *    优先级队列。
 *    每次访问的都是优先级最高的元素。
 *    默认情况下，数值越大优先级越高。
 *
 *
 * 注意：
 * 容器适配器本身不直接存储数据，
 * 它的内部需要依赖一个底层容器。
 *
 * 例如：
 * stack<int> s;
 * 默认底层容器是 deque<int>。
 *
 * stack<int, vector<int>> s;
 * 表示 stack 的底层容器改为 vector<int>。
 *
 *
 * 适配器对底层容器有要求：
 * 1. stack
 *    底层容器需要支持：
 *    back()
 *    push_back()
 *    pop_back()
 *
 * 2. queue
 *    底层容器需要支持：
 *    front()
 *    back()
 *    push_back()
 *    pop_front()
 *
 * 3. priority_queue
 *    底层容器需要支持随机访问迭代器，
 *    因为它内部通常通过堆 heap 来维护优先级。
 */


// stack
void test1()
{
    /**
     * stack 栈：
     *
     * 特点：
     * 后进先出 Last In First Out，简称 LIFO。
     *
     * 例如依次入栈：
     * 1 2 3 4
     *
     * 出栈顺序是：
     * 4 3 2 1
     *
     *
     * stack<int> s;
     * 表示创建一个存放 int 类型数据的栈。
     *
     * 默认情况下：
     * stack 的底层容器是 deque。
     *
     * deque 是双端队列，
     * 支持在头部和尾部高效插入、删除元素。
     */
    stack<int> s;

    /**
     * push：
     * 向栈顶插入元素。
     *
     * 下面依次把 1、2、3、4 压入栈中。
     * 其中 4 是最后入栈的元素，
     * 所以 4 位于栈顶。
     */
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    /**
     * top：
     * 访问栈顶元素。
     *
     * 注意：
     * top 只是获取栈顶元素，
     * 不会删除元素。
     */
    // cout << s.top() << endl;

    /**
     * pop：
     * 删除栈顶元素。
     *
     * 注意：
     * pop 只删除元素，
     * 不会返回被删除的元素。
     *
     * 如果想在删除之前看到元素，
     * 需要先 top，
     * 再 pop。
     */
    // s.pop();
    // cout << s.top() << endl;
    
    /**
     * 遍历栈中的所有元素：
     *
     * stack 没有提供迭代器，
     * 不能像 vector / list 那样使用迭代器遍历。
     *
     * 所以通常使用：
     * while(!s.empty())
     * {
     *     访问栈顶元素；
     *     弹出栈顶元素；
     * }
     *
     * 注意：
     * 这种遍历方式会不断 pop 元素，
     * 遍历结束后，栈会变成空栈。
     */
    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }

    cout << "------" << endl;

    /**
     * 注意：
     * 当栈为空时，不能再调用 top。
     *
     * 对空栈调用 top，
     * 行为是未定义的。
     *
     * 所以在调用 top / pop 之前，
     * 最好先判断 empty。
     */
    // cout << s.top() << endl;
}


// stack
void test2()
{
    /**
     * stack 可以修改底层容器。
     *
     * stack<int, vector<int>> s;
     *
     * 第一个模板参数 int：
     * 表示栈中存放的数据类型。
     *
     * 第二个模板参数 vector<int>：
     * 表示底层容器使用 vector<int>。
     *
     *
     * 为什么 vector 可以作为 stack 的底层容器？
     * 因为 vector 支持：
     * back()
     * push_back()
     * pop_back()
     *
     * 这些操作正好可以满足 stack 的需求。
     */
    stack<int, vector<int>> s;

    // 向栈顶依次压入元素
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    /**
     * 依次访问栈顶元素并弹出。
     *
     * 入栈顺序：
     * 1 2 3 4
     *
     * 出栈顺序：
     * 4 3 2 1
     *
     * 遍历结束后，栈为空。
     */
    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
}


// stack
void test3()
{
    /**
     * stack 的底层容器也可以使用 list。
     *
     * list 是双向链表，
     * 它也支持：
     * back()
     * push_back()
     * pop_back()
     *
     * 所以 list 可以作为 stack 的底层容器。
     */
    stack<int, list<int>> s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    
    // 和前面一样，使用 top + pop 的方式遍历栈
    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
}


// queue
void test4()
{
    /**
     * queue 队列：
     *
     * 特点：
     * 先进先出 First In First Out，简称 FIFO。
     *
     * 例如依次入队：
     * 1 2 3 4
     *
     * 出队顺序是：
     * 1 2 3 4
     *
     *
     * queue<int> q;
     * 表示创建一个存放 int 类型数据的队列。
     *
     * 默认情况下：
     * queue 的底层容器是 deque。
     */
    queue<int> q;

    /**
     * push：
     * 向队尾插入元素。
     *
     * 下面依次把 1、2、3、4 入队。
     */
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);

    /**
     * front：
     * 访问队头元素。
     *
     * pop：
     * 删除队头元素。
     *
     * 注意：
     * queue 也没有提供迭代器，
     * 所以通常通过 front + pop 的方式遍历。
     *
     * 遍历结束后，队列为空。
     */
    while(!q.empty())
    {
        cout << q.front() << endl;
        q.pop();
    }
}


// queue
void test5()
{
    /**
     * queue 对底层容器的要求：
     *
     * queue 是先进先出，
     * 所以它需要：
     * 1. 在队尾插入元素
     *    push_back()
     *
     * 2. 从队头删除元素
     *    pop_front()
     *
     * 3. 访问队头元素
     *    front()
     *
     * 4. 访问队尾元素
     *    back()
     *
     *
     * vector 不支持 pop_front，
     * 所以 vector 不能作为 queue 的底层容器。
     */
    // queue<int, vector<int>> q; // error

    /**
     * list 支持：
     * front()
     * back()
     * push_back()
     * pop_front()
     *
     * 所以 list 可以作为 queue 的底层容器。
     */
    queue<int, list<int>> q;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    // 入队顺序：1 2 3 4

    /**
     * 队列是先进先出，
     * 所以输出顺序也是：
     * 1 2 3 4
     */
    while (!q.empty())
    {
        cout << q.front() << endl;
        q.pop();
    }
}


// priority_queue
void test6()
{
    /**
     * priority_queue 优先级队列：
     *
     * 特点：
     * 每次访问的都是优先级最高的元素。
     *
     * 默认情况下：
     * priority_queue 是大顶堆。
     *
     * 对 int 来说：
     * 数值越大，优先级越高。
     *
     * 所以：
     * q.top()
     * 每次拿到的都是当前队列中最大的元素。
     *
     *
     * priority_queue<int> q;
     *
     * 第一个模板参数 int：
     * 表示优先级队列中存放 int 类型数据。
     *
     * 默认底层容器：
     * vector<int>
     *
     * 默认比较规则：
     * less<int>
     *
     * less<int> 会形成大顶堆，
     * 即最大值优先出队。
     */
    priority_queue<int> q;

    /**
     * push：
     * 向优先级队列中插入元素。
     *
     * 注意：
     * priority_queue 不保证元素按照插入顺序排列。
     * 它会根据优先级自动调整内部结构。
     */
    q.push(2);
    q.push(1);
    q.push(4);
    q.push(3);
    // 插入顺序：2 1 4 3
    
    /**
     * top：
     * 访问当前优先级最高的元素。
     *
     * pop：
     * 删除当前优先级最高的元素。
     *
     * 因为默认是大顶堆，
     * 所以输出顺序是从大到小：
     * 4 3 2 1
     */
    while(!q.empty())
    {
        cout << q.top() << endl;
        q.pop();
    }
    // 输出顺序：4 3 2 1
}


// priority_queue
void test7()
{
    /**
     * priority_queue 的完整模板形式：
     *
     * priority_queue<T, Container, Compare>
     *
     * T：
     * 元素类型。
     *
     * Container：
     * 底层容器类型。
     *
     * Compare：
     * 比较规则。
     *
     *
     * priority_queue<int, deque<int>, std::greater<int>> q;
     *
     * 表示：
     * 1. 元素类型是 int
     * 2. 底层容器使用 deque<int>
     * 3. 比较规则使用 greater<int>
     *
     *
     * greater<int> 会形成小顶堆，
     * 即最小值优先出队。
     *
     * 所以输出顺序是：
     * 1 2 3 4
     */
    priority_queue<int, deque<int>, std::greater<int>> q;

    /**
     * 注意：
     * priority_queue 的底层容器不能使用 list。
     *
     * 虽然 list 也有一些插入、删除相关的函数，
     * 但是 priority_queue 内部需要使用堆算法。
     *
     * 堆算法要求底层容器支持随机访问迭代器。
     *
     * vector 和 deque 支持随机访问迭代器，
     * list 只支持双向迭代器，
     * 所以 list 不能作为 priority_queue 的底层容器。
     */
    q.push(2);
    q.push(1);
    q.push(4);
    q.push(3);
    // 插入顺序：2 1 4 3

    // 每次输出当前最小的元素
    while(!q.empty())
    {
        cout << q.top() << endl;
        q.pop();
    }
    // 输出顺序：1 2 3 4
}


int main()
{
    /**
     * 依次打开不同的测试函数，
     * 可以观察不同容器适配器的行为。
     *
     * test1：
     * stack 默认底层容器 deque。
     *
     * test2：
     * stack 底层容器改为 vector。
     *
     * test3：
     * stack 底层容器改为 list。
     *
     * test4：
     * queue 默认底层容器 deque。
     *
     * test5：
     * queue 底层容器不能使用 vector，
     * 可以使用 list。
     *
     * test6：
     * priority_queue 默认大顶堆。
     *
     * test7：
     * priority_queue 使用 greater<int>，
     * 变成小顶堆。
     */
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    test7();

    return 0;
}