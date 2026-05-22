#include <iostream>
#include <set>
#include <list>
#include <vector>

using namespace std;

/**
 * 关联式容器 set
 *
 * STL 容器可以大致分为两类：
 * 1. 序列式容器
 *    元素按照插入顺序或者位置关系存储。
 *    常见容器：
 *    vector、list、deque 等。
 *
 * 2. 关联式容器
 *    元素不是按照插入顺序存储，
 *    而是按照 key 的大小关系自动排序。
 *    常见容器：
 *    set、multiset、map、multimap。
 *
 *
 * 关联式容器的特点：
 * 1. 底层通常使用红黑树实现
 *    红黑树是一种自平衡二叉搜索树。
 *    它能够保证插入、删除、查找的效率比较稳定。
 *
 * 2. 元素会按照 key 自动排序
 *    默认情况下，按照从小到大的顺序排列。
 *
 * 3. 查找、插入、删除效率较高
 *    时间复杂度通常为 O(logN)。
 *
 *
 * set：
 * - 只存储 key
 * - key 不允许重复
 * - 默认按照升序排序
 *
 * 例如：
 * set<int> box{3, 1, 2, 2};
 * 实际存储结果为：
 * 1 2 3
 * 重复的 2 只会保留一个。
 *
 *
 * multiset：
 * - 只存储 key
 * - key 允许重复
 * - 默认按照升序排序
 *
 * 例如：
 * multiset<int> box{3, 1, 2, 2};
 * 实际存储结果为：
 * 1 2 2 3
 *
 *
 * map：
 * - 存储 key-value 键值对
 * - key 不允许重复
 * - value 可以重复
 * - 默认按照 key 升序排序
 *
 *
 * multimap：
 * - 存储 key-value 键值对
 * - key 允许重复
 * - value 可以重复
 * - 默认按照 key 升序排序
 *
 *
 * 注意：
 * set / map 的 key 是唯一的，不能重复；
 * multiset / multimap 的 key 可以重复。
 */

template<typename Container>
void print(Container &box)
{
    /**
     * 范围 for 遍历容器
     *
     * auto & e：
     * 1. auto
     *    让编译器自动推导元素类型。
     *
     * 2. &
     *    表示 e 是容器中元素的引用，
     *    避免每次遍历时都拷贝一份元素。
     *
     * 对于 set 来说，
     * 元素是按照升序排列后遍历出来的，
     * 而不是按照插入顺序遍历。
     */
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

// set 容器的构造方式
void test1()
{
    /**
     * 无参构造
     *
     * 创建一个空的 set<int> 容器。
     * 此时容器中没有任何元素。
     */
    set<int> box1;

    /**
     * 初始化列表构造
     *
     * 使用 {} 中给出的元素初始化 set。
     *
     * 注意：
     * set 会自动排序，并且会去除重复元素。
     */
    set<int> box2{1,2,3,4,5};

    /**
     * 拷贝构造
     *
     * 使用一个已经存在的 set 对象 box2，
     * 初始化一个新的 set 对象 box3。
     *
     * box3 和 box2 是两个独立的容器，
     * 修改 box3 不会影响 box2。
     */
    set<int> box3(box2);

    // 下面这种写法也是拷贝构造
    // set<int> box3 = box2;

    /**
     * 使用迭代器区间构造
     *
     * box2.begin()：
     * 指向 box2 中第一个元素的迭代器。
     *
     * box2.end()：
     * 指向 box2 最后一个元素后面位置的迭代器。
     *
     * 构造范围为 [begin, end)，
     * 也就是包含 begin 指向的元素，
     * 不包含 end 指向的位置。
     */
    set<int> box4{ box2.begin(), box2.end() };

    print(box2);
}


// set 插入元素 insert
void test2()
{
    // 创建一个空的 set<int> 容器
    set<int> box;

    /**
     * insert 插入单个元素
     *
     * 对于 set 来说，
     * 插入元素时会自动判断：
     * 1. 该元素是否已经存在
     * 2. 该元素应该放在什么位置
     *
     * insert 的返回值类型是：
     * pair<iterator, bool>
     *
     * pair 可以理解为一个保存两个数据的对象。
     *
     * first：
     * 指向插入元素位置的迭代器。
     *
     * second：
     * 表示是否插入成功。
     * true  表示插入成功；
     * false 表示插入失败。
     *
     * 对于 set 来说，
     * 如果插入的 key 已经存在，
     * 那么插入会失败。
     */
    auto p = box.insert(2);

    if(p.second){
        cout << "插入成功" << endl;

        // p.first 是迭代器
        // *p.first 可以取得迭代器指向的元素
        cout << *(p.first) << endl;
    }else{
        cout << "插入失败" << endl;
    }

    /**
     * set 不允许重复元素
     *
     * 前面已经插入过 2，
     * 所以这里再次插入 2 会失败。
     *
     * 不过这里没有接收 insert 的返回值，
     * 所以不会看到插入是否成功。
     */
    box.insert(2);

    /**
     * set 会自动排序
     *
     * 虽然插入顺序是：
     * 1、4、3
     *
     * 但是遍历输出时，
     * 会按照升序输出：
     * 1 2 3 4
     */
    box.insert(1);
    box.insert(4);
    box.insert(3);
    print(box);

    cout << "----" << endl;

    /**
     * 使用迭代器区间插入多个元素
     *
     * box2.begin() 到 box2.end()
     * 表示 list 中的所有元素。
     *
     * insert 会把这个区间中的元素依次插入到 set 中。
     */
    list<int> box2{10,20,30};
    box.insert(box2.begin(), box2.end());
    print(box);

    cout << "----" << endl;

    /**
     * 使用初始化列表插入多个元素
     *
     * 这里一次性插入 100 和 200。
     */
    box.insert({100,200});
    print(box);
}

// set 查找元素 count / find
void test3()
{
    set<int> box{1,2,3,4,5};

    /**
     * count 函数
     *
     * 作用：
     * 统计某个元素在容器中出现的次数。
     *
     * 对于 set 来说，
     * 元素不允许重复，
     * 所以 count 的结果只可能是：
     * 1. 找到，返回 1
     * 2. 没找到，返回 0
     *
     * 如果是 multiset，
     * 因为允许重复元素，
     * count 可能返回大于 1 的值。
     */
    cout << box.count(3) << endl;
    cout << box.count(6) << endl;

    /**
     * find 函数
     *
     * 作用：
     * 查找指定元素。
     *
     * 找到：
     * 返回指向该元素的迭代器。
     *
     * 未找到：
     * 返回 end()。
     *
     * end() 并不指向某个真实元素，
     * 它表示容器最后一个元素后面的位置。
     */
    // auto it = box.find(3);
    auto it = box.find(6);

    if(it != box.end()){
        cout << "找到" << endl;

        // it 是迭代器，*it 取得它指向的元素
        cout << *it << endl;
    }else{
        cout << "未找到" << endl;
    }

}


// erase 删除元素
void test4()
{
    set<int> box{1,2,3,4,5};

    /**
     * begin()
     *
     * 返回指向容器中第一个元素的迭代器。
     *
     * 对于 set 来说，
     * 第一个元素就是排序后最小的元素。
     */
    auto it = box.begin();

    /**
     * 迭代器后移
     *
     * ++it 表示让迭代器指向下一个元素。
     *
     * 原来 it 指向 1，
     * 执行 ++it 后，
     * it 指向 2。
     */
    ++it;

    /**
     * erase 删除元素
     *
     * 这里调用的是：
     * erase(iterator pos)
     *
     * 作用：
     * 删除迭代器 pos 指向的元素。
     *
     * 返回值：
     * 返回一个新的迭代器，
     * 指向被删除元素的下一个位置。
     *
     * 当前 it 指向 2，
     * 删除 2 之后，
     * it2 指向 3。
     */
    auto it2 = box.erase(it);

    cout << *it2 << endl;
    print(box);
}

// set 不支持下标访问
void test5()
{
    set<int> box{1,2,3,4,5};

    /**
     * set 不支持 operator[]
     *
     * vector 可以通过下标访问：
     * vec[0]
     *
     * 但是 set 不支持下标访问：
     * box[0]
     *
     * 原因：
     * set 的底层通常是红黑树，
     * 元素不是按照连续内存的方式存储的，
     * 所以不能像数组或 vector 那样通过下标访问。
     */
    // cout << box[0] << endl;

    /**
     * set 可以通过迭代器访问元素
     *
     * begin() 返回第一个元素的迭代器。
     */
    auto it = box.begin();
    cout << *it << endl;

    /**
     * set 中的元素不能通过迭代器直接修改
     *
     * 原因：
     * set 会根据元素的值维护排序关系。
     *
     * 如果允许直接修改元素，
     * 可能会破坏 set 内部的有序结构。
     *
     * 所以 set 迭代器解引用后得到的元素，
     * 一般会被当作只读元素使用。
     */
    // *it = 10;
}

int main(int argc, char const *argv[])
{
    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}