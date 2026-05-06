/**
 * 实现一个单例模式的`Logger`类，用于记录日志。
 * 要求：
 * 1. 类中有一个`log`函数，接受一个字符串参数，输出该字符串（可简单打印到控制台）；
 * 2. 确保整个程序中只有一个`Logger`实例（堆区实现）；
 * 3. 提供`getInstance`静态方法获取实例，提供`destroyInstance`静态方法销毁实例；
 * 4. 在`main`函数中测试单例的唯一性。
 */

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Logger
{
public:
    // 获取单例对象
    // 对象创建在堆上,使用指针保存和返回对象
    static Logger * getInstance()
    {
        if(nullptr == m_pInstance){
            m_pInstance = new Logger{};
        }
        return m_pInstance;
    }

    // 释放单例对象
    static void destroyInstance()
    {
        if(m_pInstance){
            // delete会完成两件事
            // 1.调用Logger的析构函数
            // 2.释放对象占用的堆内存
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

    // 删除拷贝构造函数
    // 禁止通过已有Logger对象,再拷贝出一个新的Logger对象
    Logger(const Logger &) = delete;
    // 删除赋值运算符函数
    // 禁止Singleton对象之间进行赋值操作,用来防止误用
    Logger & operator=(const Logger &) = delete;
    
    void log(const string & msg)
    {
        cout << "[LOG] " << msg << endl;
    }

private:
    // 私有化构造函数
    // 类外不能直接创建Logger对象,只能通过getInstance获取对象
    Logger()
    {
        cout << "Logger实例创建" << endl;
    }

    // 私有化析构函数
    ~Logger()
    {
        cout << "Logger实例销毁" << endl;
    }

    // 自身类型的静态指针
    // 保存堆上唯一Logger对象的地址
    // 这里只是类内声明
    // 静态成员变量还需要在类外定义和初始化
    static Logger * m_pInstance;
};

// 类外定义并初始化静态成员变量
// Logger类中的静态成员变量m_pInstance初始值为nullptr
// nullptr 表示当前还没有创建单例对象
Logger * Logger::m_pInstance = nullptr;

int main(int argc, char * argv[])
{   
    // 测试单例唯一性
    Logger * logger1 = Logger::getInstance();
    Logger * logger2 = Logger::getInstance();

    cout << "logger1和logger2是"
         << (logger1 == logger2 ? "同一个实例" : "不同实例")
         << endl;

    // 使用单例
    logger1->log("程序启动");
    logger2->log("程序操作");

    // 销毁实例
    Logger::destroyInstance();

    // 再次获取实例(重新创建)
    Logger * logger3 = Logger::getInstance();
    logger3->log("重新启动");

    Logger::destroyInstance();

    
    return 0;
}
