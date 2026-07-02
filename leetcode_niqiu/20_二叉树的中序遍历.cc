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
public:
    // 辅助递归函数
    void inorder(TreeNode* root, vector<int>& result) {
        // 递归终止条件：节点为空
        if (root == nullptr) {
            return;
        }
        inorder(root->left, result);  // 左：递归遍历左子树
        result.push_back(root->val);  // 根：将当前节点的值加入结果集
        inorder(root->right, result); // 右：递归遍历右子树
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorder(root, result);
        return result;
    }
};
