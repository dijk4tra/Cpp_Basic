#include <vector>
#include <string>
#include <sstream>

using namespace std;

// 利用 std::stringstream 配合 getline
// getline 允许指定自定义的分隔符
class Solution {
public:
    vector<string> splitWordsBySeparator(vector<string>& words, char separator) {
        vector<string> result;
        for (auto& word : words) {
            stringstream ss(word);
            string item; // 用于存储被分割出来的单词

            while (getline(ss, item, separator)) {
                // 排除空字符串
                if (!item.empty()) {
                    result.push_back(item);
                }
            }
        }

        return result;
    }
};

// 方法二: 手动遍历
// 可以通过一个临时字符串 res 来组装当前拆分出的子串。遍历每个字符串的字符：
// 如果遇到分隔符，说明一个子串可能结束了。如果此时 res 不为空，就把它存入结果中，然后清空 res。
// 如果不是分隔符，就将当前字符加入 res。
// 注意：当遍历完一个字符串时，如果 res 里面还有内容，记得把它也放进结果中。
class Solution2 {
public:
    vector<string> splitWordsBySeparator(vector<string>& words, char separator) {
        vector<string> result;

        for (const string& word : words) {
            string current_sub = "";
            for (char ch : word) {
                if (ch == separator) {
                    // 遇到分隔符，如果当前累积的子串不为空，则加入结果
                    if (!current_sub.empty()) {
                        result.push_back(current_sub);
                        current_sub.clear(); // 清空，准备记录下一个子串
                    }
                } else {
                    current_sub += ch;
                }
            }
            // 将字符串末尾最后一个子串加入结果
            if (!current_sub.empty()) {
                result.push_back(current_sub);
            }
        }

        return result;
    }
};
