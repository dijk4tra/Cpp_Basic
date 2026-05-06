/**
 * 定义一个`Student`类，包含私有数据成员：姓名（`string`类型）、学号（`int`类型）、成绩（`double`类型）。
 * 要求：
 * 1. 提供带参数的构造函数进行初始化；
 * 2. 提供`print`函数输出学生信息；
 * 3. 在`main`函数中创建两个学生对象并输出其信息。
 */

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Student
{
private:
    string m_name;
    int id;
    double score;
public:
    Student(const string &name, int id, double score)
    : m_name(name), id(id), score(score)
    {
    }

    void print() const
    {
        cout << "Name: " << m_name << ", ID: " << id << ", Score: " << score << endl;
    }
};

int main(int argc, char *argv[])
{
    Student s1("zs", 001, 95.5);
    Student s2("ls", 002, 88.0);

    s1.print();
    s2.print();

    return 0;
}
