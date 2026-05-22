#include <iostream>
#include <unordered_set>

using namespace std;

/**
 * 无序关联式容器 unordered_multiset：
 * - unordered_multiset 是无序多集合容器
 * - 元素可以重复
 * - 底层通常使用哈希表实现
 * - 元素不会按照大小自动排序
 *
 * unordered_set 和 unordered_multiset 的区别：
 * - unordered_set：元素唯一，不能重复
 * - unordered_multiset：元素可以重复
 *
 * 注意：
 * - 输出顺序不一定是插入顺序
 * - 输出顺序也不一定是升序
 * - 查找、插入、删除的平均时间复杂度通常是 O(1)
 */

template<typename Container>
void print(Container &box)
{
    // 遍历容器中的所有元素
    // unordered_multiset 的遍历顺序是不确定的
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

// unordered_multiset 容器的构建
void test1()
{
    // 初始化列表构造
    // unordered_multiset 允许元素重复，所以两个 3 都可以被保存
    unordered_multiset<int> box {3,3, 1,2,4,5};

    print(box); // 可能输出：5 4 2 1 3 3

    // 存储的元素无序，元素可以重复
    // 实际输出顺序与编译器实现、哈希桶分布等因素有关
}

// unordered_multiset 基本操作
void test2()
{
    // 无参构造，创建一个空的 unordered_multiset
    unordered_multiset<int> box;

    // 插入元素
    // unordered_multiset 允许插入重复元素
    box.insert(1);
    box.insert(2);
    box.insert(3);

    // count：
    // 对于 unordered_multiset 来说，元素可以重复
    // 找到返回该元素出现的次数，未找到返回 0
    int rusult = box.count(3);

    // erase：
    // 删除指定迭代器位置的元素
    box.erase(box.begin());

    // 其他常见操作与 unordered_set 类似：
    // find() 查找元素
    // erase(value) 按值删除元素
    // size() 获取元素个数
    // empty() 判断是否为空
    //
    // unordered_multiset 针对自定义类型的处理方式
    // 和 unordered_set 一样：
    // 需要提供哈希函数和相等判断规则
}

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}