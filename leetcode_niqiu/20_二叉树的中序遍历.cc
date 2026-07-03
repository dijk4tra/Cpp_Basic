#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <climits>
#include <stack>

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

// 方法一：递归法
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

// 方法二：迭代法（使用栈）
class Solution2 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* curr = root;

        while (curr != nullptr || !st.empty()) {
            if (curr != nullptr) {
                st.push(curr);     // 将当前结点压栈
                curr = curr->left; // 一路向左：对应“左”
            } else {
                // 当前节点为空，说明左边走到头了，弹出栈顶元素
                curr = st.top();
                st.pop();
                result.push_back(curr->val); // 访问节点：对应“根”
                curr = curr->right;          // 转向右子树：对应“右”
            }
        }
        return result;
    }
};

// 方法三: Morris 遍历（Morris Traversal）
// 在常规的遍历中，不管是递归还是栈，都需要O(n)或O(log n)的空间来记录“回溯”的路径。
// Morris 遍历的核心思想是：利用叶子节点中空闲的右孩子指针（right = nullptr），
// 指向遍历过程中的某个祖先节点，从而实现不用栈也能“回溯”的效果。
// 中序遍历的顺序是“左-根-右”，所以对于任何一个当前节点 cur：
// 它的前驱节点（也就是在它前面被访问的最后一个节点）一定是它左子树中最右边的节点。
class Solution3 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        TreeNode* curr = root;
        TreeNode* prev = nullptr;

        while (curr != nullptr) {
            if (curr->left == nullptr) {
                // 情况 1: 左孩子为空,直接访问,然后去右子树
                result.push_back(curr->val);
                curr = curr->right;
            } else {
                // 情况 2: 左孩子不为空,向左子树的右下找前驱结点
                prev = curr->left;
                while (prev->right != nullptr && prev->right != curr) {
                    // 必须加入判断 prev->right != curr, 否则会造成死循环
                    prev = prev->right;
                }

                if (prev->right == nullptr) {
                    // 2a. 第一次到底前驱结点,建立线索
                    prev->right = curr;
                    curr = curr->left; // 已建立线索,继续向左走
                } else {
                    // 2b. 第二次到达前驱结点,说明左子树已经遍历完毕
                    prev->right = nullptr; // 断开线索,恢复原树结构
                    result.push_back(curr->val); // 访问根结点
                    curr = curr->right; // 转向右子树
                }
            }
        }

        return result;
    }
};
