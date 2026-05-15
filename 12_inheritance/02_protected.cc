#include <iostream>

using std::cout;
using std::endl;

/**
 * 访问权限修饰符：
 * public
 * protected
 * private
 *
 * private 和 protected 的区别：
 * 1. 父类中的 protected 成员，在派生类内部可以访问；
 * 2. 父类中的 private 成员，在派生类内部不可以直接访问；
 * 3. private 权限最严格，只能在本类内部访问。
 *
 * 注意：
 * 继承关系并不会让派生类直接访问父类的 private 成员。
 */

class MyClass
{
public:
    void func()
    {
        // 在本类内部，可以访问本类中的 public、protected、private 成员
        m_data1;
        m_data2;
        m_data3;
    }

    int m_data1;

protected:
    int m_data2;

private:
    int m_data3;
};

void test1()
{
    MyClass obj;

    obj.m_data1; // public 成员：类外可以访问

    /* obj.m_data2; // protected 成员：类外不能访问 */
    /* obj.m_data3; // private 成员：类外不能访问 */
}

class Father
{
public:
    int m_data1;

protected:
    int m_data2;

private:
    int m_data3;
};

class Son : public Father
{
public:
    void sonMethod()
    {
        m_data1; // 父类 public 成员：派生类内部可以访问
        m_data2; // 父类 protected 成员：派生类内部可以访问

        /* m_data3; // 父类 private 成员：派生类内部不能直接访问 */
    }
};

int main(int argc, char *argv[])
{
    test1();
    return 0;
}