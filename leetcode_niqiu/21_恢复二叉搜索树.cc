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

// 方法一: 递归版中序遍历
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

// 方法二: Morris 中序遍历
class Solution2 {
public:
    void recoverTree(TreeNode* root) {
        TreeNode* first = nullptr;  // 第一个错误节点
        TreeNode* second = nullptr; // 第二个错误节点
        TreeNode* pred = nullptr;   // 中序遍历的前驱节点
        TreeNode* curr = root;      // 当前正在处理的节点

        while (curr != nullptr) {
            if (curr->left == nullptr) {
                // ----------- 情况 A：左子树为空，直接访问当前节点 -----------

                // 检查是否破坏了二叉搜索树的递增性质
                if (pred != nullptr && pred->val > curr->val) {
                    second = curr; // 每次遇到逆序都更新 second
                    if (first == nullptr) {
                        first = pred; // 第一次遇到逆序时确定 first 为较大值
                    }
                }

                // 更新前驱节点，并准备通过“线索”或右孩子走向下一个节点
                pred = curr;
                curr = curr->right;
            } else {
                // ----------- 情况 B：左子树不为空，寻找左子树的最右节点 -----------
                // leftTreeRightmost 是 curr 左子树中序遍历的最后一个节点（即当前节点的前驱）
                TreeNode* leftTreeRightmost = curr->left;
                while (leftTreeRightmost->right != nullptr && leftTreeRightmost->right != curr) {
                    leftTreeRightmost = leftTreeRightmost->right;
                }

                if (leftTreeRightmost->right == nullptr) {
                    // 情况 B1：最右节点的右指针为空，说明是第一次访问
                    // 建立临时“线索”连接，让它指向当前节点 curr，以便后续能返回
                    leftTreeRightmost->right = curr;
                    curr = curr->left;
                } else {
                    // 情况 B2：最右节点的右指针已经指向了 curr，说明左子树已经全部遍历完
                    // 此时已经“顺着线索”第二次回到了 curr，需要恢复树的原始结构，断开连接
                    leftTreeRightmost->right = nullptr;

                    // 此时等同于完成了左子树的访问，正式开始“访问”当前节点 curr
                    if (pred != nullptr && pred->val > curr->val) {
                        second = curr;
                        if (first == nullptr) first = pred;
                    }

                    // 访问完 curr 后，更新前驱，并进入右子树
                    pred = curr;
                    curr = curr->right;
                }
            }
        }

        // ----------- 阶段 C：遍历结束，交换错误节点的值 -----------
        if (first && second) {
            std::swap(first->val, second->val);
        }
    }
};
