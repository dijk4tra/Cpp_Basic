#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

/**
 * 无序关联式容器 unordered_multimap：
 *
 * unordered_multimap 是 STL 中的无序关联式容器。
 *
 * 特点：
 * 1. unordered_multimap 用来存储 key-value 键值对
 *    key 表示键，value 表示值。
 *
 * 2. key 可以重复
 *    同一个 key 可以对应多个 value。
 *
 * 3. value 可以重复
 *    不同的 key 可以对应相同的 value。
 *
 * 4. 底层通常使用哈希表实现
 *    查找、插入、删除的平均时间复杂度通常是 O(1)。
 *
 * 5. 元素不会按照 key 自动排序
 *    遍历时的输出顺序不是插入顺序，
 *    也不是 key 的升序或者降序。
 *
 *
 * unordered_map 和 unordered_multimap 的区别：
 * 1. unordered_map
 *    key 唯一，不能重复。
 *
 * 2. unordered_multimap
 *    key 可以重复。
 *
 *
 * 注意：
 * 1. 输出顺序不一定是插入顺序。
 *
 * 2. 输出顺序也不一定是 key 的升序。
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
     * unordered_multimap 中的每一个元素都是 pair<const Key, Value>
     *
     * pair 可以理解为一个保存两个数据的对象。
     *
     * e.first：
     * 表示 key。
     *
     * e.second：
     * 表示 value。
     *
     * 注意：
     * unordered_multimap 中的 key 是 const 的，
     * 不能通过迭代器直接修改 key。
     *
     * 原因：
     * unordered_multimap 底层需要根据 key 的哈希值
     * 维护哈希表结构。
     *
     * 如果允许直接修改 key，
     * 可能会导致元素所在的哈希桶位置不正确。
     */
    for(auto & e : box)
    {
        cout << e.first << " " << e.second << " " << endl;
    }
    cout << endl;
}

// unordered_multimap 容器的特点
void test1()
{
    /**
     * 初始化列表构造
     *
     * 每个元素都是一个 key-value 键值对。
     *
     * 注意：
     * unordered_multimap 的 key 可以重复。
     *
     * 下面出现了两个 key 为 "zs" 的键值对，
     * 最终两个都会被保存。
     */
    unordered_multimap<string,int> box{
        {"zs", 18},
        {"zs", 18},  // key 可以重复，所以两个 "zs" 都可以保存
        {"ls", 20},
        {"ww", 19},
    };

    print(box);

    /*
    可能的输出结果：
    ls 20
    ww 19
    zs 18
    zs 18

    unordered_multimap 的特点：
    1. 数据无序
       不按照插入顺序保存。

    2. key 可以重复
       同一个 key 可以对应多个 value。

    3. 输出顺序与插入顺序无关，
       也不保证按照 key 升序输出。
    */
}

// unordered_multimap 基本操作
void test2()
{
    /**
     * 无参构造
     *
     * 创建一个空的 unordered_multimap<string, int> 容器。
     *
     * string：
     * 表示 key 的类型。
     *
     * int：
     * 表示 value 的类型。
     */
    unordered_multimap<string,int> box;

    /**
     * 插入元素
     *
     * unordered_multimap 中保存的是 key-value 键值对，
     * 所以插入时需要插入 pair 类型的数据。
     *
     * unordered_multimap 允许 key 重复。
     *
     * 和 unordered_map 不同：
     * unordered_map 插入重复 key 会失败，
     * unordered_multimap 插入重复 key 一般会成功。
     */
    box.insert({"zs", 20});
    box.insert({"zs", 20});
    box.insert({"ls", 19});
    box.insert({"ww", 18});

    /**
     * count 函数
     *
     * 作用：
     * 统计某个 key 在 unordered_multimap 中出现的次数。
     *
     * 对于 unordered_multimap 来说，
     * key 允许重复，
     * 所以 count 的结果可能大于 1。
     *
     * 找到：
     * 返回该 key 对应元素的个数。
     *
     * 未找到：
     * 返回 0。
     *
     * 注意：
     * 原代码中的变量名 rusult 应该是 result，
     * 不过 rusult 只是变量名拼写问题，不影响编译。
     */
    int rusult = box.count("zs");

    /**
     * erase 删除元素
     *
     * 可以通过迭代器删除元素：
     * box.erase(box.begin());
     *
     * 也可以通过 key 删除元素：
     * box.erase("zs");
     *
     * 对于 unordered_multimap 来说，
     * erase("zs") 会删除所有 key 等于 "zs" 的键值对。
     *
     * 当前代码中删除语句被注释掉了。
     */
    // box.erase(box.begin());

    print(box);

    cout << "-------" << endl;

    /**
     * unordered_multimap 不支持 operator[]
     *
     * 原因：
     * unordered_multimap 的 key 可以重复。
     *
     * 同一个 key 可能对应多个 value。
     *
     * 例如：
     * {"zs", 20}
     * {"zs", 20}
     *
     * 如果使用：
     * box["zs"]
     *
     * 编译器无法确定到底应该返回哪一个 value，
     * 所以 unordered_multimap 不提供 operator[]。
     */
    // box["zs"] = 21;
    // cout << box["zs"] << endl;
    // box["zl"] = 22;

    /**
     * 当前没有修改容器，
     * 所以两次输出内容相同。
     */
    print(box);

    /**
     * unordered_multimap 的基本操作和 unordered_map 类似：
     *
     * insert()
     * 插入键值对。
     *
     * find()
     * 根据 key 查找元素。
     * 找到返回指向该 key 对应元素的迭代器，
     * 未找到返回 end()。
     *
     * 如果存在多个相同 key，
     * find 通常返回其中一个匹配位置的迭代器。
     *
     * count()
     * 统计 key 出现次数。
     *
     * erase()
     * 删除元素。
     *
     * size()
     * 获取元素个数。
     *
     * empty()
     * 判断是否为空。
     *
     *
     * unordered_multimap 针对自定义类型 key 的处理方式
     * 和 unordered_set 存储自定义类型类似：
     *
     * 1. 需要提供哈希函数
     *    用来计算 key 的哈希值。
     *
     * 2. 需要提供相等判断规则
     *    用来判断两个 key 是否相同。
     */
}

int main(int argc, char const *argv[])
{
    test1();
    // test2();

    return 0;
}