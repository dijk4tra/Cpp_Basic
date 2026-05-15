#include <iostream>

using std::cout;
using std::endl;


/**
 * 嵌套类的使用场景：
 *
 * 如果一个类只为另一个类服务，
 * 并且不希望暴露在外部作用域中，
 * 就可以把它定义成外部类的内部类。
 *
 * 这里的例子：
 *
 * Line 表示一条线段。
 * Point 表示线段上的点。
 *
 * Point 主要是为了 Line 服务，
 * 外界不需要直接使用 Point，
 * 所以可以把 Point 定义在 Line 的内部。
 *
 * 可以类比成：
 * 外部类 Line 是“寄居蟹的壳”，
 * 内部类 Point 是“寄居蟹”。
 *
 * Point 被放在 Line 的内部，
 * 表示 Point 依附于 Line 这个作用域存在。
 */


// 外部类：Line，可以理解成寄居蟹的壳
class Line
{
    /**
     * 内部类 Point。
     *
     * 因为 class 默认访问权限是 private，
     * 所以这里的 Point 是 Line 的 private 内部类。
     *
     * 类外部不能直接写：
     * Line::Point pt{1, 2};
     *
     * 这样可以隐藏 Point 的实现细节，
     * 外界只需要使用 Line。
     */
    class Point
    {
    public:
        /**
         * Point 的构造函数。
         *
         * 用 x 初始化横坐标，
         * 用 y 初始化纵坐标。
         */
        Point(int x, int y)
        : m_x(x)
        , m_y(y)
        {

        }

        /**
         * 打印 Point 对象。
         *
         * 输出当前点的横坐标和纵坐标。
         */
        void print()
        {
            cout << m_x << " " << m_y << endl;
        }

    private:
        // 点的横坐标
        int m_x;

        // 点的纵坐标
        int m_y;
    };

public:
    /**
     * 默认构造函数。
     *
     * 注意：
     * 当前 Line 中有两个 Point 成员：
     * m_pt1 和 m_pt2。
     *
     * 但是 Point 没有默认构造函数，
     * 只有 Point(int, int) 构造函数。
     *
     * 所以如果真正使用：
     * Line line;
     *
     * 会因为 m_pt1、m_pt2 无法默认构造而编译报错。
     *
     * 当前代码中 Line() = default; 写出来了，
     * 但只要不实际调用默认构造函数，
     * 就不会触发这个问题。
     */
    Line() = default;

    /**
     * Line 的有参构造函数。
     *
     * 一条线段可以由两个点确定。
     *
     * 参数说明：
     * x1, y1 表示第一个点的坐标。
     * x2, y2 表示第二个点的坐标。
     *
     * 初始化列表中：
     * m_pt1(x1, y1) 用第一个点的坐标构造 Point 对象。
     * m_pt2(x2, y2) 用第二个点的坐标构造 Point 对象。
     */
    Line(int x1, int y1, int x2, int y2)
    : m_pt1(x1,y1)
    , m_pt2(x2,y2)
    {

    }

    /**
     * 打印线段。
     *
     * Line 内部包含两个 Point 对象，
     * 所以打印 Line 时，
     * 分别调用两个 Point 对象的 print 函数。
     */
    void print()
    {
        m_pt1.print();
        m_pt2.print();
    }

private:
    /**
     * 如果打开这个 double 成员，
     * Line 对象的大小会受到成员大小和内存对齐的影响。
     */
    /* double m_data; */

    /**
     * 线段的第一个端点。
     *
     * Point 是 Line 的 private 内部类，
     * 外界不能直接使用，
     * 但是 Line 自己可以使用它定义成员对象。
     */
    Point m_pt1;

    /**
     * 线段的第二个端点。
     */
    Point m_pt2;
};

void test1()
{
    /**
     * 如果打开下面代码：
     *
     * Line line;
     *
     * 会尝试调用 Line 的默认构造函数。
     *
     * 但是 Line 的成员 m_pt1 和 m_pt2 是 Point 类型，
     * 而 Point 没有默认构造函数，
     * 所以默认构造 Line 对象会失败。
     */
    /* Line line; */

    /**
     * sizeof(line) 用来查看对象所占内存大小。
     *
     * 如果 Line 中只有两个 Point 成员，
     * 每个 Point 中有两个 int，
     * 那么通常大小为：
     *
     * 2 个 Point * 每个 Point 2 个 int
     * = 4 个 int
     *
     * 在常见平台上 int 为 4 字节，
     * 所以 Line 大小通常为 16 字节。
     *
     * 如果增加 double 成员，
     * 还要考虑内存对齐。
     */
    /* cout << sizeof(line) << endl; */

    /**
     * 创建 Line 对象。
     *
     * 传入四个参数，
     * 分别表示两个端点的坐标：
     *
     * 第一个点：1, 2
     * 第二个点：3, 4
     */
    Line line{1,2,3,4};

    /**
     * 打印线段的两个端点。
     */
    line.print();
}

int main(int argc, char * argv[])
{
    test1();

    return 0;
}