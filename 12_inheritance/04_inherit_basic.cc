#include <iostream>

using std::cout;
using std::endl;

/*
 * 继承的基本语法：
 * 在已有类的基础上进行扩展。
 *
 * 子类可以复用父类中的成员，
 * 也可以定义子类自己的成员。
 *
 * class A {};              // A 是父类，也称为基类
 * class B : public A {};   // B 是子类，也称为派生类
 *
 * 注意：
 * class 定义的类，如果继承时不写继承方式，默认是 private 继承。
 * struct 定义的类型，如果继承时不写继承方式，默认是 public 继承。
 */

class Father
{
public:
    int m_data1;

protected:
    int m_data2;

private:
    int m_data3;
};

class Son
/* : public Father */
: Father // 没有写继承方式时，class 默认是 private 继承
{
public:
    void func()
    {
        m_data1; // 可以访问：Father 的 public 成员在 Son 中变为 private
        m_data2; // 可以访问：Father 的 protected 成员在 Son 中变为 private

        /* m_data3; // 不能访问：Father 的 private 成员不能被子类直接访问 */
    }
};

class GrandSon
: Son // 没有写继承方式时，class 默认是 private 继承
{
public:
    void func()
    {
        /*
         * 不能访问：
         * m_data1 和 m_data2 在 Son 中已经变为 private，
         * GrandSon 不能直接访问 Son 的 private 成员。
         */
        /* m_data1; */
        /* m_data2; */

        /*
         * 不能访问：
         * m_data3 是 Father 的 private 成员，
         * 派生类始终不能直接访问。
         */
        /* m_data3; */
    }
};

class Father1
{
public:
    int m_father1Data;
};

class Father2
{
public:
    int m_father2Data;
};

// Son1 同时继承 Father1 和 Father2，称为多继承
class Son1
/*
 * : public Father1, Father2
 *
 * 上面这种写法不是语法错误，但容易出错：
 * Father1 是 public 继承，
 * Father2 没有写继承方式，因此默认是 private 继承。
 */
: public Father1
, public Father2
{

};

void test1()
{
    Son1 son1;

    son1.m_father1Data; // Father1 的 public 成员，类外可以访问
    son1.m_father2Data; // Father2 的 public 成员，类外可以访问
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}