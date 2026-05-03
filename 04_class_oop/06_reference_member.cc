#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

/*
 * 引用数据成员
 *
 * 在类中，成员变量不仅可以是普通变量、指针，
 * 也可以是引用。
 *
 * 例如：
 *
 * int & m_z;
 *
 * m_z 是一个引用数据成员。
 *
 *
 * 引用数据成员的特点：
 *
 * 1. 引用必须初始化
 *
 *    引用不是对象本身，
 *    它只是某个已经存在变量或对象的别名。
 *
 *    例如：
 *
 *    int num = 3;
 *    int & ref = num;
 *
 *    ref 必须在定义时绑定到 num。
 *
 *
 * 2. 引用一旦绑定，不能再改变绑定对象
 *
 *    int a = 1;
 *    int b = 2;
 *    int & ref = a;
 *
 *    ref = b;
 *
 *    这不是让 ref 改为引用 b，
 *    而是把 b 的值赋给 ref 所绑定的 a。
 *
 *
 * 3. 引用数据成员必须在构造函数初始化列表中初始化
 *
 *    因为构造函数体内部执行时，
 *    成员变量已经完成初始化了。
 *
 *    普通成员可以在构造函数体中赋值：
 *
 *    m_x = x;
 *
 *    但是引用成员不能先不绑定，
 *    然后再赋值绑定。
 *
 *    所以必须写成：
 *
 *    Point(int x, int y, int & z)
 *    : m_x(x),
 *      m_y(y),
 *      m_z(z)
 *    {
 *    }
 *
 *
 * 4. 引用所绑定的变量或对象，
 *    生命周期最好大于等于包含该引用成员的对象。
 *
 *    否则引用成员可能会变成“悬空引用”。
 *
 *    悬空引用：
 *    引用绑定的对象已经销毁了，
 *    但是引用还在使用它。
 *
 *    这会导致未定义行为。
 *
 *
 * 引用数据成员和指针数据成员的区别：
 *
 * 1. 引用必须初始化，指针可以先不初始化
 *
 *    int & ref;  // 错误，引用必须初始化
 *    int * p;    // 可以声明，但最好初始化为 nullptr
 *
 * 2. 引用不能重新绑定，指针可以改变指向
 *
 * 3. 引用使用时语法更自然，不需要解引用
 *
 *    ref
 *
 *    指针使用时通常需要：
 *
 *    *p
 *    p->成员
 *
 * 4. 指针可能为空，需要判断 nullptr
 *
 *    if(p) {
 *        ...
 *    }
 *
 *    引用正常情况下不应该为空。
 */

class Point
{
public:
    /*
     * 构造函数
     *
     * 参数：
     * x：用来初始化 m_x
     * y：用来初始化 m_y
     * z：是一个 int 类型引用
     *
     * 例如：
     *
     * int num = 3;
     * Point pt{1, 2, num};
     *
     * 此时：
     *
     * x = 1
     * y = 2
     * z 引用 num
     *
     *
     * 初始化列表：
     *
     * m_x(x)
     * 用 x 初始化 m_x。
     *
     * m_y(y)
     * 用 y 初始化 m_y。
     *
     * m_z(z)
     * 让引用成员 m_z 绑定到 z 所引用的对象。
     *
     * 在 test1 中，z 引用的是 num，
     * 所以 m_z 最终绑定的也是 num。
     *
     *
     * 可以理解为：
     *
     * int & z = num;
     * int & m_z = z;
     *
     * 最终 m_z 和 z 都是 num 的别名。
     */
    Point(int x, int y, int & z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
    , p(nullptr)
    {

    }

    void print()
    {
        /*
         * 打印 m_x、m_y、m_z。
         *
         * m_z 是引用成员，
         * 它本质上是外部某个 int 变量的别名。
         *
         * 在 test1 中：
         *
         * int num = 3;
         * Point pt{1, 2, num};
         *
         * 所以这里打印 m_z，
         * 实际上就是打印 num 的值。
         */
        cout << m_x << " " << m_y << " " << m_z << endl;

        /*
         * p 是指针成员。
         *
         * 指针和引用不同：
         *
         * 指针可能为空，
         * 所以使用指针前通常需要做非空判断。
         *
         * 例如：
         *
         * if(p) {
         *     // p 不是 nullptr，才可以安全使用 *p
         * }
         *
         * 当前代码中没有真正使用 p，
         * 这里只是说明指针使用前一般要判断。
         */
        // if(p) {
        //     // do something
        // }
    }

    int m_x;
    int m_y;

    // 引用数据成员
    //
    // m_z 必须在构造函数初始化列表中初始化。
    //
    // 它绑定到哪个变量，
    // 以后就一直作为那个变量的别名存在。
    int & m_z;

    // 指针数据成员
    //
    // 指针可以为空，
    // 所以建议初始化为 nullptr。
    int * p;
};

void test1()
{
    // 普通局部变量 num
    int num = 3;

    /*
     * 创建 Point 对象 pt。
     *
     * 第三个参数传入 num。
     *
     * 构造函数参数：
     *
     * Point(int x, int y, int & z)
     *
     * 其中 z 是 int 引用，
     * 所以 z 会绑定到 num。
     *
     * 成员 m_z 又在初始化列表中绑定到 z。
     *
     * 因此：
     *
     * pt.m_z 实际上就是 num 的别名。
     */
    Point pt{1, 2 ,num};

    // 输出：
    // 1 2 3
    pt.print();

    /*
     * 因为 pt.m_z 是 num 的别名，
     * 所以如果修改 num：
     *
     * num = 100;
     *
     * 那么 pt.m_z 看到的值也会变成 100。
     *
     * 如果修改 pt.m_z：
     *
     * pt.m_z = 200;
     *
     * 那么 num 的值也会变成 200。
     */
}


/*
 * 类的前向声明 forward declaration
 *
 * 这里先声明有一个类叫 Mather。
 *
 * 为什么要前向声明？
 *
 * 因为 Baby 类中要使用 Mather & m_mather;
 *
 * 在 Baby 类定义之前，
 * 编译器需要先知道 Mather 是一个类型。
 *
 * 但是此时不需要知道 Mather 类里面具体有哪些成员，
 * 因为引用成员 Mather & 只需要知道类型存在即可。
 *
 * 注意：
 * 如果 Baby 中直接包含：
 *
 * Mather m_mather;
 *
 * 那么只做前向声明是不够的，
 * 因为对象成员需要知道 Mather 的完整大小。
 *
 * 但是引用成员：
 *
 * Mather & m_mather;
 *
 * 本质上类似保存一个对象的引用，
 * 编译器不需要在这里知道 Mather 的完整定义。
 */
class Mather;

class Baby
{
public:
    /*
     * Baby 构造函数
     *
     * name：婴儿名字
     * m：母亲对象的引用
     *
     * m_mather 是引用成员，
     * 所以必须在初始化列表中初始化。
     */
    Baby(string name, Mather & m)
    : m_name(name)
    , m_mather(m)
    {}

    // 普通 string 成员
    //
    // string 是 C++ 标准库中的字符串类型。
    string m_name;

    /*
     * 引用数据成员
     *
     * m_mather 绑定到外部传入的 Mather 对象。
     *
     * 在 test2 中：
     *
     * Mather mather{"lili"};
     * Baby baby{"kongling", mather};
     *
     * baby.m_mather 绑定的就是 mather。
     *
     * 注意：
     * mather 的生命周期必须至少覆盖 baby 的使用期间。
     *
     * 如果 mather 先销毁，
     * baby.m_mather 就会成为悬空引用。
     */
    Mather & m_mather;
};

class Mather
{
public:
    // Mather 构造函数
    //
    // 使用传入的 name 初始化 m_name。
    Mather(string name)
    : m_name(name)
    {}

    // 母亲名字
    string m_name;
};

void test2()
{
    /*
     * 创建 Mather 对象。
     *
     * mather 是局部对象，
     * 生命周期到 test2 函数结束。
     */
    Mather mather{"lili"};

    /*
     * 创建 Baby 对象。
     *
     * baby.m_mather 绑定到 mather。
     *
     * 注意：
     * 在这个函数中，mather 先定义，baby 后定义。
     * 局部对象析构顺序和定义顺序相反。
     *
     * 所以 test2 结束时：
     *
     * 1. baby 先销毁
     * 2. mather 后销毁
     *
     * 这样 baby.m_mather 在 baby 生命周期内一直有效。
     */
    Baby baby{"kongling", mather};
}


/*
 * Printer 类
 *
 * 这个类演示引用成员绑定到输出流对象。
 *
 * ostream 是输出流类型。
 *
 * cout 的类型可以看作是 ostream 对象。
 *
 * 所以：
 *
 * ostream & m_os;
 *
 * 可以绑定 cout。
 *
 * 这样 Printer 对象内部就可以使用 m_os 输出内容。
 */
class Printer
{
public:
    /*
     * 构造函数
     *
     * 参数 os 是输出流引用。
     *
     * 例如：
     *
     * Printer printer{ cout };
     *
     * 此时：
     *
     * os 绑定 cout，
     * m_os 又绑定 os，
     * 所以 m_os 实际上就是 cout 的别名。
     */
    Printer(ostream & os)
    : m_os(os)
    {}

    void print()
    {
        /*
         * m_os 是 ostream 引用。
         *
         * 如果 m_os 绑定的是 cout，
         * 那么下面这句：
         *
         * m_os << "123";
         *
         * 就等价于：
         *
         * cout << "123";
         */
        m_os << "123";
    }

    /*
     * 输出流引用成员
     *
     * 引用成员必须在初始化列表中初始化。
     *
     * 使用引用的好处：
     * Printer 不拥有输出流对象，
     * 只是借用外部传入的输出流。
     *
     * 这样既可以绑定 cout，
     * 也可以绑定文件输出流等其他 ostream 对象。
     */
    ostream & m_os;
};

void test3()
{
    /*
     * 创建 Printer 对象。
     *
     * 将 cout 传给构造函数。
     *
     * printer.m_os 最终绑定到 cout。
     */
    Printer printer{ cout };

    /*
     * 调用 print。
     *
     * 内部执行：
     *
     * m_os << "123";
     *
     * 因为 m_os 绑定 cout，
     * 所以等价于：
     *
     * cout << "123";
     */
    printer.print();
}

int main(int argc, char * argv[])
{
    // test1 演示 int 引用数据成员
    test1();

    // test2 演示对象引用成员
    /* test2(); */

    // test3 演示 ostream 引用成员绑定 cout
    /* test3(); */

    return 0;
}