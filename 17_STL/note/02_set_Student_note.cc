#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <string>

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
 * 3. 元素会按照指定规则自动排序
 *    插入元素时，不是按照插入顺序保存，
 *    而是根据比较规则放到合适的位置。
 *
 * 4. 默认排序规则是 std::less<T>
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
 * 1. set 中的元素需要排序
 *    set 需要知道哪个元素应该排在前面，
 *    哪个元素应该排在后面。
 *
 * 2. set 需要根据比较规则判断两个元素是否“相同”
 *    对于 set 来说，
 *    如果两个元素互相都不小于对方，
 *    set 就认为它们是等价元素。
 *
 *    也就是说：
 *    a < b 为 false，
 *    b < a 也为 false，
 *    那么 a 和 b 会被认为是相同元素。
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
 * 本例使用第 1 种方式：
 * 在 Student 类中重载 operator<。
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

    /**
     * 重载 operator<
     *
     * 作用：
     * 为 Student 类型提供“小于”比较规则。
     *
     * 为什么要写 const：
     * 1. 参数 const Student & rhs
     *    表示 rhs 是只读引用，
     *    避免拷贝，同时保证不会修改 rhs。
     *
     * 2. 函数后面的 const
     *    表示该成员函数不会修改当前对象的数据成员。
     *
     * set 内部在排序和查找时，
     * 需要频繁使用这个比较规则。
     */
    bool operator<(const Student & rhs) const
    {
        /**
         * 指定比较规则：
         * 按照学号 id 升序排序。
         *
         * 当前对象的 m_id 小于 rhs 的 m_id，
         * 当前对象就排在 rhs 前面。
         */
        return this->m_id < rhs.m_id;

        /**
         * 也可以改成按照姓名升序排序。
         *
         * 如果使用下面这条规则，
         * set 就会按照姓名排序，
         * 并且姓名相同的对象会被认为是重复元素。
         */
        // return this->m_name < rhs.m_name;
    }

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
 * cout << s 这样的写法是无法编译通过的。
 *
 * 参数说明：
 * 1. ostream & os
 *    表示输出流对象，例如 cout。
 *
 * 2. const Student & s
 *    表示要输出的 Student 对象。
 *    使用 const 引用可以避免拷贝，
 *    并且保证不会修改 s。
 *
 * 返回值：
 * 返回 ostream &，
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

void test1()
{
    /**
     * set<Student>
     *
     * 创建一个保存 Student 对象的 set 容器。
     *
     * 因为 Student 类中重载了 operator<，
     * 所以 set<Student> 默认会使用 Student::operator<
     * 作为排序规则。
     */
    set<Student> box;

    /**
     * 插入 Student 对象
     *
     * Student{2,"zs",18}
     * 表示创建一个临时的 Student 对象。
     *
     * 插入 set 时，
     * set 会根据 Student::operator< 的规则
     * 判断这个对象应该放到什么位置。
     */
    box.insert(Student{2,"zs",18});

    /**
     * set 根据比较规则判断是否重复
     *
     * 当前 operator< 只比较 m_id。
     *
     * 所以只要两个 Student 对象的 m_id 相同，
     * set 就认为它们是等价元素。
     *
     * 前面已经插入过 m_id 为 2 的对象，
     * 所以这里再次插入 m_id 为 2 的对象时，
     * 插入不会成功。
     */
    box.insert(Student{2,"zs",18});

    /**
     * 继续插入其他 Student 对象
     *
     * 最终 set 会按照 m_id 升序保存：
     * 1, 2, 3
     */
    box.insert(Student{1,"ls",20});
    box.insert(Student{3,"ww",19});

    /**
     * 输出 set 中的元素
     *
     * print 内部使用范围 for 遍历。
     *
     * 对于 set<Student> 来说，
     * 遍历顺序就是 Student::operator< 指定的排序顺序。
     */
    print(box);
}

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}