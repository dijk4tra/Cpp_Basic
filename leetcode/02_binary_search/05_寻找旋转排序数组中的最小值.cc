#include <vector>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            // 防止 left + right 溢出
            int mid = left + (right - left) / 2;

            // 情况一：
            // nums[mid] > nums[right]
            // 说明 mid 位于左边较大的有序段
            // 最小值一定在 mid 的右边
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } 
            // 情况二：
            // nums[mid] < nums[right]
            // 说明 [mid, right] 是有序的
            // 最小值可能是 nums[mid]，也可能在 mid 左边
            else {
                right = mid;
            }
        }

        // 循环结束时，left == right
        // 此时指向的就是最小值
        return nums[left];
    }
};