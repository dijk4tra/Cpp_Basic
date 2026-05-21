#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

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
 * size() 和 clear()
 *
 * size()：
 * 返回容器中当前元素的个数。
 *
 * clear()：
 * 清空容器中的所有元素。
 *
 * 注意：
 * clear() 只是删除元素，
 * 容器对象本身仍然存在。
 */
void test1()
{
    // 创建 list 容器
    list<int> box {1, 2, 3, 4, 5};

    print(box);

    // 输出当前元素个数
    cout << box.size() << endl;

    // 清空容器中的所有元素
    box.clear();

    // 此时容器为空，
    // print 不会输出任何元素，只会换行。
    print(box);

    // 再次输出元素个数，结果为 0
    cout << box.size() << endl;
}

/**
 * swap() 内容交换
 *
 * swap()：
 * 交换两个同类型容器中的内容。
 *
 * 注意：
 * 1. 两个容器类型必须相同。
 *    例如 vector<int> 只能和 vector<int> 交换。
 *
 * 2. 容器中保存的元素类型也必须相同。
 *
 * 3. swap 通常效率较高，
 *    因为它一般不是逐个元素交换，
 *    而是交换容器内部管理的数据结构。
 */
void test2()
{
    // 也可以测试 list 的 swap
    // list<int> box1 {1, 2, 3, 4, 5};
    // list<int> box2 {6, 7, 8};

    // 创建两个 vector 容器
    vector<int> box1 {1, 2, 3, 4, 5};
    vector<int> box2 {6, 7, 8};

    print(box1);
    print(box2);

    cout << "---swap()---" << endl;

    // 交换 box1 和 box2 中的内容
    //
    // 交换后：
    // box1 中保存 6 7 8
    // box2 中保存 1 2 3 4 5
    box1.swap(box2);

    print(box1);
    print(box2);
}

/**
 * resize() 更改元素个数
 *
 * resize(n)：
 * 将容器中的元素个数调整为 n。
 *
 * 如果 n 小于原来的 size：
 * 多余的元素会被删除。
 *
 * 如果 n 大于原来的 size：
 * 会在容器尾部添加新元素。
 *
 * 对于 int 类型来说，
 * 新添加的元素默认初始化为 0。
 *
 * resize(n, value)：
 * 如果需要新增元素，
 * 新增的元素会被初始化为 value。
 */
void test3()
{
    list<int> box{1, 2, 3, 4, 5};

    // 输出当前元素个数
    cout << box.size() << endl;

    print(box);

    // 调整容器元素个数为 3
    //
    // 原来有 5 个元素，
    // resize(3) 后只保留前 3 个元素。
    // box.resize(3);

    // 调整容器元素个数为 10
    //
    // 原来有 5 个元素，
    // resize(10) 后会在尾部新增 5 个元素。
    //
    // list<int> 中新增的 int 元素默认值为 0。
    box.resize(10);

    cout << box.size() << endl;

    print(box);
}

/**
 * front() 和 back()
 *
 * front()：
 * 返回容器中的第一个元素。
 *
 * back()：
 * 返回容器中的最后一个元素。
 *
 * 注意：
 * 调用 front() / back() 前，
 * 要确保容器不是空的。
 *
 * 如果容器为空，
 * 调用 front() 或 back() 会产生未定义行为。
 */
void test4()
{
    list<int> box{1, 2, 3, 4, 5};

    // 输出第一个元素
    cout << box.front() << endl;

    // 输出最后一个元素
    cout << box.back() << endl;
}

/**
 * shrink_to_fit() 减少容器的容量
 *
 * vector 有两个常见概念：
 *
 * size：
 * 当前已经存放的元素个数。
 *
 * capacity：
 * 当前已经分配的空间最多可以容纳多少个元素。
 *
 *
 * reserve(n)：
 * 预留至少可以存放 n 个元素的空间。
 *
 * 注意：
 * reserve 只改变 capacity，
 * 不改变 size。
 *
 *
 * shrink_to_fit()：
 * 请求容器释放多余容量，
 * 让 capacity 尽量接近 size。
 *
 * 注意：
 * shrink_to_fit() 是一种“请求”，
 * 标准并不强制要求一定释放成功。
 * 具体是否缩减容量，取决于编译器和标准库实现。
 */
void test5()
{
    vector<int> box{1, 2, 3, 4, 5};

    // 当前元素个数
    cout << "size: " << box.size() << endl;

    // 当前容量
    cout << "capacity: " << box.capacity() << endl;

    // 预留空间
    //
    // reserve(10) 表示希望 vector 至少预留
    // 能存放 10 个元素的空间。
    //
    // reserve 不会增加元素个数，
    // 所以 size 不变。
    box.reserve(10);

    cout << "size: " << box.size() << endl;
    cout << "capacity: " << box.capacity() << endl;

    // 回收多余空间
    //
    // 如果当前 size 是 5，capacity 是 10，
    // shrink_to_fit() 之后，
    // capacity 可能会变为 5。
    //
    // 但这不是强制保证。
    box.shrink_to_fit();

    cout << "size: " << box.size() << endl;
    cout << "capacity: " << box.capacity() << endl;
}

int main(int argc, char * argv[])
{
    // test1();  // size() 和 clear()
    // test2();  // swap() 交换容器内容
    // test3();  // resize() 修改元素个数
    // test4();  // front() 和 back()

    // shrink_to_fit() 减少 vector 容量
    test5();

    return 0;
}