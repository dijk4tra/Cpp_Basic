#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

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
public:
    // 计算以 root 为根节点的二叉树的最大深度
    int maxDepth(TreeNode* root) {
        //【终止条件】如果当前节点为空，说明已经越过了叶子节点，空树的深度为 0
        if (root == nullptr) return 0;

        // 1. maxDepth(root->left)  => 递归计算左子树的最大深度
        // 2. maxDepth(root->right) => 递归计算右子树的最大深度
        // 3. max(left_depth, right_depth) => 比较左右子树的深度，取其中的较大值
        // 4. + 1 => 加上当前节点 root 自身所占的那一层深度，并向上层返回结果
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
