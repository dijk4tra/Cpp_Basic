#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

/**
 * 无序关联式容器 unordered_map：
 *
 * unordered_map 是 STL 中的无序关联式容器。
 *
 * 特点：
 * 1. unordered_map 用来存储 key-value 键值对
 *    key 表示键，value 表示值。
 *
 * 2. key 唯一，不能重复
 *    同一个 key 只能对应一个 value。
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
 * unordered_map 和 map 的区别：
 * 1. map
 *    底层通常是红黑树，
 *    会按照 key 自动排序。
 *
 * 2. unordered_map
 *    底层通常是哈希表，
 *    不会按照 key 自动排序。
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
     * unordered_map 中的每一个元素都是 pair<const Key, Value>
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
     * unordered_map 中的 key 是 const 的，
     * 不能通过迭代器直接修改 key。
     *
     * 原因：
     * unordered_map 底层需要根据 key 的哈希值
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

// unordered_map 容器的特点
void test1()
{
    /**
     * 初始化列表构造
     *
     * 每个元素都是一个 key-value 键值对。
     *
     * 注意：
     * unordered_map 的 key 不允许重复。
     *
     * 下面出现了两个 key 为 "zs" 的键值对，
     * 最终只会保留其中一个。
     */
    unordered_map<string,int> box{
        {"zs", 18},
        {"zs", 18},  // key 重复，unordered_map 只会保留其中一个
        {"ls", 20},
        {"ww", 19},
    };

    print(box);

    /*
    可能的输出结果：
    ww 19
    ls 20
    zs 18

    unordered_map 的特点：
    1. 数据无序
       不按照插入顺序保存。

    2. key 唯一，不能重复
       相同 key 只能保存一份。

    3. 输出顺序与插入顺序无关，
       也不保证按照 key 升序输出。
    */
}

// unordered_map 基本操作
void test2()
{
    /**
     * 无参构造
     *
     * 创建一个空的 unordered_map<string, int> 容器。
     *
     * string：
     * 表示 key 的类型。
     *
     * int：
     * 表示 value 的类型。
     */
    unordered_map<string,int> box;

    /**
     * 插入元素
     *
     * unordered_map 中保存的是 key-value 键值对，
     * 所以插入时需要插入 pair 类型的数据。
     *
     * unordered_map 的 key 不允许重复。
     */
    box.insert({"zs", 20});

    /**
     * 插入重复 key
     *
     * 由于 key "zs" 已经存在，
     * 所以这次插入不会成功。
     *
     * 注意：
     * insert 插入重复 key 时不会覆盖原来的 value。
     */
    box.insert({"zs", 20});

    box.insert({"ls", 19});
    box.insert({"ww", 18});

    /**
     * count 函数
     *
     * 作用：
     * 统计某个 key 在 unordered_map 中出现的次数。
     *
     * 对于 unordered_map 来说，
     * key 不允许重复，
     * 所以 count 的结果只可能是：
     * 1. 找到，返回 1
     * 2. 没找到，返回 0
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
     * 当前代码中删除语句被注释掉了。
     */
    // box.erase(box.begin());

    print(box);

    cout << "-------" << endl;

    /**
     * operator[] 的作用：
     *
     * 1. 如果 key 存在
     *    返回该 key 对应的 value。
     *
     * 2. 如果 key 不存在
     *    会先插入一个新的 key-value，
     *    其中 value 使用默认值初始化，
     *    然后再返回这个 value。
     *
     * 对于 int 类型来说，
     * 默认值是 0。
     */

    /**
     * key "zs" 已经存在，
     * 所以这里不会插入新元素，
     * 而是修改它对应的 value。
     */
    box["zs"] = 21;
    cout << box["zs"] << endl;

    /**
     * key "zl" 不存在，
     * 所以会先插入：
     * {"zl", 0}
     *
     * 然后再把 value 修改为 22。
     */
    box["zl"] = 22;

    cout << "------" << endl;
    print(box);

    /**
     * unordered_map 的基本操作和 map 类似：
     *
     * insert()
     * 插入键值对。
     *
     * find()
     * 根据 key 查找元素。
     * 找到返回指向该键值对的迭代器，
     * 未找到返回 end()。
     *
     * count()
     * 统计 key 是否存在。
     *
     * erase()
     * 删除元素。
     *
     * operator[]
     * 根据 key 访问或修改 value。
     *
     *
     * unordered_map 针对自定义类型 key 的处理方式
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
    // test1();
    test2();

    return 0;
}