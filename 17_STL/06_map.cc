#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

/**
 * 关联式容器 map：
 * - map 用来存储 key-value 键值对
 * - key 不允许重复
 * - value 可以重复
 * - 底层通常使用红黑树实现
 * - 元素会按照 key 自动排序
 * - 默认排序规则是 std::less<Key>，也就是按照 key 升序排序
 */

template<typename Container>
void print(Container &box)
{
    // map 中的每一个元素都是 pair<const Key, Value>
    // p.first 表示 key
    // p.second 表示 value
    for(auto & p : box)
    {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
}

template<typename K, typename V>
void print2(map<K,V> &box)
{
    // 专门用于打印 map<K, V> 类型的容器
    for(auto & p : box)
    {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
}


// map 容器的构造方式
void test1()
{
    // 无参构造，创建一个空的 map
    map<int,string> box1;

    // 初始化列表构造
    // 每个元素都是一个 key-value 键值对
    map<int,string> box2{
        {1,"a"},
        {2,"b"},
        {3,"c"}
    };

    // 使用 pair 构造键值对
    map<int,string> box3{
        pair<int,string>(1,"a"),
        pair<int,string>(2,"b"),
        pair<int,string>(3,"c")
    };

    // 使用 make_pair 构造键值对
    map<int,string> box4{
        make_pair(1,"a"),
        make_pair(2,"b"),
        make_pair(3,"c")
    };
    
    // 使用迭代器区间构造
    // 构造范围为 [begin, end)，包含 begin，不包含 end
    map<int,string> box5{ box2.begin(), box2.end() };

    // 拷贝构造
    map<int,string> box6(box2);
    // map<int,string> box6 = box2;
} 


// map 查找操作 count / find
void test2()
{
    map<string,int> box{
        {"a",1},
        {"a",1},
        {"b",2},
        {"c",3}
    };

    // map 的 key 不允许重复
    // 所以上面两个 key 为 "a" 的元素，只会保留一个
    print(box);
    print2(box);

    cout << "-----" << endl;

    // count():
    // 对于 map 来说，key 不重复
    // 找到了返回 1，未找到返回 0
    // int result = box.count("a");
    int result = box.count("d");
    cout << result << endl;

    cout << "-----" << endl;

    // find():
    // 找到了返回指向对应位置的迭代器
    // 未找到返回 end()
    // auto it = box.find("a");
    auto it = box.find("d");

    if(it != box.end()){
        cout << "找到" << endl;

        // it->first 表示 key
        // it->second 表示 value
        cout << it->first << " = " << it->second << endl;
    }else{
        cout << "未找到" << endl;
    }
}

// map 插入元素 insert
void test3()
{
    map<string,int> box;

    // 插入单个键值对
    box.insert(pair<string,int>("a",1));
    box.insert({"b",2});
    box.insert(make_pair("zs",20));

    // map 会按照 key 自动升序排序
    print(box);

    // 批量插入数据：初始化列表方式
    box.insert({
        {"ls",21},
        {"ww",20},
        {"zl",22},
    });

    print(box);

    // 也可以使用迭代器区间插入
    // box.insert(first, last)
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

    // begin() 指向第一个元素
    auto it = box.begin();

    // 迭代器后移，指向第二个元素
    ++it;

    // 删除迭代器指向的元素
    box.erase(it);

    print(box);
}

// map 可以根据 key 获取或者修改对应的 value
void test5()
{
    map<string,int> box;

    box.insert(pair<string,int>("a",1));
    box.insert({"b",2});
    box.insert(make_pair("zs",20));

    // operator[] 的作用：
    // 1. 如果 key 存在，返回该 key 对应的 value
    // 2. 如果 key 不存在，会先插入一个新的 key-value，再返回 value
    // 这里 "c" 不存在，所以会插入 {"c", 0}，然后再把 value 修改为 3
    box["c"] = 3;

    print(box);

    // 如果 key 已经存在，可以通过 [] 修改对应的 value
    box["a"] = 100;

    // 通过 key 访问对应的 value
    cout << box["a"] << endl;
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
 * map 使用自定义类型作为 key 时，处理方式和 set 类似。
 *
 * 原因：
 * - map 会按照 key 进行排序
 * - 所以 key 类型必须能够比较大小
 *
 * 常见方式：
 * 1. 自定义类型中重载 operator<
 * 2. 使用函数对象，自定义比较器 operator()
 * 3. 对 std::less<Student> 做特化处理
 *
 * 本例使用第 2 种方式：自定义函数对象 StudentCompare。
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
    // map<Student, int, StudentCompare>
    // key 类型是 Student
    // value 类型是 int
    // 比较规则使用 StudentCompare
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