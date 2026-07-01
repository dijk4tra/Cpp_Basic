#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // 找 target 第一次出现的位置
        int first = findFirst(nums, target);
        // 找 target 最后一次出现的位置
        int last = findLast(nums, target);

        return {first, last};
    }

private:
    // 找 target 第一次出现的位置
    int findFirst(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int ans = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                ans = mid;        // 记录当前 target 位置
                right = mid - 1;  // 继续向左收缩，寻找更靠前的位置
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return ans;
    }

    // 找 target 最后一次出现的位置
    int findLast(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int ans = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                ans = mid;       // 记录当前 target 位置
                left = mid + 1;  // 继续向右收缩，寻找更靠后的位置
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = { 5,7,7,8,8,10 };
    vector<int> ans = sol.searchRange(nums, 8);
    cout << ans[0] <<" " << ans[1] << endl;
    return 0;
}
