#include <vector>

using namespace std;

// 方法一: 标准二维动态规划
class Solution {
public:
    int uniquePaths(int m, int n) {
        // 创建一个 m x n 的二维数组，初始化为 1
        // 这样就顺便把第一行和第一列的边界都初始化为 1
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 1));

        // 从 (1, 1) 开始遍历填表
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        // 返回右下角的值
        return dp[m - 1][n - 1];
    }
};

// 方法二：滚动数组优化（省内存）
class Solution2 {
public:
    int uniquePaths(int m, int n) {
        // 只需要一维数组，大小为列数 n，初始全部为 1
        std::vector<int> dp(n, 1);

        // 外层循环控制行数（从第 1 行到第 m-1 行）
        for (int i = 1; i < m; ++i) {
            // 内层循环控制列数（第一列永远是 1，所以从 1 开始更新）
            for (int j = 1; j < n; ++j) {
                dp[j] = dp[j] + dp[j - 1];
            }
        }

        return dp[n - 1];
    }
};
