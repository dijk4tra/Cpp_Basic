#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // 数组长度
        int n = nums.size();

        // 先排序，方便后续使用双指针，并且便于去重
        sort(nums.begin(), nums.end());

        // 保存所有不重复的三元组
        vector<vector<int>> res;

        // 枚举三元组中的第一个数 nums[i]
        for (int i = 0; i < n; i++) {
            // 如果 nums[i] 已经大于 0，
            // 由于数组已排序，后面的数也都大于等于 nums[i]，
            // 三数之和不可能再等于 0
            if (nums[i] > 0) break;

            // 跳过重复的第一个数，避免结果中出现重复三元组
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // 使用双指针在 i 右侧寻找两个数，
            // 使 nums[l] + nums[r] = -nums[i]
            int l = i + 1;
            int r = nums.size() - 1;
            int target = -nums[i];

            // 在区间 [l, r] 中寻找满足条件的两个数
            while (l < r) {
                int sum = nums[l] + nums[r];

                if (sum == target) {
                    // 找到一个满足条件的三元组
                    res.push_back({nums[i], nums[l], nums[r]});

                    // 同时移动左右指针，继续寻找其他可能的组合
                    l++;
                    r--;

                    // 跳过重复的第二个数，避免重复结果
                    while (l < r && nums[l] == nums[l - 1]) l++;

                    // 跳过重复的第三个数，避免重复结果
                    while (l < r && nums[r] == nums[r + 1]) r--;
                } else if (sum < target) {
                    // 当前两数之和偏小，需要增大 sum
                    // 因为数组已排序，所以左指针右移
                    l++;
                } else {
                    // 当前两数之和偏大，需要减小 sum
                    // 因为数组已排序，所以右指针左移
                    r--;
                }
            }
        }

        // 返回所有不重复的三元组
        return res;
    }
};