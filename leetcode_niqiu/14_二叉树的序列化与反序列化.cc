#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;

// LeetCode 默认的二叉树节点定义
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

    // 序列化函数：把二叉树序列化为一个字符串(BFS)
    string serialize(TreeNode* root) {
        // 如果是空树，直接返回空字符串
        if (!root) return "";

        string res = "";    // 用于拼接最终结果的字符串
        queue<TreeNode*> q; // BFS 核心数据结构：队列
        q.push(root);       // 根结点首先入队

        while (!q.empty()) {
            TreeNode* curr = q.front(); // 取出队头结点
            q.pop();                    // 将队头弹出

            // 如果当前结点为空，说明走到了“叶子节点的空分支”
            if (curr == nullptr) {
                // 用 "null" 记录这个空位置，并用逗号分隔
                res += "null,";
            }
            // 如果当前结点不为空
            else {
                // to_string 将整数转化为字符串，拼接后加逗号分隔
                res += to_string(curr->val) + ",";

                // 【关键点】不管左右孩子是否为空，一律放入队列
                // 这样才能在下一次循环中，把它们的空状态（nullptr）也记录到字符串里
                q.push(curr->left);
                q.push(curr->right);
            }
        }

        // 循环结束后，字符串末尾会多出一个逗号（例如 "1,2,3,null,null,"）
        // pop_back() 用于删掉最后一个多余的逗号，保持字符串整洁
        if (!res.empty()) {
            res.pop_back();
        }
        return res; // 返回最终写好的层序遍历字符串
    }

    // 反序列化函数：将字符串还原为二叉树(BFS逆过程)
    TreeNode* deserialize(string data) {
        // 如果传入的是空字符串，直接返回空指针
        if (data.empty()) return nullptr;

        // ---------- 步骤 A：字符串切分 ----------
        vector<string> nodes;  // 用于存储切分后的一个个节点字符串（如 "1", "null"）
        stringstream ss(data); // 将 string 包装成“字符串流”，让它可以像 cin 一样读取数据
        string item;           // 临时存储切分出来的小段字符串

        // getline 会不断读取 ss 流中的数据，直到遇到逗号 ',' 为止，并把读取到的内容存入 item
        while (getline(ss, item, ',')) {
            nodes.push_back(item); // 将切分好的字符串（数字或 "null"）存入数组
        }

        // ---------- 步骤 B：构建根节点并初始化队列 ----------
        // nodes[0] 必然是根节点的值。stoi() 函数用于将字符串（如 "1"）转换为整数（1）
        TreeNode* root = new TreeNode(stoi(nodes[0]));

        queue<TreeNode*> q;  // 这里的队列用于存放“已经创建好、但还没找齐左右孩子的父节点”
        q.push(root);        // 根节点率先入队，等待给它找孩子

        // ---------- 步骤 C：双指针配合，动态建树 ----------
        // 变量 i 是指向 nodes 数组的指针。因为 nodes[0] 已经是根节点了，
        // 所以后续的孩子节点必然要从数组的下标 1 开始往下找。
        int i = 1;

        // 循环条件：队列不为空（还有父节点没分配完孩子）且数组没有越界
        while (!q.empty() && i < nodes.size()) {
            TreeNode* curr = q.front(); // 从队列中取出当前的“父节点”
            q.pop();

            // 1. 处理该父结点的leftchild
            if (nodes[i] != "null") {
                // 创建leftchild结点，注意要string to int
                curr->left = new TreeNode(stoi(nodes[i]));
                // 将该leftchild结点入队，它可能也会有自己的孩子
                q.push(curr->left);
            }
            i++; // leftchild处理完完毕，i向后移动一步

            // 2. 处理该父节点的rightchild
            // 因为i自增了，这里必须加上 i < nodes.size()，防止下标越界
            if (i < nodes.size() && nodes[i] != "null") {
                // 创建rightchild结点
                curr->right = new TreeNode(stoi(nodes[i]));
                q.push(curr->right);
            }
            i++; // rightchild处理完完毕，i向后移动一步
        }

        // 所有的结点都挂载完毕，返回最初保留的根结点指针
        return root;
    }
};
