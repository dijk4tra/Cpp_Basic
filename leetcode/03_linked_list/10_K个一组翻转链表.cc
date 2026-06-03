#include <stack>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 原地迭代法(需要画图理解并维护很多指针,容易犯迷糊)
// 时间复杂度O(n), 空间复杂度O(1)
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 虚拟头节点，方便处理头节点被翻转的情况
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        // prevGroupTail 表示当前要翻转这一组的前一个节点
        ListNode* prevGroupTail = dummy;

        while (true) {
            // 1. 找到当前组的尾节点
            ListNode* groupTail = prevGroupTail;
            for (int i = 0; i < k; i++) {
                groupTail = groupTail->next;
                // 不足 k 个节点，不需要翻转，直接返回
                if (groupTail == nullptr) {
                    return dummy->next;
                }
            }

            // 2. 保存下一组的头节点
            ListNode* nextGroupHead = groupTail->next;

            // 3. 保存当前组翻转前的头节点
            // 翻转后它会变成当前组的尾节点
            ListNode* groupHead = prevGroupTail->next;

            // 4. 翻转当前 k 个节点
            ListNode* prev = nextGroupHead;
            ListNode* curr = groupHead;

            while (curr != nextGroupHead) {
                ListNode* temp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = temp;
            }

            // 5. 把上一组接到当前翻转后的头节点
            prevGroupTail->next = groupTail;

            // 6. 更新 prevGroupTail，准备处理下一组
            prevGroupTail = groupHead;
        }

        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};


// 栈解法思路:
// 每次把 k 个节点压入栈中，再依次弹出
// 因为栈是后进先出，所以弹出来的顺序天然就是翻转后的顺序
// 时间复杂度O(n), 空间复杂度O(k)
class Solution1 {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 虚拟头节点，方便统一处理新链表头
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;  // tail 始终指向已经处理好的链表尾部

        ListNode* curr = head;

        while (curr != nullptr) {
            stack<ListNode*> st;
            ListNode* temp = curr;

            // 1. 尝试收集 k 个节点
            for (int i = 0; i < k; i++) {
                if (temp == nullptr) {
                    // 剩余节点不足 k 个，不翻转，直接接到结果后面
                    tail->next = curr;
                    return dummy->next;
                }
                st.push(temp);
                temp = temp->next;
            }

            // 2. 栈中有 k 个节点，弹出并接到结果链表
            while (!st.empty()) {
                tail->next = st.top();
                st.pop();
                tail = tail->next;
            }

            // 3. 更新 curr 到下一组的起始位置
            curr = temp;
        }

        // 4. 最后一定要断开尾部，避免形成环
        tail->next = nullptr;

        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};
