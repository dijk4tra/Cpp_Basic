#include <iostream>

using std::cout;
using std::endl;

/**
 * 访问权限修饰符：
 *
 * C++ 中类的成员有三种访问权限：
 * 1. public
 * 2. protected
 * 3. private
 *
 *
 * public：
 * 公有权限。
 *
 * 类的内部可以访问。
 * 类的外部也可以访问。
 * 子类中也可以访问。
 *
 *
 * protected：
 * 保护权限。
 *
 * 类的内部可以访问。
 * 类的外部不可以访问。
 * 子类中可以访问。
 *
 *
 * private：
 * 私有权限。
 *
 * 类的内部可以访问。
 * 类的外部不可以访问。
 * 子类中也不可以访问。
 *
 *
 * private VS protected：
 *
 * private 和 protected 的区别，
 * 主要体现在继承关系中。
 *
 * 父类中的 protected 成员，
 * 在子类中可以访问。
 *
 * 父类中的 private 成员，
 * 即使有继承关系，
 * 在子类中也不可以访问。
 *
 *
 * private 权限最严格：
 *
 * private 成员只能在当前类的内部访问。
 * 即使子类继承了父类，
 * 子类中也不能直接访问父类的 private 成员。
 */

class MyClass
{
public:
    void func()
    {
        /**
         * 类的内部不受访问权限影响。
         *
         * 在类的成员函数内部，
         * public、protected、private 成员都可以直接访问。
         */

        m_data1; // public 成员，类内部可以访问
        m_data2; // protected 成员，类内部可以访问
        m_data3; // private 成员，类内部可以访问
    }

    // public 成员
    // 类内部、类外部、子类中都可以访问
    int m_data1;

protected:
    // protected 成员
    // 类内部可以访问
    // 类外部不可以访问
    // 子类中可以访问
    int m_data2;

private:
    // private 成员
    // 类内部可以访问
    // 类外部不可以访问
    // 子类中也不可以访问
    int m_data3;
};

void test1()
{
    MyClass obj;

    // public 成员可以在类的外部访问
    obj.m_data1; // public OK

    // protected 成员不可以在类的外部访问
    /* obj.m_data2; // protected NO */

    // private 成员不可以在类的外部访问
    /* obj.m_data3; // private NO */
}

class Father
{
public:
    // public 成员
    int m_data1;

protected:
    // protected 成员
    int m_data2;

private:
    // private 成员
    int m_data3;
};

class Son : public Father
{
public:
    void sonMethod()
    {
        /**
         * Son 类 public 继承 Father 类。
         *
         * 在子类 Son 的成员函数内部，
         * 可以访问父类 Father 中的 public 成员和 protected 成员。
         *
         * 但是不能访问父类 Father 中的 private 成员。
         */

        m_data1; // 父类中的 public 成员，子类中可以访问

        m_data2; // 父类中的 protected 成员，子类中可以访问

        /* m_data3; // 父类中的 private 成员，子类中不可以访问 */
    }
};

int main(int argc, char *argv[])
{
    // 测试类外部访问权限
    test1();

    return 0;
}