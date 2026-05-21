#include <iostream>
#include <vector>
#include <array>
#include <forward_list>

using namespace std;

/*
STL 容器分类:

1. 顺序容器
   按元素插入的顺序存储和访问元素。

   array        : 固定大小数组，大小在编译期确定，不能扩容
   vector       : 动态数组，支持随机访问，尾部插入/删除效率高
   forward_list : 单向链表，只能向前遍历，插入/删除效率高
   list         : 双向链表，支持前后双向遍历
   deque        : 双端队列，支持头部和尾部高效插入/删除

2. 关联容器
   底层通常是红黑树，元素会自动按照键值排序。

   set          : 集合，元素唯一
   map          : 键值对，键唯一
   multiset     : 集合，元素可以重复
   multimap     : 键值对，键可以重复

3. 无序关联容器
   底层通常是哈希表，元素不按大小顺序排列，平均查找效率高。

   unordered_set      : 无序集合，元素唯一
   unordered_map      : 无序键值对，键唯一
   unordered_multiset : 无序集合，元素可以重复
   unordered_multimap : 无序键值对，键可以重复
*/

// 简单了解 array 和 forward_list 的基本使用
void test1()
{
    // array 是固定大小的顺序容器，定义时需要指定元素类型和元素个数
    array<int,5> arr {1,2,3,4,5};

    // 使用下标访问元素，不会进行越界检查
    cout << arr[0] << endl;

    // at() 会进行越界检查，越界时会抛出异常
    cout << arr.at(1) << endl;

    // front() 获取第一个元素
    cout << arr.front() << endl;

    // back() 获取最后一个元素
    cout << arr.back() << endl;

    cout << "--------" << endl;

    // forward_list 是单向链表，只支持从前往后遍历
    forward_list<int> fl {4, 5, 6};

    // 使用范围 for 遍历 forward_list 中的元素
    for(auto & e : fl)
    {
        cout << e << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    test1();
    return 0;
}