#include <iostream>

using std::cout;
using std::endl;

/**
 * 嵌套类的访问规则：
 *
 * 嵌套类就是定义在另一个类内部的类。
 *
 * 需要注意两层访问权限：
 *
 * 1. 内部类本身的访问权限
 *    也就是 Inner1 / Inner2 放在 Outer 的 public 还是 private 区域。
 *
 * 2. 内部类成员的访问权限
 *    也就是 innerMethod、m_innerNum 本身是 public 还是 private。
 *
 * 访问规则：
 *
 * 1. 在外部类的外部访问内部类的成员
 *
 *    如果内部类是 public 的，
 *    类外部可以通过：
 *    Outer::Inner1 inner1;创建内部类对象。
 *    但是创建对象后，
 *    仍然只能访问 Inner1 的 public 成员。
 *    如果要访问 Inner1 的 private 成员，
 *    需要 Inner1 把外部函数声明为 friend。
 *
 *    如果内部类是 private 的，
 *    类外部不能直接使用这个内部类类型。
 *    除非 Outer 把外部函数声明为 friend。
 *
 * 2. 在外部类的内部访问内部类的成员
 *
 *    外部类内部可以直接创建内部类对象。
 *
 *    此时内部类本身是 public 还是 private，
 *    对 Outer 来说已经没有区别，都可以直接创建对象。
 *
 *    但是 Outer 通过对象访问内部类成员时，
 *    仍然只能访问内部类的 public 成员。
 *    如果要访问内部类的 private 成员，
 *    仍然需要友元关系。
 *
 * 3. 在内部类的内部访问外部类的成员
 *
 *    内部类可以访问外部类的 private 成员。
 *
 *    但是内部类对象并不会自动绑定某个外部类对象。
 *    所以如果要访问外部类的非静态成员，
 *    需要先有一个 Outer 对象，
 *    然后通过对象访问。
 */

class Outer
{
public:
    /**
     * public 内部类。
     *
     * 因为 Inner1 定义在 Outer 的 public 区域，
     * 所以类外部可以使用：
     *
     * Outer::Inner1
     *
     * 来定义对象。
     */
    class Inner1
    {
    public:
        /**
         * Inner1 的 public 成员函数。
         *
         * 类外部创建 Inner1 对象后，
         * 可以直接调用这个函数。
         */
        void inner1Method1()
        {
            cout << "inner1Method1()" << endl;

            /**
             * 在内部类的内部访问外部类的成员。
             *
             * 注意：
             * Inner1 是定义在 Outer 里面的类，
             * 但 Inner1 对象并不自动拥有 Outer 对象。
             *
             * 所以这里先创建一个 Outer 对象 outer，
             * 然后通过 outer 访问 Outer 的成员。
             */
            Outer outer;

            /**
             * 内部类可以访问外部类的 public 成员。
             */
            outer.m_outerNum1;

            /**
             * 内部类也可以访问外部类的 private 成员。
             *
             * 这里可以访问 m_outerNum2，
             * 是因为 Inner1 是 Outer 的嵌套类。
             */
            outer.m_outerNum2;

            /**
             * 内部类可以调用外部类的 public 成员函数。
             */
            outer.outerMethod1();

            /**
             * 内部类也可以调用外部类的 private 成员函数。
             */
            outer.outerMethod2();

            /**
             * 总结：
             *
             * 在内部类的成员函数中，
             * 只要有外部类对象，
             * 就可以通过该对象访问外部类成员，
             * 不受外部类成员 public/private 的限制。
             */
        }

        // Inner1 的 public 成员变量
        int m_inner1Num1;

        /**
         * 将 test1 声明为 Inner1 的友元函数。
         *
         * 这样 test1 虽然在类外部，
         * 也可以访问 Inner1 的 private 成员。
         */
        friend void test1();

    private:
        /**
         * Inner1 的 private 成员函数。
         *
         * 类外部不能直接调用，
         * 除非对应函数被声明为 friend。
         */
        void inner1Method2()
        {
            cout << "inner1Method2()" << endl;
        }

        // Inner1 的 private 成员变量
        int m_inner1Num2;
    };

private:
    /**
     * private 内部类。
     *
     * Inner2 定义在 Outer 的 private 区域，
     * 所以类外部默认不能直接使用：
     *
     * Outer::Inner2
     *
     * 除非类外部的函数是 Outer 的友元函数。
     */
    class Inner2
    {
    public:
        /**
         * Inner2 的 public 成员函数。
         */
        void inner2Method1()
        {
            cout << "inner2Method1()" << endl;

            /**
             * 在内部类的内部访问外部类的成员。
             *
             * 和 Inner1 一样，
             * 需要先创建 Outer 对象，
             * 再通过对象访问外部类成员。
             */
            Outer outer;

            // 访问 Outer 的 public 成员
            outer.m_outerNum1;

            // 访问 Outer 的 private 成员
            outer.m_outerNum2;

            // 调用 Outer 的 public 成员函数
            outer.outerMethod1();

            // 调用 Outer 的 private 成员函数
            outer.outerMethod2();
        }

        // Inner2 的 public 成员变量
        int m_inner2Num1;

    private:
        /**
         * Inner2 的 private 成员函数。
         *
         * 即使外部函数 test1 是 Outer 的友元，
         * 可以使用 Outer::Inner2 这个类型，
         * 也不代表它能访问 Inner2 的 private 成员。
         *
         * 如果想访问 Inner2 的 private 成员，
         * 还需要 Inner2 自己把 test1 声明为 friend。
         */
        void inner2Method2()
        {
            cout << "inner2Method1()" << endl;
        }

        // Inner2 的 private 成员变量
        int m_inner2Num2;
    };

public:
    // Outer 的 public 成员变量
    int m_outerNum1;

    /**
     * Outer 的 public 成员函数。
     */
    void outerMethod1()
    {
        cout << "outerMethod1()" << endl;

        /**
         * 在外部类的内部访问内部类的成员。
         *
         * 因为当前函数属于 Outer，
         * 所以可以直接使用 Outer 内部定义的类。
         */

        /**
         * 创建 public 内部类 Inner1 的对象。
         */
        Inner1 inner1;

        /**
         * 通过对象访问 Inner1 的 public 成员。
         */
        inner1.m_inner1Num1;
        inner1.inner1Method1();

        /**
         * 但是 Outer 通过 Inner1 对象访问成员时，
         * 仍然不能访问 Inner1 的 private 成员。
         *
         * 除非 Inner1 把 Outer 或者 Outer 的成员函数声明为 friend。
         */
        /* inner1.m_inner1Num2; */     // private 成员：NO，除非友元
        /* inner1.inner1Method2(); */  // private 成员函数：NO，除非友元

        /**
         * 创建 private 内部类 Inner2 的对象。
         *
         * 虽然 Inner2 是 private 内部类，
         * 但是这里位于 Outer 类的内部，
         * 所以可以直接使用 Inner2。
         */
        Inner2 inner2;

        /**
         * 访问 Inner2 的 public 成员。
         */
        inner2.m_inner2Num1;
        inner2.inner2Method1();

        /**
         * 仍然不能访问 Inner2 自己的 private 成员。
         */
        /* inner2.m_inner2Num2; */     // private 成员：NO
        /* inner2.inner2Method2(); */  // private 成员函数：NO
    }

private:
    /**
     * Outer 的 private 成员函数。
     */
    void outerMethod2()
    {
        cout << "outerMethod1()" << endl;
    }

    // Outer 的 private 成员变量
    int m_outerNum2;

    /**
     * 将 test1 声明为 Outer 的友元函数。
     *
     * 这样 test1 可以访问 Outer 的 private 成员，
     * 也可以使用 Outer 的 private 内部类 Inner2。
     *
     * 注意：
     * 这只表示 test1 是 Outer 的友元。
     * 并不表示 test1 自动成为 Inner2 的友元。
     */
    friend void test1();
};


void test1()
{
    /**
     * 在外部类的外部访问内部类的成员。
     *
     * 如果内部类是 public 的，
     * 可以通过：
     *
     * 外部类名::内部类名
     *
     * 来创建内部类对象。
     */
    Outer::Inner1 inner1;

    /**
     * 访问 Inner1 的 public 成员变量。
     */
    inner1.m_inner1Num1;

    /**
     * m_inner1Num2 是 Inner1 的 private 成员。
     *
     * 正常情况下类外部不能访问。
     *
     * 但是 Inner1 中写了：
     * friend void test1();
     *
     * 所以 test1 可以访问 Inner1 的 private 成员。
     */
    inner1.m_inner1Num2;

    /**
     * 调用 Inner1 的 public 成员函数。
     */
    inner1.inner1Method1();

    /**
     * inner1Method2 是 Inner1 的 private 成员函数。
     *
     * 因为 test1 是 Inner1 的友元函数，
     * 所以这里可以调用。
     */
    inner1.inner1Method2();

    /**
     * Inner2 是 Outer 的 private 内部类。
     *
     * 正常情况下，类外部不能直接写：
     * Outer::Inner2 inner2;
     *
     * 但是 Outer 把 test1 声明为了 friend，
     * 所以 test1 可以使用 Outer::Inner2 这个 private 内部类类型。
     */
    Outer::Inner2 inner2;

    /**
     * test1 可以创建 Inner2 对象后，
     * 访问 Inner2 的 public 成员。
     */
    inner2.m_inner2Num1;
    inner2.inner2Method1();

    /**
     * 但是 test1 不是 Inner2 的友元函数。
     *
     * 所以即使 test1 可以使用 Inner2 这个 private 类型，
     * 也不能访问 Inner2 自己的 private 成员。
     */
    /* inner2.m_inner2Num2; */     // private 成员：NO
    /* inner2.inner2Method2(); */  // private 成员函数：NO
}

int main(int argc, char *argv[])
{
    /**
     * 测试嵌套类在不同位置下的访问权限。
     */
    test1();

    return 0;
}