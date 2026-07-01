#include <algorithm>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        // 空链表或只有一个节点，天然有序
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // 1. 使用快慢指针找到链表中点
        ListNode* slow = head;
        ListNode* fast = head->next; // 注意：fast 从 head->next 开始可以方便断开
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2. 从中间断开链表
        ListNode* mid = slow->next; // mid 是右半部分的头节点
        slow->next = nullptr; // 断开链表，分成两段

        // 3. 递归归并左右两部分
        ListNode* left = sortList(head);
        ListNode* right = sortList(mid);

        // 4. 合并两个有序链表
        return merge(left, right);
    }

private:
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0); // 哨兵节点，简化边界处理
        ListNode* tail = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        // 将剩余部分连接上
        tail->next = l1 ? l1 : l2;

        return dummy.next;
    }
};
