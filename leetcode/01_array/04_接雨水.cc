#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        // 双指针版本更省空间
        // 空间复杂度O(1)
        
        int n = height.size();

        // 左右指针：分别指向左右两边界的列
        int left = 0;
        int right = n - 1;
        // 左指针的左边最大高度、右指针的右边最大高度
        int leftMax = height[left];
        int rightMax = height[right];
        // 最两边的列存不了水
        left++;
        right--;

        int res = 0;
        // 向中间靠拢
        while(left <= right){
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if(leftMax < rightMax){
                // 左指针的leftMax比右指针的rightMax矮
                // 说明：左指针的右边至少有一个板子 > 左指针左边所有板子
                // 根据水桶效应，保证了左指针当前列的水量决定权在左边
                // 那么可以计算左指针当前列的水量：左边最大高度-当前列高度
                res += leftMax -height[left];
                left++;
            }else{
                // 右边同理
                res += rightMax - height[right];
                right--;
            }
        }
        return res;
    }
};