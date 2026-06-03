
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* cur = dummyHead;
        while (cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* temp = cur->next;
            cur->next = cur->next->next;
            temp->next = temp->next->next;
            cur->next->next = temp;
            cur = temp;
            temp = temp->next;
        }
        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }
};
