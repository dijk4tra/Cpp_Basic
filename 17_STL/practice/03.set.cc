#include <iostream>
#include <set>

using namespace std;

int main()
{
    int n, m;
    // 读取集合 A 和 B 的元素个数
    if(!(cin >> n >> m)) return 0;

    set<int> union_set;
    int element;

    // 读取集合 A 的所有元素并插入 set
    for (int i = 0; i < n; i++)
    {
        cin >> element;
        union_set.insert(element);
    }

    // 读取集合 B 的所有元素并插入 set
    for (int i = 0; i < m ; i++)
    {
        cin >> element;
        union_set.insert(element); // 重复的元素会被 set 自动过滤
    }

    // 输出集合 A 和 B 的并集
    bool first = true;
    for (int num : union_set)
    {
        if (!first)
        {
            cout << " "; // 元素之间用空格隔开
        }
        cout << num;
        first = false;
    }
    cout << endl;

    return 0;
}