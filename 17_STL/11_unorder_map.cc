#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

/**
 * 无序关联式容器 unordered_map：
 * - unordered_map 用来存储 key-value 键值对
 * - key 唯一，不能重复
 * - value 可以重复
 * - 底层通常使用哈希表实现
 * - 元素不会按照 key 自动排序
 *
 * unordered_map 和 map 的区别：
 * - map：底层通常是红黑树，会按照 key 自动排序
 * - unordered_map：底层通常是哈希表，不会按照 key 自动排序
 *
 * 注意：
 * - 输出顺序不一定是插入顺序
 * - 输出顺序也不一定是 key 的升序
 * - 查找、插入、删除的平均时间复杂度通常是 O(1)
 */

template<typename Container>
void print(Container &box)
{
    // unordered_map 中的每一个元素都是 pair<const Key, Value>
    // e.first 表示 key
    // e.second 表示 value
    for(auto & e : box)
    {
        cout << e.first << " " << e.second << " " << endl;
    }
    cout << endl;
}

// unordered_map 容器的特点
void test1()
{
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
    - 数据无序
    - key 唯一，不能重复
    - 输出顺序与插入顺序无关，也不保证升序
    */
}

// unordered_map 基本操作
void test2()
{
    // 无参构造，创建一个空的 unordered_map
    unordered_map<string,int> box;

    // 插入元素
    // unordered_map 的 key 不允许重复
    box.insert({"zs", 20});

    // 由于 key "zs" 已经存在，这次插入不会成功
    box.insert({"zs", 20});

    box.insert({"ls", 19});
    box.insert({"ww", 18});

    // count：
    // 对于 unordered_map 来说，key 不重复
    // 找到返回 1，未找到返回 0
    int rusult = box.count("zs");

    // 删除元素
    // box.erase(box.begin());

    print(box);

    cout << "-------" << endl;

    // operator[]：
    // 1. 如果 key 存在，返回该 key 对应的 value
    // 2. 如果 key 不存在，会先插入一个新的 key-value，再返回 value
    //
    // key "zs" 已经存在，所以这里会修改它对应的 value
    box["zs"] = 21;
    cout << box["zs"] << endl;

    // key "zl" 不存在，所以会先插入 {"zl", 0}
    // 然后再把 value 修改为 22
    box["zl"] = 22;

    cout << "------" << endl;
    print(box);

    // unordered_map 的基本操作和 map 类似：
    // insert() 插入
    // find() 查找
    // count() 统计 key 是否存在
    // erase() 删除
    // operator[] 根据 key 访问或修改 value
    //
    // unordered_map 针对自定义类型 key 的处理方式
    // 和 unordered_set 存储自定义类型类似：
    // 需要提供哈希函数和相等判断规则
}

int main(int argc, char const *argv[])
{
    // test1();
    test2();

    return 0;
}