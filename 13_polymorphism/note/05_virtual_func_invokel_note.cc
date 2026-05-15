#include <iostream>

using std::cout;
using std::endl;

/**
 * 虚函数的调用方式：
 *
 * 1. 通过对象直接调用虚函数
 *    例如：
 *    son.func();
 *
 *    这种调用不是多态。
 *
 *
 * 2. 通过父类指针或者父类引用调用虚函数
 *    例如：
 *    Father * p = &son;
 *    p->func();
 *
 *    这种调用才可能构成多态。
 *
 *
 * 多态强调的是：
 * 父类型指针或者父类型引用接收子类对象，
 * 再通过父类型调用被子类重写的虚函数。
 *
 *
 * 本文件重点：
 * 直接通过子类对象调用函数，
 * 即使这个函数是虚函数，
 * 也不属于运行时多态。
 */

class Father
{
public:
    /**
     * Father 中定义了虚函数 func。
     *
     * 子类如果定义了同名、同参数列表的 func，
     * 就可以重写这个虚函数。
     */
    virtual void func()
    {
        cout << "Father::func()" << endl;
    }
};

class Son : public Father
{
public:
    /**
     * 这里定义的是 func1，
     * 而父类中的虚函数是 func。
     *
     * 函数名不同，
     * 所以 Son::func1() 并不是对 Father::func() 的重写。
     *
     * Son 只是从 Father 中继承了 func()。
     */
    virtual void func1()
    {
        cout << "Son::func1()" << endl;
    }

};

void test1()
{
    // 创建子类对象
    Son son;

    /**
     * 通过子类对象直接调用 func()。
     *
     * Son 类中没有定义 func()，
     * 所以这里调用的是从 Father 中继承下来的 func()。
     *
     * 输出：
     * Father::func()
     *
     * 注意：
     * 这里不是多态。
     *
     * 原因：
     * 这里是通过子类对象 son 直接调用函数，
     * 没有使用父类指针或者父类引用接收子类对象。
     */
    // 创建子对象
    // 通过子对象直接调用虚函数
    Son son;
    son.func();

    /**
     * 如果子类中没有重写这个虚函数，
     * 那么直接通过子类对象调用时，
     * 调用的就是继承自父类的函数。
     *
     * 当前 Son 中没有重写 func，
     * 所以 son.func() 调用 Father::func()。
     */
    // 如果子类中没有这个虚函数,则这里只是继承的表现

    /**
     * 如果 Son 中写的是：
     *
     * virtual void func() override
     * {
     *     cout << "Son::func()" << endl;
     * }
     *
     * 那么：
     * son.func();
     *
     * 会调用 Son::func()。
     *
     * 但是这种通过对象直接调用的方式，
     * 仍然不叫多态。
     *
     * 多态必须通过父类指针或者父类引用来体现。
     */

    /**
     * 通过作用域限定符 Father::，
     * 明确指定调用 Father 类中的 func()。
     *
     * 即使子类中重写了 func()，
     * son.Father::func() 也会强制调用父类版本。
     *
     * 当前 Son 中没有重写 func()，
     * 所以这里和 son.func() 的输出结果一样。
     */
    // 子类中如果有虚函数----->隐藏的效果oversee
    son.Father::func();
}

int main(int argc, char *argv[])
{
    /**
     * test1 演示：
     * 1. 子类对象可以直接调用继承自父类的虚函数
     * 2. 通过对象直接调用虚函数不是多态
     * 3. 作用域限定符可以指定调用父类版本
     */
    test1();

    return 0;
}