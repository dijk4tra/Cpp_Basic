#include <iostream>

using std::cout;
using std::endl;

/**
 * 在构造函数、析构函数中调用虚函数：
 *
 * C++ 标准规定：
 * 在构造函数和析构函数中调用虚函数时，
 * 不会发生正常意义上的多态。
 *
 *
 * 构造函数中的虚函数调用：
 * 调用的是当前正在构造的类中的虚函数版本。
 *
 * 析构函数中的虚函数调用：
 * 调用的是当前正在析构的类中的虚函数版本。
 *
 *
 * 原因：
 * 1. 构造对象时，子类部分还没有完全构造好
 *    所以父类构造函数中不能调用子类版本的虚函数。
 *
 * 2. 析构对象时，子类部分已经先析构完成
 *    所以父类析构函数中也不能调用子类版本的虚函数。
 *
 *
 * 本例中：
 * 创建 Son 对象时，构造顺序是：
 * GrandFather -> Father -> Son
 *
 * 销毁 Son 对象时，析构顺序是：
 * Son -> Father -> GrandFather
 */

class GrandFather
{
public:
    /**
     * GrandFather 构造函数。
     *
     * 构造 Son 对象时，
     * 会先构造最上层的父类 GrandFather。
     */
    GrandFather()
    {
        cout << "GrandFather()" << endl;
    }

    /**
     * GrandFather 析构函数。
     *
     * 析构 Son 对象时，
     * GrandFather 是最后析构的部分。
     */
    ~GrandFather()
    {
        cout << "~GrandFather()" << endl;
    }

    /**
     * GrandFather 中定义虚函数 func1。
     *
     * Father 和 Son 中都可以重写这个虚函数。
     */
    virtual void func1()
    {
        cout << "GrandFather::func1()" << endl;
    }

    /**
     * GrandFather 中定义虚函数 func2。
     *
     * 后面会在析构函数中调用这个虚函数，
     * 用来观察析构过程中虚函数的调用规则。
     */
    virtual void func2()
    {
        cout << "GrandFather::func2()" << endl;
    }
    
};

class Father : public GrandFather
{
public:
    /**
     * Father 构造函数。
     *
     * 构造 Son 对象时，
     * 构造顺序是：
     * 1. GrandFather()
     * 2. Father()
     * 3. Son()
     *
     * 所以执行到 Father 构造函数时，
     * GrandFather 部分已经构造完成，
     * 但是 Son 部分还没有开始构造。
     */
    Father()
    {
        cout << "Father()" << endl;

        /**
         * 在构造函数中调用虚函数。
         *
         * 虽然 func1 是虚函数，
         * 并且 Son 中也重写了 func1，
         * 但是这里不会调用 Son::func1()。
         *
         * 因为当前正在执行 Father 的构造函数，
         * 所以这里调用的是 Father::func1()。
         *
         * 输出：
         * Father::func1()
         */
        func1();

        // C++标准中规定，在构造、析构函数中调用虚函数
        // 体现的是当前类的版本
    }

    /**
     * Father 析构函数。
     *
     * 析构 Son 对象时，
     * 析构顺序是：
     * 1. ~Son()
     * 2. ~Father()
     * 3. ~GrandFather()
     *
     * 执行到 Father 析构函数时，
     * Son 部分已经析构完成了。
     */
    ~Father()
    {
        cout << "~Father()" << endl;

        /**
         * 在析构函数中调用虚函数。
         *
         * 虽然 func2 是虚函数，
         * 并且 Son 中也重写了 func2，
         * 但是这里不会调用 Son::func2()。
         *
         * 因为当前正在执行 Father 的析构函数，
         * 所以这里调用的是 Father::func2()。
         *
         * 输出：
         * Father::func2()
         */
        func2();
    }

    /**
     * Father 重写 GrandFather 中的 func1。
     *
     * 如果通过 GrandFather 指针或引用指向 Father / Son 对象，
     * 并在普通成员函数中调用 func1，
     * 才可能体现多态。
     *
     * 但是在构造函数和析构函数中调用时，
     * 不会向下调用到 Son 版本。
     */
    // 在Father类中重写虚函数
    virtual void func1() override
    {
        cout << "Father::func1()" << endl;
    }

    /**
     * Father 重写 GrandFather 中的 func2。
     */
    virtual void func2() override
    {
        cout << "Father::func2()" << endl;
    }
};

class Son : public Father
{
public:
    /**
     * Son 构造函数。
     *
     * 执行到这里时，
     * GrandFather 和 Father 部分已经构造完成。
     */
    Son()
    {
        cout << "Son()" << endl;
    }

    /**
     * Son 析构函数。
     *
     * 析构 Son 对象时，
     * Son 自己的析构函数最先执行。
     */
    ~Son()
    {
        cout << "~Son()" << endl;
    }

    /**
     * Son 重写 Father 中的 func1。
     *
     * 但是 Father 构造函数中调用 func1() 时，
     * 不会调用到这里。
     */
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }

    /**
     * Son 重写 Father 中的 func2。
     *
     * 但是 Father 析构函数中调用 func2() 时，
     * 不会调用到这里。
     */
    virtual void func2() override
    {
        cout << "Son::func2()" << endl;
    }

};

void test1()
{
    /**
     * 创建 Son 对象。
     *
     * 构造过程：
     * 1. 调用 GrandFather()
     * 2. 调用 Father()
     *    - Father 构造函数中调用 func1()
     *    - 此时调用 Father::func1()
     * 3. 调用 Son()
     *
     *
     * son 离开作用域时自动销毁。
     *
     * 析构过程：
     * 1. 调用 ~Son()
     * 2. 调用 ~Father()
     *    - Father 析构函数中调用 func2()
     *    - 此时调用 Father::func2()
     * 3. 调用 ~GrandFather()
     *
     *
     * 所以大致输出顺序是：
     * GrandFather()
     * Father()
     * Father::func1()
     * Son()
     * ~Son()
     * ~Father()
     * Father::func2()
     * ~GrandFather()
     */
    Son son;
}

int main(int argc, char *argv[])
{
    /**
     * test1 演示：
     * 1. 构造函数的调用顺序
     * 2. 析构函数的调用顺序
     * 3. 构造 / 析构函数中调用虚函数时，不体现子类版本
     */
    test1();

    return 0;
}