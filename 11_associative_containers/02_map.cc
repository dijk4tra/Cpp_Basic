#include <iostream> 
#include <map>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;
using std::vector;

/**
 * map：
 * 1. 存储双列数据，即一对一对的数据
 * 2. 每个元素都是 key-value 键值对，具有自我描述性
 *
 * 例如：
 * name = "zs"
 * city = "BJ"
 *
 * 底层通常采用红黑树实现
 *
 * 特点：
 * 1. key 不能重复
 * 2. 元素会按照 key 自动排序，默认按 key 升序排列
 *
 * map 的使用：
 * 需要同时指明 key 和 value 的数据类型
 *
 * 语法：
 * map<key 的类型, value 的类型>
 */

// map 容器的构造
void test1()
{
    // 无参构造：创建一个空的 map 容器
    map<int,string> m1; // 每个元素的类型是 pair<const int, string>

    // 通过初始化列表构造，存储的是 pair 对象
    map<int,string> m2{
        pair<int,string>{2,"zs"},
        pair<int,string>{1,"ls"},
        pair<int,string>{3,"ww"}
    };

    // 简写方式：直接使用 {key, value}
    map<int,string> m3{
        {2,"zs"},
        {1,"ls"},
        {3,"ww"}
    };
    
    // 通过 make_pair 函数创建 pair 对象
    map<int,string> m4{
        std::make_pair(2,"zs"),
        std::make_pair(1,"ls"),
        std::make_pair(3,"ww")
    };

    // 通过迭代器区间构造
    map<int,string> m5{ m4.begin(), m4.end() };

    // 通过拷贝构造函数构造
    map<int,string> m6{ m4 };
    
    // key 和 value 可以使用不同的数据类型
    map<string,string> m7;
    map<string,int> m8;
    map<string,vector<int>> m9;
}

// 遍历 map：增强 for 循环方式
void visitMap(map<int,string> & m)
{
    for(auto & p : m){
        // p 是 map 中的一个元素，本质上是一个键值对
        // p.first 表示 key，p.second 表示 value
        cout << p.first << " = " << p.second << endl;
    }
    cout << endl;
}

// 遍历 map：迭代器方式
void visitMap2(map<int,string> & m)
{
    auto it = m.begin();
    for(; it != m.end(); ++it){
        /* cout << (*it).first << endl; */
        /* cout << (*it).second << endl; */

        // it 指向 map 中的一个键值对
        // it->first 表示 key，it->second 表示 value
        cout << it->first << endl;
        cout << it->second << endl;
    }
    cout << endl;
}

// 验证 map 的特点
void test2()
{
    map<int,string> m{
        {2,"zs"},  
        {2,"zs"},  
        {5,"zs"},  
        {1,"ls"},  
        {3,"ww"}  
    };

    visitMap(m);

    // key 不可重复，value 可以重复
    // 元素会按照 key 自动排序，默认升序
}

// map 的查找操作
void test3()
{
    map<int,string> m{
        {2,"zs"},  
        {2,"zs"},  
        {5,"zs"},  
        {1,"ls"},  
        {3,"ww"}  
    };

    // count(目标 key)
    // 对于 map 而言，key 不能重复
    // 找到返回 1，未找到返回 0
    int result = m.count(3);
    if(result){
        cout << "find success!" << endl;
    }else{
        cout << "find failed!" << endl;
    }

    cout << "---------" << endl;

    // find(目标 key)
    // 找到：返回指向该键值对的迭代器
    // 未找到：返回 end()
    auto it = m.find(3);
    if(it != m.end()){
        cout << "find success!" << endl;
        cout << it->first << endl;
        cout << it->second << endl;
    }
}

// insert 插入操作
void test4()
{
    map<int,string> m;

    // 插入单个键值对
    m.insert(pair<int,string>{1,"zs"});
    m.insert(pair<int,string>{2,"ww"});

    // key 已经存在时，insert 插入失败，不会覆盖原有 value
    m.insert({1,"zs"});

    // 批量插入键值对
    m.insert({
        {5,"zs"},
        {4,"ww"},
        {3,"ls"}
    });

    visitMap(m);
}

// operator[] 下标操作
void test5()
{
    // map 支持下标访问
    // 可以通过 key 获取对应的 value
    map<int,string> m{
        {2,"zs"},
        {5,"zs"},
        {1,"ls"},
        {3,"ww"}
    };

    cout << m[2] << endl;

    cout << "---------" << endl;

    map<string,string> m2{
        {"city","BJ"},
        {"name","zs"},
        {"gender","male"}
    };

    cout << m2["city"] << endl;
    cout << m2["name"] << endl;
    
    cout << "---------" << endl;
    
    // 也可以通过下标方式插入新元素
    // 如果 key 不存在，会先创建该 key，再给 value 赋值
    m2["age"] = "20";

    for(auto & p : m2){
        cout << p.first << "=" << p.second << endl;
    }
    
    cout << "---------" << endl;
    
    // 如果 key 不存在，仅使用 m2["class"]
    // 会插入一个 key 为 "class" 的元素
    // value 会被默认初始化为空字符串
    m2["class"];

    for(auto & p : m2){
        cout << p.first << "=" << p.second << endl;
    }
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    test5();
    
    return 0;
}