#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * std::mem_fn：成员函数适配器
 * std::mem_fn 定义在头文件 <functional> 中。
 *
 * 作用：
 * 把成员函数指针包装成一个函数对象。
 * 包装后的函数对象可以像普通函数一样调用。
 *
 *
 * 1. 成员函数指针的特点
 *
 * 普通函数指针可以直接调用。
 * 例如：
 * void (*f)() = func;
 * f();
 *
 * 但是成员函数指针不能脱离对象单独调用。
 * 因为成员函数必须依赖某个具体对象。
 * 例如：
 * void (Number::*f)() = &Number::print;
 *
 * f 表示：
 * 指向 Number 类中某个成员函数的指针。
 *
 * 但是调用时不能写成：
 * f();
 * 因为缺少对象。
 *
 * 正确调用方式是：
 * (obj.*f)();
 * 或：
 * (ptr->*f)();
 *
 * 其中：
 * obj 是对象；
 * ptr 是对象指针。
 *
 *
 * 2. 使用 std::mem_fn 后
 *
 * auto f1 = std::mem_fn(&Number::print);
 * f1 就是一个函数对象。
 *
 * 它可以接收对象：
 * f1(obj);
 * 等价于：
 * obj.print();
 *
 * 它也可以接收对象指针：
 * f1(&obj);
 * 等价于：
 * (&obj)->print();
 *
 *
 * 3. 常见使用场景
 *
 * 当容器中存放的是对象，
 * 并且想要批量调用对象的成员函数时，
 * 可以配合 std::for_each 使用 std::mem_fn。
 *
 * 例如：
 * std::for_each(box.begin(), box.end(),
 *               std::mem_fn(&Number::print));
 *
 * 表示：
 * 遍历 box 中的每一个 Number 对象，
 * 并调用它的 print 成员函数。
 *
 *
 * 4. 和 std::bind 的关系
 *
 * std::bind 也可以适配成员函数。
 * 例如：
 * bind(&Number::print, std::placeholders::_1)
 *
 * 也能把成员函数指针适配成一个接收对象的函数对象。
 *
 * 但是在“只是调用某个成员函数”这种场景下，
 * std::mem_fn 更简单、更直接。
 */


class Number
{
public:
    // 构造函数，默认 m_data = 0
    Number(int data = 0)
    : m_data(data)
    {}

    /**
     * 普通成员函数 print
     * 
     * 注意：
     * print 是非静态成员函数，
     * 必须依赖某个 Number 对象才能调用。
     */
    void print()
    {
        cout << "m_data:" << m_data << endl;
    }

    // 保存整数数据
    int m_data;
};


void test1()
{
    // 创建 Number 对象
    // 因为构造函数参数有默认值 0，所以这里 m_data = 0
    Number obj;

    /**
     * 定义成员函数指针
     *
     * void (Number::*f)() = &Number::print;
     *
     * 拆开理解：
     *
     * void
     * 表示这个成员函数的返回值类型是 void。
     *
     * Number::*
     * 表示这是一个指向 Number 类成员的指针。
     *
     * f
     * 是成员函数指针变量名。
     *
     * ()
     * 表示这个成员函数没有参数。
     *
     *
     * 所以：
     *
     * f 指向 Number 类中：
     * 返回值为 void，
     * 参数为空的成员函数。
     *
     *
     * &Number::print
     *
     * 表示取 Number::print 这个成员函数的地址。
     */
    void (Number::*f)() = &Number::print;

    /**
     * 通过对象调用成员函数指针
     *
     * 语法：
     *
     * (obj.*f)();
     *
     * 含义：
     * 使用对象 obj 调用 f 指向的成员函数。
     *
     * 等价于：
     *
     * obj.print();
     *
     *
     * 注意：
     * .* 是“对象访问成员指针”的运算符。
     */
    (obj.*f)();

    /**
     * 通过对象指针调用成员函数指针
     *
     * 语法：
     *
     * (ptr->*f)();
     *
     * 其中 ptr 是对象指针。
     *
     * 在本例中：
     *
     * ptr 可以写成 &obj。
     *
     * 所以：
     *
     * ((&obj)->*f)();
     *
     * 等价于：
     *
     * (&obj)->print();
     *
     * 也就是：
     *
     * obj.print();
     *
     *
     * 注意：
     * ->* 是“对象指针访问成员指针”的运算符。
     */
    ((&obj)->*f)();

    /**
     * 使用 std::mem_fn 包装成员函数指针
     *
     * std::mem_fn(&Number::print)
     *
     * 表示：
     * 把成员函数指针 &Number::print
     * 包装成一个普通函数对象。
     *
     *
     * 包装之后得到的 f1，
     * 可以通过普通函数调用语法使用。
     */
    auto f1 = std::mem_fn(&Number::print);

    /**
     * f1 接收对象
     *
     * f1(obj)
     *
     * 等价于：
     *
     * obj.print()
     */
    f1(obj);

    /**
     * f1 接收对象指针
     *
     * f1(&obj)
     *
     * 等价于：
     *
     * (&obj)->print()
     *
     * 也就是：
     *
     * obj.print()
     */
    f1(&obj);
}


void test2()
{
    // 创建 vector 容器，保存 Number 对象
    vector<Number> box;

    /**
     * 向容器中插入 10 个 Number 对象。
     *
     * i 从 0 到 9。
     *
     * 每次执行：
     *
     * box.push_back(Number(i));
     *
     * 都会创建一个 m_data 为 i 的临时 Number 对象，
     * 然后放入 vector 中。
     */
    for (int i = 0; i < 10; ++i)
    {
        box.push_back(Number(i));
    }

    /**
     * 使用 for_each 批量调用成员函数
     *
     * std::for_each 的第三个参数需要的是一个可调用对象。
     *
     * 它会把区间中的每一个元素依次传给这个可调用对象。
     *
     *
     * 如果直接写：
     *
     * std::for_each(box.begin(), box.end(), &Number::print);
     *
     * 这是不合适的。
     *
     * 原因：
     * &Number::print 是成员函数指针。
     *
     * 成员函数指针不能像普通函数一样直接调用，
     * 它必须依赖某个对象。
     *
     *
     * 解决方式一：使用 std::bind
     *
     * std::for_each(box.begin(), box.end(),
     *               bind(&Number::print, std::placeholders::_1));
     *
     * 含义：
     * for_each 每遍历到一个 Number 对象，
     * 就把该对象作为参数传给 bind 返回的函数对象，
     * 从而调用该对象的 print 成员函数。
     *
     *
     * 解决方式二：使用 std::mem_fn
     *
     * std::mem_fn(&Number::print)
     *
     * 会把成员函数指针包装成函数对象。
     *
     * for_each 每次遍历到一个 Number 对象时，
     * 都会执行类似：
     *
     * obj.print();
     *
     *
     * 这里使用 mem_fn 更简洁。
     */
    std::for_each(box.begin(), box.end(), std::mem_fn(&Number::print));
}


int main()
{
    // test1();

    // 当前测试 mem_fn 配合 for_each 批量调用成员函数
    test2();

    return 0;
}