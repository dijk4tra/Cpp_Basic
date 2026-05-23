#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <unordered_set>

using namespace std;

/**
 * 迭代器分类
 *
 * 1. 输出迭代器 output iterator
 *    主要用于写操作，例如：*it = 100
 *
 * 2. 输入迭代器 input iterator
 *    主要用于读操作，例如：cout << *it
 *
 * 3. 前向迭代器 forward iterator
 *    只能向前移动，支持 ++it
 *    不能反向移动，不支持 --it
 *
 * 4. 双向迭代器 bidirectional iterator
 *    可以向前、向后移动，支持 ++it 和 --it
 *    但不能随机跳转，不支持 it += n
 *
 * 5. 随机访问迭代器 random access iterator
 *    功能最强，支持前面几类迭代器的操作
 *    还支持随机访问，例如：it += 3、it -= 3、it[n]
 *
 *
 * 常见容器对应的迭代器类型：
 *
 * 1. 无序关联式容器
 *    unordered_set、unordered_map 等：前向迭代器
 *
 * 2. 有序关联式容器
 *    set、map、multiset、multimap 等：双向迭代器
 *
 * 3. 顺序容器
 *    vector、deque：随机访问迭代器
 *    list：双向迭代器
 *
 * 4. 容器适配器
 *    stack、queue、priority_queue 不提供迭代器
 *    因此不能使用 begin()、end() 进行遍历
 */

// 从容器中获取迭代器

// unordered_set : 前向迭代器
void test1()
{
    unordered_set<int> box{1,2,3,4,5};

    // begin() 获取指向容器中某个元素的迭代器
    // 注意：unordered_set 是无序容器，元素的遍历顺序不一定是插入顺序
    auto it = box.begin();

    // 前向迭代器支持向前移动
    ++it;
    ++it;

    // 前向迭代器不支持反向移动
    // it--; // 错误，前向迭代器不能往左移动

    cout << *it << endl;
}

// list : 双向迭代器
void test2()
{
    list<int> box{1,2,3,4,5};

    auto it = box.begin();

    // list 的迭代器支持双向移动
    ++it;
    ++it;
    --it;

    // 通过迭代器修改元素
    *it = 100; // 写操作

    // 通过迭代器读取元素
    cout << *it << endl;

    // list 的迭代器是双向迭代器，不支持随机访问
    // it += 3; // 错误，双向迭代器不能随机访问，只能单步移动
}

// vector : 随机访问迭代器
void test3()
{
    vector<int> box{1,2,3,4,5};

    auto it = box.begin();

    // vector 的迭代器支持双向移动
    ++it;
    ++it;
    --it;

    // 通过迭代器修改元素
    *it = 100; // 写操作

    // 通过迭代器读取元素
    cout << *it << endl; // 读操作

    // vector 的迭代器是随机访问迭代器，支持直接跳转
    it += 3; // 可以随机访问

    cout << *it << endl;
}


int main(int argc, char *argv[])
{
    // test1();
    // test2();
    test3();

    return 0;
}