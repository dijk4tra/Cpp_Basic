#include <iostream>

using std::cout;
using std::endl;

/*
 * 可调用实体：
 * 1. 普通函数
 * 2. 成员函数
 * 3. 函数指针
 * 4. 成员函数指针
 * 5. 函数对象
 * 6. lambda 表达式
 *
 * 函数对象：
 * 在类中重载了 operator() 函数调用运算符的对象，
 * 可以像普通函数一样被调用。
 *
 * 使用场景：
 * 1. 配合标准算法库使用
 * 2. 函数对象的本质是对象，因此可以保存额外的数据，
 *    这些数据的生命周期与函数对象本身一致
 */

class MyClass
{
public:
    // 重载 operator() 函数调用运算符，后面的 () 才是真正的参数列表
    void operator()()
    {
        cout << "operator()()" << endl;
    }

    // 对函数调用运算符进行重载
    void operator()(int num)
    {
        cout << "operator()(int)" << endl;
        cout << "num=" << num << endl;
    }

    int  operator()(int a, int b)
    {
        cout << "operator()(int,int)" << endl;
        return a + b;
    }
};

void test1()
{
    MyClass obj;

    // obj 是一个对象，但由于重载了 operator()，因此可以像函数一样调用
    obj();  // 调用无参版本的 operator()

    // 本质：
    /* obj.operator()(); */

    obj(100);

    // 本质：
    /* obj.operator()(100); */

    int sum = obj(1,2);
    cout << sum << endl;

    // 本质：
    /* int sum = obj.operator()(1,2); */

}

void test2()
{
    int count = 0;
}

void test3()
{   
    // 无法访问 test2 中定义的局部变量
    /* cout << count << endl; */
}

// 统计 MyClass2 对象被调用的次数
class MyClass2
{
public:
    // 重载 operator()
    void operator()()
    {
        cout << "operator()()" << endl;
        count++;
    }

    void operator()(int num)
    {
        cout << "operator()(int)" << endl;
        count++;
    }

    int count = 0;
};

void test4()
{
    MyClass2 obj;
    obj();
    obj();
    obj(100);

    cout << obj.count << endl;
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test4();
    return 0;
}