#include <vector>
#include <iostream>
#include <limits.h>
#include <algorithm>

using namespace std;

// 解法一: 二分划分线法
// 其本质是将问题转化为：如何在两个数组中各画一条分割线，
// 使得左半部分的所有元素都小于或等于右半部分的所有元素，且左右两边的元素个数相等（或左边比右边多一个）。
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 确保 nums1 是较短的数组，这样二分查找更快，且能保证 j 不会变成负数
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size();
        int n = nums2.size();

        if (m + n == 0) {
            return 0.0;
        }

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
            int j = half -i;

            // nums1 左边部分的最大值
            int nums1Left = (i == 0) ? INT_MIN : nums1[i - 1];

            // nums1 右边部分的最小值
            int nums1Right = (i == m) ? INT_MAX : nums1[i];

            // nums2 左边部分的最大值
            int nums2Left = (j == 0) ? INT_MIN : nums2[j - 1];

            // nums2 右边部分的最小值
            int nums2Right = (j == n) ? INT_MAX : nums2[j];

            // 找到了正确切割:
            // 左半部分所有元素 <= 右半部分所有元素
            if (nums1Left <= nums2Right && nums2Left <= nums1Right) {
                // 如果总长度是奇数
                // 中位数就是左半部分的最大值
                if ((m + n) % 2 == 1) {
                    return max(nums1Left, nums2Left);
                }

                // 如果总长度是偶数
                // 中位数就是左半部分的最大值和右半部分最小值的平均值
                int leftMax = max(nums1Left, nums2Left);
                int rightMin = min(nums1Right, nums2Right);

                return (leftMax + rightMin) / 2.0;
            }

            // nums1 左边元素太大
            // 说明 nums1 切得太靠右，需要往左切
            else if (nums1Left > nums2Right) {
                right = i - 1;
            }

            // nums2 左边元素太大（即 nums2Left > nums1Right）
            // 说明 nums1 切得太靠左了，需要往右切
            else {
                left = i + 1;
            }
        }

        return 0.0;
    }
};


// 解法二：寻找第 K 小的数
// 把“找中位数”转换为“寻找两个有序数组中的第 K 小的数”
class Solution2 {
public:
    /**
     * 辅助函数：在两个有序数组的当前有效区间内，寻找第 k 小的元素（k 从 1 开始计数）
     * @param start1 nums1 当前有效的起始下标（此下标之前的元素已被淘汰）
     * @param start2 nums2 当前有效的起始下标（此下标之前的元素已被淘汰）
     * @param k      当前剩余元素中，我们需要寻找的“第几小”的目标
     */
    int getKthElement(const std::vector<int>& nums1, int start1, const std::vector<int>& nums2, int start2, int k) {
        int m = nums1.size();
        int n = nums2.size();

        while (true) {
            // =================================================================
            // 一、三大边界退出条件（循环的终点）
            // =================================================================

            // 退出条件 1：nums1 的有效元素已全部被淘汰（起始指针越界到达了末尾 m）
            // 说明剩下的数全在 nums2 里。我们直接从 nums2 的有效起点 start2 开始，向后数 k 个数。
            // 因为数组下标从 0 开始，所以数 k 个数对应的下标就是：起点 + k - 1
            if (start1 == m) {
                return nums2[start2 + k - 1];
            }

            // 退出条件 2：nums2 的有效元素已全部被淘汰（起始指针越界到达了末尾 n）
            // 同理，直接去 nums1 中，从有效起点 start1 开始向后数 k 个数
            if (start2 == n) {
                return nums1[start1 + k - 1];
            }

            // 退出条件 3：k 已经减小到了 1（即我们要找当前剩下所有元素中的“最小那一个”）
            // 既然两个数组都是升序的，最小的数一定在两个数组当前的“有效第一位”中诞生。谁小，谁就是答案。
            if (k == 1) {
                return std::min(nums1[start1], nums2[start2]);
            }

            // =================================================================
            // 二、二分比较逻辑（核心下标计算）
            // =================================================================

            // 计算在 nums1 中尝试进行比较的“哨兵”下标：我们要从有效起点 start1 开始，往后数 k/2 个元素。
            // 1. 正常情况下，数 k/2 个元素对应的下标是：start1 + k/2 - 1
            // 2. 特殊情况：如果 nums1 剩下的元素已经不够 k/2 个了，为了防止数组越界，
            //    我们利用 std::min 强行让它停在 nums1 的最后一个元素（即下标 m - 1）
            int newStart1 = std::min(start1 + k / 2 - 1, m - 1);

            // 同理，计算在 nums2 中尝试进行比较的“哨兵”下标。如果不够数，则强行停在最后一个元素（即下标 n - 1）
            int newStart2 = std::min(start2 + k / 2 - 1, n - 1);

            // 取出两个数组中计算出来的哨兵元素值，准备比较大小
            int pivot1 = nums1[newStart1];
            int pivot2 = nums2[newStart2];

            // =================================================================
            // 三、区间淘汰与状态更新
            // =================================================================
            if (pivot1 <= pivot2) {
                // 当 pivot1 较小时，说明 nums1 从【当前有效起点 start1】到【哨兵位置 newStart1】这一整段元素，
                // 由于太小了，绝对不可能包含全局第 k 小的元素。必须将这一段整体淘汰！

                // 1. 计算这一轮被淘汰掉的元素个数：下标大减小，再加 1
                int count = newStart1 - start1 + 1;

                // 2. 更新 k 值：由于已经淘汰了 count 个元素，下一轮只需要在剩余元素中找第 (k - count) 小的元素
                k -= count;

                // 3. 更新有效起点：把 nums1 的有效起点跳过被淘汰的区域，挪到 newStart1 的下一个位置
                start1 = newStart1 + 1;
            }
            else {
                // 反之，说明 pivot2 较小，nums2 对应的这一段区间被整体淘汰
                int count = newStart2 - start2 + 1;
                k -= count;
                start2 = newStart2 + 1; // nums2 的有效起点后移
            }
        }
    }

    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();

        // 情况 A：总长度是奇数。中位数就是两个数组合并后，第 (总长度/2 + 1) 小的那个数
        if (totalLength % 2 == 1) {
            return getKthElement(nums1, 0, nums2, 0, totalLength / 2 + 1);
        }
        // 情况 B：总长度是偶数。中位数是中间两个数的平均值，
        // 也就是第 (总长度/2) 小和第 (总长度/2 + 1) 小的两个数相加，最后除以 2.0 转化成浮点数
        else {
            return (getKthElement(nums1, 0, nums2, 0, totalLength / 2) +
                    getKthElement(nums1, 0, nums2, 0, totalLength / 2 + 1)) / 2.0;
        }
    }
};

int main() {
    Solution2 sol;
    vector<int> nums1 = { 1,3 };
    vector<int> nums2 = { 2,4,7,9,11,13 };
    double ans = sol.findMedianSortedArrays(nums1, nums2);
    cout << ans << endl;

    return 0;
}
