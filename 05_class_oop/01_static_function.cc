#include <iostream>
#include <locale>

using std::cout;
using std::endl;

/**
 *  特殊的成员函数:
 *  1.静态的成员函数
 *  2.const成员函数
 *
 *  静态成员函数: static修饰普通成员函数
 *  特点:
 *  1.不依赖于对象,依赖于类
 *  2.一般可以使用类名作用域方式访问
 *
 * 访问测试: 静态成员函数 VS 普通成员函数
 * 静态成员函数:
 *     访问静态成员   ---> ok
 *     范围非静态成员 ---> no
 * 普通成员函数:
 *     访问静态成员   ---> ok
 *     范围非静态成员 ---> ok
 *
 * 小结:
 * 静态的成员函数中可以直接访问静态成员,
 * 但是不能直接访问非静态成员,
 * 特殊的可以间接访问,需要创建对象
 *
 * 非静态的成员函数不受限制
 *
 *
 * 静态成员函数的应用场景:
 * 1.作为工具类中的函数
 * 举例:
 * class DBUtils
 * {
 * public:
 *    // 获取数据库连接
 *    static Connection getConnection(string user, string password)
 *    {}
 *
 *    // 释放数据库连接
 *    static void close()
 *    {}
 * }
 * 
 * class ThreadUtils{}
 * class StringUtils{}
 * class DataUtils{}
 * class FileUtils{}
 *
 */

class MyClass
{
public:
    // 静态成员函数
    static void func()
    {
        cout << "static func()" << endl;        
    }

    static void func2()
    {   
        // 静态的成员函数无法直接访问非静态的成员
        /* m_data1; */
        /* normalFunc(); */
        
        // 静态的成员函数中没有this存在
        /* this; */

        // 特殊的 可以通过创建对象 对象.成员的方式来访问
        MyClass obj;
        obj.m_data1;
        obj.normalFunc();

        // 测试访问静态成员
        m_data2; // ok
        func();  // ok
    }
    
    void normalFunc()
    {
        
    }

    void normalFunc2()
    {
        // 测试访问静态成员
        /* m_data1; */
        /* normalFunc(); */

        // 测试访问非静态成员
        normalFunc();
        m_data1;
    }

    int m_data1;
    static int m_data2;
};

void test1()
{
    // 一般通过类名作用域方式调用
    MyClass::func();

    MyClass obj;
    obj.func();
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

