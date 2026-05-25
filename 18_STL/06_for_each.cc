#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * for_each 函数
 *
 * 定义于头文件 <algorithm>
 *
 * 函数原型：
 * template< class InputIt, class UnaryFunction >
 * UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );
 *
 * 功能：
 * 按顺序将函数对象 f 应用于区间 [first, last) 中的每一个元素。
 *
 * 参数说明：
 * first：区间起始位置
 * last ：区间结束位置，注意不包含 last 指向的元素
 * f    ：可调用对象，可以是普通函数、函数指针、函数对象、lambda 表达式
 *
 * 返回值：
 * 返回传入的函数对象 f。
 */

// 普通函数
// for_each 遍历时，会把每个元素作为参数传给该函数
void func(int num)
{
    cout << num << " ";
}

// 使用普通函数
void test1()
{
    vector<int> box1{1, 2, 3, 4, 5};
    list<int> box2{2, 1, 3, 5, 4};

    // 把 box1 迭代器范围 [begin, end) 内的每个元素依次传给 func
    for_each(box1.begin(), box1.end(), func);

    cout << endl;
    cout << "------------------------" << endl;

    // 把 box2 迭代器范围 [begin, end) 内的每个元素依次传给 func
    for_each(box2.begin(), box2.end(), func);

    cout << endl;
}

// 使用函数指针
void test2()
{
    vector<int> box1{1, 2, 3, 4, 5};
    list<int> box2{2, 1, 3, 5, 4};

    // func 是函数名，&func 是函数地址
    // 在这里 func 和 &func 都可以作为 for_each 的第三个参数
    for_each(box1.begin(), box1.end(), &func);

    cout << endl;
    cout << "------------------------" << endl;

    // 使用函数指针作为可调用对象
    for_each(box2.begin(), box2.end(), &func);

    cout << endl;
}

// 函数对象，也叫仿函数
struct Func
{
    // 重载 operator()
    // 使 Func 的对象可以像函数一样被调用
    void operator()(int num)
    {
        cout << num << " ";
    }
};

// 使用函数对象
void test3()
{
    vector<int> box{1, 2, 3, 4, 5};

    // Func() 创建一个匿名函数对象
    // for_each 会将每个元素依次传给 Func::operator()
    for_each(box.begin(), box.end(), Func());
}

// 使用 lambda 表达式
void test4()
{
    vector<int> box{1, 2, 3, 4, 5};

    // 使用 lambda 表达式作为 for_each 的第三个参数
    // [](int num)->void 表示：
    // []        捕获列表，此处为空，表示不捕获外部变量
    // (int num) 参数列表，接收当前遍历到的元素
    // ->void    返回值类型，可以省略
    for_each(box.begin(), box.end(), 
        [](int num)->void
        {
            cout << num << " ";
        }
    );

    cout << endl;
}


int main()
{
    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}