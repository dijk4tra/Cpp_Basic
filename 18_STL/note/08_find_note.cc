#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * 常用算法说明：
 *
 * 这些算法大多定义在头文件：
 * #include <algorithm>
 *
 * STL 算法通常不会直接操作某一种具体容器，
 * 而是通过迭代器区间来处理数据。
 *
 * 常见形式：
 * algorithm(first, last, ...);
 *
 * 其中：
 * first：区间起始位置。
 * last：区间结束位置。
 *
 * 注意：
 * STL 中的区间一般都是左闭右开：[first, last)
 * 表示包含 first 指向的元素，
 * 不包含 last 指向的位置。
 */


/**
 * find：
 *
 * 在指定区间中查找等于目标值的元素。
 *
 * 函数形式：
 * find(first, last, value);
 *
 * 功能：
 * 从 [first, last) 区间中，
 * 查找第一个等于 value 的元素。
 *
 * 找到了：
 * 返回指向该元素的迭代器。
 *
 * 没找到：
 * 返回 last。
 *
 * 对容器来说，
 * last 通常就是 end()。
 */


/**
 * find_if：
 *
 * 按指定条件查找元素。
 *
 * 函数形式：
 * find_if(first, last, pred);
 * pred：一元谓词。
 *
 *
 * 一元谓词 unary predicate：
 * 1. 参数只有一个
 * 2. 返回值是 bool 类型
 * 3. 返回 true 表示当前元素满足条件
 *
 * 找到了：返回第一个满足条件的元素位置。
 * 没找到：返回 last。
 */


/**
 * replace：
 *
 * 将指定区间中等于旧值的元素替换为新值。
 *
 * 函数形式：
 *
 * replace(first, last, old_value, new_value);
 *
 * 功能：
 * 在 [first, last) 区间中，
 * 把所有等于 old_value 的元素替换为 new_value。
 *
 * 找到了就替换，
 * 没找到就不替换。
 */


/**
 * replace_if：
 *
 * 按条件进行替换。
 *
 * 函数形式：
 *
 * replace_if(first, last, pred, new_value);
 *
 * 功能：
 * 在 [first, last) 区间中，
 * 把所有满足 pred 条件的元素替换为 new_value。
 */


/**
 * remove：
 *
 * remove 的名字容易误导。
 *
 * 注意：
 * remove 并不会真正删除容器中的元素。
 *
 * 它做的是：
 *
 * 1. 把不需要删除的元素向前移动
 * 2. 返回新的“逻辑结尾”迭代器
 *
 *
 * 为什么 remove 不真正删除元素？
 *
 * 因为 STL 算法只通过迭代器操作区间，
 * 它不知道具体容器是什么，
 * 也不能直接改变容器的 size。
 *
 * 所以 remove 只能调整元素位置，
 * 不能改变容器大小。
 *
 *
 * 如果想真正删除元素，
 * 需要配合容器自己的 erase 使用。
 *
 * 这叫 erase-remove 惯用法：
 *
 * auto it = remove(box.begin(), box.end(), value);
 * box.erase(it, box.end());
 */


/**
 * remove_if：
 *
 * 带条件的 remove。
 *
 * 函数形式：
 *
 * remove_if(first, last, pred);
 *
 * 功能：
 * 把不满足删除条件的元素向前移动，
 * 把满足条件的元素移动到新的逻辑结尾之后。
 *
 * 返回值：
 * 新的逻辑结尾迭代器。
 *
 * 如果要真正删除，
 * 仍然需要配合 erase。
 */


/**
 * 集合算法：
 *
 * set_union：
 * 求两个有序集合的并集。
 *
 * set_intersection：
 * 求两个有序集合的交集。
 *
 * set_difference：
 * 求两个有序集合的差集。
 *
 * set_symmetric_difference：
 * 求两个有序集合的对称差集。
 *
 *
 * 注意：
 * 这些集合算法要求输入区间通常是有序的。
 */


void test1()
{
    /**
     * 创建 vector 容器。
     *
     * 元素为：
     * 1 2 3 3 4 5
     *
     * 注意：
     * 里面有两个 3。
     */
    vector<int> box{1, 2, 3, 3, 4, 5};

    /**
     * find(box.begin(), box.end(), 3);
     *
     * 含义：
     * 在 box 的 [begin, end) 区间中，
     * 查找第一个等于 3 的元素。
     *
     * 因为 find 只查找“第一个”匹配元素，
     * 所以返回的迭代器 it 指向第一个 3。
     *
     * 如果没有找到，
     * it 会等于 box.end()。
     */
    auto it = find(box.begin(), box.end(), 3);

    /**
     * 判断是否查找成功。
     *
     * 如果 it != box.end()，
     * 说明找到了目标元素。
     *
     * 如果 it == box.end()，
     * 说明没有找到。
     *
     * 注意：
     * 只有确认 it != box.end() 后，
     * 才能安全地解引用 *it。
     */
    if (it != box.end())
    {
        cout << "find it" << endl;
        cout << *it << endl;
    }

    /**
     * 当前 it 指向第一个 3。
     *
     * ++it 后，
     * it 向后移动一个位置，
     * 指向第二个 3。
     */
    ++it;
    cout << *it << endl;

    /**
     * 再次 ++it 后，
     * it 指向元素 4。
     */
    ++it;
    cout << *it << endl;
}


/**
 * 普通函数形式的一元谓词。
 *
 * 参数：
 * int num
 *
 * 返回值：
 * bool
 *
 * 作用：
 * 判断当前元素是否大于 3。
 *
 * 如果 num > 3，
 * 返回 true，
 * 表示当前元素满足条件。
 */
bool func(int num)
{
    return num > 3;
}


// 函数对象
/**
 * 函数对象形式的一元谓词。
 *
 * OverThree 重载了 operator()，
 * 所以它的对象可以像函数一样被调用。
 *
 * 例如：
 *
 * OverThree obj;
 * obj(5);
 *
 * 实际调用的是：
 *
 * obj.operator()(5);
 */
struct OverThree
{
    bool operator()(int num)
    {
        return num > 3;
    }
};


// find_if：找到了返回对应位置的迭代器，没找到返回 end()
void test2()
{
    vector<int> box{1, 2, 3, 3, 4, 5};

    /**
     * find_if 的第三个参数是一元谓词。
     *
     * 它会把区间中的元素依次传给这个谓词。
     *
     * 当谓词第一次返回 true 时，
     * find_if 就停止查找，
     * 并返回当前元素的位置。
     *
     *
     * 当前查找条件：
     * num > 3
     *
     * 在 1 2 3 3 4 5 中，
     * 第一个大于 3 的元素是 4。
     */

    // 使用普通函数作为判断条件
    // auto it = find_if(box.begin(), box.end(), func);

    // 使用函数指针作为判断条件
    // auto it = find_if(box.begin(), box.end(), &func);

    // 使用函数对象作为判断条件
    // auto it = find_if(box.begin(), box.end(), OverThree());

    /**
     * 使用 lambda 表达式作为判断条件。
     *
     * [](int num)->bool
     * {
     *     return num > 3;
     * }
     *
     * 表示：
     * 接收当前元素 num，
     * 如果 num 大于 3，就返回 true。
     */
    auto it = find_if(box.begin(), box.end(), 
        [](int num)->bool{
            return num > 3;
        }
    );

    /**
     * 找到的第一个满足条件的元素是 4。
     *
     * 注意：
     * 严谨写法中，解引用前最好判断：
     *
     * if (it != box.end())
     */
    cout << *it << endl;

    /**
     * ++it 后，
     * it 指向 5。
     */
    ++it;
    cout << *it << endl;
}


// replace：找到了就替换，没找到就不替换
void test3()
{
    /**
     * 创建 vector：
     * 1 2 3 3 4 5
     */
    vector<int> box{1, 2, 3, 3, 4, 5};

    /**
     * replace(box.begin(), box.end(), 3, 100);
     *
     * 含义：
     * 在 box 的 [begin, end) 区间中，
     * 把所有等于 3 的元素替换为 100。
     *
     *
     * 替换前：
     * 1 2 3 3 4 5
     *
     * 替换后：
     * 1 2 100 100 4 5
     */
    replace(box.begin(), box.end(), 3, 100);

    /**
     * 输出替换后的 vector。
     */
    std::copy(box.begin(), box.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


// replace_if：带条件的 replace
void test4()
{
    vector<int> box{1, 2, 3, 3, 4, 5};

    /**
     * replace_if：
     *
     * 按条件替换元素。
     *
     * 第三个参数是谓词，
     * 第四个参数是新值。
     *
     *
     * 当前条件：
     * num == 3
     *
     * 当前新值：
     * 100
     *
     * 所以所有等于 3 的元素都会被替换为 100。
     */
    replace_if(box.begin(), box.end(), [](int num)->bool{ return num == 3; }, 100);

    /**
     * 输出结果：
     * 1 2 100 100 4 5
     */
    std::copy(box.begin(), box.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


// remove：并不会真正删除元素
void test5()
{
    /**
     * 创建 vector：
     * 1 2 3 4 5
     */
    vector<int> box{1, 2, 3, 4, 5};

    /**
     * remove(box.begin(), box.end(), 3);
     *
     * 逻辑含义：
     * 删除区间中所有等于 3 的元素。
     *
     * 但注意：
     * remove 不会真正改变 vector 的 size。
     *
     *
     * 实际处理过程可以理解为：
     *
     * 原始数据：
     * 1 2 3 4 5
     *
     * 删除逻辑上的 3 后，
     * 不需要删除的元素向前移动：
     * 1 2 4 5 ?
     *
     * 新的逻辑有效区间是：
     * [begin, it)
     *
     * it 是 remove 返回的新逻辑结尾。
     */
    auto it = remove(box.begin(), box.end(), 3);

    /**
     * it 指向新的逻辑结尾位置。
     *
     * 一般不建议解引用 remove 返回的迭代器。
     *
     * 因为从 it 到 end() 之间的元素，
     * 已经不属于逻辑有效数据。
     *
     * 这里有些编译器环境下可能输出 5，
     * 但不能把它当成可靠结果。
     */
    cout << "it = " << *it << endl;

    /**
     * erase-remove 惯用法：
     *
     * remove：
     * 负责把不删除的元素移动到前面，
     * 并返回新的逻辑结尾 it。
     *
     * erase：
     * 负责真正删除 [it, box.end()) 区间中的元素，
     * 从而改变容器大小。
     *
     *
     * 执行后，
     * box 中真正只剩下：
     * 1 2 4 5
     */
    box.erase(it, box.end());

    std::copy(box.begin(), box.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


// remove_if：带条件的 remove
void test6()
{
    /**
     * 创建 vector：
     * 1 2 3 4 5
     */
    vector<int> box{1, 2, 3, 4, 5};

    /**
     * remove_if：
     *
     * 按条件进行逻辑删除。
     *
     * 第三个参数是谓词。
     *
     * 当前条件：
     * num > 3
     *
     * 表示逻辑删除所有大于 3 的元素。
     *
     *
     * 原始数据：
     * 1 2 3 4 5
     *
     * 逻辑删除大于 3 的元素后：
     * 1 2 3 ? ?
     *
     * remove_if 返回新的逻辑结尾。
     */
    auto it = remove_if(box.begin(), box.end(), 
        [](int num)->bool{
            return num > 3;
        }
    );

    /**
     * it 指向新的逻辑结尾。
     *
     * 一般不建议解引用 remove_if 返回的迭代器。
     *
     * 因为 it 到 end() 之间的元素，
     * 不再属于有效逻辑区间。
     */
    cout << "it = " << *it << endl;

    /**
     * 真正删除 [it, box.end()) 区间中的元素。
     *
     * 删除后，
     * box 中只剩：
     * 1 2 3
     */
    box.erase(it, box.end());

    // 输出结果：1 2 3
    std::copy(box.begin(), box.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


int main()
{
    /**
     * test1：
     * find 查找第一个等于目标值的元素。
     *
     * test2：
     * find_if 按条件查找元素。
     *
     * test3：
     * replace 把等于旧值的元素替换为新值。
     *
     * test4：
     * replace_if 按条件替换元素。
     *
     * test5：
     * remove 逻辑删除元素，
     * 需要配合 erase 真正删除。
     *
     * test6：
     * remove_if 按条件逻辑删除元素，
     * 也需要配合 erase 真正删除。
     */
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}