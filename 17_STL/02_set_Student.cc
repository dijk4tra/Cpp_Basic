#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <string>

using namespace std;

/**
 * 关联式容器 set：
 * - set 是无重复元素的集合
 * - 底层通常使用红黑树实现
 * - 元素会按照指定规则自动排序
 * - 默认排序规则是 std::less<T>，也就是升序排序
 */

template<typename Container>
void print(Container &box)
{
    // 遍历容器中的所有元素
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

/**
 * set 存储自定义类型时，需要提供比较规则。
 *
 * 原因：
 * - set 中的元素需要排序
 * - set 需要根据比较规则判断两个元素是否“相同”
 *
 * 常见方式：
 * 1. 在自定义类型中重载 operator<
 * 2. 使用函数对象，重载 operator()，作为自定义比较器
 * 3. 对 std::less 做特化处理
 *
 * 本例使用第 1 种方式：在 Student 类中重载 operator<
 */

class Student
{
public:
    Student(int id, string name, int age)
    :m_id(id)
    ,m_name(name)
    ,m_age(age)
    {}
    
    // 重载 operator<，为 Student 提供排序规则
    bool operator<(const Student & rhs) const
    {
        // 指定比较规则：按照学号 id 升序排序
        // 当前对象的 id 小于 rhs 的 id，则当前对象排在前面
        return this->m_id < rhs.m_id;

        // 也可以改成按照姓名升序排序
        // return this->m_name < rhs.m_name;
    }

    int m_id;       // 学号
    string m_name;  // 姓名
    int m_age;      // 年龄
};

// 重载 operator<<，方便直接输出 Student 对象
ostream & operator<<(ostream & os, const Student & s)
{
    os << s.m_id << " " << s.m_name << " " << s.m_age << endl;
    return os;
}

void test1()
{
    // set<Student> 使用 Student::operator< 作为排序规则
    set<Student> box;

    // 按照 Student 中 operator< 的规则进行排序和去重
    box.insert(Student{2,"zs",18});

    // 由于比较规则只比较 m_id
    // 所以只要 m_id 相同，set 就认为是重复元素
    // 这一条不会插入成功
    box.insert(Student{2,"zs",18});

    box.insert(Student{1,"ls",20});
    box.insert(Student{3,"ww",19});

    // 输出结果会按照 m_id 升序排列
    print(box);
} 

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}