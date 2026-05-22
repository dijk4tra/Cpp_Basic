#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <string>   // 使用 string 类型，需要包含 string 头文件

using namespace std;

/**
 * 关联式容器 set：
 * - set 是无重复元素的集合
 * - 底层通常使用红黑树实现
 * - 元素会按照比较规则自动排序
 * - 默认比较规则是 std::less<T>，也就是升序排序
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
 * - set 需要根据比较规则对元素进行排序
 * - set 也需要根据比较规则判断两个元素是否重复
 *
 * 常见方式：
 * 1. 在自定义类型中重载 operator<
 * 2. 使用函数对象，重载 operator()，作为自定义比较器
 * 3. 对 std::less 做特化处理
 *
 * 本例使用第 2 种方式：自定义函数对象 StudentCompare。
 */

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

// 重载 operator<<，方便直接输出 Student 对象
ostream & operator<<(ostream & os, const Student & s)
{
    os << s.m_id << " " << s.m_name << " " << s.m_age << endl;
    return os;
}

// 方式二：自定义比较器，也叫函数对象
struct StudentCompare
{
    // 重载 operator()，使 StudentCompare 对象可以像函数一样被调用
    bool operator()(const Student & lhs, const Student & rhs) const
    {
        // 指定比较规则：按照年龄 age 升序排序
        // lhs 的年龄小于 rhs 的年龄，则 lhs 排在前面
        return lhs.m_age < rhs.m_age;
    }
};

void test1()
{
    // 创建 set 时，通过第二个模板参数指定比较器类型
    // set 会使用 StudentCompare 中的 operator() 进行排序和去重
    set<Student, StudentCompare> box;

    box.insert(Student{2,"zs",18});

    // 由于当前比较规则只比较 m_age
    // 所以只要年龄相同，set 就认为是重复元素
    // 这一条不会插入成功
    box.insert(Student{2,"zs",18});

    box.insert(Student{1,"ls",20});
    box.insert(Student{3,"ww",19});

    // 输出结果会按照年龄升序排列
    print(box);
} 

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}