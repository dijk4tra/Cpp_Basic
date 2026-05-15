#include <iostream>

using std::cout;
using std::endl;

/**
 * overload VS oversee VS override：
 *
 * 1. overload
 *    重载。
 *
 *    发生在同一个作用域中。
 *    函数名相同，但是参数列表不同。
 *
 *
 * 2. hide(oversee)
 *    隐藏。
 *
 *    发生在继承关系中。
 *    父类和子类中有同名成员。
 *
 *    当通过子类对象访问同名成员时，
 *    默认访问的是子类自己的成员。
 *
 *    父类中的同名成员不会消失，
 *    只是被子类中的同名成员隐藏了。
 *
 *
 * 3. override
 *    重写，覆盖。
 *
 *    发生在继承关系中。
 *    父类中通常有 virtual 虚函数，
 *    子类重新实现这个虚函数。
 *
 *
 * oversee 隐藏：
 *
 * 父类和子类中有同名的成员变量或者成员函数时，
 * 通过子类对象访问该成员，
 * 默认访问的是子类中的成员。
 *
 * 如果想访问父类中的同名成员，
 * 需要通过类名作用域的方式访问：
 *
 * 子类对象.父类名::成员名
 *
 * 例如：
 * son.Father::m_data
 * son.Father::func()
 */

class Father
{
public:
    // 父类中的成员函数
    void func()
    {
        cout << "Father::func()" << endl;
    }

    // 父类中的成员变量
    int m_data = 1;
};

class Son : public Father
{
public:
    /**
     * 子类中定义了和父类同名的成员函数 func。
     *
     * 这时通过 Son 对象直接调用 func()，
     * 默认调用的是 Son 类中的 func()。
     *
     * Father 中的 func() 被隐藏了，
     * 但是并没有消失。
     */
    void func()
    {
        cout << "Son::func()" << endl;
    }

    /**
     * 子类中定义了和父类同名的成员变量 m_data。
     *
     * 这时通过 Son 对象直接访问 m_data，
     * 默认访问的是 Son 类中的 m_data。
     *
     * Father 中的 m_data 被隐藏了，
     * 但是仍然存在于 Son 对象中。
     */
    int m_data = 2;
};

void test1()
{
    // 创建子类对象
    Son son;

    /**
     * 子类和父类中都有 m_data。
     *
     * 通过子类对象直接访问 m_data，
     * 默认访问的是子类 Son 中的 m_data。
     */

    cout << son.m_data << endl; // 输出 2，体现出的是子类的结果

    /**
     * Son 对象中同时包含：
     *
     * 1. 从 Father 中继承来的 m_data
     * 2. Son 自己定义的 m_data
     *
     * 虽然两个成员变量名字相同，
     * 但是它们是两个不同的成员。
     *
     * 所以 Son 对象中有两个 int 类型成员，
     * sizeof(son) 通常为 8B。
     */

    cout << sizeof(son) << endl;

    /**
     * 如果想要访问父类中的同名成员，
     * 需要通过类名作用域方式访问。
     *
     * 格式：
     * 对象.父类名::成员名
     */

    cout << son.Father::m_data << endl; // 输出 1，访问父类中的 m_data

    /**
     * 子类和父类中都有 func()。
     *
     * 通过子类对象直接调用 func()，
     * 默认调用的是子类 Son 中的 func()。
     */

    son.func(); // 输出 Son::func()，子类的结果

    /**
     * 如果想调用父类中的同名成员函数，
     * 也可以通过类名作用域方式访问。
     */

    son.Father::func(); // 输出 Father::func()
}

int main(int argc, char *argv[])
{
    // 测试继承关系中的同名成员隐藏
    test1();

    return 0;
}