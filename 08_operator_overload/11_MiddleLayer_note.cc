#include <cerrno>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;

/**
 * 成员访问运算符的重载：
 *
 * 这里主要学习两个运算符：
 * 1. operator->
 * 2. operator*
 *
 * 对于普通指针来说：
 *
 * Type * p = new Type();
 *
 * 可以通过下面两种方式访问对象成员：
 *
 * 1. 指针方式：
 *    p->m_data;
 *    p->func();
 *
 * 2. 解引用方式：
 *    (*p).m_data;
 *    (*p).func();
 *
 * 一般情况下，只有指针才能使用 -> 和 *。
 *
 * 但是如果一个类重载了 operator-> 和 operator*，
 * 那么这个类的对象就可以像指针一样使用。
 *
 * 这种写法常见于智能指针。
 *
 * 智能指针的核心思想：
 * 把堆资源交给一个对象管理，
 * 对象生命周期结束时自动释放资源，
 * 避免手动 delete。
 */

class Data
{
public:
    int getData()
    {
        return m_data;
    }

/* private: */
    /**
     * 这里为了测试方便，把 m_data 暂时放在 public 区域。
     *
     * 如果放在 private 区域，
     * 类外部就不能直接访问 m_data。
     */
    int m_data = 1;
};

class MiddleLayer
{
public:
    /**
     * 构造函数。
     *
     * 参数 p 是一个 Data 类型的指针，
     * 指向堆上的 Data 对象。
     *
     * MiddleLayer 接收这个指针之后，
     * 就负责管理这块堆空间。
     */
    MiddleLayer(Data * p)
    : m_p(p)
    {
        cout << "MiddleLayer(Data * p)" << endl;
    }

    /**
     * 析构函数。
     *
     * MiddleLayer 对象销毁时，
     * 自动释放 m_p 指向的堆空间。
     *
     * 这样外部就不需要再手动 delete。
     */
    ~MiddleLayer()
    {
        cout << "~MiddleLayer()" << endl;

        /**
         * 释放 MiddleLayer 管理的 Data 对象。
         *
         * 注意：
         * 如果这块空间已经在外部 delete 过，
         * 这里再次 delete 就会造成 double free。
         */
        delete m_p;

        // 避免野指针
        m_p = nullptr;
    }

    /**
     * operator-> 重载函数。
     *
     * 表达式：
     * ml->getData();
     *
     * 本质上会调用：
     * ml.operator->()->getData();
     *
     * operator-> 的返回值必须是：
     * 1. 一个指针
     * 或者
     * 2. 一个重载了 operator-> 的对象
     *
     * 这里返回 Data *，
     * 然后再通过这个 Data * 去访问 Data 对象的成员函数。
     */
    Data * operator->()
    {
        cout << "MiddleLayer::operator->()" << endl;

        // 返回被管理资源的指针
        return m_p;
    }

    /**
     * operator* 重载函数。
     *
     * 表达式：
     * (*ml).getData();
     *
     * 本质上会调用：
     * ml.operator*().getData();
     *
     * operator* 通常返回被管理对象本身的引用。
     *
     * 这里返回 Data &，
     * 表示返回 m_p 指向的 Data 对象。
     */
    Data & operator*()
    {
        cout << "MiddleLayer::operator*()" << endl;

        // *m_p 表示 m_p 指向的 Data 对象
        return *m_p;
    }

private:
    /**
     * 保存 Data 对象的地址。
     *
     * MiddleLayer 通过这个指针管理堆上的 Data 对象。
     */
    Data * m_p;
};

void test1()
{
    /**
     * 栈对象。
     *
     * data 是普通对象，
     * 通过 . 运算符访问成员。
     */
    Data data;

    // 对象.成员访问
    data.getData();

    /**
     * 堆对象。
     *
     * new Data{} 会在堆上创建一个 Data 对象，
     * 返回值是 Data * 类型的指针。
     */
    Data * p = new Data{};

    /**
     * 指针->成员访问。
     *
     * p->getData();
     *
     * 等价于：
     * (*p).getData();
     */
    p->getData();

    /**
     * 先对指针 p 解引用，
     * 得到 p 指向的 Data 对象，
     * 再通过 . 调用成员函数。
     */
    (*p).getData();

    /**
     * 手动释放堆资源。
     *
     * 使用 new 申请的资源，
     * 需要使用 delete 释放。
     */
    delete p;

    // 避免野指针
    p = nullptr;
}

void test2()
{
    /**
     * 在堆上创建 Data 对象。
     */
    Data * p = new Data{};

    /**
     * 创建 MiddleLayer 栈对象。
     *
     * 把 p 指向的堆资源交给 ml 管理。
     *
     * 当 ml 生命周期结束时，
     * 会自动调用析构函数释放 p 指向的资源。
     */
    MiddleLayer ml {p};

    /**
     * 这里不能再手动 delete p。
     *
     * 因为 p 指向的资源已经交给 ml 管理了。
     * ml 析构时会 delete m_p。
     *
     * 如果这里提前 delete p，
     * 等 ml 析构时又会 delete 一次，
     * 就会造成 double free。
     */
    delete p; // error: double free
}

void test3()
{
    /**
     * 把 Data 对象当作一个内存资源，
     * 并把该资源交给 MiddleLayer 对象管理。
     *
     * 之后不需要手动 delete，
     * MiddleLayer 析构函数会自动释放资源。
     */
    MiddleLayer ml {new Data{}};

    /**
     * MiddleLayer 对象在这里扮演智能指针的角色。
     *
     * 它内部保存一个 Data *，
     * 并在析构函数中释放该指针指向的资源。
     */

    /*
     * 如果 MiddleLayer 没有重载 operator-> 和 operator*，
     * 那么就无法像使用指针一样使用 MiddleLayer 对象。
     *
     * ml->getData();                 // error
     * ml.operator->()->getData();    // error
     */

    /**
     * getData() 的两种调用方式：
     *
     * 1. 通过对象调用：
     *    Data对象.getData();
     *
     * 2. 通过指针调用：
     *    Data指针->getData();
     */

    /**
     * operator-> 的本质调用。
     *
     * ml.operator->() 会返回一个 Data *，
     * 然后再通过这个 Data * 调用 getData()。
     *
     * 调用过程：
     * ml.operator->()
     * -> Data *
     * -> getData()
     */
    ml.operator->()->getData();

    /**
     * 简写形式。
     *
     * ml->getData();
     *
     * 本质上会自动调用：
     * ml.operator->()->getData();
     */
    ml->getData();

    cout << "----------" << endl;

    /**
     * operator* 的本质调用。
     *
     * ml.operator*() 返回一个 Data 对象的引用，
     * 然后通过该引用调用 getData()。
     *
     * 调用过程：
     * ml.operator*()
     * -> Data 对象
     * -> getData()
     */
    ml.operator*().getData();

    /**
     * 简写形式。
     *
     * (*ml).getData();
     *
     * 本质上会自动调用：
     * ml.operator*().getData();
     */
    (*ml).getData();
}

void test4()
{
    /**
     * 使用智能指针管理资源。
     *
     * auto_ptr<Data> ap{new Data{}};
     *
     * 表示把 new 出来的 Data 对象交给 auto_ptr 管理。
     *
     * 当 ap 生命周期结束时，
     * auto_ptr 会自动释放它管理的资源。
     *
     * 注意：
     * auto_ptr 是旧标准中的智能指针，
     * 在现代 C++ 中已经被废弃。
     *
     * 实际开发中更推荐使用：
     * std::unique_ptr
     * std::shared_ptr
     */
    auto_ptr<Data> ap{new Data{}};

    /**
     * auto_ptr 重载了 operator->，
     * 所以可以像普通指针一样使用：
     *
     * ap->getData();
     */
    cout << ap->getData() << endl;

    /**
     * auto_ptr 也重载了 operator*，
     * 所以可以通过解引用方式访问对象：
     *
     * (*ap).getData();
     */
    cout << (*ap).getData() << endl;
}

int main(int argc, char *argv[])
{
    /**
     * test1 测试普通对象和普通指针的成员访问方式。
     *
     * test2 演示资源交给管理对象之后，
     * 不能再手动 delete，否则会 double free。
     *
     * test3 测试自定义 MiddleLayer 的 operator->
     * 和 operator*。
     *
     * test4 测试智能指针 auto_ptr 的 operator->
     * 和 operator*。
     */
    /* test1(); */
    /* test2(); */
    test4();

    return 0;
}