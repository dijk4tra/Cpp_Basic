#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * for_each：
 *
 * for_each 是 STL 中的遍历算法。
 *
 * 头文件：
 * #include <algorithm>
 *
 *
 * 函数原型：
 *
 * template< class InputIt, class UnaryFunction >
 * UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );
 *
 *
 * 功能：
 *
 * 按顺序遍历区间 [first, last) 中的每一个元素，
 * 并把每个元素依次传给可调用对象 f。
 *
 *
 * 参数说明：
 *
 * first：
 * 区间起始位置。
 *
 * last：
 * 区间结束位置。
 *
 * 注意：
 * STL 中的区间通常都是左闭右开：
 *
 * [first, last)
 *
 * 表示包含 first 指向的元素，
 * 不包含 last 指向的元素。
 *
 *
 * f：
 * 可调用对象。
 *
 * 可以是：
 * 1. 普通函数
 * 2. 函数指针
 * 3. 函数对象，也叫仿函数
 * 4. lambda 表达式
 *
 *
 * 返回值：
 *
 * for_each 会返回传入的可调用对象 f。
 *
 * 在普通遍历打印时，
 * 通常不会关心这个返回值。
 *
 *
 * 注意：
 *
 * for_each 本身只是负责遍历区间，
 * 至于每个元素要做什么操作，
 * 由第三个参数 f 决定。
 */


// 普通函数
/**
 * func 是一个普通函数。
 *
 * 参数：
 * int num
 *
 * 表示接收当前遍历到的元素。
 *
 * for_each 遍历容器时，
 * 会把区间中的每一个元素依次传给 func。
 *
 * 例如容器中有：
 * 1 2 3 4 5
 *
 * 那么调用过程类似于：
 * func(1);
 * func(2);
 * func(3);
 * func(4);
 * func(5);
 */
void func(int num)
{
    cout << num << " ";
}


// 使用普通函数
void test1()
{
    /**
     * 创建 vector 容器 box1。
     *
     * vector 是顺序容器，
     * 支持随机访问迭代器。
     */
    vector<int> box1{1, 2, 3, 4, 5};

    /**
     * 创建 list 容器 box2。
     *
     * list 是双向链表，
     * 支持双向迭代器。
     *
     * for_each 只要求输入迭代器能力，
     * 所以 vector 和 list 都可以使用 for_each 遍历。
     */
    list<int> box2{2, 1, 3, 5, 4};

    /**
     * for_each(box1.begin(), box1.end(), func);
     *
     * 含义：
     * 遍历 box1 中 [begin, end) 区间的所有元素，
     * 并把每个元素依次传给普通函数 func。
     *
     * 调用效果类似于：
     *
     * func(1);
     * func(2);
     * func(3);
     * func(4);
     * func(5);
     *
     * 输出结果：
     * 1 2 3 4 5
     */
    for_each(box1.begin(), box1.end(), func);

    cout << endl;
    cout << "------------------------" << endl;

    /**
     * 同样的方式遍历 list。
     *
     * 因为 for_each 是通过迭代器访问元素，
     * 所以它并不关心容器底层是数组还是链表。
     */
    for_each(box2.begin(), box2.end(), func);

    cout << endl;
}


// 使用函数指针
void test2()
{
    vector<int> box1{1, 2, 3, 4, 5};
    list<int> box2{2, 1, 3, 5, 4};

    /**
     * 函数名 func 在很多场景下，
     * 可以自动转换为函数地址。
     *
     * 所以下面两种写法都可以：
     *
     * for_each(box1.begin(), box1.end(), func);
     *
     * for_each(box1.begin(), box1.end(), &func);
     *
     *
     * &func 表示取函数 func 的地址，
     * 也就是函数指针。
     *
     * for_each 内部会通过这个函数指针调用 func。
     */
    for_each(box1.begin(), box1.end(), &func);

    cout << endl;
    cout << "------------------------" << endl;

    /**
     * 使用函数指针作为 for_each 的第三个参数。
     *
     * 效果和直接传函数名 func 一样。
     */
    for_each(box2.begin(), box2.end(), &func);

    cout << endl;
}


// 函数对象，也叫仿函数
/**
 * 函数对象 function object：
 *
 * 也叫仿函数 functor。
 *
 * 它本质上是一个类或结构体对象，
 * 但是这个类重载了 operator()，
 * 所以它的对象可以像函数一样被调用。
 *
 *
 * 例如：
 *
 * Func f;
 * f(10);
 *
 * 这句代码看起来像调用函数，
 * 实际上调用的是：
 *
 * f.operator()(10);
 *
 *
 * 函数对象的优点：
 *
 * 1. 可以像函数一样使用
 * 2. 可以保存状态，也就是可以有成员变量
 * 3. 比普通函数更灵活
 */
struct Func
{
    /**
     * 重载函数调用运算符 operator()。
     *
     * 参数 num：
     * 接收 for_each 当前遍历到的元素。
     *
     * 返回值 void：
     * 表示只打印，不返回结果。
     */
    void operator()(int num)
    {
        cout << num << " ";
    }
};


// 使用函数对象
void test3()
{
    /**
     * 创建 vector 容器。
     */
    vector<int> box{1, 2, 3, 4, 5};

    /**
     * Func()：
     *
     * 创建一个匿名函数对象。
     *
     * for_each 会把每个元素依次传给
     * Func 对象的 operator() 函数。
     *
     *
     * 执行效果类似于：
     *
     * Func tmp;
     * tmp(1);
     * tmp(2);
     * tmp(3);
     * tmp(4);
     * tmp(5);
     *
     *
     * 输出结果：
     * 1 2 3 4 5
     */
    for_each(box.begin(), box.end(), Func());
}


// 使用 lambda 表达式
void test4()
{
    /**
     * 创建 vector 容器。
     */
    vector<int> box{1, 2, 3, 4, 5};

    /**
     * lambda 表达式：
     *
     * lambda 是一种匿名函数。
     *
     * 它可以直接写在需要可调用对象的位置，
     * 不需要提前单独定义普通函数或函数对象。
     *
     *
     * 基本格式：
     *
     * [捕获列表](参数列表)->返回值类型
     * {
     *     函数体;
     * };
     *
     *
     * 本例中的 lambda：
     *
     * [](int num)->void
     * {
     *     cout << num << " ";
     * }
     *
     * 含义：
     *
     * []：
     * 捕获列表。
     *
     * 当前为空，
     * 表示不捕获外部变量。
     *
     *
     * (int num)：
     * 参数列表。
     *
     * num 用来接收 for_each 当前遍历到的元素。
     *
     *
     * ->void：
     * 返回值类型。
     *
     * 表示这个 lambda 不返回值。
     *
     * 当返回值类型可以被编译器推导出来时，
     * ->void 可以省略。
     *
     *
     * 函数体：
     *
     * cout << num << " ";
     *
     * 表示打印当前元素。
     */
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
    /**
     * test1：
     * 使用普通函数作为 for_each 的第三个参数。
     *
     * test2：
     * 使用函数指针作为 for_each 的第三个参数。
     *
     * test3：
     * 使用函数对象，也叫仿函数。
     *
     * test4：
     * 使用 lambda 表达式。
     *
     *
     * 四种方式的核心思想都是一样的：
     *
     * for_each 负责遍历区间，
     * 第三个参数负责处理每一个元素。
     */
    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}