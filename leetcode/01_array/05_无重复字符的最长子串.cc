#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // window 用来维护当前滑动窗口中的字符，保证窗口内没有重复字符
        unordered_set<char> window;

        // left 表示滑动窗口的左边界
        int left = 0;

        // ans 记录目前找到的最长无重复子串的长度
        int ans = 0;

        // right 表示滑动窗口的右边界，逐步向右遍历字符串
        for (int right = 0; right < s.size(); right++) {

            // 如果当前字符 s[right] 已经在窗口中，
            // 说明加入它会导致重复，需要移动左边界，直到把重复的字符移出窗口
            while (window.count(s[right])) {
                // 删除窗口最左侧的字符
                window.erase(s[left]);

                // 左边界右移，缩小窗口
                left++;
            }

            // 此时窗口中已经没有 s[right]，可以安全加入
            window.insert(s[right]);

            // 更新最长无重复子串的长度
            ans = max(ans, right - left + 1);
        }

        // 返回最终答案
        return ans;
    }
};