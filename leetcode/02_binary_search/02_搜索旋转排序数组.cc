#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            // 防止 left + right 溢出
            int mid = left + (right - left) / 2;

            // 找到目标值，直接返回下标
            if (nums[mid] == target) {
                return mid;
            }

            // 情况一：左半边 [left, mid] 是有序的
            if(nums[left] <= nums[mid]){
                // target 位于左半边的有序区间内
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                }
                // target 不在左半边，只能去右半边找
                else {
                    left = mid + 1;
                }
            }
            // 情况二：右半边 [mid, right] 是有序的
            else {
                // target 位于右半边的有序区间内
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                }
                // target 不在右半边，只能去左半边找
                else {
                    right = mid - 1;
                }
            }
        }

        // 搜索结束仍然没有找到
        return -1;
    }
};