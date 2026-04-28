#include <iostream>

using std::cout;
using std::endl;

/*
 * C++中的struct和class有什么区别
 * 默认权限不一样,其他东西一样
 */

// 类中如果没有设置权限,
// 默认是private权限
class Dog
{
    int m_data;
    void func(){};
};

// C中的struct不能写函数
// C++中的struct可以写函数,默认权限是public的
struct Student
{
int m_data;
void func(){
    cout << "Student::func()" << endl;
};
};


void test1()
{
    Dog dog;
    /* dog.m_data; */
    Student stu;
    stu.func();
    stu.m_data;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

