#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

/**
 * 无序关联式容器 unordered_set：
 *
 * unordered_set 是 STL 中的无序关联式容器。
 *
 * 特点：
 * 1. unordered_set 是无序集合容器
 *    只保存 key，不保存 value。
 *
 * 2. 元素唯一，不能重复
 *    相同元素只能保存一份。
 *
 * 3. 底层通常使用哈希表实现
 *    查找、插入、删除的平均时间复杂度通常是 O(1)。
 *
 * 4. 元素不会按照大小自动排序
 *    遍历时的输出顺序不是插入顺序，
 *    也不是升序或者降序。
 *
 *
 * unordered_set 存储内置类型时，
 * 系统已经提供了哈希函数和相等判断规则。
 *
 * 例如：
 * unordered_set<int>
 * unordered_set<string>
 *
 * 标准库已经知道：
 * 1. 如何计算 int / string 的哈希值
 * 2. 如何判断两个 int / string 是否相等
 *
 *
 * unordered_set 存储自定义类型时，
 * 需要告诉容器两件事情：
 *
 * 1. 如何计算对象的哈希值
 *    因为 unordered_set 底层是哈希表，
 *    插入和查找时需要先根据哈希值确定元素大概存放的位置。
 *
 * 2. 如何判断两个对象是否相等
 *    因为不同对象可能计算出相同的哈希值，
 *    也就是发生哈希冲突。
 *    所以还需要相等判断规则来确认两个对象是否真的是同一个元素。
 */

template<typename Container>
void print(Container &box)
{
    /**
     * 范围 for 遍历容器
     *
     * auto & e：
     * 1. auto
     *    自动推导容器中元素的类型。
     *
     * 2. &
     *    使用引用接收元素，避免拷贝。
     *
     * 对于 unordered_set 来说，
     * 遍历顺序是不确定的。
     *
     * 它既不是插入顺序，
     * 也不是从小到大的排序顺序。
     */
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

class Student
{
public:
    /**
     * 构造函数
     *
     * 创建 Student 对象时，
     * 需要传入学号和姓名。
     *
     * 初始化列表：
     * 直接对成员变量进行初始化。
     */
    Student(int id, string name)
    :m_id(id)
    ,m_name(name)
    {}

    /**
     * studentHash 成员函数
     *
     * 作用：
     * 计算当前 Student 对象的哈希值。
     *
     * size_t：
     * 是一种无符号整数类型，
     * 常用于表示大小、下标、哈希值等。
     *
     * 函数后面的 const：
     * 表示该函数不会修改当前 Student 对象。
     */
    size_t studentHash() const
    {
        /**
         * std::hash<T>
         *
         * 是标准库提供的哈希函数对象模板。
         *
         * std::hash<int>()：
         * 创建一个可以计算 int 哈希值的函数对象。
         *
         * std::hash<int>()(m_id)：
         * 调用这个函数对象，
         * 计算 m_id 的哈希值。
         */
        size_t h1 = std::hash<int>()(m_id);

        /**
         * 对 string 类型的 m_name 计算哈希值。
         *
         * 标准库已经提供了 std::hash<string>，
         * 所以可以直接使用。
         */
        size_t h2 = std::hash<string>()(m_name);

        /**
         * 合并两个哈希值
         *
         * 一个 Student 对象由 m_id 和 m_name 共同决定，
         * 所以哈希值也应该同时考虑这两个成员。
         *
         * ^：
         * 按位异或运算。
         *
         * << 1：
         * 左移一位。
         *
         * 这里使用异或和左移，
         * 是一种简单的哈希组合方式。
         */
        return h1 ^ (h2 << 1);
    }

    /**
     * 重载 == 运算符
     *
     * 作用：
     * 判断两个 Student 对象是否相等。
     *
     * unordered_set 判断元素是否重复时，
     * 需要使用相等判断规则。
     *
     * 参数使用 const 引用：
     * 1. 避免拷贝
     * 2. 保证不会修改 rhs
     *
     * 函数后面的 const：
     * 表示该函数不会修改当前对象。
     */
    bool operator==(const Student & rhs) const
    {
        /**
         * id 和 name 都相同，
         * 才认为是同一个学生。
         */
        return m_id == rhs.m_id && m_name == rhs.m_name;
    }

public:
    int m_id;       // 学号
    string m_name;  // 姓名
};

/**
 * 重载 operator<<
 *
 * 作用：
 * 让 Student 对象可以直接通过 cout 输出。
 *
 * 如果没有重载 operator<<，
 * cout << s 这样的写法无法编译通过。
 *
 * 返回 ostream &：
 * 是为了支持连续输出。
 */
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
 *
 *
 * 注意：
 * 对于 unordered_set 来说，
 * “哈希函数”和“相等判断函数”要配合使用。
 *
 * 如果两个对象相等，
 * 它们的哈希值也应该相同。
 *
 * 也就是说：
 * 如果 a == b 为 true，
 * 那么 hash(a) 和 hash(b) 应该相等。
 */

// 方式一：自定义函数对象，分别提供哈希函数和相等判断函数

/**
 * 自定义哈希函数对象
 *
 * 函数对象：
 * 本质上是一个类或结构体对象，
 * 但是因为它重载了 operator()，
 * 所以可以像函数一样被调用。
 */
struct StudentHash
{
    /**
     * 重载 operator()
     *
     * 作用：
     * 计算 Student 对象的哈希值。
     *
     * 例如：
     * StudentHash hash;
     * hash(s);
     *
     * 实际调用的是：
     * hash.operator()(s);
     *
     * 函数后面的 const：
     * 表示该函数不会修改 StudentHash 对象本身。
     */
    size_t operator()(const Student & s) const
    {
        return s.studentHash();
    }
};

/**
 * 自定义相等判断函数对象
 *
 * 作用：
 * 告诉 unordered_set 如何判断两个 Student 对象是否相等。
 */
struct StudentEqual
{
    /**
     * 重载 operator()
     *
     * 返回 true：
     * 表示 lhs 和 rhs 是相同元素。
     *
     * 返回 false：
     * 表示 lhs 和 rhs 不是相同元素。
     */
    bool operator()(const Student & lhs, const Student & rhs) const
    {
        // 方式一：直接使用重载好的 operator==
        // return lhs == rhs;

        // 方式二：显式调用 operator== 成员函数
        return lhs.operator==(rhs);
    }
};

// unordered_set 使用自定义哈希函数和自定义相等判断函数
void test1()
{
    /**
     * unordered_set<Student, StudentHash, StudentEqual>
     *
     * unordered_set 的第一个模板参数：
     * Student
     * 表示容器中存储的元素类型。
     *
     * unordered_set 的第二个模板参数：
     * StudentHash
     * 表示哈希函数对象类型。
     *
     * unordered_set 的第三个模板参数：
     * StudentEqual
     * 表示相等判断函数对象类型。
     *
     * 创建容器后，
     * unordered_set 会使用 StudentHash 计算哈希值，
     * 使用 StudentEqual 判断两个元素是否相等。
     */
    unordered_set<Student, StudentHash, StudentEqual> box{
        Student(1, "zs"),
        Student(1, "zs"),  // 与第一个元素相同，会被认为是重复元素
        Student(2, "ls"),
        Student(3, "ws"),
    };

    /**
     * 输出 unordered_set 中的元素
     *
     * 注意：
     * unordered_set 不保证输出顺序。
     *
     * 由于 Student(1, "zs") 出现了两次，
     * 并且根据 StudentEqual 判断它们相等，
     * 所以最终只会保留一个。
     */
    print(box);
}

// 方式二：对 std::hash 和 std::equal_to 做特化处理
namespace std
{
    /**
     * 对 std::hash<Student> 做特化
     *
     * std::hash<T>：
     * 是标准库提供的哈希函数对象模板。
     *
     * unordered_set<T> 默认会使用：
     * std::hash<T>
     *
     * 对于自定义类型 Student，
     * 标准库默认不知道如何计算它的哈希值。
     *
     * 所以这里对 std::hash<Student> 做特化，
     * 明确告诉 unordered_set：
     * Student 类型应该如何计算哈希值。
     */
    template <>
    struct hash<Student>
    {
        /**
         * 重载 operator()
         *
         * 返回 Student 对象的哈希值。
         */
        size_t operator()(const Student & s) const
        {
            return s.studentHash();
        }
    };

    /**
     * 对 std::equal_to<Student> 做特化
     *
     * std::equal_to<T>：
     * 是标准库提供的相等判断函数对象模板。
     *
     * unordered_set<T> 默认会使用：
     * std::equal_to<T>
     *
     * 对于自定义类型 Student，
     * 如果没有合适的相等判断规则，
     * unordered_set 就无法判断两个 Student 对象是否重复。
     *
     * 这里对 std::equal_to<Student> 做特化，
     * 明确告诉 unordered_set：
     * Student 类型应该如何判断相等。
     */
    template <>
    struct equal_to<Student>
    {
        /**
         * 重载 operator()
         *
         * 判断两个 Student 对象是否相等。
         *
         * 这里直接调用 Student 中重载的 operator==。
         */
        bool operator()(const Student & s1, const Student & s2) const
        {
            return s1 == s2;
        }
    };
}

void test2()
{
    /**
     * unordered_set<Student>
     *
     * unordered_set 的第二个模板参数默认是：
     * std::hash<Student>
     *
     * unordered_set 的第三个模板参数默认是：
     * std::equal_to<Student>
     *
     * 由于前面对 std::hash<Student>
     * 和 std::equal_to<Student> 做了特化，
     * 所以这里可以直接写 unordered_set<Student>。
     */
    unordered_set<Student> box{
        Student{1, "zs"},
        Student{1, "zs"},  // id 和 name 都相同，会被认为是重复元素
        Student{2, "ls"},
        Student{3, "ww"}
    };

    /**
     * 输出 unordered_set 中的元素。
     *
     * 注意：
     * unordered_set 不会按照 id 或 name 自动排序，
     * 输出顺序是不确定的。
     */
    print(box);
}

int main(int argc, char const *argv[])
{
    // test1();
    test2();

    return 0;
}