#include <vector>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        // 左边界，表示当前查找区间的起点
        int left = 0;

        // 右边界，使用 nums.size()
        // 搜索区间是左闭右开：[left, right)
        // 这样可以自然处理 target 应该插入到数组末尾的情况
        int right = nums.size();

        // 当 left == right 时，查找结束
        while(left < right)
        {   
            // 防止 left + right 过大导致整数溢出
            int mid = left + (right - left) / 2;

            // 如果中间值小于 target
            // 说明 mid 以及 mid 左边的位置都不可能是答案
            // 所以去右半部分继续查找
            if (nums[mid] < target)
            {
                left = mid + 1;
            }
            // 如果 nums[mid] >= target
            // 说明 mid 可能就是答案
            // 但左边可能还有更早的位置满足条件
            // 所以继续在左半部分查找
            else 
            {
                right = mid;
            }
        }

        // 循环结束时，left == right
        // 这个位置就是第一个大于等于 target 的位置
        // 如果 target 存在，这是它的下标
        // 如果 target 不存在，这是它应该插入的位置
        return left;
    }
};