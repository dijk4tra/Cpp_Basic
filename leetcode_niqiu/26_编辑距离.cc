#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // 1. 定义状态数组 dp[i][j]
        // dp[i][j] 表示：将 word1 的前 i 个字符（即 word1[0...i-1]）
        // 转换成 word2 的前 j 个字符（即 word2[0...j-1]）所需的最少操作数。
        // 因为需要考虑空串的情况，所以维度大小为 (n + 1) * (m + 1)
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // 2. 初始化边界条件
        // 当 word2 为空串时（j = 0），把 word1 的前 i 个字符全部删除，需要 i 次操作
        for (int i = 0; i <= n; i++) dp[i][0] = i;

        // 当 word1 为空串时（i = 0），往空串中插入 word2 的前 j 个字符，需要 j 次操作
        for (int j = 0; j <= m; j++) dp[0][j] = j;

        // 3. 状态转移遍历
        // 外部两层循环从 1 开始，依次计算每个子问题的最优解
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // 注意：由于 dp 数组的索引比字符串索引大 1，
                // 对应到字符串中，当前比较的字符是 word1[i - 1] 和 word2[j - 1]
                if (word1[i - 1] == word2[j - 1]) {
                    // 情况 A：当前字符相同，不需要任何操作
                    // 直接继承「不包含这两个当前字符」时的最少操作数
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // 情况 B：当前字符不同，我们需要在三种操作中选择代价最小的一种，并外加当前这一次操作 (+ 1)
                    dp[i][j] = min({
                        dp[i - 1][j - 1], // 1. 替换操作：将 word1[i-1] 替换为 word2[j-1]，之后转化为求解 dp[i-1][j-1]
                        dp[i - 1][j],     // 2. 删除操作：将 word1[i-1] 删除，之后继续用 word1[0...i-2] 去匹配 word2[0...j-1]
                        dp[i][j - 1]      // 3. 插入操作：在 word1 后面插入一个 word2[j-1]，使得末尾匹配，之后转化为求解 dp[i][j-1]
                    }) + 1;
                }
            }
        }

        // 4. 返回最终结果
        // dp[n][m] 即为将整个 word1 转化为整个 word2 的最少编辑距离
        return dp[n][m];
    }
};
