#include <iostream>

using std::cout;
using std::endl;

/**
 * 继承的基本语法：
 *
 * 可以在已有类的基础上进行扩展。
 *
 * 子类可以复用父类中的成员，
 * 也可以定义子类自己独有的成员。
 *
 *
 * 基本格式：
 *
 * class A
 * {
 *
 * };
 *
 * class B : public A
 * {
 *
 * };
 *
 *
 * A 是父类，也叫基类。
 * B 是子类，也叫派生类。
 *
 *
 * 继承方式：
 *
 * class 子类名 : 继承方式 父类名
 * {
 *
 * };
 *
 * 继承方式可以是：
 * public
 * protected
 * private
 *
 *
 * 注意：
 * 如果继承时没有写继承方式，
 * class 默认是 private 继承。
 *
 * 例如：
 * class Son : Father
 * {
 *
 * };
 *
 * 等价于：
 * class Son : private Father
 * {
 *
 * };
 */

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

class Son
/* : public Father */
: Father // 没有加继承权限，则默认是 private 继承
{
public:
    void func()
    {
        /**
         * Son 默认 private 继承 Father。
         *
         * private 继承：
         *
         * 父类中的 public 成员，
         * 到子类中变成 private 成员。
         *
         * 父类中的 protected 成员，
         * 到子类中也变成 private 成员。
         *
         * 父类中的 private 成员，
         * 子类中不能直接访问。
         *
         *
         * 注意：
         * 虽然 m_data1 和 m_data2 继承到 Son 中后变成 private，
         * 但是在 Son 类自己的成员函数内部，
         * 仍然可以访问它们。
         */

        m_data1; // 父类中的 public 成员，子类内部可以访问

        m_data2; // 父类中的 protected 成员，子类内部可以访问

        /* m_data3; // 父类中的 private 成员，子类中不能直接访问 */
    }
};

class GrandSon
: Son // 没有加继承权限，默认 private 继承 Son
{
public:
    void func()
    {
        /**
         * GrandSon 继承 Son。
         *
         * Son 是 private 继承 Father。
         *
         * 所以 Father 中的 public 成员 m_data1，
         * 到 Son 中变成了 private 成员。
         *
         * Father 中的 protected 成员 m_data2，
         * 到 Son 中也变成了 private 成员。
         *
         * private 成员只能在 Son 类内部访问，
         * GrandSon 作为 Son 的子类，
         * 不能直接访问 Son 中的 private 成员。
         *
         * 所以 GrandSon 中不能访问 m_data1 和 m_data2。
         */

        /* m_data1; // 不能访问，已经在 Son 中变成 private 成员 */

        /* m_data2; // 不能访问，已经在 Son 中变成 private 成员 */

        /* m_data3; // 不能访问，Father 中的 private 成员本来就不能被子类直接访问 */
    }
};

class Father1
{
public:
    // Father1 中的 public 成员
    int m_father1Data;
};

class Father2
{
public:
    // Father2 中的 public 成员
    int m_father2Data;
};

/**
 * 多继承：
 *
 * 一个子类可以同时继承多个父类。
 *
 * 语法：
 * class 子类名 : 继承方式 父类1, 继承方式 父类2
 * {
 *
 * };
 *
 * 例如：
 * class Son1 : public Father1, public Father2
 * {
 *
 * };
 *
 * 表示：
 * Son1 同时 public 继承 Father1 和 Father2。
 *
 *
 * 注意：
 * 多继承时，每一个父类前面都要单独写继承方式。
 *
 * class Son1 : public Father1, Father2
 *
 * 这种写法不是 Father1 和 Father2 都是 public 继承。
 *
 * 因为 Father2 前面没有写继承方式，
 * 所以 Father2 默认是 private 继承。
 */

// Son1 多继承 Father1 和 Father2
class Son1
/* : public Father1, Father2  // 错误写法，Father2 为 private 继承 */
: public Father1
, public Father2
{
    /**
     * Son1 public 继承 Father1，
     * 同时 public 继承 Father2。
     *
     * 所以 Father1 中的 public 成员 m_father1Data，
     * 到 Son1 中仍然是 public 成员。
     *
     * Father2 中的 public 成员 m_father2Data，
     * 到 Son1 中也仍然是 public 成员。
     */
};


void test1()
{
    // 创建 Son1 对象
    Son1 son1;

    /**
     * Son1 同时 public 继承 Father1 和 Father2。
     *
     * 所以可以通过 Son1 对象，
     * 访问 Father1 和 Father2 中的 public 成员。
     */

    son1.m_father1Data; // 访问 Father1 中继承过来的 public 成员

    son1.m_father2Data; // 访问 Father2 中继承过来的 public 成员
}

int main(int argc, char *argv[])
{
    // 测试多继承
    test1();

    return 0;
}