#include <vector>
#include <numeric>

using namespace std;

// 方法一: 二维动态规划
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // 1. 计算数组中所有数字的总和
        int sum = accumulate(nums.begin(), nums.end(), 0);

        // 如果总和是奇数，绝对不可能平分成两个和相等的整数子集，直接返回 false
        if (sum % 2 == 1) {
            return false;
        }

        // 目标是：从数组中选出若干数字，使其和恰好等于总和的一半
        int m = sum / 2;
        int n = nums.size();

        // 2. 定义 DP 数组
        // dp[i][j] 表示：在前 i 个数字中，能否选出若干个数字，其和恰好为 j
        // 行数大小为 n + 1，列数大小为 m + 1，初始全部赋为 false
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        // 3. 初始化边界条件
        // 当目标和 j = 0 时，什么都不选即可凑出 0，所以所有 dp[i][0] 都为 true
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = true;
        }

        // 4. 状态转移
        // 外层循环：遍历每一个数字
        for (int i = 1; i <= n; ++i) {
            int coin = nums[i - 1]; // 当前面对的数字（注意下标偏移）

            // 内层循环：遍历每一种可能的背包容量（目标和）
            for (int j = 1; j <=m; ++j) {
                // 情况 A：不选择当前的数字 coin
                // 那么能否凑出 j，完全取决于前 i-1 个数字能否凑出 j
                dp[i][j] = dp[i - 1][j];

                // 情况 B：选择当前的数字 coin（前提是当前目标和 j 大于等于该数字）
                if (j >= coin) {
                    // 只要“不选”或“选”其中有一种情况能成功，dp[i][j] 就会是 true
                    // dp[i - 1][j - coin] 表示：用了当前数字后，前 i-1 个数字能否凑出剩下的容量 (j - coin)
                    dp[i][j] = dp[i][j] || dp[i - 1][j - coin];
                }
            }
        }

        // 5. 返回结果
        // 返回在前 n 个数字中，能否凑出和为 m
        return dp[n][m];
    }
};

// 方法二: 优化为一维数组
class Solution2 {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);

        // 剪枝：总和为奇数则无法平分
        if (sum % 2 == 1) {
            return false;
        }

        int m = sum / 2;

        // 定义一维 DP 数组，大小为 m + 1，初始全部为 false
        // dp[j] 表示：当前能否凑出和为 j
        vector<bool> dp(m + 1, false);

        // 初始化：目标和为 0 时，不选任何元素即可凑出，所以为 true
        dp[0] = true;

        // 状态转移
        // 外层循环：遍历数组中的每一个数字
        for (int coin : nums) {
            // 内层循环：逆序遍历背包容量！
            // 必须从 m 倒序遍历到 coin。如果正序遍历，同一个数字会被多次重复累加（变成完全背包）
            for (int j = m; j >= coin; --j) {
                // 如果原本就能凑出 j，或者能凑出 (j - coin)，那么现在就能凑出 j
                dp[j] = dp[j] || dp[j - coin];
            }
        }

        // 返回能否恰好凑出目标和 m
        return dp[m];
    }
};
