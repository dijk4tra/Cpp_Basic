#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

// 哈希表法
// 时间复杂度O(n), 空间复杂度O(n)
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        unordered_map<Node*, Node*> mp;

        // 第一步：复制所有节点，只复制 val
        Node* cur = head;
        while (cur != nullptr) {
            mp[cur] = new Node(cur->val);
            cur = cur->next;
        }

        // 第二步：复制 next 和 random 指针关系
        cur = head;
        while (cur != nullptr) {
            mp[cur]->next = cur->next ? mp[cur->next] : nullptr;
            mp[cur]->random = cur->random ? mp[cur->random] : nullptr;
            cur = cur->next;
        }

        return mp[head];
    }
};

// 原地交织法
// 时间复杂度O(n), 空间复杂度O(1)
// 第一步：复制节点，并插入原节点后面
// 第二步：设置复制节点的 random 指针
// 第三步：拆分两个链表
class Solution1 {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        // 第一步：在每个原节点后面插入复制节点
        // A -> B -> C -> nullptr
        // A -> a -> B -> b -> C -> c -> nullptr
        Node* cur = head;
        while (cur != nullptr) {
            Node* copy = new Node(cur->val);
            copy->next = cur->next;
            cur->next = copy;
            cur = copy->next;
        }

        // 第二步：设置复制节点的 random 指针
        cur = head;
        while (cur != nullptr) {
            Node* copy = cur->next;

            if (cur->random != nullptr) {
                copy->random = cur->random->next;
            } else {
                copy->random = nullptr;
            }

            cur = copy->next;
        }

        // 第三步：拆分原链表和复制链表
        cur = head;
        Node* newHead = head->next;

        while (cur != nullptr) {
            Node* copy = cur->next;

            cur->next = copy->next;

            if (cur->next != nullptr) {
                copy->next = cur->next->next;
            } else {
                copy->next = nullptr;
            }

            cur = cur->next;
        }

        return newHead;
    }
};
