#include <iostream>
#include <unordered_set>

using namespace std;

/**
 * 无序关联式容器：哈希表
 *
 * unordered_set：
 * - 无序集合容器
 * - 元素唯一，不能重复
 * - 底层通常使用哈希表实现
 * - 元素不会按照大小自动排序
 *
 * unordered_multiset：
 * - 无序多集合容器
 * - 元素可以重复
 * - 底层通常使用哈希表实现
 *
 * unordered_map：
 * - 无序映射容器
 * - 存储 key-value 键值对
 * - key 唯一，不能重复
 * - 底层通常使用哈希表实现
 *
 * unordered_multimap：
 * - 无序多映射容器
 * - 存储 key-value 键值对
 * - key 可以重复
 * - 底层通常使用哈希表实现
 *
 * 注意：
 * - 无序关联式容器不按照大小排序
 * - 元素的输出顺序与插入顺序无关
 * - 查找、插入、删除的平均时间复杂度通常是 O(1)
 */

template<typename Container>
void print(Container &box)
{
    // 遍历容器中的所有元素
    // unordered_set 的遍历顺序是不确定的
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

// unordered_set 容器的构建
void test1()
{
    // 初始化列表构造
    // unordered_set 中元素不能重复，所以重复的 3 只会保留一个
    unordered_set<int> box {3, 3, 1, 2, 4, 5};

    print(box); 

    // unordered_set 中元素无序，不能重复
    // 输出顺序不一定是插入顺序，也不一定是升序
}

// unordered_set 基本操作
void test2()
{
    // 无参构造，创建一个空的 unordered_set
    unordered_set<int> box;

    // 插入元素
    box.insert(1);
    box.insert(2);
    box.insert(3);

    // count：
    // 对于 unordered_set 来说，元素不重复
    // 找到返回 1，未找到返回 0
    int result = box.count(3);

    // erase：
    // 删除指定迭代器位置的元素
    box.erase(box.begin());

    // 其他常见操作与 set 类似：
    // find() 查找元素
    // erase(value) 按值删除元素
    // size() 获取元素个数
    // empty() 判断是否为空
}

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}