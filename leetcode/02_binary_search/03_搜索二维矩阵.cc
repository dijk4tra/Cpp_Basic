#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(); // 行数
        int n = matrix[0].size(); // 列数

        // 把二维矩阵看成一个长度为 m * n 的一维升序数组
        int left = 0;
        int right = m * n - 1;

        while (left <= right){
            // 防止 left + right 溢出
            int mid = left + (right - left) / 2;

            // 一维下标 mid 转换成二维下标：
            // 行号 = mid / n
            // 列号 = mid % n
            int x = matrix[mid / n][mid % n];

            if (x == target){
                return true;
            } else if (x < target){
                // 当前值小于 target，说明 target 只可能在右半边
                left = mid + 1;
            } else {
                // 当前值大于 target，说明 target 只可能在左半边
                right = mid - 1;
            }

        }

        // 搜索区间为空，说明不存在 target
        return false;
    }
};