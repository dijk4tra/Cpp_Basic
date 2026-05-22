#include <iostream>
#include <set>
#include <list>
#include <vector>

using namespace std;

/**
 * 关联式容器 set
 *
 * 关联式容器：
 * 1. 底层通常使用红黑树实现
 * 2. 元素会按照 key 自动排序
 * 3. 查找、插入、删除效率较高，通常为 O(logN)
 *
 * set：
 * - 只存储 key
 * - key 不允许重复
 * - 默认按照升序排序
 *
 * multiset：
 * - 只存储 key
 * - key 允许重复
 * - 默认按照升序排序
 *
 * map：
 * - 存储 key-value 键值对
 * - key 不允许重复
 * - value 可以重复
 * - 默认按照 key 升序排序
 *
 * multimap：
 * - 存储 key-value 键值对
 * - key 允许重复
 * - value 可以重复
 * - 默认按照 key 升序排序
 *
 * 注意：
 * set / map 的 key 是唯一的，不能重复；
 * multiset / multimap 的 key 可以重复。
 */

template<typename Container>
void print(Container &box)
{
    // 范围 for 遍历容器中的所有元素
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

// set 容器的构造方式
void test1()
{
    // 无参构造，创建一个空的 set
    set<int> box1;

    // 初始化列表构造
    set<int> box2{1,2,3,4,5};

    // 拷贝构造
    set<int> box3(box2);
    // set<int> box3 = box2;

    // 使用迭代器区间构造
    // 构造范围为 [begin, end)，包含 begin，不包含 end
    set<int> box4{ box2.begin(), box2.end() };

    print(box2);
} 


// set 插入元素 insert
void test2()
{
    set<int> box;

    // insert 插入单个元素
    // 返回值是 pair<iterator, bool>
    // first：指向插入元素位置的迭代器
    // second：是否插入成功，true 表示成功，false 表示失败
    auto p = box.insert(2);

    if(p.second){
        cout << "插入成功" << endl;
        cout << *(p.first) << endl;
    }else{
        cout << "插入失败" << endl;
    }

    // set 不允许重复元素，所以再次插入 2 会失败
    box.insert(2);

    // set 会自动按照升序排序
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

// set 查找元素 count / find
void test3()
{
    set<int> box{1,2,3,4,5};

    // count：
    // 对于 set 来说，元素不重复
    // 找到返回 1，未找到返回 0
    cout << box.count(3) << endl;
    cout << box.count(6) << endl;

    // find：
    // 找到返回指向该元素的迭代器
    // 未找到返回 end()
    // auto it = box.find(3);
    auto it = box.find(6);

    if(it != box.end()){
        cout << "找到" << endl;
        cout << *it << endl;
    }else{
        cout << "未找到" << endl;
    }

}


// erase 删除元素
void test4()
{
    set<int> box{1,2,3,4,5};

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

// set 不支持下标访问
void test5()
{
    set<int> box{1,2,3,4,5};

    // set 不支持 operator[]，不能通过下标访问元素
    // cout << box[0] << endl;

    // 可以通过迭代器访问元素
    auto it = box.begin();
    cout << *it << endl;

    // set 中的元素不能通过迭代器直接修改
    // 因为修改元素可能破坏 set 的有序结构
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