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

// vector的insert操作
void test1()
{
    vector<int> box {1, 2, 3, 4, 5};
    cout << "size = "<< box.size() << endl;
    cout << "capacity = " << box.capacity() << endl;
    print(box);

    auto it = box.begin();
    ++it;

    it = box.insert(it, 100); // 用返回值更新迭代器it
    print(box);

    cout << "*it = " << *it << endl;
    ++it;
    cout << "*it = " << *it << endl;
    ++it;
    cout << "*it = " << *it << endl;

    auto it2 = box.begin();
    ++it2;
    // 使用初始化列表插入多个元素
    it2 = box.insert(it2, {1000, 2000});
    print(box);
    cout << "*it2 = " << *it2 << endl;
    
    // 插入一个迭代器范围
    vector<int> box2{10, 20, 30};
    // 将 box2 的 [begin, end) 区间插入到 it2 指向的位置前面
    // 返回值指向第一个新插入的元素 10
    it2 = box.insert(it2, box2.begin(), box2.end());
    print(box);
}

// list的insert操作
void test2()
{
    list<int> box {1, 2, 3, 4, 5};
    print(box);

    auto it = box.begin();
    ++it; // 此时 it 指向元素 2
    cout << "*it = " << *it << endl;

    it = box.insert(it, 10);
    print(box);
    cout << "*it = " << *it << endl;

    cout << "-------" << endl;

    // 在 it 指向的位置前面插入 2 个 200
    // 返回值指向第一个新插入的 200
    it = box.insert(it, 2, 200);
    print(box);
    // it 指向第一个新插入的 200
    cout << "*it = " << *it << endl;
}

// deque的insert操作
void test3()
{
    deque<int> box {1,2,3,4,5};
    print(box);

    auto it = box.begin();
    ++it;
    cout << "*it = " << *it << endl;
    
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
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}
