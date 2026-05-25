#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

/*
自定义类型的“两条铁律”：
1. 必须是严格弱序（Strict Weak Ordering）：
   在比较函数里，绝对不能写 return a.id <= b.id;（带等号）。
   红黑树判断两个元素是否相等的逻辑是：如果 !(a < b) 并且 !(b < a)，就认为它们相等。
   如果你写了 <=，当 a 和 b 相等时，a <= b 成立，b <= a 也成立，红黑树就会彻底混乱。
2. const 关键字不能丢：
   无论是 operator< 还是仿函数的 operator()，最后的 const 修饰符都必须加上。
   因为 set 内部为了防止你修改 key 破坏树的结构，所有调用都是基于 const 对象的。
*/

// 存储自定义类型，核心就是要给容器提供“比较规则”
// 方式一：重载 < 运算符（内部打补丁）
// 这种方法直接把比较规则写在结构体/类内部。
// 这样，这个自定义类型就自带了“可比性”，成为它的默认排序行为。
struct Student
{
    int id;
    string name;

    // 💡 核心：重载 < 运算符
    // 注意：两处的 const 极其重要，漏掉任何一个都会导致编译报错！
    bool operator<(const Student& other) const
    {
        return this->id < other.id; // 默认按学号升序排列
    }
};

int main()
{
    // 此时可以直接定义 set，它会自动调用我们写好的 operator<
    set<Student> studentSet;

    studentSet.insert({103, "Charlie"});
    studentSet.insert({101, "Alice"});
    studentSet.insert({102, "Bob"});

    // 自动按学号排序输出：101, 102, 103
    for (const auto& s: studentSet)
    {
        cout << "学号: " << s.id << ", 姓名: " << s.name << endl;
    } 

    return 0;
}