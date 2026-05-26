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
 * 这些算法主要定义在头文件：
 *
 * #include <algorithm>
 *
 *
 * STL 算法一般通过迭代器区间操作数据。
 *
 * 常见区间形式：
 *
 * [first, last)
 *
 * 表示包含 first 指向的元素，
 * 不包含 last 指向的位置。
 */


/**
 * sort：
 *
 * 对指定区间进行排序。
 *
 * 函数形式：
 *
 * sort(first, last);
 *
 * 默认按照升序排序。
 *
 *
 * 注意：
 * sort 要求传入的迭代器必须是随机访问迭代器。
 *
 * 所以 sort 可以用于：
 * 1. vector
 * 2. deque
 * 3. array
 *
 * 不能直接用于：
 * list
 *
 *
 * 原因：
 * vector / deque 的迭代器支持随机访问：
 *
 * it + n
 * it - n
 * it1 < it2
 *
 * 这些操作可以满足 sort 算法的要求。
 *
 * list 是链表，
 * 只支持双向迭代器，
 * 不支持随机访问，
 * 所以不能直接使用 std::sort。
 *
 *
 * 如果要给 list 排序，
 * 应该使用 list 自己的成员函数：
 *
 * box.sort();
 */


/**
 * max / min：
 *
 * max：
 * 返回两个值中的较大值。
 *
 * min：
 * 返回两个值中的较小值。
 *
 *
 * 默认情况下，
 * max / min 会使用 operator< 进行比较。
 *
 * 对于 int、double、string 等类型，
 * 标准库已经提供了可用的比较方式。
 *
 * 对于自定义类型，
 * 需要：
 *
 * 1. 重载 operator<
 * 或者
 * 2. 提供自定义比较器
 */


/**
 * lower_bound：
 *
 * 在有序区间中进行二分查找。
 *
 * 函数形式：
 *
 * lower_bound(first, last, value);
 *
 * 返回：
 * 第一个大于等于 value 的元素位置。
 *
 *
 * upper_bound：
 *
 * 在有序区间中进行二分查找。
 *
 * 函数形式：
 *
 * upper_bound(first, last, value);
 *
 * 返回：
 * 第一个大于 value 的元素位置。
 *
 *
 * 注意：
 * lower_bound 和 upper_bound 要求区间已经有序。
 *
 * 如果区间无序，
 * 查找结果没有意义。
 */


/**
 * equal_range：
 *
 * 在有序区间中查找等于目标值的元素范围。
 *
 * 函数形式：
 *
 * equal_range(first, last, value);
 *
 *
 * 返回值：
 * pair 对象。
 *
 * pair.first：
 * 等价于 lower_bound 的结果，
 * 表示第一个大于等于 value 的位置。
 *
 * pair.second：
 * 等价于 upper_bound 的结果，
 * 表示第一个大于 value 的位置。
 *
 *
 * 因此：
 *
 * [pair.first, pair.second)
 *
 * 就是所有等于 value 的元素范围。
 *
 *
 * 如果目标值不存在：
 *
 * pair.first 和 pair.second
 * 都会指向第一个大于 value 的元素位置。
 */


/**
 * 集合算法：
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
 *
 * 注意：
 * STL 中的集合算法要求两个输入区间都是有序的。
 *
 * 如果输入区间无序，
 * 结果可能不符合预期。
 *
 *
 * 集合算法一般不会直接修改原容器，
 * 而是把结果写入到第五个参数指定的位置。
 *
 * 所以常见写法是：
 *
 * vector<int> result;
 *
 * set_union(
 *     box1.begin(), box1.end(),
 *     box2.begin(), box2.end(),
 *     back_inserter(result)
 * );
 */


void test1()
{    
    /**
     * vector 和 deque 都支持随机访问迭代器，
     * 因此可以使用 std::sort。
     *
     * 这里可以切换观察：
     *
     * vector<int> box{3, 1, 5, 2, 4};
     *
     * 或者：
     *
     * deque<int> box{3, 1, 5, 2, 4};
     *
     *
     * list<int> 不能直接使用 std::sort，
     * 因为 list 的迭代器不是随机访问迭代器。
     */
    // vector<int> box{3, 1, 5, 2, 4};
    deque<int> box{3, 1, 5, 2, 4};

    /**
     * sort(box.begin(), box.end());
     *
     * 对区间 [begin, end) 进行升序排序。
     *
     * 排序前：
     * 3 1 5 2 4
     *
     * 排序后：
     * 1 2 3 4 5
     */
    sort(box.begin(), box.end());

    /**
     * 输出排序后的结果。
     */
    copy(box.begin(), box.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;

    /**
     * 如果是自定义类型，例如 Student，
     * sort 默认不知道如何比较两个 Student 对象。
     *
     * 这时需要：
     *
     * 1. 在 Student 类中重载 operator<
     *
     * 或者：
     *
     * 2. 给 sort 传入自定义比较规则。
     *
     * 例如：
     *
     * sort(box.begin(), box.end(), [](const Student& s1, const Student& s2){
     *     return s1.m_age < s2.m_age;
     * });
     */
    // vector<Student> box;
}


// max / min 返回最大值 / 最小值
void test2()
{
    int a = 1;
    int b = 2;

    /**
     * max(a, b);
     *
     * 返回 a 和 b 中较大的值。
     *
     * 当前：
     * a = 1
     * b = 2
     *
     * 所以 maxValue = 2。
     */
    int maxValue = max(a, b);
    cout << "maxValue = " << maxValue << endl;

    cout << "-----------" << endl;

    /**
     * min(a, b);
     *
     * 返回 a 和 b 中较小的值。
     *
     * 当前：
     * a = 1
     * b = 2
     *
     * 所以 minValue = 1。
     */
    int minValue = min(a, b);
    cout << "minValue = " << minValue << endl;

    
    /**
     * 对于自定义类，
     * max / min 默认不知道如何比较对象大小。
     *
     * 所以需要自定义比较器。
     *
     * 比较器用于告诉算法：
     * 两个对象之间按照什么规则比较大小。
     */
    /*
    struct StudentCompare
    {
        bool operator()(const Student& s1, const Student& s2)
        {
            return s1.m_age > s2.m_age;
        }
    };

    Student s1{1,"zs",20};
    Student s2{2,"ls",21};

    // 使用自定义比较器比较两个 Student 对象。
    max(s1, s2, StudentCompare());
    */
}


// lower_bound：二分查找第一个大于等于目标值的元素
// upper_bound：二分查找第一个大于目标值的元素
void test3()
{
    /**
     * lower_bound / upper_bound 要求区间有序。
     *
     * 当前 vector 已经是升序：
     * 1 2 3 4 5
     */
    vector<int> box{1, 2, 3, 4, 5};

    /**
     * lower_bound(box.begin(), box.end(), 3);
     *
     * 查找第一个大于等于 3 的元素。
     *
     * 当前区间中：
     * 第一个 >= 3 的元素就是 3。
     *
     * 所以 it 指向元素 3。
     */
    auto it = lower_bound(box.begin(), box.end(), 3);
    cout << *it << endl; // 3

    cout << "-----------" << endl;

    /**
     * upper_bound(box.begin(), box.end(), 3);
     *
     * 查找第一个大于 3 的元素。
     *
     * 当前区间中：
     * 第一个 > 3 的元素是 4。
     *
     * 所以 it2 指向元素 4。
     */
    auto it2 = upper_bound(box.begin(), box.end(), 3);
    cout << *it2 << endl; // 4

    cout << "-----------" << endl;
}


// equal_range
void test4()
{
    /**
     * 当前 vector 是有序区间：
     *
     * 1 2 3 3 3 4 5
     *
     * 里面有三个连续的 3。
     */
    vector<int> box{1, 2, 3, 3, 3, 4, 5};

    /**
     * equal_range(box.begin(), box.end(), 3);
     *
     * 查找所有等于 3 的元素范围。
     *
     * 返回一个 pair 对象。
     *
     * p.first：
     * 第一个大于等于 3 的位置，
     * 也就是第一个 3。
     *
     * p.second：
     * 第一个大于 3 的位置，
     * 也就是 4。
     */
    auto p = equal_range(box.begin(), box.end(), 3);

    auto itStart = p.first;
    auto itEnd = p.second;

    /**
     * itStart 指向第一个 3。
     */
    cout << *itStart << endl; // 3

    /**
     * itEnd 指向第一个大于 3 的元素，
     * 也就是 4。
     *
     * 注意：
     * itEnd 不属于等于 3 的范围。
     */
    cout << *itEnd << endl; // 4

    cout << "-----------" << endl;

    /**
     * [itStart, itEnd)
     *
     * 表示所有等于 3 的元素区间。
     *
     * 所以输出：
     * 3 3 3
     */
    copy(itStart, itEnd, std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


// 集合操作：并集
void test5()
{
    /**
     * 两个输入区间都必须有序。
     *
     * box1：
     * 1 2 3 4
     *
     * box2：
     * 4 5 6
     */
    vector<int> box1{1, 2, 3, 4};
    vector<int> box2{4, 5, 6};

    /**
     * box3 用来保存集合运算结果。
     *
     * 初始为空。
     */
    vector<int> box3;

    /**
     * set_union：
     *
     * 求两个有序区间的并集。
     *
     * 并集：
     * 出现在 box1 或 box2 中的元素都会出现在结果中。
     *
     *
     * set_union 的参数：
     *
     * 1. box1.begin()
     *    第一个区间的起始位置
     *
     * 2. box1.end()
     *    第一个区间的结束位置
     *
     * 3. box2.begin()
     *    第二个区间的起始位置
     *
     * 4. box2.end()
     *    第二个区间的结束位置
     *
     * 5. back_inserter(box3)
     *    输出结果的位置
     *
     *
     * back_inserter(box3) 会把结果不断 push_back 到 box3 中。
     *
     *
     * 当前：
     * box1 = 1 2 3 4
     * box2 = 4 5 6
     *
     * 并集结果：
     * 1 2 3 4 5 6
     */
    set_union(box1.begin(), box1.end(), box2.begin(), box2.end(), back_inserter(box3));

    /**
     * 输出结果：
     * 1 2 3 4 5 6
     */
    copy(box3.begin(), box3.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


// 集合操作：交集
void test6()
{
    /**
     * 两个输入区间都已经有序。
     */
    vector<int> box1{1, 2, 3, 4};
    vector<int> box2{4, 5, 6};
    vector<int> box3;

    /**
     * set_intersection：
     *
     * 求两个有序区间的交集。
     *
     * 交集：
     * 只有同时出现在 box1 和 box2 中的元素，
     * 才会出现在结果中。
     *
     *
     * 当前：
     * box1 = 1 2 3 4
     * box2 = 4 5 6
     *
     * 只有 4 同时存在于两个容器中，
     * 所以交集结果是：
     * 4
     */
    set_intersection(box1.begin(), box1.end(), box2.begin(), box2.end(), back_inserter(box3));

    /**
     * 输出结果：
     * 4
     */
    copy(box3.begin(), box3.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}


int main()
{
    /**
     * test1：
     * sort 对 vector / deque 排序。
     *
     * test2：
     * max / min 获取两个值中的较大值 / 较小值。
     *
     * test3：
     * lower_bound / upper_bound
     * 在有序区间中进行二分查找。
     *
     * test4：
     * equal_range 查找等于目标值的元素范围。
     *
     * test5：
     * set_union 求并集。
     *
     * test6：
     * set_intersection 求交集。
     */
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}