#include <stack>
#include <utility>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 方法一: 用栈(Stack)来实现 K 个一组翻转链表
// 注意: 最后要 tail->next = nullptr; 避免形成环
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 虚拟头节点,方便统一处理新链表头
        ListNode* dummy = new ListNode(0);
        // tail 始终指向已经处理好的链表尾部
        ListNode* tail = dummy;
        ListNode* curr = head;

        while (curr != nullptr) {
            stack<ListNode*> st;
            ListNode* temp = curr;

            // 1. 尝试收集k个结点
            for (int i = 0; i < k; i++) {
                if (temp == nullptr) {
                    // 剩余结点不足k个,不翻转,直接接到结果后面
                    tail->next = curr;
                    return dummy->next;
                }
                st.push(temp);
                temp = temp->next;
            }

            // 2. 栈中有k个节点,弹出并接到结果链表
            while (!st.empty()) {
                tail->next = st.top();
                st.pop();
                tail = tail->next;
            }

            // 3. 更新curr到下一组的起始位置
            curr = temp;
        }

        // 4. 最后一定要断开尾部,避免形成环
        // dummy -> 2 -> 1 -> 4 -> 3
        //                    ↑    │
        //                    └────┘ (无限循环)
        tail->next = nullptr;

        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

// 方法二: 迭代法
// 1. 检查剩余节点是否足够：每次从当前位置向后数 k 个节点。
//    如果不足 k 个，说明已经是最后一组且数量不够，直接保持原样返回。
// 2. 记录边界：找到这 k 个节点的起始节点（head）和末尾节点（tail），
//    同时记录下这组节点的前驱节点（pre）和后继节点（nex）。
// 3. 翻转局部的 k 个节点：将这 k 个节点独立出来进行翻转。
// 4. 重新拼接链表：把翻转后的局部链表接回原链表中。
//    具体来说，让 pre 指向翻转后的新头部，让翻转后的新尾部指向 nex。
class Solution2 {
public:
    // 辅助函数：翻转一个局部链表，并返回新链表的 [head, tail]
    std::pair<ListNode*, ListNode*> reverseList(ListNode* head, ListNode* tail) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* terminal = tail->next; // 记录翻转区间的下一个节点，作为终止边界

        while (curr != terminal) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        // 翻转后，原来的 tail 变成了新头部，原来的 head 变成了新尾部
        return {tail, head};
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        // 如果链表为空，或者 k 为 1，无需翻转直接返回
        if (!head || k == 1) return head;

        // 引入虚拟头节点，方便统一处理
        ListNode* dummy = new ListNode(0, head);
        ListNode* prev = dummy; // prev 始终指向当前待翻转组的前驱节点

        while (head) {
            ListNode* tail = prev;

            // 1. 检查剩余部分的节点数量是否大于等于 k
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail) {
                    // 数量不足 k 个，说明是最后一组，保持原样直接返回
                    ListNode* res = dummy->next;
                    delete dummy;
                    return res;
                }
            }

            // 记录下一组的起始节点（后继节点）
            ListNode* next = tail->next;

            // 2. 翻转当前这 k 个节点组成的局部链表
            auto result = reverseList(head, tail);
            head = result.first;  // 翻转后的新头部
            tail = result.second; // 翻转后的新尾部

            // 3. 将翻转后的局部链表重新拼接回原链表
            prev->next = head; // 前驱节点指向新头部
            tail->next = next; // 新尾部指向后继节点

            // 4. 为下一轮循环更新指针位置
            prev = tail; // 当前的尾部变成下一组的前驱
            head = next;  // 下一组的起点作为下一轮的 head
        }

        // 释放虚拟头节点内存，返回最终结果
        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }
};
