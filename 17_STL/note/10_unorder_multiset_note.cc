#include <iostream>
#include <unordered_set>

using namespace std;

/**
 * 无序关联式容器 unordered_multiset：
 *
 * unordered_multiset 是 STL 中的无序关联式容器。
 *
 * 特点：
 * 1. unordered_multiset 是无序多集合容器
 *    只保存 key，不保存 value。
 *
 * 2. 元素可以重复
 *    相同元素可以保存多份。
 *
 * 3. 底层通常使用哈希表实现
 *    查找、插入、删除的平均时间复杂度通常是 O(1)。
 *
 * 4. 元素不会按照大小自动排序
 *    遍历时的输出顺序不是插入顺序，
 *    也不是升序或者降序。
 *
 *
 * unordered_set 和 unordered_multiset 的区别：
 * 1. unordered_set
 *    元素唯一，不能重复。
 *
 * 2. unordered_multiset
 *    元素可以重复。
 *
 *
 * 注意：
 * 1. 输出顺序不一定是插入顺序。
 *
 * 2. 输出顺序也不一定是升序。
 *
 * 3. 输出顺序与编译器实现、哈希桶分布等因素有关。
 *
 * 4. 查找、插入、删除的平均时间复杂度通常是 O(1)，
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
     * 对于 unordered_multiset 来说，
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

// unordered_multiset 容器的构建
void test1()
{
    /**
     * 初始化列表构造
     *
     * 使用 {} 中给出的元素初始化 unordered_multiset。
     *
     * unordered_multiset 允许元素重复。
     *
     * 这里出现了两个 3，
     * 最终两个 3 都可以被保存。
     */
    unordered_multiset<int> box {3,3, 1,2,4,5};

    /**
     * 输出 unordered_multiset 中的元素。
     *
     * 注意：
     * unordered_multiset 是无序容器，
     * 所以输出顺序是不确定的。
     *
     * 可能输出：
     * 5 4 2 1 3 3
     *
     * 也可能是其他顺序。
     */
    print(box);

    /**
     * unordered_multiset 中存储的元素无序，
     * 并且元素可以重复。
     *
     * 实际输出顺序与编译器实现、
     * 哈希桶分布、插入元素的哈希值等因素有关。
     */
}

// unordered_multiset 基本操作
void test2()
{
    /**
     * 无参构造
     *
     * 创建一个空的 unordered_multiset<int> 容器。
     */
    unordered_multiset<int> box;

    /**
     * 插入元素
     *
     * insert 用来向 unordered_multiset 中插入元素。
     *
     * unordered_multiset 允许插入重复元素。
     *
     * 和 unordered_set 不同：
     * unordered_set 插入重复元素会失败，
     * unordered_multiset 插入重复元素一般会成功。
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
     * 对于 unordered_multiset 来说，
     * 元素允许重复，
     * 所以 count 的结果可能大于 1。
     *
     * 找到：
     * 返回该元素出现的次数。
     *
     * 未找到：
     * 返回 0。
     *
     * 注意：
     * 原代码中的变量名 rusult 应该是 result，
     * 不过 rusult 只是变量名拼写问题，不影响编译。
     */
    int rusult = box.count(3);

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
     * 返回指向 unordered_multiset 中某个元素的迭代器。
     *
     * 注意：
     * 因为 unordered_multiset 是无序的，
     * 所以 begin() 指向的元素不一定是最小值，
     * 也不一定是最先插入的元素。
     */
    box.erase(box.begin());

    /**
     * 其他常见操作与 unordered_set 类似：
     *
     * find()
     * 查找元素。
     * 找到返回指向该元素的迭代器，
     * 未找到返回 end()。
     *
     * erase(value)
     * 按值删除元素。
     *
     * 对于 unordered_multiset 来说，
     * erase(value) 会删除所有等于 value 的元素。
     *
     * size()
     * 获取容器中元素的个数。
     *
     * empty()
     * 判断容器是否为空。
     *
     *
     * unordered_multiset 针对自定义类型的处理方式
     * 和 unordered_set 一样：
     *
     * 1. 需要提供哈希函数
     *    用来计算对象的哈希值。
     *
     * 2. 需要提供相等判断规则
     *    用来判断两个对象是否是相同元素。
     */
}

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}