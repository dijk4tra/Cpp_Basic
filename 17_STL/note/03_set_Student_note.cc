#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <string>   // 使用 string 类型，需要包含 string 头文件

using namespace std;

/**
 * 关联式容器 set：
 *
 * set 是 STL 中的关联式容器。
 *
 * 特点：
 * 1. set 是无重复元素的集合
 *    同一个 key 只能保存一份。
 *
 * 2. 底层通常使用红黑树实现
 *    所以插入、删除、查找的效率通常是 O(logN)。
 *
 * 3. 元素会按照比较规则自动排序
 *    插入元素时，不是按照插入顺序存储，
 *    而是根据比较规则放到合适的位置。
 *
 * 4. 默认比较规则是 std::less<T>
 *    也就是默认使用 operator< 进行比较，
 *    按照升序排序。
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
     * 对于 set 来说，
     * 遍历顺序就是元素的排序顺序。
     */
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
 * 1. set 需要根据比较规则对元素进行排序
 *    set 必须知道哪个元素应该排在前面，
 *    哪个元素应该排在后面。
 *
 * 2. set 也需要根据比较规则判断两个元素是否重复
 *    对于 set 来说，
 *    如果两个元素互相都不小于对方，
 *    set 就认为它们是等价元素。
 *
 *    也就是说：
 *    lhs < rhs 为 false，
 *    rhs < lhs 也为 false，
 *    那么 lhs 和 rhs 会被认为是相同元素。
 *
 *
 * 常见方式：
 * 1. 在自定义类型中重载 operator<
 *    让对象本身具备“小于比较”的能力。
 *
 * 2. 使用函数对象，重载 operator()
 *    将函数对象作为 set 的第二个模板参数，
 *    用来指定排序规则。
 *
 * 3. 对 std::less 做特化处理
 *    修改默认的比较规则。
 *
 *
 * 本例使用第 2 种方式：
 * 自定义函数对象 StudentCompare。
 */

class Student
{
public:
    /**
     * 构造函数
     *
     * 创建 Student 对象时，
     * 需要传入学号、姓名、年龄。
     *
     * 初始化列表：
     * 直接对成员变量进行初始化。
     */
    Student(int id, string name, int age)
    :m_id(id)
    ,m_name(name)
    ,m_age(age)
    {}

    int m_id;       // 学号
    string m_name;  // 姓名
    int m_age;      // 年龄
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
 *
 * 例如：
 * cout << s1 << s2;
 */
ostream & operator<<(ostream & os, const Student & s)
{
    os << s.m_id << " " << s.m_name << " " << s.m_age << endl;
    return os;
}

/**
 * 方式二：自定义比较器，也叫函数对象
 *
 * 函数对象：
 * 本质上是一个类或结构体对象，
 * 但是因为它重载了 operator()，
 * 所以可以像函数一样被调用。
 *
 * 例如：
 * StudentCompare cmp;
 * cmp(s1, s2);
 *
 * 看起来像调用函数，
 * 实际上调用的是：
 * cmp.operator()(s1, s2);
 */
struct StudentCompare
{
    /**
     * 重载 operator()
     *
     * 作用：
     * 指定两个 Student 对象之间的比较规则。
     *
     * 参数：
     * lhs：left hand side，左操作数
     * rhs：right hand side，右操作数
     *
     * 返回值：
     * true：
     * 表示 lhs 应该排在 rhs 前面。
     *
     * false：
     * 表示 lhs 不应该排在 rhs 前面。
     *
     * 函数后面的 const：
     * 表示该函数不会修改 StudentCompare 对象本身。
     */
    bool operator()(const Student & lhs, const Student & rhs) const
    {
        /**
         * 指定比较规则：
         * 按照年龄 age 升序排序。
         *
         * lhs 的年龄小于 rhs 的年龄，
         * 则 lhs 排在 rhs 前面。
         *
         * 注意：
         * 当前比较规则只比较 m_age，
         * 所以 set 会根据 m_age 判断是否重复。
         */
        return lhs.m_age < rhs.m_age;
    }
};

void test1()
{
    /**
     * set<Student, StudentCompare>
     *
     * set 的第一个模板参数：
     * Student
     * 表示 set 中存储的元素类型。
     *
     * set 的第二个模板参数：
     * StudentCompare
     * 表示自定义比较器类型。
     *
     * 创建 set 时，
     * set 会使用 StudentCompare 中的 operator()
     * 对 Student 对象进行排序和去重。
     */
    set<Student, StudentCompare> box;

    /**
     * 插入 Student 对象
     *
     * Student{2,"zs",18}
     * 表示创建一个临时的 Student 对象。
     */
    box.insert(Student{2,"zs",18});

    /**
     * set 根据比较规则判断是否重复
     *
     * 当前比较规则只比较 m_age。
     *
     * 所以只要两个 Student 对象的 m_age 相同，
     * set 就认为它们是等价元素。
     *
     * 前面已经插入过年龄为 18 的对象，
     * 所以这里再次插入年龄为 18 的对象时，
     * 插入不会成功。
     */
    box.insert(Student{2,"zs",18});

    /**
     * 继续插入其他 Student 对象
     *
     * 最终 set 会按照年龄升序保存：
     * 18, 19, 20
     */
    box.insert(Student{1,"ls",20});
    box.insert(Student{3,"ww",19});

    /**
     * 输出 set 中的元素
     *
     * print 内部使用范围 for 遍历。
     *
     * 对于 set<Student, StudentCompare> 来说，
     * 遍历顺序就是 StudentCompare 指定的排序顺序。
     */
    print(box);
}

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}