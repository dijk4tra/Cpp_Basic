#include <iostream>
#include <memory>

using namespace std;

/**
 * 智能指针和多态结合
 *
 * 1. 多态的基本形式
 *
 *    C++ 中实现运行时多态通常需要：
 *
 *    - 继承
 *    - 虚函数
 *    - 父类指针或父类引用指向子类对象
 *
 *    例如：
 *
 *    Father * f = new Son{};
 *    f->func();
 *
 *    虽然 f 的静态类型是 Father*，
 *    但是它实际指向的是 Son 对象。
 *
 *    如果 func 是虚函数，
 *    那么调用 f->func() 时，
 *    会根据实际对象类型调用 Son::func()。
 *
 *
 * 2. 智能指针与多态
 *
 *    智能指针本质上也是对指针的一层封装。
 *
 *    因此可以使用：
 *
 *    unique_ptr<Father> up { new Son{} };
 *
 *    表示：
 *    用父类类型的 unique_ptr 管理子类对象。
 *
 *    之后通过 up->func() 调用虚函数，
 *    仍然可以实现动态多态。
 *
 *
 * 3. 为什么更推荐智能指针？
 *
 *    如果使用裸指针：
 *
 *    Father * f = new Son{};
 *
 *    使用结束后需要手动：
 *
 *    delete f;
 *
 *    如果忘记 delete，
 *    就会造成内存泄漏。
 *
 *    使用 unique_ptr 后，
 *    当 up 离开作用域时，
 *    会自动释放它管理的资源。
 *
 *
 * 4. 注意父类析构函数
 *
 *    如果使用父类指针或父类智能指针管理子类对象，
 *    通常父类析构函数应该写成 virtual。
 *
 *    例如：
 *
 *    virtual ~Father() = default;
 *
 *    这样通过 Father* 删除 Son 对象时，
 *    才能保证先调用 Son 的析构函数，
 *    再调用 Father 的析构函数。
 *
 *    当前代码中 Son 没有额外资源，
 *    所以问题不明显。
 *
 *    但在实际开发中，
 *    多态基类一般都应该提供虚析构函数。
 */

class Father
{
public:
    /**
     * 纯虚函数
     *
     * virtual void func() = 0;
     *
     * 含义：
     * - func 是虚函数
     * - = 0 表示它是纯虚函数
     * - 包含纯虚函数的类是抽象类
     *
     * 抽象类不能直接创建对象。
     *
     * 例如：
     * Father f;       // error
     *
     * Father 的作用通常是作为接口或基类，
     * 让子类去实现具体行为。
     */
    virtual void func() = 0;

    /**
     * 多态基类通常应该提供虚析构函数。
     *
     * 原因：
     * 如果通过 Father* 或 unique_ptr<Father>
     * 删除实际类型为 Son 的对象，
     * 需要保证析构过程能够正确发生。
     *
     * 如果父类析构函数不是 virtual，
     * 通过父类指针删除子类对象可能导致未定义行为。
     *
     * 当前示例中没有显式写析构函数，
     * 为了教学完整性，实际开发中建议补上：
     *
     * virtual ~Father() = default;
     */
};

class Son : public Father
{
public:
    /**
     * 子类重写父类虚函数
     *
     * virtual void func() override
     *
     * override 表示：
     * 当前函数要重写父类中的虚函数。
     *
     * 使用 override 的好处：
     * 如果函数名、参数列表、const 属性等写错，
     * 编译器会直接报错。
     *
     * 所以实际开发中，
     * 重写虚函数时推荐加 override。
     */
    virtual void func() override
    {
        cout << "Son::func()" << endl;
    }
};

void test1()
{
    /**
     * 传统裸指针写法：
     *
     * Father * f = new Son{};
     * f->func();
     *
     * Father 是父类类型，
     * Son 是子类类型。
     *
     * 父类指针可以指向子类对象。
     *
     * 如果 func 是虚函数，
     * 那么 f->func() 会发生动态绑定，
     * 实际调用 Son::func()。
     *
     * 但是裸指针写法需要手动 delete，
     * 否则会造成内存泄漏。
     */
    // Father * f = new Son{};
    // f->func();

    /**
     * unique_ptr<Father> up { new Son{} };
     *
     * 使用父类类型的 unique_ptr
     * 管理子类对象。
     *
     * 模板参数 Father 表示：
     * 这个智能指针的静态类型是 unique_ptr<Father>。
     *
     * new Son{} 表示：
     * 实际创建的是 Son 类型对象。
     *
     * 这和 Father* 指向 Son 对象类似，
     * 只是这里资源由 unique_ptr 自动管理。
     */
    unique_ptr<Father> up { new Son{} };

    /**
     * 通过智能指针调用虚函数。
     *
     * up->func()
     *
     * unique_ptr 重载了 operator->，
     * 所以可以像裸指针一样通过 -> 调用成员函数。
     *
     * 因为 func 是虚函数，
     * 并且 up 实际管理的是 Son 对象，
     * 所以这里会调用 Son::func()。
     */
    up->func();

    /**
     * (*up).func()
     *
     * unique_ptr 也重载了 operator*。
     *
     * *up 得到它管理的 Father 对象引用。
     *
     * 虽然表达式类型表现为 Father，
     * 但是实际对象仍然是 Son。
     *
     * 因为 func 是虚函数，
     * 所以这里同样会动态绑定到 Son::func()。
     */
    (*up).func();

    /**
     * test1 结束时：
     *
     * up 是局部对象，会自动析构。
     *
     * unique_ptr 析构时会释放它管理的对象。
     *
     * 实际开发中要求 Father 拥有 virtual 析构函数，
     * 这样通过父类指针释放子类对象时才安全。
     */
}

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}