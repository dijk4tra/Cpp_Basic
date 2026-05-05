#include <iostream>

using std::cout;
using std::endl;

/*
 *  特殊成员函数：
 *  1. 静态成员函数
 *  2. const 成员函数
 *
 *  静态成员函数：使用 static 修饰的成员函数
 *
 *  特点：
 *  1. 不依赖具体对象，而是属于类本身
 *  2. 通常使用“类名::函数名”的方式调用
 *
 *  静态成员函数与普通成员函数的访问权限测试：
 *
 *  静态成员函数：
 *      访问静态成员       OK
 *      访问非静态成员     NO
 *
 *  普通成员函数：
 *      访问静态成员       OK
 *      访问非静态成员     OK
 *
 *  小结：
 *  静态成员函数可以直接访问静态成员，
 *  但不能直接访问非静态成员。
 *
 *  如果必须在静态成员函数中访问非静态成员，
 *  需要先创建对象，再通过对象进行访问。
 *
 *  非静态成员函数没有上述限制。
 *
 *  静态成员函数的应用场景：
 *  1. 用作工具类中的函数
 *
 *  示例：
 *
 *  class DBUtils {
 *  public:
 *      // 获取数据库连接
 *      static Connection getConnection(string user, string password)
 *      {
 *
 *      }
 *
 *      // 释放数据库连接
 *      static void close()
 *      {
 *
 *      }
 *  };
 *
 *  class ThreadUtils {};
 *  class StringUtils {};
 *  class DataUtils {};
 *  class FileUtils {};
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
        // 静态成员函数不能直接访问非静态成员
        /* m_data1; */
        /* normalFunc(); */

        // 静态成员函数中没有 this 指针
        /* this; */

        // 可以先创建对象，再通过对象间接访问非静态成员
        MyClass obj;
        obj.m_data1;
        obj.normalFunc();

        // 静态成员函数可以直接访问静态成员
        m_data2; // OK
        func();  // OK
    }
    
    void normalFunc()
    {

    }

    void normalFunc2()
    {
        // 普通成员函数可以访问静态成员
        func();
        m_data2;

        // 普通成员函数也可以访问非静态成员
        normalFunc();
        m_data1;
    }

    int m_data1;
    static int m_data2;
};

void test1()
{
    // 通常使用“类名::函数名”的方式调用静态成员函数
    MyClass::func();

    MyClass obj;

    // 也可以通过对象调用，但不推荐作为主要写法
    obj.func();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}
