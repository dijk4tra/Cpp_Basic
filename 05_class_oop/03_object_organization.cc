#include <iostream>

using std::cout;
using std::endl;

/**
 * const 成员函数的调用规则
 *
 * 如果类中同时存在 const 版本和非 const 版本的成员函数：
 *
 * 1. 普通对象
 *    优先调用非 const 版本的成员函数。
 *
 * 2. const 对象
 *    只能调用 const 版本的成员函数。
 *
 *
 * 如果类中只有非 const 版本的成员函数：
 *
 * 1. 普通对象
 *    可以调用非 const 版本的成员函数。
 *
 * 2. const 对象
 *    不能调用非 const 版本的成员函数。
 *
 * 原因：
 * 非 const 成员函数中的 this 指针类型是：
 * Point * const this
 *
 * const 对象调用成员函数时，
 * this 指针应该具有只读属性：
 * const Point * const this
 *
 * 两者类型不匹配，
 * 所以 const 对象不能调用非 const 成员函数。
 *
 *
 * 如果类中只有 const 版本的成员函数：
 *
 * 1. 普通对象
 *    可以调用 const 成员函数。
 *
 * 2. const 对象
 *    也可以调用 const 成员函数。
 *
 * 原因：
 * const 成员函数承诺不修改对象状态，
 * 所以普通对象和 const 对象调用它都是安全的。
 */

class Point
{
public:
    /*
     * 构造函数
     *
     * 创建 Point 对象时调用。
     *
     * 这里使用初始化列表初始化成员变量：
     * m_x(x)
     * m_y(y)
     *
     * 初始化列表的执行顺序不是由书写顺序决定的，
     * 而是由成员变量在类中声明的顺序决定的。
     */
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    /*
     * 拷贝构造函数 copy constructor
     *
     * 使用一个已经存在的 Point 对象，
     * 创建一个新的 Point 对象时会调用拷贝构造函数。
     *
     * 参数一般写成 const Point & rhs。
     *
     * const：
     * 表示在拷贝过程中不会修改 rhs 对象。
     *
     * 引用 &：
     * 避免传参时再次发生拷贝。
     *
     * rhs：
     * right hand side，通常表示等号右边的对象，
     * 也就是被拷贝的对象。
     */
    Point(const Point & rhs)
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    {
        cout << "Point(const Point &)" << endl;
    }

    /*
     * 普通成员函数
     *
     * print 不是 const 成员函数。
     *
     * 因此：
     * 普通对象可以调用 print。
     * const 对象不能调用 print。
     *
     * 如果希望 const 对象也能打印坐标，
     * 可以将该函数改成：
     *
     * void print() const
     * {
     *     cout << m_x << " " << m_y << endl;
     * }
     */
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

    /*
     * const 成员函数
     *
     * show 函数后面加了 const，
     * 表示该函数不会修改当前对象的状态。
     *
     * 因此：
     * 普通对象可以调用 show。
     * const 对象也可以调用 show。
     */
    void show() const
    {
        cout << "show() const" << endl;
    }

    /*
     * 如果再提供一个非 const 版本的 show，
     * 那么它可以和上面的 const show 构成重载。
     *
     * void show();
     * void show() const;
     *
     * 它们的区别在于隐含的 this 指针类型不同。
     *
     * 非 const 版本：
     * Point * const this
     *
     * const 版本：
     * const Point * const this
     *
     *
     * 调用规则：
     * 普通对象优先调用非 const 版本。
     * const 对象只能调用 const 版本。
     */
    /* void show() */
    /* { */
    /*     cout << "show()" << endl; */
    /* } */

/* private: */
    /*
     * 坐标成员变量
     *
     * m_x 和 m_y 用来表示 Point 对象的两个坐标值。
     *
     * 这里 private 被注释掉了，
     * 所以 m_x 和 m_y 当前仍然是 public 成员。
     *
     * 如果取消 private 注释，
     * 外部就不能直接访问 m_x 和 m_y，
     * 只能通过成员函数间接访问。
     */
    int m_x;
    int m_y;
};

void test1()
{
    /*
     * 普通变量和 const 变量对比
     *
     * num 是普通变量，可以修改。
     * num2 是 const 变量，初始化后不能修改。
     */
    int num = 1;
    const int num2 = 2;

    /*
     * pt 是普通对象。
     *
     * 如果 Point 中同时存在：
     * show()
     * show() const
     *
     * 那么普通对象 pt 会优先调用非 const 版本。
     *
     * 当前代码中只有 show() const，
     * 所以普通对象 pt 调用 const 版本。
     */
    Point pt{1, 2};
    pt.show();

    cout << "--------" << endl;

    /*
     * pt2 是 const 对象。
     *
     * const 对象只能调用 const 成员函数。
     *
     * 因此：
     * pt2.show(); 可以调用。
     *
     * 如果 show 只有非 const 版本，
     * 那么 pt2.show(); 会报错。
     */
    const Point pt2{3, 4};
    pt2.show();
}

/**
 * 对象数组
 *
 * 对象数组就是数组中的每一个元素都是对象。
 *
 * 构建对象数组的常见形式：
 *
 * 1. 通过左值对象构建数组
 *    Point pts[3] = { pt1, pt2, pt3 };
 *
 * 2. 通过右值对象构建数组
 *    Point pts[] = {
 *        Point{1, 1},
 *        Point{2, 2},
 *        Point{3, 3}
 *    };
 *
 * 3. 通过初始化列表简写构建数组
 *    Point pts[] = {
 *        {1, 1},
 *        {2, 2},
 *        {3, 3}
 *    };
 */

void test2()
{
    /*
     * 普通数组的初始化形式：
     *
     * int arr[3] = {1, 2, 3};
     *
     * 对象数组的初始化形式和普通数组类似，
     * 只是数组中的元素变成了对象。
     */

    /*
     * 创建三个 Point 对象。
     *
     * pt1、pt2、pt3 都是已经有名字的对象，
     * 所以它们都是左值对象。
     */
    Point pt1{ 1, 1 };
    Point pt2{ 2, 2 };
    Point pt3{ 3, 3 };

    /*
     * 使用左值对象构建对象数组。
     *
     * pt1、pt2、pt3 已经是存在的对象。
     * 再用它们初始化数组元素时，
     * 数组中的每个元素都需要根据已有对象进行拷贝构造。
     *
     * 因此这里会调用拷贝构造函数。
     */
    Point pts[3] = { pt1, pt2, pt3 };

    /*
     * 因为当前 m_x 是 public，
     * 所以可以直接访问：
     *
     * pts[0].m_x = 10;
     *
     * 但是通常不建议把数据成员暴露为 public。
     * 更推荐使用 private 成员变量，
     * 再提供 public 成员函数进行访问和修改。
     */
    /* pts[0].m_x = 10; */

    /*
     * 访问数组中的第 0 个对象，
     * 并调用它的 print 成员函数。
     */
    pts[0].print();
}

/*
 * 使用右值对象构建对象数组
 *
 * Point{1, 1} 是临时对象，
 * 没有名字，属于右值对象。
 */
void test3()
{
    /*
     * 使用右值对象初始化数组元素。
     *
     * 每个 Point{...} 都会直接构造一个 Point 对象。
     *
     * 在现代 C++ 中，
     * 编译器通常会进行优化，
     * 避免不必要的拷贝。
     */
    Point pts[] = {
        Point{ 1, 1 },
        Point{ 2, 2 },
        Point{ 3, 3 }
    };

    /*
     * 打印对象数组中第一个元素。
     */
    pts[0].print();
}

void test4()
{
    /*
     * 使用初始化列表进行简写。
     *
     * 下面这种写法等价于：
     *
     * Point pts[] = {
     *     Point{1, 1},
     *     Point{2, 2},
     *     Point{3, 3}
     * };
     *
     * 因为数组元素类型是 Point，
     * 所以编译器会根据 {1, 1} 自动调用：
     *
     * Point(int, int)
     */
    Point pts[] = {
        { 1, 1 },
        { 2, 2 },
        { 3, 3 }
    };

    /*
     * 打印数组第 0 个元素。
     */
    pts[0].print();

    cout << "----->" << endl;

    /*
     * 普通 for 循环遍历对象数组。
     *
     * i 是数组下标，
     * pts[i] 表示访问数组中的第 i 个对象。
     *
     * 这种方式不会产生额外对象，
     * 直接使用数组中的原对象调用 print。
     */
    for(int i = 0; i < 3; ++i){
        pts[i].print();
    }

    cout << "----->" << endl;

    /*
     * foreach 遍历，也叫增强 for 循环或者范围 for 循环。
     *
     * 语法：
     * for(元素类型 变量名 : 容器或数组)
     * {
     *     循环体
     * }
     *
     *
     * 注意：
     * 这里的 Point pt 是值传递。
     *
     * 每次循环时，
     * 都会将数组中的当前元素拷贝一份给 pt，
     * 因此会调用拷贝构造函数。
     *
     * pt 是数组元素的副本，
     * 修改 pt 不会影响数组中的原对象。
     */
    for(Point pt : pts){
        pt.print();
    }

    cout << "----->" << endl;

    /*
     * auto 关键字
     *
     * auto 可以根据右边的初始化内容，
     * 自动推导变量类型。
     *
     * 在这里：
     * auto pt : pts
     *
     * 编译器会推导出 pt 的类型是 Point。
     *
     * 所以这段代码等价于：
     *
     * for(Point pt : pts)
     *
     * 注意：
     * 这里仍然是值传递，
     * 每次循环都会拷贝数组元素。
     */
    for(auto pt : pts){
        pt.print();
    }

    cout << "----->" << endl;

    /*
     * 使用引用遍历对象数组。
     *
     * auto & pt 表示 pt 是数组元素的引用，
     * 不是数组元素的副本。
     *
     * 好处：
     * 1. 不会调用拷贝构造函数。
     * 2. 效率更高。
     * 3. 可以通过 pt 修改数组中的原对象。
     *
     * 如果只想读取，不想修改，
     * 可以写成：
     *
     * for(const auto & pt : pts)
     *
     * 这样既避免拷贝，
     * 又能防止误修改数组元素。
     */
    for(auto & pt : pts){
        pt.print();
    }
}

/**
 * 栈对象和堆对象
 *
 * C++ 中对象可以创建在栈区，
 * 也可以创建在堆区。
 *
 *
 * 1. 栈对象
 *
 * 语法：
 * 类名 对象名{参数};
 *
 * 例如：
 * Point pt1{1, 1};
 *
 * 特点：
 * 栈对象由系统自动管理生命周期。
 * 当对象所在作用域结束时，
 * 对象会自动销毁。
 *
 *
 * 2. 堆对象
 *
 * 语法：
 * 类名 * 指针名 = new 类名{参数};
 *
 * 例如：
 * Point * p2 = new Point{1, 2};
 *
 * 特点：
 * 堆对象由程序员手动管理生命周期。
 * 使用 new 创建，
 * 必须使用 delete 释放。
 *
 * 如果 new 之后忘记 delete，
 * 就会造成内存泄漏。
 */

void test5()
{
    /*
     * 栈对象
     *
     * pt1 是创建在栈区上的对象。
     *
     * 当 test5 函数执行结束时，
     * pt1 会自动销毁。
     */
    Point pt1{1, 1};

    /*
     * 对象访问成员使用 . 运算符。
     *
     * 语法：
     * 对象.成员
     */
    pt1.print();

    /*
     * p 是指针变量，
     * 保存的是 pt1 对象的地址。
     *
     * &pt1 表示取 pt1 的地址。
     */
    Point* p = &pt1;

    /*
     * 指针访问成员使用 -> 运算符。
     *
     * 语法：
     * 指针->成员
     *
     * p->print();
     *
     * 等价于：
     * (*p).print();
     */
    p->print();

    /*
     * 堆对象
     *
     * 使用 new 在堆区创建对象。
     *
     * new Point{1, 2}
     *
     * 会完成两件事：
     * 1. 在堆区申请内存。
     * 2. 调用 Point(int, int) 构造函数创建对象。
     *
     * new 表达式的返回值是对象的地址，
     * 所以需要使用 Point* 类型的指针接收。
     */
    Point * p2 = new Point{ 1, 2 };

    /*
     * p2 是指针，
     * 所以通过 -> 调用成员函数。
     */
    p2->print();

    /*
     * delete 用来释放 new 创建的堆对象。
     *
     * delete p2 会完成两件事：
     * 1. 调用对象的析构函数。
     * 2. 释放对象占用的堆内存。
     */
    delete p2;

    /*
     * delete 之后，
     * p2 指针中原来保存的地址已经失效。
     *
     * 这个时候 p2 称为空悬指针或者野指针。
     *
     * 为了避免误用，
     * 通常在 delete 之后将指针置空。
     */
    p2 = nullptr;
}

int main(int argc, char * argv[])
{
    /*
     * 当前只调用 test5。
     *
     * 其他测试函数被注释掉了，
     * 可以根据需要取消注释进行测试。
     */
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    test5();

    return 0;
}


/*
#include <iostream>

using std::cout;
using std::endl;

class Point
{
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    Point(const Point & rhs)
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    {
        cout << "Point(const Point &)" << endl;
    }

    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

    void show() const
    {
        cout << "show() const" << endl;
    }

    // void show()
    // {
    //     cout << "show()" << endl;
    // }

    int m_x;
    int m_y;
};

void test1()
{
    int num = 1;
    const int num2 = 2;

    Point pt{1, 2};
    pt.show();

    cout << "--------" << endl;

    const Point pt2{3, 4};
    pt2.show();
}

void test2()
{
    Point pt1{1, 1};
    Point pt2{2, 2};
    Point pt3{3, 3};

    Point pts[3] = { pt1, pt2, pt3 };

    // pts[0].m_x = 10;
    pts[0].print();
}

void test3()
{
    Point pts[] = {
        Point{1, 1},
        Point{2, 2},
        Point{3, 3}
    };

    pts[0].print();
}

void test4()
{
    Point pts[] = {
        {1, 1},
        {2, 2},
        {3, 3}
    };

    pts[0].print();

    cout << "----->" << endl;

    for(int i = 0; i < 3; ++i){
        pts[i].print();
    }

    cout << "----->" << endl;

    for(Point pt : pts){
        pt.print();
    }

    cout << "----->" << endl;

    for(auto pt : pts){
        pt.print();
    }

    cout << "----->" << endl;

    for(auto & pt : pts){
        pt.print();
    }
}

void test5()
{
    Point pt1{1, 1};
    pt1.print();

    Point * p = &pt1;
    p->print();

    Point * p2 = new Point{1, 2};
    p2->print();

    delete p2;
    p2 = nullptr;
}

int main(int argc, char * argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();

    return 0;
}
*/