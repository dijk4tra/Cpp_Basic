#include <iostream>

using std::cout;
using std::endl;

/**
 * overload VS hide VS override
 *
 * overload：重载
 * 在同一个作用域中，函数名相同，但参数列表不同。
 *
 * hide：隐藏，也叫同名隐藏
 * 父类和子类中存在同名成员时，
 * 通过子类对象直接访问该成员，默认访问的是子类中的成员。
 *
 * override：重写
 * 父类中有虚函数，子类重新实现该虚函数。
 *
 * 本例演示的是：hide，同名隐藏。
 */

class Father
{
public:
    void func()
    {
        cout << "Father::func()" << endl;
    }

    int m_data = 1;
};

class Son : public Father
{
public:
    void func()
    {
        cout << "Son::func()" << endl;
    }

    int m_data = 2;
};

void test1()
{
    Son son;

    // 子类和父类中都有 m_data，
    // 通过子类对象直接访问时，访问的是子类自己的 m_data。
    cout << son.m_data << endl;

    // Son 对象中同时包含 Father::m_data 和 Son::m_data，
    // 因此这里通常为 8B，即两个 int 的大小。
    cout << sizeof(son) << endl;

    // 如果想访问父类中的同名成员，
    // 可以通过“对象.父类名::成员名”的方式访问。
    cout << son.Father::m_data << endl;

    // 子类和父类中都有 func()，
    // 通过子类对象直接调用时，调用的是子类自己的 func()。
    son.func();

    // 如果想调用父类中的同名函数，
    // 可以通过“对象.父类名::函数名()”的方式调用。
    son.Father::func();
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}