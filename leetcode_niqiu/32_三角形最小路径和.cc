#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// 方法一: 标准二维动态规划 (自顶向下, 边界条件很复杂)
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        // 创建一个和 triangle 结构完全一样的二维 dp 数组
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // 1. 基础状态：起点的值
        dp[0][0] = triangle[0][0];

        // 2. 自顶向下状态转移
        for (int r = 1; r < n; ++r) {
            for (int c = 0; c <= r; ++c) {
                if (c == 0) {
                    // 特殊情况 1：最左边，只能从上一行的最左边走下来
                    dp[r][c] = dp[r - 1][c] + triangle[r][c];
                }
                else if (c == r) {
                    // 特殊情况 2：最右边，只能从上一行的最右边（斜上方）走下来
                    dp[r][c] = dp[r - 1][c - 1] + triangle[r][c];
                }
                else {
                    // 正常情况：取左上和正上的较小值
                    dp[r][c] = min(dp[r - 1][c], dp[r - 1][c - 1]) + triangle[r][c];
                }
            }
        }

        // 3. 在最后一行找到最小值
        int min_path = INT_MAX;
        for (int c = 0; c < n; ++c) {
            min_path = min(min_path, dp[n - 1][c]);
        }

        return min_path;
    }
};

// 方法二: 仅使用一维数组, 且自底向上, 没有复杂的边界条件
class Solution2 {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        // 初始状态：dp 数组直接存放最后一行的数据
        vector<int> dp = triangle[n - 1];

        // 从倒数第二行开始，自底向上动态规划
        for (int r = n - 2; r >= 0; --r) {
            for (int c = 0; c <= r; ++c) {
                // 当前位置的最小路径和 = 当前值 + 下方两个邻居的较小值
                dp[c] = triangle[r][c] + min(dp[c], dp[c + 1]);
            }
        }

        // 最终顶部的元素即为答案
        return dp[0];
    }
};
