#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

// 定义一个函数模板，可以打印支持范围 for 遍历的容器
template<typename Container>
void print(const Container& box)
{
    for (auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

// size() / clear()
// size()  : 获取容器中当前元素的个数
// clear() : 清空容器中的所有元素，清空后 size() 为 0
void test1()
{
    list<int> box {1, 2, 3, 4, 5};

    print(box);

    // 输出当前元素个数
    cout << box.size() << endl;

    // 清空容器中的所有元素
    box.clear();

    print(box);

    // 清空后，元素个数为 0
    cout << box.size() << endl;
}

// swap()
// 交换两个同类型容器中的内容
void test2()
{
    // list<int> box1 {1, 2, 3, 4, 5};
    // list<int> box2 {6, 7, 8};

    vector<int> box1 {1, 2, 3, 4, 5};
    vector<int> box2 {6, 7, 8};

    print(box1);
    print(box2);

    cout << "---swap()---" << endl;

    // 交换 box1 和 box2 中的元素
    box1.swap(box2);

    print(box1);
    print(box2);
}

// resize()
// 更改容器中元素的个数，也就是改变 size()
void test3()
{
    list<int> box{1, 2, 3, 4, 5};

    cout << box.size() << endl;
    print(box);

    // resize(3) 会保留前 3 个元素，删除后面的元素
    // box.resize(3);

    // resize(10) 会把元素个数扩展到 10
    // 新增的 int 元素会进行值初始化，默认值为 0
    box.resize(10);

    cout << box.size() << endl;
    print(box);
}

// front() / back()
// front() : 获取容器的第一个元素
// back()  : 获取容器的最后一个元素
void test4()
{
    list<int> box{1, 2, 3, 4, 5};

    // 获取第一个元素
    cout << box.front() << endl;

    // 获取最后一个元素
    cout << box.back() << endl;
}

// reserve() / shrink_to_fit()
// reserve()       : 预留容量，只影响 capacity，不改变 size
// shrink_to_fit() : 请求容器释放多余容量，使 capacity 尽量接近 size
void test5()
{
    vector<int> box{1, 2, 3, 4, 5};

    // size 表示当前实际元素个数
    cout << "size: " << box.size() << endl;

    // capacity 表示当前已经分配的容量
    cout << "capacity: " << box.capacity() << endl;

    // 预留至少 10 个元素的空间
    // reserve 不会新增元素，因此 size 不变
    box.reserve(10);

    cout << "size: " << box.size() << endl;
    cout << "capacity: " << box.capacity() << endl;

    // shrink_to_fit() 请求释放多余空间
    // 注意：这是一个“请求”，标准不强制要求一定回收到 size 大小
    box.shrink_to_fit();

    cout << "size: " << box.size() << endl;
    cout << "capacity: " << box.capacity() << endl;
}

int main(int argc, char * argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();

    return 0;
}