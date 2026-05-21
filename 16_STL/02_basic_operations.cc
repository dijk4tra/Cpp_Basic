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

// vector 初始化
void test1()
{
    // 无参构造，创建一个空 vector
    vector<int> box1;

    // 初始化列表构造
    vector<int> box2 = {1, 2, 3, 4, 5};

    // 拷贝构造，用已有 vector 创建新的 vector
    vector<int> box3(box2);

    // 拷贝初始化，也是合法的
    // vector<int> box3 = box2;

    // 迭代器范围构造，使用 box2 的 [begin, end) 区间创建新容器
    vector<int> box4{box2.begin(), box2.end()};

    // 创建 3 个元素，每个元素的值都是 100
    vector<int> box5(3, 100);

    print(box2);
}   

// list 初始化
void test2()
{
    // 无参构造，创建一个空 list
    list<int> box1;

    // 初始化列表构造
    list<int> box2 = {1, 2, 3, 4, 5};

    // 拷贝构造，用已有 list 创建新的 list
    list<int> box3(box2);

    // 拷贝初始化，也是合法的
    // list<int> box3 = box2;

    // 迭代器范围构造，使用 box2 的 [begin, end) 区间创建新容器
    list<int> box4{box2.begin(), box2.end()};

    // 创建 3 个元素，每个元素的值都是 100
    list<int> box5(3, 100);

    print(box2);
}

// deque 初始化
void test3()
{
    // 无参构造，创建一个空 deque
    deque<int> box1;

    // 初始化列表构造
    deque<int> box2 = {1, 2, 3, 4, 5};

    // 拷贝构造，用已有 deque 创建新的 deque
    deque<int> box3(box2);

    // 拷贝初始化，也是合法的
    // deque<int> box3 = box2;

    // 迭代器范围构造，使用 box2 的 [begin, end) 区间创建新容器
    deque<int> box4{box2.begin(), box2.end()};

    // 创建 3 个元素，每个元素的值都是 100
    deque<int> box5(3, 100);

    print(box2);
}

// 容器遍历
void test4()
{   
    cout << "-----vector-----" << endl;
    vector<int> box1 {1, 2, 3, 4, 5};

    // vector 支持随机访问，可以通过下标遍历
    for (int i = 0; i < box1.size(); i++)
    {
        cout << box1[i] << " ";
    }
    cout << endl;

    // 使用迭代器遍历
    for(auto it = box1.begin(); it != box1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 使用范围 for 遍历
    for(auto e : box1)
    {
        cout << e << " ";
    }
    cout << endl;


    cout << "-----list-----" << endl;
    list<int> box2 {1, 2, 3, 4, 5};

    // list 不支持随机访问，因此不能通过下标访问元素
    /*
    for (int i = 0; i < box2.size(); i++)
    {
        cout << box2[i] << " ";
    }
    cout << endl;
    */

    // 使用迭代器遍历
    for(auto it = box2.begin(); it != box2.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 使用范围 for 遍历
    for(auto e : box2)
    {
        cout << e << " ";
    }
    cout << endl;


    cout << "-----deque-----" << endl;
    deque<int> box3 {1, 2, 3, 4, 5};

    // deque 支持随机访问，可以通过下标遍历
    for (int i = 0; i < box3.size(); i++)
    {
        cout << box3[i] << " ";
    }
    cout << endl;

    // 使用迭代器遍历
    for(auto it = box3.begin(); it != box3.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 使用范围 for 遍历
    for(auto e : box3)
    {
        cout << e << " ";
    }
    cout << endl;
}


// vector: push_back() / pop_back()
// 在尾部插入和删除元素
void test5()
{
    vector<int> box {1, 2, 3};
    print(box);

    // 尾部插入元素
    box.push_back(4);
    box.push_back(5);
    print(box);

    // 删除尾部元素
    box.pop_back();
    print(box);
}

// list: push_back() / pop_back()
// 在尾部插入和删除元素
void test6()
{
    list<int> box {1, 2, 3};
    print(box);

    // 尾部插入元素
    box.push_back(4);
    box.push_back(5);
    print(box);

    // 删除尾部元素
    box.pop_back();
    print(box);
}

// deque: push_back() / pop_back()
// 在尾部插入和删除元素
void test7()
{
    deque<int> box {1, 2, 3};
    print(box);

    // 尾部插入元素
    box.push_back(4);
    box.push_back(5);
    print(box);

    // 删除尾部元素
    box.pop_back();
    print(box);
}


// list: push_front() / pop_front()
// 在头部插入和删除元素
void test8()
{
    list<int> box {1, 2, 3};
    print(box);

    // 头部插入元素
    box.push_front(4);
    box.push_front(5);
    print(box);

    // 删除头部元素
    box.pop_front();
    print(box);
}

// deque: push_front() / pop_front()
// 在头部插入和删除元素
void test9()
{
    deque<int> box {1, 2, 3};
    print(box);

    // 头部插入元素
    box.push_front(4);
    box.push_front(5);
    print(box);

    // 删除头部元素
    box.pop_front();
    print(box);
}

// vector 不支持 push_front() / pop_front()
// vector 主要支持尾部高效插入和删除
void test10()
{
    vector<int> box;

    // box.push_front(1); // 错误，vector 不支持 push_front()
    // box.pop_front();   // 错误，vector 不支持 pop_front()
}

int main() 
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    // test7();
    // test8();
    test9();

    return 0;
}