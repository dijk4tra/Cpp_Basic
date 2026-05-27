#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;


/**
 * std::bind
 *
 * std::bind 是 C++11 提供的函数适配器。
 *
 * 作用：
 * 包装一个可调用对象，生成一个新的可调用对象。
 *
 * 这个新的可调用对象可以：
 * 1. 固定原可调用对象的某些参数
 * 2. 保留原可调用对象的某些参数
 * 3. 调整原可调用对象的参数顺序
 * 4. 改变原可调用对象的调用形式
 *
 *
 * 可调用对象 callable object：
 * 可以像函数一样被调用的对象。
 *
 * 常见的可调用对象包括：
 * 1. 普通函数
 * 2. 函数指针
 * 3. 函数对象
 * 4. lambda 表达式
 * 5. 成员函数
 *
 *
 * 例如：
 * 原函数 add 的调用形式是：
 *
 * int add(int a, int b)
 *
 * 也就是：
 *
 * int(int, int)
 *
 *
 * 通过 bind 固定两个参数后：
 *
 * auto f = bind(add, 1, 2);
 *
 * f 的调用形式变成：
 *
 * int()
 *
 * 调用：
 *
 * f()
 *
 * 等价于：
 *
 * add(1, 2)
 *
 *
 * 通过 bind 固定一个参数，保留一个参数后：
 *
 * auto f = bind(add, placeholders::_1, 10);
 *
 * f 的调用形式变成：
 *
 * int(int)
 *
 * 调用：
 *
 * f(100)
 *
 * 等价于：
 *
 * add(100, 10)
 *
 *
 * 占位符 placeholders：
 *
 * std::placeholders::_1
 * 表示新函数对象调用时传入的第一个参数。
 *
 * std::placeholders::_2
 * 表示新函数对象调用时传入的第二个参数。
 *
 *
 * 注意：
 * std::bind 比 bind1st / bind2nd 更通用。
 *
 * bind1st / bind2nd 只能绑定二元函数对象的第一个或第二个参数；
 * std::bind 可以绑定普通函数、函数对象、lambda、成员函数等多种可调用对象。
 *
 * 但在实际开发中，
 * 很多场景下 lambda 表达式比 std::bind 更直观。
 */


/**
 * 普通函数
 *
 * add 是一个普通函数。
 *
 * 函数类型：
 *
 * int(int, int)
 *
 * 表示：
 * 需要两个 int 类型参数，
 * 返回一个 int 类型结果。
 */
int add(int a, int b)
{
    cout << "a:" << a << " b:" << b << endl;
    return a + b;
}


/**
 * test1
 *
 * bind 包装普通函数。
 *
 * 主要演示：
 * 1. 固定全部参数
 * 2. 使用占位符保留参数
 * 3. 调整参数顺序
 * 4. 固定部分参数
 */
void test1()
{
    // 直接调用普通函数
    // a = 1，b = 2
    add(1, 2);

    cout << "-----" << endl;

    /**
     * 固定全部参数
     *
     * add 原来的调用形式是：
     *
     * int(int, int)
     *
     * bind(add, 1, 2)
     *
     * 表示：
     * 把 add 的第一个参数固定为 1，
     * 把 add 的第二个参数固定为 2。
     *
     * 所以 bind 之后得到的新可调用对象 f1
     * 不再需要额外传参。
     *
     * 调用形式变成：
     *
     * int()
     *
     * f1() 等价于：
     *
     * add(1, 2)
     */
    auto f1 = bind(add, 1, 2);

    // 调用 f1
    f1();

    cout << "-------" << endl;

    /**
     * 使用占位符保留参数
     *
     * std::placeholders::_1
     * 表示新函数对象调用时传入的第一个参数。
     *
     * std::placeholders::_2
     * 表示新函数对象调用时传入的第二个参数。
     *
     * bind(add, _1, _2)
     *
     * 表示：
     * add 的第一个参数来自 f2 的第一个实参；
     * add 的第二个参数来自 f2 的第二个实参。
     *
     * 所以：
     *
     * f2(100, 200)
     *
     * 等价于：
     *
     * add(100, 200)
     */
    auto f2 = bind(add, std::placeholders::_1, std::placeholders::_2);

    f2(100, 200);

    cout << "-------" << endl;

    /**
     * 调整参数顺序
     *
     * bind(add, _2, _1)
     *
     * 表示：
     * add 的第一个参数来自 f3 的第二个实参；
     * add 的第二个参数来自 f3 的第一个实参。
     *
     * 所以：
     *
     * f3(300, 400)
     *
     * 等价于：
     *
     * add(400, 300)
     *
     * 参数顺序被调换了。
     */
    auto f3 = bind(add, std::placeholders::_2, std::placeholders::_1);

    f3(300, 400);

    cout << "-----" << endl;

    /**
     * 固定部分参数
     *
     * bind(add, _1, 10)
     *
     * 表示：
     * add 的第一个参数由调用 f4 时传入；
     * add 的第二个参数固定为 10。
     *
     * 原函数调用形式：
     *
     * int(int, int)
     *
     * bind 之后：
     *
     * int(int)
     *
     * 所以：
     *
     * f4(100)
     *
     * 等价于：
     *
     * add(100, 10)
     */
    auto f4 = bind(add, std::placeholders::_1, 10);

    f4(100);
}


/**
 * test2
 *
 * bind 包装普通函数指针。
 *
 * 普通函数名 add 可以自动转换成函数指针，
 * 所以在很多情况下：
 *
 * bind(add, ...)
 *
 * 和：
 *
 * bind(&add, ...)
 *
 * 效果类似。
 *
 * &add 表示取函数 add 的地址，
 * 得到的是一个函数指针。
 */
void test2()
{
    // 直接调用普通函数
    add(1, 2);

    cout << "-----" << endl;

    /**
     * 使用函数指针包装普通函数
     *
     * &add 表示 add 函数的地址。
     *
     * bind(&add, 1, 2)
     *
     * 表示：
     * 通过函数指针调用 add，
     * 并固定 a = 1，b = 2。
     *
     * 原调用形式：
     *
     * int(int, int)
     *
     * bind 后：
     *
     * int()
     */
    auto f1 = bind(&add, 1, 2);

    // 等价于 add(1, 2)
    f1();

    cout << "-------" << endl;

    /**
     * 保留两个参数
     *
     * f2(100, 200)
     *
     * 等价于：
     *
     * add(100, 200)
     */
    auto f2 = bind(&add, std::placeholders::_1, std::placeholders::_2);

    f2(100, 200);

    cout << "-------" << endl;

    /**
     * 调整参数顺序
     *
     * f3(300, 400)
     *
     * 等价于：
     *
     * add(400, 300)
     */
    auto f3 = bind(&add, std::placeholders::_2, std::placeholders::_1);

    f3(300, 400);

    cout << "-----" << endl;

    /**
     * 固定第二个参数
     *
     * f4(100)
     *
     * 等价于：
     *
     * add(100, 10)
     */
    auto f4 = bind(&add, std::placeholders::_1, 10);

    f4(100);
}


/**
 * 函数对象
 *
 * 函数对象 function object：
 * 重载了 operator() 的类对象。
 *
 * 一旦一个类重载了 operator()，
 * 这个类创建出来的对象就可以像函数一样使用。
 *
 * 例如：
 *
 * Callable callable;
 * callable(1, 2);
 *
 * 等价于：
 *
 * callable.operator()(1, 2);
 */
struct Callable
{
    /**
     * 重载函数调用运算符 operator()
     *
     * 使 Callable 对象可以像普通函数一样被调用。
     *
     * 调用形式：
     *
     * int(int, int)
     */
    int operator()(int a, int b)
    {
        cout << "a =" << a << " b =" << b << endl;
        return a + b;
    }
};


/**
 * test3
 *
 * bind 包装函数对象。
 *
 * 函数对象本质上也是可调用对象，
 * 所以也可以被 std::bind 包装。
 */
void test3()
{
    // 创建函数对象
    Callable callable;

    // 直接调用函数对象
    // 等价于 callable.operator()(1, 2)
    callable(1, 2);

    cout << "-----" << endl;

    /**
     * 固定函数对象的两个参数
     *
     * Callable() 创建了一个临时函数对象。
     *
     * bind(Callable(), 1, 2)
     *
     * 表示：
     * 调用 Callable 对象时，
     * 第一个参数固定为 1，
     * 第二个参数固定为 2。
     *
     * 原调用形式：
     *
     * int(int, int)
     *
     * bind 后：
     *
     * int()
     *
     * f1() 等价于：
     *
     * Callable()(1, 2)
     */
    auto f1 = bind(Callable(), 1, 2);

    f1();

    cout << "-------" << endl;

    /**
     * 使用占位符保留两个参数
     *
     * f2(100, 200)
     *
     * 等价于：
     *
     * Callable()(100, 200)
     */
    auto f2 = bind(Callable(), std::placeholders::_1, std::placeholders::_2);

    f2(100, 200);

    cout << "-------" << endl;

    /**
     * 固定第二个参数
     *
     * bind(Callable(), _1, 20)
     *
     * 表示：
     * Callable 的第一个参数由 f3 调用时传入；
     * Callable 的第二个参数固定为 20。
     *
     * f3(100)
     *
     * 等价于：
     *
     * Callable()(100, 20)
     */
    auto f3 = bind(Callable(), std::placeholders::_1, 20);

    f3(100);
}


/**
 * test4
 *
 * bind 包装 lambda 表达式。
 *
 * lambda 表达式本身也是可调用对象，
 * 因此也可以使用 std::bind 进行参数绑定。
 */
void test4()
{
    /**
     * 定义 lambda 后立即调用
     *
     * [](int a, int b)->void {
     *     ...
     * }(1, 2);
     *
     * 前半部分是 lambda 表达式定义，
     * 后面的 (1, 2) 表示立即调用这个 lambda。
     */
    [](int a, int b)->void {
        cout << "a:" << a << " b:" << b << endl;
    }(1, 2);

    cout << "-------" << endl;

    /**
     * 使用 auto 接收 lambda 表达式
     *
     * f0 保存这个 lambda 对象。
     *
     * f0 的调用形式是：
     *
     * void(int, int)
     */
    auto f0 = [](int a, int b)->void {
        cout << "a:" << a << " b:" << b << endl;
    };

    // 调用 lambda
    f0(1, 2);

    cout << "-------" << endl;

    /**
     * bind 包装 lambda，并固定全部参数
     *
     * 原 lambda 的调用形式是：
     *
     * void(int, int)
     *
     * bind 后：
     *
     * void()
     *
     * f1() 等价于：
     *
     * lambda(1, 2)
     */
    auto f1 = bind([](int a, int b)->void {
        cout << "a:" << a << " b:" << b << endl;
    }, 1, 2);

    f1();

    cout << "-----" << endl;

    /**
     * bind 包装 lambda，并固定部分参数
     *
     * bind(lambda, 1, _1)
     *
     * 表示：
     * lambda 的第一个参数 a 固定为 1；
     * lambda 的第二个参数 b 由 f2 调用时传入。
     *
     * 原调用形式：
     *
     * void(int, int)
     *
     * bind 后：
     *
     * void(int)
     *
     * f2(100) 等价于：
     *
     * lambda(1, 100)
     */
    auto f2 = bind([](int a, int b)->void {
        cout << "a:" << a << " b:" << b << endl;
    }, 1, std::placeholders::_1);

    f2(100);
}


/**
 * 成员函数
 *
 * 普通成员函数必须依赖对象调用。
 *
 * 例如：
 *
 * MyClass obj;
 * obj.add(1, 2);
 *
 * 成员函数 add 虽然表面上只写了两个参数：
 *
 * int add(int a, int b)
 *
 * 但是它必须通过某个 MyClass 对象才能调用。
 *
 * 所以 bind 包装成员函数时，
 * 除了要传入成员函数地址，
 * 还必须传入对象、对象指针或对象引用。
 */
class MyClass
{
public:
    /**
     * 普通成员函数
     *
     * 调用形式：
     *
     * obj.add(a, b)
     *
     * 返回 a + b。
     */
    int add(int a, int b)
    {
        cout << "a:" << a << " b:" << b << endl;
        return a + b;
    }
};


/**
 * test5
 *
 * bind 包装成员函数。
 *
 * 成员函数和普通函数不同：
 * 普通函数可以直接调用；
 * 成员函数必须通过对象调用。
 *
 * 因此 std::bind 绑定成员函数时，
 * 第一个参数写成员函数地址：
 *
 * &MyClass::add
 *
 * 第二个参数需要指定调用该成员函数的对象。
 */
void test5()
{
    // 创建对象
    MyClass obj;

    // 通过对象调用成员函数
    obj.add(1, 2);

    cout << "------" << endl;

    // 通过对象指针调用成员函数
    MyClass * p = &obj;
    p->add(1, 2);

    cout << "------" << endl;

    /**
     * bind 包装成员函数，并传入对象
     *
     * &MyClass::add
     * 表示成员函数 add 的地址。
     *
     * obj
     * 表示通过哪个对象来调用这个成员函数。
     *
     * bind(&MyClass::add, obj, 10, 20)
     *
     * 表示：
     * 调用 obj 的 add 成员函数，
     * 并固定 a = 10，b = 20。
     *
     * f1() 等价于：
     *
     * obj.add(10, 20)
     *
     *
     * 注意：
     * 这里传入的是 obj，
     * bind 内部通常会保存 obj 的副本。
     */
    auto f1 = bind(&MyClass::add, obj, 10, 20);

    f1();

    cout << "----" << endl;

    /**
     * bind 包装成员函数，并传入对象地址
     *
     * &obj
     * 表示通过 obj 的地址调用成员函数。
     *
     * bind(&MyClass::add, &obj, 10, 20)
     *
     * f2() 等价于：
     *
     * (&obj)->add(10, 20)
     *
     * 也等价于：
     *
     * obj.add(10, 20)
     */
    auto f2 = bind(&MyClass::add, &obj, 10, 20);

    f2();

    cout << "----" << endl;

    /**
     * bind 包装成员函数，并保留普通参数
     *
     * 对象地址 &obj 已经固定。
     *
     * std::placeholders::_1
     * 对应成员函数 add 的第一个普通参数 a。
     *
     * std::placeholders::_2
     * 对应成员函数 add 的第二个普通参数 b。
     *
     * bind 后的新调用形式是：
     *
     * int(int, int)
     *
     * f3(100, 200)
     *
     * 等价于：
     *
     * obj.add(100, 200)
     */
    auto f3 = bind(&MyClass::add, &obj,
                   std::placeholders::_1,
                   std::placeholders::_2);

    f3(100, 200);
}


/**
 * test6
 *
 * 函数引用。
 *
 * 引用不仅可以绑定普通变量，
 * 也可以绑定函数。
 *
 * 函数引用的作用：
 * 给已有函数起一个引用别名，
 * 通过这个引用也可以调用原函数。
 */
void test6()
{
    // 定义一个普通变量
    int num = 1;

    /**
     * 普通引用
     *
     * ref 是 num 的引用。
     *
     * ref 和 num 代表同一块内存。
     */
    int & ref = num;

    // 通过引用修改 num
    ref = 2;

    // 输出 ref，也就是输出 num 当前的值
    cout << ref << endl;

    cout << "--------" << endl;

    /**
     * 函数引用
     *
     * add 的函数类型是：
     *
     * int(int, int)
     *
     * 定义函数引用的语法：
     *
     * int (&refAdd)(int, int) = add;
     *
     * 含义：
     * refAdd 是 add 函数的引用。
     *
     *
     * 拆开理解：
     *
     * int
     * 表示函数返回值类型。
     *
     * (&refAdd)
     * 表示 refAdd 是一个引用。
     *
     * (int, int)
     * 表示这个函数需要两个 int 参数。
     *
     *
     * 注意：
     * 函数引用不是新的函数，
     * 它只是已有函数 add 的别名。
     */
    int (&refAdd)(int, int) = add;

    // 通过函数引用调用 add
    refAdd(1, 2);

    /**
     * 使用 auto& 自动推导函数引用类型
     *
     * auto & refAdd2 = add;
     *
     * refAdd2 也是 add 的函数引用。
     */
    auto & refAdd2 = add;

    // 通过函数引用调用 add
    refAdd2(1, 2);
}


int main(int argc, char const *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();

    // 当前只测试函数引用
    test6();

    return 0;
}