#include <iostream>

using std::cout;
using std::endl;

/**
 * 虚函数在继承中的调用规则：
 *
 * 1. 通过 Father::func() 这种类名作用域调用虚函数时，
 *    会抑制虚函数的动态绑定，直接调用 Father::func()。
 *
 * 2. 在成员函数中直接调用 func() 时，
 *    等价于 this->func()，会发生虚函数的动态绑定。
 *
 * 3. 当 Son 对象调用从 Father 继承来的成员函数时，
 *    该成员函数中的 this 指针的静态类型是 Father *。
 *
 *    但是 this 实际指向的是 Son 对象中的 Father 子对象部分。
 *
 *    如果该函数内部直接调用虚函数 func()，
 *    最终会根据对象的实际类型调用对应的虚函数版本。
 *
 *
 * 本文件重点：
 * 同样是在 Father 的成员函数中调用虚函数，
 * 调用方式不同，结果不同：
 *
 * Father::func();  // 指定调用 Father 版本，不发生多态
 * func();          // 等价于 this->func()，会发生动态绑定
 */

class Father 
{
public:
    /**
     * 在 Father 类中定义虚函数 func。
     *
     * 子类 Son 可以重写该虚函数。
     *
     * 注意：
     * 这里输出的是 "Father::func1()"，
     * 但函数名是 func。
     *
     * 从语义上看，
     * 可以写成：
     * cout << "Father::func()" << endl;
     *
     * 不过这不影响本例对虚函数调用规则的演示。
     */
    // 在Father类中定义虚函数
    virtual void func()
    {
        cout << "Father::func1()" << endl;
    }

    /**
     * fatherMethod1 本身也是虚函数。
     *
     * 但是 Son 中没有重写 fatherMethod1，
     * 所以不管是 Father 对象调用，
     * 还是 Son 对象调用，
     * 实际执行的都是 Father::fatherMethod1()。
     */
    virtual void fatherMethod1()
    {
        cout << "fatherMethod1()" << endl;

        /**
         * 通过类名作用域调用虚函数：
         * Father::func();
         *
         * 这种写法会明确指定调用 Father 类中的 func。
         *
         * 即使当前对象实际是 Son 对象，
         * 这里也不会调用 Son::func()。
         *
         * 原因：
         * 类名作用域调用会抑制虚函数的动态绑定。
         */
        // 通过类名作用域调用虚函数，会抑制动态绑定
        // 因此这里一定调用 Father::func()
        Father::func();
    }

    /**
     * fatherMethod2 本身也是虚函数。
     *
     * Son 中没有重写 fatherMethod2，
     * 所以 Son 对象调用 fatherMethod2 时，
     * 实际执行的也是 Father::fatherMethod2()。
     *
     * 但是该函数内部直接调用了 func()，
     * 由于 func 是虚函数，
     * 所以这里会发生动态绑定。
     */
    virtual void fatherMethod2()
    {
        /**
         * 打印 this 指针。
         *
         * 在 Father 的成员函数中，
         * this 的静态类型是 Father *。
         *
         * 如果是 father 对象调用：
         * this 指向 father 对象。
         *
         * 如果是 son 对象调用：
         * this 指向 son 对象中的 Father 子对象部分。
         *
         * 在单继承且 Father 是第一个基类的情况下，
         * Father 子对象通常位于 Son 对象的起始位置，
         * 所以 this 和 &son 的地址通常相同。
         */
        cout << this << endl;

        cout << "fatherMethod2()" << endl;

        /**
         * 直接调用虚函数：
         * func();
         *
         * 在成员函数内部，
         * func();
         *
         * 等价于：
         * this->func();
         *
         * 因为 func 是虚函数，
         * 所以会根据当前对象的实际类型进行动态绑定。
         *
         * 如果当前对象实际是 Father，
         * 调用 Father::func()。
         *
         * 如果当前对象实际是 Son，
         * 调用 Son::func()。
         */
        // 直接调用虚函数，等价于 this->func()
        // 会发生动态绑定
        func();

        // 通过son.调用该函数 所以this指针指向的是son对象
        // 当前对象是Son对象 
        // 这里体现的是一个特殊的多态, 运行的结果
        // 取决于具体对象的类型

        // 如果当前对象实际是 Father 对象，则调用 Father::func()
        // 如果当前对象实际是 Son 对象，则调用 Son::func()
    }
};

class Son : public Father
{
public:
    /**
     * Son 类重写 Father 类中的虚函数 func。
     *
     * 当通过 Father 类型调用虚函数 func 时，
     * 如果实际对象是 Son，
     * 就会动态绑定到 Son::func()。
     */
    // Son 类重写 Father 类中的虚函数 func()
    virtual void func() override
    {
        cout << "Son::func()" << endl;
    }

};

void test1()
{
    /**
     * 测试 Father 对象。
     *
     * father 的实际类型就是 Father。
     */
    // 测试Father对象
    Father father;

    /**
     * fatherMethod1 中使用的是：
     * Father::func();
     *
     * 类名作用域调用会抑制动态绑定，
     * 所以调用 Father::func()。
     */
    // fatherMethod1 中使用 Father::func()，调用 Father::func()
    father.fatherMethod1();

    /**
     * fatherMethod2 中使用的是：
     * func();
     *
     * 直接调用虚函数，
     * 等价于 this->func()。
     *
     * 当前对象实际类型是 Father，
     * 所以调用 Father::func()。
     */
    // fatherMethod2 中直接调用 func()，当前对象是 Father，调用 Father::func()
    father.fatherMethod2();

    cout << "---------" << endl;

    /**
     * 测试 Son 对象。
     *
     * Son 继承自 Father，
     * 所以 Son 对象可以调用从 Father 继承来的
     * fatherMethod1 和 fatherMethod2。
     */
    // 测试Son对象
    Son son;
    
    /**
     * fatherMethod1 是从 Father 继承来的成员函数。
     *
     * Son 中没有重写 fatherMethod1，
     * 所以这里执行的是 Father::fatherMethod1()。
     *
     * 但是 fatherMethod1 内部调用的是：
     * Father::func();
     *
     * 因为使用了类名作用域，
     * 所以一定调用 Father::func()，
     * 不会调用 Son::func()。
     */
    // fatherMethod1 和 fatherMethod2 都是从 Father 类继承来的成员函数
    // fatherMethod1 中使用 Father::func()，所以仍然调用 Father::func()
    son.fatherMethod1(); 

    /**
     * fatherMethod2 也是从 Father 继承来的成员函数。
     *
     * Son 中没有重写 fatherMethod2，
     * 所以这里执行的是 Father::fatherMethod2()。
     *
     * 但是 fatherMethod2 内部调用的是：
     * func();
     *
     * 等价于：
     * this->func();
     *
     * 因为 func 是虚函数，
     * 并且当前对象实际类型是 Son，
     * 所以最终调用 Son::func()。
     */
    // fatherMethod2 中直接调用 func()，当前对象实际类型是 Son，所以调用 Son::func()
    son.fatherMethod2(); 

    /**
     * 打印 Son 对象的地址。
     *
     * 在本例的单继承结构中，
     * Father 是 Son 的唯一基类，
     * Father 子对象通常位于 Son 对象的起始位置。
     *
     * 所以：
     * &son
     *
     * 和 fatherMethod2 中打印出来的 this 地址，
     * 通常是相同的。
     *
     * 如果是多继承，
     * 不同父类子对象在子类对象中的位置可能不同，
     * 那么转换成不同父类指针时，
     * 地址可能会发生偏移。
     */
    // &son 和 fatherMethod2 中打印的 this 地址通常相同
    // 因为 Father 是 Son 的第一个且唯一基类，Father 子对象通常位于 Son 对象起始位置
    cout << &son << endl;

}

int main(int argc, char *argv[])
{
    /**
     * test1 演示：
     * 1. Father 对象调用继承体系中的虚函数
     * 2. Son 对象调用从 Father 继承来的成员函数
     * 3. Father::func() 会抑制动态绑定
     * 4. func() 等价于 this->func()，会发生动态绑定
     */
    test1();

    return 0;
}