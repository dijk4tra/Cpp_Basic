#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // 1. 使用二分查找找到第一个大于等于 x 的位置
        auto it = lower_bound(arr.begin(), arr.end(), x);
        // int right = distance(arr.begin(), it);
        int right = static_cast<int>(it - arr.begin());
        int left = right - 1;

        // 2. 双指针向两边扩展，直到选满 k 个元素
        while (k > 0) {
            if (left < 0) {
                // 左边越界，只能选右边
                right++;
            } else if (right >= arr.size()) {
                // 右边越界，只能选左边
                left--;
            } else if (x - arr[left] <= arr[right] - x){
                // 左边更接近，或者距离相等（约定相等时优先选较小的，即左边）
                left--;
            } else {
                // 右边更接近
                right++;
            }
            k--;
        }

        // 3. 此时的区间 (left, right) 就是我们要找的 k 个元素（注意是开区间）
        // 当选满 k 个元素跳出循环时，left 和 right 已经变成了边界外的指针
        // 真正的有效数据区间是闭区间 [left + 1, right - 1]
        // vector 构造函数遵循左闭右开原则：包含 start_iterator，但不包含 end_iterator
        return vector<int>(arr.begin() + left + 1, arr.begin() + right);
    }
};

int main() {
    Solution sol;
    vector<int> arr = { 1,1,2,3,4,5 };
    vector<int> ans = sol.findClosestElements(arr, 4, -1);
    for (int num : ans) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
