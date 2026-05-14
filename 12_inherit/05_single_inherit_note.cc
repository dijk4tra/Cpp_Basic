#include <iostream>
#include <ostream>

using std::cout;
using std::endl;

/**
 * 单继承下的子类对象的创建和销毁过程：
 *
 * 当创建子类对象时，
 * 会先创建对象中继承自父类的那一部分，
 * 再创建子类自己定义的那一部分。
 *
 * 所以构造顺序是：
 * 1. 先调用父类构造函数
 * 2. 再调用子类构造函数
 *
 *
 * 当销毁子类对象时，
 * 顺序和构造顺序相反：
 * 1. 先调用子类析构函数
 * 2. 再调用父类析构函数
 *
 *
 * 子类对象的组成：
 *
 * 一个子类对象中包含两部分：
 * 1. 从父类继承下来的成员
 * 2. 子类自己定义的成员
 *
 * 例如：
 * Son public 继承 Father。
 *
 * Son 对象中既有 Father 中的 m_f，
 * 也有 Son 自己的 m_s。
 */

class Father
{
public:
    // 无参构造函数
    //
    // 如果子类构造函数没有显式调用父类的有参构造函数，
    // 编译器会默认调用父类的无参构造函数。
    //
    // 所以：
    // 如果父类没有无参构造函数，
    // 并且子类构造函数中也没有显式调用父类的有参构造函数，
    // 那么创建子类对象时会报错。
    Father()
    {
        cout << "Father()" << endl;
    }

    // 有参构造函数
    Father(int f)
    : m_f(f)
    {
        /**
         * 父类的有参构造函数。
         *
         * 通过初始化列表，
         * 使用参数 f 初始化成员变量 m_f。
         */

        cout << "Father(int)" << endl;
    }

    // 父类中的成员变量
    int m_f = 1;
};

class Son : public Father
{
public:
    Son()
    /**
     * 子类的无参构造函数。
     *
     * 这里虽然没有写初始化列表，
     * 但是会有一个隐式的初始化过程。
     *
     * 编译器会默认调用父类的无参构造函数 Father()，
     * 先初始化从父类继承过来的那一部分成员。
     *
     * 等父类部分构造完成后，
     * 再执行子类构造函数体中的代码。
     */
    {
        cout << "Son()" << endl;
    }

    // 有参构造函数
    Son(int f, int s)
    : Father(f) // 显式调用父类的一个参数构造函数
    {
        /**
         * 子类的有参构造函数。
         *
         * : Father(f)
         *
         * 表示在创建 Son 对象时，
         * 不再默认调用父类的无参构造函数，
         * 而是显式调用父类的有参构造函数 Father(int)。
         *
         *
         * 注意：
         * 这里的参数 s 没有用来初始化 m_s。
         * 所以 m_s 仍然使用类内初始值 2。
         *
         * 如果想用 s 初始化 m_s，
         * 可以写成：
         *
         * Son(int f, int s)
         * : Father(f)
         * , m_s(s)
         * {
         *
         * }
         */

        cout << "Son(int, int)" << endl;
    }

    // 子类自己定义的成员变量
    int m_s = 2;
};

void test1()
{
    // 创建 Son 对象
    Son son;

    /**
     * 创建 son 对象时，
     * 会先调用父类 Father 的无参构造函数，
     * 再调用子类 Son 的无参构造函数。
     *
     * 输出结果：
     * Father()
     * Son()
     */

    // m_f 是从父类 Father 中继承过来的成员
    cout << son.m_f << endl;

    // m_s 是子类 Son 自己定义的成员
    cout << son.m_s << endl;

    // 查看 Son 对象所占空间大小
    cout << sizeof(son) << endl; // 大小为 8B

    /**
     * Son 对象中有两个 int 类型成员：
     *
     * 1. Father 中的 m_f
     * 2. Son 自己的 m_s
     *
     * 一个 int 通常占 4B，
     * 所以 Son 对象大小通常为 8B。
     *
     * 子类对象中有两个部分：
     * 一部分是继承得来的父类成员，
     * 另一部分是子类自己定义的成员。
     */
}

// 测试子类对象的创建过程
void test2()
{
    // 调用 Son 的无参构造函数
    Son son;

    /**
     * 创建 son 对象的过程：
     *
     * 1. 先调用 Father()
     * 2. 再调用 Son()
     *
     * 输出结果：
     * Father()
     * Son()
     */

    cout << "--------" << endl;

    // 调用 Son 的有参构造函数
    Son son2{1, 2};

    /**
     * 创建 son2 对象的过程：
     *
     * Son(int, int) 的初始化列表中写了 Father(f)，
     * 所以会先调用 Father(int)。
     *
     * 然后再执行 Son(int, int) 构造函数体。
     *
     * 输出结果：
     * Father(int)
     * Son(int, int)
     */
}

int main(int argc, char *argv[])
{
    /* test1(); */

    // 测试子类对象构造时，
    // 父类构造函数和子类构造函数的调用顺序
    test2();

    return 0;
}