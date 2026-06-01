#include <vector>
using namespace std;

// 思路：用 right 扫描整个数组，用 left 维护非零元素应该放置的位置。
// 遍历结束后，所有非零元素都被移动到前面，所有 0 自然被交换到后面。

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        // left 指向下一个非零元素应该放置的位置
        int left = 0;

        // right 用于遍历数组，寻找非零元素
        for (int right = 0; right < nums.size(); ++right) {
            // 如果当前元素不是 0，就把它移动到 left 位置
            if (nums[right]) {
                swap(nums[left], nums[right]);

                // left 后移，准备存放下一个非零元素
                left++;
            }
        }
    }
};