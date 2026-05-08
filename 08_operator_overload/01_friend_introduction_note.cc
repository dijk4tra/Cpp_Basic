#include <iostream>

using std::cout;
using std::endl;

/**
 * 友元 friend：
 * 
 * 在 C++ 中，类的 private 成员只能在类的内部访问。
 * 类的外部代码不能直接访问 private 成员。
 *
 * 但是可以通过 friend 友元机制，
 * 让某个函数或者某个类拥有访问当前类 private 成员的权限。
 *
 * 友元可以理解成：
 * 当前类主动“授权”某个外部函数或外部类，
 * 让它可以访问自己的私有成员。
 *
 * 注意：
 * friend 会破坏类的封装性，
 * 所以实际开发中不要滥用。
 */

class MyClass
{
public:
    /**
     * 普通成员函数
     *
     * 成员函数属于类的内部，
     * 所以可以直接访问本类的 private 成员 m_data。
     *
     * 外部代码如果想获取 m_data，
     * 可以通过这个 public 成员函数间接访问。
     */
    int getData()
    {
        return m_data;
    }

private:
    /**
     * private 成员变量
     *
     * m_data 是私有成员，
     * 只能在 MyClass 类的内部直接访问。
     *
     * 类的外部不能通过对象直接访问：
     * obj.m_data;
     */
    int m_data = 1;
};


void test1()
{
    // 创建 MyClass 对象
    MyClass obj;

    /**
     * m_data 是 private 成员，
     * 在类的外部不能直接访问。
     *
     * 所以下面这行代码如果打开，
     * 会编译报错。
     */
    /* obj.m_data; */

    /**
     * getData 是 public 成员函数，
     * 可以在类的外部通过对象调用。
     *
     * getData 函数在类的内部访问 m_data，
     * 外部代码通过 getData 间接获取 m_data 的值。
     */
    obj.getData();
}

int main(int argc, char *argv[])
{
    // 测试 private 成员的访问方式
    test1();

    return 0;
}