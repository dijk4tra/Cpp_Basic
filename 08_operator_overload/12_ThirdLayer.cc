#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;

/*
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
 * 通常需要通过指针完成的成员访问操作，
 * 在重载 operator-> 和 operator* 后，
 * 可以让对象像指针一样被使用。
 *
 * 自动释放资源：
 * 利用栈对象的生命周期，在对象销毁时自动释放其管理的资源。
 */

class Data
{
public:
    Data()
    {
        cout << "Data()" << endl;
    }

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
    // 构造函数
    MiddleLayer(Data * p)
    : m_p(p)
    {
        cout << "MiddleLayer(Data *)" << endl;
    }

    ~MiddleLayer()
    {
        cout << "~MiddleLayer()" << endl;
        if(m_p){
            delete m_p;
            m_p = nullptr;
        }
    }

    // 重载 operator->
    // 返回值必须是指针，或者是一个继续重载了 operator-> 的对象
    Data * operator->()
    {
        return  m_p;
    }

    // 重载 operator*
    Data & operator*()
    {
        return *m_p;
    }

private:
    // 原生指针，也称原始指针、裸指针或底层指针
    Data * m_p;
};

// 定义第三层结构
class ThirdLayer
{
public:
    ThirdLayer(MiddleLayer * m_p)
    : m_pml(m_p)
    {
        cout << "ThirdLayer(MiddleLayer*)" << endl;
    }

    ~ThirdLayer()
    {
        cout << "~ThirdLayer()" << endl;
        if(m_pml){
            delete m_pml;
            m_pml = nullptr;
        }
    }

    // 重载 operator->
    MiddleLayer & operator->()
    {
        return *m_pml;
    }

    // 重载 operator*
    MiddleLayer & operator*()
    {
        return *m_pml;
    }

    /* Data & operator*() */
    /* { */
    /*     return **m_pml; */
    /* } */

private:
    MiddleLayer * m_pml;
};

// 使用第三层对象作为资源管理者
void test1()
{
    /* MiddleLayer ml { new Data{} }; */

    ThirdLayer tl {new MiddleLayer{ new Data{} }};

    // 通过 tl 对象访问其间接管理的 Data 对象中的 getData 函数

    // 调用过程：
    // tl 的 operator-> 返回 MiddleLayer 对象
    // MiddleLayer 的 operator-> 返回 Data 指针
    // 最后通过 Data 指针调用 getData()
    // 本质：
    // tl.operator->().operator->()->getData()
    tl.operator->().operator->()->getData();

    // 简写形式：
    tl->getData();


    cout << "----------" << endl;

    // 调用过程：
    // tl.operator*() 返回 MiddleLayer 对象
    // MiddleLayer.operator*() 返回 Data 对象
    // 最后通过 Data 对象调用 getData()
    // 本质：
    tl.operator*().operator*().getData();

    // 简写形式：
    (*(*tl)).getData();

    // 如果希望只解引用一次就能访问 getData()，
    // 可以修改 ThirdLayer 的 operator*，让其直接返回 Data&
    /* (*tl).getData(); */
}

int main(int argc, char * argv[])
{
    test1();

    return 0;
}