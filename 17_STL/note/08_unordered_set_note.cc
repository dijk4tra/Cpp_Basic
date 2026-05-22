#include <iostream>
#include <unordered_set>

using namespace std;

/**
 * 无序关联式容器：
 *
 * STL 中的关联式容器可以分为两类：
 *
 * 1. 有序关联式容器
 *    set、multiset、map、multimap
 *
 *    特点：
 *    底层通常使用红黑树实现，
 *    元素会按照 key 的比较规则自动排序。
 *
 * 2. 无序关联式容器
 *    unordered_set、unordered_multiset、
 *    unordered_map、unordered_multimap
 *
 *    特点：
 *    底层通常使用哈希表实现，
 *    元素不会按照大小自动排序。
 *
 *
 * unordered_set：
 * - 无序集合容器
 * - 元素唯一，不能重复
 * - 底层通常使用哈希表实现
 * - 元素不会按照大小自动排序
 *
 *
 * unordered_multiset：
 * - 无序多集合容器
 * - 元素可以重复
 * - 底层通常使用哈希表实现
 *
 *
 * unordered_map：
 * - 无序映射容器
 * - 存储 key-value 键值对
 * - key 唯一，不能重复
 * - 底层通常使用哈希表实现
 *
 *
 * unordered_multimap：
 * - 无序多映射容器
 * - 存储 key-value 键值对
 * - key 可以重复
 * - 底层通常使用哈希表实现
 *
 *
 * 注意：
 * 1. 无序关联式容器不按照大小排序
 *    也不会按照插入顺序保存元素。
 *
 * 2. 元素的输出顺序与插入顺序无关
 *    输出顺序由哈希表内部的存储结构决定，
 *    不同编译器、不同环境下可能不同。
 *
 * 3. 查找、插入、删除的平均时间复杂度通常是 O(1)
 *    但是在哈希冲突较多的情况下，
 *    最坏情况可能退化为 O(N)。
 */

template<typename Container>
void print(Container &box)
{
    /**
     * 范围 for 遍历容器
     *
     * auto & e：
     * 1. auto
     *    自动推导容器中元素的类型。
     *
     * 2. &
     *    使用引用接收元素，避免拷贝。
     *
     * 对于 unordered_set 来说，
     * 遍历顺序是不确定的。
     *
     * 它既不是插入顺序，
     * 也不是从小到大的排序顺序。
     */
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

// unordered_set 容器的构建
void test1()
{
    /**
     * 初始化列表构造
     *
     * 使用 {} 中给出的元素初始化 unordered_set。
     *
     * 注意：
     * unordered_set 中元素不能重复。
     *
     * 这里出现了两个 3，
     * 但是最终只会保留一个 3。
     */
    unordered_set<int> box {3, 3, 1, 2, 4, 5};

    print(box);

    /**
     * unordered_set 中元素无序，不能重复。
     *
     * 输出顺序不一定是插入顺序，
     * 也不一定是升序。
     *
     * 例如：
     * 插入顺序是 3、3、1、2、4、5，
     * 但是输出结果可能不是这个顺序。
     */
}

// unordered_set 基本操作
void test2()
{
    /**
     * 无参构造
     *
     * 创建一个空的 unordered_set<int> 容器。
     */
    unordered_set<int> box;

    /**
     * 插入元素
     *
     * insert 用来向 unordered_set 中插入元素。
     *
     * unordered_set 不允许重复元素，
     * 如果插入已经存在的元素，
     * 插入会失败。
     *
     * 和 set 不同：
     * unordered_set 不会按照大小排序。
     */
    box.insert(1);
    box.insert(2);
    box.insert(3);

    /**
     * count 函数
     *
     * 作用：
     * 统计某个元素在容器中出现的次数。
     *
     * 对于 unordered_set 来说，
     * 元素不允许重复，
     * 所以 count 的结果只可能是：
     * 1. 找到，返回 1
     * 2. 没找到，返回 0
     */
    int result = box.count(3);

    /**
     * erase 删除元素
     *
     * 这里调用的是：
     * erase(iterator pos)
     *
     * 作用：
     * 删除指定迭代器位置的元素。
     *
     * box.begin()：
     * 返回指向 unordered_set 中某个元素的迭代器。
     *
     * 注意：
     * 因为 unordered_set 是无序的，
     * 所以 begin() 指向的元素不一定是最小值，
     * 也不一定是最先插入的元素。
     */
    box.erase(box.begin());

    /**
     * 其他常见操作与 set 类似：
     *
     * find()
     * 查找元素。
     * 找到返回指向该元素的迭代器，
     * 未找到返回 end()。
     *
     * erase(value)
     * 按值删除元素。
     *
     * size()
     * 获取容器中元素的个数。
     *
     * empty()
     * 判断容器是否为空。
     */
}

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}