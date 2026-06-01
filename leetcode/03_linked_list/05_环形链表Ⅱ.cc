#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


// Floyd 判圈算法：
// 1. 使用两个指针 slow 和 fast，slow 每次移动一步，fast 每次移动两步，
//    若链表有环，则 slow 和 fast 一定会相遇。
// 2. 当 slow 和 fast 相遇时，设置新指针 ptr 指向链表头，slow 保持在相遇点，
//    然后 slow 和 ptr 同时移动，每次移动一步，再次相遇时即为环的入口。

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // 第一阶段：寻找相遇点
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                // 第二阶段：寻找环入口
                ListNode* ptr = head;

                while (ptr != slow)
                {
                    ptr = ptr->next;
                    slow = slow->next;
                }

                return ptr;
            }
        }

        return nullptr;
    }
};



// 哈希表法：
// 使用哈希表存储访问过的节点，遍历链表时，第一次出现重复节点时，该节点即为环的入口。
class Solution2 {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> visited;

        while (head != nullptr) {
            if (visited.count(head) > 0) {
                return head;
            }

            visited.insert(head);
            head = head->next;
        }

        return nullptr;
    }
};
