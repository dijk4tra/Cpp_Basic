#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// 方法一: 动态规划(更通用!)
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // dp 记录以当前位置结尾的最大和，maxSum 记录全局最大和
        int dp = nums[0];
        int maxSum = nums[0];

        // 从第二个元素开始遍历
        for (int i = 1; i < nums.size(); ++i) {
            // 状态转移方程：要么结合前面，要么自立门户
            dp = max(dp + nums[i], nums[i]);

            // 随时记录过程中出现过的最大值
            maxSum = max(maxSum, dp);
        }

        return maxSum;
    }
};


// 方法二: 寻找当前前缀和与历史最小前缀和的最大差值
class Solution2 {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        // 1. 创建前缀和数组 s，大小为 n
        vector<int> s(n);
        s[0] = nums[0];

        // 2. 第一次遍历：计算所有位置的前缀和
        for (int i = 1; i < n; ++i) {
            s[i] = s[i - 1] + nums[i];
        }

        // 3. 第二次遍历：寻找最大差值
        int maxSum = nums[0];
        int minPrefix = 0; // 记录在下标 j 之前的最小的 s[i]

        for (int j = 0; j < n; j++) {
            // 用 s[j] 去减去前面最小的 s[i]
            int currSum = s[j] - minPrefix;

            // 如果当前得到的子数组和更大, 则更新最大值
            maxSum = max(maxSum, currSum);

            // 如果当前的 s[j] 更小, 则更新minPrefix
            minPrefix = min(minPrefix, s[j]);
        }

        return maxSum;
    }
};

// 方法三: 方法二的空间优化版
class Solution3 {
public:
    int maxSubArray(vector<int>& nums) {
        // max_sum初始化为最小整数, 确保能正确记录负数结果
        int max_sum = INT_MIN;

        int curr_sum = 0; // 当前的前缀和
        int min_sum = 0;  // 历史遇到的最小前缀和

        for (int num : nums) {
            curr_sum += num; // 计算当前位置的前缀和

            // 用当前的前缀和减去历史最小的前缀和, 尝试更新最大子数组和
            max_sum = max(max_sum, curr_sum - min_sum);

            // 更新历史最小前缀和, 供后续循环使用
            min_sum = min(min_sum, curr_sum);
        }

        return max_sum;
    }
};
