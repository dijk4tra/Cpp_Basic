#include <iostream>

using std::cout;
using std::endl;

/**
 * 多继承下，子类对象的创建和销毁过程：
 *
 * 创建子类对象时：
 * 1. 按照继承列表中的声明顺序，依次调用各个父类的构造函数；
 * 2. 再调用子类自己的构造函数。
 *
 * 销毁子类对象时：
 * 1. 先调用子类自己的析构函数；
 * 2. 再按照构造顺序的相反顺序，依次调用父类的析构函数。
 *
 * 总结：
 * 构造顺序：先父类，后子类；
 * 析构顺序：先子类，后父类；
 * 多个父类之间的构造顺序，由继承列表中的声明顺序决定。
 */

class Father1
{
public:
    Father1()
    {
        cout << "Father1()" << endl;
    }

    ~Father1()
    {
        cout << "~Father1()" << endl;
    }

    double m_f1 = 1;
};

class Father2
{
public:
    Father2()
    {
        cout << "Father2()" << endl;
    }

    ~Father2()
    {
        cout << "~Father2()" << endl;
    }

    double m_f2 = 2;
};

// 多继承
// Son 先继承 Father1，再继承 Father2，
// 因此构造时先调用 Father1()，再调用 Father2()。
class Son
: public Father1
, public Father2
{
public:
    Son()
    {
        cout << "Son()" << endl;
    }

    ~Son()
    {
        cout << "~Son()" << endl;
    }

    double m_s = 3;
};

void test1()
{
    Son son;

    cout << son.m_s << endl;
    cout << son.m_f1 << endl;
    cout << son.m_f2 << endl;

    /*
     * Son 对象中包含：
     * 1. Father1 子对象：double m_f1，通常占 8B；
     * 2. Father2 子对象：double m_f2，通常占 8B；
     * 3. Son 自己的成员：double m_s，通常占 8B。
     *
     * 因此 sizeof(son) 通常为 24B。
     */
    cout << sizeof(son) << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}