#include <iostream>

using std::cout;
using std::endl;

/**
 * 多继承下，子类对象的创建和销毁过程：
 *
 * 多继承：
 * 一个子类同时继承多个父类。
 *
 *
 * 子类对象的创建过程：
 *
 * 创建子类对象时，
 * 会先创建从父类继承来的部分，
 * 再创建子类自己定义的部分。
 *
 * 也就是说：
 * 调用构造函数时，先父后子。
 *
 *
 * 多个父类构造函数的调用顺序：
 *
 * 多继承时，
 * 多个父类构造函数的调用顺序，
 * 和继承时父类的声明顺序一致。
 *
 * 注意：
 * 构造顺序不是由初始化列表中的书写顺序决定的，
 * 而是由继承列表中的声明顺序决定的。
 *
 * 例如：
 * class Son
 * : public Father1
 * , public Father2
 *
 * 所以创建 Son 对象时，
 * 会先调用 Father1 的构造函数，
 * 再调用 Father2 的构造函数，
 * 最后调用 Son 的构造函数。
 *
 *
 * 子类对象的销毁过程：
 *
 * 对象销毁时会调用析构函数。
 * 析构函数的调用顺序和构造函数的调用顺序相反。
 *
 * 所以销毁 Son 对象时：
 * 1. 先调用 Son 的析构函数
 * 2. 再调用 Father2 的析构函数
 * 3. 最后调用 Father1 的析构函数
 */

class Father1
{
public:
    // Father1 的无参构造函数
    Father1()
    {
        cout << "Father1()" << endl;
    }

    // Father1 的析构函数
    //
    // 当 Father1 对象或者 Son 对象中继承自 Father1 的部分销毁时，
    // 会自动调用该析构函数。
    ~Father1()
    {
        cout << "~Father1()" << endl;
    }

    // Father1 中的成员变量
    double m_f1 = 1;
};

class Father2
{
public:
    // Father2 的无参构造函数
    Father2()
    {
        cout << "Father2()" << endl;
    }

    // Father2 的析构函数
    //
    // 当 Father2 对象或者 Son 对象中继承自 Father2 的部分销毁时，
    // 会自动调用该析构函数。
    ~Father2()
    {
        cout << "~Father2()" << endl;
    }

    // Father2 中的成员变量
    double m_f2 = 2;
};

// 多继承
class Son
: public Father1
, public Father2
{
public:
    // Son 的无参构造函数
    Son()
    {
        /**
         * 创建 Son 对象时，
         * 构造函数调用顺序为：
         *
         * 1. Father1()
         * 2. Father2()
         * 3. Son()
         *
         * 因为继承列表中 Father1 写在 Father2 前面。
         */

        cout << "Son()" << endl;
    }

    // Son 的析构函数
    ~Son()
    {
        /**
         * 销毁 Son 对象时，
         * 析构函数调用顺序与构造函数相反：
         *
         * 1. ~Son()
         * 2. ~Father2()
         * 3. ~Father1()
         */

        cout << "~Son()" << endl;
    }

    // Son 自己定义的成员变量
    double m_s = 3;
};

void test1()
{
    // 创建 Son 对象
    Son son;

    /**
     * 创建 son 对象时输出：
     *
     * Father1()
     * Father2()
     * Son()
     */

    // 访问子类自己定义的成员
    cout << son.m_s << endl;

    // 访问从 Father1 继承过来的 public 成员
    cout << son.m_f1 << endl;

    // 访问从 Father2 继承过来的 public 成员
    cout << son.m_f2 << endl;

    /**
     * 查看 Son 对象所占空间大小。
     *
     * Son 对象中包含三个 double 类型成员：
     *
     * 1. Father1 中的 m_f1
     * 2. Father2 中的 m_f2
     * 3. Son 自己的 m_s
     *
     * 一个 double 通常占 8B。
     *
     * 所以 Son 对象大小通常为：
     * 8 + 8 + 8 = 24B
     */

    cout << sizeof(son) << endl; // 24 = 8(父类1) + 8(父类2) + 8(子类)

    /**
     * test1 函数结束时，
     * 局部对象 son 会自动销毁。
     *
     * 此时输出：
     *
     * ~Son()
     * ~Father2()
     * ~Father1()
     */
}

int main(int argc, char *argv[])
{
    // 测试多继承下子类对象的创建和销毁过程
    test1();

    return 0;
}