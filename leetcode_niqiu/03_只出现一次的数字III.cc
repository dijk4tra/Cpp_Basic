#include <vector>
#include <iostream>
#include <limits.h>

using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        // 1. 算出 a ^ b 的值
        int xor_sum = 0;
        for (int num : nums) {
            xor_sum ^= num;
        }

        // 2. 防止溢出，用 unsigned int 提取出 xor_sum 最右侧的 1
        // 这个 1 代表 a 和 b 在这一位上不同
        unsigned int lsb = (xor_sum == INT_MIN) ? xor_sum : (xor_sum & (-xor_sum));

        // 3. 根据 lsb 将数组分为两组，分别进行异或
        int group1_xor_sum = 0;
        int group2_xor_sum = 0;
        for (int num : nums) {
            if (num & lsb) {
                // 第 k 位为 1 的组
                group1_xor_sum ^= num;
            } else {
                // 第 k 位为 0 的组
                group2_xor_sum ^= num;
            }
        }

        // group1_xor_sum, group2_xor_sum 分别为仅出现一次的那两个数字
        return {group1_xor_sum, group2_xor_sum};
    }
};

int main() {
    Solution sol;
    vector<int> nums = { 1,2,1,3,2,5 };
    vector<int> ans = sol.singleNumber(nums);
    std::cout << ans[0] << " " << ans[1] << std::endl;
    return 0;
}
