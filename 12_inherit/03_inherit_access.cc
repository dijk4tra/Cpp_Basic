#include <iostream>

using std::cout;
using std::endl;

/*
 * 继承方式会影响父类成员在子类中的访问权限：
 *
 * public 继承：
 * 父类 public 成员    -> 子类 public 成员
 * 父类 protected 成员 -> 子类 protected 成员
 *
 * protected 继承：
 * 父类 public 成员    -> 子类 protected 成员
 * 父类 protected 成员 -> 子类 protected 成员
 *
 * private 继承：
 * 父类 public 成员    -> 子类 private 成员
 * 父类 protected 成员 -> 子类 private 成员
 *
 * 注意：
 * 父类 private 成员，无论使用哪种继承方式，
 * 都不能被子类直接访问。
 */

class GrandFather
{
public:
    int m_data1;
};

class Father : public GrandFather
{
public:
    int m_data2;
};

class Son : public Father
{

};

class Father1
{
public:
    int m_data1;

protected:
    int m_data2;

private:
    int m_data3;
};

// public 继承
// Father1 的 public 成员在 Son1 中仍然是 public
// Father1 的 protected 成员在 Son1 中仍然是 protected
class Son1 : public Father1
{
public:
    void func()
    {
        m_data1; // 父类 public 成员：子类内部可以访问
        m_data2; // 父类 protected 成员：子类内部可以访问

        /* m_data3; // 父类 private 成员：子类内部不能直接访问 */
    }
};

class Father2
{
public:
    int m_data1;

protected:
    int m_data2;

private:
    int m_data3;
};

// protected 继承
// Father2 的 public 成员在 Son2 中变为 protected
// Father2 的 protected 成员在 Son2 中仍然是 protected
class Son2 : protected Father2
{
public:
    void func()
    {
        m_data1; // 父类 public 成员变为 protected，子类内部可以访问
        m_data2; // 父类 protected 成员仍为 protected，子类内部可以访问

        /* m_data3; // 父类 private 成员：子类内部不能直接访问 */
    }
};

// GrandSon2 继承 Son2
// 因为 m_data1 和 m_data2 在 Son2 中是 protected，
// 所以 GrandSon2 内部仍然可以访问
class GrandSon2 : protected Son2
{
public:
    void func()
    {
        m_data1; // 可以访问
        m_data2; // 可以访问

        /* m_data3; // 父类 private 成员：不能直接访问 */
    }
};

class Father3
{
public:
    int m_data1;

protected:
    int m_data2;

private:
    int m_data3;
};

// private 继承
// Father3 的 public 成员在 Son3 中变为 private
// Father3 的 protected 成员在 Son3 中也变为 private
class Son3 : private Father3
{
public:
    void func()
    {
        m_data1; // 父类 public 成员变为 private，Son3 内部可以访问
        m_data2; // 父类 protected 成员变为 private，Son3 内部可以访问

        /* m_data3; // 父类 private 成员：子类内部不能直接访问 */
    }
};

// GrandSon3 继承 Son3
// 由于 m_data1 和 m_data2 在 Son3 中已经变成 private，
// 所以 GrandSon3 内部不能再直接访问它们
class GrandSon3 : private Son3
{
public:
    void func()
    {
        /* m_data1; // 不能访问：在 Son3 中已经是 private */
        /* m_data2; // 不能访问：在 Son3 中已经是 private */
        /* m_data3; // 不能访问：Father3 的 private 成员始终不能直接访问 */
    }
};

void test1()
{
    Son son;

    son.m_data1; // public 继承链：GrandFather 的 public 成员仍然可以在类外访问
    son.m_data2; // Father 的 public 成员可以在类外访问
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}