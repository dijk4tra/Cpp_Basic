#include <iostream>
#include <set>
#include <list>
#include <vector>

using namespace std;

/**
 * 关联式容器 multiset：
 *
 * multiset 是 STL 中的关联式容器。
 *
 * 特点：
 * 1. multiset 是允许元素重复的集合
 *    同一个 key 可以保存多份。
 *
 * 2. 底层通常使用红黑树实现
 *    所以插入、删除、查找的效率通常是 O(logN)。
 *
 * 3. 元素会按照比较规则自动排序
 *    插入元素时，不是按照插入顺序保存，
 *    而是根据比较规则放到合适的位置。
 *
 * 4. 默认排序规则是 std::less<T>
 *    也就是默认使用 operator< 进行比较，
 *    按照升序排序。
 *
 *
 * set 和 multiset 的区别：
 * 1. set
 *    元素不能重复。
 *    插入重复元素时，插入会失败。
 *
 * 2. multiset
 *    元素可以重复。
 *    插入重复元素时，重复元素也会被保存。
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
     * 对于 multiset 来说，
     * 遍历顺序就是元素的排序顺序。
     */
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

// multiset 容器的构造方式
void test1()
{
    /**
     * 无参构造
     *
     * 创建一个空的 multiset<int> 容器。
     * 此时容器中没有任何元素。
     */
    multiset<int> box1;

    /**
     * 初始化列表构造
     *
     * 使用 {} 中给出的元素初始化 multiset。
     *
     * 注意：
     * multiset 会自动排序，
     * 但是不会去除重复元素。
     */
    multiset<int> box2{1,2,3,4,5};

    /**
     * 拷贝构造
     *
     * 使用已经存在的 multiset 对象 box2，
     * 初始化一个新的 multiset 对象 box3。
     *
     * box3 和 box2 是两个独立的容器。
     */
    multiset<int> box3(box2);

    // 下面这种写法也是拷贝构造
    // multiset<int> box3 = box2;

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
     * 包含 begin 指向的元素，
     * 不包含 end 指向的位置。
     */
    multiset<int> box4{ box2.begin(), box2.end() };

    print(box2);
}


// multiset 插入元素 insert
void test2()
{
    // 创建一个空的 multiset<int> 容器
    multiset<int> box;

    /**
     * insert 插入单个元素
     *
     * 对于 multiset 来说，
     * 因为允许重复元素，
     * 所以插入一般都会成功。
     *
     * 返回值：
     * 返回指向新插入元素位置的迭代器。
     *
     * 注意：
     * 这里和 set 不一样。
     *
     * set::insert 插入单个元素时，
     * 返回 pair<iterator, bool>。
     *
     * multiset::insert 插入单个元素时，
     * 返回 iterator。
     */
    auto it = box.insert(2);
    cout << *it << endl;

    /**
     * multiset 允许插入重复元素
     *
     * 前面已经插入了一个 2，
     * 这里再次插入 2 仍然可以成功。
     */
    box.insert(2);

    /**
     * multiset 会自动排序
     *
     * 虽然插入顺序是：
     * 2、1、4、3
     *
     * 但是遍历输出时，
     * 会按照升序输出：
     * 1 2 2 3 4
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
     * insert 会把这个区间中的元素依次插入到 multiset 中。
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

// multiset 查找元素 count / find
void test3()
{
    multiset<int> box{1,2,3,3,3,4,4,5};
    print(box);

    /**
     * count 函数
     *
     * 作用：
     * 统计某个元素在容器中出现的次数。
     *
     * 对于 multiset 来说，
     * 元素允许重复，
     * 所以 count 的结果可能大于 1。
     *
     * 找到：
     * 返回该元素出现的次数。
     *
     * 未找到：
     * 返回 0。
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
     * 返回指向目标元素的迭代器。
     *
     * 如果有多个相同元素，
     * 通常返回其中第一个匹配位置的迭代器。
     *
     * 未找到：
     * 返回 end()。
     */
    auto it = box.find(3);
    // auto it = box.find(6);

    if(it != box.end()){
        cout << "找到" << endl;

        /**
         * 当前 box 中有三个 3。
         *
         * find(3) 返回其中一个 3 的位置。
         *
         * 因为 multiset 中相同元素会连续排列，
         * 所以可以通过迭代器不断后移，
         * 访问后面的相同元素。
         */
        cout << *it << endl;
        ++it;
        cout << *it << endl;
        ++it;
        cout << *it << endl;
        ++it;

        /**
         * 继续后移后，
         * 会访问到 3 后面的元素，
         * 也就是 4。
         */
        cout << *it << endl;
    }else{
        cout << "未找到" << endl;
    }

}

// erase 删除元素
void test4()
{
    multiset<int> box{1,2,3,4,5};

    /**
     * begin()
     *
     * 返回指向容器中第一个元素的迭代器。
     *
     * 对于 multiset 来说，
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

// multiset 不支持下标访问
void test5()
{
    multiset<int> box{1,2,3,4,5};

    /**
     * multiset 不支持 operator[]
     *
     * vector 可以通过下标访问：
     * vec[0]
     *
     * 但是 multiset 不支持下标访问：
     * box[0]
     *
     * 原因：
     * multiset 的底层通常是红黑树，
     * 元素不是按照连续内存的方式存储的，
     * 所以不能像数组或 vector 那样通过下标访问。
     */
    // cout << box[0] << endl;

    /**
     * multiset 可以通过迭代器访问元素
     *
     * begin() 返回第一个元素的迭代器。
     */
    auto it = box.begin();
    cout << *it << endl;

    /**
     * multiset 中的元素不能通过迭代器直接修改
     *
     * 原因：
     * multiset 会根据元素的值维护排序关系。
     *
     * 如果允许直接修改元素，
     * 可能会破坏 multiset 内部的有序结构。
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