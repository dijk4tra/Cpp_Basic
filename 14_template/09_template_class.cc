#include <iostream>
#include <string>
#include <array>

using std::cout;
using std::endl;
using std::array;

/**
 * 类模板：把模板应用在类上。
 *
 * 基本语法：
 *
 * template <typename T>
 * class Box
 * {
 *     // 在类中可以正常使用 T 类型
 * };
 *
 * T 是类型参数，可以作为：
 * 1. 数据成员的类型
 * 2. 成员函数的参数类型
 * 3. 成员函数的返回值类型
 *
 * 类模板本身不是一个具体的类。
 * 只有指定模板参数后，编译器才会生成具体的类。
 *
 * 例如：
 * Box<int>       // 生成一个管理 int 类型数据的类
 * Box<double>    // 生成一个管理 double 类型数据的类
 * Box<string>    // 生成一个管理 string 类型数据的类
 */


class Data
{
public:
    Data(int data = 0)
    : m_data(data)
    {}

    int getData()
    {
        return m_data;
    }

private:
    int m_data;
};


// 需求：希望管理者可以管理任意类型的资源，
// 而不是只能管理单一的 Data 资源。
// 如果不用模板，下面这个 MiddleLayer 只能管理 Data 类型资源。
class MiddleLayer
{
public:
    MiddleLayer(Data *p)
    : m_p(p)
    {}

    ~MiddleLayer()
    {
        delete m_p;
    }

    // operator->：让对象可以像指针一样访问成员
    Data *operator->()
    {
        return m_p;
    }

    // operator*：让对象可以像指针一样解引用
    Data &operator*()
    {
        return *m_p;
    }

private:
    // 资源类型的指针
    Data *m_p;
};


void test1()
{
    MiddleLayer ml{new Data{}};

    ml->getData();
    (*ml).getData();

    cout << "-----" << endl;

    // 错误：
    // MiddleLayer 只能管理 Data*，不能管理 int*
    // MiddleLayer ml2{new int{100}};
}


// Box 是类模板，T 可以代表任意类型
template <typename T>
class Box
{
public:
    Box(T data)
    : m_data(data)
    {}

    // 成员函数中可以使用类模板参数 T
    void print(T t)
    {
        cout << "print()" << endl;
        cout << t << endl;
    }

    // 成员函数声明和定义分开写
    void print2(T t);

private:
    T m_data;
};


// 类外实现类模板的成员函数
// 注意：
// 1. 类外实现时，需要重新写 template <typename T>
// 2. 类名作用域要写成 Box<T>::
// 3. 如果类模板参数有默认值，类外实现时不要重复写默认值
template <typename T>
void Box<T>::print2(T t)
{
    cout << "print2()" << endl;
    cout << t << endl;
}


// 使用类模板之后，遇到新类型时就不需要重新写一个新类了
/*
class Box2
{
public:
    Box2(double data)
    : m_data(data)
    {}

private:
    double m_data;
};
*/


class Point
{
public:
    Point(int a, int b)
    : m_num1(a)
    , m_num2(b)
    {}

private:
    int m_num1;
    int m_num2;
};


void test3()
{
    // C++17 起支持类模板参数推导，可以写成：
    // Box box1{100};      // 推导为 Box<int>
    // Box box2{3.14};     // 推导为 Box<double>
    //
    // 为了学习类模板基础，这里使用更明确的写法。

    // 显式指定类模板参数
    Box<int> box1{100};
    Box<double> box2{3.13};
    Box<std::string> box3{"abc"};
    Box<Point> box4{Point{1, 2}};

    // 注意：
    // Box<> 只有在类模板参数有默认值时才能使用。
    // 当前 Box<T> 没有给 T 设置默认类型，所以不能写 Box<>。
    //
    // Box<> box5{100}; // 错误

    Box<int> box5{100};
    box5.print(10);
    box5.print2(10);
}


// 作业：自定义一个栈 Stack，可以存储任意类型的数据。
// 支持入栈、出栈、判空、判满、查看栈顶元素等操作。
template <typename T = int, int Capacity = 10>
class Stack
{
public:
    Stack()
    : m_p(new T[Capacity])
    , m_size(0)
    {}

    ~Stack()
    {
        delete[] m_p;
    }

    bool isEmpty() const
    {
        return m_size == 0;
    }

    bool isFull() const
    {
        return m_size == Capacity;
    }

    void push(const T &value)
    {
        if (isFull())
        {
            cout << "栈已满，无法入栈" << endl;
            return;
        }

        m_p[m_size++] = value;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "栈为空，无法出栈" << endl;
            return;
        }

        --m_size;
    }

    T &top()
    {
        return m_p[m_size - 1];
    }

    const T &top() const
    {
        return m_p[m_size - 1];
    }

private:
    T *m_p;
    int m_size;
};


// STL：std::array 静态数组
// array<T, N> 中：
// T 是类型模板参数，表示元素类型
// N 是非类型模板参数，表示数组容量
void test4()
{
    array<int, 5> arr{1, 2, 3, 4, 5};

    cout << arr[0] << endl;
    cout << arr[1] << endl;
    cout << arr[2] << endl;
    cout << arr[3] << endl;
    cout << arr[4] << endl;

    cout << "---------" << endl;
    cout << arr.size() << endl;

    cout << "---------" << endl;
    cout << arr.front() << endl;

    cout << "---------" << endl;
    cout << arr.back() << endl;
}


int main(int argc, char *argv[])
{
    /* test1(); */
    /* test3(); */
    test4();

    return 0;
}