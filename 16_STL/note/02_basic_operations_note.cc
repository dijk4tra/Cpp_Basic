#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

/**
 * print 函数：
 * 用来打印 vector<int> 容器中的所有元素。
 *
 * 参数：
 * const vector<int>& box
 *
 * const：
 * 表示在函数内部不能修改 box 中的数据。
 *
 * &：
 * 表示引用传参。
 * 使用引用可以避免拷贝整个容器，
 * 提高程序效率。
 */
void print(const vector<int>& box)
{
    // 范围 for 循环
    // 依次取出 box 中的每一个元素
    for (auto & e : box)
    {
        cout << e << " ";
    }

    cout << endl;
}

/**
 * 函数模板：
 * template<typename Container>
 *
 * typename Container：
 * 表示 Container 是一个类型参数，
 * 具体是什么类型，由调用函数时传入的实参决定。
 *
 * 这样写的好处：
 * 不仅可以打印 vector，
 * 也可以打印 list、deque 等其他容器。
 *
 * 注意：
 * 这个 print 是一个函数模板，
 * 上面的 print 是普通函数。
 *
 * 当传入 vector<int> 时，
 * 普通函数和函数模板都可以匹配。
 * 一般情况下，编译器会优先选择普通函数。
 */
template<typename Container>
void print(const Container& box)
{
    // 使用范围 for 遍历容器
    // 只要容器支持 begin() 和 end()，
    // 就可以使用这种方式遍历。
    for (auto & e : box)
    {
        cout << e << " ";
    }

    cout << endl;
}

/**
 * vector 初始化方式
 *
 * vector：
 * 动态数组。
 * 底层是一段连续空间。
 *
 * 特点：
 * 1. 支持下标访问。
 * 2. 支持尾部高效插入和删除。
 * 3. 不适合在头部频繁插入和删除。
 */
void test1()
{
    // 无参构造
    // 创建一个空的 vector 容器
    vector<int> box1;

    // 初始化列表
    // 创建 vector 容器时，直接指定初始元素
    vector<int> box2 = {1, 2, 3, 4, 5};

    // 拷贝构造
    // 使用 box2 创建 box3
    // box3 中的元素和 box2 相同
    vector<int> box3(box2);

    // vector 可以拷贝赋值
    // 这种写法也是正确的
    // vector<int> box3 = box2;

    // 迭代器范围构造
    // box2.begin() 指向第一个元素
    // box2.end() 指向最后一个元素的下一个位置
    //
    // 使用 [begin, end) 这个左闭右开的范围
    // 来初始化 box4
    vector<int> box4{box2.begin(), box2.end()};

    // 创建一个 vector 容器
    // 容器中有 3 个元素
    // 每个元素的值都是 100
    vector<int> box5(3, 100);

    // 打印 box2 中的元素
    print(box2);
}

/**
 * list 初始化方式
 *
 * list：
 * 双向链表。
 *
 * 特点：
 * 1. 不支持下标访问。
 * 2. 支持在任意位置高效插入和删除。
 * 3. 支持头部和尾部插入、删除。
 */
void test2()
{
    // 无参构造
    // 创建一个空的 list 容器
    list<int> box1;

    // 初始化列表
    list<int> box2 = {1, 2, 3, 4, 5};

    // 拷贝构造
    // 使用 box2 创建 box3
    list<int> box3(box2);

    // list 也可以拷贝赋值
    // 这种写法是正确的
    // list<int> box3 = box2;

    // 迭代器范围构造
    // 使用 box2 的所有元素初始化 box4
    list<int> box4{box2.begin(), box2.end()};

    // 创建一个 list 容器
    // 容器中有 3 个元素
    // 每个元素的值都是 100
    list<int> box5(3, 100);

    print(box2);
}

/**
 * deque 初始化方式
 *
 * deque：
 * 双端队列。
 *
 * 特点：
 * 1. 支持下标访问。
 * 2. 支持头部和尾部高效插入、删除。
 * 3. 适合需要同时操作头部和尾部的场景。
 */
void test3()
{
    // 无参构造
    // 创建一个空的 deque 容器
    deque<int> box1;

    // 初始化列表
    deque<int> box2 = {1, 2, 3, 4, 5};

    // 拷贝构造
    deque<int> box3(box2);

    // deque 也可以拷贝赋值
    // 这种写法是正确的
    // deque<int> box3 = box2;

    // 迭代器范围构造
    deque<int> box4{box2.begin(), box2.end()};

    // 创建一个 deque 容器
    // 容器中有 3 个元素
    // 每个元素的值都是 100
    deque<int> box5(3, 100);

    print(box2);
}

/**
 * 容器遍历
 *
 * 常见遍历方式：
 * 1. 下标遍历
 * 2. 迭代器遍历
 * 3. 范围 for 遍历
 *
 * 注意：
 * vector 和 deque 支持下标访问。
 * list 不支持下标访问。
 */
void test4()
{
    cout << "-----vector-----" << endl;

    vector<int> box1 {1, 2, 3, 4, 5};

    // 通过下标进行遍历
    // vector 支持 operator[]
    // size() 返回容器中元素的个数
    for (int i = 0; i < box1.size(); i++)
    {
        cout << box1[i] << " ";
    }
    cout << endl;

    // 迭代器遍历
    //
    // begin()：
    // 返回指向第一个元素的迭代器。
    //
    // end()：
    // 返回指向最后一个元素下一个位置的迭代器。
    //
    // it++：
    // 让迭代器指向下一个元素。
    //
    // *it：
    // 解引用迭代器，得到迭代器当前指向的元素。
    for(auto it = box1.begin(); it != box1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 范围 for 遍历
    // auto e 表示每次循环都会拷贝一个元素给 e
    for(auto e : box1)
    {
        cout << e << " ";
    }
    cout << endl;


    cout << "-----list-----" << endl;

    list<int> box2 {1, 2, 3, 4, 5};

    // list 不支持通过下标进行遍历
    // 因为 list 的底层结构是链表，
    // 元素在内存中不是连续存放的。
    /*
    for (int i = 0; i < box2.size(); i++)
    {
        cout << box2[i] << " ";
    }
    cout << endl;
    */

    // 迭代器遍历
    // list 虽然不支持下标访问，
    // 但是支持通过迭代器进行遍历。
    for(auto it = box2.begin(); it != box2.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 范围 for 遍历
    // 本质上也是通过迭代器实现的
    for(auto e : box2)
    {
        cout << e << " ";
    }
    cout << endl;


    cout << "-----deque-----" << endl;

    deque<int> box3 {1, 2, 3, 4, 5};

    // 通过下标进行遍历
    // deque 支持 operator[]
    for (int i = 0; i < box3.size(); i++)
    {
        cout << box3[i] << " ";
    }
    cout << endl;

    // 迭代器遍历
    for(auto it = box3.begin(); it != box3.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 范围 for 遍历
    for(auto e : box3)
    {
        cout << e << " ";
    }
    cout << endl;
}

/**
 * vector 尾部插入和删除
 *
 * push_back(value)：
 * 在容器尾部插入一个元素。
 *
 * pop_back()：
 * 删除容器尾部的一个元素。
 *
 * 注意：
 * pop_back() 只删除元素，
 * 不返回被删除的元素。
 */
void test5()
{
    vector<int> box {1, 2, 3};

    print(box);

    // 在尾部插入元素 4
    box.push_back(4);

    // 在尾部插入元素 5
    box.push_back(5);

    print(box);

    // 删除尾部元素
    box.pop_back();

    print(box);
}

/**
 * list 尾部插入和删除
 *
 * list 也支持 push_back() 和 pop_back()。
 */
void test6()
{
    list<int> box {1, 2, 3};

    print(box);

    box.push_back(4);
    box.push_back(5);

    print(box);

    box.pop_back();

    print(box);
}

/**
 * deque 尾部插入和删除
 *
 * deque 也支持 push_back() 和 pop_back()。
 */
void test7()
{
    deque<int> box {1, 2, 3};

    print(box);

    box.push_back(4);
    box.push_back(5);

    print(box);

    box.pop_back();

    print(box);
}

/**
 * list 头部插入和删除
 *
 * push_front(value)：
 * 在容器头部插入一个元素。
 *
 * pop_front()：
 * 删除容器头部的一个元素。
 *
 * list 是双向链表，
 * 适合在头部和尾部进行插入、删除。
 */
void test8()
{
    list<int> box {1, 2, 3};

    print(box);

    // 在头部插入元素 4
    // 插入后容器变成：4 1 2 3
    box.push_front(4);

    // 在头部插入元素 5
    // 插入后容器变成：5 4 1 2 3
    box.push_front(5);

    print(box);

    // 删除头部元素
    // 删除后容器变成：4 1 2 3
    box.pop_front();

    print(box);
}

/**
 * deque 头部插入和删除
 *
 * deque 是双端队列，
 * 既支持尾部操作，
 * 也支持头部操作。
 */
void test9()
{
    deque<int> box {1, 2, 3};

    print(box);

    // 在头部插入元素 4
    box.push_front(4);

    // 在头部插入元素 5
    box.push_front(5);

    print(box);

    // 删除头部元素
    box.pop_front();

    print(box);
}

/**
 * vector 不支持 push_front() 和 pop_front()
 *
 * 原因：
 * vector 的底层是一段连续空间。
 * 如果在头部插入或删除元素，
 * 后面的元素都需要移动位置，
 * 效率比较低。
 *
 * 所以 STL 没有给 vector 提供
 * push_front() 和 pop_front()。
 */
void test10()
{
    vector<int> box;

    // 错误：
    // vector 不支持头部插入
    // box.push_front(1);

    // 错误：
    // vector 不支持头部删除
    // box.pop_front();
}

int main()
{
    // test1();  // vector 的初始化方式
    // test2();  // list 的初始化方式
    // test3();  // deque 的初始化方式
    // test4();  // 容器遍历
    // test5();  // vector 尾部插入和删除
    // test6();  // list 尾部插入和删除
    // test7();  // deque 尾部插入和删除
    // test8();  // list 头部插入和删除

    // deque 头部插入和删除
    test9();

    return 0;
}