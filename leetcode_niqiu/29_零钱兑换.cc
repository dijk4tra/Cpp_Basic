#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        const int INF = amount + 1; // 合法的数量不会超过amount

        // 定义二维 DP 表：dp[i][j] 表示使用前 i 种硬币，凑齐金额 j 所需的最少硬币个数。
        // 行数大小为 n + 1（包含不选任何硬币的第 0 行）
        // 列数大小为 amount + 1（包含金额为 0 的第 0 列）
        // 初始时将所有格子都设为 INF，代表默认情况下所有金额都无法被凑齐。
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, INF));

        // 初始化基本情况（边界条件）：
        // 无论可选的硬币有几种（i 从 0 到 n），如果要凑的总金额为 0，所需要的硬币个数都是 0。
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 0;
        }

        // 外层循环：遍历每一种硬币。i 代表当前考虑前 i 种硬币
        for (int i = 1; i <= n; ++i) {
            // 获取当前这一步新加入的硬币面值（注意硬币数组下标从 0 开始，所以对应 coins[i - 1]）
            int coin = coins[i - 1];

            // 内层循环：遍历目标金额 j，从 1 元一直算到最终的 amount 元
            for (int j = 1; j <= amount; ++j) {
                // 情况 1：coin 没有被使用
                // 如果完全不用这第 i 种硬币，那么最少硬币数就取决于只用前 i-1 种硬币凑齐金额 j 的结果
                dp[i][j] = dp[i-1][j];
                // 情况 2：coin 被使用
                // 只有当前目标金额 j 大于等于当前硬币面值时，我们才有机会选择使用它
                if (j >= coin) {
                    // 在“不使用当前硬币（当前的 dp[i][j]）”和“使用至少一枚当前硬币”之间取最小值。
                    // dp[i][j - coin] + 1 表示：回退到金额 (j - coin) 的最优解，并加上当前这 1 枚硬币。
                    // 为什么第一维是 i 而不是 i-1？因为每种硬币数量无限，选完一次后，后续依然可以继续选第 i 种硬币。
                    dp[i][j] = min(dp[i][j], dp[i][j - coin] + 1);
                }
            }
        }

        // 最终结果返回：
        // 检查使用全部 n 种硬币凑齐 amount 的最终格子 dp[n][amount]。
        // 如果该数值依然 >= INF，说明历经所有硬币组合也无法凑齐该金额，按题目要求返回 -1；
        // 否则，返回计算出的最少硬币个数。
        return dp[n][amount] >= INF ? -1 : dp[n][amount];
    }
};
