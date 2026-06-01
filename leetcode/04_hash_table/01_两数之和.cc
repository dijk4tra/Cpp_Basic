#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 哈希表：key 表示数组中的元素值，value 表示该元素对应的下标
        unordered_map<int, int> map;

        // 遍历数组，尝试为当前元素 nums[i] 寻找另一个数
        for (int i = 0; i < nums.size(); i++) {
            // 当前遍历到的元素
            int x = nums[i];

            // 为了凑成 target，当前元素还需要的另一个数
            int need = target - x;

            // 如果 need 已经在哈希表中，说明找到了两个数
            if (map.count(need)) {
                // 返回 need 的下标和当前元素的下标
                return {map[need], i};
            }

            // 如果暂时没找到配对元素，就把当前元素和下标存入哈希表
            map[x] = i;
        }

        // 如果没有找到，返回空数组
        return {};
    }
};