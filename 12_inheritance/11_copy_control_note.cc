#include <iostream>

using std::cout;
using std::endl;

/**
 * 子类对象的复制控制操作：
 *
 * 1. 拷贝构造函数
 *
 *    使用一个已有对象创建新对象时调用。
 *
 *    例如：
 *    Son s2 = s1;
 *
 *
 * 2. 赋值运算符函数
 *
 *    两个已经存在的对象之间赋值时调用。
 *
 *    例如：
 *    s2 = s1;
 *
 *
 * 对于子类对象来说：
 *
 * 无论是拷贝构造还是赋值，
 * 都需要同时处理两个部分：
 *
 * 1. 从父类继承来的父类部分
 * 2. 子类自己定义的成员部分
 *
 *
 * 默认拷贝构造函数：
 *
 * 如果子类中没有显式定义拷贝构造函数，
 * 编译器会自动生成默认拷贝构造函数。
 *
 * 默认拷贝构造函数会自动完成：
 *
 * 1. 调用父类的拷贝构造函数，拷贝父类部分
 * 2. 拷贝子类自己定义的成员
 *
 *
 * 自定义拷贝构造函数：
 *
 * 如果在子类中显式定义了拷贝构造函数，
 * 那么需要在初始化列表中显式调用父类的拷贝构造函数。
 *
 * 否则父类部分不会按照拷贝构造的方式初始化，
 * 而是会尝试调用父类的无参构造函数。
 *
 * 如果父类没有无参构造函数，
 * 就会编译报错。
 *
 *
 * 默认赋值运算符函数：
 *
 * 如果子类中没有显式定义赋值运算符函数，
 * 编译器会自动生成默认赋值运算符函数。
 *
 * 默认赋值运算符函数会自动完成：
 *
 * 1. 调用父类的赋值运算符函数，给父类部分赋值
 * 2. 给子类自己定义的成员赋值
 *
 *
 * 自定义赋值运算符函数：
 *
 * 如果在子类中显式定义了赋值运算符函数，
 * 那么需要在函数体中显式调用父类的赋值运算符函数。
 *
 * 否则父类部分不会按照预期完成赋值。
 */

class Father
{
public:
    // 父类有参构造函数
    Father(int f)
    : m_f(f)
    {
        /**
         * 使用初始化列表，
         * 用参数 f 初始化父类成员 m_f。
         */
    }

    // 父类拷贝构造函数
    Father(const Father &rhs)
    : m_f(rhs.m_f)
    {
        /**
         * 使用已有的 Father 对象，
         * 创建新的 Father 对象时调用。
         *
         * rhs 是被拷贝的对象。
         *
         * 当前对象的 m_f，
         * 使用 rhs.m_f 进行初始化。
         */

        cout << "Father copy constructor called" << endl;
    }

    // 父类赋值运算符函数
    Father &operator=(const Father &rhs)
    {
        /**
         * 两个已经存在的 Father 对象之间赋值时调用。
         *
         * 例如：
         * f2 = f1;
         *
         * this 指向等号左边的对象。
         * rhs 表示等号右边的对象。
         */

        cout << "Father operator= called" << endl;

        // 防止自赋值
        //
        // 例如：
        // f1 = f1;
        //
        // 如果左右两边是同一个对象，
        // 就不需要再执行赋值操作。
        if (this != &rhs) {
            this->m_f = rhs.m_f;
        }

        // 返回当前对象本身
        // 支持连续赋值
        //
        // 例如：
        // f3 = f2 = f1;
        return *this;
    }

    // 父类中的成员变量
    int m_f;
};

class Son : public Father
{
public:
    // 子类有参构造函数
    Son(int f, int s)
    : Father(f) // 先调用父类有参构造函数，初始化父类部分
    , m_s(s)    // 再初始化子类自己的成员
    {
        /**
         * 创建 Son 对象时，
         * 对象中包含两个部分：
         *
         * 1. 从 Father 继承来的父类部分 m_f
         * 2. Son 自己定义的成员 m_s
         */
    }

    // 子类拷贝构造函数
    Son(const Son &rhs)
    /*
     * 显式调用父类的拷贝构造函数。
     *
     * 作用：
     * 使用 rhs 中的父类部分，
     * 初始化当前对象中的父类部分。
     *
     *
     * rhs 是 Son 对象，
     * 但是 Son public 继承 Father，
     * 满足 Son is a Father。
     *
     * 所以 rhs 可以作为 Father 引用，
     * 传给 Father 的拷贝构造函数。
     *
     * 这属于向上转型。
     */
    : Father(rhs)
    , m_s(rhs.m_s)
    {
        /**
         * 子类自定义拷贝构造函数。
         *
         * 拷贝 Son 对象时，
         * 需要完成两个部分：
         *
         * 1. 父类 Father 部分
         *    通过 Father(rhs) 完成。
         *
         * 2. 子类 Son 自己的成员
         *    通过 m_s(rhs.m_s) 完成。
         */

        cout << "Son copy constructor called" << endl;
    }

    // 子类赋值运算符函数
    Son &operator=(const Son &rhs)
    {
        /**
         * 两个已经存在的 Son 对象之间赋值时调用。
         *
         * 例如：
         * s2 = s1;
         *
         * this 指向等号左边的对象 s2。
         * rhs 表示等号右边的对象 s1。
         */

        cout << "Son operator= called" << endl;

        // 防止自赋值
        if (this != &rhs) {
            /*
             * 显式调用父类的赋值运算符函数。
             *
             * 作用：
             * 完成当前 Son 对象中父类部分的赋值。
             *
             *
             * rhs 是 Son 对象，
             * 但是 Son public 继承 Father，
             * 所以 rhs 可以作为 Father 引用传入。
             *
             * 这同样属于向上转型。
             */

            Father::operator=(rhs);

            // 再完成子类自己成员的赋值
            this->m_s = rhs.m_s;
        }

        // 返回当前对象本身
        // 支持连续赋值
        return *this;
    }

    // 子类自己定义的成员变量
    int m_s;
};

void test1()
{
    // 创建 Son 对象 s1
    Son s1{1, 2};

    // 输出父类部分的数据
    cout << s1.m_f << endl;

    // 输出子类自己成员的数据
    cout << s1.m_s << endl;

    cout << "-----" << endl;

    /**
     * 使用已有对象 s1 创建新对象 s2。
     *
     * 这里会调用 Son 的拷贝构造函数。
     *
     * 因为 Son 中手动定义了拷贝构造函数，
     * 所以会执行：
     *
     * Son(const Son &rhs)
     *
     *
     * 在 Son 的拷贝构造函数中：
     *
     * 1. Father(rhs)
     *    调用父类拷贝构造函数，
     *    拷贝父类部分 m_f。
     *
     * 2. m_s(rhs.m_s)
     *    拷贝子类自己的成员 m_s。
     *
     *
     * 如果 Son 的拷贝构造函数中不写 Father(rhs)，
     * 编译器会尝试调用 Father 的无参构造函数。
     *
     * 但是本例中 Father 没有无参构造函数，
     * 所以会编译失败。
     */

    Son s2 = s1;

    // 输出拷贝后 s2 中的父类成员
    cout << s2.m_f << endl;

    // 输出拷贝后 s2 中的子类成员
    cout << s2.m_s << endl;
}

void test2()
{
    // 创建两个已经存在的 Son 对象
    Son s1{1, 2};
    Son s2{3, 4};

    /**
     * s1 和 s2 都已经存在。
     *
     * 此时执行赋值操作：
     *
     * s2 = s1;
     *
     * 会调用 Son 的赋值运算符函数：
     *
     * Son &operator=(const Son &rhs)
     *
     *
     * 在 Son::operator= 中：
     *
     * 1. 先调用 Father::operator=(rhs)
     *    完成父类部分 m_f 的赋值。
     *
     * 2. 再执行 this->m_s = rhs.m_s
     *    完成子类自己成员 m_s 的赋值。
     */

    s2 = s1;

    // 输出赋值后 s2 中的父类成员
    cout << s2.m_f << endl;

    // 输出赋值后 s2 中的子类成员
    cout << s2.m_s << endl;
}

int main(int argc, char *argv[])
{
    /* test1(); */

    // 测试子类对象的赋值运算符函数
    test2();

    return 0;
}