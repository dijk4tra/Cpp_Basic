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
 */

/**
 * 类的前向声明。
 *
 * 因为 FriendClass 的成员函数 func 中，
 * 参数类型使用到了 MyClass。
 *
 * 但是此时 MyClass 还没有完整定义，
 * 所以需要先告诉编译器：
 * MyClass 是一个类类型。
 */
class MyClass;

class FriendClass;

/**
 * FriendClass 类
 *
 * 这个类中的成员函数 func，
 * 后面会被声明为 MyClass 的友元函数。
 */
class FriendClass
{
public:
    /**
     * 这里只做函数声明，不写函数实现。
     *
     * 因为 func 的参数是 MyClass 对象的引用，
     * 这里只需要知道 MyClass 是一个类类型即可。
     *
     * 但是如果要在函数体中访问 MyClass 的成员，
     * 就必须等 MyClass 完整定义之后再实现。
     */
    void func(const MyClass & obj);
};

class MyClass
{
public:
    // 普通成员函数
    int getData()
    {
        return m_data;
    }

    /**
     * 把 FriendClass 类中的成员函数 func，
     * 声明为 MyClass 的友元函数。
     *
     * 注意：
     * 这里不是把整个 FriendClass 类声明为友元，
     * 而只是把 FriendClass::func 这一个成员函数声明为友元。
     *
     * 因此，只有 FriendClass::func 可以访问 MyClass 的 private 成员。
     * FriendClass 中的其他成员函数不能访问。
     */
    friend
    void FriendClass::func(const MyClass & obj);

private:
    /**
     * private 成员变量
     *
     * 类外部不能直接访问 obj.m_data。
     * 但是 MyClass 已经把 FriendClass::func 声明为 friend，
     * 所以后面 func 的实现中可以访问 obj.m_data。
     */
    int m_data = 1;
};

/**
 * FriendClass 中 func 的实现。
 *
 * 这里必须写在 MyClass 完整定义之后。
 *
 * 因为函数体中访问了 obj.m_data，
 * 编译器需要知道 MyClass 类中确实有 m_data 这个成员，
 * 并且需要通过 friend 声明判断它是否有访问 private 成员的权限。
 */
void FriendClass::func(const MyClass & obj)
{
    /**
     * func 是 MyClass 的友元函数，
     * 所以可以直接访问 MyClass 对象的 private 成员 m_data。
     */
    cout << obj.m_data << endl;
}


void test1()
{
    // 当前测试函数中暂时没有测试代码
}


int main(int argc, char *argv[])
{
    test1();

    return 0;
}