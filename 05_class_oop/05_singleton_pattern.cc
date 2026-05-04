#include <iostream>

using std::cout;
using std::endl;

/**
 *
 *
 * 
 *
 * 单例设计模式的实现步骤:
 * 1.private修饰构造函数(构造函数私有)
 * 2.提供一个public函数返回这个唯一的对象
 * 3.在函数中保证该对象唯一
 *
 * 通常可以把拷贝构造,赋值运算符删掉
 *
 */

class Singleton
{
public:
    static Singleton & getInstance()
    {
        static Singleton instance;
        // 返回一个唯一的对象
        return instance;
    }

    // 删除复制控制的函数
    Singleton(const Singleton &) = delete;
    Singleton & operator = (const Singleton &) = delete;

private:
    Singleton(){}
};

void test1()
{
    /* Singleton s1; */
    /* Singleton s2; */
    /* Singleton s3; */

    // 对象getInstance
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

