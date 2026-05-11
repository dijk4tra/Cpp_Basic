#include <iostream>

using std::cout;
using std::endl;

/*
 * 嵌套类的访问规则
 * 
 * 1. 在外部类的外部访问内部类成员
 *    - public 嵌套类：
 *      可以通过 Outer::Inner 创建对象，再通过对象访问其成员。
 *      其中 public 成员可以访问，private 成员不能访问，除非设置友元。
 *
 *    - private 嵌套类：
 *      外部默认不能直接创建对象，因为没有访问权限。
 *      如果外部函数被声明为友元，则可以访问该嵌套类。
 *      但创建对象后，仍然只能访问其 public 成员；
 *      private 成员依然需要额外的友元权限。
 *
 * 2. 在外部类内部访问内部类成员
 *    - 可以直接创建内部类对象，例如 Inner inner;
 *    - 通过对象访问内部类成员时，public 成员可以访问，private 成员不能访问；
 *    - 如果必须访问内部类的 private 成员，可以使用友元。
 *
 *    注意：
 *    在外部类内部，内部类本身是 public 还是 private 已经不影响创建对象，
 *    但内部类成员自身的访问权限仍然有效。
 *
 * 3. 在内部类内部访问外部类成员
 *    - 可以创建外部类对象，例如 Outer outer;
 *    - 再通过对象访问外部类成员；
 *    - 嵌套类可以访问外部类的 private 成员。
 */

class Outer
{
public:
    // public 嵌套类
    class Inner1
    {
    public:
        void inner1Method1()
        {
            cout << "inner1Method1()" << endl;

            // 在内部类中访问外部类成员
            // 先创建外部类对象，再通过对象访问成员
            Outer outer;

            outer.m_outerNum1; // public 成员：可以访问
            outer.m_outerNum2; // private 成员：也可以访问

            outer.outerMethod1();
            outer.outerMethod2();

            // 嵌套类可以访问外部类的所有成员，不受外部类成员访问权限影响
        }

        int m_inner1Num1;

        friend void test1();

    private:
        void inner1Method2()
        {
            cout << "inner1Method2()" << endl;
        }

        int m_inner1Num2;
    };

private:
    // private 嵌套类
    class Inner2
    {
    public:
        void inner2Method1()
        {
            cout << "inner2Method1()" << endl;

            // 在内部类中访问外部类成员
            // 先创建外部类对象，再通过对象访问成员
            Outer outer;

            outer.m_outerNum1;
            outer.m_outerNum2;
            outer.outerMethod1();
            outer.outerMethod2();
        }

        int m_inner2Num1;

    private:
        void inner2Method2()
        {
            cout << "inner2Method1()" << endl;
        }

        int m_inner2Num2;
    }; 

public:
    // 外部类的 public 成员
    int m_outerNum1;

    void outerMethod1()
    {
        cout << "outerMethod1()" << endl;

        // 在外部类内部访问内部类成员
        // 可以直接创建内部类对象

        // public 嵌套类
        Inner1 inner1;

        inner1.m_inner1Num1; // public 成员：可以访问
        inner1.inner1Method1();

        /* inner1.m_inner1Num2;  // private 成员：不能访问，除非设置友元 */
        inner1.inner1Method1();
        /* inner1.inner1Method2(); */

        // private 嵌套类
        // 在外部类内部可以直接创建对象
        Inner2 inner2;

        inner2.m_inner2Num1; // public 成员：可以访问
        /* inner2.m_inner2Num2; // private 成员：不能访问 */
    }

private:
    void outerMethod2()
    {
        cout << "outerMethod1()" << endl;
    }

    int m_outerNum2;

    // 将 test1 声明为友元函数，使其可以在外部访问 private 嵌套类 Inner2
    friend void test1();
};


void test1()
{
    // 在外部类的外部访问内部类成员
    // 需要通过 外部类名::内部类名 指定该内部类所属的外部类

    Outer::Inner1 inner1;

    inner1.m_inner1Num1;    // public 成员：可以访问
    inner1.m_inner1Num2;    // private 成员：正常情况下不能访问，这里因为 test1 是友元函数，所以可以访问

    inner1.inner1Method1();
    inner1.inner1Method2();

    // Inner2 是 private 嵌套类
    // 正常情况下外部不能创建 Inner2 对象
    // 这里因为 test1 是 Outer 的友元函数，所以可以访问 Inner2
    Outer::Inner2 inner2;

    inner2.m_inner2Num1;    // public 成员：可以访问
    /* inner2.m_inner2Num2; // private 成员：不能访问 */ 

    inner2.inner2Method1();
    /* inner2.inner2Method2(); */
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}