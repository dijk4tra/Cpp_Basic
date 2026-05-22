#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main()
{
    deque<string> words;
    string word;

    cout << "请输入一系列字符串（按Ctrl+D结束输入）：" << endl;

    // 从标准输入中循环读取 string 序列
    while (cin >> word)
    {
        words.push_back(word);
    }
    
    // 打印 words 中的所有元素
    for (deque<string>::iterator it = words.begin(); it != words.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}