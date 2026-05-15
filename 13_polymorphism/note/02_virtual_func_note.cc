#include <iostream>

using std::cout;
using std::endl;

/**
 * 虚函数 virtual function：
 * 使用 virtual 修饰类中的成员函数，
 * 这个成员函数就是虚函数。
 *
 *
 * 虚函数的作用：
 * 当父类指针或者父类引用接收子类对象时，
 * 如果通过父类指针或者引用调用虚函数，
 * 程序会在运行时根据实际指向的对象类型，
 * 调用对应子类中的函数版本。
 *
 * 这就是运行时多态。
 *
 *
 * 普通成员函数和虚函数的区别：
 * 1. 普通成员函数
 *    调用哪个函数版本，
 *    通常在编译阶段就确定。
 *
 * 2. 虚函数
 *    如果通过父类指针或引用调用，
 *    调用哪个函数版本，
 *    会在运行阶段根据实际对象类型确定。
 *
 *
 * 注意：
 * virtual 只需要在类中声明函数时写。
 * 如果虚函数在类外实现，
 * 类外实现时不能再写 virtual。
 */

class Father
{
public:
    /**
     * 使用 virtual 修饰 func1，
     * func1 就是虚函数。
     *
     * 子类如果定义了与父类虚函数
     * 函数名、参数列表、返回类型兼容的函数，
     * 就是在重写 override 父类的虚函数。
     */
    virtual // 虚函数
    void func1()
    {
       cout << "Father::func1()" << endl;
    }

    /**
     * func2 没有使用 virtual 修饰，
     * 所以它是普通成员函数，
     * 不是虚函数。
     *
     * 子类中即使写了同名同参数的 func2，
     * 也不是虚函数重写，
     * 而是名字隐藏 / 重定义。
     */
    void func2()
    {
        
    }

    /**
     * 声明虚函数。
     *
     * 这里只是声明，
     * 没有在类中给出函数体。
     *
     * 注意：
     * 这不是纯虚函数。
     * 纯虚函数的写法是：
     * virtual void func3() = 0;
     *
     * 当前写法只是普通虚函数的声明，
     * 后面还需要在类外给出具体实现。
     */
    virtual void func3();
};

// 类外给出虚函数具体实现
/**
 * 类外实现虚函数时，
 * 不要再加 virtual。
 *
 * virtual 关键字只写在类内的函数声明处。
 *
 * 错误写法：
 * virtual void Father::func3()
 * {
 * }
 *
 * 正确写法：
 * void Father::func3()
 * {
 * }
 */
/* virtual // 类外实现虚函数时不要再加virtual */
void Father::func3()
{

}

class Son : public Father
{
public:
    /**
     * 子类中重写父类的虚函数。
     *
     * 这里 Son::func1() 和 Father::func1()
     * 函数名相同、参数列表相同、返回类型兼容，
     * 并且父类中的 func1 是虚函数，
     * 所以这里构成函数重写 override。
     *
     *
     * override：
     * 用来标记当前函数是重写父类中的虚函数。
     *
     * 好处：
     * 如果函数名、参数列表、const 属性等写错，
     * 编译器会直接报错。
     *
     * 例如：
     * virtual void func1(int) override
     * {
     * }
     *
     * 如果父类中没有对应的虚函数，
     * 编译器会报错。
     *
     *
     * 在子类中：
     * virtual 可以省略。
     *
     * 因为父类中的 func1 已经是虚函数，
     * 子类中重写后的 func1 默认也是虚函数。
     *
     * 但是不建议省略，
     * 写上 virtual 和 override 可读性更好。
     */
    // 子类中重写虚函数
    // override: 用来标记子类中重写的父类的虚函数
    // 在子类中virtual和override都可以省略(不建议省略)
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }

    /**
     * 这里不是 override。
     *
     * 原因：
     * Father::func2() 不是虚函数，
     * 所以 Son::func2() 不能算作重写虚函数。
     *
     * 更准确地说：
     * 这里是名字隐藏 / 重定义。
     *
     * 注意：
     * override 只能用于标记虚函数重写。
     * 如果这里写成：
     *
     * void func2() override
     * {
     * }
     *
     * 编译器会报错。
     */
    // 这里是oversee
    void func2() // override只能标记虚函数
    {

    }

};


void test1()
{
    Son son;

    /**
     * son 是 Son 类型对象。
     *
     * 通过子类对象直接调用 func1()，
     * 会调用 Son 类中的 func1()。
     *
     * 输出：
     * Son::func1()
     *
     * 注意：
     * 这里虽然调用的是子类版本，
     * 但还不是多态。
     *
     * 多态强调的是：
     * 父类指针或者父类引用接收子类对象，
     * 再通过父类类型调用虚函数。
     */
    son.func1(); // 现象：oversee，体现的是子类的结果

    /**
     * 通过作用域限定符 Father::，
     * 可以指定调用父类中的 func1()。
     *
     * 输出：
     * Father::func1()
     *
     * 这种写法绕过了虚函数的动态绑定机制，
     * 明确告诉编译器：
     * 就调用 Father 作用域中的 func1()。
     */
    son.Father::func1(); // 父类的结果

    // 上方的代码不是多态
    // 因为没有使用父类指针或者父类引用接收子类对象

    /**
     * 下方的代码才是多态。
     *
     * Father * f = &son;
     *
     * f 的静态类型是 Father *，
     * 但是 f 实际指向的是 Son 对象。
     *
     * 通过父类指针 f 调用虚函数 func1() 时，
     * 程序会在运行时根据 f 实际指向的对象类型，
     * 调用 Son::func1()。
     */
    // 下方的代码才是多态
    Father * f = &son;
    f->func1();

    /**
     * 多态的条件：
     *
     * 1. 继承是前提条件
     *    Son 继承自 Father。
     *
     * 2. 父类中要定义虚函数
     *    Father 中的 func1() 使用 virtual 修饰。
     *
     * 3. 子类中要重写父类的虚函数
     *    Son 中重写了 Father::func1()。
     *
     * 4. 父类的指针或者引用接收子类对象
     *    Father * f = &son;
     *
     * 5. 通过父类型调用同名的虚函数
     *    f->func1();
     *
     *
     * 满足以上条件时，
     * 才能体现出运行时多态。
     */
}

int main(int argc, char *argv[])
{
    test1();

    return 0;
}