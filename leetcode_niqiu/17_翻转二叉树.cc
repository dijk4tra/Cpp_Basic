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
    // 翻转以 root 为根节点的二叉树，并返回翻转后的根节点
    TreeNode* invertTree(TreeNode* root) {
        //【终止条件】如果当前节点为空，说明已经越过叶子节点，无需翻转，直接返回空指针
        if (root == nullptr) {
            return nullptr;
        }

        // 分别递归地翻转当前节点的左子树和右子树
        TreeNode* invertedLeft = invertTree(root->left);
        TreeNode* invertedRight = invertTree(root->right);

        root->left = invertedRight;
        root->right = invertedLeft;
        // 或者直接交换当前节点的左右指针，
        // 就不需要invertedLeft和invertedRight两个辅助变量
        // std::swap(root->left, root->right);

        return root;
    }
};
