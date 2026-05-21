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
 * list 的 erase 操作：不更新迭代器
 *
 * erase(pos)：
 * 删除 pos 位置上的元素。
 *
 * 注意：
 * 被删除元素对应的迭代器一定会失效。
 *
 * 对 list 来说：
 * 删除某个元素后，
 * 指向其他元素的迭代器仍然有效；
 * 但是指向被删除元素的迭代器会失效。
 *
 * 当前 test1 是错误示范：
 * erase(it) 删除 it 指向的元素后，
 * it 已经失效。
 *
 * 失效后的迭代器不能再解引用，
 * 也不能继续用于 insert、erase 等操作，
 * 否则会产生未定义行为。
 */
void test1()
{
    list<int> box{1, 2, 3, 4, 5, 6, 7};

    print(box);

    // 获取指向第一个元素的迭代器
    auto it = box.begin();

    // it 向后移动两次
    // 此时 it 指向元素 3
    ++it;
    ++it;

    // 删除 it 指向的元素 3
    //
    // 由于没有接收 erase 的返回值，
    // 此时 it 仍然是原来的迭代器，
    // 但它指向的元素已经被删除，
    // 所以 it 已经失效。
    box.erase(it);

    // 删除后容器变成：
    // 1 2 4 5 6 7
    print(box);

    // 错误：
    // it 已经失效，
    // 继续解引用 it 会导致未定义行为。
    cout << "*it = " << *it << endl;

    // 错误：
    // 使用已经失效的 it 作为插入位置，
    // 也会导致未定义行为。
    box.insert(it, 100);

    print(box);

    // 错误：
    // 再次解引用失效迭代器。
    cout << "*it = " << *it << endl;
}

/**
 * list 的 erase 操作：更新迭代器
 *
 * erase(pos) 的返回值：
 * 返回指向被删除元素后一个位置的迭代器。
 *
 * 所以删除元素后，
 * 建议使用 erase 的返回值更新迭代器。
 *
 *
 * erase(first, last)：
 * 删除 [first, last) 范围中的元素。
 *
 * [first, last) 是左闭右开区间：
 * 包含 first 指向的元素，
 * 不包含 last 指向的元素。
 *
 * erase(first, last) 的返回值：
 * 返回指向最后一个被删除元素后一个位置的迭代器，
 * 也就是 last 原本指向的位置。
 */
void test2()
{
    list<int> box{1, 2, 3, 4, 5, 6, 7};

    print(box);

    auto it = box.begin();

    // it 指向元素 3
    ++it;
    ++it;

    // 删除元素 3，
    // 并使用 erase 的返回值更新 it。
    //
    // 删除后 it 指向元素 4。
    it = box.erase(it);

    print(box);

    cout << "*it = " << *it << endl;

    // itBegin 指向第一个元素
    auto itBegin = box.begin();

    // itEnd 初始指向最后一个元素的下一个位置
    auto itEnd = box.end();

    // --itEnd 后，itEnd 指向最后一个元素 7
    --itEnd;

    // 再次 --itEnd 后，itEnd 指向元素 6
    --itEnd;

    // 删除 [itBegin, itEnd) 范围中的元素
    //
    // 当前容器是：
    // 1 2 4 5 6 7
    //
    // itBegin 指向 1，
    // itEnd 指向 6。
    //
    // 所以删除：
    // 1 2 4 5
    //
    // 不删除 itEnd 指向的 6。
    //
    // 删除后容器变成：
    // 6 7
    //
    // 返回值 it2 指向 itEnd 原本指向的位置，
    // 也就是元素 6。
    auto it2 = box.erase(itBegin, itEnd);

    print(box);

    cout << "*it2 = " << *it2 << endl;
}

/**
 * deque 的 erase 操作：不更新迭代器
 *
 * deque 在中间位置删除元素时，
 * 可能会导致迭代器失效。
 *
 * 当前 test3 是错误示范：
 * erase(it) 后没有更新 it，
 * 后面继续使用 it 是不安全的。
 */
void test3()
{
    deque<int> box{1, 2, 3, 4, 5, 6, 7};

    print(box);

    auto it = box.begin();

    // it 指向元素 3
    ++it;
    ++it;

    cout << "*it = " << *it << endl;

    // 删除 it 指向的元素 3
    //
    // 对 deque 来说，
    // 删除中间元素后，原来的迭代器可能失效。
    box.erase(it);

    print(box);

    // 错误：
    // it 可能已经失效，
    // 不应该继续使用。
    cout << "*it = " << *it << endl;

    // 错误：
    // 继续使用可能失效的 it。
    box.erase(it);

    print(box);

    cout << "*it = " << *it << endl;
}

/**
 * deque 的 erase 操作：更新迭代器
 *
 * 对 deque 执行 erase 后，
 * 建议使用 erase 的返回值更新迭代器。
 *
 * erase 的返回值：
 * 返回指向被删除元素后一个位置的迭代器。
 */
void test4()
{
    deque<int> box{1, 2, 3, 4, 5, 6, 7};

    print(box);

    auto it = box.begin();

    // it 指向元素 3
    ++it;
    ++it;

    cout << "*it = " << *it << endl;

    // 删除元素 3，
    // 删除后 it 指向元素 4。
    it = box.erase(it);

    print(box);

    cout << "*it = " << *it << endl;

    // 删除当前 it 指向的元素 4，
    // 删除后 it 指向元素 5。
    it = box.erase(it);

    print(box);

    cout << "*it = " << *it << endl;
}

/**
 * vector 的 erase 操作：不更新迭代器
 *
 * vector 底层是连续空间。
 *
 * 删除中间元素时，
 * 被删除元素后面的所有元素都需要向前移动。
 *
 * 所以 erase 后：
 * 1. 被删除元素对应的迭代器失效。
 * 2. 被删除元素后面的迭代器也会失效。
 *
 * 当前 test5 是不推荐写法：
 * erase 后没有更新迭代器，
 * 后面继续使用 it 是不安全的。
 */
void test5()
{
    vector<int> box{1, 2, 3, 4, 5, 6, 7};

    print(box);

    auto it = box.begin();

    // it 指向元素 3
    ++it;
    ++it;

    cout << "*it = " << *it << endl;

    // 删除元素 3
    //
    // 删除后容器变成：
    // 1 2 4 5 6 7
    //
    // 原来的 it 已经失效。
    box.erase(it);

    print(box);

    // 错误：
    // 原来的 it 已经失效，
    // 继续使用 it 是未定义行为。
    cout << "*it = " << *it << endl;

    // 错误：
    // 继续使用失效迭代器删除元素。
    box.erase(it);

    print(box);

    cout << "*it = " << *it << endl;

    // 错误：
    // 继续使用失效迭代器删除元素。
    box.erase(it);

    print(box);

    cout << "*it = " << *it << endl;
}

/**
 * vector 的 erase 操作：更新迭代器
 *
 * erase(pos)：
 * 删除 pos 指向的元素。
 *
 * 返回值：
 * 返回指向被删除元素后一个位置的迭代器。
 *
 * 对 vector 来说，
 * erase 之后一定要注意迭代器失效问题。
 *
 * 推荐写法：
 * it = box.erase(it);
 */
void test6()
{
    vector<int> box{1, 2, 3, 4, 5, 6, 7};

    print(box);

    auto it = box.begin();

    // it 指向元素 3
    ++it;
    ++it;

    cout << "*it = " << *it << endl;

    // 删除元素 3，
    // 删除后 it 指向元素 4。
    it = box.erase(it);

    print(box);

    cout << "*it = " << *it << endl;

    // 删除元素 4，
    // 删除后 it 指向元素 5。
    it = box.erase(it);

    print(box);

    cout << "*it = " << *it << endl;

    // 删除元素 5，
    // 删除后 it 指向元素 6。
    it = box.erase(it);

    print(box);

    cout << "*it = " << *it << endl;
}

/**
 * 遍历 vector 容器，删除所有元素 3
 *
 * 重点：
 * 遍历过程中删除元素时，
 * for 循环第三部分不要写 ++it。
 *
 * 原因：
 * 1. 如果当前元素不是要删除的元素，
 *    才手动执行 ++it。
 *
 * 2. 如果当前元素是要删除的元素，
 *    erase 会删除当前元素，
 *    并返回下一个有效位置。
 *
 * 如果 erase 后又在 for 循环中自动 ++it，
 * 就会跳过元素。
 */
void test7()
{
    vector<int> box {1, 2, 3, 3, 3, 3, 4, 5, 6};

    print(box);

    // 使用迭代器方式遍历
    //
    // 注意：
    // for 的第三个表达式位置不要写 ++it。
    //
    // 因为是否移动迭代器，
    // 要根据当前元素是否被删除来决定。
    for(auto it = box.begin(); it != box.end(); )
    {
        // 如果当前元素是 3
        if(*it == 3)
        {
            // 删除当前元素，
            // 并用 erase 返回值更新 it。
            //
            // 删除后 it 指向原本被删除元素的下一个元素。
            it = box.erase(it);
        }
        else
        {
            // 如果当前元素不是 3，
            // 说明不需要删除，
            // 此时手动让迭代器向后移动。
            ++it;
        }
    }

    print(box);
}

int main()
{
    // test1();  // list erase 后不更新迭代器，错误示范
    // test2();  // list erase 后更新迭代器，推荐写法
    // test3();  // deque erase 后不更新迭代器，错误示范
    // test4();  // deque erase 后更新迭代器，推荐写法
    // test5();  // vector erase 后不更新迭代器，错误示范
    // test6();  // vector erase 后更新迭代器，推荐写法

    // 遍历 vector，删除所有元素 3
    test7();

    return 0;
}