#include <vector>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        // left 和 right 分别指向容器的左右边界
        int left = 0;
        int right = height.size() - 1;

        // 记录当前能装下的最大水量
        long maxArea = 0;

        // 当左右边界没有相遇时，继续尝试不同的容器宽度
        while (left < right) {
            // 当前容器的宽度为 right - left
            // 当前容器的高度由较短的那条边决定
            long area = (right - left) * min(height[left], height[right]);

            // 更新最大面积
            if (area > maxArea) {
                maxArea = area;
            }

            // 移动较短的一侧：
            // 因为面积受较短边限制，移动较高的一侧不可能得到更大的高度收益
            height[left] > height[right] ? right-- : left++;
        }

        // 返回最大水量
        return maxArea;
    }
};