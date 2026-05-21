#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>

using namespace std;

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

    // list 有成员函数 sort()
    // vector 没有 sort() 成员函数，vector 排序通常使用算法库中的 std::sort()
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

    // list<Student>::sort() 默认需要使用 < 比较两个 Student 对象
    // 因此自定义类型如果直接调用 sort()，需要提供 operator<
    // 这里按照学号 m_id 升序排序
    bool operator<(const Student & rhs) const
    {
        return m_id < rhs.m_id;
    }

    int m_id;
    string m_name;
    int m_age;
};

// 重载输出运算符，使 Student 对象可以直接使用 cout 输出
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

    // 根据 Student::operator< 的规则排序
    // 当前规则是按照 m_id 升序排序
    box.sort();

    print(box);
}

int main(int argc, char const *argv[])
{
    // test1();
    test2();

    return 0;
}