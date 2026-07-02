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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        // 1. 边界条件判断
        if (root == nullptr) {
            return result;
        }

        // 2. 创建队列并将根节点入队
        queue<TreeNode*> q;
        q.push(root);

        // 3. 只要队列不为空，就继续遍历
        while (!q.empty()) {
            // 获取当前层的节点数量
            int levelSize = q.size();
            vector<int> currentLevel;

            // 4. 严格遍历当前层的所有节点
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();

                // 记录当前节点的值
                currentLevel.push_back(node->val);

                // 将下一层的节点（左、右子节点）加入队列尾部
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            result.push_back(currentLevel);
        }

        // 5. 将当前层的结果存入最终结果中
        return result;
    }
};
