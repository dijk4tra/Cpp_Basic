#include <iostream>
#include <set>
#include <list>
#include <vector>

using namespace std;

/**
 * 关联式容器 multiset：
 * - multiset 是允许元素重复的集合
 * - 底层通常使用红黑树实现
 * - 元素会按照比较规则自动排序
 * - 默认排序规则是 std::less<T>，也就是升序排序
 *
 * set 和 multiset 的区别：
 * - set：元素不能重复
 * - multiset：元素可以重复
 */

template<typename Container>
void print(Container &box)
{
    // 遍历容器中的所有元素
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

// multiset 容器的构造方式
void test1()
{
    // 无参构造，创建一个空的 multiset
    multiset<int> box1;

    // 初始化列表构造
    multiset<int> box2{1,2,3,4,5};

    // 拷贝构造
    multiset<int> box3(box2);
    // multiset<int> box3 = box2;

    // 使用迭代器区间构造
    // 构造范围为 [begin, end)，包含 begin，不包含 end
    multiset<int> box4{ box2.begin(), box2.end() };

    print(box2);
} 


// multiset 插入元素 insert
void test2()
{
    multiset<int> box;

    // insert 插入单个元素
    // multiset 允许重复元素，所以插入一般都会成功
    // 返回值是指向新插入元素位置的迭代器
    auto it = box.insert(2);
    cout << *it << endl;

    // multiset 允许插入重复元素
    box.insert(2);

    // 插入后，元素会按照升序自动排序
    box.insert(1);
    box.insert(4);
    box.insert(3);
    print(box);

    cout << "----" << endl;

    // 使用迭代器区间插入多个元素
    list<int> box2{10,20,30};
    box.insert(box2.begin(), box2.end());
    print(box);

    cout << "----" << endl;

    // 使用初始化列表插入多个元素
    box.insert({100,200});
    print(box);
}

// multiset 查找元素 count / find
void test3()
{
    multiset<int> box{1,2,3,3,3,4,4,5};
    print(box);

    // count：
    // 对于 multiset 来说，元素可以重复
    // 找到返回该元素出现的次数，未找到返回 0
    cout << box.count(3) << endl;
    cout << box.count(6) << endl;

    // find：
    // 找到返回指向目标元素的迭代器
    // 如果有多个相同元素，通常返回其中第一个匹配位置的迭代器
    // 未找到返回 end()
    auto it = box.find(3);
    // auto it = box.find(6);

    if(it != box.end()){
        cout << "找到" << endl;

        // 当前 box 中有三个 3，find(3) 返回其中一个 3 的位置
        cout << *it << endl;
        ++it;
        cout << *it << endl;
        ++it;
        cout << *it << endl;
        ++it;

        // 继续后移后，会访问到 3 后面的元素，也就是 4
        cout << *it << endl;
    }else{
        cout << "未找到" << endl;
    }

}

// erase 删除元素
void test4()
{
    multiset<int> box{1,2,3,4,5};

    // begin() 指向第一个元素
    auto it = box.begin();

    // 迭代器后移，指向第二个元素
    ++it;

    // erase 删除迭代器指向的元素
    // 返回值是指向被删除元素下一个位置的迭代器
    auto it2 = box.erase(it);

    cout << *it2 << endl;
    print(box);
}

// multiset 不支持下标访问
void test5()
{
    multiset<int> box{1,2,3,4,5};

    // multiset 不支持 operator[]，不能通过下标访问元素
    // cout << box[0] << endl;

    // 可以通过迭代器访问元素
    auto it = box.begin();
    cout << *it << endl;

    // multiset 中的元素不能通过迭代器直接修改
    // 因为修改元素可能破坏 multiset 的有序结构
    // *it = 10;
}

int main(int argc, char const *argv[])
{
    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}