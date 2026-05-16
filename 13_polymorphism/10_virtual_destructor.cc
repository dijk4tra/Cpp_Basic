#include <iostream>
#include <ostream>

using std::cout;
using std::endl;

/**
 * 析构函数: destructor
 * 加了virtual之后: dtor
 * 
 * 如果没有虚析构函数,父类和子类中涉及动态内存分配,
 * 且使用了多态
 * Father * f = 子对象, delete f : 通过父指针只能访问
 * 父类的析构函数--->子类的析构函数未执行--->内存泄露
 *
 * 解决方案:
 * 使用虚析构函数,析构函数被加入到虚函数表中,表中存放
 * 的肯定是子类的虚析构函数
 * delete f-->执行子类的虚析构函数--->自动调用父类虚析构函数
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
    // 对象销毁时,先调用子类的析构函数,再调用父类的析构函数
    
    // 堆对象
    /* Son * s = new Son{}; */ 
    Father * f = new Son{};
    cout << sizeof(*f) << endl;
    delete f; // 调用析构函数,只调用了父类析构,未调用子类析构
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

