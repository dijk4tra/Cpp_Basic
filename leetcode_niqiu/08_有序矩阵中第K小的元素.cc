#include <vector>
#include <iostream>
#include <limits.h>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 统计矩阵中绝对小于或等于 mid 的元素个数
    bool check(vector<vector<int>>& matrix, int mid, int k, int n) {
        int i = n - 1; // 从左下角开始
        int j = 0;
        int count = 0;

        while (i >= 0 && j < n) {
            if (matrix[i][j] <= mid) {
                count += (i + 1); // 当前列及上方所有的元素都小于等于 mid
                j++;              // 右移一列
            } else {
                i--;              // 上移一行
            }
        }
        return count >= k;
    }

    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int left = matrix[0][0];           // 矩阵的最小值
        int right = matrix[n - 1][n - 1];  // 矩阵的最大值

        // 开始二分查找
        while (left < right) {
            int mid = left + (right - left) / 2;

            // 调用 check 函数，看看矩阵中 <= mid 的元素个数是否足够 k 个
            if (check(matrix, mid, k, n)) {
                // 如果数量 >= k，说明第 k 小的数必然小于或等于 mid。
                // 注意：因为 mid 本身有可能是我们要找的那个答案（刚好是第 k 小），
                // 所以不能写成 mid - 1，而是要保留 mid，即 right = mid。
                right = mid;
            } else {
                // 如果数量 < k，说明 mid 猜小了，
                // 真正的第 k 小元素绝对不可能小于或等于 mid，必然大于 mid。
                // 所以我们可以安全地排除 mid，将左边界调整为 mid + 1。
                left = mid + 1;
            }
        }
        // 最后返回的 left 一定在矩阵中，因为二分查找在不断逼近边界
        return left;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix = { {1,5,9},{10,11,13},{12,13,15} };

    int ans = sol.kthSmallest(matrix, 8);
    cout << ans << endl;

    return 0;
}
