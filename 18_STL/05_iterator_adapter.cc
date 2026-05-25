#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>
#include <list>

using namespace std;

/**
 * 迭代器适配器
 *
 * 插入迭代器适配器：
 *
 * 1. back_insert_iterator
 *    尾部插入迭代器，底层调用容器的 push_back()
 *
 * 2. front_insert_iterator
 *    头部插入迭代器，底层调用容器的 push_front()
 *
 * 3. insert_iterator
 *    指定位置插入迭代器，底层调用容器的 insert()
 *
 * 以上三种都是迭代器适配器类型。
 *
 * 注意：
 * 使用插入迭代器适配器时，要确保容器支持对应的成员函数。
 *
 * 例如：
 * vector 支持 push_back()，但不支持 push_front()
 * list 支持 push_back()、push_front()、insert()
 *
 *
 * 创建插入迭代器适配器的辅助函数：
 *
 * 1. back_inserter()
 *    创建 back_insert_iterator 对象
 *
 * 2. front_inserter()
 *    创建 front_insert_iterator 对象
 *
 * 3. inserter()
 *    创建 insert_iterator 对象
 *
 * 以上三个是函数，用于简化插入迭代器对象的创建。
 */


// 把一个容器中的元素复制到另一个空容器中
// 使用尾部插入，底层调用目标容器的 push_back()
void test1()
{
    vector<int> box1{1, 2, 3, 4, 5};
    vector<int> box2;

    // 结合 copy 算法和尾插迭代器适配器
    // back_insert_iterator 会把写入操作转换为 box2.push_back()
    back_insert_iterator<vector<int>> it{ box2 };

    // 将 box1 中的元素依次复制到 box2 尾部
    std::copy(box1.begin(), box1.end(), it);

    // 打印 box2
    std::copy(box2.begin(), box2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}


// 尾部插入
void test2()
{
    vector<int> box1{1, 2, 3, 4, 5};
    vector<int> box2;

    // 结合 copy 算法和尾插迭代器适配器
    // 使用 back_inserter() 函数简化 back_insert_iterator 的创建
    std::copy(box1.begin(), box1.end(), back_inserter(box2));

    // 打印 box2
    std::copy(box2.begin(), box2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}


// 头部插入，底层调用目标容器的 push_front()
void test3()
{
    vector<int> box1{1, 2, 3, 4, 5};
    list<int> box2;

    // 结合 copy 算法和头插迭代器适配器
    // front_insert_iterator 会把写入操作转换为 box2.push_front()
    front_insert_iterator<list<int>> it{ box2 };

    // 将 box1 中的元素依次插入到 box2 头部
    // 注意：每次都插入到头部，所以最终顺序会变成 5 4 3 2 1
    std::copy(box1.begin(), box1.end(), it);

    // 打印 box2
    std::copy(box2.begin(), box2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}


// 头部插入
void test4()
{
    vector<int> box1{1, 2, 3, 4, 5};
    list<int> box2;

    // 结合 copy 算法和头插迭代器适配器
    // 使用 front_inserter() 函数简化 front_insert_iterator 的创建
    std::copy(box1.begin(), box1.end(), front_inserter(box2));

    // 打印 box2
    // 输出顺序为：5 4 3 2 1
    std::copy(box2.begin(), box2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}


// 中间插入，底层调用目标容器的 insert() 函数
void test5()
{
    vector<int> box1{1, 2, 3, 4, 5};
    list<int> box2{6, 7, 8};

    // 结合 copy 算法和插入迭代器适配器
    // 中间插入需要指定插入位置
    auto it = box2.begin();

    // it 指向第二个元素 7
    it++;

    // inserter(box2, it) 创建 insert_iterator 对象
    // 将 box1 中的元素插入到 it 指向的位置之前
    //
    // 插入后 box2 为：6 1 2 3 4 5 7 8
    std::copy(box1.begin(), box1.end(), inserter(box2, it));

    // 打印 box2
    std::copy(box2.begin(), box2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}


void test6()
{
    vector<int> box1{1, 2, 3, 4, 5};

    // 正向遍历：
    // for (auto it = box1.begin(); it != box1.end(); ++it)

    // 反向遍历可以使用反向迭代器 reverse_iterator
    // rbegin() 指向最后一个元素
    // rend() 指向第一个元素之前的位置

    // auto it = box1.rbegin();
    vector<int>::reverse_iterator it = box1.rbegin();

    // 当前 it 指向最后一个元素 5
    cout << *it << endl;

    // 对反向迭代器执行 ++it
    // 从逻辑上看是向后遍历下一个元素
    // 从底层位置看，实际是向容器左侧移动
    ++it;

    // 当前 it 指向元素 4
    cout << *it << endl;
}


void test7()
{
    vector<int> box1{1,2,3,4,5};

    // 使用反向迭代器倒序遍历容器
    // rbegin() 指向最后一个元素
    // rend() 指向第一个元素之前的位置
    for(auto it  = box1.rbegin() ; it != box1.rend() ; ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}


int main(int argc, char *argv[])
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