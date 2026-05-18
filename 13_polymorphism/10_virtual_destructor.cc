#include <iostream>
#include <ostream>

using std::cout;
using std::endl;

/**
 * 析构函数：destructor，常简称为 dtor。
 *
 * 虚析构函数：
 * 使用 virtual 修饰的析构函数，称为虚析构函数。
 *
 * 为什么父类析构函数通常要写成虚析构函数？
 *
 * 当存在以下情况时：
 * 1. 父类指针指向子类对象；
 * 2. 通过父类指针 delete 对象；
 * 3. 父类和子类中都涉及资源管理，例如动态内存分配。
 *
 * 如果父类析构函数不是虚析构函数，
 * 通过父类指针 delete 子类对象时，
 * 子类析构函数可能不会被正确调用，
 * 子类中申请的资源就无法释放，可能造成内存泄漏。
 *
 * 解决方案：
 * 将父类析构函数定义为虚析构函数。
 *
 * 当父类析构函数是虚函数时，
 * 析构函数会参与虚函数机制。
 * 通过父类指针 delete 子类对象时，
 * 会先调用子类析构函数，
 * 再自动调用父类析构函数，
 * 从而保证对象的资源被完整释放。
 */

class Father
{
public:
    Father()
    : m_f(new int{1})
    {
        cout << "Father constructor" << endl;
    }

    virtual // 虚析构函数
    ~Father()
    {
        cout << "~Father()" << endl;
        delete m_f;
    }

    /* virtual void func(); */

    int * m_f;
};

class Son : public Father
{
public:
    Son()
    : m_s(new int{2})
    {
        cout << "Son constructor" << endl;
    }

    ~Son()
    {
        cout << "~Son()" << endl;
        delete m_s;
    }

    int * m_s;
};

void test1()
{
    // 栈对象
    /* Son son; */
    /* cout << sizeof(son) << endl; */

    // 栈对象生命周期结束时，
    // 析构顺序是：先调用子类析构函数，再调用父类析构函数。

    // 堆对象
    /* Son * s = new Son{}; */

    // 父类指针指向子类对象，属于多态场景中常见的写法。
    Father * f = new Son{};

    // sizeof(*f) 的结果由表达式的静态类型决定。
    // 这里 f 的类型是 Father*，所以 *f 的静态类型是 Father，
    // 因此这里得到的是 Father 类型的大小，而不是 Son 类型的大小。
    cout << sizeof(*f) << endl;

    // 通过父类指针释放子类对象。
    //
    // 如果 Father 的析构函数不是虚析构函数，
    // delete f 时子类析构函数可能不会被正确调用，
    // Son 中的 m_s 可能无法释放。
    //
    // 当前代码中 Father 的析构函数已经声明为 virtual，
    // 因此 delete f 时会先调用 Son::~Son()，
    // 再调用 Father::~Father()。
    delete f;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}