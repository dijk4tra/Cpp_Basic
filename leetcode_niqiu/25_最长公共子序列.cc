#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();

        // 创建一个(m+1)x(n+1)的二维数组，并初始化为 0
        // dp[0][j] 和 dp[i][0] 自动初始化为 0，作为边界条件
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // 从m+1行,n+1列的表格的左上角(dp[1][1])开始填表
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    // 情况一：当前字符相等，看左上角
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    // 情况二：当前字符不相等，看上方和左方，取最大值
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // 右下角的最后一个格子(dp[m][n])就是最终答案
        return dp[m][n];
    }
};
