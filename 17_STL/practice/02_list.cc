#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Student
{
    string name; // 姓名
    int chinese; // 语文成绩
    int math;    // 数学成绩
    int english; // 英语成绩
    int sum;     // 总成绩

    Student(string n, int c, int m, int e)
    : name(n), chinese(c), math(m), english(e)
    {
        sum = chinese + math + english;
    }
};


// 编写排序规则回调函数
// 返回 true 表示 s1 应该排在 s2 前面
bool compareStudent(const Student& s1, const Student& s2)
{
    if (s1.sum != s2.sum)
    {
        // 规则：按照总成绩进行降序排列
        return s1.sum > s2.sum;
    }
    else
    {
        // 规则：如果总成绩相同，按照语文成绩进行降序排列
        return s1.chinese > s2.chinese;
    }
}

// 打印学生列表的辅助函数
void printList(const list<Student>& stuList)
{
    cout << "姓名\t总分\t语文\t数学\t英语" << endl;
    cout << "--------------------------------------------" << endl;
    for(const auto& stu : stuList)
    {
        cout << stu.name << "\t" 
             << stu.sum << "\t" 
             << stu.chinese << "\t" 
             << stu.math << "\t" 
             << stu.english << endl;
    }
}

int main() 
{
    // 创建一个 list 容器，用于存储学生信息
    list<Student> studentList;

    studentList.push_back(Student("张三", 85, 90, 80)); // 总分 255，语文 85
    studentList.push_back(Student("李四", 95, 95, 95)); // 总分 285
    studentList.push_back(Student("王五", 90, 85, 80)); // 总分 255，语文 90
    studentList.push_back(Student("赵六", 70, 80, 75)); // 总分 225
    studentList.push_back(Student("孙七", 92, 98, 95)); // 总分 285，语文 92

    cout << "=== 排序前的学生成绩单 ===" << endl;
    printList(studentList);

    studentList.sort(compareStudent);
    cout << "=== 排序后的学生成绩单 ===" << endl;
    printList(studentList);

    return 0;
}