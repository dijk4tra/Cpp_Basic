#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/**
 * 析构函数 destructor：一种特殊的成员函数
 *
 * 析构函数的作用：
 * 当对象销毁时，析构函数会自动调用。
 * 析构函数通常用于释放对象占用的资源。
 *
 * 语法：
 * ~类名()
 * {
 *     析构函数体
 * }
 *
 * 例如：
 * ~Computer()
 * {
 *     // 释放资源
 * }
 *
 * 析构函数的特点：
 * 1.析构函数没有返回值类型
 *   不能写 void，也不能写 int
 * 2.析构函数的函数名是：
 *   ~类名
 * 3.析构函数没有参数
 * 4.析构函数不能重载
 *   因为它不能有参数，所以一个类中只能有一个析构函数
 * 5.析构函数在对象销毁时自动调用
 *
 *
 * 什么是资源？
 * 资源不只是普通变量。
 * 资源通常指需要手动申请、手动释放的东西。
 *
 * 常见资源：
 * 1. 内存资源
 *    例如 new / new[] 申请的堆内存
 * 2. 文件资源
 *    例如打开文件后，需要关闭文件
 * 3. 网络资源
 *    例如网络连接、socket 等
 * 4. 锁资源
 *    例如多线程中的互斥锁
 *
 *
 * 析构函数的调用时机：
 * 1.局部对象：
 *   离开局部作用域时自动调用析构函数
 * 2.全局对象：
 *   程序结束时自动调用析构函数
 * 3.静态对象：
 *   程序结束时自动调用析构函数
 * 4.堆上对象：
 *   必须手动 delete 指针
 *   delete 时才会调用析构函数
 *
 *
 * 重点：
 * 构造函数负责“初始化资源”
 * 析构函数负责“释放资源”
 *
 * 这是一种非常重要的 C++ 编程思想：
 * 对象创建时申请资源，
 * 对象销毁时释放资源。
 */


class Computer
{
public:
    // 构造函数
    // 初始化列表
    // strlen(brand) 计算字符串长度，不包含结尾的 '\0'
    // 所以要 + 1：
    // 额外留出一个位置存放字符串结束符 '\0'
    //
    // new char[strlen(brand) + 1]{}
    // 在堆区申请一段 char 数组，并且用 {} 初始化为 0
    // m_brand 保存这段堆内存的首地址
    Computer(const char * brand, int price)
    : m_brand(new char[strlen(brand) + 1]{}),
      m_price(price)
    {
        cout << "constructor" << endl;
        // strcpy 将 brand 指向的字符串拷贝到 m_brand 指向的堆内存中
        strcpy(m_brand, brand);
        
    }

    void print()
    {
        cout << m_brand << " " << m_price << endl;
    }
    
    /* 
    // 如果没有析构函数，也可以写一个普通成员函数 release()
    // 用来手动释放资源，但如果忘记调用，就会造成内存泄漏
    // 析构函数的好处是：
    // 对象销毁时会自动调用，不需要用户手动记住释放资源。
    void release()
    {
        if(m_brand){
            delete [] m_brand;
            m_brand = nullptr;
        }
    }
    */

    // 析构函数destructor
    // 当 Computer 对象销毁时，自动调用 ~Computer()
    ~Computer()
    {
        cout << "~Computer()" << endl;
        if(m_brand){
            // new    要搭配 delete
            // new[]  要搭配 delete[]
            delete [] m_brand;
            m_brand = nullptr; // 避免野指针
        }
    }

private:
    // 指针成员变量
    // m_brand 本身在对象内部，
    // 但是它指向的字符串内容在堆区
    // 所以对象销毁时，
    // 不仅要销毁 m_brand 这个指针变量本身，
    // 还要释放它指向的堆内存
    char * m_brand;
    // 普通 int 成员变量
    // 对象销毁时，它会自动销毁
    int m_price;
};

void test1()
{   
    // 局部对象
    Computer pc{ "xiaomi", 1999 };
    pc.print();
    /* pc.~Computer(); // 手动调用析构函数,不要这样写 */
    /*                 // 一般都是让析构函数自动去执行 */  
}
/*
// 不建议手动调用析构函数
// pc.~Computer();
//
// 为什么？
// 因为 pc 是局部对象，
// 离开 test1 函数时，析构函数还会自动调用一次。
//
// 如果在这里手动调用了一次析构函数，
// 离开作用域时又自动调用一次，
// 就会导致同一块堆内存被释放两次。
//
// 这叫 double free，属于严重错误，可能会导致程序崩溃！
*/


// 全局对象
// 它在 main 函数执行之前就会被创建，
// 在程序结束时自动调用析构函数
/* Computer pc{"apple", 9999}; */


void test2()
{   
    // 静态局部对象
    // static Computer pc{"apple", 9999};
    //
    // 特点：
    // 1. 第一次执行到这行代码时才创建
    // 2. 之后再次进入 test2，不会重复创建
    // 3. 生命周期一直持续到程序结束
    // 4. 程序结束时自动调用析构函数
    //
    // 注意：
    // 虽然 pc 写在 test2 函数内部，
    // 但是因为它是 static，
    // 所以它不会在 test2 结束时销毁
    cout << "test2 start" << endl;
    // 静态对象,程序结束时自动调用析构函数
    static Computer pc{"apple", 9999};
    cout << "test2 end" << endl;
}

void test3()
{
    // 堆上对象
    // new Computer{"xiaomi", 1999}
    //
    // 做了两件事：
    // 1.在堆区申请一块内存，用来存放 Computer 对象
    // 2.调用 Computer 的构造函数初始化这个对象
    //
    // 返回值是这个堆对象的地址，
    // 用 Computer* 类型的指针 p 保存
    Computer * p = new Computer{"xiaomi", 1999};
    // 这里的对象没有名字,无法通过对象名.访问成员
    // 只能通过指针->访问成员
    p->print();
    // delete指针时会调用析构函数
    delete p;
    // delete p 做了两件事：
    // 1. 调用 p 指向对象的析构函数 ~Computer()
    //    析构函数中会释放 m_brand 指向的堆内存
    // 2. 释放 Computer 对象本身占用的堆内存
    //
    // 注意：
    // 只要使用 new 创建对象，
    // 就必须使用 delete 释放对象
    p = nullptr; // 避免野指针
}


int main(int argc, char *argv[])
{   
    cout << "main start" << endl;
    /* test1(); */
    /* test2(); */
    test3();
    cout << "main end" << endl;
    return 0;
}

