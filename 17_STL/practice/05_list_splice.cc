#include <iostream>
#include <list>
#include <algorithm> // 引入 std::find 用于查找元素

using namespace std;

class LRUCache
{
private:
    list<int> lst;  // 容器：双向链表，头部表示最近使用，尾部表示最久未使用
    size_t cap = 3; // 容量为3

public:
    void refer(int page)
    {
        // 在链表中查找该页面是否已经存在
        auto it = find(lst.begin(), lst.end(), page);

        // 情况一：页面已在缓存中(缓存命中)
        if (it != lst.end())
        {
            // 使用 splice 将该节点直接移动到链表头部
            // 参数含义：(移动到的目标位置, 源链表, 要移动的元素的迭代器)
            lst.splice(lst.begin(), lst, it);
        }
        else // 情况二：页面不在缓存中(缓存缺失)
        {
            // 如果缓存已满，需要淘汰最久未使用的页面（即链表尾部的页面）
            if (lst.size() == cap)
            {
                lst.pop_back(); // 移除尾部元素
            }
            // 将新页面插入到链表头部
            lst.push_front(page);
        }
        // 每次操作后，打印当前的缓存状态
        print();
    }

    // 辅助函数：用于输出每一步之后的链表内容(从头到尾)
    void print()
    {
        for (int x : lst)
        {
            cout << x << " ";
        }
        cout << endl;
    }
};


int main()
{
    LRUCache cache;

    cache.refer(1); // 期望输出: 1
    cache.refer(2); // 期望输出: 2 1
    cache.refer(3); // 期望输出: 3 2 1
    cache.refer(2); // 期望输出: 2 3 1 （2被移动到头部）
    cache.refer(4); // 期望输出: 4 2 3 （1被淘汰，4插入头部）
    cache.refer(1); // 期望输出: 1 4 2 （3被淘汰，1插入头部）

    return 0;
}

