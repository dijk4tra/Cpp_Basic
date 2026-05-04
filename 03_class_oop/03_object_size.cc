#include <iostream>

using std::cout;
using std::endl;

/**
 * 对象的大小
 *
 * 一个对象占用多少内存，主要取决于类中的“非静态数据成员”。
 *
 * 注意：
 * 1.普通成员函数不占用对象本身的大小
 * 2.构造函数、析构函数等成员函数也不占用对象本身的大小
 * 3.对象大小主要由数据成员决定
 *
 * 例如：
 * class Point
 * {
 *     int m_x;
 *     int m_y;
 * };
 * 如果 int 占 4 个字节，
 * 那么两个 int 一共占 8 个字节，
 * 所以 Point 对象大小通常是 8。
 *
 *
 * 特殊情况：内存对齐
 *
 * 编译器为了提高 CPU 访问内存的效率，
 * 通常不会简单地把成员变量一个接一个紧密排列，
 * 而是会按照一定规则进行“内存对齐”。
 *
 * 常见规则：
 * 1. 每个成员变量通常要放在自己类型大小的整数倍地址处
 * 2. 整个对象的大小通常要是最大对齐单位的整数倍
 * 3. 成员变量的声明顺序会影响对象大小
 *
 * 例如：
 * int    通常占 4 字节，对齐单位通常是 4
 * double 通常占 8 字节，对齐单位通常是 8
 * char   通常占 1 字节，对齐单位通常是 1
 *
 * 注意：
 * 实际大小可能和平台、编译器、编译选项有关。
 */

class Point
{
public:
    // 无参构造函数
    Point()
    {
        cout << "Point()" << endl;
    }

    // 有参构造函数
    Point(int x, int y)
    : m_x(x),
      m_y(y)
    {
        cout << "Point(int, int)" << endl;
    }

    // 成员函数
    // 成员函数属于类的代码区，不会存放在每个对象内部
    // 所以 print 函数不会增加 sizeof(Point) 的大小
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

private:
    // 当前写法：
    // int 通常占 4 字节
    // 两个 int 一共 8 字节
    // 所以 sizeof(Point) 通常是 8
    int m_x;
    int m_y;


    /*
    // 如果改成下面这种：
    int m_x;
    double m_y;

    // int 占 4 字节
    // double 占 8 字节
    //
    // 内存布局通常类似：
    //
    // m_x      占 4 字节
    // padding  补 4 字节，用来让 double 按 8 字节对齐
    // m_y      占 8 字节
    //
    // 总大小：4 + 4 + 8 = 16
    //
    // 所以 sizeof(Point) 通常是 16
    */
};

void test1()
{   
    // 创建 Point 对象
    // 会先调用无参构造函数 Point()
    Point pt;
    cout << sizeof(pt) << endl; // int_int --> 8
                                // int_double --> 16
}

class C
{   
    // C 的成员声明顺序：
    //
    // int    m_c1;  4 字节
    // int    m_c2;  4 字节
    // double m_c3;  8 字节
    //
    // 内存布局通常是：
    //
    // 偏移 0 ~ 3   : m_c1
    // 偏移 4 ~ 7   : m_c2
    // 偏移 8 ~ 15  : m_c3
    //
    // 最大对齐单位是 double 的 8 字节
    // 总大小 16 正好是 8 的整数倍
    //
    // 所以 sizeof(C) 通常是 16
    int m_c1;
    int m_c2;
    double m_c3;
};

class D
{   
    // D 的成员声明顺序：
    //
    // int    m_d1;  4 字节
    // double m_d2;  8 字节
    // int    m_d3;  4 字节
    //
    // 内存布局通常是：
    //
    // 偏移 0 ~ 3   : m_d1
    // 偏移 4 ~ 7   : padding，补 4 字节
    // 偏移 8 ~ 15  : m_d2
    // 偏移 16 ~ 19 : m_d3
    // 偏移 20 ~ 23 : padding，补 4 字节
    //
    // 为什么最后还要补 4 字节？
    //
    // 因为整个对象大小要是最大对齐单位的整数倍。
    // D 中最大对齐单位是 double 的 8 字节。
    //
    // 20 不是 8 的整数倍，
    // 所以要补到 24。
    //
    // 所以 sizeof(D) 通常是 24
    int m_d1;
    double m_d2;
    int m_d3;
};

void test2()
{
    C c;
    D d;

    // C 的成员顺序比较合理：
    // int + int + double
    // 两个 int 可以刚好凑成 8 字节，
    // double 直接从 8 字节对齐的位置开始放
    cout << sizeof(c) << endl; // 16

    // D 的成员顺序是：
    // int + double + int
    // 中间和末尾都会产生 padding，
    // 所以对象更大。
    cout << sizeof(d) << endl; // 24
}

class E
{   
    // E 的成员声明顺序：
    //
    // double m_e;       8 字节
    // char m_eArr[20]; 20 字节
    // double m_e1;      8 字节
    // int m_e2;         4 字节
    //
    // 注意：
    // char 数组本身的每个元素对齐单位是 1，
    // 但是数组整体仍然会占据连续的 20 字节。
    //
    // E 中最大对齐单位通常仍然是 double 的 8 字节。
    //
    // 内存布局通常是：
    //
    // 偏移 0 ~ 7    : m_e
    // 偏移 8 ~ 27   : m_eArr[20]
    // 偏移 28 ~ 31  : padding，补 4 字节，让下一个 double 对齐到 8 的倍数地址
    // 偏移 32 ~ 39  : m_e1
    // 偏移 40 ~ 43  : m_e2
    // 偏移 44 ~ 47  : padding，补 4 字节，让整个对象大小是 8 的整数倍
    //
    // 所以 sizeof(E) 通常是 48
    double m_e;
    char m_eArr[20];
    double m_e1;
    int m_e2;
};

class F
{   
    // F 中只有一个 char 数组
    //
    // char m_fArr[20] 占 20 字节
    //
    // 因为没有 double、int 等更大对齐要求的成员，
    // char 的对齐单位通常是 1。
    //
    // 所以 sizeof(F) 通常就是 20
    char m_fArr[20];
};

class G
{
    // 空类
    //
    // 类中没有任何数据成员。
    //
    // 但是 C++ 规定：
    // 即使是空类，也要保证每个对象都有唯一地址。
    //
    // 如果空对象大小是 0，
    // 那么多个空对象可能会拥有相同地址，
    // 这不符合对象模型的要求。
    //
    // 所以空类对象的大小通常是 1 字节。
};

void test3()
{
    E e;
    F f;
    cout << sizeof(e) << endl;// 48
    cout << sizeof(f) << endl;// 20
    G g;
    cout << sizeof(g) << endl;// 空对象大小为1
}


int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

