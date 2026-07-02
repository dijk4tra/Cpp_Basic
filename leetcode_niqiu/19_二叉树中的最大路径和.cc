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
    int maxPathSum(TreeNode* root) {
        // 重置最大值（如果是多组测试数据，确保不被上次的结果干扰）
        maxSum = INT_MIN;

        // 开始递归遍历整棵树
        maxGain(root);

        // 最终返回记录下来的最大路径和
        return maxSum;
    }

private:
    // 全局/类成员变量，用来记录旅途中遇到的最大“折线”路径和
    // 初始化为 int 的最小值，防止树中全都是负数时发生错误
    int maxSum = INT_MIN;

    int maxGain(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        // 递归计算左、右子树能提供的最大“直线”贡献
        // 如果子树的贡献是负数，直接放弃该子树（即与 0 取 max）
        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);

        // 尝试在当前结点“拐弯”，算一算以当前结点为最高拐点的“折线”路径和
        int newPath = node->val + leftGain + rightGain;

        // 用 maxSum 记录、更新见过的最大“折线”
        maxSum = max(maxSum, newPath);

        // 核心：返回给父结点的，只能是包含当前结点的单边“直线”！
        return node->val + max(leftGain, rightGain);
    }
};
