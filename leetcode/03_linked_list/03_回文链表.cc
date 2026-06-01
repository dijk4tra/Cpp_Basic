#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// 链表法：使用快慢指针找到链表中点，反转后半部分链表，然后比较前半部分和反转后的后半部分
// 时间复杂度 O(n)，空间复杂度 O(1)
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // 1. 空链表或者只有一个节点，一定是回文
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        // 2. 使用快慢指针寻找链表中点
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            // 偶数长度时，fast 最后会走到 nullptr
            // 奇数长度时，fast 最后会走到最后一个节点
        }

        // 3. 如果 fast 不为空，说明链表长度是奇数
        //    此时 slow 指向中间节点，需要跳过中间节点
        if (fast != nullptr) {
            slow = slow->next;
        }

        // 4. 反转后半部分链表
        ListNode* secondHalf = reverseList(slow);

        // 5. 比较前半部分和反转后的后半部分
        ListNode* p1 = head;
        ListNode* p2 = secondHalf;
        while (p2 != nullptr) {
            if (p1->val != p2->val) {
                return false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        return true;

    }

private:
    // 反转链表
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (cur != nullptr) {
            ListNode* next = cur->next; // 暂存下一个节点
            cur->next = prev;           // 当前节点指向前一个节点
            prev = cur;                 // prev 后移
            cur = next;                 // cur 后移
        }
        return prev;
    }
};


// 数组法：先把链表的值放进数组，然后用双指针判断数组是否回文
// 时间复杂度 O(n)，空间复杂度 O(n)
class Solution2 {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> nums;

        // 1. 将链表中的值存储到数组中
        ListNode* cur = head;
        while (cur != nullptr) {
            nums.push_back(cur->val);
            cur = cur->next;
        }

        // 2. 双指针判断数组是否为回文
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            if (nums[left] != nums[right]) {
                return false;
            }
            left++;
            right--;
        }

        return true;
    }
};
