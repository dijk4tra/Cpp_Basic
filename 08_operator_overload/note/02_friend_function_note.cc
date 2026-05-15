#include <iostream>
#include <ostream>

using std::cout;
using std::endl;

/**
 * friend 友元：
 *
 * friend 可以让类外部的函数或者其他类，
 * 访问当前类的 private 成员。
 *
 * 友元常见形式：
 * 1. 普通函数的友元形式
 *    把一个普通函数声明为当前类的友元函数。
 *
 * 2. 成员函数的友元形式
 *    把另一个类中的某个成员函数，
 *    声明为当前类的友元函数。
 *
 * 3. 友元类
 *    把另一个类整体声明为当前类的友元类。
 *
 * 注意：
 * friend 只是授权外部函数或者外部类访问 private 成员，
 * 它本身并不是类的成员函数。
 */


class MyClass
{
public:
    // 普通成员函数
    int getData()
    {
        return m_data;
    }

    /**
     * 把普通函数 test1 声明为 MyClass 的友元函数。
     *
     * test1 虽然不是 MyClass 的成员函数，
     * 但是因为被声明为了 friend，
     * 所以它可以访问 MyClass 对象的 private 成员 m_data。
     *
     * 友元声明可以写在 public 区域，
     * 也可以写在 private 区域。
     * 写在哪里都不影响友元权限。
     */
    friend void test1();

private:
    /**
     * 把普通函数 test2 声明为 MyClass 的友元函数。
     *
     * 注意：
     * friend 声明写在 private 区域也是可以的。
     * friend 声明本质上是在给外部函数授权，
     * 不受 public/private 访问权限的影响。
     */
    friend void test2();

    // private 成员变量
    // 类外部不能直接访问 obj.m_data
    int m_data;
};


void test1()
{
    MyClass obj;

    /**
     * test1 是 MyClass 的友元函数，
     * 所以可以直接访问 obj 的 private 成员 m_data。
     *
     * 如果 test1 没有被声明为 friend，
     * 这里访问 obj.m_data 会编译报错。
     */
    cout << obj.m_data << endl;
}

void test2()
{
    MyClass obj;

    /**
     * test2 也是 MyClass 的友元函数，
     * 虽然它的 friend 声明写在 private 区域，
     * 但是仍然可以访问 private 成员 m_data。
     */
    cout << obj.m_data << endl;
}


int main(int argc, char *argv[])
{
    // 调用友元函数 test1
    test1();

    return 0;
}