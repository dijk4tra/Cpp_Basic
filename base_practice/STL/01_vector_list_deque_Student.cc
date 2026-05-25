#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>

using namespace std;

// 定义一个自定义的结构体
struct Student
{
    string name;
    int age;

    // 构造函数
    Student(string n, int a) 
    : name(n), age(a) 
    {
        cout << "【构造】" << name << " 被创建了" << endl;
    }

    // 核心点 1：重载 == 运算符
    // 如果没有这个，list.remove() 或某些查找算法会直接报错，
    // 因为编译器不知道怎么判断两个学生“相等”
    bool operator==(const Student& other) const
    {
        return this->name == other.name && this->age == other.age;
    }


};

// 辅助打印函数
template <typename T>
void printStudent(const string& containerName, const T& container)
{
    cout << containerName << " 里的学生: ";
    for (const auto& stu : container)
    {
        cout << "[" << stu.name << ", " << stu.age << "] ";
    }
    cout << endl << "------------------------" << endl;
}


int main()
{
    // ==========================================
    // 1. VECTOR + emplace_back (原地构造)
    // ==========================================
    cout << "=== 1. Vector & Deque 测试 ===" << endl;
    vector<Student> vec;

    // 传统做法：先创建一个临时对象，再复制/移动进容器
    cout << "使用 push_back:" << endl;
    vec.push_back(Student("Alice", 20));

    cout << "\n使用 emplace_back:" << endl;
    // 现代 C++ 做法：直接把参数传进去，在容器内存里“就地”构造对象，少了一次拷贝
    vec.emplace_back("Bob", 22);
    printStudent("Vector", vec);

    // Deque 同样支持 emplace_front 和 emplace_back
    deque<Student> deq;
    deq.emplace_front("Charlie", 23); // 头插
    deq.emplace_back("Diana", 21);   // 尾插
    printStudent("Deque", deq);
    

    // ==========================================
    // 2. LIST + 运算符重载测试
    // ==========================================
    cout << endl << "=== 2. List 测试 ===" << endl;
    list<Student> lst;
    lst.emplace_back("Eve", 24);
    lst.emplace_back("Frank", 25);
    lst.emplace_back("Grace", 26);
    printStudent("List 初始状态", lst);

    // 修改：通过引用修改
    lst.front().age = 16; // 修改第一个学生的年龄

    // 删除：利用 remove 删除“小红”
    // 注意：这里传入了一个临时的 Student 对象，编译器会调用我们写的 operator== 来对比
    cout << "尝试删除 [小红, 16]..." << endl;
    lst.remove(Student("小红", 16));

    printStudent("List 删除后", lst);

    return 0;
}