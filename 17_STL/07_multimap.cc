#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

/**
 * 关联式容器 multimap：
 * - multimap 用来存储 key-value 键值对
 * - key 可以重复
 * - value 可以重复
 * - 底层通常使用红黑树实现
 * - 元素会按照 key 自动排序
 * - 默认排序规则是 std::less<Key>，也就是按照 key 升序排序
 *
 * map 和 multimap 的区别：
 * - map：key 不允许重复
 * - multimap：key 允许重复
 */

template<typename Container>
void print(Container &box)
{
    // multimap 中的每一个元素都是 pair<const Key, Value>
    // p.first 表示 key
    // p.second 表示 value
    for(auto & p : box)
    {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
}

template<typename K, typename V>
void print2(multimap<K,V> &box)
{
    // 专门用于打印 multimap<K, V> 类型的容器
    for(auto & p : box)
    {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
}


// multimap 容器的构造方式
void test1()
{
    // 无参构造，创建一个空的 multimap
    multimap<int,string> box1;

    // 初始化列表构造
    // multimap 允许 key 重复
    multimap<int,string> box2{
        {3,"c"},
        {3,"c"},
        {1,"a"},
        {2,"b"},
        {2,"bb"},
        {2,"bbb"}
    };

    // 使用 pair 构造键值对
    multimap<int,string> box3{
        pair<int,string>(1,"a"),
        pair<int,string>(2,"b"),
        pair<int,string>(3,"c")
    };

    // 使用 make_pair 构造键值对
    multimap<int,string> box4{
        make_pair(1,"a"),
        make_pair(2,"b"),
        make_pair(3,"c")
    };
    
    // 使用迭代器区间构造
    // 构造范围为 [begin, end)，包含 begin，不包含 end
    multimap<int,string> box5{ box2.begin(), box2.end() };

    // 拷贝构造
    multimap<int,string> box6(box2);
    // multimap<int,string> box6 = box2;

    // 输出结果会按照 key 升序排列
    print(box2);
} 


// multimap 查找操作 count / find
void test2()
{
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

    // count():
    // 对于 multimap 来说，key 可以重复
    // 找到了返回该 key 对应元素的个数，未找到返回 0
    // int result = box.count("a");
    int result = box.count("d");
    cout << result << endl;

    cout << "-----" << endl;

    // find():
    // 找到了返回目标 key 对应元素的迭代器
    // 如果有多个相同的 key，通常返回其中第一个匹配位置的迭代器
    // 没找到返回 end()
    // auto it = box.find("a");
    auto it = box.find("d");

    if(it != box.end()){
        cout << "找到" << endl;

        // it->first 表示 key
        // it->second 表示 value
        cout << it->first << endl;
        cout << it->second << endl;
    }else{
        cout << "未找到" << endl;
    }
}

// multimap 插入元素 insert
void test3()
{
    multimap<string,int> box;

    // 插入单个键值对
    box.insert(pair<string,int>("a",1));
    box.insert({"b",2});
    box.insert(make_pair("zs",20));

    // multimap 会按照 key 自动升序排序
    print(box);

    // 批量插入数据：初始化列表方式
    box.insert({
        {"ls",21},
        {"ww",20},
        {"zl",22},
    });

    print(box);

    // 也可以使用迭代器区间插入
    // box.insert(box2.begin(), box2.end());
}

// erase 删除元素
void test4()
{
    multimap<string,int> box;

    // 插入单个键值对
    box.insert(pair<string,int>("a",1));
    box.insert({"b",2});
    box.insert(make_pair("zs",20));

    print(box);

    // begin() 指向第一个元素
    auto it = box.begin();

    // 迭代器后移，指向第二个元素
    ++it;

    // 删除迭代器指向的元素
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

    // multimap 不支持 operator[]
    // 因为 multimap 的 key 可以重复
    // 如果使用 box["a"]，无法确定访问的是 1、11 还是 111
    // cout << box["a"] << endl;
}

class Student
{
public:
    Student(int id, string name, int age)
    :m_id(id)
    ,m_name(name)
    ,m_age(age)
    {}

    int m_id;       // 学号
    string m_name;  // 姓名
    int m_age;      // 年龄
};

// 重载 operator<<，方便输出 Student 对象
ostream & operator<<(ostream & os, const Student & s)
{
    os << s.m_id << " " << s.m_name << " " << s.m_age << endl;
    return os;
}

/**
 * map / multimap 使用自定义类型作为 key 时，处理方式和 set 类似。
 *
 * 原因：
 * - map / multimap 会按照 key 进行排序
 * - 所以 key 类型必须能够比较大小
 *
 * 常见方式：
 * 1. 自定义类型重载 operator<
 * 2. 使用函数对象方式，自定义比较器 operator()
 * 3. 对 std::less<Student> 做特化处理
 */

// 自定义比较器
struct StudentCompare
{
    // 重载 operator()，让 StudentCompare 对象可以像函数一样被调用
    bool operator()(const Student & lhs, const Student & rhs) const
    {
        // 指定比较规则：按照年龄 age 升序排序
        // lhs 的年龄小于 rhs 的年龄，则 lhs 排在前面
        return lhs.m_age < rhs.m_age;
    }
};

void test6()
{
    // 注意：
    // 这里使用的是 map，不是 multimap
    // map 的 key 不允许重复
    // 但这不是编译错误，所以不修改代码
    map<Student,int,StudentCompare> box;

    box.insert({Student{2,"zs",18},2});

    // 当前比较规则只比较 m_age
    // 所以只要年龄相同，map 就认为 key 重复
    // 这一条不会插入成功
    box.insert({Student{2,"zs",18},2});

    box.insert({Student{1,"ls",20},1});
    box.insert({Student{3,"ww",19},3});

    // 输出结果会按照 Student 的年龄升序排列
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