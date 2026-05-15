#include <iostream>

using std::cout;
using std::endl;

/**
 * 虚函数表 virtual table：
 *
 * 当一个类中有虚函数时，
 * 该类的对象中通常会多出一个隐藏的指针：
 * vfptr，虚函数指针。
 *
 * vfptr 指向一张虚函数表：
 * vftable / vtable。
 *
 *
 * 虚函数表中存放的是虚函数的入口地址。
 *
 * 例如 Father 中有 3 个虚函数：
 * func1()
 * func2()
 * func3()
 *
 * 那么 Father 的虚函数表中通常会保存这 3 个虚函数的地址。
 *
 *
 * 子类 Son 继承 Father，
 * 并且重写了 Father 中的 3 个虚函数。
 *
 * 那么 Son 对象中的 vfptr 指向的是 Son 类对应的虚函数表。
 * Son 的虚函数表中保存的是：
 * Son::func1()
 * Son::func2()
 * Son::func3()
 *
 *
 * 注意：
 * 下面的代码是为了观察虚函数表的底层结构，
 * 使用了强制类型转换直接查看对象内存。
 *
 * 这种写法依赖具体编译器、平台和 ABI，
 * 并不是标准 C++ 推荐的写法。
 *
 * 实际开发中不要这样调用虚函数表，
 *这里只用于教学演示。
 */

class Father
{
public:
    /**
     * Father 中定义了第一个虚函数 func1。
     *
     * 因为 Father 类中存在虚函数，
     * 所以 Father 对象中通常会有一个隐藏的 vfptr。
     */
    virtual void func1()
    {
        cout << "Father::func1()" << endl;
    }

    /**
     * Father 中定义了第二个虚函数 func2。
     *
     * func2 的函数入口地址通常会放在
     * Father 虚函数表的第二个位置。
     */
    virtual void func2()
    {
        cout << "Father::func2()" << endl;
    }

    /**
     * Father 中定义了第三个虚函数 func3。
     *
     * func3 的函数入口地址通常会放在
     * Father 虚函数表的第三个位置。
     */
    virtual void func3()
    {
        cout << "Father::func3()" << endl;
    }

    /**
     * 普通数据成员。
     *
     * Father 对象中大致包含：
     * 1. vfptr
     * 2. m_f
     *
     * 在 64 位环境下，
     * 如果 long 占 8 字节，
     * 那么可以用 long * 的方式观察对象中的内容。
     *
     * 但是注意：
     * 不同平台上 long 的大小可能不同。
     * 例如有的平台 long 是 4 字节。
     */
    long m_f = 1;
};

class Son : public Father
{
public:
    /**
     * Son 重写 Father 中的 func1。
     *
     * 因为 func1 是虚函数，
     * 所以 Son 的虚函数表中，
     * func1 对应的位置会保存 Son::func1() 的地址。
     */
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }

    /**
     * Son 重写 Father 中的 func2。
     */
    virtual void func2() override
    {
        cout << "Son::func2()" << endl;
    }

    /**
     * Son 重写 Father 中的 func3。
     */
    virtual void func3() override
    {
        cout << "Son::func3()" << endl;
    }

    /**
     * Son 自己的数据成员。
     *
     * Son 对象中大致包含：
     * 1. 从 Father 继承来的 vfptr
     * 2. Father::m_f
     * 3. Son::m_s
     */
    long m_s = 2;
};

void test1()
{
    /**
     * 验证 Father 对象的内存结构。
     */
    // 验证Father对象
    Father father;

    /**
     * 将 Father 对象的地址强制转换为 long *。
     *
     * 这样就可以把 father 对象的内存
     * 按照 long 类型数组的方式进行访问。
     *
     * 假设在当前平台上：
     * 1. 指针占 8 字节
     * 2. long 占 8 字节
     *
     * 那么：
     * f[0] 表示对象中的第一个 long 大小的数据，
     *      通常就是 vfptr 的值，也就是虚函数表的地址。
     *
     * f[1] 表示对象中的第二个 long 大小的数据，
     *      通常就是 m_f 的值。
     */
    long * f = (long*)&father;

    /**
     * 输出 f[0]。
     *
     * f[0] 通常保存的是 vfptr 的值。
     * vfptr 指向 Father 类的虚函数表。
     *
     * 所以 f[0] 可以理解为：
     * Father 虚函数表的地址。
     */
    cout << f[0] << endl; // 虚函数指针指向的虚函数表的地址

    /**
     * 输出 f[1]。
     *
     * f[1] 对应 Father 对象中的普通数据成员 m_f。
     *
     * 因为 m_f 初始化为 1，
     * 所以这里通常输出 1。
     */
    cout << f[1] << endl; // m_f成员的值

    /**
     * f[0] 是虚函数表的地址。
     *
     * 将 f[0] 再强制转换为 long *，
     * 就可以把虚函数表也看成一个 long 类型数组。
     *
     * vftable_f[0] 通常保存 Father::func1() 的地址。
     * vftable_f[1] 通常保存 Father::func2() 的地址。
     * vftable_f[2] 通常保存 Father::func3() 的地址。
     */
    long * vftable_f = (long*)f[0];

    /**
     * 定义函数指针类型 F。
     *
     * typedef void(*F)();
     *
     * 表示：
     * F 是一种函数指针类型，
     * 可以指向返回值为 void、参数列表为空的函数。
     *
     * 后面会把虚函数表中的函数地址
     * 强制转换成 F 类型，
     * 然后通过函数指针调用。
     */
    typedef void(*F)();

    /**
     * 取出 Father 虚函数表中的第一个函数地址。
     *
     * vftable_f[0] 通常对应 Father::func1()。
     *
     * 将其强制转换为函数指针 F，
     * 然后通过 f1() 调用。
     *
     * 输出：
     * Father::func1()
     */
    F f1 = (F)vftable_f[0];
    f1();

    /**
     * 取出 Father 虚函数表中的第二个函数地址。
     *
     * vftable_f[1] 通常对应 Father::func2()。
     *
     * 输出：
     * Father::func2()
     */
    F f2 = (F)vftable_f[1];
    f2();

    /**
     * 取出 Father 虚函数表中的第三个函数地址。
     *
     * vftable_f[2] 通常对应 Father::func3()。
     *
     * 输出：
     * Father::func3()
     */
    F f3 = (F)vftable_f[2];
    f3();

    cout << "---------" << endl;

    /**
     * 验证 Son 对象的内存结构。
     */
    // 验证Son对象
    Son son;

    /**
     * 将 Son 对象的地址强制转换为 long *。
     *
     * Son 继承 Father，
     * Father 中有虚函数，
     * 所以 Son 对象中也会有 vfptr。
     *
     * Son 对象大致结构：
     * s[0] -> vfptr，指向 Son 的虚函数表
     * s[1] -> Father::m_f
     * s[2] -> Son::m_s
     */
    long * s = (long*)&son;

    /**
     * 输出 s[0]。
     *
     * s[0] 通常保存 Son 对象中的 vfptr。
     *
     * 因为 son 是 Son 类型对象，
     * 所以这个 vfptr 通常指向 Son 类的虚函数表。
     */
    cout << s[0] << endl; // 虚函数指针指向的虚函数表的地址

    /**
     * 输出 s[1]。
     *
     * s[1] 通常对应从 Father 继承来的成员 m_f。
     *
     * Father::m_f 初始化为 1，
     * 所以这里通常输出 1。
     */
    cout << s[1] << endl; // m_f成员的值

    /**
     * 输出 s[2]。
     *
     * s[2] 通常对应 Son 自己的成员 m_s。
     *
     * Son::m_s 初始化为 2，
     * 所以这里通常输出 2。
     */
    cout << s[2] << endl; // m_s成员的值

    /**
     * s[0] 是 Son 对象中的 vfptr。
     *
     * 它指向 Son 类对应的虚函数表。
     *
     * 因为 Son 重写了 Father 中的 func1、func2、func3，
     * 所以 Son 虚函数表中对应位置保存的是：
     * Son::func1()
     * Son::func2()
     * Son::func3()
     */
    long * vftable_s = (long*)s[0];

    /**
     * 定义函数指针类型 S。
     *
     * 这里和前面的 F 本质上一样：
     * 都是指向返回值为 void、参数列表为空的函数。
     */
    typedef void(*S)();

    /**
     * 取出 Son 虚函数表中的第一个函数地址。
     *
     * vftable_s[0] 通常对应 Son::func1()。
     *
     * 输出：
     * Son::func1()
     */
    S s1 = (S)vftable_s[0];
    s1();

    /**
     * 取出 Son 虚函数表中的第二个函数地址。
     *
     * vftable_s[1] 通常对应 Son::func2()。
     *
     * 输出：
     * Son::func2()
     */
    S s2 = (S)vftable_s[1];
    s2();

    /**
     * 取出 Son 虚函数表中的第三个函数地址。
     *
     * vftable_s[2] 通常对应 Son::func3()。
     *
     * 输出：
     * Son::func3()
     */
    S s3 = (S)vftable_s[2];
    s3();

}

int main(int argc, char *argv[])
{
    /**
     * test1 演示：
     *
     * 1. Father 对象中的 vfptr
     * 2. Father 虚函数表中的函数地址
     * 3. Son 对象中的 vfptr
     * 4. Son 虚函数表中的函数地址
     * 5. 子类重写虚函数后，虚函数表中对应位置会变成子类函数地址
     */
    test1();

    return 0;
}