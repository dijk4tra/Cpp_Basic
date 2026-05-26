#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * std::mem_fn：成员函数适配器
 *
 * 1. 作用
 *
 *    std::mem_fn 可以把成员函数指针包装成一个函数对象，
 *    包装后的对象可以像普通函数一样调用。
 *
 * 2. 成员函数指针的特点
 *
 *    普通函数指针可以直接调用，
 *    但是成员函数指针必须依赖某个对象或对象指针才能调用。
 *
 *    例如：
 *    void (Number::*f)() = &Number::print;
 *
 *    调用时需要写成：
 *
 *    (obj.*f)();
 *    或
 *    (ptr->*f)();
 *
 * 3. 使用 std::mem_fn 后
 *
 *    auto f1 = std::mem_fn(&Number::print);
 *
 *    f1 变成了一个函数对象，
 *    既可以接收对象，也可以接收对象指针：
 *
 *    f1(obj);
 *    f1(&obj);
 *
 * 4. 常见使用场景
 *
 *    当容器中存放的是对象，想要批量调用对象的成员函数时，
 *    可以配合 std::for_each 使用 std::mem_fn。
 */

class Number
{
public:
    Number(int data = 0)
    : m_data(data)
    {}

    // 普通成员函数
    void print()
    {
        cout << "m_data:" << m_data << endl;
    }

    int m_data;
};

void test1()
{
    Number obj;

    // 定义成员函数指针：
    // f 指向 Number 类中返回值为 void、参数为空的成员函数
    void (Number::*f)() = &Number::print;

    // 通过对象调用成员函数指针
    // 等价于 obj.print()
    (obj.*f)();

    // 通过对象指针调用成员函数指针
    // 等价于 (&obj)->print()
    (&obj->*f)();

    // 使用 std::mem_fn 包装成员函数指针
    //
    // &Number::print 原本是成员函数指针，
    // 使用 mem_fn 后会被转换成一个可调用的函数对象
    auto f1 = std::mem_fn(&Number::print);

    // f1 可以接收对象
    // 等价于 obj.print()
    f1(obj);

    // f1 也可以接收对象指针
    // 等价于 (&obj)->print()
    f1(&obj);
}

void test2()
{
    vector<Number> box;

    for(int i = 0; i < 10; ++i)
    {
        box.push_back(Number(i));
    }

    // 使用 for_each 遍历容器，
    // 对容器中的每一个 Number 对象调用 print 成员函数
    //
    // 不能直接写：
    // std::for_each(box.begin(), box.end(), &Number::print);
    //
    // 因为 &Number::print 是成员函数指针，
    // 不能像普通函数一样直接调用。
    //
    // 可以使用 bind 适配：
    // std::for_each(box.begin(), box.end(), bind(&Number::print, std::placeholders::_1));
    //
    // 也可以使用 mem_fn 适配：
    // std::mem_fn(&Number::print) 会把成员函数指针包装成函数对象，
    // for_each 每次遍历到一个 Number 对象时，都会调用它的 print 成员函数。
    std::for_each(box.begin(), box.end(), std::mem_fn(&Number::print));
}

int main()
{
    // test1();
    test2();
    
    return 0;
}