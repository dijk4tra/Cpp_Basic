#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;

        int n = s.size();
        int m = p.size();

        // 如果 s 比 p 还短，不可能存在异位词子串
        if (n < m)
            return ans;

        // pCount 统计 p 中字符频率
        // windowCount 统计当前窗口中的字符频率
        vector<int> pCount(26, 0);
        vector<int> windowCount(26, 0);

        // 初始化 pCount
        for (char c : p) {
            pCount[c - 'a']++;
        }

        // 遍历 s，维护一个长度不超过 m 的窗口
        for (int right = 0; right < n; right++) {
            // 右边加入当前字符
            windowCount[s[right] - 'a']++;

            // 如果窗口长度超过 m，需要移出左边字符
            if (right >= m) {
                int leftCharIndex = s[right - m] - 'a';
                windowCount[leftCharIndex]--;
            }

            // 当窗口长度达到 m 时，判断是否是异位词
            if (right >= m - 1) {
                if (windowCount == pCount) {
                    // 当前窗口是 s[right - m + 1 ... right]
                    ans.push_back(right - m + 1);
                }
            }
        }

        return ans;
    }
};