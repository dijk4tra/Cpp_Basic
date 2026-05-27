#include <iostream>
#include <functional>

using namespace std;


/**
 * std::function 与 std::bind
 *
 * 1. 函数指针
 *
 * 函数指针只能指向普通函数。
 *
 * 例如：
 *
 * int (*p)(int, int) = func;
 *
 * 这里 p 是函数指针，
 * 它只能保存普通函数 func 的地址。
 *
 *
 * 注意：
 * 函数指针不能接收 std::bind 的返回结果。
 *
 * 原因：
 * std::bind 返回的不是普通函数，
 * 而是一个函数对象。
 *
 * 函数对象和函数指针不是同一种类型，
 * 所以不能直接赋值。
 *
 *
 * 2. std::function
 *
 * std::function 是 C++11 提供的通用函数包装器。
 *
 * 作用：
 * 保存各种“可调用对象”。
 *
 * 可调用对象包括：
 * 1. 普通函数
 * 2. 函数指针
 * 3. 函数对象
 * 4. lambda 表达式
 * 5. 成员函数
 * 6. std::bind 的返回结果
 *
 *
 * 3. std::function 的写法
 *
 * std::function<返回值类型(参数类型列表)>
 *
 * 例如：
 *
 * std::function<int(int, int)> f;
 *
 * 表示 f 可以保存这样一种可调用对象：
 *
 * 返回值是 int，
 * 参数是两个 int。
 *
 *
 * 再例如：
 *
 * std::function<void(int)> f;
 *
 * 表示 f 可以保存这样一种可调用对象：
 *
 * 返回值是 void，
 * 参数是一个 int。
 *
 *
 * 4. std::bind
 *
 * std::bind 可以提前绑定可调用对象的部分参数，
 * 从而改变可调用对象的调用形式。
 *
 * 例如：
 *
 * int(int, int)  --->  int()
 *
 * 表示：
 * 原本需要两个 int 参数的函数，
 * 通过 bind 绑定两个参数后，
 * 变成不需要参数的可调用对象。
 *
 *
 * 再例如：
 *
 * int(int, int)  --->  int(int)
 *
 * 表示：
 * 原本需要两个 int 参数的函数，
 * 通过 bind 绑定一个参数后，
 * 变成只需要一个 int 参数的可调用对象。
 *
 *
 * 总结：
 *
 * 函数指针：
 * 只能保存普通函数地址。
 *
 * std::function：
 * 可以统一保存各种可调用对象。
 *
 * std::bind：
 * 用来生成新的可调用对象。
 */


/**
 * 普通函数 func
 *
 * 函数签名：
 *
 * int(int, int)
 *
 * 表示：
 * 接收两个 int 参数，
 * 返回一个 int 结果。
 */
int func(int a, int b)
{
    cout << "a:" << a << " b:" << b << endl;
    return a + b;
}


/**
 * test1
 *
 * 演示：
 * 函数指针能否接收 std::bind 的返回结果。
 *
 * 结论：
 * 函数指针可以接收普通函数地址，
 * 但是不能接收 std::bind 的返回结果。
 */
void test1()
{
    // 直接调用普通函数
    func(1, 2);

    cout << "-------" << endl;

    /**
     * 使用 using 定义函数指针类型
     *
     * using F = int(*)(int, int);
     *
     * 含义：
     * F 是一个函数指针类型。
     *
     * 这个函数指针可以指向：
     * 返回值为 int，
     * 参数为 int、int 的普通函数。
     */
    using F = int(*)(int, int);

    /**
     * 函数名可以隐式转换为函数指针。
     *
     * func 是普通函数名。
     *
     * F f = func;
     *
     * 表示：
     * f 指向 func 函数。
     */
    F f = func;

    // 通过函数指针调用 func
    f(1, 2);

    cout << "-------" << endl;

    /**
     * 显式取函数地址
     *
     * &func 表示取 func 函数的地址。
     *
     * 下面这种写法和：
     *
     * F f = func;
     *
     * 本质上是一样的。
     */
    int (*f1)(int, int) = &func;

    // 通过函数指针调用 func
    f1(3, 4);

    /**
     * 使用 auto 接收 bind 的返回结果
     *
     * bind(func, 10, 20)
     *
     * 表示：
     * 把 func 的两个参数提前绑定为 10 和 20。
     *
     * 原来的调用形式：
     *
     * int(int, int)
     *
     * bind 之后：
     *
     * int()
     *
     * 所以 f2 调用时不需要再传入参数。
     */
    auto f2 = bind(func, 10, 20);

    // 等价于 func(10, 20)
    f2();

    cout << "-------" << endl;

    /**
     * 错误示例：
     *
     * f1 = bind(func, 100, 200);
     *
     * 原因：
     * f1 是函数指针。
     *
     * 函数指针只能保存普通函数的地址。
     *
     * 但是 bind(func, 100, 200)
     * 返回的是一个函数对象，
     * 不是普通函数地址。
     *
     * 所以不能用函数指针接收 bind 的返回结果。
     *
     *
     * 如果想统一接收 bind 的返回结果，
     * 可以使用 std::function。
     */
    // f1 = bind(func, 100, 200);
}


/**
 * test2
 *
 * std::function 存储普通函数。
 *
 * 普通函数本身是一种可调用对象，
 * 所以可以被 std::function 保存。
 */
void test2()
{
    /**
     * func 的函数签名是：
     *
     * int(int, int)
     *
     * 所以可以使用：
     *
     * std::function<int(int, int)>
     *
     * 来保存 func。
     *
     * 注意：
     * std::function 中写的返回值类型和参数列表，
     * 要和实际保存的可调用对象匹配。
     */
    std::function<int(int, int)> f3 = func;

    // 等价于 func(1, 2)
    f3(1, 2);

    cout << "----------" << endl;

    /**
     * std::function 存储 bind 的返回结果
     *
     * bind(func, 1, 2)
     *
     * 表示：
     * 把 func 的两个参数都提前绑定好。
     *
     * 原调用形式：
     *
     * int(int, int)
     *
     * bind 后：
     *
     * int()
     *
     * 所以应该使用：
     *
     * std::function<int()>
     *
     * 来接收 bind 的返回结果。
     */
    std::function<int()> f4 = bind(func, 1, 2);

    // 等价于 func(1, 2)
    f4();
}


/**
 * test3
 *
 * std::function 存储函数指针。
 *
 * 函数指针也是一种可调用对象，
 * 因此也可以交给 std::function 保存。
 */
void test3()
{
    /**
     * &func 表示 func 的函数地址。
     *
     * func 的函数签名是：
     *
     * int(int, int)
     *
     * 所以可以使用：
     *
     * std::function<int(int, int)>
     *
     * 来接收函数指针。
     */
    std::function<int(int, int)> f3 = &func;

    // 等价于 func(1, 2)
    f3(1, 2);

    cout << "----------" << endl;

    /**
     * bind 也可以绑定函数地址
     *
     * bind(&func, 1, 2)
     *
     * 表示：
     * 通过函数地址调用 func，
     * 并且把两个参数提前绑定为 1 和 2。
     *
     * 原调用形式：
     *
     * int(int, int)
     *
     * bind 后：
     *
     * int()
     */
    std::function<int()> f4 = bind(&func, 1, 2);

    // 等价于 func(1, 2)
    f4();
}


/**
 * 函数对象
 *
 * 只要一个类重载了 operator()，
 * 这个类创建出来的对象就可以像函数一样调用。
 *
 * 这种对象称为函数对象。
 */
struct Callable
{
    /**
     * 重载函数调用运算符 operator()
     *
     * 使 Callable 对象可以像函数一样被调用。
     *
     * 调用形式：
     *
     * int(int, int)
     */
    int operator()(int a, int b)
    {
        cout << "a:" << a << " b:" << b << endl;
        return a + b;
    }
};


/**
 * test4
 *
 * std::function 存储函数对象。
 *
 * 函数对象也是可调用对象，
 * 因此可以使用 std::function 保存。
 */
void test4()
{
    /**
     * Callable() 创建一个临时函数对象。
     *
     * Callable::operator() 的调用形式是：
     *
     * int(int, int)
     *
     *
     * 这里使用：
     *
     * function<void(int, int)>
     *
     * 来接收 Callable()。
     *
     * 虽然 Callable::operator() 的返回值是 int，
     * 但是 function<void(int, int)> 只关心调用参数，
     * 会忽略返回值。
     *
     * 也就是说：
     * f1(1, 2) 会调用 Callable()(1, 2)，
     * 只是返回的 int 结果没有被接收。
     */
    function<void(int, int)> f1 = Callable();

    // 等价于 Callable()(1, 2)
    f1(1, 2);

    /**
     * std::function 存储 bind 包装后的函数对象
     *
     * bind(Callable(), 1, _1)
     *
     * 表示：
     * 调用 Callable 对象时，
     * 第一个参数固定为 1，
     * 第二个参数由调用 f2 时传入。
     *
     * 原调用形式：
     *
     * int(int, int)
     *
     * bind 后：
     *
     * int(int)
     *
     * 这里同样使用 function<void(int)> 接收，
     * 表示忽略返回值，只关心一个 int 参数。
     */
    function<void(int)> f2 = bind(Callable(), 1, std::placeholders::_1);

    // 等价于 Callable()(1, 100)
    f2(100);
}


/**
 * test5
 *
 * std::function 存储 lambda 表达式。
 *
 * lambda 表达式本质上也是函数对象，
 * 所以也可以被 std::function 保存。
 */
void test5()
{
    /**
     * lambda 的调用形式是：
     *
     * void(int)
     *
     * 所以可以使用：
     *
     * function<void(int)>
     *
     * 来保存它。
     */
    function<void(int)> f1 = [](int num)->void {
        cout << "Hello, Lambda!" << endl;
        cout << num << endl;
    };

    // 调用 lambda
    f1(100);

    /**
     * std::function 存储 bind 包装后的 lambda
     *
     * 原 lambda 的调用形式：
     *
     * void(int)
     *
     * bind(lambda, 200)
     *
     * 表示：
     * 把 lambda 的参数固定为 200。
     *
     * bind 后的新调用形式：
     *
     * void()
     *
     * 所以使用：
     *
     * function<void()>
     *
     * 来接收。
     */
    function<void()> f2 = bind([](int num)->void {
        cout << "Hello, Lambda!" << endl;
        cout << num << endl;
    }, 200);

    // 等价于 lambda(200)
    f2();
}


/**
 * 成员函数
 *
 * 成员函数必须依赖对象调用。
 *
 * 例如：
 *
 * MyClass obj;
 * obj.func(1, 2);
 *
 * 或者：
 *
 * MyClass * p = &obj;
 * p->func(1, 2);
 *
 *
 * 成员函数指针和普通函数指针不同。
 *
 * 对于成员函数：
 *
 * void MyClass::func(int, int)
 *
 * 如果使用 std::function 保存它，
 * 需要额外把“对象”作为第一个参数。
 *
 *
 * 也就是说：
 *
 * &MyClass::func
 *
 * 可以被看成类似下面的调用形式：
 *
 * void(MyClass&, int, int)
 *
 * 或：
 *
 * void(MyClass*, int, int)
 *
 * 第一个参数用来说明：
 * 到底调用哪个对象的成员函数。
 */
class MyClass
{
public:
    /**
     * 普通成员函数
     *
     * 成员函数调用时，
     * 必须依赖某个具体对象。
     */
    void func(int a, int b)
    {
        cout << "a = " << a << " b = " << b << endl;
    }
};


/**
 * test6
 *
 * std::function 存储成员函数。
 *
 * 成员函数与普通函数最大的区别：
 * 成员函数需要对象才能调用。
 *
 * 所以 std::function 保存成员函数时，
 * 通常需要把对象引用或对象指针作为第一个参数。
 */
void test6()
{
    // 创建对象
    MyClass obj;

    // 方式一：通过对象调用成员函数
    obj.func(1, 2);

    // 方式二：通过对象指针调用成员函数
    MyClass * p = &obj;
    p->func(3, 4);

    cout << "----------" << endl;

    /**
     * std::function 保存成员函数指针
     *
     * &MyClass::func
     *
     * 表示 MyClass 类中成员函数 func 的地址。
     *
     *
     * 第一种形式：
     *
     * function<void(MyClass&, int, int)> f1 = &MyClass::func;
     *
     * 含义：
     * f1 保存的是 MyClass::func。
     *
     * 调用 f1 时，
     * 第一个参数需要传入 MyClass 对象引用，
     * 后两个参数才是成员函数 func 本身需要的 int 参数。
     *
     *
     * f1(obj, 10, 20)
     *
     * 等价于：
     *
     * obj.func(10, 20)
     */
    function<void(MyClass&, int, int)> f1 = &MyClass::func;
    f1(obj, 10, 20);

    /**
     * 第二种形式：
     *
     * function<void(MyClass*, int, int)> f2 = &MyClass::func;
     *
     * 含义：
     * 第一个参数也可以写成对象指针。
     *
     * f2(&obj, 30, 40)
     *
     * 等价于：
     *
     * obj.func(30, 40)
     */
    function<void(MyClass*, int, int)> f2 = &MyClass::func;
    f2(&obj, 30, 40);

    /**
     * bind 绑定成员函数所属对象
     *
     * bind(&MyClass::func, obj, _1, _2)
     *
     * 表示：
     * 成员函数所属对象固定为 obj，
     * 成员函数的两个普通参数通过占位符传入。
     *
     * 原调用形式可以理解为：
     *
     * void(MyClass&, int, int)
     *
     * bind 绑定对象 obj 后：
     *
     * void(int, int)
     *
     *
     * 注意：
     * 这里传入的是 obj，
     * bind 内部通常保存的是 obj 的副本。
     */
    function<void(int, int)> f3 = bind(&MyClass::func, obj,
                                       std::placeholders::_1,
                                       std::placeholders::_2);

    // 等价于 obj.func(100, 200)
    f3(100, 200);

    /**
     * bind 绑定成员函数所属对象指针
     *
     * bind(&MyClass::func, &obj, _1, _2)
     *
     * 表示：
     * 成员函数所属对象固定为 &obj。
     *
     * 后续调用 f4 时，
     * 会通过对象地址调用成员函数。
     *
     * bind 后的新调用形式仍然是：
     *
     * void(int, int)
     *
     * f4(300, 400)
     *
     * 等价于：
     *
     * obj.func(300, 400)
     */
    function<void(int, int)> f4 = bind(&MyClass::func, &obj,
                                       std::placeholders::_1,
                                       std::placeholders::_2);

    f4(300, 400);
}


int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();

    // 当前测试 std::function 保存成员函数
    test6();

    return 0;
}