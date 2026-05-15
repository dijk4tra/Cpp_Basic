#include <iostream>

using std::cout;
using std::endl;

class Point
{
public:
    /*
     * 构造函数
     *
     * 创建 Point 对象时会自动调用构造函数。
     *
     * 这里使用初始化列表初始化成员变量：
     * m_x(x)
     * m_y(y)
     *
     * 注意：
     * 成员变量真正的初始化顺序，
     * 不是由初始化列表中的书写顺序决定的，
     * 而是由成员变量在类中声明的顺序决定的。
     */
    Point(int x, int y)
    : m_x(x),
      m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    /*
     * 拷贝构造函数 copy constructor
     *
     * 使用一个已经存在的 Point 对象，
     * 创建另一个新的 Point 对象时会调用拷贝构造函数。
     *
     * 参数通常写成：
     * const Point & rhs
     *
     * const：
     * 表示不会修改被拷贝的对象。
     *
     * &：
     * 表示引用传递，
     * 避免传参过程中再次发生拷贝。
     *
     * rhs：
     * right hand side，
     * 通常表示等号右边的对象，
     * 也就是被拷贝的对象。
     */
    Point(const Point & rhs)
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    {
        cout << "Point(const Point &)" << endl;
    }

    /*
     * const 成员函数
     *
     * show 函数后面加 const，
     * 表示该函数不会修改当前对象的成员变量。
     *
     * const 对象只能调用 const 成员函数。
     */
    void show() const
    {
        cout << "show() const" << endl;
    }

    /*
     * 普通成员函数
     *
     * 该 show 函数没有 const 修饰，
     * 所以它是非 const 版本的成员函数。
     *
     * 它可以和上面的 show() const 构成函数重载。
     *
     * 原因：
     * 两个函数隐含的 this 指针类型不同。
     *
     * 非 const 版本：
     * Point * const this
     *
     * const 版本：
     * const Point * const this
     *
     *
     * 调用规则：
     * 普通对象优先调用 show()。
     * const 对象只能调用 show() const。
     */
    void show()
    {
        cout << "show()" << endl;
    }

    /*
     * 析构函数 destructor
     *
     * 析构函数在对象销毁时自动调用。
     *
     * 语法：
     * ~类名()
     * {
     *     函数体
     * }
     *
     *
     * 析构函数的特点：
     *
     * 1. 函数名固定
     *    析构函数名是在类名前面加 ~。
     *
     * 2. 没有返回值
     *    不能写返回类型，连 void 也不能写。
     *
     * 3. 没有参数
     *    所以析构函数不能重载。
     *
     * 4. 一个类只能有一个析构函数
     *
     * 5. 对象销毁时自动调用
     *
     *
     * 析构函数的常见作用：
     * 释放对象生命周期内申请的资源。
     *
     * 例如：
     * 1. 释放堆内存
     * 2. 关闭文件
     * 3. 断开网络连接
     * 4. 释放数据库连接
     */
    ~Point()
    {
        cout << "~Point()" << endl;
    }

    /*
     * 普通成员函数
     *
     * print 用来打印当前 Point 对象中的坐标值。
     *
     * 这里没有修改成员变量，
     * 所以也可以设计成 const 成员函数：
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

    /**
     * operator new
     *
     * operator new 是一个特殊的函数，
     * 用来控制对象在堆区申请内存的过程。
     *
     * 当执行：
     * Point * p = new Point{1, 2};
     * 大致会发生两步：
     * 1. 调用 operator new 申请内存。
     * 2. 在申请到的内存上调用构造函数创建对象。
     *
     * 注意：
     * operator new 只负责申请内存，
     * 不负责调用构造函数。
     * 构造函数的调用是 new 表达式的后续步骤。
     *
     * 参数：
     * size_t size
     * size 表示需要申请的内存大小，
     * 通常就是 sizeof(Point)。
     *
     * 返回值：
     * void *
     * 返回申请到的堆空间首地址。
     */
    void * operator new (size_t size)
    {
        cout << "operator new" << endl;

        /*
         * operator new 底层可以使用 malloc 申请内存。
         *
         * malloc 只负责申请一块原始内存，
         * 不会调用构造函数。
         *
         * malloc 的返回值是 void *，
         * 正好符合 operator new 的返回值类型。
         */
        return malloc(size);
    }

    /**
     * operator delete
     *
     * operator delete 是一个特殊的函数，
     * 用来控制对象在堆区释放内存的过程。
     *
     * 当执行：
     * delete p;
     * 大致会发生两步：
     * 1. 调用析构函数销毁对象。
     * 2. 调用 operator delete 释放内存。
     *
     * 注意：
     * operator delete 只负责释放内存，
     * 不负责调用析构函数。
     * 析构函数的调用是 delete 表达式的前置步骤。
     *
     * 参数：
     * void * p
     * p 表示需要释放的堆空间地址。
     */
    void operator delete(void * p)
    {
        cout << "operator delete" << endl;

        /*
         * 因为 operator new 中使用 malloc 申请内存，
         * 所以 operator delete 中使用 free 释放内存。
         *
         * malloc 和 free 成对使用。
         * new 和 delete 成对使用。
         *
         * 在这里：
         * new 表达式底层调用了 operator new，
         * operator new 内部使用 malloc。
         *
         * delete 表达式底层调用了 operator delete，
         * operator delete 内部使用 free。
         */
        free(p);
    }

private:
    /*
     * 私有成员变量
     *
     * m_x 和 m_y 用来保存 Point 对象的坐标。
     *
     * private 表示类外不能直接访问这两个成员变量。
     * 类外如果想访问它们，
     * 需要通过 public 成员函数间接访问。
     */
    int m_x;
    int m_y;
};

void test1()
{
    /*
     * 使用 new 创建堆对象。
     *
     * Point * p = new Point{1, 2};
     *
     * 执行过程：
     *
     * 1. 调用 Point::operator new 申请内存。
     *    输出：
     *    operator new
     *
     * 2. 调用 Point(int, int) 构造函数创建对象。
     *    输出：
     *    Point(int,int)
     */
    Point * p = new Point{1, 2};

    /*
     * 使用 delete 释放堆对象。
     *
     * delete p;
     *
     * 执行过程：
     *
     * 1. 调用析构函数销毁对象。
     *    输出：
     *    ~Point()
     *
     * 2. 调用 Point::operator delete 释放内存。
     *    输出：
     *    operator delete
     */
    delete p;
}

/**
 * 创建栈对象和堆对象需要满足的条件
 *
 *
 * 一、创建栈对象需要什么条件？
 *
 * 需要：
 * 1. public 权限的构造函数
 * 2. public 权限的析构函数
 *
 * 原因：
 * 栈对象离开作用域时会自动销毁，
 * 编译器需要能够在类外访问析构函数。
 *
 * 如果析构函数是 private，
 * 那么类外创建栈对象会失败。
 *
 *
 * 二、创建堆对象需要什么条件？
 *
 * 需要：
 * 1. public 权限的构造函数
 * 2. 可以访问 operator new
 * 3. 可以访问 operator delete
 * 4. 通常也需要可以访问析构函数
 *
 * 原因：
 * new 表达式需要申请内存并调用构造函数。
 * delete 表达式需要调用析构函数并释放内存。
 *
 *
 * 三、只允许创建栈对象
 *
 * 做法：
 * 把 operator new 和 operator delete 设置为 private。
 *
 * 这样类外就不能使用 new 创建堆对象。
 *
 * 但是仍然可以直接创建栈对象：
 *
 * Point pt{1, 2};
 *
 *
 * 四、只允许创建堆对象
 *
 * 做法：
 * 把析构函数设置为 private。
 *
 * 这样类外不能创建栈对象。
 *
 * 原因：
 * 栈对象离开作用域时需要自动调用析构函数，
 * 但是析构函数是 private，
 * 类外无法访问。
 *
 * 注意：
 * 如果析构函数是 private，
 * 类外直接 delete p 通常也会失败。
 *
 * 这时一般会提供一个 public 的销毁函数，
 * 在类内部 delete this。
 *
 * 例如：
 *
 * void destroy()
 * {
 *     delete this;
 * }
 */

void test2()
{
    /*
     * 创建栈对象。
     *
     * pt 是栈对象，
     * 生命周期由系统自动管理。
     *
     * 创建时：
     * 自动调用构造函数。
     *
     * test2 结束时：
     * 自动调用析构函数。
     *
     *
     * 创建栈对象要求：
     * 构造函数和析构函数都能在当前作用域中访问。
     */
    Point pt{1, 2};
}

void test3()
{
    /*
     * 创建堆对象。
     *
     * new Point{1, 2}
     *
     * 执行过程：
     * 1. 调用 operator new 申请内存。
     * 2. 调用构造函数创建对象。
     *
     *
     * 注意：
     * 当前代码中只 new 了对象，
     * 但是没有 delete。
     *
     * 这会导致堆对象没有被释放，
     * 从而造成内存泄漏。
     *
     * 更完整的写法应该是：
     *
     * Point * p = new Point{1, 2};
     * delete p;
     * p = nullptr;
     */
    Point * p = new Point{1, 2};
}

int main(int argc, char *argv[])
{
    /*
     * 当前调用 test1。
     *
     * test1 中会测试：
     * 1. operator new
     * 2. 构造函数
     * 3. 析构函数
     * 4. operator delete
     *
     *
     * 预期输出顺序：
     *
     * operator new
     * Point(int,int)
     * ~Point()
     * operator delete
     */
    test1();

    return 0;
}