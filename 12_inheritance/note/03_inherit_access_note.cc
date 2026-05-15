#include <iostream>

using std::cout;
using std::endl;

/**
 * 继承方式：
 *
 * C++ 中常见的继承方式有三种：
 * 1. public 继承
 * 2. protected 继承
 * 3. private 继承
 *
 *
 * 继承方式影响的是：
 * 父类中的 public 成员和 protected 成员，
 * 继承到子类之后的访问权限。
 *
 * 注意：
 * 父类中的 private 成员，
 * 不管使用哪种继承方式，
 * 子类中都不能直接访问。
 *
 *
 * public 继承：
 *
 * 父类中的 public 成员，
 * 到子类中仍然是 public 成员。
 *
 * 父类中的 protected 成员，
 * 到子类中仍然是 protected 成员。
 *
 *
 * protected 继承：
 *
 * 父类中的 public 成员，
 * 到子类中变成 protected 成员。
 *
 * 父类中的 protected 成员，
 * 到子类中仍然是 protected 成员。
 *
 * 也就是说：
 * protected 继承之后，
 * 父类中可以被继承的成员，
 * 在子类中最多只能是 protected 权限。
 *
 * 所以类外部不能通过子类对象访问这些成员，
 * 但是子类的子类仍然可以继续访问。
 *
 * protected 继承：
 * 最下方的类也可以访问祖先类的成员。
 * 可以理解为“千秋万代”。
 *
 *
 * private 继承：
 *
 * 父类中的 public 成员，
 * 到子类中变成 private 成员。
 *
 * 父类中的 protected 成员，
 * 到子类中变成 private 成员。
 *
 * 也就是说：
 * private 继承之后，
 * 父类中可以被继承的成员，
 * 在子类中都变成 private 权限。
 *
 * 所以子类自己可以访问，
 * 但是子类的子类不能继续访问。
 *
 * private 继承：
 * 最下方的类不能访问祖先类的成员。
 * 可以理解为“断子绝孙”。
 */

class GrandFather
{
public:
    // public 成员
    int m_data1;
};

class Father : public GrandFather
{
public:
    // Father public 继承 GrandFather
    //
    // GrandFather 中的 public 成员 m_data1，
    // 继承到 Father 中以后仍然是 public 成员。

    int m_data2;
};

class Son : public Father
{
    /**
     * Son public 继承 Father。
     *
     * 因为 Father 中的 m_data1 和 m_data2 都是 public 成员，
     * 所以 Son 对象可以在类外部直接访问：
     * son.m_data1;
     * son.m_data2;
     */
};


class Father1
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

// public 继承
class Son1 : public Father1
{
public:
    void func()
    {
        /**
         * public 继承：
         *
         * 父类中的 public 成员，
         * 到子类中仍然是 public。
         *
         * 父类中的 protected 成员，
         * 到子类中仍然是 protected。
         *
         * 父类中的 private 成员，
         * 子类中不能直接访问。
         */

        m_data1; // 父类中的 public 成员，子类中可以访问

        m_data2; // 父类中的 protected 成员，子类中可以访问

        /* m_data3; // error，父类中的 private 成员，子类中不能访问 */
    }
};

class Father2
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

// protected 继承
class Son2 : protected Father2
{
public:
    void func()
    {
        /**
         * protected 继承：
         *
         * 父类中的 public 成员，
         * 到子类中会变成 protected 成员。
         *
         * 父类中的 protected 成员，
         * 到子类中仍然是 protected 成员。
         *
         * 父类中的 private 成员，
         * 子类中不能直接访问。
         */

        m_data1; // 父类中的 public 成员，子类中可以访问

        m_data2; // 父类中的 protected 成员，子类中可以访问

        /* m_data3; // error，父类中的 private 成员，子类中不能访问 */
    }
};

class GrandSon2 : protected Son2
{
public:
    void func()
    {
        /**
         * GrandSon2 protected 继承 Son2。
         *
         * 因为 Son2 是 protected 继承 Father2，
         * 所以 Father2 中的 public 成员 m_data1
         * 到 Son2 中变成了 protected 成员。
         *
         * Father2 中的 protected 成员 m_data2
         * 到 Son2 中仍然是 protected 成员。
         *
         * protected 成员可以被下一代子类继续访问，
         * 所以 GrandSon2 中仍然可以访问 m_data1 和 m_data2。
         */

        m_data1; // 祖先类 Father2 中的 public 成员，经过 protected 继承后仍可在后代类中访问

        m_data2; // 祖先类 Father2 中的 protected 成员，后代类中可以访问

        /* m_data3; // private NO，父类中的 private 成员，后代类中也不能访问 */
    }
};

class Father3
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

// private 继承
class Son3 : private Father3
{
public:
    void func()
    {
        /**
         * private 继承：
         *
         * 父类中的 public 成员，
         * 到子类中会变成 private 成员。
         *
         * 父类中的 protected 成员，
         * 到子类中也会变成 private 成员。
         *
         * 父类中的 private 成员，
         * 子类中不能直接访问。
         */

        m_data1; // 父类中的 public 成员，子类中可以访问

        m_data2; // 父类中的 protected 成员，子类中可以访问

        /* m_data3; // error，父类中的 private 成员，子类中不能访问 */
    }
};

class GrandSon3 : private Son3
{
public:
    void func()
    {
        /**
         * GrandSon3 private 继承 Son3。
         *
         * Son3 是 private 继承 Father3。
         *
         * Father3 中的 public 成员 m_data1
         * 到 Son3 中变成了 private 成员。
         *
         * Father3 中的 protected 成员 m_data2
         * 到 Son3 中也变成了 private 成员。
         *
         * private 成员只能在 Son3 类内部访问，
         * GrandSon3 作为 Son3 的子类，
         * 也不能直接访问 Son3 中的 private 成员。
         *
         * 所以 GrandSon3 中不能访问 m_data1 和 m_data2。
         */

        /* m_data1; // 不能访问，已经在 Son3 中变成 private 成员 */
        /* m_data2; // 不能访问，已经在 Son3 中变成 private 成员 */
        /* m_data3; // 不能访问，Father3 中的 private 成员本来就不能被子类直接访问 */
    }
};

void test1()
{
    Son son;

    /**
     * Son public 继承 Father，
     * Father public 继承 GrandFather。
     *
     * 所以 GrandFather 中的 public 成员 m_data1，
     * 经过多层 public 继承之后，
     * 在 Son 中仍然是 public 成员。
     *
     * Father 中的 public 成员 m_data2，
     * 在 Son 中也仍然是 public 成员。
     *
     * 因此可以在类外部通过 Son 对象直接访问。
     */

    son.m_data1; // 可以访问祖先类 GrandFather 中的 public 成员
    son.m_data2; // 可以访问父类 Father 中的 public 成员
}

int main(int argc, char *argv[])
{
    // 测试多层 public 继承之后的访问权限
    test1();

    return 0;
}