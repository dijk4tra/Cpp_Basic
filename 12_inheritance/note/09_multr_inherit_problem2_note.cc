#include <iostream>

using std::cout;
using std::endl;

/**
 * 多重继承问题 2：
 * 菱形继承 diamond inheritance。
 *
 *
 * 什么是菱形继承？
 *
 * 当一个类 D 同时继承了两个类 B 和 C，
 * 而 B 和 C 又都继承了同一个类 A 时，
 * 就会出现菱形继承问题。
 *
 * 继承关系如下：
 *
 *        A
 *      /   \
 *     B     C
 *      \   /
 *        D
 *
 *
 * 如果 B 和 C 都是普通继承 A，
 * 那么 D 对象中会包含两份 A 类子对象：
 *
 * 1. 通过 B 继承来的一份 A
 * 2. 通过 C 继承来的一份 A
 *
 * 这样访问 A 类中的成员时，
 * 编译器就不知道应该访问哪一份 A 中的成员，
 * 从而产生二义性。
 *
 * 例如：
 * d.m_a;
 *
 * 编译器不知道访问的是：
 * B 中继承来的 A::m_a
 * 还是
 * C 中继承来的 A::m_a
 *
 *
 * 菱形继承的解决方法：
 *
 * 使用虚继承 virtual inheritance。
 *
 * 在 B 和 C 继承 A 时，
 * 加上 virtual 关键字：
 *
 * class B : virtual public A
 * {
 *
 * };
 *
 * class C : virtual public A
 * {
 *
 * };
 *
 *
 * 使用虚继承以后：
 *
 * D 对象中只会保留一份 A 类子对象。
 *
 * 这样通过 D 对象访问 A 类中的成员时，
 * 就不会再产生二义性。
 *
 *
 * 虚继承的对象模型：
 *
 * 使用虚继承时，
 * 对象结构中通常会多一个虚基指针 vbptr。
 *
 * vbptr 指向虚基表 vbtable。
 *
 * 虚基表中保存的是偏移信息。
 *
 * 程序可以通过：
 *
 * vbptr + 偏移信息
 *
 * 找到共享的虚基类子对象。
 *
 *
 * 注意：
 * 虚继承会让虚基类子对象在最终派生类对象中只保留一份。
 *
 * 在这个例子中：
 * A 是虚基类。
 * B 和 C 都虚继承 A。
 * D 同时继承 B 和 C。
 *
 * 所以 D 对象中只有一份 A 类子对象。
 */

class A
{
public:
    // A 类中的成员变量
    double m_a = 1;
};

class B
: virtual public A // B 虚继承 A
{
public:
    /**
     * B 使用 virtual public A 继承 A。
     *
     * 表示 A 是 B 的虚基类。
     *
     * 这样以后如果某个类同时继承 B 和 C，
     * 且 C 也虚继承 A，
     * 那么最终派生类对象中只会有一份 A 类子对象。
     */

    double m_b = 2;
};

class C
: virtual public A // C 虚继承 A
{
public:
    /**
     * C 也使用 virtual public A 继承 A。
     *
     * B 和 C 都虚继承 A，
     * 是解决菱形继承问题的关键。
     */

    double m_c = 3;
};

class D
: public B
, public C
{
public:
    /**
     * D 同时继承 B 和 C。
     *
     * 因为 B 和 C 都虚继承 A，
     * 所以 D 对象中不会有两份 A 类子对象，
     * 而是只有一份共享的 A 类子对象。
     */

    double m_d = 4;
};

void test1()
{
    // 创建 D 对象
    D d;

    /**
     * D 对象中包含：
     *
     * 1. 从 B 继承来的部分
     * 2. 从 C 继承来的部分
     * 3. D 自己定义的部分
     * 4. 一份共享的虚基类 A 子对象
     */

    // 访问 D 自己定义的成员
    d.m_d;

    // 访问从 B 中继承来的成员
    d.m_b;

    // 访问从 C 中继承来的成员
    d.m_c;

    /**
     * 如果没有使用虚继承：
     *
     * B 普通继承 A，
     * C 普通继承 A，
     * D 又同时继承 B 和 C。
     *
     * 那么 D 对象中会有两份 A 类子对象，
     * 也就会有两份 m_a。
     *
     * 此时直接访问 d.m_a 会产生二义性。
     */

    /* d.m_a; // 没有使用虚继承时，D 对象中有 2 份 m_a，不知道访问哪个，二义性 */

    /**
     * 使用虚继承后：
     *
     * B 和 C 共享同一份 A 类子对象。
     *
     * 所以 D 对象中只有一份 m_a，
     * 通过 d.m_a 可以直接访问，
     * 不会产生二义性。
     */

    d.m_a;

    /**
     * 查看 D 对象大小。
     *
     * 从逻辑上看，D 对象中有：
     *
     * 1. B 中的 m_b
     * 2. C 中的 m_c
     * 3. D 中的 m_d
     * 4. A 中的 m_a
     *
     * 但是由于使用了虚继承，
     * B 和 C 子对象中通常还会各自保存一个虚基指针 vbptr。
     *
     * 所以 sizeof(d) 的结果，
     * 不只是 4 个 double 的大小。
     *
     * 具体大小和编译器、平台、对象模型有关。
     */

    cout << sizeof(d) << endl;
}

int main(int argc, char *argv[])
{
    // 测试菱形继承和虚继承
    test1();

    return 0;
}