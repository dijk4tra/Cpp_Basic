#include <iostream>
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


// 快慢指针法：使用快慢指针遍历链表，如果存在环，则快慢指针一定会相遇。
// 时间复杂度 O(n)，空间复杂度 O(1)
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
};



// 哈希表法：使用哈希表存储访问过的节点，遍历链表时，如果节点已经在哈希表中，则说明存在环。
// 时间复杂度 O(n)，空间复杂度 O(n)
class Solution2 {
public:
    bool hasCycle(ListNode *head) {
        unordered_multiset<ListNode*> visited;

        while (head != nullptr) {
            if (visited.count(head)) {
                return true;
            }

            visited.insert(head);
            head = head->next;
        }

        return false;
    }
};
