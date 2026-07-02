#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    TreeNode* first = nullptr;  // 记录第一个错误节点（值偏大的那个）
    TreeNode* second = nullptr; // 记录第二个错误节点（值偏小的那个）
    TreeNode* pred = nullptr;   // 记录中序遍历序列中的前驱节点（上一个访问的节点）

    void inorder(TreeNode* root) {
        if (!root) return;

        // 1. 递归遍历左子树
        inorder(root->left);

        // 2. 核心逻辑：检查当前节点与前驱节点的值是否满足递增关系
        if (pred && pred->val > root->val) {
            // 只要发现逆序，second 就要更新为当前较小的 root 节点
            // 情况一（相邻交换）：只会触发一次，second 正确指向较小值
            // 情况二（不相邻交换）：会触发两次，第二次遇到逆序时，second 会更新为后面那个更小的错误值
            second = root;

            // first 只在第一次遇到逆序时赋值，指向较大的那个错误值（即前驱 pred）
            if (!first) {
                first = pred;
            }
        }

        // 访问完当前节点后，当前节点变成下一个节点的前驱
        pred = root;

        // 3. 递归遍历右子树
        inorder(root->right);
    }

public:
    void recoverTree(TreeNode* root) {
        // 执行中序遍历，找出两个错误节点
        inorder(root);

        // 遍历结束后，如果找到了错误的节点，交换它们的值
        if (first && second) {
            std::swap(first->val, second->val);
        }
    }
};
