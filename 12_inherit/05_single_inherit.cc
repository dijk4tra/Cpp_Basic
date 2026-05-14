#include <iostream>

using std::cout;
using std::endl;

/**
 * 单继承下，子类对象的创建和销毁过程：
 *
 * 创建子类对象时：
 * 1. 先调用父类构造函数；
 * 2. 再调用子类构造函数。
 *
 * 销毁子类对象时：
 * 1. 先调用子类析构函数；
 * 2. 再调用父类析构函数。
 *
 * 总结：
 * 构造顺序：先父后子
 * 析构顺序：先子后父
 */

class Father
{
public:
    // 父类无参构造函数
    // 如果子类构造函数没有显式调用父类构造函数，
    // 默认会调用父类的无参构造函数。
    Father()
    {
        cout << "Father()" << endl;
    }

    // 父类有参构造函数
    Father(int f)
    : m_f(f)
    {
        cout << "Father(int)" << endl;
    }

    // 父类析构函数
    ~Father()
    {
        cout << "~Father()" << endl;
    }

    int m_f = 1;
};

class Son : public Father
{
public:
    // 子类无参构造函数
    // 这里没有显式调用父类构造函数，
    // 因此会默认调用 Father()。
    Son()
    {
        cout << "Son()" << endl;
    }

    // 子类有参构造函数
    // 通过初始化列表显式调用父类的有参构造函数，
    // 同时初始化子类自己的成员变量 m_s。
    Son(int f, int s)
    : Father(f)
    , m_s(s)
    {
        cout << "Son(int, int)" << endl;
    }

    // 子类析构函数
    ~Son()
    {
        cout << "~Son()" << endl;
    }

    int m_s = 2;
};

void test1()
{
    Son son;

    cout << son.m_f << endl;
    cout << son.m_s << endl;

    cout << sizeof(son) << endl; // 通常为 8B，包含两个 int 成员

    /*
     * 子类对象中包含两部分：
     * 1. 从父类继承来的成员；
     * 2. 子类自己定义的成员。
     *
     * 这里 Son 对象中包含：
     * Father::m_f
     * Son::m_s
     */
}

// 测试子类对象的创建和销毁过程
void test2()
{
    Son son;

    cout << "--------" << endl;

    Son son2{1, 2};

    cout << "--------" << endl;

    // test2 函数结束时，局部对象 son2 和 son 会被自动销毁。
    // 局部对象的销毁顺序与创建顺序相反：
    // 先销毁 son2，再销毁 son。
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();

    return 0;
}