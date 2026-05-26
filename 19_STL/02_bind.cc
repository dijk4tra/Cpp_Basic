#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;


/*
 * std::bind
 *
 * 作用：
 * 包装一个可调用对象，生成一个新的可调用对象，
 * 新对象可以像普通函数一样被调用。
 *
 * 可调用对象包括：
 * 1. 普通函数
 * 2. 函数指针
 * 3. 函数对象
 * 4. lambda 表达式
 * 5. 成员函数
 *
 * bind 可以固定部分参数，也可以调整参数顺序。
 *
 * 例如：
 * 原函数类型：
 *     int(int, int)
 *
 * 通过 bind 固定两个参数后：
 *     int()
 *
 * 通过 bind 固定一个参数后：
 *     int(int)
 *
 * 因此 bind 可以改变函数调用形态：
 *     二元函数 ---> 一元函数
 *     二元函数 ---> 零元函数
 *
 * 占位符：
 * std::placeholders::_1 表示新函数对象调用时传入的第一个参数
 * std::placeholders::_2 表示新函数对象调用时传入的第二个参数
 */

int add(int a, int b)
{
    cout << "a:" << a << " b:" << b << endl;
    return a + b;
}


// bind 包装普通函数
void test1()
{
    // 直接调用普通函数
    add(1,2);

    cout << "-----" << endl;

    // 固定 add 函数中的两个参数：
    // a = 1，b = 2
    //
    // 原函数类型：
    // int(int, int)
    //
    // bind 后的新可调用对象类型：
    // int()
    auto f1 = bind(add,1,2); 

    // 调用 f1() 等价于调用 add(1, 2)
    f1();

    cout << "-------" << endl;

    // std::placeholders::_1 是占位符，表示新函数对象的第一个参数
    // std::placeholders::_2 是占位符，表示新函数对象的第二个参数
    //
    // f2(100, 200) 等价于 add(100, 200)
    auto f2 = bind(add,std::placeholders::_1,std::placeholders::_2);

    f2(100, 200); 

    cout << "-------" << endl;

    // 调整参数顺序：
    //
    // std::placeholders::_2 作为 add 的第一个参数 a
    // std::placeholders::_1 作为 add 的第二个参数 b
    //
    // f3(300, 400) 等价于 add(400, 300)
    auto f3 = bind(add,std::placeholders::_2, std::placeholders::_1);

    f3(300, 400); 

    cout << "-----" << endl;

    // 部分固定，部分传递：
    //
    // a 使用占位符，由调用 f4 时传入
    // b 固定为 10
    //
    // 原函数类型：
    // int(int, int)
    //
    // bind 后：
    // int(int)
    //
    // f4(100) 等价于 add(100, 10)
    auto f4 = bind(add,std::placeholders::_1, 10);

    f4(100);
}


// bind 包装普通函数指针
void test2()
{
    // 直接调用普通函数
    add(1,2);

    cout << "-----" << endl;

    // &add 表示普通函数 add 的函数指针
    // 固定 add 函数中的参数 a = 1，b = 2
    //
    // int(int, int) ---> int()
    auto f1 = bind(&add,1,2); 

    // 等价于 add(1, 2)
    f1();

    cout << "-------" << endl;

    // 使用占位符保留两个参数
    //
    // f2(100, 200) 等价于 add(100, 200)
    auto f2 = bind(&add,std::placeholders::_1,std::placeholders::_2);

    f2(100, 200); 

    cout << "-------" << endl;

    // 调整参数顺序
    //
    // f3(300, 400) 等价于 add(400, 300)
    auto f3 = bind(&add,std::placeholders::_2, std::placeholders::_1);

    f3(300, 400); 

    cout << "-----" << endl;

    // 部分固定，部分传递
    //
    // a 使用占位符
    // b 固定为 10
    //
    // int(int, int) ---> int(int)
    //
    // f4(100) 等价于 add(100, 10)
    auto f4 = bind(&add,std::placeholders::_1, 10);

    f4(100);
}

// bind 包装函数对象
struct Callable
{
    // 重载 operator()
    // 使 Callable 的对象可以像函数一样被调用
    int operator()(int a,int b)
    {
        cout << "a =" << a << " b =" << b << endl;
        return a + b;
    }

};

void test3()
{
    Callable callable;

    // 直接调用函数对象
    callable(1,2);

    cout << "-----" << endl;

    // bind 包装函数对象
    //
    // 固定函数对象的两个参数：
    // a = 1，b = 2
    //
    // int(int, int) ---> int()
    auto f1 = bind(Callable(),1,2);

    // 等价于 Callable()(1, 2)
    f1();

    cout << "-------" << endl;

    // 使用占位符保留两个参数
    //
    // f2(100, 200) 等价于 Callable()(100, 200)
    auto f2 = bind(Callable(),std::placeholders::_1, std::placeholders::_2);

    f2(100, 200);

    cout << "-------" << endl;

    // 部分固定，部分传递
    //
    // a 使用占位符
    // b 固定为 20
    //
    // int(int, int) ---> int(int)
    //
    // f3(100) 等价于 Callable()(100, 20)
    auto f3 = bind(Callable(),std::placeholders::_1,20);

    f3(100);
}


// bind 包装 lambda 表达式
void test4()
{
    // 定义 lambda 后立即调用
    [](int a, int b)->void{
        cout << "a:" << a << " b:" << b << endl;
    }(1,2);

    cout << "-------" << endl;

    // 使用 auto 接收 lambda 表达式
    // f0 的调用形式为：void(int, int)
    auto f0 = [](int a, int b)->void{
        cout << "a:" << a << " b:" << b << endl;
    };

    // 调用 lambda
    f0(1,2);

    cout << "-------" << endl;

    // 使用 bind 绑定 lambda 表达式的两个参数
    //
    // void(int, int) ---> void()
    //
    // f1() 等价于调用 lambda(1, 2)
    auto f1 = bind([](int a, int b)->void{
        cout << "a:" << a << " b:" << b << endl;
    }, 1,2);

    f1();

    cout << "-----" << endl;

    // 使用占位符
    //
    // 第一个参数 a 固定为 1
    // 第二个参数 b 使用占位符，由调用 f2 时传入
    //
    // void(int, int) ---> void(int)
    //
    // f2(100) 等价于调用 lambda(1, 100)
    auto f2 = bind([](int a, int b)->void{
        cout << "a:" << a << " b:" << b << endl;
    }, 1, std::placeholders::_1);

    f2(100);
}

// bind 包装成员函数
class MyClass
{
public:
    int add(int a, int b)
    {
        cout << "a:" << a << " b:" << b << endl;
        return a + b;
    }
};

void test5()
{
    MyClass obj;

    // 通过对象调用成员函数
    obj.add(1,2);

    cout << "------" << endl;

    // 通过对象指针调用成员函数
    MyClass * p = &obj;
    p->add(1,2);

    cout << "------" << endl;

    // bind 包装成员函数时，需要指定成员函数地址：
    // &MyClass::add
    //
    // 第二个参数需要提供对象或对象指针，
    // 用来说明调用哪个对象的成员函数。
    //
    // 这里传入 obj，bind 内部会保存 obj 的副本。
    //
    // f1() 等价于：
    // obj.add(10, 20)
    auto f1 = bind(&MyClass::add, obj, 10, 20);

    f1();

    cout << "----" << endl;

    // 这里传入 &obj，表示通过对象地址调用成员函数。
    //
    // int(MyClass*, int, int) ---> int()
    //
    // f2() 等价于：
    // (&obj)->add(10, 20)
    auto f2 = bind(&MyClass::add, &obj, 10, 20);

    f2();

    cout << "----" << endl;

    // 使用占位符保留成员函数的两个普通参数
    //
    // 对象地址 &obj 已经固定
    // a 和 b 通过占位符传入
    //
    // int(MyClass*, int, int) ---> int(int, int)
    //
    // f3(100, 200) 等价于：
    // obj.add(100, 200)
    auto f3 = bind(&MyClass::add, &obj, std::placeholders::_1, std::placeholders::_2);

    f3(100, 200);
}


// 函数引用
void test6()
{
    int num = 1;

    // 定义普通引用 ref，绑定到变量 num
    int & ref = num;

    // 通过引用修改 num
    ref = 2;

    cout << ref << endl;

    cout << "--------" << endl;

    // 定义一个引用绑定到函数 add 上
    //
    // add 的函数类型是：
    // int(int, int)
    //
    // refAdd 是 add 的函数引用
    int (&refAdd)(int,int) = add;

    // 通过函数引用调用 add
    refAdd(1,2);

    // 其他写法：
    // auto& 可以自动推导出函数引用类型
    auto & refAdd2 = add;

    // 通过函数引用调用 add
    refAdd2(1,2);
}

int main(int argc, char const *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}