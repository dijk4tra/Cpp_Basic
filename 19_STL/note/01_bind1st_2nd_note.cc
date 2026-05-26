#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;


/*
 * std::bind1st / std::bind2nd
 *
 * 作用：
 * 将二元函数对象的某一个参数绑定为固定值，
 * 从而把“二元函数对象”适配成“一元函数对象”。
 *
 * 二元函数对象：
 * 需要两个参数才能调用，例如：
 * std::less<int>()(a, b)
 *
 * 一元函数对象：
 * 只需要一个参数就能调用，例如：
 * pred(x)
 *
 * 注意：
 * bind1st / bind2nd 是旧式函数适配器。
 * C++11 起已废弃，C++17 中已移除。
 * 新代码通常使用 lambda、std::bind 或其他方式替代。
 */

/*
 * std::less<int>
 *
 * std::less<int>() 是一个二元函数对象，
 * 等价于判断 lhs < rhs。
 *
 * 简化理解：
 *
 * struct less
 * {
 *     bool operator()(int lhs, int rhs) const
 *     {
 *         return lhs < rhs;
 *     }
 * };
 *
 *
 * bind1st(std::less<int>(), 3)
 *
 * 表示绑定第一个参数 lhs 为 3：
 *
 *     std::less<int>()(3, rhs)
 *
 * 等价于：
 *
 *     3 < rhs
 *
 * 所以它可以用来判断元素是否大于 3。
 *
 *
 * bind2nd(std::less<int>(), 3)
 *
 * 表示绑定第二个参数 rhs 为 3：
 *
 *     std::less<int>()(lhs, 3)
 *
 * 等价于：
 *
 *     lhs < 3
 *
 * 所以它可以用来判断元素是否小于 3。
 */


/*
 * 普通函数的默认参数示例：
 *
 * void func(int a = 1, int b = 2) {}
 *
 * 调用方式：
 *
 * func(1, 2);  // 传入两个参数
 * func(1);     // 第二个参数使用默认值
 * func();      // 两个参数都使用默认值
 *
 * 注意：
 * 默认参数和 bind1st / bind2nd 的作用不同。
 *
 * 默认参数是函数声明层面的默认值；
 * bind1st / bind2nd 是把二元函数对象适配成一元函数对象。
 */


void test1()
{
    vector<int> box {1,2,3,4,5};

    // 使用 remove_if 删除满足条件的元素
    //
    // remove_if 的第三个参数需要的是“一元谓词”：
    // 也就是接收一个参数，并返回 bool 值的可调用对象。
    //
    // std::less<int>() 是二元函数对象，需要两个参数：
    // std::less<int>()(lhs, rhs)
    //
    // 因此下面这样直接写会报错，因为参数个数不匹配：
    // auto it = std::remove_if(box.begin(), box.end(), std::less<int>());

    // 如果可以把二元函数对象转换成一元函数对象，
    // 就可以适配 remove_if 的参数要求。

    // 使用 bind1st 绑定 lhs 为 3：
    //
    // bind1st(std::less<int>(), 3)
    //
    // 等价于：
    // 3 < num
    //
    // 用在 remove_if 中时，表示删除大于 3 的元素。
    //
    // auto it = std::remove_if(box.begin(), box.end(), 
    //      bind1st(std::less<int>(), 3));

    // 使用 bind2nd 绑定 rhs 为 3：
    //
    // bind2nd(std::less<int>(), 3)
    //
    // 等价于：
    // num < 3
    //
    // 用在 remove_if 中时，表示删除小于 3 的元素。
    auto it = std::remove_if(box.begin(), box.end(), 
         bind2nd(std::less<int>(), 3));

    // remove_if 只是把不删除的元素前移，
    // 并返回新的逻辑结尾 it。
    //
    // erase 才是真正删除 [it, box.end()) 区间中的元素。
    box.erase(it, box.end());

    // 打印删除后的结果
    // 当前代码删除的是小于 3 的元素，因此输出：3 4 5
    std::for_each(box.begin(), box.end(),
        [](int num){
            cout << num << " ";
        }
    );

    cout << endl;
}


int main(int argc, char const *argv[])
{
    test1();

    return 0;
}