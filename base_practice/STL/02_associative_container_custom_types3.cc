#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

// 存储自定义类型，核心就是要给容器提供“比较规则”
// 第三种写法：特化 std::less（在 std 命名空间中注入规则）
// 这种方法比较特殊，适合在无法修改结构体内部代码，也不想写一个单独的比较类的情况下使用。
// std::set 和 std::map 的声明其实自带默认参数，完整的面貌是 std::set<T, std::less<T>>。
// 这就意味着，如果我们在 std 命名空间中对 std::less 进行特化（Specialization），
// 就能在不修改结构体内部、也不修改 set 声明的前提下，优雅地为自定义类型定制默认排序规则。

struct Student
{
    int id;
    string name;
};

// 💡 核心：向 std 命名空间中注入 std::less 的特化版本
namespace std
{
    template <>
    struct less<Student>
    {
        bool operator()(const Student& s1, const Student& s2) const
        {
            return s1.id < s2.id; // 按学号升序排列
        }
    };
}

int main()
{
    // 💡 不同点：定义 set 时不需要传入任何外部比较类
    // 它会自动检测并调用我们刚刚特化的 std::less<Student>
    std::set<Student> studentSet;

    studentSet.insert({103, "Charlie"});
    studentSet.insert({101, "Alice"});
    studentSet.insert({102, "Bob"});

    // 自动按学号排序输出
    for (const auto& s : studentSet)
    {
        std::cout << "学号: " << s.id << ", 姓名: " << s.name << "\n";
    }

    return 0;
}