#include <iostream>

using std::cout;
using std::endl;

/**
 * 多继承问题 2：菱形继承
 *
 * 菱形继承结构：
 *
 *        A
 *      /   \
 *     B     C
 *      \   /
 *        D
 *
 * 当 D 同时继承 B 和 C，
 * 而 B 和 C 又都继承同一个基类 A 时，
 * 就形成了菱形继承。
 *
 * 如果 B 和 C 普通继承 A：
 * 1. D 对象中会包含两份 A 子对象；
 * 2. 访问 A 中的成员时会产生二义性；
 * 3. 例如 d.m_a 时，编译器无法判断访问的是 B 中的 A，还是 C 中的 A。
 *
 * 解决方法：
 * 使用虚继承 virtual inheritance。
 *
 * 虚继承的作用：
 * 1. 让最终派生类 D 中只保留一份共享的 A 子对象；
 * 2. 避免访问 A 成员时产生二义性。
 *
 * 注意：
 * 虚继承通常会让对象中增加额外的实现信息，
 * 例如某些编译器会使用虚基指针 vbptr 和虚基表 vbtable
 * 来定位虚基类子对象。
 *
 * 但对象的具体布局、大小以及虚基类子对象的位置，
 * 都属于编译器实现细节，不同编译器可能不同。
 */

class A
{
public:
    double m_a = 1;
};

class B
: virtual public A // B 虚继承 A
{
public:
    double m_b = 2;
};

class C
: virtual public A // C 虚继承 A
{
public:
    double m_c = 3;
};

class D
: public B
, public C
{
public:
    double m_d = 4;
};

void test1()
{
    D d;

    d.m_d; // 访问 D 自己的成员
    d.m_b; // 访问 B 中的成员
    d.m_c; // 访问 C 中的成员

    /*
     * 如果 B 和 C 没有使用虚继承，
     * 那么 D 对象中会有两份 A 子对象，
     * 此时直接访问 d.m_a 会产生二义性：
     *
     * d.m_a; // error：不知道访问 B 路径下的 A，还是 C 路径下的 A
     *
     * 可以通过 d.B::m_a 或 d.C::m_a 指定访问路径，
     * 但这样仍然表示 D 中存在两份 A 子对象。
     */

    /*
     * 使用虚继承后，
     * D 对象中只保留一份共享的 A 子对象，
     * 因此可以直接访问 d.m_a。
     */
    d.m_a;

    /*
     * sizeof(d) 的结果与编译器实现有关。
     * 虚继承通常会带来额外开销，
     * 例如保存用于定位虚基类子对象的信息。
     */
    cout << sizeof(d) << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}