#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

/**
 * 无序关联式容器 unordered_set：
 * - unordered_set 是无序集合容器
 * - 元素唯一，不能重复
 * - 底层通常使用哈希表实现
 * - 元素不会按照大小自动排序
 *
 * unordered_set 存储内置类型时，系统已经提供了哈希函数和相等判断规则。
 * unordered_set 存储自定义类型时，需要告诉容器：
 * 1. 如何计算对象的哈希值
 * 2. 如何判断两个对象是否相等
 */

template<typename Container>
void print(Container &box)
{
    // 遍历容器中的所有元素
    // unordered_set 的遍历顺序是不确定的
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

class Student
{
public:
    Student(int id, string name)
    :m_id(id)
    ,m_name(name)
    {}

    // 计算 Student 对象的哈希值
    size_t studentHash() const
    {   
        // 分别对 id 和 name 进行哈希计算
        size_t h1 = std::hash<int>()(m_id);      // std::hash<int>() 创建函数对象，再用 (m_id) 调用
        size_t h2 = std::hash<string>()(m_name);

        // 将两个哈希值合并，得到 Student 对象的哈希值
        // 这里使用异或和左移是一种简单的组合方式
        return h1 ^ (h2 << 1);
    }

    // 重载 == 运算符，用于判断两个 Student 对象是否相等
    bool operator==(const Student & rhs) const
    {
        // id 和 name 都相同，才认为是同一个学生
        return m_id == rhs.m_id && m_name == rhs.m_name;
    }

public:
    int m_id;       // 学号
    string m_name;  // 姓名
};

// 重载 operator<<，方便输出 Student 对象
ostream & operator<<(ostream & os, const Student & s)
{
    os << "Student(id: " << s.m_id << ", name: " << s.m_name << ")";
    os << endl;
    return os;
}

/**
 * unordered_set 存储自定义类型时，常见处理方式：
 *
 * 1. 自定义函数对象
 *    - 一个函数对象负责计算哈希值
 *    - 一个函数对象负责判断对象是否相等
 *
 * 2. 对 std::hash 和 std::equal_to 做特化处理
 *    - 让 unordered_set<Student> 可以直接使用默认模板参数
 */

// 方式一：自定义函数对象，分别提供哈希函数和相等判断函数

// 自定义哈希函数对象
struct StudentHash
{   
    // 重载 operator()，用于计算 Student 对象的哈希值
    size_t operator()(const Student & s) const
    {
        return s.studentHash();
    }
};

// 自定义相等判断函数对象
struct StudentEqual
{
    // 重载 operator()，用于判断两个 Student 对象是否相等
    bool operator()(const Student & lhs, const Student & rhs) const
    {
        // return lhs == rhs;
        return lhs.operator==(rhs);
    }
};

// unordered_set 使用自定义哈希函数和自定义相等判断函数
void test1()
{
    // unordered_set<Student, StudentHash, StudentEqual>
    // 第一个模板参数：元素类型 Student
    // 第二个模板参数：哈希函数 StudentHash
    // 第三个模板参数：相等判断函数 StudentEqual
    unordered_set<Student, StudentHash, StudentEqual> box{
        Student(1, "zs"),
        Student(1, "zs"),  // 与第一个元素相同，会被认为是重复元素
        Student(2, "ls"),
        Student(3, "ws"),
    };

    print(box);
}

// 方式二：对 std::hash 和 std::equal_to 做特化处理
namespace std
{
    // 对 std::hash<Student> 做特化
    // 作用：告诉 unordered_set 如何计算 Student 的哈希值
    template <>
    struct hash<Student>
    {
        // 重载 operator()，返回 Student 对象的哈希值
        size_t operator()(const Student & s) const
        {
            return s.studentHash();
        }
    };
    
    // 对 std::equal_to<Student> 做特化
    // 作用：告诉 unordered_set 如何判断两个 Student 对象是否相等
    template <>
    struct equal_to<Student>
    {
        // 重载 operator()，判断两个 Student 对象是否相等
        bool operator()(const Student & s1, const Student & s2) const
        {
            return s1 == s2;
        }
    };
}

void test2()
{
    // 由于已经特化了 std::hash<Student> 和 std::equal_to<Student>
    // 所以这里可以直接写 unordered_set<Student>
    unordered_set<Student> box{
        Student{1, "zs"},
        Student{1, "zs"},  // id 和 name 都相同，会被认为是重复元素
        Student{2, "ls"},
        Student{3, "ww"}
    };

    print(box);
}

int main(int argc, char const *argv[])
{
    // test1();
    test2();

    return 0;
}