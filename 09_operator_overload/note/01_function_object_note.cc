#include <iostream>

using std::cout;
using std::endl;

/**
 * 可调用实体：
 *
 * 在 C++ 中，可以像函数一样被调用的东西，
 * 都可以称为可调用实体。
 *
 * 常见的可调用实体有：
 * 1. 普通函数
 * 2. 成员函数
 * 3. 函数指针
 * 4. 成员函数指针
 * 5. 函数对象
 * 6. lambda 表达式
 *
 * 函数对象：
 *
 * 如果一个类中重载了 operator() 函数调用运算符，
 * 那么这个类创建出来的对象，
 * 就可以像函数一样被调用。
 *
 * 这样的对象就叫做函数对象，
 * 也叫仿函数。
 *
 * 例如：
 * MyClass obj;
 * obj();
 *
 * 表面上看 obj 像函数一样被调用，
 * 本质上是调用：
 * obj.operator()();
 *
 * 函数对象的使用场景：
 *
 * 1. 配合算法库使用
 *    例如排序、查找、遍历等算法中，
 *    可以传入函数对象作为判断规则或者处理逻辑。
 *
 * 2. 函数对象本质上是对象
 *    所以它可以保存一些额外的数据成员。
 *
 * 这些数据成员的生命周期和对象一致，
 * 因此函数对象可以记录状态。
 */

class MyClass
{
public:
    /**
     * 重载 operator() 函数调用运算符。
     *
     * 注意：
     * operator() 是函数名的一部分，
     * 后面的 () 才是真正的参数列表。
     *
     * 这个版本没有参数，
     * 所以调用形式是：
     * obj();
     */
    void operator()()
    {
        cout << "operator()()" << endl;
    }

    /**
     * 对函数调用运算符进行重载。
     *
     * 这个版本接收一个 int 参数，
     * 所以调用形式是：
     * obj(100);
     *
     * 本质上等价于：
     * obj.operator()(100);
     */
    void operator()(int num)
    {
        cout << "operator()(int)" << endl;
        cout << "num=" << num << endl;
    }

    /**
     * 再次重载 operator()。
     *
     * 这个版本接收两个 int 参数，
     * 并返回它们的和。
     *
     * 调用形式是：
     * obj(1, 2);
     *
     * 本质上等价于：
     * obj.operator()(1, 2);
     */
    int operator()(int a, int b)
    {
        cout << "operator()(int,int)" << endl;
        return a + b;
    }
};

void test1()
{
    /**
     * 创建 MyClass 对象。
     *
     * obj 是一个对象，
     * 但是因为 MyClass 重载了 operator()，
     * 所以 obj 可以像函数一样调用。
     */
    MyClass obj;

    /**
     * 调用无参版本的 operator()。
     *
     * 表达式：
     * obj();
     *
     * 本质上等价于：
     * obj.operator()();
     */
    obj();

    // 本质
    /* obj.operator()(); */

    /**
     * 调用一个 int 参数版本的 operator()。
     *
     * 表达式：
     * obj(100);
     *
     * 本质上等价于：
     * obj.operator()(100);
     */
    obj(100);

    // 本质
    /* obj.operator()(100); */

    /**
     * 调用两个 int 参数版本的 operator()。
     *
     * 表达式：
     * obj(1, 2);
     *
     * 本质上等价于：
     * obj.operator()(1, 2);
     *
     * 该版本有返回值，
     * 所以可以用 sum 接收返回结果。
     */
    int sum = obj(1,2);
    cout << sum << endl;

    // 本质
    /* int sum = obj.operator()(1,2); */
}

void test2()
{
    /**
     * count 是 test2 函数内部的局部变量。
     *
     * 它的作用域只在 test2 函数内部，
     * 离开 test2 后就不能再访问。
     */
    int count = 0;
}

void test3()
{
    /**
     * 这里无法访问 test2 里面的局部变量 count。
     *
     * 因为局部变量的作用域只在定义它的函数内部。
     */
    /* cout << count << endl; */
}

/**
 * 统计 MyClass2 对象被调用了几次。
 *
 * 函数对象的优势之一：
 * 它本质上是对象，
 * 所以可以拥有自己的数据成员。
 *
 * 这里通过 count 记录 operator() 被调用的次数。
 */
class MyClass2
{
public:
    /**
     * 无参版本的 operator()。
     *
     * 每调用一次，
     * count 就加 1。
     */
    void operator()()
    {
        cout << "operator()()" << endl;
        count++;
    }

    /**
     * 一个 int 参数版本的 operator()。
     *
     * 虽然参数 num 这里没有使用，
     * 但是每调用一次，
     * count 仍然加 1。
     */
    void operator()(int num)
    {
        cout << "operator()(int)" << endl;
        count++;
    }

    /**
     * 记录当前对象被调用的次数。
     *
     * count 是对象的数据成员，
     * 它的生命周期和 obj 对象一致。
     *
     * 只要 obj 对象还存在，
     * count 的值就会一直保留。
     */
    int count = 0;
};

void test4()
{
    /**
     * 创建函数对象 obj。
     *
     * obj 内部有自己的 count 成员，
     * 用来记录 obj 被调用的次数。
     */
    MyClass2 obj;

    /**
     * 第一次调用 obj 的 operator()。
     *
     * count 从 0 变成 1。
     */
    obj();

    /**
     * 第二次调用 obj 的 operator()。
     *
     * count 从 1 变成 2。
     */
    obj();

    /**
     * 第三次调用 obj 的 operator()。
     *
     * 调用的是带 int 参数的版本。
     *
     * count 从 2 变成 3。
     */
    obj(100);

    /**
     * 输出 obj 被调用的次数。
     *
     * 结果为 3。
     */
    cout << obj.count << endl;
}

int main(int argc, char * argv[])
{
    /**
     * test1 测试 operator() 的不同重载形式。
     *
     * test4 测试函数对象可以保存状态。
     */
    /* test1(); */
    test4();

    return 0;
}