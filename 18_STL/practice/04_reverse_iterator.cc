#include <iostream>
#include <vector>
#include <list>
#include <algorithm> // std::copy
#include <iterator>  // std::back_inserter

using namespace std;

int main()
{
    vector<int> src = {5, 4, 3, 2, 1};
    list<int> dst;

    // 使用反向迭代器作为源区间，通过 back_inserter 动态插入到 dst 中
    copy(src.rbegin(), src.rend(), back_inserter(dst));

    // 打印 dst 验证结果
    cout << "dst 中的元素为: ";
    for (int val : dst)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
} 