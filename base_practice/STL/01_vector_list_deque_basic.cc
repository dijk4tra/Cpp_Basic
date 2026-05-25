#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

/*
list 无法使用 []：如果你写了 lst[2]，编译器会直接报错。
想访问 list 的中间元素，必须用迭代器一个个 ++ 过去。

迭代器的加法限制：vec.begin() + 3 是合法的，因为 vector 内存连续，指针可以直接做加法。
但 lst.begin() + 3 是非法的，链表只能 it++。

头插与头删：deque 和 list 拥有 push_front 和 pop_front，而 vector 没有。
虽然 vector 可以通过 vec.insert(vec.begin(), val) 来实现头插，但效率极低。

*/


template <typename T>
void printContainer(const string& name, const T& container)
{
    cout << name << ": ";
    for (const auto& val : container)
    {
        cout << val << " ";
    }
    cout << endl;
}

int main()
{
    // ==========================================
    // 1. VECTOR 测试 (动态数组)
    // ==========================================
    cout << "--- Vector 测试 ---" << endl;
    vector<int> vec;

    // 增
    vec.push_back(10); // 尾插
    vec.push_back(20);
    vec.insert(vec.begin() + 1, 15); // 在第二个位置插入15
    printContainer("Vector 增", vec);

    // 改、查
    vec[1] = 99;
    cout << "Vector 修改后第二个元素: " << vec.at(1) << endl; // at() 会检查越界

    // 删
    vec.pop_back(); // 尾删
    vec.erase(vec.begin()); // 删掉第一个元素
    printContainer("Vector 删", vec); // 输出: 99

    // ==========================================
    // 2. DEQUE 测试 (双端队列)
    // ==========================================
    cout << "\n--- Deque 测试 ---" << endl;
    deque<int> deq;

    // 增
    deq.push_back(20); // 尾插
    deq.push_front(10); // 头插(Vector做不到!)
    deq.insert(deq.begin() + 1, 15); // 中间插入
    printContainer("Deque 增", deq); // 输出: 10 15 
    
    // 改、插
    deq[0] = 11; // 支持下标访问
    printContainer("Deque 改", deq); // 输出: 11 15 20

    // 删
    deq.pop_front(); // 头删 (Vector做不到！)
    deq.pop_back();  // 尾删
    printContainer("Deque 删", deq); // 输出: 15

    // ==========================================
    // 3. LIST 测试 (双向链表)
    // ==========================================
    cout << "\n--- List 测试 ---" << endl;
    list<int> lst;

    // 增
    lst.push_back(20);
    lst.push_front(10); // 支持头插
    // lst.insert(lst.begin() + 1, 15); // 报错！链表内存不连续，迭代器不支持 +1 操作
    auto it = lst.begin();
    it++; // 只能一步一步挪动（自增）
    lst.insert(it, 15); // 在第二个位置插入15
    printContainer("List 增", lst); // 输出: 10 15 20

    // 改、查
    // lst[0] = 5; // 报错！链表不支持下标访问
    lst.front() = 5; // 只能改头尾
    cout << "List 头部元素: " << lst.front() << endl;

    // 删
    lst.remove(15); // List 独有技能：直接按【值】删除所有匹配的元素
    printContainer("List 删", lst); // 输出: 5 20


    return 0;
}