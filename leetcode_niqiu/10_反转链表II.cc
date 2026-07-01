struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 方法一: 头插法（一次遍历，原地反转）
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        // 1. 找到prev结点
        ListNode* prev = dummy;
        for (int i = 0; i < left - 1; i++) {
            prev = prev->next;
        }

        // 2. curr始终是反转区间的第一个节点(整个过程中它会不断向后退)
        ListNode* curr = prev->next;

        // 3. 穿针引线: 执行 right-left 次头插
        for (int i = 0; i < right - left; i++) {
            ListNode* next = curr->next; // 抓取curr后面的节点
            curr->next = next->next;     // curr越过next，指向更后面一个
            next->next = prev->next;     // next插到整个反转区间的头部
            prev->next = next;           // prev接上新的头部
        }

        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

// 方法二: 找到区间前驱、找到区间末尾、断开子链表、反转、重新拼接
class Solution2 {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // 创建虚拟头结点,指向head
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        // 1. 让prev指针从dummy开始,走left-1步,找到left的前驱结点
        ListNode* prevNode = dummy;
        for (int i = 0; i < left - 1; i++) {
            prevNode = prevNode->next;
        }

        // 2. 让rightNode从prevNode开始,走right-left+1 步,找到区间的最后一个结点
        ListNode* rightNode = prevNode;
        for (int j = 0; j < right - (left - 1); j++) {
            rightNode = rightNode->next;
        }

        // 3. 记录边界结点
        ListNode* leftNode = prevNode->next;
        ListNode* succNode = rightNode->next;

        // 4. 断开子链表
        prevNode->next = nullptr;
        rightNode->next = nullptr;

        // 5. 反转子链表
        reverseList(leftNode);

        // 6. 重新接回原链表
        // 反转后,原本的rightNode变成了新头部,leftNode变成了新尾部
        prevNode->next = rightNode;
        leftNode->next = succNode;

        // 7. 释放虚拟节点内存,返回真正的头节点
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }

    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};

// 方法三: 递归
// 可以把这个问题拆解为两个子问题：
// 如果 left == 1：说明问题变成了“反转链表的前 N 个节点”。
// 如果 left > 1：把 head 扔在一边，让 head->next 去重复这个过程，
// 同时 left 和 right 都减 1，直到触发情况 1。
class Solution3 {
private:
    ListNode* successor = nullptr; // 记录反转区间后面的那个节点

    // 辅助函数：反转链表的前 n 个节点，并返回新头节点
    ListNode* reverseN(ListNode* head, int n) {
        if (n == 1) {
            successor = head->next; // 找到第 n+1 个节点，先存起来
            return head;
        }
        // 递归反转前 n-1 个节点
        ListNode* last = reverseN(head->next, n - 1);

        head->next->next = head; // 翻转指针指向
        head->next = successor;  // 接上后面没反转的部分
        return last;
    }

public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // Base case: 如果 left == 1，直接变成反转前 right 个节点的问题
        if (left == 1) {
            return reverseN(head, right);
        }

        // 递归向前推进，直到 left 变成 1
        head->next = reverseBetween(head->next, left - 1, right - 1);
        return head;
    }
};
