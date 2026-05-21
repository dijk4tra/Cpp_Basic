#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

void print(const vector<int>& box)
{
    for (auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

template<typename Container>
void print(const Container& box)
{
    for (auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

/**
 * vector 的 insert 操作
 *
 * insert：
 * 在指定位置之前插入元素。
 *
 * 常见形式：
 * 1. insert(pos, value)
 *    在 pos 位置之前插入一个元素。
 *
 * 2. insert(pos, count, value)
 *    在 pos 位置之前插入 count 个 value。
 *
 * 3. insert(pos, {初始化列表})
 *    在 pos 位置之前插入初始化列表中的元素。
 *
 * 4. insert(pos, first, last)
 *    在 pos 位置之前插入 [first, last) 范围中的元素。
 *
 *
 * 注意：
 * vector 底层是连续空间。
 * 插入元素时，如果容量不够，可能会扩容。
 *
 * 一旦扩容，原来的迭代器可能会失效。
 * 所以 insert 之后，建议使用 insert 的返回值
 * 来更新迭代器。
 *
 * insert 的返回值：
 * 返回指向第一个新插入元素的迭代器。
 */
void test1()
{
    vector<int> box = {1, 2, 3, 4, 5};

    // size()：
    // 返回容器中当前元素的个数。
    cout << "size = " << box.size() << endl;

    // capacity()：
    // 返回 vector 当前容量。
    //
    // 容量表示当前已经申请的空间
    // 最多可以容纳多少个元素。
    //
    // 注意：
    // size 表示已经存放的元素个数，
    // capacity 表示当前可容纳的元素个数。
    cout << "capacity = " << box.capacity() << endl;

    print(box);

    // 获取指向第一个元素的迭代器
    auto it = box.begin();

    // 让迭代器向后移动一个位置
    // 此时 it 指向元素 2
    ++it;

    // 在 it 指向的位置之前插入元素 100
    //
    // 这种写法虽然可以插入成功，
    // 但是没有接收 insert 的返回值。
    //
    // 对于 vector 来说，插入操作可能导致扩容，
    // 扩容后原来的迭代器 it 可能失效。
    // box.insert(it, 100);

    // 推荐写法：
    // 使用 insert 的返回值更新 it。
    //
    // 插入后 it 指向新插入的元素 100。
    it = box.insert(it, 100);

    cout << "size = " << box.size() << endl;
    cout << "capacity = " << box.capacity() << endl;

    print(box);

    // 输出 it 当前指向的元素
    cout << "*it = " << *it << endl;

    // 在 it 指向的位置之前插入 2 个 200
    //
    // insert(pos, count, value)
    //
    // 插入后返回指向第一个新插入元素的迭代器。
    // 所以此时 it 指向第一个 200。
    it = box.insert(it, 2, 200);

    print(box);

    cout << "*it = " << *it << endl;

    // 让 it 指向下一个元素
    ++it;
    cout << "*it = " << *it << endl;

    // 再让 it 指向下一个元素
    ++it;
    cout << "*it = " << *it << endl;

    // 重新获取 box 的 begin 迭代器
    auto it2 = box.begin();

    // it2 向后移动一个位置
    ++it2;

    // 在 it2 指向的位置之前插入初始化列表中的元素
    //
    // insert(pos, {value1, value2, ...})
    //
    // 返回值指向第一个新插入的元素。
    // 所以 it2 指向 1000。
    it2 = box.insert(it2, {1000, 2000});

    print(box);

    cout << "*it2 = " << *it2 << endl;

    // 创建另一个 vector 容器
    vector<int> box2{10, 20, 30};

    // 插入迭代器范围
    //
    // box2.begin() 指向 box2 的第一个元素
    // box2.end() 指向 box2 最后一个元素的下一个位置
    //
    // [box2.begin(), box2.end())
    // 表示左闭右开的范围，
    // 也就是插入 box2 中的所有元素。
    //
    // 返回值指向第一个新插入的元素 10。
    it2 = box.insert(it2, box2.begin(), box2.end());

    print(box);
}

/**
 * list 的 insert 操作：不更新迭代器
 *
 * list 底层是双向链表。
 *
 * list 插入元素时，
 * 不需要像 vector 一样移动大量元素，
 * 也不会因为扩容导致原来的迭代器失效。
 *
 * 所以：
 * 对 list 执行 insert 后，
 * 原来的迭代器仍然有效。
 *
 * 但是要注意：
 * 如果不接收 insert 的返回值，
 * 原来的迭代器仍然指向原来的元素，
 * 不会自动指向新插入的元素。
 */
void test2()
{
    list<int> box{1, 2, 3, 4, 5};

    print(box);

    // 获取指向第一个元素的迭代器
    auto it = box.begin();

    // it 向后移动一个位置
    // 此时 it 指向元素 2
    ++it;

    cout << "*it = " << *it << endl;

    // 在 it 指向的位置之前插入元素 10
    //
    // 插入后容器变成：
    // 1 10 2 3 4 5
    //
    // 由于没有更新 it，
    // 所以 it 仍然指向原来的元素 2。
    box.insert(it, 10);

    print(box);

    cout << "*it = " << *it << endl;

    cout << "-------" << endl;

    // 在 it 指向的位置之前插入 2 个 200
    //
    // 此时 it 仍然指向元素 2，
    // 所以 2 个 200 会插入到元素 2 的前面。
    //
    // 插入后 it 仍然指向元素 2。
    box.insert(it, 2, 200);

    print(box);

    cout << "*it = " << *it << endl;
}

/**
 * list 的 insert 操作：更新迭代器
 *
 * insert 的返回值：
 * 返回指向第一个新插入元素的迭代器。
 *
 * 如果希望迭代器指向新插入的元素，
 * 就需要使用返回值更新迭代器。
 */
void test3()
{
    list<int> box{1, 2, 3, 4, 5};

    print(box);

    auto it = box.begin();

    // it 指向元素 2
    ++it;

    cout << "*it = " << *it << endl;

    // 在元素 2 前面插入 10
    //
    // 使用返回值更新 it，
    // 所以插入后 it 指向新插入的元素 10。
    it = box.insert(it, 10);

    print(box);

    cout << "*it = " << *it << endl;

    cout << "-------" << endl;

    // 在 it 指向的位置之前插入 2 个 200
    //
    // 当前 it 指向 10，
    // 所以 2 个 200 插入到 10 前面。
    //
    // 插入后 it 指向第一个新插入的 200。
    it = box.insert(it, 2, 200);

    print(box);

    cout << "*it = " << *it << endl;
}

/**
 * deque 的 insert 操作：不更新迭代器
 *
 * deque 是双端队列。
 *
 * 注意：
 * deque 在中间位置插入元素时，
 * 可能会导致迭代器失效。
 *
 * 所以对 deque 执行 insert 后，
 * 不建议继续使用原来的迭代器。
 *
 * 更安全的做法：
 * 使用 insert 的返回值更新迭代器。
 *
 * 当前 test4 是为了演示：
 * 如果不更新迭代器，可能会出现问题。
 */
void test4()
{
    deque<int> box{1, 2, 3, 4, 5};

    print(box);

    auto it = box.begin();

    // it 指向元素 2
    ++it;

    cout << "*it = " << *it << endl;

    // 在 it 指向的位置之前插入元素 10
    //
    // 注意：
    // deque 在中间插入元素后，
    // 原来的 it 可能已经失效。
    //
    // 所以后面继续使用 it 是不安全的。
    box.insert(it, 10);

    print(box);

    // 这里继续使用 it，
    // 可能会产生未定义行为。
    cout << "*it = " << *it << endl;

    // 继续使用已经可能失效的 it 插入元素，
    // 这种写法不推荐。
    box.insert(it, 2, 200);

    print(box);

    cout << "*it = " << *it << endl;

    // 再次使用可能失效的 it，
    // 这种写法不安全。
    box.insert(it, 300);

    print(box);

    cout << "*it = " << *it << endl;
}

/**
 * deque 的 insert 操作：更新迭代器
 *
 * deque 插入元素后，
 * 建议使用 insert 的返回值更新迭代器。
 *
 * insert 的返回值：
 * 返回指向第一个新插入元素的迭代器。
 */
void test5()
{
    deque<int> box {1, 2, 3, 4, 5};

    print(box);

    auto it = box.begin();

    // it 指向元素 2
    ++it;

    cout << "*it = " << *it << endl;

    // 在元素 2 前面插入 10
    //
    // 使用返回值更新 it，
    // 插入后 it 指向新插入的 10。
    it = box.insert(it, 10);

    print(box);

    cout << "*it = " << *it << endl;

    // 在 it 指向的位置之前插入 2 个 200
    //
    // 当前 it 指向 10，
    // 所以 2 个 200 插入到 10 的前面。
    //
    // 插入后 it 指向第一个新插入的 200。
    it = box.insert(it, 2, 200);

    print(box);

    cout << "*it = " << *it << endl;

    // 在 it 指向的位置之前插入 300
    //
    // 当前 it 指向第一个 200，
    // 所以 300 会插入到这个 200 的前面。
    //
    // 插入后 it 指向新插入的 300。
    it = box.insert(it, 300);

    print(box);

    cout << "*it = " << *it << endl;
}

int main()
{
    // test1();  // vector 的 insert 操作
    // test2();  // list insert 后不更新迭代器
    // test3();  // list insert 后更新迭代器
    // test4();  // deque insert 后不更新迭代器，不推荐
    test5();     // deque insert 后更新迭代器，推荐

    return 0;
}