#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * 常用排序、查找和集合算法：
 *
 * sort：
 * 对指定区间进行排序。
 * 注意：sort 要求随机访问迭代器，因此可以用于 vector、deque，
 * 但不能直接用于 list。
 *
 * max：
 * 返回两个值中的较大值。
 *
 * min：
 * 返回两个值中的较小值。
 *
 * lower_bound：
 * 在有序区间中进行二分查找，
 * 返回第一个大于等于目标值的元素位置。
 *
 * upper_bound：
 * 在有序区间中进行二分查找，
 * 返回第一个大于目标值的元素位置。
 *
 * equal_range：
 * 在有序区间中进行二分查找，
 * 返回一个 pair 对象。
 * first  表示第一个大于等于目标值的元素位置。
 * second 表示第一个大于目标值的元素位置。
 * 因此 [first, second) 就是所有等于目标值的元素范围。
 *
 * set_union：
 * 求两个有序集合的并集。
 *
 * set_intersection：
 * 求两个有序集合的交集。
 *
 * set_difference：
 * 求两个有序集合的差集。
 *
 * set_symmetric_difference：
 * 求两个有序集合的对称差集。
 *
 * 注意：
 * lower_bound、upper_bound、equal_range 以及集合算法，
 * 都要求操作的区间是有序的。
 */

void test1()
{    
    // vector 和 deque 都支持随机访问迭代器，因此可以使用 sort
    // vector<int> box{3, 1, 5, 2, 4};
    deque<int> box{3, 1, 5, 2, 4};

    // 对区间 [begin, end) 进行升序排序
    sort(box.begin(), box.end());

    // 输出排序后的结果：1 2 3 4 5
    copy(box.begin(), box.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;

    // 如果是自定义类型，例如 Student，
    // 需要提供比较规则，或者在类中重载 operator<
    // vector<Student> box;
}


// max / min 返回最大值 / 最小值
void test2()
{
    int a = 1;
    int b = 2;

    // 返回 a 和 b 中较大的值
    int maxValue = max(a, b);
    cout << "maxValue = " << maxValue << endl;

    cout << "-----------" << endl;

    // 返回 a 和 b 中较小的值
    int minValue = min(a, b);
    cout << "minValue = " << minValue << endl;

    /*
    // 对于自定义类，需要自定义比较器
    // 比较器用于告诉算法如何判断两个对象的大小关系
    struct StudentCompare
    {
        bool operator()(const Student& s1, const Student& s2)
        {
            return s1.m_age > s2.m_age;
        }
    };

    Student s1{1,"zs",20};
    Student s2{2,"ls",21};

    // 使用自定义比较器比较两个 Student 对象
    max(s1, s2, StudentCompare());
    */
}


// lower_bound：二分查找第一个大于等于目标值的元素
// upper_bound：二分查找第一个大于目标值的元素
//
// 注意：
// lower_bound 和 upper_bound 要求区间已经有序。
void test3()
{
    vector<int> box{1, 2, 3, 4, 5};

    // 查找第一个大于等于 3 的元素
    auto it = lower_bound(box.begin(), box.end(), 3);
    cout << *it << endl; // 3

    cout << "-----------" << endl;

    // 查找第一个大于 3 的元素
    auto it2 = upper_bound(box.begin(), box.end(), 3);
    cout << *it2 << endl; // 4

    cout << "-----------" << endl;
}

// equal_range：
// 在有序区间中查找等于目标值的元素范围。
//
// 返回一个 pair 对象：
// first  是第一个大于等于目标值的元素的迭代器
// second 是第一个大于目标值的元素的迭代器
//
// 如果目标值在范围内不存在，
// first 和 second 都指向第一个大于目标值的元素。
void test4()
{
    vector<int> box{1, 2, 3, 3, 3, 4, 5};

    // 查找所有等于 3 的元素范围
    auto p = equal_range(box.begin(), box.end(), 3);

    auto itStart = p.first;
    auto itEnd = p.second;

    // itStart 指向第一个 3
    cout << *itStart << endl; // 3

    // itEnd 指向第一个大于 3 的元素，也就是 4
    cout << *itEnd << endl; // 4

    cout << "-----------" << endl;

    // [itStart, itEnd) 表示所有等于 3 的元素范围
    copy(itStart, itEnd, std::ostream_iterator<int>(cout, " ")); // 3 3 3
    cout << endl;
}

// 集合操作：并集、交集等
//
// 注意：
// STL 的集合算法要求两个输入区间都是有序的。
void test5()
{
    vector<int> box1{1, 2, 3, 4};
    vector<int> box2{4, 5, 6};
    vector<int> box3;

    // 求 box1 和 box2 的并集
    // set_union 会把结果写入第五个参数指定的位置
    // back_inserter(box3) 表示将结果尾插到 box3 中
    set_union(box1.begin(), box1.end(), box2.begin(), box2.end(), back_inserter(box3));

    // 输出结果：1 2 3 4 5 6
    copy(box3.begin(), box3.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}

void test6()
{
    vector<int> box1{1, 2, 3, 4};
    vector<int> box2{4, 5, 6};
    vector<int> box3;

    // 求 box1 和 box2 的交集
    // 两个容器中都存在的元素才会被放入结果区间
    set_intersection(box1.begin(), box1.end(), box2.begin(), box2.end(), back_inserter(box3));

    // 输出结果：4
    copy(box3.begin(), box3.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}