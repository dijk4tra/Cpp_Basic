#include <iostream>
#include <set>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::set;
using std::string;
using std::pair;

/*
 * 关联式容器：set、map
 *
 * set：
 * 1. 底层通常使用红黑树实现
 * 2. 元素会按照一定规则自动排序
 * 3. 元素不能重复
 *
 * set 的特点：
 * 1. 存储单列数据，即一个一个独立的元素
 *    例如：
 *    int 类型：1、2、3、4、5
 *    string 类型："abc"、"hello"
 *    自定义类型：Point 对象、Student 对象等
 *
 * 2. set 中的元素是有序的
 *    默认按照升序排列
 *
 * 3. set 中的元素不能重复
 *
 * 使用场景：
 * 1. 去重
 * 2. 排序
 *
 * map：
 * 1. 存储双列数据，即一对一对的数据
 * 2. 每个元素都是 key-value 键值对
 *
 * 例如：
 * name = "zs"
 * city = "BJ"
 * age = 20
 */

// set 容器的构造
void test1()
{
    // 无参构造：创建一个空的 set 容器
    set<int> box1;

    // 初始化列表构造
    set<int> box2{3,1,2,5,4};

    // 通过迭代器区间构造
    set<int> box3{box2.begin(), box2.end()};

    // 拷贝构造
    /* set<int> box4 = box3; */
    set<int> box4{box3};
}

// 验证 set 容器的特点
void test2()
{
    /* set<int> box {3,1,2,5,4}; */
    set<int> box {3,1,1,2,5,5,4};

    for(auto & e : box){
        cout << e << "";
    }
    cout << endl;

    // set 中的元素会自动排序，默认升序，并且重复元素会被去掉
}

// 元素查找操作：count / find
void test3()
{
    set<int> box {3,1,2,5,4};

    // count(目标元素)
    // 对于 set 而言，元素不能重复
    // 找到返回 1，未找到返回 0
    int result = box.count(3);
    if(result){
        cout << "find success!" << endl;
    }else{
        cout << "not found!" << endl;
    }

    cout << "---------" << endl;
    
    // find(目标元素)
    // 找到：返回指向目标元素的迭代器
    // 未找到：返回 end()
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
    for(auto & e : box){
        cout << e << " ";
    }
    cout << endl;
}

// 使用迭代器遍历 set
void visitSet2(set<int> & box)
{
    auto it = box.begin();
    for(; it != box.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}

// 单个元素插入 / 批量元素插入
void test4()
{
    set<int> box;

    // 插入单个元素
    box.insert(1);
    box.insert(2);
    visitSet(box);

    cout << "---------" << endl;

    // 批量插入元素：初始化列表方式
    box.insert({5,4,3});
    visitSet(box);

    cout << "---------" << endl;

    // 批量插入元素：迭代器区间方式
    set<int> box2{10,11,12};
    box.insert(box2.find(11), box2.end());
    visitSet(box);

    cout << "---------" << endl;

    // insert 插入单个元素时，返回 pair<iterator, bool>
    // first：指向插入元素或已存在元素的迭代器
    // second：表示是否插入成功
    pair<set<int>::iterator, bool> p = box.insert(100);
    if(p.second){
        cout << "insert success!" << endl;
        cout << *(p.first) << endl;
    }else {
        cout << "insert failed!" << endl;
    }
}

// pair：用于存储一对数据，成员名分别为 first 和 second
void test5()
{
    // 使用 pair 时，需要指定 first 和 second 的类型
    pair<string,int> p{"age", 20};

    cout << p.first << endl;
    cout << p.second << endl;
}

// erase 删除元素
void test6()
{
    set<int> box{1,2,3,4,5};

    // 获取 begin() 位置的迭代器
    auto it = box.begin();

    // 将迭代器移动到要删除的元素位置
    ++it;
    ++it;

    // 按迭代器位置删除元素
    box.erase(it);

    visitSet(box);
}

// set 不能通过下标访问元素
void test7()
{
    set<int> box{1,2,3,4,5};

    /* cout << box[0] << endl; // error：set 没有重载 operator[] */
}

// set 存储其他类型的数据
void test8()
{
    // string 类型默认按照字典序排序
    set<string> box{"zs","ls","ww"};

    for(auto & e : box){
        cout << e << " ";
    }
    cout << endl;
}

// set 存储自定义类型的数据
class Student
{
public:
    Student(int id, string name, int age)
    : m_id(id)
    , m_name(name)
    , m_age(age)
    {}
    
    void print()
    {
        cout << m_id << " " << m_name << " " << m_age << endl;
    }

    int m_id;
    string m_name;
    int m_age;
};

// 为 Student 类型提供比较规则
// set 需要根据比较规则对元素进行排序和去重
bool operator<(const Student & s1, const Student & s2)
{
    // 制定比较规则：按照 id 进行比较
    return s1.m_id < s2.m_id;

    /* return s1.m_age < s2.m_age; */
}

void test9()
{
    set<Student> box;

    box.insert(Student{2,"zs",18});
    box.insert(Student{1,"ls",20});
    box.insert(Student{3,"ww",19});

    // 按照 operator< 指定的规则进行排序后遍历
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
    test9();

    return 0;
}