#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;

/**
 * map 的使用场景：
 * 一般情况下，map 适合做数据统计。
 *
 *
 * 举例 1：
 * 班级里面不同省份的同学有多少个？
 *
 * 河南：3
 * 湖北：5
 *
 * key：省份
 * value：人数
 *
 * 可以使用：
 * map<string, int>
 *
 *
 * 举例 2：
 * 班级里面不同省份的同学都是谁？
 *
 * 河南：{"张三", "李四", "王五"}
 * 湖北：{"赵六", "钱七"}
 *
 * key：省份
 * value：同学姓名的集合
 *
 * 可以使用：
 * map<string, vector<string>>
 *
 *
 * 举例 3：
 * 班级里面不同省份的学生对象分别是谁？
 *
 * key：省份
 * value：Student 对象的集合
 *
 * 可以使用：
 * map<string, vector<Student>>
 *
 *
 * 总结：
 * map 的 key 一般用来表示分类依据。
 * map 的 value 用来表示分类之后对应的数据。
 */

// 遍历 map<string, int>
void visitMap(map<string,int> &m)
{
    /**
     * map 中每一个元素都是一个 pair。
     *
     * p.first  表示 key
     * p.second 表示 value
     */
    for(auto & p : m){
        cout << p.first << " = " << p.second << endl;
    }
}

// map 的 operator[]
void test1()
{
    map<string,int> m;

    // 通过 insert 插入键值对
    m.insert({"one", 1});
    m.insert({"two", 2});
    m.insert({"three", 3});
    m.insert({"four", 4});

    visitMap(m);

    cout << "---------" << endl;

    /**
     * map 支持 operator[]。
     *
     * 注意：
     * map 的下标不是位置下标，
     * 而是 key。
     *
     * 通过 key 可以访问对应的 value。
     */

    // 如果 key 已经存在，
    // m["two"] 表示访问 key 为 "two" 的 value，
    // 然后将 value 修改为 20。
    m["two"] = 20;

    // 如果 key 不存在，
    // m["five"] 会先插入一个新的键值对，
    // 然后把 value 设置为 5。
    m["five"] = 5;

    visitMap(m);
}

// 删除元素 erase
void test2()
{
    map<string,int> m;

    m.insert({"one", 1});
    m.insert({"two", 2});
    m.insert({"three", 3});
    m.insert({"four", 4});

    visitMap(m);

    cout << "---------" << endl;

    // begin() 指向 map 中第一个元素
    auto it = m.begin();

    // 迭代器向后移动一次
    ++it;

    /**
     * erase(迭代器)
     *
     * 作用：
     * 删除迭代器指向的元素。
     *
     * 注意：
     * map 会按照 key 升序排列，
     * 所以 begin() 指向的是 key 最小的元素。
     */
    m.erase(it);

    visitMap(m);
}

/**
 * map<string, vector<string>> 示例
 *
 * 需求：
 * 统计不同省份的同学都是谁。
 *
 * key：
 * 省份，string 类型。
 *
 * value：
 * 同学姓名的集合，vector<string> 类型。
 */
void visitMapStudentName(map<string, vector<string>> & m)
{
    for(auto & p : m){
        // p.first 表示省份
        cout << p.first << " : ";

        // p.second 表示该省份对应的所有学生姓名
        for(auto & name : p.second){
            cout << name << " ";
        }

        cout << endl;
    }
}

void test3()
{
    /**
     * 创建 map<string, vector<string>> 容器。
     *
     * key 是 string 类型，表示省份。
     * value 是 vector<string> 类型，表示该省份的学生姓名。
     */
    map<string, vector<string>> m;

    /**
     * 使用 operator[] 往 vector 中添加元素。
     *
     * m["河南"] 表示：
     * 访问 key 为 "河南" 对应的 value。
     *
     * 这个 value 的类型是 vector<string>，
     * 所以可以继续调用 push_back 添加学生姓名。
     *
     * 如果 "河南" 这个 key 不存在，
     * map 会先自动插入一个新的键值对：
     *
     * key 是 "河南"
     * value 是一个空的 vector<string>
     *
     * 然后再执行 push_back。
     */
    m["河南"].push_back("张三");
    m["河南"].push_back("李四");
    m["河南"].push_back("王五");

    m["湖北"].push_back("赵六");
    m["湖北"].push_back("钱七");

    m["湖南"].push_back("孙八");

    visitMapStudentName(m);
}

/**
 * Student 类
 *
 * 用来表示一个学生对象。
 */
class Student
{
public:
    Student(int id, string name, int age)
    : m_id(id)
    , m_name(name)
    , m_age(age)
    {}

    // 打印学生信息
    void print()
    {
        cout << m_id << " " << m_name << " " << m_age;
    }

    int m_id;
    string m_name;
    int m_age;
};

/**
 * map<string, vector<Student>> 示例
 *
 * 需求：
 * 统计不同省份的学生对象分别是谁。
 *
 * key：
 * 省份，string 类型。
 *
 * value：
 * 学生对象的集合，vector<Student> 类型。
 */
void visitMapStudent(map<string, vector<Student>> & m)
{
    for(auto & p : m){
        // p.first 表示省份
        cout << p.first << " : " << endl;

        // p.second 表示该省份对应的所有 Student 对象
        for(auto & stu : p.second){
            stu.print();
            cout << endl;
        }

        cout << endl;
    }
}

void test4()
{
    /**
     * 创建 map<string, vector<Student>> 容器。
     *
     * key 是 string 类型，表示省份。
     * value 是 vector<Student> 类型，表示该省份的学生对象。
     */
    map<string, vector<Student>> m;

    /**
     * m["河南"] 的类型是 vector<Student>。
     *
     * 所以可以调用 push_back，
     * 往这个 vector 中添加 Student 对象。
     */
    m["河南"].push_back(Student{1001, "张三", 18});
    m["河南"].push_back(Student{1002, "李四", 19});
    m["河南"].push_back(Student{1003, "王五", 20});

    m["湖北"].push_back(Student{1004, "赵六", 18});
    m["湖北"].push_back(Student{1005, "钱七", 21});

    m["湖南"].push_back(Student{1006, "孙八", 22});

    visitMapStudent(m);
}

/**
 * map<string, int> 示例
 *
 * 需求：
 * 统计不同省份的同学有多少个。
 *
 * key：
 * 省份。
 *
 * value：
 * 人数。
 */
void test5()
{
    map<string, int> m;

    /**
     * 如果 key 不存在，
     * m["河南"] 会自动插入：
     *
     * key 是 "河南"
     * value 是 int 的默认值 0。
     *
     * 然后再执行 ++ 操作。
     */
    ++m["河南"];
    ++m["河南"];
    ++m["河南"];

    ++m["湖北"];
    ++m["湖北"];

    ++m["湖南"];

    visitMap(m);
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */

    // 测试 map<string, vector<string>>
    /* test3(); */

    // 测试 map<string, vector<Student>>
    /* test4(); */

    // 测试 map<string, int> 统计人数
    test5();

    return 0;
}