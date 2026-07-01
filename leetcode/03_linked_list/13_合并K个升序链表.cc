#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 方法一：优先队列 / 最小堆
class Solution {
public:

    // 为了让优先队列明白“应该怎么比”，我们需要传给它一个可调用对象（Callable Object）。
    // 在 C++ 中，最标准的做法就是定义一个结构体，并在里面重载 () 运算符。
    // 这种结构体被称为仿函数（Functor）。
    struct compare {
        // 为什么是 > 符号？
        // C++ 的 priority_queue 默认是大顶堆（把“最大”的放堆顶）。
        // 它的逻辑是：如果 compare(a, b) 返回 true，说明 a 的优先级比 b 低，a 就会被排到后面。
        // 当我们写 a->val > b->val 时，值越大的，返回 true，优先级越低，被压到堆底。
        // 结果就是：值越小的，反而留在了堆顶。这就是小顶堆。
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };


    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 定义优先队列(小顶堆)：
        // 参数 1: 存储的数据类型 (ListNode*)
        // 参数 2: 底层容器类型 (默认用 vector)
        // 参数 3: 比较规则 (我们自定义的 compare)
        priority_queue<ListNode*, vector<ListNode*>, compare> pq;

        // 1. 将所有链表的头节点（如果不为空）放入堆中
        for (ListNode* head : lists) {
            if (head != nullptr) {
                pq.push(head);
            }
        }

        // 2. 设立一个虚拟头节点（Dummy Node），方便连接结果
        ListNode dummy(0);
        ListNode* tail = &dummy;

        // 3. 不断从堆中取出最小节点
        while (!pq.empty()) {
            ListNode* minNode = pq.top();
            pq.pop();

            tail->next = minNode; // 接入结果链表
            tail = tail->next;    // 尾指针后移

            // 如果该节点后续还有节点，将下一个节点压入堆中
            if (minNode->next != nullptr) {
                pq.push(minNode->next);
            }
        }

        return dummy.next;
    }
};


// 方法二：分治法（Divide and Conquer）
class Solution2 {
public:
    // 辅助函数：合并两个升序链表
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = (l1 != nullptr) ? l1 : l2;
        return dummy.next;
    }

    // 分治核心递归函数：利用归并排序的思想，将范围 [start, end] 内的 K 个链表进行拆分和合并
    ListNode* mergeHelper(vector<ListNode*>& lists, int start, int end) {
        // 如果区间非法（比如 lists 本身为空时），返回空指针
        if (start > end) return nullptr;

        // 如果区间内只有一个链表，无需合并，直接返回它
        if (start == end) return lists[start];

        // 【分（Divide）】计算中点，将当前的大区间一分为二
        int mid = start + (end - start) / 2; // 防止 start + end 的数值过大导致整型溢出
        // 【治（Conquer）】递归处理左半部分，最终会合并成一个完整的有序链表
        ListNode* left = mergeHelper(lists, start, mid);
        /// 【治（Conquer）】递归处理右半部分，最终也会合并成一个完整的有序链表
        ListNode* right = mergeHelper(lists, mid + 1, end);

        // 【合（Combine）】将左边合并好的大链表和右边合并好的大链表，最后做一次两两合并
        return mergeTwoLists(left, right);
    }

    // 主入口函数
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 如果输入的 vector 长度为 0（即 lists = []），直接返回 nullptr
        if (lists.empty()) return nullptr;
        // 开启分治递归，初始区间为整个数组的范围：从索引 0 到 lists.size() - 1
        return mergeHelper(lists, 0, lists.size() - 1);
    }
};
