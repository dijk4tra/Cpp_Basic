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
 * map 是存储双列数据的容器。
 *
 * 双列数据：
 * 也就是一对一对的数据。
 *
 * 形式：
 * key-value
 * 键值对数据
 *
 * 例如：
 * name = "zs"
 * city = "BJ"
 *
 * 其中：
 * name、city 是 key
 * "zs"、"BJ" 是 value
 *
 * key-value 数据具有自我描述性。
 * 通过 key 可以知道 value 表示的含义。
 *
 *
 * map 的底层：
 * 通常采用红黑树实现。
 *
 *
 * map 的特点：
 * 1. key 不能重复
 *    如果插入相同的 key，
 *    后插入的数据不会生效。
 *
 * 2. 按照 key 升序进行排序
 *    map 中的数据不是按照插入顺序存储的，
 *    而是按照 key 的大小自动排序。
 *
 *
 * map 的使用：
 * 使用 map 时需要指明 key 和 value 的数据类型。
 *
 * 语法：
 * map<key的类型, value的类型>
 *
 * 例如：
 * map<int, string>
 * 表示 key 是 int 类型，value 是 string 类型。
 */

// map 的构建
void test1()
{
    // 无参构造
    // 创建一个空的 map<int, string> 容器
    //
    // map 中每一个元素本质上都是一个 pair。
    // 对于 map<int, string> 来说，
    // 每一个元素的类型可以理解为 pair<int, string>。
    map<int,string> m1; // pair<int,string>

    /**
     * 通过初始化列表构建 map。
     *
     * map 中存储的是 pair 对象。
     *
     * pair<int, string>{2, "zs"}
     * 表示：
     * key 是 2
     * value 是 "zs"
     */
    map<int,string> m2{
        pair<int,string>{2,"zs"},
        pair<int,string>{1,"ls"},
        pair<int,string>{3,"ww"}
    };

    /**
     * 简写方式。
     *
     * {2, "zs"} 会自动构造成一个 pair。
     *
     * 这种写法更常用。
     */
    map<int,string> m3{
        {2,"zs"},
        {1,"ls"},
        {3,"ww"}
    };

    /**
     * 通过 make_pair 函数创建 pair 对象。
     *
     * std::make_pair(2, "zs")
     * 会生成一个 pair 对象。
     *
     * first 是 2，
     * second 是 "zs"。
     */
    map<int,string> m4{
        std::make_pair(2,"zs"),
        std::make_pair(1,"ls"),
        std::make_pair(3,"ww")
    };

    // 还可以通过迭代器方式构建
    //
    // 使用 m4 的 begin() 和 end() 表示的范围，
    // 构建一个新的 map 容器 m5。
    //
    // 范围是：[begin, end)
    map<int,string> m5{ m4.begin(), m4.end() };

    // 可以通过拷贝构造函数构建
    //
    // 用已经存在的 map 容器 m4，
    // 初始化一个新的 map 容器 m6。
    map<int,string> m6{ m4 };

    // 更换一下 key 和 value 的类型
    //
    // key 是 string，value 是 string
    map<string,string> m7;

    // key 是 string，value 是 int
    map<string,int> m8;

    // key 是 string，value 是 vector<int>
    //
    // 说明：
    // map 的 value 可以是普通类型，
    // 也可以是容器类型。
    map<string,vector<int>> m9;
}

// 容器遍历：增强 for 循环方式
void visitMap(map<int,string> & m)
{
    /**
     * map 中的每一个元素都是一个 pair。
     *
     * p.first  表示 key
     * p.second 表示 value
     */
    for(auto & p : m){
        // key = value
        cout << p.first << " = " << p.second << endl;
    }
    cout << endl;
}

// 容器遍历：迭代器方式
void visitMap2(map<int,string> & m)
{
    // begin() 返回指向第一个元素的迭代器
    auto it = m.begin();

    // end() 返回最后一个元素的后一个位置
    // 遍历范围是：[begin, end)
    for(; it != m.end(); ++it){
        /**
         * it 是迭代器。
         *
         * *it 取出来的是 map 中的一个元素，
         * 这个元素是 pair。
         *
         * 所以可以通过：
         * (*it).first
         * (*it).second
         *
         * 访问 key 和 value。
         */
        /* cout << (*it).first << endl; */
        /* cout << (*it).second << endl; */

        /**
         * it->first 是 (*it).first 的简写。
         * it->second 是 (*it).second 的简写。
         */
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

    /**
     * 总结：
     *
     * 1. key 不可重复。
     *    这里写了两个 key 为 2 的数据，
     *    但是 map 中只会保留一个。
     *
     * 2. value 可以重复。
     *    这里多个 value 都是 "zs"，
     *    这是允许的。
     *
     * 3. map 会按照 key 升序排序。
     *    输出结果不是插入顺序，
     *    而是按照 key 从小到大输出。
     */
}

// map 的查找
void test3()
{
    map<int,string> m{
        {2,"zs"},
        {2,"zs"},
        {5,"zs"},
        {1,"ls"},
        {3,"ww"}
    };

    /**
     * count(目标元素的 key)
     *
     * 作用：
     * 判断指定 key 是否存在。
     *
     * 对 map 来说：
     * 因为 key 不能重复，
     * 所以 count 的返回值只可能是 0 或 1。
     *
     * 返回值：
     * 1 表示找到了
     * 0 表示没有找到
     */
    int result = m.count(3);
    if(result){
        cout << "find success!" << endl;
    }else{
        cout << "find failed!" << endl;
    }

    cout << "---------" << endl;

    /**
     * find(目标元素的 key)
     *
     * 作用：
     * 根据 key 查找对应的键值对。
     *
     * 返回值：
     * 如果找到了，
     * 返回指向该元素的迭代器。
     *
     * 如果没有找到，
     * 返回 end()。
     */
    auto it = m.find(3);
    if(it != m.end()){
        cout << "find success!" << endl;

        // it->first 表示 key
        cout << it->first << endl;

        // it->second 表示 value
        cout << it->second << endl;
    }
}

// insert 插入操作
void test4()
{
    map<int,string> m;

    // 单个数据插入
    //
    // map 中插入的是 pair 对象。
    // pair<int, string>{1, "zs"}
    // 表示 key 是 1，value 是 "zs"。
    m.insert(pair<int,string>{1,"zs"});
    m.insert(pair<int,string>{2,"ww"});

    // 简写方式
    //
    // {1, "zs"} 会自动构造成 pair。
    //
    // 注意：
    // 如果 key 已经存在，
    // 插入会失败。
    m.insert({1,"zs"});

    /**
     * 批量数据插入。
     *
     * 使用初始化列表，
     * 一次性插入多个键值对。
     */
    m.insert({
        {5,"zs"},
        {4,"ww"},
        {3,"ls"}
    });

    visitMap(m);
}

// operator[]
void test5()
{
    /**
     * map 支持下标访问。
     *
     * 注意：
     * map 的下标不是位置下标，
     * 而是 key。
     *
     * 也就是说：
     * 通过 key 获取对应的 value。
     */
    map<int,string> m{
        {2,"zs"},
        {5,"zs"},
        {1,"ls"},
        {3,"ww"}
    };

    // 通过 key 为 2，
    // 获取对应的 value。
    cout << m[2] << endl;

    cout << "---------" << endl;

    map<string,string> m2{
        {"city","BJ"},
        {"name","zs"},
        {"gender","male"}
    };

    // 通过 key 获取 value
    cout << m2["city"] << endl;
    cout << m2["name"] << endl;

    cout << "---------" << endl;

    /**
     * 还可以通过下标方式进行插入。
     *
     * 如果 key 不存在：
     * m2["age"] 会先创建一个新的键值对。
     *
     * 然后通过赋值运算符，
     * 把 value 设置为 "20"。
     */
    m2["age"] = "20";

    for(auto & p : m2){
        cout << p.first << "=" << p.second << endl;
    }

    cout << "---------" << endl;

    /**
     * 使用 operator[] 时需要特别注意：
     *
     * 如果 key 不存在，
     * map 会自动插入一个新的键值对。
     *
     * 对于 map<string, string> 来说，
     * 新插入的 value 会使用 string 的默认值，
     * 也就是空字符串 ""。
     *
     * 所以下面这句代码：
     * m2["class"];
     *
     * 会插入：
     * key 是 "class"
     * value 是 ""
     */
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

    // 测试 map 的 operator[]
    test5();

    return 0;
}