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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) {
            return result;
        }

        queue<TreeNode*> q;
        q.push(root);

        // 标记变量：true 表示从左往右，false 表示从右往左
        bool isOrderLeft = true;

        while (!q.empty()) {
            int levelSize = q.size();
            // 使用指定大小的 vector，方便后面通过索引直接填值
            vector<int> currentLevel(levelSize);

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();

                // 根据当前层的方向，决定填入数组的位置
                // 如果 isOrderLeft 为 true，正序填入（0, 1, 2...）
                // 如果 isOrderLeft 为 false，倒序填入（size-1, size-2...）
                int index = isOrderLeft ? i : (levelSize - 1 - i);
                currentLevel[index] = node->val;

                if (node->left != nullptr){
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            result.push_back(currentLevel);
            // 每遍历完一层，方向取反
            isOrderLeft = !isOrderLeft;
        }

        return result;
    }
};
