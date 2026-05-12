#include <iostream>

using std::cout;
using std::endl;

/**
 * 代理设计模式：委托类、代理类 —— 代理类帮助委托类完成操作
 * 
 * 景天类：委托类，负责买早餐
 *
 * 空灵类：代理类，代替景天买早餐
 *
 * 常见的代理实现方式：
 * 1. 将委托对象作为代理类的数据成员
 * 2. 将委托类作为代理类的父类，通过继承实现代理
 */

 // 委托类
class JingTian
{
public:
    void buyBreakfast()
    {
        cout << "买两个包子" << endl;
    }
};

// 代理类
class KongLing
{
public:
    void buyBreakfast()
    {   
        cout << "帮景天" << endl;
        m_jingtian.buyBreakfast();
    }

    // 将委托对象作为代理类的数据成员
    JingTian & m_jingtian;
};


void test1()
{
    JingTian jingtian;
    KongLing kl{ jingtian };
    kl.buyBreakfast();
}


// 使用方式二实现代理模式：通过继承实现代理
// 委托类
class JingTian2
{
public:
    void buyBreakfast()
    {
        cout << "买两个包子" << endl;
    }
};

// 代理类
// 将委托类作为代理类的父类
// JingTian2 是父类，KongLing2 是子类
class KongLing2 : public JingTian2
{
public:
    void buyBreakfast()
    {   
        cout << "帮景天" << endl;

        // 调用父类中同名的成员函数
        // 通过类名作用域明确指定调用父类版本
        JingTian2::buyBreakfast();
    }
};

void test2()
{
    KongLing2 kl;
    kl.buyBreakfast();
}


int main(int argc, char *argv[])
{
    /* test1(); */
    test2();
    return 0;
}