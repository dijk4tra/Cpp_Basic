#include <algorithm>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 将两个升序链表合并为一个新的升序链表并返回。
// 新链表是通过拼接给定的两个链表的所有节点组成的。

// 迭代法
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // 1. 创建哨兵节点，省去处理头节点为空的麻烦
        ListNode* dummy = new ListNode(-1);
        ListNode* cur = dummy;

        // 2. 遍历两个链表，将较小的节点连接到新链表的末尾
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                cur->next = list1;
                list1 = list1->next;
            } else {
                cur->next = list2;
                list2 = list2->next;
            }
            cur = cur->next; // 更新新链表的指针
        }

        // 3. 将未合并完的链表的剩余节点直接接到新链表的尾部
        cur->next = (list1 != nullptr) ? list1 : list2;

        // 4. 返回新链表的头节点并释放dummy节点的内存
        ListNode* result = dummy->next;
        delete dummy;

        return result;
    }
};


// 递归法
// 合并两个链表的问题可以拆解为：找出当前较小的节点，然后让它的 next 指向“剩余两个链表合并后的结果”
class Solution2 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        if (list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoLists(list2->next, list1);
            return list2;
        }
    }
};
