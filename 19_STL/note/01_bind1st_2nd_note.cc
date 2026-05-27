#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;


/**
 * STL 算法适配器：bind1st / bind2nd
 *
 * 在 STL 中，很多算法要求传入特定形式的函数对象。
 * 例如：
 * remove_if 的第三个参数要求是“一元谓词”。
 *
 * 一元谓词 unary predicate：
 * 只接收一个参数，并且返回 bool 值的可调用对象。
 *
 * 例如：
 * [](int num) {
 *     return num < 3;
 * }
 *
 * 这个 lambda 只接收一个参数 num，
 * 返回值是 bool，所以它就是一元谓词。
 *
 *
 * 二元函数对象 binary function object：
 * 需要两个参数才能调用的函数对象。
 *
 * 例如：
 * std::less<int>()(lhs, rhs)
 *
 * std::less<int>() 用来判断：
 * lhs < rhs
 *
 *
 * 问题：
 * remove_if 需要一元谓词，
 * 但是 std::less<int>() 是二元函数对象，
 * 二者参数个数不匹配。
 *
 * 解决方式：
 * 使用 bind1st 或 bind2nd，
 * 把二元函数对象的某一个参数绑定成固定值，
 * 从而把二元函数对象适配成一元函数对象。
 *
 *
 * bind1st / bind2nd 的作用：
 * 1. bind1st
 *    绑定 binary function object 的第一个参数。
 *
 *    例如：
 *    bind1st(std::less<int>(), 3)
 *
 *    原本 std::less<int>() 需要两个参数：
 *    std::less<int>()(lhs, rhs)
 *
 *    bind1st 绑定 lhs 为 3 之后，
 *    就变成：
 *    std::less<int>()(3, rhs)
 *
 *    等价于：
 *    3 < rhs
 *
 *    所以可以用来判断元素是否大于 3。
 *
 *
 * 2. bind2nd
 *    绑定 binary function object 的第二个参数。
 *
 *    例如：
 *    bind2nd(std::less<int>(), 3)
 *
 *    原本 std::less<int>() 需要两个参数：
 *    std::less<int>()(lhs, rhs)
 *
 *    bind2nd 绑定 rhs 为 3 之后，
 *    就变成：
 *    std::less<int>()(lhs, 3)
 *
 *    等价于：
 *    lhs < 3
 *
 *    所以可以用来判断元素是否小于 3。
 *
 *
 * 注意：
 * bind1st / bind2nd 是旧式函数适配器。
 * C++11 起已废弃，C++17 中已移除。
 *
 * 在新代码中，更推荐使用 lambda 表达式。
 *
 * 例如：
 * [](int num) {
 *     return num < 3;
 * }
 *
 * 这种写法更直观，也不依赖旧式适配器。
 */


/**
 * std::less<int>
 *
 * std::less<int> 是 STL 提供的函数对象。
 * 它的作用类似于“小于号 <”。
 *
 * 可以简单理解为：
 *
 * struct less
 * {
 *     bool operator()(int lhs, int rhs) const
 *     {
 *         return lhs < rhs;
 *     }
 * };
 *
 * 所以：
 *
 * std::less<int>()(1, 2)
 *
 * 等价于：
 *
 * 1 < 2
 *
 *
 * std::less<int>() 本身需要两个参数，
 * 因此它是一个二元函数对象。
 *
 * 如果某个算法只接收一个参数的函数对象，
 * 就不能直接传入 std::less<int>()。
 */


/**
 * 默认参数和 bind1st / bind2nd 的区别
 *
 * 普通函数可以设置默认参数。
 *
 * 例如：
 * void func(int a = 1, int b = 2)
 * {
 * }
 *
 * 调用方式：
 * func(1, 2);  // a = 1, b = 2
 * func(1);     // a = 1, b 使用默认值 2
 * func();      // a 和 b 都使用默认值
 *
 *
 * 默认参数：
 * 是函数声明层面的默认值。
 * 它解决的是“调用函数时可以少传参数”的问题。
 *
 *
 * bind1st / bind2nd：
 * 是函数对象适配器。
 * 它解决的是“算法要求的函数对象形式不匹配”的问题。
 *
 * 例如：
 * remove_if 需要一元谓词，
 * 而 std::less<int>() 是二元函数对象。
 *
 * bind1st / bind2nd 可以固定其中一个参数，
 * 从而把二元函数对象转换成一元函数对象。
 */


void test1()
{
    // 创建一个 vector 容器
    // box 中保存了 1、2、3、4、5 这几个整数
    vector<int> box {1, 2, 3, 4, 5};

    /**
     * std::remove_if
     *
     * remove_if 是 STL 算法。
     *
     * 作用：
     * 把满足条件的元素“移到逻辑尾部”，
     * 并返回新的逻辑结尾位置。
     *
     * 语法：
     * remove_if(first, last, pred)
     *
     * 参数：
     * 1. first
     *    起始迭代器。
     *
     * 2. last
     *    结束迭代器。
     *
     * 3. pred
     *    判断条件。
     *    pred 必须是一元谓词，
     *    也就是只接收一个元素作为参数，
     *    并返回 bool 值。
     *
     *
     * 注意：
     * remove_if 不会真正删除容器中的元素。
     *
     * 它只是把不需要删除的元素往前移动，
     * 然后返回一个新的逻辑结尾。
     *
     * 真正删除元素，需要再配合 erase。
     */

    /**
     * 错误示例：
     *
     * auto it = std::remove_if(box.begin(), box.end(), std::less<int>());
     *
     * 这行代码不能通过编译。
     *
     * 原因：
     * remove_if 的第三个参数需要一元谓词，
     * 也就是类似下面这样的可调用对象：
     *
     * pred(num)
     *
     * 但是 std::less<int>() 是二元函数对象，
     * 调用时需要两个参数：
     *
     * std::less<int>()(lhs, rhs)
     *
     * 参数个数不匹配，所以不能直接传入。
     */


    /**
     * bind1st 示例：
     *
     * bind1st(std::less<int>(), 3)
     *
     * 表示绑定 std::less<int>() 的第一个参数 lhs 为 3。
     *
     * 原来的调用形式是：
     * std::less<int>()(lhs, rhs)
     *
     * 绑定第一个参数之后变成：
     * std::less<int>()(3, rhs)
     *
     * 等价于：
     * 3 < rhs
     *
     * 在 remove_if 中，rhs 就是当前遍历到的元素。
     *
     * 所以：
     * bind1st(std::less<int>(), 3)
     *
     * 表示判断当前元素是否大于 3。
     *
     * 如果返回 true，
     * remove_if 就会把该元素视为需要删除的元素。
     *
     * 因此下面这行代码的含义是：
     * 删除所有大于 3 的元素。
     */
    /*
    auto it = std::remove_if(box.begin(), box.end(),
                             bind1st(std::less<int>(), 3));
    */


    /**
     * bind2nd 示例：
     *
     * bind2nd(std::less<int>(), 3)
     *
     * 表示绑定 std::less<int>() 的第二个参数 rhs 为 3。
     *
     * 原来的调用形式是：
     * std::less<int>()(lhs, rhs)
     *
     * 绑定第二个参数之后变成：
     * std::less<int>()(lhs, 3)
     *
     * 等价于：
     * lhs < 3
     *
     * 在 remove_if 中，lhs 就是当前遍历到的元素。
     *
     * 所以：
     * bind2nd(std::less<int>(), 3)
     *
     * 表示判断当前元素是否小于 3。
     *
     * 如果当前元素小于 3，
     * 谓词返回 true，
     * remove_if 就会把它视为需要删除的元素。
     *
     * 因此下面这行代码的含义是：
     * 删除所有小于 3 的元素。
     */
    auto it = std::remove_if(box.begin(), box.end(),
                             bind2nd(std::less<int>(), 3));

    /**
     * erase-remove 惯用法
     *
     * remove_if 并不会真正缩小 vector 的大小。
     * 它只是把不需要删除的元素移动到前面，
     * 然后返回新的逻辑结尾 it。
     *
     * 区间 [it, box.end()) 中的元素，
     * 就是逻辑上应该被删除的元素。
     *
     * 所以需要调用 erase：
     *
     * box.erase(it, box.end());
     *
     * 这样才会真正删除这些元素，
     * 并改变 vector 的大小。
     */
    box.erase(it, box.end());

    /**
     * std::for_each
     *
     * for_each 是 STL 算法。
     *
     * 作用：
     * 遍历指定区间中的每一个元素，
     * 并对每个元素执行指定操作。
     *
     * 这里使用 lambda 表达式打印每个元素。
     *
     * 当前代码中，remove_if 删除的是小于 3 的元素，
     * 所以原来的：
     * 1 2 3 4 5
     *
     * 删除之后剩下：
     * 3 4 5
     */
    std::for_each(box.begin(), box.end(),
        [](int num) {
            cout << num << " ";
        }
    );

    cout << endl;
}


int main(int argc, char const *argv[])
{
    // 调用测试函数
    test1();

    return 0;
}