#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int singleNumber(std::vector<int>& nums) {
        int xor_sums = 0;
        for (auto num : nums) {
            xor_sums = xor_sums ^ num;
        }
        return xor_sums;
    }
};


int main() {
    Solution sol;
    std::vector<int> nums = { 4,1,2,1,2 };
    int ans = sol.singleNumber(nums);
    std::cout << ans << std::endl;
    return 0;
}
