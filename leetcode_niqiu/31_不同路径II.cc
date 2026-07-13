#include <vector>

using namespace std;

// 方法一: 标准二维动态规划
class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        // 如果起点或终点有障碍物，直接返回 0
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) {
            return 0;
        }

        // 创建 DP 数组，初始化为 0
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

        // 初始化起点
        dp[0][0] = 1;

        // 初始化第一列：只要没遇到障碍物，路径就为 1；遇到障碍物后，后续全为 0
        for (int i = 1; i < m; ++i) {
            if (obstacleGrid[i][0] == 0 && dp[i - 1][0] == 1) {
                dp[i][0] = 1;
            }
        }

        // 初始化第一行：同理
        for (int j = 1; j < n; ++j) {
            if (obstacleGrid[0][j] == 0 && dp[0][j - 1] == 1) {
                dp[0][j] = 1;
            }
        }

        // 填充其余网格
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0; // 遇到障碍物，当前位置不可达，路径清零
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};

// 方法二：滚动数组优化（省内存）
class Solution2 {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        // 如果起点有障碍物，直接返回 0
        if (obstacleGrid[0][0] == 1) return 0;

        // 用一维数组代替二维矩阵，大小为列数 n
        vector<int> dp(n, 0);
        dp[0] = 1; // 起点初始化

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0; // 遇到障碍物，当前位置不可达，路径清零
                } else if (j > 0) {
                    // 当前格子路径数 = 上方格子路径数(原dp[j]) + 左方格子路径数(dp[j-1])
                    dp[j] = dp[j] + dp[j - 1];
                }
            }
        }

        return dp[n - 1];
    }
};
