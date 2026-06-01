struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // pA 从链表 A 出发
        // pB 从链表 B 出发
        ListNode *pA = headA;
        ListNode *pB = headB;

        // 当两个指针不相等时，继续向后走
        // 如果有交点，最终会在交点相遇
        // 如果没有交点，最终会同时变成 nullptr
        while (pA != pB) {
            // pA 走到 A 的末尾后，切换到 B 的头节点
            if (pA == nullptr) {
                pA = headB;
            } else {
                pA = pA->next;
            }

            // pB 走到 B 的末尾后，切换到 A 的头节点
            if (pB == nullptr) {
                pB = headA;
            } else {
                pB = pB->next;
            }
        }

        // pA == pB
        // 可能是交点，也可能是 nullptr
        return pA;
    }
};