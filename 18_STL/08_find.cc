#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * 常用算法说明：
 *
 * find：
 * 在指定区间中查找等于目标值的元素。
 * 找到了返回对应位置的迭代器，没找到返回 end()。
 *
 * find_if：
 * 按指定条件查找元素。
 * 找到了返回对应位置的迭代器，没找到返回 end()。
 *
 * replace：
 * 将指定区间中等于旧值的元素替换为新值。
 * 找到了就替换，没找到就不替换。
 *
 * replace_if：
 * 按条件进行替换。
 * 满足条件的元素会被替换为新值。
 *
 * remove：
 * 并不会真正删除容器中的元素。
 * 它会把不需要删除的元素向前移动，
 * 并返回新的“逻辑结尾”迭代器。
 *
 * remove_if：
 * 带条件的 remove。
 * 满足条件的元素会被移到逻辑结尾之后。
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
 */

void test1()
{
    vector<int> box{1, 2, 3, 3, 4, 5};

    // find 在 [begin, end) 区间中查找第一个等于 3 的元素
    auto it = find(box.begin(), box.end(), 3);

    // 判断是否查找成功
    if (it != box.end())
    {
        cout << "find it" << endl;
        cout << *it << endl;
    }

    // 当前 it 指向第一个 3
    // 向后移动后，指向第二个 3
    ++it;
    cout << *it << endl;

    // 再向后移动后，指向 4
    ++it;
    cout << *it << endl;
}


bool func(int num)
{
    return num > 3;
}

// 函数对象
struct OverThree
{
    bool operator()(int num)
    {
        return num > 3;
    }
};

// find_if：找到了返回对应位置的迭代器，没找到返回 end()
//
// 第三个参数是一元谓词：
// 1. 参数只有一个
// 2. 返回值是 bool 类型
// 3. 返回 true 表示当前元素满足查找条件
void test2()
{
    vector<int> box{1, 2, 3, 3, 4, 5};

    // 使用普通函数作为判断条件
    // auto it = find_if(box.begin(), box.end(), func);

    // 使用函数指针作为判断条件
    // auto it = find_if(box.begin(), box.end(), &func);

    // 使用函数对象作为判断条件
    // auto it = find_if(box.begin(), box.end(), OverThree());

    // 使用 lambda 表达式作为判断条件
    // 查找第一个大于 3 的元素
    auto it = find_if(box.begin(), box.end(), 
        [](int num)->bool{
            return num > 3;
        }
    );

    // 找到的第一个满足条件的元素是 4
    cout << *it << endl;

    // 向后移动后，指向 5
    ++it;
    cout << *it << endl;
}


// replace：找到了就替换，没找到就不替换
void test3()
{
    vector<int> box{1, 2, 3, 3, 4, 5};

    // 将区间中所有等于 3 的元素替换为 100
    replace(box.begin(), box.end(), 3, 100);

    // 输出结果：1 2 100 100 4 5
    std::copy(box.begin(), box.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


// replace_if：带条件的 replace
void test4()
{
    vector<int> box{1, 2, 3, 3, 4, 5};

    // 将区间中所有满足 num == 3 的元素替换为 100
    replace_if(box.begin(), box.end(), [](int num)->bool{ return num == 3; }, 100);

    // 输出结果：1 2 100 100 4 5
    std::copy(box.begin(), box.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


// remove：并不会真正删除元素
//
// remove 的处理过程：
// 1. 将不等于目标值的元素向前(右)移动
// 2. 返回新的逻辑结尾迭代器
//
// 注意：
// remove 后，容器的实际 size 不会改变。
// 如果想真正删除元素，需要配合容器的 erase() 使用。
void test5()
{
    vector<int> box{1, 2, 3, 4, 5};

    // 删除逻辑上的 3
    // 返回值 it 是新的逻辑结尾
    auto it = remove(box.begin(), box.end(), 3);

    // it 指向新的逻辑结尾位置
    // 该位置之后的元素不再属于有效逻辑区间
    // 一般不建议解引用 remove 返回的迭代器
    cout << "it = " << *it << endl; // 这里可能输出 5

    // 这里需要结合 erase 算法一起使用
    // 否则下面直接输出整个 vector，可能得到：1 2 4 5 5
    //
    // erase-remove 惯用法：
    // remove 负责移动元素并返回新的逻辑结尾
    // erase 负责真正删除 [it, end) 区间中的元素
    box.erase(it, box.end());

    std::copy(box.begin(), box.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


// remove_if：带条件的 remove
void test6()
{
    vector<int> box{1, 2, 3, 4, 5};

    // 将不满足条件的元素向前移动
    // 满足 num > 3 的元素被移动到新的逻辑结尾之后
    auto it = remove_if(box.begin(), box.end(), 
        [](int num)->bool{
            return num > 3;
        }
    );

    // it 指向新的逻辑结尾
    // 一般不建议解引用 remove_if 返回的迭代器
    cout << "it = " << *it << endl;

    // 这里需要结合 erase 算法一起使用
    // 真正删除 [it, box.end()) 区间中的元素
    box.erase(it, box.end());

    // 输出结果：1 2 3
    std::copy(box.begin(), box.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}



int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}