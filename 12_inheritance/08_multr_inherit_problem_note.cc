#include <iostream>

/**
 * 多重继承问题 1：
 * 二义性 ambiguity。
 *
 *
 * 什么是二义性？
 *
 * 当一个类 C 同时继承了两个类 A 和 B，
 * 而 A 和 B 中都有一个同名成员时，
 * 就可能出现二义性问题。
 *
 * 例如：
 * A 中有 func()
 * B 中也有 func()
 * C 同时继承 A 和 B
 *
 * 如果 C 中没有自己的 func()，
 * 那么通过 C 对象直接调用 func() 时：
 *
 * c.func();
 *
 * 编译器无法确定到底应该调用：
 * A::func()
 * 还是
 * B::func()
 *
 * 因此会产生编译错误。
 *
 *
 * 二义性的解决方法：
 *
 * 在调用同名成员时，
 * 明确指定要访问哪个父类中的成员。
 *
 * 可以使用类名作用域运算符：
 *
 * 对象.父类名::成员名
 *
 * 例如：
 * c.A::func();
 * c.B::func();
 *
 *
 * 如果子类中也定义了同名成员：
 *
 * 通过子类对象直接调用该成员时，
 * 默认访问的是子类自己的成员。
 *
 * 父类中的同名成员会被隐藏，
 * 但是父类中的成员并没有消失。
 *
 * 如果想访问父类中的同名成员，
 * 仍然可以通过类名作用域方式访问。
 */

using std::cout;
using std::endl;

class A
{
public:
    // A 类中的成员函数 func
    void func()
    {
        cout << "A::func()" << endl;
    }
};

class B
{
public:
    // B 类中的成员函数 func
    void func()
    {
        cout << "B::func()" << endl;
    }
};

// C 多继承 A 和 B
class C
: public A
, public B
{
public:
    /**
     * C 类中也定义了一个和父类同名的 func 函数。
     *
     * 这样通过 C 对象直接调用 func() 时，
     * 默认调用的是 C 自己的 func()。
     *
     * A::func() 和 B::func() 会被隐藏，
     * 但是仍然可以通过作用域运算符访问。
     */
    void func()
    {
        cout << "C::func()" << endl;
    }
};

void test1()
{
    /**
     * 创建子类对象。
     *
     * C 同时继承了 A 和 B。
     * 所以 C 对象中包含：
     *
     * 1. A 类部分
     * 2. B 类部分
     * 3. C 类自己定义的部分
     */

    C c;

    /**
     * 如果 C 中没有 func 函数：
     *
     * A 中有 func()
     * B 中也有 func()
     *
     * 那么通过 C 对象直接调用 func() 时，
     * 编译器不知道应该调用 A::func() 还是 B::func()。
     *
     * 因此会出现二义性错误。
     */

    /* c.func(); // error：二义性，不知道该调用哪个 func() */

    /**
     * 如果子类 C 中有和父类同名的成员函数 func()：
     *
     * 通过子类对象直接调用 func()，
     * 默认调用的是子类 C 自己的 func()。
     */

    c.func(); // 调用子类 C 的 func()

    /**
     * 如果想要访问父类中的同名函数，
     * 需要通过类名作用域方式指定。
     *
     * 格式：
     * 对象.父类名::成员函数()
     */

    c.A::func(); // 调用父类 A 中的 func()

    c.B::func(); // 调用父类 B 中的 func()
}

int main(int argc, char *argv[])
{
    // 测试多继承中的同名函数二义性问题
    test1();

    return 0;
}