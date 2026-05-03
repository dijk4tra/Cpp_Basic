#include <iostream>

using std::cout;
using std::endl;

/**
 * 对象复制操作：复制、赋值
 * 在 C++ 中，对象之间常见的复制操作有两类：
 * 1. 拷贝构造
 *    用一个已经存在的对象，创建一个新的对象。
 *    例如：
 *    Point pt1{1, 2};
 *    Point pt2 = pt1;
 *    Point pt3{pt1};
 *    pt2 和 pt3 都是新对象，
 *    它们是通过 pt1 拷贝构造出来的。
 *
 * 2. 赋值操作
 *    两个对象都已经存在，然后把一个对象的内容赋给另一个对象。
 *    例如：
 *    Point pt1{1, 2};
 *    Point pt2{3, 4};
 *    pt2 = pt1;
 *    这里不是拷贝构造，而是赋值操作。
 *
 *
 * 拷贝构造函数 copy constructor：
 * 可以理解成：
 * 参数是“同类型对象的 const 引用”的构造函数。
 *
 * 语法：
 * 类名(const 类名 & rhs)
 * {
 *     构造函数体
 * }
 * 
 * 例如：
 * Point(const Point & rhs)
 * {
 *     ...
 * }
 *
 * rhs 是 right hand side 的缩写，
 * 一般表示右操作数，也就是被拷贝的那个对象。
 *
 *
 * 为什么拷贝构造函数的参数要使用 const？
 * 1. 防止在拷贝过程中修改原对象
 *    Point(const Point & rhs)
 *    const 表示 rhs 是只读的。
 *    拷贝构造函数只应该读取 rhs 的数据，
 *    不应该修改 rhs。
 * 
 * 2. 可以接收 const 对象
 *    const Point pt1{1, 2};
 *    Point pt2{pt1};
 *    如果参数不是 const Point &，
 *    就无法接收 const 对象。
 * 
 * 3. 可以绑定右值对象
 *    Point pt{Point{1, 2}};
 *    Point{1, 2} 是一个临时对象，也就是右值。
 *    const 引用可以绑定右值。
 *
 *
 * 为什么拷贝构造函数的参数要使用引用？
 * 1. 避免不必要的复制
 *    如果写成：
 *    Point(Point rhs)
 *    那么调用拷贝构造函数之前，
 *    需要先把实参拷贝一份给形参 rhs。
 * 
 * 2. 避免无限递归调用
 *    Point(Point rhs)
 *    为了生成 rhs，需要调用拷贝构造函数；
 *    调用拷贝构造函数又需要生成 rhs；
 *    生成 rhs 又需要调用拷贝构造函数……
 *    这样会无限递归。
 *    所以拷贝构造函数的参数必须使用引用。
 *
 *
 * 左值和右值：
 * 1. 左值 lvalue
 *    一般可以理解为：
 *    有名字、可以取地址、生命周期相对明确的表达式。
 *    常见左值：
 *    - 变量
 *    - 已经创建好的对象
 *    - 字符串常量
 *    例如：
 *    int a = 1;
 *    Point pt{1, 2};
 *    "hello";
 * 
 * 2. 右值 rvalue
 *    一般可以理解为：
 *    临时的、匿名的、通常不能取地址的表达式。
 *    常见右值：
 *    - 字面值常量，例如 1、2、100
 *    - 表达式计算结果，例如 b + c
 *    - 临时对象，例如 Point{1, 2}
 *
 *
 * 拷贝构造函数的调用时机：
 * 1. 用一个已经存在的对象初始化新对象
 *    Point pt1{1, 2};
 *    Point pt2 = pt1;
 *    Point pt3{pt1};
 * 
 * 2. 对象作为函数参数，并且是值传递
 *    void func(Point pt);
 *    Point p{1, 2};
 *    func(p);
 *    这里会用 p 拷贝构造形参 pt。
 * 
 * 3. 对象作为函数返回值
 *    Point func2()
 *    {
 *        Point pt{1, 2};
 *        return pt;
 *    }
 *    早期 C++ 中，这种情况可能会触发拷贝构造。
 *    但现代 C++ 编译器通常会进行返回值优化：
 *    RVO / NRVO。
 *    因此实际运行时，可能看不到拷贝构造函数被调用。
 */

class Point
{
public:
    // 有参构造函数
    Point(int x, int y)
    : m_x(x),
      m_y(y)
    {
        cout << "Point(int, int)" << endl;
    }
    
    /**
     * 拷贝构造函数 copy constructor
     *
     * 作用：
     * 使用一个已经存在的 Point 对象，
     * 初始化一个新的 Point 对象。
     *
     * 参数：
     * const Point & rhs
     * rhs 表示被拷贝的对象。
     *
     * 例如：
     * Point pt1{1, 2};
     * Point pt2{pt1};
     * 此时 rhs 引用的就是 pt1。
     */
    Point(const Point & rhs)
    : m_x(rhs.m_x),
      m_y(rhs.m_y)
    {
        cout << "Point(const Point & rhs)" << endl;
        /*
         * 注意：
         * 上面的初始化列表已经完成了成员变量初始化：
         * : m_x(rhs.m_x),
         *   m_y(rhs.m_y)
         *
         * 所以下面这两行其实是多余的。
         * 它们不是初始化，而是赋值。
         * ·构造函数初始化列表：
         *  对成员变量进行初始化。
         * ·构造函数体内部：
         *  对已经初始化好的成员变量再次赋值。
         * 对 int 来说影响不大，
         * 但对复杂类型来说，推荐只在初始化列表中完成初始化。
         */
        /* m_x = rhs.m_x; */
        /* m_y = rhs.m_y; */
    }

    // 普通成员函数
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

private:
    int m_x;
    int m_y;
};


void test1()
{
    int a = 1;
    // 用已经存在的变量 a 初始化新变量 b
    // 对于内置类型 int 来说，这是普通复制
    int b = a;

    // 创建 pt1 对象
    Point pt1{1,2};

    // 用一个已经存在的对象 pt1 初始化一个新对象 pt2
    // 这里会调用拷贝构造函数：
    // Point(const Point & rhs)
    // rhs 引用 pt1。
    /* Point pt2 = pt1; */
    // 下面这种写法和 Point pt2 = pt1; 本质上都是拷贝初始化新对象
    // 注意：
    // pt2 是一个新对象，
    // 所以调用的是拷贝构造函数，而不是赋值运算符。
    Point pt2{ pt1 };
    pt2.print();
}

// 常见的左值和右值
void test2()
{
    // 左值：可以取地址
    int a = 1;
    // 变量 a 是左值，可以取地址
    &a;
    // pt 是有名字的对象，是左值，可以取地址
    Point pt{1,2};
    &pt;
    // 一个字符串字面值，可以取地址
    &"hello";

    // 右值：通常是临时值，不能直接取地址
    // Point{3, 4} 是匿名临时对象
    // 一般把它视为右值
    /* &Point{3, 4}; */
    
    int b = 1;
    int c = 1;
    // b + c 的结果是一个临时值
    // 这个计算结果没有名字，通常不能取地址
    /* &(b + c); */

    // 100 是字面值常量，是右值，不能取地址
    /* &100; */
}

void test3()
{
    int num = 1;
    
    // 非const的引用可以绑定左值
    int & ref = num;
    
    // 非const的引用不可以绑定右值
    /* int & ref2 = 1; //error */
    
    // const的引用可以绑定左值,也可以绑定右值
    // ref3 引用 num，
    // 但是不能通过 ref3 修改 num
    const int & ref3 = num;
    // const 的引用也可以绑定右值
    // 编译器会临时创建一个对象保存 1，
    // 然后让 ref4 引用这个临时对象。
    // 这个临时对象的生命周期会延长到 ref4 的生命周期结束。
    const int & ref4 = 1;
}

// 测试拷贝构造函数的参数接收右值对象
void test4()
{
    /*
    Point pt1{1, 2};
    // 用左值对象 pt1 初始化新对象 pt
    // 会调用拷贝构造函数。
    Point pt{pt1};
    */
    
    /** 
     * Point{1, 2} 是一个匿名临时对象，也就是右值。
     * Point pt{ Point{1, 2} };
     * 理论上可以理解为：
     * 1. 先创建临时对象 Point{1, 2}
     * 2. 再用这个临时对象拷贝构造 pt
     *
     * 所以如果拷贝构造函数写成：
     * Point(Point & rhs)
     * 就不能接收这个右值对象。
     * 因为非 const 左值引用不能绑定右值。
     *
     * 写成：
     * Point(const Point & rhs)
     * 就可以接收右值对象。
     *
     * 注意：
     * 在现代 C++ 中，这里很可能发生拷贝省略。
     * 也就是说，编译器可能直接构造 pt，
     * 不一定真的调用拷贝构造函数。
     */
    Point pt { Point{1, 2} };
}


/**
 * 如果函数参数写成 Point & pt：
 * void func(Point & pt)
 * {
 *     pt.print();
 * }
 * 这是引用传递，不会产生对象复制。
 * 形参 pt 是实参对象的别名。
 *
 * 如果函数参数写成 const Point & pt：
 * void func(const Point & pt)
 * {
 *     pt.print();
 * }
 * 也不会产生对象复制，
 * 并且可以接收 const 对象和临时对象。
 * 实际开发中，如果函数只读取对象，通常推荐使用 const 引用。
 */
// 当前写法是值传递：
void func(Point pt)
{
    // 这里的 pt 是一个新的对象，
    // 是由调用者传入的对象拷贝构造出来的
    pt.print();
}

// 验证拷贝构造的调用时机
void test5()
{   
    // p 作为函数参数传递给 func
    // 而且是值传递
    // 所以会用 p 拷贝构造形参 pt，
    // 调用 Point(const Point & rhs)
    Point p{1, 2};
    func(p);
}

// 返回一个 Point 对象
Point func2()
{
    Point pt{1, 2};
    /**
     * 返回对象 pt
     * 理论上：
     * 返回时可能会用 pt 拷贝构造一个临时返回对象。
     * 但是现代 C++ 编译器通常会进行 NRVO：
     * Named Return Value Optimization
     * 命名返回值优化
     * 编译器可能会直接在调用者的存储空间中构造 pt，
     * 从而避免拷贝构造。
     *
     * 所以你运行时可能只看到：
     * Point(int, int)
     * 而看不到：    
     * Point(const Point &)
     */
    return pt;
}

void test6()
{   
    // 用 func2() 的返回值初始化 pt1
    // func2() 返回的是一个临时对象，属于右值。
    // 理论上可能调用拷贝构造。
    // 但是现代 C++ 中，返回值优化经常会省略拷贝。
    // 所以这行代码不一定会输出拷贝构造函数的信息。
    Point pt1 = func2();
}


int main(int argc, char *argv[])
{
    // 用一个已经存在的对象初始化新对象时调用拷贝构造
    /* test1(); */

    // 对象作为函数参数，且参数是值传递时调用拷贝构造
    /* test5(); */

    // 对象作为函数返回值时，理论上可能调用拷贝构造，
    // 但现代编译器可能进行返回值优化
    test6();
    
    return 0;
}

