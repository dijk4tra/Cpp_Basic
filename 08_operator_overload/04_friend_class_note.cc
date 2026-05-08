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
 * FriendClass 的成员函数参数中使用到了 MyClass，
 * 所以这里先声明 MyClass 是一个类类型。
 */
class MyClass;

class FriendClass;

class FriendClass
{
public:
    // 只做函数声明，函数实现放在 MyClass 完整定义之后
    void func(const MyClass & obj);
    void func2(const MyClass & obj);
    void func3(const MyClass & obj);
};

class MyClass
{
public:
    // 普通成员函数，可以在类内部访问 private 成员
    int getData()
    {
        return m_data;
    }

    /**
     * 下面这种写法是“成员函数友元”的形式。
     *
     * 如果只想让 FriendClass 中的某一个成员函数
     * 访问 MyClass 的 private 成员，
     * 可以单独把这个成员函数声明为 friend。
     *
     * 例如：
     * friend void FriendClass::func(const MyClass & obj);
     */
    /* friend */
    /* void FriendClass::func(const MyClass & obj); */

    /* friend */
    /* void FriendClass::func2(const MyClass & obj); */

    /* friend */
    /* void FriendClass::func3(const MyClass & obj); */

    /**
     * 把 FriendClass 声明为 MyClass 的友元类。
     *
     * 这表示 FriendClass 中的所有成员函数，
     * 都可以访问 MyClass 的 private 成员。
     *
     * 和“成员函数友元”相比，
     * 友元类授权范围更大。
     *
     * 注意：
     * 友元关系是单向的。
     * MyClass 把 FriendClass 声明为友元，
     * 只表示 FriendClass 可以访问 MyClass 的私有成员。
     *
     * 反过来，MyClass 并不会自动拥有
     * 访问 FriendClass 私有成员的权限。
     */
    friend class FriendClass;

private:
    /**
     * private 成员变量。
     *
     * 类外部不能直接访问 obj.m_data。
     * 但是 FriendClass 是 MyClass 的友元类，
     * 所以 FriendClass 的成员函数可以访问它。
     */
    int m_data = 1;
};

// FriendClass 中 func 的实现
void FriendClass::func(const MyClass & obj)
{
    /**
     * FriendClass 是 MyClass 的友元类，
     * 所以 FriendClass 中的成员函数
     * 可以直接访问 MyClass 对象的 private 成员。
     */
    cout << obj.m_data << endl;
}

void FriendClass::func2(const MyClass & obj)
{
    // 同样可以访问 MyClass 的 private 成员
    cout << obj.m_data << endl;
}

void FriendClass::func3(const MyClass & obj)
{
    // 同样可以访问 MyClass 的 private 成员
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