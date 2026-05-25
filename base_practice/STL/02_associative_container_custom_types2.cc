#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

// 存储自定义类型，核心就是要给容器提供“比较规则”
// 方式二：使用仿函数 / 比较类（外部定制规则）
// 如果不想或者不能修改结构体的内部代码，
// 或者希望在不同的场景下使用不同的排序规则，
// 就需要用到仿函数（Functor）。

struct Teacher
{
    int id;
    string name;
    int salary;
};

// 💡 核心：定义一个专门用于比较的仿函数类
struct CompareBySalaryDesc
{
    // 重载 () 运算符，使其可以像函数一样被调用
    bool operator()(const Teacher& t1, const Teacher& t2) const
    {
        return t1.salary > t2.salary; // 降序：薪水高的排前面
    }
};

int main()
{
    // ⚠️ 注意：此时定义 set 时，必须在第二个模板参数中传入这个比较类
    set<Teacher, CompareBySalaryDesc> teacherSet;

    teacherSet.insert({1, "Tom", 8000});
    teacherSet.insert({2, "Jerry", 12000});
    teacherSet.insert({3, "Spike", 10000});

    // 自动按薪水降序输出：Jerry(12000), Spike(10000), Tom(8000)
    for (const auto& t : teacherSet)
    {
        std::cout << "姓名: " << t.name << ", 薪水: " << t.salary << "\n";
    }

    return 0;
}