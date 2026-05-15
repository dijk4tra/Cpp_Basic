#include <iostream>

/**
 * 多继承问题 1：二义性
 *
 * 当一个类 C 同时继承 A 和 B，
 * 而 A 和 B 中存在同名成员时，
 * 通过 C 对象直接访问该同名成员，可能会产生二义性。
 *
 * 例如：
 * A 中有 func()，B 中也有 func()。
 * 如果 C 中没有定义自己的 func()，
 * 那么通过 C 对象直接调用 c.func() 时，
 * 编译器无法判断应该调用 A::func() 还是 B::func()，
 * 因此会产生编译错误。
 *
 * 解决方法：
 * 使用类名作用域限定符，明确指定要访问哪个父类中的成员。
 *
 * 例如：
 * c.A::func();
 * c.B::func();
 *
 * 注意：
 * 如果 C 中定义了自己的 func()，
 * 那么 c.func() 会优先调用 C::func()，
 * 此时不会产生二义性。
 */

using std::cout;
using std::endl;

class A
{
public:
    void func()
    {
        cout << "A::func()" << endl;
    }
};

class B
{
public:
    void func()
    {
        cout << "B::func()" << endl;
    }
};

// C 同时继承 A 和 B，属于多继承
class C
: public A
, public B
{
public:
    void func()
    {
        cout << "C::func()" << endl;
    }
};

void test1()
{
    C c;

    /*
     * 如果 C 中没有定义 func()，
     * 那么下面这句会产生二义性：
     *
     * c.func();
     *
     * 因为 A 和 B 中都有 func()，
     * 编译器无法判断应该调用 A::func() 还是 B::func()。
     */

    // 当前 C 中定义了自己的 func()，
    // 所以这里调用的是 C::func()。
    c.func();

    // 如果想访问父类中的同名函数，
    // 可以通过类名作用域限定符明确指定。
    c.A::func();
    c.B::func();
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}