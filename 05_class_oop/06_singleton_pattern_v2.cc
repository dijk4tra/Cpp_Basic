#include <cstdint>
#include <iostream>

using std::cout;
using std::endl;

/**
 * 单例实现方式二: 单例对象创建在堆上
 *
 * 步骤:
 * 1.构造函数私有
 * 2.提供一个外部的访问,获取这个唯一的对象
 * 3.函数中保证这个对象是唯一的
 * 4.提供一个自身类型的指针
 *
 */

class Singleton
{
public:
    static Singleton * getInstance()
    {
        // 增加一些逻辑判断
        if(!m_pInstance){
            m_pInstance = new Singleton{};
        }
        return m_pInstance;
    }
    
    // 释放资源的操作
    static void destroyInstance()
    {
        if(m_pInstance){
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

    // 删除复制控制相关的函数
    Singleton(const Singleton &) = delete;
    Singleton & operator = (const Singleton &) = delete;

private:
    Singleton(){}
    // 增加一个自身类型的指针
    static Singleton * m_pInstance;
};

// 类外初始化
Singleton * Singleton::m_pInstance = nullptr;

void test1()
{

}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

