#include <iostream>
#include <vector>
#include <algorithm> // std::remove_if

using namespace std;

int main()
{
    vector<int> nums = {1, 5, 8, 3, 6, 9, 2, 7, 4};

    // 使用 remove_if 把 > 5 的元素“移走”，返回新结尾的迭代器
    auto new_end = remove_if(nums.begin(), nums.end(), 
        [](int x)
        {
            return x > 5; // Lambda 表达式：定义删除条件
        }
    );

    cout << "仅 remove_if 后的 nums: ";
    for (int n : nums)
    {
        cout << n << " ";  // 输出：1 5 3 2 4 9 2 7 4（>5 的元素被移到末尾，但仍在容器中）
    }
    cout << endl;

    // 使用 erase 真正从内存中擦除不需要的尾部元素
    nums.erase(new_end, nums.end());

    // 打印最终结果
    cout << "真正删除后的 nums: ";
    for (int n : nums)
    {
        cout << n << " ";  // 输出：1 5 3 2 4
    }
    cout << endl;

    return 0;
}