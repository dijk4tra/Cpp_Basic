#include <iostream>
#include <cstdlib>   // 使用 atexit 需要包含这个头文件
using namespace std;

class Singleton
{
private:
    // 保存唯一的单例对象
    static Singleton* _instance;

    // 构造函数私有化，防止外部创建对象
    Singleton()
    {
        cout << "Singleton 构造函数" << endl;
    }

    // 析构函数私有化，防止外部随意 delete
    ~Singleton()
    {
        cout << "Singleton 析构函数" << endl;
    }

    // 禁止拷贝构造，防止复制单例对象
    Singleton(const Singleton&) = delete;

    // 禁止赋值操作，防止复制单例对象
    Singleton& operator=(const Singleton&) = delete;

public:
    // 获取单例对象
    static Singleton* getInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new Singleton();

            // 注册 destroy 函数
            // 程序正常结束时，系统会自动调用 Singleton::destroy()
            atexit(destroy);
        }

        return _instance;
    }

    // 静态 destroy 函数，用于释放单例对象
    static void destroy()
    {
        if (_instance != nullptr)
        {
            delete _instance;       // 释放单例对象
            _instance = nullptr;    // 防止野指针

            cout << "Singleton 对象已通过 destroy 自动释放" << endl;
        }
    }

    // 测试函数
    void print()
    {
        cout << "调用 Singleton::print()" << endl;
    }
};

// 静态成员变量类外初始化
Singleton* Singleton::_instance = nullptr;

int main()
{
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    s1->print();
    s2->print();

    if (s1 == s2)
    {
        cout << "s1 和 s2 指向同一个 Singleton 对象" << endl;
    }

    // 不需要手动 delete
    // 程序正常结束时，atexit 会自动调用 Singleton::destroy()

    return 0;
}