#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;
/*
Vector（动态数组）—— “扩容狂魔”
底层结构：一块连续的内存空间（和 C 语言的普通数组一样，但它能自动变大）。
核心特点：
随机访问极快：支持用下标 vec[i] 直接访问任意元素，时间复杂度是 O(1)。
尾部操作高效：在末尾追加（push_back）或删除元素很快。
中间/头部操作很慢：如果在开头或中间插入/删除元素，需要把后面所有的元素都挨个往前或往后挪动，非常费劲（O(N)）。
扩容代价大：当现有的格子装满时，它会去内存的其他地方开辟一块大约原来 1.5 倍或 2 倍大的新空间，把老数据全部复制过去，再释放老空间。

List（双向链表）—— “指针专家”
底层结构：由一个个独立的“节点”串联起来的双向链表。每个节点除了存数据，还拉着前一个节点和后一个节点的“手”（指针）。它的内存空间是散落不连续的。
核心特点：
无法随机访问：不能用下标取值。想找第 5 个元素？对不起，必须从头节点开始顺着指针数过去（O(N)）。
任何位置插入/删除都极快：只要你知道位置，把前后节点的指针重新指向一下就完成了（O(1)），不需要搬移任何数据。
没有扩容焦虑：要存新数据就临时申请一个节点的内存，不用像 vector 那样整体搬家。

Deque（双端队列）—— “拼接大师”
底层结构：一种分段连续的结构（分段连续数组）。它有一个“中央控制板”（Map），里面存放着一堆指针，每个指针指向一块固定大小的连续内存块（Buffer）。
核心特点：
两端开弓：在头部（push_front）和尾部（push_back）插入或删除元素都非常快，都是 O(1)。
支持随机访问：虽然不如 vector 那么纯粹，但也能通过下标访问，只不过内部需要通过中控板做一次指针跳转。
中间操作依然慢：在中间插入删除，同样需要移动元素。

核心特性速查表
容器,底层结构,随机访问 [i],头部插入/删除,尾部插入/删除,中间插入/删除
vector,连续数组,极快 (O(1)),很慢 (O(N)),极快 (O(1)),很慢 (O(N))
list,双向链表,很慢 (O(N)),极快 (O(1)),极快 (O(1)),极快 (O(1))
deque,分段连续数组,较快 (O(1)),极快 (O(1)),极快 (O(1)),很慢 (O(N))
*/

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