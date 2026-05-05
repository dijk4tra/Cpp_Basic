#include <iostream>

using std::cout;
using std::endl;

/**
 * 保证某个类型在系统中只有一个对象实例。
 * 无论获取多少次，拿到的始终都是同一个对象。
 *
 * 单例设计模式的实现步骤：
 * 1. 使用 private 修饰构造函数，使外部无法直接创建对象
 * 2. 提供一个 public 函数，用于返回这个唯一对象
 * 3. 在该函数中保证对象只创建一次
 *
 * 通常还需要删除拷贝构造函数和赋值运算符，
 * 防止通过拷贝或赋值产生新的对象。
 *
 * 实现方式一：
 * 将单例对象创建在静态区。
 */

class Singleton
{
public:
    static Singleton & getInstance()
    {
        static Singleton instance;

        // 返回唯一的对象实例
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
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

    // 通过 getInstance 获取单例对象
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}