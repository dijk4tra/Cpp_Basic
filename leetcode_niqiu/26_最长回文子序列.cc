#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 方法一: 动态规划 (二维数组,时间复杂度O(n^2),空间复杂度O(n^2))
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        // 创建一个 nxn 的二维数组，初始化为 0
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // 从后往前遍历 i
        for (int i = n - 1; i >= 0; --i) {
            dp[i][i] = 1; // 单个字符的最长回文子序列长度为 1

            // 从 i+1 开始往后遍历 j
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }

        // 最终结果保存在区间 [0, n-1] 中
        return dp[0][n - 1];
    }
};

// 方法二: 动态规划 + 滚动数组（Rolling Array）(一维数组,时间复杂度O(n^2),空间复杂度O(n))
