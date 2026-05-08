#include <cerrno>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;

/**
 * 成员访问相关运算符：
 * 1. operator->
 * 2. operator*
 *
 * Type * p = new Type();
 * p->m_data;
 * p->func();
 *
 * (*p).m_data;
 * (*p).func();
 *  
 * 通常情况下，需要通过指针完成的成员访问操作，
 * 在重载 operator-> 和 operator* 后，
 * 可以让对象像指针一样被使用。
 */

class Data
{
public:
    int getData()
    {
        return m_data;
    }

/* private: */
    int m_data = 1;
};

class MiddleLayer
{
public:
    MiddleLayer(Data * p)
    : m_p(p)
    {
        cout << "MiddleLayer(Data * p)" << endl;
    }

    ~MiddleLayer()
    {
        cout << "~MiddleLayer()" << endl;
        delete m_p;
        m_p = nullptr;
    }

    // 重载 operator->
    // 返回值必须是指针，或者是一个继续重载了 operator-> 的对象
    Data * operator->()
    {
        cout << "MiddleLayer::operator->()" << endl;
        return m_p;
    }

    // 重载 operator*
    // 返回被管理资源对象的引用
    Data & operator*()
    {
        cout << "MiddleLayer::operator*()" << endl;
        return *m_p;
    }

private:
    Data * m_p;
};

void test1()
{   
    // 栈对象
    Data data;

    // 通过对象访问成员
    data.getData();
    
    // 堆对象
    Data * p = new Data{};

    // 通过指针访问成员
    p->getData();

    // 解引用指针后，再通过对象访问成员
    (*p).getData();

    // 释放堆资源
    delete p;
    p = nullptr;
}

void test2()
{
    Data * p = new Data{};

    // 创建栈对象 ml，并将堆资源交给 ml 管理
    MiddleLayer ml {p};

    // 资源已经由 MiddleLayer 管理，不能再手动 delete
    delete p; // error：重复释放，double free
}

void test3()
{   
    // 将 Data 对象作为资源交给 MiddleLayer 管理，
    // 后续无需手动释放该资源
    MiddleLayer ml {new Data{}};

    // MiddleLayer 对象在这里扮演类似智能指针的角色

    /*
     * 如果 MiddleLayer 没有重载 operator-> 和 operator*，
     * 就无法像使用指针一样使用 MiddleLayer 对象。
     *
     * ml->getData();                 // error
     * ml.operator->()->getData();    // error
     */
    
    // getData() 的两种常见调用方式：
    // 1. Data 对象调用：对象.getData()
    // 2. Data 指针调用：指针->getData()
    
    // operator-> 返回 Data 对象的指针，
    // 再通过该指针调用 getData()
    // 本质：
    ml.operator->()->getData();

    // 简写形式：
    ml->getData();

    cout << "----------" << endl;

    // operator* 返回 Data 对象的引用，
    // 再通过该引用调用 getData()
    // 本质：
    ml.operator*().getData();

    // 简写形式：
    (*ml).getData();
}

void test4()
{
    // 使用智能指针管理资源
    auto_ptr<Data> ap{new Data{}};

    // 智能指针重载了 operator->，因此可以像普通指针一样访问成员
    cout << ap->getData() << endl;

    // 智能指针重载了 operator*，因此可以解引用后访问成员
    cout << (*ap).getData() << endl;
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test4();
    
    return 0;
}