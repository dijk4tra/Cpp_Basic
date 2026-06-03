struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 1. 创建一个虚拟头节点，方便串联结果
        ListNode* dummyHead = new ListNode(0);
        ListNode* curr = dummyHead; // curr 用来指向当前正要构建的节点的前驱

        int carry = 0; // 初始化进位为 0

        // 2. 只要 l1 不为空，或者 l2 不为空，或者还有进位没处理完，就继续循环
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            // 如果链表遍历完了，对应位置的值就取 0
            int val1 = (l1 != nullptr) ? l1->val : 0;
            int val2 = (l2 != nullptr) ? l2->val : 0;

            // 计算当前位的总和
            int sum = val1 + val2 + carry;

            // 更新进位
            carry = sum / 10;

            // 创建新节点存储当前位的结果（sum % 10），并挂在 curr 后面
            curr->next = new ListNode(sum % 10);
            curr = curr->next; // curr 指针向后移动

            // 两个输入链表指针分别后移
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }

        // 3. 记录真正的头节点，释放虚拟头节点内存，防止内存泄漏
        ListNode* result = dummyHead->next;
        delete dummyHead;

        return result;
    }
};


// 原创代码(会溢出!)
// 溢出原因: 链表可能很长, 转成 int / long long 都可能装不下
// 链表 l1 -> 整数 num1
// 链表 l2 -> 整数 num2
// sum = num1 + num2
// sum -> 链表 result
class Solution1 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int num1 = 0;
        int num2 = 0;
        int ten_count_1 = 1;
        int ten_count_2 = 1;

        while(l1 != nullptr) {
            num1 += l1->val * ten_count_1;
            ten_count_1 *= 10;
            l1 = l1->next;
        }

        while(l2 != nullptr) {
            num2 += l2->val * ten_count_2;
            ten_count_2 *= 10;
            l2 = l2->next;
        }

        int sum = num1 + num2;

        ListNode* result = new ListNode(sum % 10);
        ListNode* current = result;
        sum /= 10;
        while (sum > 0) {
            current->next = new ListNode(sum % 10);
            current = current->next;
            sum /= 10;
        }

        return result;
    }
};

// 既然不能整体转成数字，那就把“整数加法”改成逐位加法
// 优化后的思路:
// 当前位 = l1 当前值 + l2 当前值 + carry
// 结果节点 = 当前位 % 10
// 进位 carry = 当前位 / 10
class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 创建一个虚拟头节点 dummyHead
        // 作用：方便统一处理结果链表的头节点，避免单独判断第一个节点
        ListNode* dummyHead = new ListNode(0);

        // current 指针用于构建结果链表
        // 它始终指向结果链表当前的最后一个节点
        ListNode* current = dummyHead;

        // carry 表示进位
        // 例如 8+7=15, 那么当前位是5, 进位是1
        int carry = 0;

        // 只要 l1 没遍历完, 或者 l2 没遍历完, 或者还有进位, 就继续循环
        while (l1 != nullptr || l2 != nullptr || carry > 0) {
            // 如果 l1 当前节点不为空，就取出它的值
            // 如果 l1 已经遍历完了，就用 0 代替
            int val1 = (l1 != nullptr) ? l1->val : 0;

            // 如果 l2 当前节点不为空，就取出它的值
            // 如果 l2 已经遍历完了，就用 0 代替
            int val2 = (l2 != nullptr) ? l2->val : 0;

            // 当前位相加：
            // l1 当前位 + l2 当前位 + 上一轮产生的进位
            int sum = val1 + val2 + carry;

            // 计算新的进位
            // 如果 sum >= 10，carry 就是 1；否则是 0
            carry = sum / 10;

            // sum % 10 是当前位真正要存入结果链表的值
            // 例如 sum = 15，当前节点存 5，进位 carry = 1
            current->next = new ListNode(sum % 10);

            // current 向后移动，指向刚刚新创建的节点
            current = current->next;

            // 如果 l1 还没遍历完，就移动到下一个节点
            if (l1 != nullptr) {
                l1 = l1->next;
            }

            // 如果 l2 还没遍历完，就移动到下一个节点
            if (l2 != nullptr) {
                l2 = l2->next;
            }
        }

        // 真正的结果链表从 dummyHead->next 开始
        ListNode* result = dummyHead->next;
        delete dummyHead; // 释放虚拟头节点，避免内存泄漏

        // 返回结果链表的头节点
        return result;
    }
};
