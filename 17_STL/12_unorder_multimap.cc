#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

/**
 * 无序关联式容器 unordered_multimap：
 * - unordered_multimap 用来存储 key-value 键值对
 * - key 可以重复
 * - value 可以重复
 * - 底层通常使用哈希表实现
 * - 元素不会按照 key 自动排序
 *
 * unordered_map 和 unordered_multimap 的区别：
 * - unordered_map：key 唯一，不能重复
 * - unordered_multimap：key 可以重复
 *
 * 注意：
 * - 输出顺序不一定是插入顺序
 * - 输出顺序也不一定是 key 的升序
 * - 查找、插入、删除的平均时间复杂度通常是 O(1)
 */

template<typename Container>
void print(Container &box)
{
    // unordered_multimap 中的每一个元素都是 pair<const Key, Value>
    // e.first 表示 key
    // e.second 表示 value
    for(auto & e : box)
    {
        cout << e.first << " " << e.second << " " << endl;
    }
    cout << endl;
}

// unordered_multimap 容器的特点
void test1()
{
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
    - 数据无序
    - key 可以重复
    - 输出顺序与插入顺序无关，也不保证升序
    */
}

// unordered_multimap 基本操作
void test2()
{
    // 无参构造，创建一个空的 unordered_multimap
    unordered_multimap<string,int> box;

    // 插入元素
    // unordered_multimap 允许 key 重复
    box.insert({"zs", 20});
    box.insert({"zs", 20});
    box.insert({"ls", 19});
    box.insert({"ww", 18});

    // count：
    // 对于 unordered_multimap 来说，key 可以重复
    // 找到返回该 key 对应元素的个数，未找到返回 0
    int rusult = box.count("zs");

    // 删除元素
    // box.erase(box.begin());

    print(box);

    cout << "-------" << endl;

    // unordered_multimap 不支持 operator[]
    // 因为 key 可以重复，同一个 key 可能对应多个 value
    // 无法确定 box["zs"] 应该返回哪一个 value
    // box["zs"] = 21;
    // cout << box["zs"] << endl;
    // box["zl"] = 22;

    // 当前没有修改容器，所以两次输出内容相同
    print(box);

    // unordered_multimap 的基本操作和 unordered_map 类似：
    // insert() 插入
    // find() 查找
    // count() 统计 key 出现次数
    // erase() 删除
    // size() 获取元素个数
    // empty() 判断是否为空
    //
    // unordered_multimap 针对自定义类型 key 的处理方式
    // 和 unordered_set 存储自定义类型类似：
    // 需要提供哈希函数和相等判断规则
}

int main(int argc, char const *argv[])
{
    test1();
    // test2();

    return 0;
}