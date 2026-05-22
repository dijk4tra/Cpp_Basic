#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    // 1.初始化一个 vector<char> 模拟字符序列
    vector<char> char_vec = {'H', 'e', 'l', 'l', 'o', '!', 'C', '+', '+'};
    
    // 2. 使用迭代器区间初始化 string
    string str(char_vec.begin(), char_vec.end());
    
    cout << "vector 中的字符已成功拼接到 string: " << str << endl;
    
    
}