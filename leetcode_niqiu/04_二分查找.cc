#include <vector>
#include <iostream>

using namespace std;

// 左闭右闭 [left, right]： while (left <= right)，right = mid - 1
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
};

// 左闭右开 [left, right)： while (left < right)，right = mid
// 半开区间 [left, right)： 当 left == right 时，
// 比如 [2, 2)，在数学上这是一个空区间，里面不包含任何元素。
// 如果继续循环，去执行 nums[mid] 就会毫无意义，甚至在特定情况下导致死循环。
// 因此，循环成立的条件必须是 left < right。
class Solution1 {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid; // 注意: 不能为 mid - 1
                // 因为右边界是开区间（即 right 指向的下标永远不包含在查找范围内）。
                // 既然 mid 已经排除掉了，直接让 right = mid。
                // 此时，新的查找区间变成了 [left, mid)，它正好把 mid 排除在外，符合逻辑。
            }
        }

        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> nums = { -1,0,3,5,9,12 };
    int ans = sol.search(nums, 9);
    cout << ans << endl;
    return 0;
}
