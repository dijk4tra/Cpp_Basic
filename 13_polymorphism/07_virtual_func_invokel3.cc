#include <iostream>

using std::cout;
using std::endl;

/**
 * 虚函数在继承中的调用规则：
 *
 * 1. 通过 Father::func() 这种“类名 + 作用域限定符”的方式调用虚函数时，
 *    会抑制虚函数的动态绑定，直接调用 Father::func()。
 *
 * 2. 在成员函数中直接调用 func() 时，
 *    等价于 this->func()。
 *    如果 func() 是虚函数，就会根据当前对象的实际类型进行动态绑定。
 *
 * 3. 当 Son 对象调用从 Father 继承来的成员函数时，
 *    该成员函数中的 this 指针类型是 Father*，
 *    但它指向的是 Son 对象中的 Father 子对象部分。
 *
 *    如果该成员函数内部直接调用虚函数 func()，
 *    最终会根据实际对象类型调用对应版本：
 *    - 实际对象是 Father，调用 Father::func()
 *    - 实际对象是 Son，调用 Son::func()
 */

class Father
{
public:
    // 在 Father 类中定义虚函数
    virtual void func()
    {
        cout << "Father::func()" << endl;
    }

    virtual void fatherMethod1()
    {
        cout << "fatherMethod1()" << endl;

        // 通过类名作用域调用虚函数，会抑制动态绑定
        // 因此这里一定调用 Father::func()
        Father::func();
    }

    virtual void fatherMethod2()
    {
        cout << this << endl;
        cout << "fatherMethod2()" << endl;

        // 直接调用虚函数，等价于 this->func()
        // 会发生动态绑定
        func();

        // 如果当前实际对象是 Father 对象，则调用 Father::func()
        // 如果当前实际对象是 Son 对象，则调用 Son::func()
    }
};

class Son : public Father
{
public:
    // Son 类重写 Father 类中的虚函数 func()
    virtual void func() override
    {
        cout << "Son::func()" << endl;
    }
};

void test1()
{
    // 测试 Father 对象
    Father father;

    // fatherMethod1 中使用 Father::func()
    // 所以调用 Father::func()
    father.fatherMethod1();

    // fatherMethod2 中直接调用 func()
    // 当前实际对象是 Father，所以调用 Father::func()
    father.fatherMethod2();

    cout << "---------" << endl;

    // 测试 Son 对象
    Son son;

    // fatherMethod1 是从 Father 类继承来的成员函数
    // 但它内部使用 Father::func()
    // 因此会抑制动态绑定，仍然调用 Father::func()
    son.fatherMethod1();

    // fatherMethod2 也是从 Father 类继承来的成员函数
    // 它内部直接调用 func()
    // 等价于 this->func()
    // 当前实际对象是 Son，所以调用 Son::func()
    son.fatherMethod2();

    // &son 和 fatherMethod2 中打印的 this 地址通常相同
    // 因为 Father 是 Son 的第一个且唯一基类，
    // Father 子对象通常位于 Son 对象的起始位置。
    //
    // 注意：
    // 这属于常见编译器实现现象，
    // 具体对象布局仍然与编译器实现有关。
    cout << &son << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}