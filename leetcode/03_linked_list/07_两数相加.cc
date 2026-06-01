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


// 原创代码
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
