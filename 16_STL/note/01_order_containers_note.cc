#include <iostream>
#include <vector>
#include <array>
#include <forward_list>

using namespace std;

/**
 * STL 标准模板库：
 * STL 是 Standard Template Library 的缩写，
 * 中文通常叫做标准模板库。
 *
 * STL 中常用内容主要包括：
 * 1. 容器 container
 *    用来存放数据。
 *
 * 2. 迭代器 iterator
 *    用来访问容器中的元素，
 *    可以理解成“泛化的指针”。
 *
 * 3. 算法 algorithm
 *    用来对容器中的数据进行操作，
 *    例如查找、排序、复制等。
 *
 *
 * 容器分类：
 * 1. 顺序容器 sequence container
 *    元素按照插入顺序进行存储。
 *    常见顺序容器：
 *
 *    array：
 *    静态数组。
 *    大小在编译期确定，
 *    创建之后不能改变容量。
 *
 *    vector：
 *    动态数组。
 *    底层是一段连续空间，
 *    支持随机访问，
 *    并且容量可以动态扩展。
 *
 *    forward_list：
 *    单向链表。
 *    每个节点只保存下一个节点的位置，
 *    只能向前遍历。
 *
 *    list：
 *    双向链表。
 *    每个节点既保存前一个节点的位置，
 *    也保存后一个节点的位置。
 *
 *    deque：
 *    双端队列。
 *    支持在头部和尾部进行高效插入、删除。
 *
 *
 * 2. 关联容器 associative container
 *    底层通常是红黑树。
 *    元素会按照一定规则自动排序。
 *    常见关联容器：
 *    set
 *    map
 *    multimap
 *    multiset
 *
 *
 * 3. 无序关联式容器 unordered associative container
 *    底层通常是哈希表。
 *    元素不按照大小顺序排列，
 *    而是根据哈希值确定存储位置。
 *    常见无序关联式容器：
 *    unordered_set
 *    unordered_map
 *    unordered_multimap
 *    unordered_multiset
 */

/**
 * 了解 array 和 forward_list
 *
 * array：
 * 1. 头文件是 <array>
 * 2. array<int, 5> 表示：
 *    创建一个保存 int 类型数据的静态数组，
 *    数组中有 5 个元素。
 * 3. array 的大小是固定的，
 *    一旦定义之后，不能再改变元素个数。
 *
 * forward_list：
 * 1. 头文件是 <forward_list>
 * 2. forward_list 是单向链表。
 * 3. 只支持从前往后遍历，
 *    不支持反向遍历。
 */
void test1()
{
    // 创建一个 array 容器
    // int 表示容器中保存的数据类型
    // 5 表示容器中元素的个数
    // {1, 2, 3, 4, 5} 是列表初始化
    array<int, 5> arr {1, 2, 3, 4, 5};

    // 使用下标访问元素
    // arr[0] 表示访问第 0 个元素
    // 注意：
    // operator[] 不会进行越界检查。
    // 如果下标越界，程序可能出现未定义行为。
    cout << arr[0] << endl;

    // 使用 at() 成员函数访问元素
    // arr.at(1) 表示访问第 1 个元素
    // 注意：
    // at() 会进行越界检查。
    // 如果下标越界，会抛出异常。
    cout << arr.at(1) << endl;

    // front() 返回容器中的第一个元素
    cout << arr.front() << endl;

    // back() 返回容器中的最后一个元素
    cout << arr.back() << endl;

    cout << "--------" << endl;

    // 创建一个 forward_list 容器
    // forward_list<int> 表示：
    // 创建一个保存 int 类型数据的单向链表
    forward_list<int> fl {4, 5, 6};

    // 范围 for 循环
    // 依次遍历 fl 中的每一个元素
    //
    // auto：
    // 让编译器根据元素类型自动推导 e 的类型。
    //
    // &：
    // 表示引用。
    // auto & e 表示 e 是容器中元素的引用，
    // 不会拷贝元素。
    //
    // 如果写成 auto e，
    // 则每次循环都会把容器中的元素复制一份给 e。
    for(auto & e : fl)
    {
        cout << e << " ";
    }

    cout << endl;
}

int main(int argc, char const *argv[])
{
    // 调用 test1，
    // 测试 array 和 forward_list 的基本使用
    test1();

    return 0;
}