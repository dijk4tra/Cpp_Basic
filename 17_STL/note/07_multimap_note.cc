#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

/**
 * 关联式容器 multimap：
 *
 * multimap 是 STL 中的关联式容器。
 *
 * 特点：
 * 1. multimap 用来存储 key-value 键值对
 *    key 表示键，value 表示值。
 *
 * 2. key 可以重复
 *    同一个 key 可以对应多个 value。
 *
 * 3. value 可以重复
 *    不同的 key 可以对应相同的 value。
 *
 * 4. 底层通常使用红黑树实现
 *    所以插入、删除、查找的效率通常是 O(logN)。
 *
 * 5. 元素会按照 key 自动排序
 *    插入元素时，不是按照插入顺序保存，
 *    而是按照 key 的比较规则排序。
 *
 * 6. 默认排序规则是 std::less<Key>
 *    也就是默认按照 key 升序排序。
 *
 *
 * map 和 multimap 的区别：
 * 1. map
 *    key 不允许重复。
 *
 * 2. multimap
 *    key 允许重复。
 */

template<typename Container>
void print(Container &box)
{
    /**
     * multimap 中的每一个元素都是 pair<const Key, Value>
     *
     * pair 可以理解为一个保存两个数据的对象。
     *
     * p.first：
     * 表示 key。
     *
     * p.second：
     * 表示 value。
     *
     * 注意：
     * multimap 中的 key 是 const 的，
     * 不能通过迭代器直接修改 key。
     *
     * 原因：
     * multimap 会根据 key 维护内部排序结构，
     * 如果允许直接修改 key，
     * 可能会破坏 multimap 的有序结构。
     */
    for(auto & p : box)
    {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
}

template<typename K, typename V>
void print2(multimap<K,V> &box)
{
    /**
     * 专门用于打印 multimap<K, V> 类型的容器
     *
     * K：
     * 表示 key 的类型。
     *
     * V：
     * 表示 value 的类型。
     *
     * 这里的写法比上面的 print 更具体，
     * 只能打印 multimap<K, V> 类型的容器。
     */
    for(auto & p : box)
    {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
}


// multimap 容器的构造方式
void test1()
{
    /**
     * 无参构造
     *
     * 创建一个空的 multimap<int, string> 容器。
     *
     * int：
     * 表示 key 的类型。
     *
     * string：
     * 表示 value 的类型。
     */
    multimap<int,string> box1;

    /**
     * 初始化列表构造
     *
     * 每个元素都是一个 key-value 键值对。
     *
     * multimap 允许 key 重复，
     * 所以下面多个 key 为 2 或 3 的键值对
     * 都可以被保存。
     *
     * multimap 会按照 key 自动升序排序。
     */
    multimap<int,string> box2{
        {3,"c"},
        {3,"c"},
        {1,"a"},
        {2,"b"},
        {2,"bb"},
        {2,"bbb"}
    };

    /**
     * 使用 pair 构造键值对
     *
     * pair<int,string>(1,"a")
     * 表示创建一个 pair 对象。
     *
     * first 是 1，
     * second 是 "a"。
     */
    multimap<int,string> box3{
        pair<int,string>(1,"a"),
        pair<int,string>(2,"b"),
        pair<int,string>(3,"c")
    };

    /**
     * 使用 make_pair 构造键值对
     *
     * make_pair 可以根据传入的数据，
     * 自动推导 pair 中两个数据的类型。
     *
     * make_pair(1,"a")
     * 会生成一个键值对。
     */
    multimap<int,string> box4{
        make_pair(1,"a"),
        make_pair(2,"b"),
        make_pair(3,"c")
    };

    /**
     * 使用迭代器区间构造
     *
     * box2.begin()：
     * 指向 box2 中第一个元素的迭代器。
     *
     * box2.end()：
     * 指向 box2 最后一个元素后面位置的迭代器。
     *
     * 构造范围为 [begin, end)，
     * 包含 begin 指向的元素，
     * 不包含 end 指向的位置。
     */
    multimap<int,string> box5{ box2.begin(), box2.end() };

    /**
     * 拷贝构造
     *
     * 使用已经存在的 multimap 对象 box2，
     * 初始化一个新的 multimap 对象 box6。
     *
     * box6 和 box2 是两个独立的容器。
     */
    multimap<int,string> box6(box2);

    // 下面这种写法也是拷贝构造
    // multimap<int,string> box6 = box2;

    /**
     * 输出结果会按照 key 升序排列。
     *
     * 即使初始化时的顺序是 3、3、1、2、2、2，
     * 最终输出时也会按照 key 排序。
     */
    print(box2);
}


// multimap 查找操作 count / find
void test2()
{
    /**
     * multimap 初始化
     *
     * multimap 允许 key 重复，
     * 所以下面两个 key 为 "a" 的键值对
     * 都会被保存。
     */
    multimap<string,int> box{
        {"a",1},
        {"a",1},
        {"b",2},
        {"c",3}
    };

    // multimap 允许 key 重复
    print(box);
    print2(box);

    cout << "-----" << endl;

    /**
     * count 函数
     *
     * 作用：
     * 统计某个 key 在 multimap 中出现的次数。
     *
     * 对于 multimap 来说，
     * key 允许重复，
     * 所以 count 的结果可能大于 1。
     *
     * 找到：
     * 返回该 key 对应元素的个数。
     *
     * 未找到：
     * 返回 0。
     */
    // int result = box.count("a");
    int result = box.count("d");
    cout << result << endl;

    cout << "-----" << endl;

    /**
     * find 函数
     *
     * 作用：
     * 根据 key 查找对应的键值对。
     *
     * 找到：
     * 返回目标 key 对应元素的迭代器。
     *
     * 如果有多个相同的 key，
     * 通常返回其中第一个匹配位置的迭代器。
     *
     * 没找到：
     * 返回 end()。
     */
    // auto it = box.find("a");
    auto it = box.find("d");

    if(it != box.end()){
        cout << "找到" << endl;

        /**
         * it 是迭代器。
         *
         * it->first：
         * 表示当前键值对的 key。
         *
         * it->second：
         * 表示当前键值对的 value。
         */
        cout << it->first << endl;
        cout << it->second << endl;
    }else{
        cout << "未找到" << endl;
    }
}

// multimap 插入元素 insert
void test3()
{
    // 创建一个空的 multimap<string, int> 容器
    multimap<string,int> box;

    /**
     * 插入单个键值对
     *
     * multimap 中保存的是 key-value 键值对，
     * 所以插入时需要插入 pair 类型的数据。
     *
     * 和 map 不同：
     * multimap 允许 key 重复，
     * 所以插入重复 key 一般也会成功。
     */

    // 方式一：使用 pair 构造键值对
    box.insert(pair<string,int>("a",1));

    // 方式二：使用初始化列表构造键值对
    box.insert({"b",2});

    // 方式三：使用 make_pair 构造键值对
    box.insert(make_pair("zs",20));

    /**
     * multimap 会按照 key 自动升序排序。
     *
     * 对于 multimap<string, int> 来说，
     * 默认按照 string 类型的 key 升序排序。
     */
    print(box);

    /**
     * 批量插入数据：初始化列表方式
     *
     * insert 可以一次性插入多个键值对。
     */
    box.insert({
        {"ls",21},
        {"ww",20},
        {"zl",22},
    });

    print(box);

    /**
     * 也可以使用迭代器区间插入
     *
     * 语法：
     * box.insert(first, last);
     *
     * 插入范围为 [first, last)，
     * 包含 first，
     * 不包含 last。
     */
    // box.insert(box2.begin(), box2.end());
}

// erase 删除元素
void test4()
{
    map<string,int> box;

    // 插入单个键值对
    box.insert(pair<string,int>("a",1));
    box.insert({"b",2});
    box.insert(make_pair("zs",20));

    print(box);

    /**
     * begin()
     *
     * 返回指向容器中第一个元素的迭代器。
     *
     * 对于 map / multimap 来说，
     * 第一个元素是按照 key 排序后的第一个元素。
     */
    auto it = box.begin();

    /**
     * 迭代器后移
     *
     * ++it 表示让迭代器指向下一个元素。
     */
    ++it;

    /**
     * erase 删除元素
     *
     * 这里调用的是：
     * erase(iterator pos)
     *
     * 作用：
     * 删除迭代器 pos 指向的键值对。
     */
    box.erase(it);

    print(box);
}

// multimap 中，不能根据 key 使用 [] 获取或者修改对应的 value
// 这一点和 map 不一样
void test5()
{
    multimap<string,int> box;

    box.insert(pair<string,int>("a",1));
    box.insert(pair<string,int>("a",11));
    box.insert(pair<string,int>("a",111));

    /**
     * multimap 不支持 operator[]
     *
     * 原因：
     * multimap 的 key 可以重复。
     *
     * 例如当前有三个 key 为 "a" 的键值对：
     * {"a", 1}
     * {"a", 11}
     * {"a", 111}
     *
     * 如果使用：
     * box["a"]
     *
     * 编译器无法确定到底要访问哪一个 value，
     * 所以 multimap 不提供 operator[]。
     */
    // cout << box["a"] << endl;
}

class Student
{
public:
    /**
     * 构造函数
     *
     * 创建 Student 对象时，
     * 需要传入学号、姓名、年龄。
     *
     * 初始化列表：
     * 直接对成员变量进行初始化。
     */
    Student(int id, string name, int age)
    :m_id(id)
    ,m_name(name)
    ,m_age(age)
    {}

    int m_id;       // 学号
    string m_name;  // 姓名
    int m_age;      // 年龄
};

/**
 * 重载 operator<<
 *
 * 作用：
 * 让 Student 对象可以直接通过 cout 输出。
 *
 * 如果没有重载 operator<<，
 * cout << s 这样的写法无法编译通过。
 *
 * 返回 ostream &：
 * 是为了支持连续输出。
 */
ostream & operator<<(ostream & os, const Student & s)
{
    os << s.m_id << " " << s.m_name << " " << s.m_age << endl;
    return os;
}

/**
 * map / multimap 使用自定义类型作为 key 时，处理方式和 set 类似。
 *
 * 原因：
 * 1. map / multimap 会按照 key 进行排序
 *    所以 key 类型必须能够比较大小。
 *
 * 2. map / multimap 会根据 key 判断是否重复
 *    如果两个 key 被比较规则认为是等价的，
 *    那么它们就会被认为是相同 key。
 *
 *
 * 常见方式：
 * 1. 自定义类型重载 operator<
 *    让 key 类型本身具备比较能力。
 *
 * 2. 使用函数对象方式，自定义比较器 operator()
 *    将比较器作为 map / multimap 的第三个模板参数。
 *
 * 3. 对 std::less<Student> 做特化处理
 *    修改 Student 类型默认使用的 std::less 比较规则。
 */

// 自定义比较器
struct StudentCompare
{
    /**
     * 重载 operator()
     *
     * 作用：
     * 指定两个 Student 类型的 key 之间的比较规则。
     *
     * 参数：
     * lhs：left hand side，左操作数
     * rhs：right hand side，右操作数
     *
     * 返回值：
     * true：
     * 表示 lhs 应该排在 rhs 前面。
     *
     * false：
     * 表示 lhs 不应该排在 rhs 前面。
     *
     * 函数后面的 const：
     * 表示该函数不会修改 StudentCompare 对象本身。
     */
    bool operator()(const Student & lhs, const Student & rhs) const
    {
        /**
         * 指定比较规则：
         * 按照年龄 age 升序排序。
         *
         * lhs 的年龄小于 rhs 的年龄，
         * 则 lhs 排在 rhs 前面。
         *
         * 注意：
         * 当前比较规则只比较 m_age。
         *
         * 如果两个 Student 的年龄相同，
         * 比较器会认为它们是等价 key。
         */
        return lhs.m_age < rhs.m_age;
    }
};

void test6()
{
    /**
     * 注意：
     * 这里使用的是 map，不是 multimap。
     *
     * map 的 key 不允许重复，
     * multimap 的 key 才允许重复。
     *
     * 这里不是编译错误，
     * 只是和当前文件主要讲解的 multimap 不完全一致。
     */
    map<Student,int,StudentCompare> box;

    /**
     * 插入键值对
     *
     * Student{2,"zs",18}：
     * 作为 key。
     *
     * 2：
     * 作为 value。
     */
    box.insert({Student{2,"zs",18},2});

    /**
     * 当前比较规则只比较 m_age。
     *
     * 所以只要两个 Student 对象的 m_age 相同，
     * map 就认为它们是等价 key。
     *
     * 前面已经插入过年龄为 18 的 Student，
     * 所以这里再次插入年龄为 18 的 Student 时，
     * 插入不会成功。
     */
    box.insert({Student{2,"zs",18},2});

    /**
     * 继续插入其他键值对
     *
     * 最终 map 会按照 Student 的年龄升序排列：
     * 18, 19, 20
     */
    box.insert({Student{1,"ls",20},1});
    box.insert({Student{3,"ww",19},3});

    /**
     * 输出结果
     *
     * print 内部遍历 map。
     *
     * p.first：
     * Student 类型的 key。
     *
     * p.second：
     * int 类型的 value。
     *
     * 因为 Student 重载了 operator<<，
     * 所以 p.first 可以直接输出。
     */
    print(box);
}

int main(int argc, char const *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}