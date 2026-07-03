#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// 方法一: 经典动态规划 (时间复杂度为O(n^2))
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        // 如果数组为空，最长递增子序列长度显然为 0
        if (n == 0) {
            return 0;
        }

        // 初始化 dp 数组，大小为 n，所有元素初始值设为 1
        // 因为每个独立的元素自身都可以看作是一个长度为 1 的严格递增子序列
        vector<int> dp(n, 1);

        // result 用于记录全局的最长递增子序列长度，至少为 1
        int result = 1;

        // 外层循环：遍历每一个位置 i，计算以 nums[i] 结尾的最长递增子序列长度
        for (int i = 0; i < n; ++i) {
            // 内层循环：遍历 i 之前的每一个位置 j (0 到 i-1)
            for (int j = 0; j < i; ++j) {
                // 如果前方的元素 nums[j] 小于当前元素 nums[i]
                // 说明 nums[i] 可以接在以 nums[j] 结尾的递增子序列后面
                if (nums[j] < nums[i]) {
                    // 状态转移方程：
                    // 我们尝试把 nums[i] 接到以 nums[j] 结尾的序列后面，长度变成 dp[j] + 1
                    // 并与当前已知的 dp[i] 取最大值，以确保 dp[i] 记录的是最长的那条路径
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            // 每算完一个以 nums[i] 结尾的最长长度，就去更新全局最大值 result
            result = max(result, dp[i]);
        }

        // 返回最终找到的最长递增子序列的长度
        return result;
    }
};

// 方法二: 动态规划 + 二分查找 (时间复杂度为O(nlog n))
class Solution2 {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;

        // tails[i] 表示长度为 i+1 的递增子序列中，最小的结尾元素
        vector<int> tails;

        for (int x : nums) {
            // 使用二分查找，在 tails 中找到第一个大于或等于 x 的元素的迭代器
            auto it = lower_bound(tails.begin(), tails.end(), x);

            if (it == tails.end()) {
                // 如果没找到，说明 x 比 tails 里的所有元素都大
                // x 可以和前面所有元素组成一个更长的递增子序列，直接加到末尾
                tails.push_back(x);
            } else {
                // 如果找到了，用更小的 x 更新这个位置的结尾元素（贪心策略）
                *it = x;
            }
        }

        // 最终 tails 的长度就是最长递增子序列的长度
        return tails.size();
    }
};
