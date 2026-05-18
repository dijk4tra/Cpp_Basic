#include <iostream>
#include <ostream>

using std::cout;
using std::endl;

/**
 * 析构函数 destructor：
 * 对象销毁时自动调用的特殊成员函数，
 * 通常用来释放对象占用的资源。
 *
 *
 * 虚析构函数 virtual destructor：
 * 使用 virtual 修饰的析构函数。
 *
 * 语法：
 * virtual ~类名()
 * {
 * }
 *
 *
 * 为什么需要虚析构函数？
 *
 * 如果一个类作为多态基类使用，
 * 也就是可能出现下面这种写法：
 *
 * Father * f = new Son{};
 * delete f;
 *
 * 那么 Father 的析构函数应该写成 virtual。
 *
 *
 * 如果父类析构函数不是虚函数：
 *
 * Father * f = new Son{};
 * delete f;
 *
 * 通过父类指针 delete 子类对象时，
 * 子类析构函数可能不会被正确调用。
 *
 * 这样会导致：
 * 1. Son 中的资源没有释放
 * 2. 只释放了 Father 中的资源
 * 3. 造成内存泄漏
 *
 * 更准确地说：
 * 通过没有虚析构函数的父类指针删除子类对象，
 * 在 C++ 中属于未定义行为 undefined behavior。
 *
 *
 * 如果父类析构函数是虚函数：
 *
 * delete f;
 *
 * 会先调用子类析构函数：
 * ~Son()
 *
 * 然后自动调用父类析构函数：
 * ~Father()
 *
 * 这样父类和子类中的资源都能被正确释放。
 *
 *
 * 结论：
 * 如果一个类中有虚函数，
 * 并且这个类可能作为父类使用，
 * 通常建议把析构函数写成虚析构函数。
 */

class Father
{
public:
    /**
     * Father 构造函数。
     *
     * 构造 Father 对象时，
     * 会在堆区动态申请一个 int，
     * 并让 m_f 指向这块空间。
     *
     * m_f(new int{1})
     *
     * 表示：
     * 1. 在堆区申请一个 int 空间
     * 2. 使用 1 初始化这个 int
     * 3. 将申请到的地址保存到 m_f 中
     */
    Father()
    : m_f(new int{1})
    {
        cout << "Father constructor" << endl;
    }

    /**
     * 虚析构函数。
     *
     * 因为 Father 可能作为父类，
     * 使用 Father * 指针指向 Son 对象，
     * 所以这里应该把析构函数写成 virtual。
     *
     *
     * 当执行：
     * Father * f = new Son{};
     * delete f;
     *
     * 如果 ~Father() 是虚析构函数，
     * 会先调用：
     * ~Son()
     *
     * 再调用：
     * ~Father()
     *
     * 这样可以保证子类资源和父类资源都被释放。
     *
     *
     * 注意：
     * 析构函数一旦在父类中声明为 virtual，
     * 子类析构函数天然也是虚函数。
     *
     * 子类析构函数可以不写 virtual，
     * 但父类析构函数必须写 virtual。
     */
    virtual // 虚析构函数 
    ~Father()
    {   
        cout << "~Father()" << endl;

        /**
         * 释放 Father 构造函数中申请的堆空间。
         *
         * new 和 delete 要配对使用。
         *
         * m_f 是 new int{1} 申请来的，
         * 所以这里使用 delete m_f。
         */
        delete m_f;
    }
    
    /**
     * 如果类中有普通虚函数，
     * 这个类也会有虚函数表。
     *
     * 但即使没有普通虚函数，
     * 只要析构函数是 virtual，
     * 析构函数也会进入虚函数机制，
     * 对象中通常也会有 vfptr。
     */
    /* virtual void func(); */

    /**
     * Father 中的指针成员。
     *
     * 该指针指向堆区申请的 int 空间。
     * 所以 Father 析构时需要手动 delete。
     */
    int * m_f;
};

class Son : public Father
{
public:
    /**
     * Son 构造函数。
     *
     * 创建 Son 对象时，
     * 构造顺序是：
     * 1. 先调用 Father 构造函数
     * 2. 再调用 Son 构造函数
     *
     * 所以创建 Son 对象时会先输出：
     * Father constructor
     *
     * 再输出：
     * Son constructor
     */
    Son()
    : m_s(new int{2})
    {
        cout << "Son constructor" << endl;
    }

    /**
     * Son 析构函数。
     *
     * 因为 Father 的析构函数是 virtual，
     * 所以 Son 的析构函数也是虚析构函数。
     *
     * 可以写成：
     * virtual ~Son()
     *
     * 也可以直接写：
     * ~Son()
     *
     * 如果想让语义更清楚，也可以写：
     * ~Son() override
     *
     *
     * 当通过父类指针 delete 子类对象时：
     *
     * Father * f = new Son{};
     * delete f;
     *
     * 会先执行这里的 ~Son()，
     * 释放 Son 自己申请的资源 m_s。
     *
     * 然后自动调用 ~Father()，
     * 释放 Father 申请的资源 m_f。
     */
    ~Son()
    {   
        cout << "~Son()" << endl;

        /**
         * 释放 Son 构造函数中申请的堆空间。
         */
        delete m_s;
    }

    /**
     * Son 中的指针成员。
     *
     * 该指针指向堆区申请的 int 空间，
     * 所以 Son 析构时需要手动 delete。
     */
    int * m_s;
};


void test1()
{
    /**
     * 栈对象。
     *
     * 如果创建的是栈对象：
     *
     * Son son;
     *
     * 当 son 离开作用域时，
     * 会自动调用析构函数。
     *
     * 析构顺序是：
     * 1. 先调用子类析构函数 ~Son()
     * 2. 再调用父类析构函数 ~Father()
     *
     * 这和析构函数是否为 virtual 没有直接关系。
     * 栈对象销毁时，本来就知道对象的真实类型是 Son。
     */
    // 栈对象
    /* Son son; */
    /* cout << sizeof(son) << endl; */
    // 对象销毁时,先调用子类的析构函数,再调用父类的析构函数
    
    /**
     * 堆对象。
     *
     * 如果使用子类指针接收：
     *
     * Son * s = new Son{};
     * delete s;
     *
     * 编译器知道 s 是 Son *，
     * 所以会正确调用：
     * ~Son()
     * ~Father()
     */
    // 堆对象
    /* Son * s = new Son{}; */ 

    /**
     * 使用父类指针接收子类对象。
     *
     * f 的静态类型是 Father *，
     * 但是实际指向的是 Son 对象。
     *
     * 这是多态中非常常见的写法。
     */
    Father * f = new Son{};

    /**
     * sizeof(*f) 的结果由 f 的静态类型决定。
     *
     * f 的类型是 Father *，
     * 所以 *f 的静态类型是 Father。
     *
     * 因此：
     * sizeof(*f)
     *
     * 等价于：
     * sizeof(Father)
     *
     * 而不是 sizeof(Son)。
     *
     * 在 64 位环境下，
     * Father 中通常包含：
     * 1. vfptr，8 字节
     * 2. int * m_f，8 字节
     *
     * 所以 sizeof(*f) 通常是 16。
     *
     * 实际结果仍然以当前平台和编译器为准。
     */
    cout << sizeof(*f) << endl;

    /**
     * 通过父类指针释放子类对象。
     *
     * 因为 Father 的析构函数是 virtual，
     * 所以这里会发生动态绑定。
     *
     * delete f 的执行过程：
     * 1. 调用 Son::~Son()
     *    释放 Son 中的 m_s
     *
     * 2. 自动调用 Father::~Father()
     *    释放 Father 中的 m_f
     *
     *
     * 如果 Father 的析构函数没有 virtual，
     * 那么通过 Father * 删除 Son 对象时，
     * 子类析构函数可能不会被调用，
     * Son 中的 m_s 就可能发生内存泄漏。
     */
    delete f; // 当前代码中会先调用子类析构，再调用父类析构
}

int main(int argc, char *argv[])
{
    /**
     * test1 演示：
     * 1. 父类和子类中都有动态申请的资源
     * 2. 父类指针指向子类对象
     * 3. 通过父类指针 delete 子类对象
     * 4. 父类析构函数为 virtual 时，可以正确调用完整析构链
     */
    test1();

    return 0;
}