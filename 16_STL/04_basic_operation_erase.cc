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

// list: erase 操作，不更新迭代器
void test1()
{
    list<int> box{1, 2, 3, 4, 5, 6, 7};
    print(box);

    auto it = box.begin();
    ++it;
    ++it;

    // 此时 it 指向元素 3
    // erase 删除 it 指向的元素
    box.erase(it); // 没有使用返回值更新迭代器

    // 注意：
    // 被 erase 删除的元素对应的迭代器会失效
    // 此时 it 已经失效，下面继续解引用 it 属于未定义行为
    print(box);

    cout << "*it = " << *it << endl;

    // 继续使用已经失效的 it 插入元素，也属于未定义行为
    box.insert(it, 100);

    print(box);
    cout << "*it = " << *it << endl;
}

// list: erase 操作，更新迭代器
void test2()
{
    list<int> box{1, 2, 3, 4, 5, 6, 7};
    print(box);

    auto it = box.begin();
    ++it;
    ++it;

    // 此时 it 指向元素 3
    // erase 删除当前元素，并返回被删除元素的下一个位置
    it = box.erase(it);

    // 删除 3 后，it 指向元素 4
    print(box);
    cout << "*it = " << *it << endl;

    auto itBegin = box.begin();
    auto itEnd = box.end();

    // end() 指向最后一个元素的后一个位置
    // --itEnd 后，itEnd 指向最后一个元素 7
    --itEnd;

    // 再 --itEnd 后，itEnd 指向元素 6
    --itEnd;

    // erase(first, last) 删除区间 [first, last)
    // 删除从 begin 到 itEnd 之前的元素，不包含 itEnd 指向的元素
    auto it2 = box.erase(itBegin, itEnd);

    print(box);

    // it2 指向被删除区间后面的第一个元素，也就是原 itEnd 指向的元素
    cout << "*it2 = " << *it2 << endl;
}

// deque: erase 操作，不更新迭代器
void test3()
{
    deque<int> box{1, 2, 3, 4, 5, 6, 7};
    print(box);

    auto it = box.begin();
    ++it;
    ++it;

    // 此时 it 指向元素 3
    cout << "*it = " << *it << endl;
    
    // erase 删除 it 指向的元素
    box.erase(it);

    print(box);

    // 注意：
    // deque 删除元素后，被删除元素对应的迭代器会失效
    // 在中间位置 erase 还可能导致其他迭代器失效
    // 此处继续使用旧 it 属于未定义行为
    cout << "*it = " << *it << endl;

    // 继续使用失效的 it 删除元素，行为不可靠
    box.erase(it);

    print(box);
    cout << "*it = " << *it << endl;
}

// deque: erase 操作，更新迭代器
void test4()
{
    deque<int> box{1, 2, 3, 4, 5, 6, 7};
    print(box);

    auto it = box.begin();
    ++it;
    ++it;

    // 此时 it 指向元素 3
    cout << "*it = " << *it << endl;
    
    // erase 删除当前元素，并返回被删除元素的下一个位置
    it = box.erase(it);

    // 删除 3 后，it 指向元素 4
    print(box);
    cout << "*it = " << *it << endl;

    // 继续删除当前 it 指向的元素 4
    // 删除后 it 指向元素 5
    it = box.erase(it);

    print(box);
    cout << "*it = " << *it << endl;
}

// vector: erase 操作，不更新迭代器
void test5()
{
    vector<int> box{1, 2, 3, 4, 5, 6, 7};
    print(box);

    auto it = box.begin();
    ++it;
    ++it;

    // 此时 it 指向元素 3
    cout << "*it = " << *it << endl;
    
    // erase 删除 it 指向的元素
    box.erase(it); // 没有使用返回值更新迭代器

    // 注意：
    // vector 删除元素后，被删除位置及其后面的迭代器都会失效
    // 此时继续使用旧 it 属于未定义行为
    print(box);
    cout << "*it = " << *it << endl;

    // 继续使用失效的 it 删除元素，行为不可靠
    box.erase(it);

    print(box);
    cout << "*it = " << *it << endl;

    box.erase(it);

    print(box);
    cout << "*it = " << *it << endl;
}

// vector: erase 操作，更新迭代器
void test6()
{
    vector<int> box{1, 2, 3, 4, 5, 6, 7};
    print(box);

    auto it = box.begin();
    ++it;
    ++it;

    // 此时 it 指向元素 3
    cout << "*it = " << *it << endl;
    
    // erase 删除当前元素，并返回被删除元素的下一个位置
    it = box.erase(it);

    // 删除 3 后，it 指向元素 4
    print(box);
    cout << "*it = " << *it << endl;

    // 删除当前 it 指向的元素 4
    // 删除后 it 指向元素 5
    it = box.erase(it);

    print(box);
    cout << "*it = " << *it << endl;

    // 删除当前 it 指向的元素 5
    // 删除后 it 指向元素 6
    it = box.erase(it);

    print(box);
    cout << "*it = " << *it << endl;
}

// 遍历 vector 容器，删除所有值为 3 的元素
void test7()
{
    vector<int> box {1, 2, 3, 3, 3, 3, 4, 5, 6};
    print(box);

    // 使用迭代器遍历并删除元素
    // 注意：for 语句第三部分不要写 ++it
    // 因为 erase 后需要根据返回值决定新的迭代器位置
    for(auto it = box.begin(); it != box.end(); )
    {
        if(*it == 3)
        {
            // 删除当前元素
            // erase 返回被删除元素的下一个位置
            // 必须用返回值更新 it，避免使用失效迭代器
            it = box.erase(it);
        }
        else
        {
            // 当前元素不删除时，才手动移动到下一个元素
            ++it;
        }
    }

    print(box);
}

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    test7();
    
    return 0;
}