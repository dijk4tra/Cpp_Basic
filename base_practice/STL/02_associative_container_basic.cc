#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

/*
容器,存储内容,键（Key）是否允许重复,迭代器遍历顺序
std::set,仅键（Key）,严格唯一,默认升序（从小到大）
std::multiset,仅键（Key）,允许重复,默认升序（从小到大）
std::map,键值对（Key-Value Pair）,键唯一，值可重复,按键（Key）默认升序
std::multimap,键值对（Key-Value Pair）,键允许重复，值可重复,按键（Key）默认升序
*/

/*
这四个容器虽然名字不同，但它们有一个共同的底层结构——红黑树（Red-Black Tree）。
这意味着它们的所有基本操作（插入、删除、查找）的时间复杂度都是稳定的 O(log n)。

底层结构：红黑树（一种自平衡的二叉搜索树）为什么不用普通的二叉搜索树（BST）？ 
    普通的二叉搜索树在极端情况下（比如按顺序插入 1,2,3,4,5）会退化成一个链表，查找效率从 O(log n) 崩塌到 O(n)。
    红黑树通过一套复杂的红黑节点着色和旋转机制，保证树的高度始终维持在 O(log n) 左右。
为什么元素会自动排序？ 
    因为红黑树在插入节点时，会根据你提供的比较规则（默认是 < 运算符）自动寻找合适的位置插入。
    因此，当你使用迭代器从 begin() 走到 end() 时，输出的数据天然就是有序的。
只读的 Key：
    在 set 中，所有元素都是不可直接修改的（只读）；
    在 map 中，元素的 Key 是不可修改的（std::pair<const Key, T>）。
    如果允许随便修改 Key，红黑树的平衡和有序性就会被瞬间破坏。
*/

// std::set
void test1()
{
    set<int> mySet;

    // 1. 插入元素(insert)
    mySet.insert(40);
    mySet.insert(10);
    mySet.insert(30);
    auto res = mySet.insert(20); // res 是一个 pair，first 是迭代器，second 是 bool
    cout << "插入 20 是否成功？" << (res.second ? "是" : "否") << endl; // 输出: 是
    
    // 思考：重复插入会发生什么？
    auto fail_res = mySet.insert(20);
    if(!fail_res.second)
    {
        cout << "再次插入 20 失败，因为它已经存在了" << endl;
    }

    // 2. 遍历（默认自动排序：10 20 30 40）
    cout << "当前 Set 中的元素: ";
    for (int x : mySet) {
        cout << x << " ";
    }
    cout << endl;

    // 3. 查找 (find) - 返回的是迭代器
    auto it = mySet.find(30);
    if (it != mySet.end()){
        std::cout << "找到了元素: " << *it << "\n";
    } else {
        std::cout << "未找到该元素\n";
    }

    // 4. 删除 (erase) - 可以传迭代器，也可以直接传值
    mySet.erase(30); // 直接删除值为 30 的元素
    
    // 5. 计数/是否存在 (count) - 因为 set 元素唯一，结果只能是 0 或 1
    if (mySet.count(40)){
        cout << "元素 40 存在\n";
    } else {
        cout << "元素 40 不存在\n";
    }

    return;
}

// std::map
void test2()
{
    // Key 为学号(int)，Value 为姓名(string)
    map<int, string> myMap;

    // 1. 插入元素的两种常见方式
    myMap.insert(make_pair(101, "Alice")); // 方式 A：通过 pair 插入
    myMap[102] = "Bob"; // 方式 B：通过[]下标操作符插入（如果 Key 不存在会自动创建）
    myMap[103] = "Charlie";

    // 2. 遍历 map (注意：元素是 pair，.first 是 Key，.second 是 Value)
    cout << "当前 Map 中的元素:\n";
    for (const auto& kv : myMap) {
        cout << "学号: " << kv.first << ", 姓名: " << kv.second << "\n";
    }

    // 3. 查找 (find) - 返回的是迭代器
    auto it = myMap.find(102);
    if (it != myMap.end()){
        std::cout << "找到了学号 102，对应的姓名是: " << it->second << "\n";
    }

    // 4. 修改 Value
    myMap[102] = "Robert"; // 直接通过[]修改 Value

    // 5. 删除 (erase) - 通过 Key 来删除
    myMap.erase(101); // 删除学号为 101 的元素

    return;

    /*
    在 map 中使用 [] 运算符时有一个初学者极易踩雷的副作用：
    如果你执行 std::cout << myMap[999];（其中 999 是一个不存在的 Key），
    map 会自动往红黑树里插入一个 Key 为 999、Value 为默认空值的节点。

    铁律：如果只是想检查某个 Key 是否存在，请使用 find() 或 count()，千万不要用 []！
    */
}


// std::multiset
void test3()
{
    multiset<int> myMultiSet;

    // 1. 插入元素
    myMultiSet.insert(20);
    myMultiSet.insert(10);
    myMultiSet.insert(20); // 再次插入 20，成功！

    // 2. 遍历 (结果：10 20 20 30)
    cout << "当前 multiset 中的元素: ";
    for (int x : myMultiSet){
        cout << x << " "; 
    }
    cout << endl;

    // 3. 计数 (count) - 现在返回值可以是任意大于等于 0 的数
    cout << "20 出现的次数：" << myMultiSet.count(20) << endl; // 输出 2

    // 4. 删除 (erase) —— ⚠️这里有一个经典的坑！
    // 行为 A：如果传入的是具体的值，它会删掉【所有】等于该值的元素！
    myMultiSet.erase(20); // 删除所有值为 20 的元素
    for (int x : myMultiSet) {
        cout << x << " "; // 只剩下 10 30
    }
    cout << endl;

    // 如果只想删除【一个】20，应该怎么做？
    myMultiSet.insert(20);
    myMultiSet.insert(20); // 先补两个 20 进去
    auto it = myMultiSet.find(20); // find 只会返回【第一个】找到的 20 的迭代器
    if (it != myMultiSet.end()) {
        myMultiSet.erase(it); // 传入迭代器，精准删除第一个 20
    }

    cout << "删除一个20后: ";
    for (int x : myMultiSet){
        cout << x << " "; // 剩下 10 20 30
    }
    cout << endl;

    return;
}


// std::multimap
void test4()
{
    // 键：课号(string)，值：选课学生名字(string)
    multimap<string, string> courseMap;

    // 1. 插入元素 (只能用 insert，不能用 [])
    courseMap.insert(make_pair("C++", "Alice"));
    courseMap.insert(make_pair("Java", "Bob"));
    courseMap.insert(std::make_pair("C++", "Charlie")); // C++ 课有多个学生
    courseMap.insert(std::make_pair("C++", "David"));

    // 2. 查找并遍历某个 Key 对应的所有数据
    string searchKey = "C++";

    // equal_range 返回一个 pair，包含两个迭代器：
    // .first 是指向第一个 "C++" 的迭代器 (lower_bound)
    // .second 是指向最后一个 "C++" 后面位置的迭代器 (upper_bound)
    auto range = courseMap.equal_range(searchKey);

    cout << "选修 " << searchKey << " 的学生有:\n";
    for (auto it = range.first; it != range.second; ++it)
    {
        cout << " - " << it->second << "\n";
    }

    return;
}


int main()
{
    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}