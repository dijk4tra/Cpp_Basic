/*
定义类Person，包含姓名（char*）、年龄，提供成员函数display输出信息。
类Employee由Person派生，包含部门（char*）、工资, 
成员函数display用来输出职工姓名、年龄、部门、工资。
要求Employee对象能够进行正确的复制、赋值操作，同时提供计算平均工资的功能。
*/

#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

class Person
{
protected:
    char * m_name;
    int m_age;

public:
    // 构造函数
    Person(const char *name = "", int age = 0)
    {
        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
        m_age = age;
    }

    // 拷贝构造函数
    Person(const Person & p)
    {
        m_name = new char[strlen(p.m_name) + 1];
        strcpy(m_name, p.m_name);
        m_age = p.m_age;
    }
    
    // operator=
    Person & operator=(const Person & p)
    {
        if(this != &p){
            char * old_ptr = m_name;
            m_name = new char[strlen(p.m_name) + 1];
            strcpy(m_name, p.m_name);
            delete [] old_ptr;
            m_age = p.m_age;
        }
        return *this;
    }
    
    // 析构函数
    virtual ~Person()
    {
        delete [] m_name;
    }

    virtual void display() const
    {
        cout << "姓名: " << m_name << endl;
        cout << "年龄: " << m_age << endl;
    }

};

class Employee : public Person
{
private:
    char * m_department;
    double m_salary;

public:
    Employee(const char* name = "", int age = 0,
             const char* department = "",
             const double salary = 0.0)
    : Person(name, age)
    {
        m_department = new char[strlen(department) + 1];
        strcpy(m_department, department);
        m_salary = salary;
    }
    
    Employee(const Employee & e)
    : Person(e)
    {
        m_department = new char[strlen(e.m_department) + 1];
        strcpy(m_department, e.m_department);
        m_salary = e.m_salary;
    }

    Employee & operator=(const Employee & e)
    {
        if(this != &e)
        {
            Person::operator=(e);
            
            char * old = m_department;

            m_department = new char[strlen(e.m_department) + 1];
            strcpy(m_department, e.m_department);
            delete [] old;
            m_salary = e.m_salary;
        }
        return *this;
    }

    ~Employee()
    {
        delete [] m_department;
    }

    virtual void display() const override
    {
        cout << "姓名: " << m_name << endl;
        cout << "年龄: " << m_age << endl;
        cout << "部门: " << m_department << endl;
        cout << "工资: " << m_salary << endl;
    }

    double getSalary() const
    {
        return m_salary;
    }

    static double averageSalary(Employee arr[], int n)
    {
        if(n <= 0) return 0;

        double sum = 0.0;
        for(int i = 0; i < n; ++i)
        {
            sum += arr[i].getSalary();
        }
        return sum / n;
    }
};

int main()
{
    Employee e1("张三", 30, "技术部", 8000);
    Employee e2("李四", 28, "财务部", 7000);

    Employee e3 = e1; // 调用拷贝构造函数
    e2 = e1;          // 调用赋值运算符
    
    e1.display();
    cout << "----------" << endl;

    e3.display();
    cout << "----------" << endl;

    Employee employees[3] = {
        Employee("张三", 30, "技术部", 8000),
        Employee("李四", 28, "财务部", 7000),
        Employee("王五", 35, "人事部", 9000)
    };
    
    cout << "平均工资: "
         << Employee::averageSalary(employees, 3)
         << endl;

}
