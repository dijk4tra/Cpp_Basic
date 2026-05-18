#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

/**
 * 模板 template：
 * 可以理解成：
 * 把“类型”也当成参数来传递。
 *
 * 普通函数的参数通常是具体的数据：
 * int add(int a, int b)
 * 这里 a 和 b 是数据参数。
 *
 * 模板的参数可以是类型：
 * template <typename T>
 * 这里 T 是类型参数。
 *
 *
 * 模板编程：
 * 也叫泛型编程 generic programming。
 * 它强调代码的通用性。
 *
 * 例如：
 * int、double、string 都可以做加法或拼接，
 * 如果分别写多个 add 函数，会产生大量重复代码。
 *
 * 使用模板以后，
 * 可以只写一份代码，
 * 让编译器根据实际使用的类型生成对应的函数或类。
 *
 *
 * 模板的分类：
 * 1. 函数模板
 *    把模板作用在函数上。
 *    例如：
 *    template <typename T>
 *    T add(T a, T b);
 *
 * 2. 类模板
 *    把模板作用在类上。
 *    例如：
 *    template <typename T>
 *    class Box;
 *
 *
 * 模板的本质：
 * 模板本身不是一个真正的函数或类，
 * 它更像是一个代码生成器。
 *
 * 在编译时期，
 * 编译器会根据模板和具体类型，
 * 生成真正可以使用的代码。
 *
 * 函数模板生成出来的具体函数：
 * 叫模板函数。
 *
 * 类模板生成出来的具体类：
 * 叫模板类。
 *
 *
 * 实例化 instantiation：
 * 由模板生成具体代码的过程，
 * 叫做实例化。
 *
 * 例如：
 * add(1, 2);
 * 编译器会根据 int 类型，
 * 由函数模板生成：
 * int add(int, int);
 *
 *
 * 实例化的方式：
 * 1. 隐式实例化
 *    不明确写出模板参数，
 *    由编译器根据实参自动推导。
 *
 *    例如：
 *    add(1, 2);
 *    编译器看到 1 和 2 都是 int，
 *    就推导出 T 是 int。
 *
 * 2. 显式实例化 / 显式调用
 *    明确告诉编译器模板参数是什么。
 *
 *    例如：
 *    add<int>(1, 2);
 *    这里直接指定 T 是 int。
 */


/*
int add(int a, int b)
{
    return a + b;
}

double add(double a, double b)
{
    return a + b;
}

string add (string a, string b)
{
    return a + b;
}

void test1()
{
    add(1, 2);
    add(1.1, 2.2);
}
*/

/**
 * 上面被注释掉的代码：
 * 使用函数重载实现了多个 add 函数。
 *
 * 问题：
 * int、double、string 的 add 逻辑基本相同，
 * 都是返回 a + b。
 *
 * 如果每一种类型都单独写一个函数，
 * 会造成代码重复。
 *
 * 模板可以解决这个问题：
 * 把类型抽象出来，
 * 用一个类型参数 T 表示。
 */


// 把模板作用在函数上
// 定义模板的关键字：template
// typename 表示后面的 T 是一个类型参数
// T 是类型参数，也叫模板参数，可以是任意合法名字
template <typename T>
T add(T a, T b)
{
    cout << "使用了模板" << endl;

    /**
     * 这里的 a 和 b 的类型都是 T。
     *
     * 当 T 是 int 时：
     * return a + b;
     * 相当于两个 int 相加。
     *
     * 当 T 是 double 时：
     * 相当于两个 double 相加。
     *
     * 当 T 是 string 时：
     * string 类型重载了 operator+，
     * 所以这里表示字符串拼接。
     *
     * 注意：
     * 模板并不是对所有类型都一定可用。
     * 如果某个类型不支持 a + b，
     * 那么实例化 add<T> 时就会编译报错。
     */
    return a + b;
}
// 好处：代码简洁，可以重复使用

void test1()
{
    // 隐式实例化
    // 编译器根据实参 1 和 2 推导出 T 是 int
    // 因此会生成类似于：
    // int add(int, int)
    add(1, 2);     // add(int, int)

    // 编译器根据 1.1 和 2.2 推导出 T 是 double
    // 因此会生成类似于：
    // double add(double, double)
    add(1.1, 2.2); // add(double, double)

    string s1 = "abc";
    string s2 = "bcd";

    // 编译器根据 s1 和 s2 推导出 T 是 string
    // 因此会生成类似于：
    // string add(string, string)
    //
    // 对 string 来说，+ 表示字符串拼接
    cout << add(s1, s2) << endl; // add(string, string)
    
    // 显式实例化 / 显式指定模板参数
    // 这里明确告诉编译器：
    // T 是 int
    //
    // 所以即使不完全依赖编译器推导，
    // 也可以直接写出模板参数类型。
    add<int>(1, 2);
}


// 把模板作用于类上
// T 类型可以作为成员函数的参数、返回值和数据成员的类型等
template <typename T>
class Box
{
public:
    /**
     * 构造函数
     *
     * 参数：
     * T data
     *
     * 因为 T 是类型参数，
     * 所以 data 的具体类型取决于创建 Box 对象时指定的类型。
     *
     * 例如：
     * Box<int> box{100};
     * 此时 T 是 int，
     * 构造函数相当于：
     * Box(int data);
     *
     * Box<double> box{1.1};
     * 此时 T 是 double，
     * 构造函数相当于：
     * Box(double data);
     */
    Box(T data)
    : m_data(data)
    {}

private:
    /**
     * m_data 的类型是 T。
     *
     * 也就是说：
     * Box<int> 中，m_data 是 int 类型；
     * Box<double> 中，m_data 是 double 类型；
     * Box<string> 中，m_data 是 string 类型。
     */
    T m_data;
};

// 类的前向声明
// 表示 Point 是一个类，后面可能会定义它
//
// 这里 vector<Point> 只是演示模板可以使用自定义类型。
// 在某些场景下，完整使用 Point 对象时，
// 还需要 Point 的完整定义。
class Point;

void test2()
{
    /**
     * 之前其实已经使用过模板。
     *
     * vector 本身就是类模板。
     * vector<int>、vector<string>、vector<Point>
     * 是由同一个 vector 类模板实例化出来的不同类型。
     */

    // vector<int>
    // 表示这个 vector 容器中存放 int 类型的数据
    vector<int> v1;

    // vector<string>
    // 表示这个 vector 容器中存放 string 类型的数据
    vector<string> v2;

    // vector<Point>
    // 表示这个 vector 容器中存放 Point 类型的数据
    vector<Point> v3;

    /**
     * map 也是类模板。
     *
     * map<K, V>
     * 通常表示：
     * key 的类型是 K，
     * value 的类型是 V。
     */

    // key 是 int，value 也是 int
    map<int, int> m1;

    // key 是 int，value 是 string
    map<int, string> m2;

    /**
     * 创建自定义类模板 Box 的对象。
     *
     * Box 是类模板，
     * 使用时需要确定 T 的具体类型。
     */

    // C++17 起支持类模板参数推导 CTAD：
    // Class Template Argument Deduction
    //
    // 根据构造函数参数 100，
    // 编译器可以推导出 T 是 int。
    //
    // 因此这里相当于：
    // Box<int> box{100};
    Box box{100};

    // 显式指定模板参数为 double
    // 因此这里创建的是 Box<double> 类型的对象
    Box<double> box2{1.1};
}


int main(int argc, char *argv[])
{
    // 测试函数模板 add
    test1();

    // 当前没有调用 test2
    // 如果想测试类模板 Box、vector、map 的使用，
    // 可以取消下面这一行注释。
    /* test2(); */

    return 0;
}