#include <iostream>
#include <iterator>
#include <array>

using std::cout;
using std::endl;
using std::array;

/**
 * 类模板：
 * 把模板作用于类上。
 *
 * 基本语法：
 *
 * template <typename T>
 * class Box
 * {
 *
 * };
 *
 *
 * T 是类型参数。
 *
 * 在类模板内部，
 * 可以像使用普通类型一样使用 T。
 *
 * 例如：
 * 1. T 可以作为数据成员的类型
 * 2. T 可以作为成员函数的参数类型
 * 3. T 可以作为成员函数的返回值类型
 * 4. T 可以作为局部变量类型
 *
 *
 * 类模板和函数模板的区别：
 *
 * 函数模板调用时，
 * 很多情况下可以通过函数实参自动推导模板参数。
 *
 * 例如：
 * print(100);
 * 编译器可以推导出 T = int。
 *
 *
 * 类模板创建对象时，
 * 通常需要显式写出模板参数：
 *
 * Box<int> box1{100};
 *
 * 表示创建一个 Box<int> 类型的对象。
 *
 *
 * C++17 之后支持类模板参数推导 CTAD：
 * 某些情况下可以写成：
 *
 * Box box1{100};
 *
 * 编译器根据构造函数参数推导出 T = int。
 *
 * 但在学习阶段，
 * 建议先明确写出：
 *
 * Box<int> box1{100};
 */ 


class Data
{
public:
    /**
     * 普通成员函数。
     *
     * 返回 Data 对象中的 m_data。
     *
     * 当前 m_data 没有显式初始化，
     * 如果直接读取它，
     * 得到的值是不确定的。
     *
     * 更规范的写法是：
     * 给 Data 添加构造函数，
     * 或者给 m_data 设置类内默认值。
     */
    int getData()
    {
        return m_data;
    }

private:
    int m_data;
};

/**
 * 需求：
 * 希望“管理者”可以管理任何类型的资源，
 * 而不是只能管理 Data 资源。
 *
 * 当前 MiddleLayer 不是模板类，
 * 它只能管理 Data *。
 *
 * 如果要管理 int *、double *、Point * 等其他资源，
 * 就需要重新写新的类。
 *
 * 这会导致代码重复。
 *
 * 解决思路：
 * 使用类模板，
 * 把资源类型抽象成模板参数 T。
 */
class MiddleLayer
{
public:
    /**
     * 构造函数。
     *
     * 参数是 Data *。
     *
     * 表示 MiddleLayer 当前只能接收并管理 Data 类型资源。
     */
    MiddleLayer(Data * p)
    : m_p(p)
    {}

    /**
     * 析构函数。
     *
     * 当 MiddleLayer 对象销毁时，
     * 自动释放 m_p 指向的堆区资源。
     *
     * 这里体现了一种资源管理思想：
     * 对象创建时接管资源，
     * 对象销毁时释放资源。
     *
     * 注意：
     * 因为使用的是 new Data，
     * 所以释放时用 delete。
     */
    ~MiddleLayer()
    {
        delete m_p;
    }

    /**
     * 重载 operator->。
     *
     * 作用：
     * 让 MiddleLayer 对象可以像指针一样使用。
     *
     * 例如：
     * ml->getData();
     *
     * 实际上会被解释成：
     * ml.operator->()->getData();
     *
     * operator-> 返回 m_p，
     * 然后通过 m_p 调用 Data 的 getData 成员函数。
     */
    Data * operator->()
    {
        return m_p;
    }

    /**
     * 重载 operator*。
     *
     * 作用：
     * 让 MiddleLayer 对象可以像指针一样解引用。
     *
     * 例如：
     * (*ml).getData();
     *
     * 实际上会先调用：
     * ml.operator*()
     *
     * 返回 m_p 指向的 Data 对象引用，
     * 然后调用 getData()。
     */
    Data & operator*()
    {
        return *m_p;
    }

private:
    // 资源类型的指针
    // 当前只能保存 Data *
    Data * m_p;
};

void test1()
{
    /**
     * 创建 MiddleLayer 对象。
     *
     * new Data{}：
     * 在堆区创建一个 Data 对象。
     *
     * MiddleLayer ml { new Data{} };
     * 表示 ml 接管这个 Data 对象的管理权。
     *
     * 当 ml 生命周期结束时，
     * 析构函数会 delete m_p。
     */
    MiddleLayer ml { new Data{} };

    /**
     * 因为 MiddleLayer 重载了 operator->，
     * 所以可以像指针一样访问 Data 的成员函数。
     */
    ml->getData();

    /**
     * 因为 MiddleLayer 重载了 operator*，
     * 所以可以像指针一样解引用后访问成员函数。
     */
    (*ml).getData();

    cout << "-----" << endl;

    /**
     * 当前 MiddleLayer 只能管理 Data *。
     *
     * 如果传入 int *，
     * 类型不匹配，会编译失败。
     *
     * 这正是需要类模板的原因。
     */
    /* MiddleLayer ml2{ new int{100} }; */
}


/**
 * 类模板 Box。
 *
 * template <typename T>
 * 表示 Box 是一个类模板，
 * T 是类型参数。
 *
 * 使用时需要指定 T 的具体类型。
 *
 * 例如：
 * Box<int>
 * Box<double>
 * Box<std::string>
 */
template<typename T>
class Box
{
public:
    /**
     * 构造函数。
     *
     * 参数类型是 T。
     *
     * 当创建 Box<int> 时：
     * T = int
     * 构造函数相当于：
     * Box(int data);
     *
     * 当创建 Box<double> 时：
     * T = double
     * 构造函数相当于：
     * Box(double data);
     */
    Box(T data)
    : m_data(data)
    {}
    
    /**
     * 成员函数。
     *
     * 参数 t 的类型是 T。
     *
     * 注意：
     * 这里的 print 不是成员函数模板，
     * 它只是类模板中的普通成员函数。
     *
     * 因为 T 来自类模板 Box<T>，
     * 所以不同的 Box<T> 会生成不同版本的 print。
     *
     * 例如：
     * Box<int> 中：
     * void print(int t);
     *
     * Box<double> 中：
     * void print(double t);
     */
    void print(T t)
    {
        cout << "print()" << endl;
    }

    /**
     * 成员函数声明。
     *
     * 这里只声明，不在类内定义。
     *
     * 因为 Box 是类模板，
     * 所以类外实现时需要带上模板参数。
     */
    void print2(T t);

private:
    /**
     * 数据成员。
     *
     * m_data 的类型是 T。
     *
     * Box<int> 中：
     * m_data 是 int。
     *
     * Box<double> 中：
     * m_data 是 double。
     *
     * Box<std::string> 中：
     * m_data 是 std::string。
     */
    T m_data;
};


/**
 * 类模板的成员函数在类外实现。
 *
 * 注意几点：
 *
 * 1. 需要重新写模板参数列表：
 *
 *    template <typename T>
 *
 *
 * 2. 类名作用域要写成：
 *
 *    Box<T>::print2
 *
 *    因为 Box 不是一个具体类，
 *    Box<T> 才表示某一种具体的模板实例。
 *
 *
 * 3. 如果类模板参数有默认值，
 *    类外实现成员函数时不要再重复写默认值。
 *
 *    例如：
 *    template <typename T = int>
 *    class Box;
 *
 *    类外实现时写：
 *    template <typename T>
 *    void Box<T>::func()
 *
 *    不要再写：
 *    template <typename T = int>
 */
template <typename T>
void Box<T>::print2(T t)
{
    cout << "xxxxx" << endl;
}


// 使用模板之后，遇到新需求，例如 double m_data，
// 就不需要再写新的类了。
// 只需要创建 Box<double> 即可。
/* class Box2 */
/* { */
/* public: */
/*     Box2(double data) */
/*     : m_data(data) */
/*     {} */

/* private: */
/*     double m_data; */
/* }; */


class Point
{
public:
    /**
     * 构造函数。
     *
     * 用两个 int 初始化 Point 对象。
     */
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
    /**
     * 如果不使用类模板，
     * int 类型需要写一个 Box，
     * double 类型可能又要写一个 Box2。
     *
     * 使用类模板后，
     * 只需要写一份 Box<T>。
     */

    /* Box box1{ 100 }; */
    /* Box2 box2{ 3.14 }; */

    /**
     * 显式实例化类模板。
     *
     * Box<int>：
     * T = int
     *
     * box1 中的 m_data 是 int。
     */
    Box<int> box1{100};

    /**
     * Box<double>：
     * T = double
     *
     * box2 中的 m_data 是 double。
     */
    Box<double> box2{3.13};

    /**
     * Box<std::string>：
     * T = std::string
     *
     * box3 中的 m_data 是 std::string。
     *
     * 注意：
     * 当前代码没有显式包含 <string>。
     * 更规范的写法是补充：
     * #include <string>
     */
    Box<std::string> box3{"abc"};

    /**
     * 类模板也可以使用自定义类型作为模板参数。
     *
     * 例如：
     * Box<Point> box3{ Point{1, 2} };
     *
     * 此时：
     * T = Point
     * m_data 是 Point 类型。
     */
    /* Box<Point> box3{ Point{1,2} }; */

    /**
     * 类模板参数推导。
     *
     * 在 C++17 之前，
     * 类模板创建对象时通常必须显式指定模板参数：
     *
     * Box<int> box4{100};
     *
     * 不能直接写：
     * Box box4{100};
     *
     *
     * 如果类模板有默认模板参数，
     * 可以写：
     * Box<> box4{100};
     *
     * 其中 <> 表示使用默认模板参数。
     *
     * 但是当前 Box 没有默认模板参数，
     * 所以 Box<> box4{100}; 不能使用。
     */
    // 隐式实例化 需要加一个 <>
    /* Box<> box4{100}; */

    Box<int> box4{100};

    /**
     * 对于 Box<int> 来说，
     * print 的参数类型是 int。
     */
    box4.print(10);

    /**
     * 调用类外实现的成员函数 print2。
     *
     * 对于 Box<int> 来说，
     * print2 的参数类型也是 int。
     */
    box4.print2(10);
}


/**
 * 作业：
 * 自定义一个栈 Stack，
 * 可以存储任意类型的数据。
 *
 * 要实现的常见操作：
 *
 * 1. push：入栈
 * 2. pop：出栈
 * 3. isEmpty：判断栈是否为空
 * 4. isFull：判断栈是否已满
 * 5. top：获取栈顶元素
 *
 *
 * 这里 Stack 使用了两个模板参数：
 *
 * 1. typename T = int
 *
 *    类型参数 T，
 *    默认值是 int。
 *
 *    如果写：
 *    Stack<> s;
 *
 *    就表示：
 *    Stack<int, 10> s;
 *
 *
 * 2. int Capacity = 10
 *
 *    非类型模板参数 Capacity，
 *    默认值是 10。
 *
 *    它表示栈的容量。
 *
 *    Capacity 必须是编译期常量。
 */
template<typename T = int, int Capacity = 10>
class Stack
{
public:
    /**
     * 构造函数。
     *
     * new T[Capacity]：
     * 在堆区申请一个 T 类型数组，
     * 数组容量是 Capacity。
     *
     * 例如：
     * Stack<double, 20> s;
     *
     * T = double
     * Capacity = 20
     *
     * 会申请：
     * new double[20]
     */
    Stack()
    : m_p(new T[Capacity])
    {}

    /**
     * 这里还没有完整实现栈的功能。
     *
     * 后续可以补充：
     *
     * 析构函数：
     * 释放 m_p 指向的数组资源。
     *
     * push：
     * 向栈中加入元素。
     *
     * pop：
     * 移除栈顶元素。
     *
     * isEmpty：
     * 判断 m_size 是否为 0。
     *
     * isFull：
     * 判断 m_size 是否等于 Capacity。
     *
     * top：
     * 返回栈顶元素。
     */
    // ~Stack()
    // push
    // pop
    // isEmpty
    // isFull
    // top

private:
    /**
     * 指向堆区数组的指针。
     *
     * 数组中存储 T 类型数据。
     */
    T * m_p;

    /**
     * 当前栈中已有元素个数。
     *
     * 注意：
     * 当前构造函数中没有初始化 m_size。
     *
     * 更规范的写法应该是：
     * Stack()
     * : m_p(new T[Capacity])
     * , m_size(0)
     * {}
     */
    int m_size;
};


// STL：std::array 静态数组
void test4()
{
    /**
     * std::array 是标准库中的类模板。
     *
     * 它表示一个固定大小的数组。
     *
     * 语法：
     * array<元素类型, 元素个数> 数组名;
     *
     * 例如：
     * array<int, 5> arr;
     *
     * 表示：
     * arr 是一个可以存放 5 个 int 的静态数组。
     *
     *
     * 注意：
     * std::array 的第二个模板参数 5
     * 是非类型模板参数。
     *
     * 它表示数组大小，
     * 必须在编译期确定。
     */
    array<int, 5> arr{1, 2, 3, 4, 5};

    /**
     * 使用下标访问元素。
     *
     * arr[0] 表示第 1 个元素。
     * arr[4] 表示第 5 个元素。
     *
     * 注意：
     * operator[] 不做越界检查。
     */
    cout << arr[0] << endl;
    cout << arr[1] << endl;
    cout << arr[2] << endl;
    cout << arr[3] << endl;
    cout << arr[4] << endl;

    cout << "---------" << endl;

    /**
     * size()
     *
     * 返回 array 中元素的个数。
     *
     * 对于 array<int, 5> 来说，
     * size() 返回 5。
     */
    cout << arr.size() << endl;

    cout << "---------" << endl;

    /**
     * front()
     *
     * 返回第一个元素。
     *
     * 对于当前数组，
     * front() 返回 1。
     */
    cout << arr.front() << endl;

    cout << "---------" << endl;

    /**
     * back()
     *
     * 返回最后一个元素。
     *
     * 对于当前数组，
     * back() 返回 5。
     */
    cout << arr.back() << endl;
}


int main(int argc, char *argv[])
{
    // 测试只能管理 Data 资源的普通 MiddleLayer
    /* test1(); */

    // 测试自定义类模板 Box
    /* test3(); */

    // 测试标准库类模板 std::array
    test4();
    
    return 0;
}