#include <iostream>
#include <vector>
#include <list>
#include <deque>

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

/**
 * list 中特有的 sort() 操作
 *
 * sort()：
 * 对 list 容器中的元素进行排序。
 *
 * 注意：
 * list 有自己的 sort() 成员函数。
 *
 * vector 没有 sort() 成员函数，
 * 如果 vector 需要排序，
 * 要使用标准库算法 sort()。
 *
 * 对于内置类型：
 * 例如 int、double、char 等，
 * 可以直接调用 sort()。
 *
 * 默认排序规则：
 * 升序排序。
 */
void test1()
{
    list<int> box{ 3, 1, 2, 5, 4 };

    print(box);

    // 对 list 中的元素进行排序
    //
    // int 是内置类型，
    // 编译器知道如何比较两个 int 的大小，
    // 所以可以直接调用 sort()。
    //
    // 排序后结果为：
    // 1 2 3 4 5
    box.sort();

    print(box);
}

/**
 * Student 类：
 * 用来演示 list 中保存自定义类型时，
 * 如何进行排序。
 */
class Student
{
public:
    /**
     * 有参构造函数
     *
     * Student(int id, string name, int age)
     *
     * 创建 Student 对象时，
     * 需要传入学生 id、姓名和年龄。
     */
    Student(int id, string name, int age)
    : m_id(id)
    , m_name(name)
    , m_age(age)
    {

    }

    int m_id;       // 学号
    string m_name;  // 姓名
    int m_age;      // 年龄
};

/**
 * 重载 operator<< 输出运算符
 *
 * 作用：
 * 让 Student 对象可以直接使用 cout 输出。
 *
 * 如果没有重载 operator<<，
 * print(box) 中的 cout << e 就无法输出 Student 对象。
 *
 * 参数：
 * ostream & os：
 * 表示输出流对象，例如 cout。
 *
 * const Student & s：
 * 表示要输出的 Student 对象。
 *
 * 返回值：
 * ostream&
 *
 * 返回输出流本身，
 * 这样可以支持连续输出。
 */
ostream & operator<<(ostream & os, const Student & s)
{
    os << s.m_id << " " << s.m_name << " " << s.m_age;

    return os;
}

/**
 * 针对自定义类型进行比较排序
 *
 * 对于自定义类型 Student 来说，
 * 编译器不知道应该按照什么规则排序。
 *
 * 例如：
 * 可以按照学号排序，
 * 也可以按照年龄排序，
 * 还可以按照姓名排序。
 *
 * 所以不能直接写：
 * box.sort();
 *
 * 否则会报错。
 *
 * 解决方式：
 * 给 sort() 传入一个比较规则。
 *
 * 常见写法：
 * 1. 使用 lambda 表达式。
 * 2. 重载 operator<。
 * 3. 定义函数对象。
 *
 * 这里使用 lambda 表达式演示。
 */
void test2()
{
    Student s1(2, "张三", 19);
    Student s2(1, "李四", 21);
    Student s3(3, "王五", 20);

    // 创建 list 容器
    // 容器中保存 Student 类型对象
    list<Student> box{
        s1,
        s2,
        s3,
    };

    print(box);

    /**
     * 错误写法：
     *
     * box.sort();
     *
     * 原因：
     * Student 是自定义类型，
     * 没有默认的大小比较规则。
     *
     * list 的 sort() 默认需要使用 < 比较元素大小，
     * 但是 Student 没有重载 operator<，
     * 所以直接调用 box.sort() 会报错。
     */
    // box.sort();

    /**
     * 正确写法：
     * 给 sort() 传入比较规则。
     *
     * [](const Student & lhs, const Student & rhs)
     *
     * []：
     * 表示 lambda 表达式的捕获列表。
     * 当前没有使用外部变量，所以为空。
     *
     * const Student & lhs：
     * 表示参与比较的左边对象。
     *
     * const Student & rhs：
     * 表示参与比较的右边对象。
     *
     * return lhs.m_id < rhs.m_id;
     * 表示按照学号升序排序。
     *
     * 如果返回 true，
     * 表示 lhs 应该排在 rhs 前面。
     */
    box.sort([](const Student & lhs, const Student & rhs){
        return lhs.m_id < rhs.m_id;
    });

    print(box);
}

int main(int argc, char const *argv[])
{
    // test1();  // list 对内置类型排序

    // list 对自定义类型排序
    test2();

    return 0;
}