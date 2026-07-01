#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int singleNumber(std::vector<int>& nums) {
        int ans = 0;

        // 遍历 32 个 bit 位
        for (int i = 0; i < 32; i++) {
            int cnt = 0;

            // 统计所有数字在第 i 位上 1 的个数
            for (int x : nums) {
                if ((x >> i) & 1) { // 把 x 往右移动 i 位
                    cnt++;
                }
            }

            if (cnt % 3 != 0) {
                // 使用 1U (unsigned int) 避免左移 31 位时发生符号位溢出的未定义行为
                ans |= (1U << i); // |:按位或
            }
        }

        return ans;
    }
};



class Solution1 {
public:
    int singleNumber(std::vector<int>& nums) {
        int ans = 0;

        for (int i = 0; i < 32; i++) {
            int cnt = 0;

            for (int x : nums) {
                if (x & (1 << i)) { // 把 1 往左移动 i 位
                    cnt++;
                }
            }

            if (cnt % 3 != 0) {
                ans += (1 << i);
            }
        }

        return ans;
    }
};


int main() {
    Solution sol;
    std::vector<int> nums = { 0,1,0,1,0,1,99 };
    int ans = sol.singleNumber(nums);
    std::cout << ans << std::endl;
    return 0;
}
