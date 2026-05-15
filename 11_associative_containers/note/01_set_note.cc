#include <iostream>
#include <set>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::set;
using std::string;
using std::pair;

/**
 * 关联式容器 associative container：
 * 常见的关联式容器有 set、map。
 *
 * 关联式容器的特点：
 * 容器中的元素不是按照插入顺序存储的，
 * 而是按照某种“比较规则”自动排列。
 *
 *
 * set 容器：
 * 底层结构通常使用红黑树实现。
 *
 * set 的特点：
 * 1. 存储单列数据
 *    也就是一个一个独立的数据。
 *    例如：
 *    int 类型的 1、2、3、4、5
 *    string 类型的 "abc"、"hello"
 *    或者自定义类型 Student 对象。
 *
 * 2. set 中的数据是有序的
 *    默认按照升序排列。
 *
 * 3. set 中的数据不能重复
 *    如果插入重复数据，插入会失败。
 *
 *
 * set 的使用场景：
 * 1. 去重
 * 2. 排序
 *
 *
 * map 容器：
 * map 存储的是双列数据，也就是一对一对的数据。
 *
 * 形式：
 * key-value
 * 键值对
 *
 * 例如：
 * name = "zs"
 * city = "BJ"
 * age = 20
 *
 * 其中：
 * name、city、age 是 key
 * "zs"、"BJ"、20 是 value
 */

// set 容器的构建
void test1()
{
    // 无参构造函数
    // 创建一个空的 set<int> 容器
    set<int> box1;

    // 初始化列表方式
    // 创建 set 容器时直接放入一组数据
    // 注意：
    // set 会自动对数据进行排序
    set<int> box2{3, 1, 2, 5, 4};

    // 迭代器方式
    // 使用 box2 的 begin() 和 end() 表示的范围，
    // 构建一个新的 set 容器 box3。
    //
    // 范围是：[begin, end)
    // 包含 begin 指向的元素，
    // 不包含 end 指向的位置。
    set<int> box3{box2.begin(), box2.end()};

    // 拷贝构造
    // 用一个已经存在的 set 容器 box3，
    // 初始化一个新的 set 容器 box4。
    /* set<int> box4 = box3; */
    set<int> box4{box3};
}

// 验证 set 容器的特点
void test2()
{
    /* set<int> box {3,1,2,5,4}; */

    // set 中的元素不能重复
    // 即使初始化列表中写了多个 1、多个 5，
    // 最终 set 中也只会保留一个。
    set<int> box{3, 1, 1, 2, 5, 5, 4};

    // 遍历 set 容器
    // 输出结果会自动按照升序排列
    for(auto & e : box){
        cout << e << "";
    }
    cout << endl;

    // 总结：
    // set 中的数据是有序的，默认升序；
    // set 中的元素不能重复。
}

// 元素的查找操作 count/find
void test3()
{
    set<int> box{3, 1, 2, 5, 4};

    /**
     * count(目标元素)
     *
     * 作用：
     * 统计目标元素在容器中出现的次数。
     *
     * 对 set 来说：
     * 因为 set 中元素不能重复，
     * 所以 count 的返回值只可能是 0 或 1。
     *
     * 返回值：
     * 1 表示找到了
     * 0 表示没有找到
     */
    int result = box.count(3);
    if(result){
        cout << "find success!" << endl;
    }else{
        cout << "not found!" << endl;
    }

    cout << "---------" << endl;

    /**
     * find(目标元素)
     *
     * 作用：
     * 查找目标元素。
     *
     * 返回值：
     * 如果找到了，返回指向目标元素的迭代器；
     * 如果没有找到，返回 end()。
     *
     * 注意：
     * end() 不指向有效元素，
     * 它表示容器最后一个元素的后一个位置。
     */
    // set<int>::iterator
    auto it = box.find(3);
    if(it != box.end()){
        cout << "find success!" << endl;
        cout << *it << endl;
    }else{
        cout << "not found!" << endl;
    }
}

// 增强 for 循环遍历 set
void visitSet(set<int> & box)
{
    // auto & e 表示用引用接收容器中的元素
    // 避免不必要的拷贝。
    for(auto & e : box){
        cout << e << " ";
    }
    cout << endl;
}

// 迭代器循环遍历 set
void visitSet2(set<int> & box)
{
    // begin() 返回指向第一个元素的迭代器
    auto it = box.begin();

    // end() 返回最后一个元素的后一个位置
    // 遍历范围是：[begin, end)
    for(; it != box.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}

// 单个数据插入 / 批量数据插入
void test4()
{
    set<int> box;

    // 单个数据插入
    // insert(元素)
    box.insert(1);
    box.insert(2);

    visitSet(box);

    cout << "---------" << endl;

    // 批量数据插入
    // 初始化列表方式
    // 一次性插入多个元素
    box.insert({5, 4, 3});

    visitSet(box);

    cout << "---------" << endl;

    // 还可以使用迭代器范围进行插入
    set<int> box2{10, 11, 12};

    /**
     * box2.find(11) 返回指向 11 的迭代器。
     *
     * box2.end() 表示最后一个元素的后一个位置。
     *
     * 所以下面插入的范围是：
     * [box2.find(11), box2.end())
     *
     * 也就是插入 11 和 12。
     */
    box.insert(box2.find(11), box2.end());

    visitSet(box);

    cout << "---------" << endl;

    /**
     * insert 插入单个元素时，
     * 返回值是一个 pair。
     *
     * pair<set<int>::iterator, bool>
     *
     * first：
     * 指向插入元素的迭代器。
     *
     * second：
     * bool 类型，表示是否插入成功。
     *
     * true  表示插入成功
     * false 表示插入失败
     *
     * 对 set 来说：
     * 如果插入的元素已经存在，
     * 插入会失败。
     */
    pair<set<int>::iterator, bool> p = box.insert(100);
    if(p.second){
        cout << "insert success!" << endl;
        cout << *(p.first) << endl;
    }else {
        cout << "insert failed!" << endl;
    }
}

// pair：存储一对数据 first 和 second
void test5()
{
    /**
     * pair 可以用来存储两个数据。
     *
     * 使用时需要指明：
     * first 的类型
     * second 的类型
     *
     * 语法：
     * pair<first的类型, second的类型> 对象名{first的值, second的值};
     */
    pair<string, int> p{"age", 20};

    // 访问第一个数据
    cout << p.first << endl;

    // 访问第二个数据
    cout << p.second << endl;
}

// erase 删除
void test6()
{
    set<int> box{1, 2, 3, 4, 5};

    // begin() 指向第一个元素 1
    auto it = box.begin();

    // 迭代器向后移动两次
    // 此时 it 指向元素 3
    ++it;
    ++it;

    // erase(迭代器)
    // 删除迭代器指向的元素
    // 这里删除的是 3
    box.erase(it);

    visitSet(box);
}

// set 不能通过下标访问
void test7()
{
    set<int> box{1, 2, 3, 4, 5};

    /**
     * set 不支持下标访问。
     *
     * 原因：
     * set 底层通常是红黑树，
     * 元素按照比较规则组织，
     * 不是像数组或 vector 那样连续存储。
     *
     * 所以 set 没有 operator[]。
     */
    /* cout << box[0] << endl; // error: 没有 operator[] */
}

// set 存储其它类型的数据
void test8()
{
    /**
     * set 也可以存储 string 类型。
     *
     * 对 string 来说：
     * 默认按照字典序进行排序。
     *
     * 例如：
     * "ls"、"ww"、"zs"
     */
    set<string> box{"zs", "ls", "ww"};

    for(auto & e : box){
        cout << e << " ";
    }
    cout << endl;
}

// 如果 set 存储自定义类型的数据
class Student
{
public:
    // 有参构造函数
    Student(int id, string name, int age)
    : m_id(id)
    , m_name(name)
    , m_age(age)
    {}

    // 打印学生信息
    void print()
    {
        cout << m_id << " " << m_name << " " << m_age << endl;
    }

    int m_id;
    string m_name;
    int m_age;
};

/**
 * set 存储自定义类型时，
 * 必须告诉 set 如何比较两个对象的大小。
 *
 * 因为 set 内部需要根据比较规则进行排序，
 * 同时也需要根据比较规则判断两个元素是否重复。
 *
 * 这里通过重载 operator< 来制定比较规则。
 */
bool operator<(const Student & s1, const Student & s2)
{
    // 制定比较规则
    // 按 id 进行比较
    //
    // id 小的 Student 对象排在前面。
    return s1.m_id < s2.m_id;

    // 也可以按 age 进行比较
    // 如果按 age 比较，
    // age 相同的两个对象会被 set 认为是重复数据。
    /* return s1.m_age < s2.m_age; */
}

void test9()
{
    /**
     * 创建一个存储 Student 对象的 set 容器。
     *
     * 注意：
     * Student 是自定义类型，
     * 所以前面必须提供比较规则。
     * 这里使用的是 operator<。
     */
    set<Student> box;

    // 插入 Student 对象
    // 因为比较规则是按 id 排序，
    // 所以最终输出顺序不是插入顺序，
    // 而是按照 id 从小到大输出。
    box.insert(Student{2, "zs", 18});
    box.insert(Student{1, "ls", 20});
    box.insert(Student{3, "ww", 19});

    // 遍历 set<Student>
    for(Student e : box){
        e.print();
    }
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    /* test6(); */
    /* test8(); */

    // 测试 set 存储自定义类型
    test9();

    return 0;
}