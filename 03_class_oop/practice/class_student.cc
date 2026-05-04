#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

class Student
{
private:
    char * m_name;
    int m_id;
    int m_age;
public:
    Student(const char *name, int id, int age)
    : m_name(new char[strlen(name)+1]{}),
      m_id(id),
      m_age(age)
    {
        cout << "constructor" << endl;
        strcpy(m_name, name);
    }

    void print()
    {
        cout << m_name << " " << m_id << " " << m_age << endl;
    }

    ~Student()
    {
        cout << "destructor" << endl;
        if(m_name)
        {
            delete [] m_name;
            m_name = nullptr;
        }
    }
};

void test1()
{
    // 局部对象,函数调用结束时自动调用析构函数
    Student s1{"zhangsan", 00001, 23};
    Student s2{"lisi", 00002, 24};
    Student s3{"wangwu", 00003, 25};

    s1.print();
    s2.print();
    s3.print();
}

// 全局对象,程序结束时自动调用析构函数
/* Student s4{"shenzhilong", 00004, 25}; */

void test2()
{
    cout << "test2 start" << endl;
    // 静态对象,程序结束时自动调用析构函数
    static Student s5{"xiaowu", 00006, 26};
    s5.print();
    cout << "test2 end" << endl;
}

void test3()
{   
    // 存储于堆空间的对象
    Student *p = new Student{"suansuan", 00007, 26};
    // 这里的对象没有名字,无法通过对象名.访问成员
    // 需要通过指针->来访问成员
    p->print();
    // 对于存储于堆空间的对象,不会自动调用析构函数
    // delete指针时会调用析构函数
    delete p;
    p = nullptr;
}

int main(int argc, char *argv[])
{   
    cout << "main start" << endl;
    /* test1(); */
    /* test2(); */
    test3();
    cout << "main end" << endl;
    return 0;
}
