struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// 迭代法
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // prev 指向已经反转好的链表头
        // 一开始还没有反转任何节点，所以是 nullptr
        ListNode* prev = nullptr;

        // cur 指向当前正在处理的节点
        ListNode* cur = head;

        while (cur != nullptr) {
            // 先保存当前节点的下一个节点
            // 否则反转 cur->next 后，后面的链表会丢失
            ListNode* next = cur->next;

            // 反转当前节点的 next 指针
            cur->next = prev;

            // prev 和 cur 同时向后移动
            prev = cur;
            cur = next;
        }

        // cur 为空时，prev 正好指向反转后的新头节点
        return prev;
    }
};

// 递归法
class Solution2 {
public:
    ListNode* reverseList(ListNode* head) {
        // 空链表或只有一个节点时，直接返回
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // 递归反转 head 后面的链表
        // newHead 是反转后的新头节点
        ListNode* newHead = reverseList(head->next);

        // 此时 head->next 是原链表中 head 的下一个节点
        // 让这个节点反过来指向 head
        head->next->next = head;

        // head 变成尾节点，所以它的 next 要置空
        head->next = nullptr;

        // 返回新的头节点
        return newHead;
    }
};