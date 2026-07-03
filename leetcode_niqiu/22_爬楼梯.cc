#include <vector>

using namespace std;

// 方法二: 基于方法一的滚动变量优化
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }

        int first = 1;  // 代表 f(n-2)
        int second = 2; // 代表 f(n-1)
        int sum = 0;    // 代表 f(n)

        for (int i = 3; i <= n; i++) {
            sum = first + second; // 当前的方法数 = 前两步之和
            first = second;       // 状态向后移动
            second = sum;
        }

        return second;
    }
};

// 方法二: 动态规划（使用数组保存状态）
class Solution2 {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }

        // dp[i] 表示爬到第 i 阶的方法数
        std::vector<int> dp(n + 1);
        dp[1] = 1;
        dp[2] = 2;

        // 从第 3 阶开始递推
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};
