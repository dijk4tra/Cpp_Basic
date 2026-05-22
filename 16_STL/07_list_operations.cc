#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

// 定义一个函数模板，可以打印支持范围 for 遍历的容器
// 注意：容器中的元素需要支持 operator<< 输出
template<typename Container>
void print(Container &box)
{
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

// list 中特有的操作
// sort() : 对 list 中的元素进行排序
// 对于内置类型，默认按照升序排序
void test1()
{
    list<int> box{ 3, 1, 2, 5, 4 };

    print(box);

    // list 有自己的成员函数 sort()
    // vector 和 deque 没有 sort() 成员函数
    // vector/deque 排序通常使用算法库中的 std::sort()
    box.sort();

    print(box);
}

class Student
{
public:
    Student(int id, string name, int age)
        : m_id(id)
        , m_name(name)
        , m_age(age)
    {

    }

    /*
    // operator< 成员函数版本
    // list<Student>::sort() 默认会使用 < 比较两个 Student 对象
    // 因此自定义类型如果直接调用 sort()，需要提供 operator<

    bool operator<(const Student & rhs) const
    {   
        // 指定比较规则：按照什么字段进行排序

        // 按照学号 m_id 升序排序
        // return this->m_id < rhs.m_id;

        // 按照年龄 m_age 升序排序
        return this->m_age < rhs.m_age;
    }
    */

public:
    int m_id;
    string m_name;
    int m_age;
};

// operator< 普通函数版本
// list<Student>::sort() 默认会调用该比较规则
bool operator<(const Student & lhs, const Student & rhs)
{
    // 指定比较规则：按照什么字段进行排序

    // 按照学号 m_id 升序排序
    // return lhs.m_id < rhs.m_id;

    // 按照年龄 m_age 升序排序
    return lhs.m_age < rhs.m_age;
}

// 重载输出运算符 <<
// 使 Student 对象可以直接通过 cout 输出
ostream & operator<<(ostream & os, const Student & s)
{
    os << s.m_id << " " << s.m_name << " " << s.m_age;
    return os;
}

// 针对自定义类型进行排序
// 自定义类型调用 list::sort() 时，需要提供比较规则
void test2()
{
    Student s1(2, "张三", 19);
    Student s2(1, "李四", 21);
    Student s3(3, "王五", 20);

    list<Student> box{
        s1,
        s2,
        s3,
    };

    print(box);

    // 默认调用 operator< 进行排序
    // 当前 operator< 的规则是按照 m_age 升序排序
    box.sort();

    cout << "---after sort()---" << endl;
    print(box);
}

// 自定义比较器
// 函数对象：通过重载 operator()，使对象可以像函数一样被调用
struct StudentCompare
{
    // list::sort(Compare) 需要一个二元谓词
    // 二元谓词：接收两个参数，返回 bool 类型
    bool operator()(const Student & lhs, const Student & rhs) const
    {
        // 按照年龄 m_age 升序排序
        return lhs.m_age < rhs.m_age;
    }

};

void test3()
{
    Student s1(2, "张三", 19);
    Student s2(1, "李四", 21);
    Student s3(3, "王五", 20);

    list<Student> box{
        s1,
        s2,
        s3,
    };

    print(box);

    // 根据 StudentCompare 的规则排序
    // StudentCompare() 是一个临时函数对象
    // 当前规则是按照 m_age 升序排序
    box.sort(StudentCompare());

    cout << "---after sort()---" << endl;
    print(box);
}

void test4()
{
    list<int> box{ 3, 1, 2, 5, 4 };
    print(box);

    // box.sort(); 
    // 默认升序排序，相当于使用 std::less<int>()

    // 使用标准库函数对象 std::less<int>()，升序排序
    // box.sort(std::less<int>());

    // 使用标准库函数对象 std::greater<int>()，降序排序
    box.sort(std::greater<int>());

    cout << "---after sort()---" << endl;
    print(box);
}

void test5()
{
    // vector<int> box{ 3, 1, 2, 5, 4 };
    deque<int> box{ 3, 1, 2, 5, 4 };

    print(box);

    // vector 和 deque 没有 sort() 成员函数
    // box.sort();

    // vector 和 deque 支持随机访问迭代器
    // 因此可以使用算法库中的 std::sort() 排序
    std::sort(box.begin(), box.end()); // 升序排序

    cout << "---after sort()---" << endl;
    print(box);
}

// reverse()
// 将 list 中的元素顺序反转
void test6()
{
    list<int> box{ 1, 2, 3, 4, 5 };
    print(box);

    // 反转链表中元素的顺序
    box.reverse();

    cout << "---after reverse()---" << endl;
    print(box);
}

// unique()
// 删除连续重复的元素
// 注意：unique 只会删除“相邻的重复元素”
// 如果想删除所有重复值，通常先 sort()，再 unique()
void test7()
{
    // list<int> box{ 1, 2, 2, 2, 3, 3, 3, 3, 4, 5 };
    list<int> box{ 1, 2, 2, 4, 5, 2, 3, 3, 3, 5 };

    print(box);

    // 先排序，让相同元素变成连续排列
    box.sort();

    cout << "---after sort()---" << endl;
    print(box);

    // 删除连续重复的元素
    // 排序后使用 unique，可以达到去重效果
    box.unique();

    cout << "---after unique()---" << endl;
    print(box);
}

void test8()
{
    list<int> box1{1, 3, 5};
    list<int> box2{2, 4, 6};

    cout << "---before merge()---" << endl;
    print(box1);
    print(box2);

    // merge() 合并两个 list
    // 前提：两个 list 通常应当已经按照相同规则有序
    // 合并后仍保持有序
    // box2 中的元素会被转移到 box1 中，box2 变为空
    box1.merge(box2);

    cout << "---after merge()---" << endl;
    print(box1);
    print(box2); // box2 没有数据了，相当于元素被移动到了 box1
}

// remove()
// 删除 list 中所有等于指定值的元素
void test9()
{
    list<int> box{1, 2, 3, 3, 3, 4, 5, 3, 6};

    print(box);

    // 删除所有值等于 3 的元素
    box.remove(3);

    cout << "---after remove()---" << endl;
    print(box);
}

bool overThree(int n)
{
    return n > 3;
}

// remove_if()
// 删除满足条件的元素
// remove_if 的参数是一元谓词
// 一元谓词：接收一个参数，返回 bool 类型
void test10()
{
    list<int> box{1, 2, 3, 4, 5, 6};

    print(box);

    // 删除所有大于 3 的元素
    // overThree 返回 true 的元素会被删除
    box.remove_if(overThree);

    cout << "---after remove_if(overThree)---" << endl;  
    print(box);
}

// splice()
// list 特有操作，用于在 list 之间转移元素
// splice 不会拷贝元素，而是直接改变链表节点的连接关系
void test11()
{
    list<int> box1{1, 2, 3, 4};
    list<int> box2{5, 6, 7};

    cout << "---before splice()---" << endl;
    print(box1);
    print(box2);

    auto it = box1.begin();
    ++it;

    // 将 box2 中的所有元素转移到 box1 的 it 位置之前
    // 转移后 box2 变为空
    box1.splice(it, box2); 

    cout << "---after splice()---" << endl;
    print(box1);
    print(box2); // box2 空了

    cout << "----------------------" << endl << endl;

    list<int> box3{1, 2, 3, 4};
    list<int> box4{5, 6, 7};

    cout << "---before splice()---" << endl;
    print(box3);
    print(box4);

    auto it2 = box3.begin();
    auto it3 = box4.begin();
    ++it3;

    // 将 box4 中 it3 指向的单个元素转移到 box3 的 it2 位置之前
    // 此时 it3 指向元素 6
    box3.splice(it2, box4, it3);

    cout << "---after splice()---" << endl;
    print(box3);
    print(box4);

    cout << "----------------------" << endl << endl;
    
    list<int> box5{1, 2, 3, 4};
    list<int> box6{5, 6, 7};

    cout << "---before splice()---" << endl;
    print(box5);
    print(box6);

    // 将 box6 的 [begin, end) 区间转移到 box5 的末尾
    // 这里转移的是 box6 的全部元素
    box5.splice(box5.end(), box6, box6.begin(), box6.end());

    cout << "---after splice()---" << endl;
    print(box5);
    print(box6);

    cout << "----------------------" << endl << endl;
    
    list<int> box{1,2,3,4,5,6,7};

    cout << "---before splice()---" << endl;
    print(box);

    // 同一个 list 内部也可以使用 splice 调整元素位置
    // 将 box 的最后一个元素转移到 box 的开头
    box.splice(box.begin(), box, --box.end());

    cout << "---after splice()---" << endl;
    print(box);
}

int main(int argc, char const *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    // test7();
    // test8();
    // test9();
    // test10();
    test11();

    return 0;
}