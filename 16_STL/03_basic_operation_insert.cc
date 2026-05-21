#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

// 专门用于打印 vector<int> 的函数
void print(const vector<int>& box)
{
    for (auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

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

// vector 的 insert 操作
void test1()
{
    vector<int> box = {1, 2, 3, 4, 5};

    // size 表示当前容器中实际存放的元素个数
    cout << "size = " << box.size() << endl;

    // capacity 表示当前 vector 已经分配的容量
    // capacity >= size
    cout << "capacity = " << box.capacity() << endl;

    print(box);

    // 给定位置，插入单个元素
    auto it = box.begin();
    ++it;

    // vector 在插入元素时，如果容量不足，可能会发生扩容
    // 扩容后，原来的迭代器可能失效
    // box.insert(it, 100); // 只插入，不接收返回值，后续继续使用 it 可能有风险

    // insert 返回指向新插入元素的迭代器
    // 因此这里用返回值更新 it
    it = box.insert(it, 100);

    cout << "size = " << box.size() << endl;
    cout << "capacity = " << box.capacity() << endl;
    print(box);

    // 此时 it 指向刚插入的元素 100
    cout << "*it = " << *it << endl;

    // 给定位置，插入多个相同元素
    // 在 it 指向的位置前面插入 2 个 200
    // 返回值指向第一个新插入的 200
    it = box.insert(it, 2, 200);

    print(box);

    // it 指向第一个插入的 200
    cout << "*it = " << *it << endl;

    ++it;
    // 此时 it 指向第二个插入的 200
    cout << "*it = " << *it << endl;

    ++it;
    // 此时 it 指向原来 it 所指向的元素 100
    cout << "*it = " << *it << endl;

    auto it2 = box.begin();
    ++it2;

    // 给定位置，使用初始化列表插入多个元素
    // 在 it2 指向的位置前面插入 1000 和 2000
    // 返回值指向第一个新插入的元素 1000
    it2 = box.insert(it2, {1000, 2000});

    print(box);

    // it2 指向第一个新插入的元素 1000
    cout << "*it2 = " << *it2 << endl;

    // 插入一个迭代器范围
    vector<int> box2{10, 20, 30};

    // 将 box2 的 [begin, end) 区间插入到 it2 指向的位置前面
    // 返回值指向第一个新插入的元素 10
    it2 = box.insert(it2, box2.begin(), box2.end());

    print(box);
}

// list: insert 后不手动更新迭代器
void test2()
{
    list<int> box{1, 2, 3, 4, 5};
    print(box);

    auto it = box.begin();
    ++it;

    // 此时 it 指向元素 2
    cout << "*it = " << *it << endl;

    // 在 it 指向的位置前面插入 10
    // list 插入元素后，原来的迭代器不会失效
    // 因此这里即使不更新 it，it 仍然指向原来的元素 2
    box.insert(it, 10);

    print(box);

    // it 仍然指向元素 2
    cout << "*it = " << *it << endl;

    cout << "-------" << endl;

    // 在 it 指向的位置前面插入 2 个 200
    // it 仍然不会失效，仍指向原来的元素 2
    box.insert(it, 2, 200);

    print(box);

    // it 仍然指向元素 2
    cout << "*it = " << *it << endl;
}

// list: insert 后使用返回值更新迭代器
void test3()
{
    list<int> box{1, 2, 3, 4, 5};
    print(box);

    auto it = box.begin();
    ++it;

    // 此时 it 指向元素 2
    cout << "*it = " << *it << endl;

    // 在 it 指向的位置前面插入 10
    // insert 返回指向新插入元素的迭代器
    // 因此更新后 it 指向 10
    it = box.insert(it, 10);

    print(box);

    // it 指向新插入的元素 10
    cout << "*it = " << *it << endl;

    cout << "-------" << endl;

    // 在 it 指向的位置前面插入 2 个 200
    // 返回值指向第一个新插入的 200
    it = box.insert(it, 2, 200);

    print(box);

    // it 指向第一个新插入的 200
    cout << "*it = " << *it << endl;
}


// deque: insert 后不手动更新迭代器
void test4()
{
    deque<int> box{1, 2, 3, 4, 5};
    print(box);

    auto it = box.begin();
    ++it;

    // 此时 it 指向元素 2
    cout << "*it = " << *it << endl;

    // 在 deque 中间位置插入元素，可能导致迭代器失效
    // 这里没有使用 insert 的返回值更新 it
    // 代码可以编译，但后续继续使用旧 it 有风险
    box.insert(it, 10);

    print(box);

    // 注意：如果 it 已经失效，继续解引用 it 属于未定义行为
    cout << "*it = " << *it << endl;

    // 继续在旧 it 位置插入多个元素
    // 如果前面 it 已经失效，这里的行为也不可靠
    box.insert(it, 2, 200);

    print(box);

    // 注意：继续使用旧 it 可能有风险
    cout << "*it = " << *it << endl;

    // 继续使用旧 it 插入元素
    box.insert(it, 300);

    print(box);

    // 注意：继续使用旧 it 可能有风险
    cout << "*it = " << *it << endl;
}

// deque: insert 后使用返回值更新迭代器
void test5()
{
    deque<int> box {1,2,3,4,5};
    print(box);

    auto it = box.begin();
    ++it;

    // 此时 it 指向元素 2
    cout << "*it = " << *it << endl;

    // 在 it 指向的位置前面插入 10
    // insert 返回指向新插入元素的迭代器
    // 更新后 it 指向 10
    it = box.insert(it, 10);

    print(box);
    cout << "*it = " << *it << endl;

    // 在 it 指向的位置前面插入 2 个 200
    // 返回值指向第一个新插入的 200
    it = box.insert(it, 2, 200);

    print(box);
    cout << "*it = " << *it << endl;

    // 在 it 指向的位置前面插入 300
    // 返回值指向新插入的元素 300
    it = box.insert(it, 300);

    print(box);
    cout << "*it = " << *it << endl;
}

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();

    return 0;
}
