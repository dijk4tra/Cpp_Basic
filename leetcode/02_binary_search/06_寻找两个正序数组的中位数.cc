#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 保证 nums1 是较短的数组
        // 这样可以在 nums1 上二分，避免 j 越界
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size();
        int n = nums2.size();

        // left 和 right 表示 nums1 的切割位置范围
        // i 可以从 0 到 m
        int left = 0;
        int right = m;

        // 左半部分需要包含的元素个数
        // 如果总长度是奇数，左半部分比右半部分多一个
        int half = (m + n + 1) / 2;

        while (left <= right) {
            // nums1 的切割位置
            int i = left + (right - left) / 2;

            // nums2 的切割位置
            int j = half - i;

            // nums1 左边最大值
            int nums1Left = (i == 0) ? INT_MIN : nums1[i - 1];

            // nums1 右边最小值
            int nums1Right = (i == m) ? INT_MAX : nums1[i];

            // nums2 左边最大值
            int nums2Left = (j == 0) ? INT_MIN : nums2[j - 1];

            // nums2 右边最小值
            int nums2Right = (j == n) ? INT_MAX : nums2[j];

            // 找到了正确切割：
            // 左半部分所有元素 <= 右半部分所有元素
            if (nums1Left <= nums2Right && nums2Left <= nums1Right){
                // 如果总长度是奇数
                // 中位数就是左半部分的最大值
                if((m + n) % 2 == 1) {
                    return max(nums1Left, nums2Left);
                }

                // 如果总长度是偶数
                // 中位数是左半部分最大值和右半部分最小值的平均值
                int leftMax = max(nums1Left, nums2Left);
                int rightMin = min(nums1Right, nums2Right);

                return (leftMax + rightMin) / 2.0;
            }

            // nums1 左边元素太大了
            // 说明 nums1 切得太靠右，需要往左切
            else if (nums1Left > nums2Right) {
                right = i - 1;
            }

            // nums1 左边元素太小了
            // 说明 nums1 切得太靠左了，需要往右切
            else {
                left = i + 1;
            }
        }
        return 0.0;
    }
};