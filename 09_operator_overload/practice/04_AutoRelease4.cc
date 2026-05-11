#include <iostream>
#include <pthread.h>
using namespace std;

class Singleton
{
private:
    // 保存唯一的单例对象指针
    static Singleton* _instance;

    // pthread_once_t 控制变量，保证初始化函数只执行一次
    static pthread_once_t _once;

    // 构造函数私有化，防止外部创建对象
    Singleton()
    {
        cout << "Singleton 构造函数" << endl;
    }

    // 析构函数私有化，防止外部 delete
    ~Singleton()
    {
        cout << "Singleton 析构函数" << endl;
    }

    // 禁止拷贝构造
    Singleton(const Singleton&) = delete;

    // 禁止赋值运算符
    Singleton& operator=(const Singleton&) = delete;

    // pthread_once 调用的初始化函数
    static void init()
    {
        _instance = new Singleton();
    }

public:
    // 嵌套类：负责释放 Singleton 对象
    class AutoRelease
    {
    public:
        // 析构函数会在程序结束时自动调用
        ~AutoRelease()
        {
            destroy();
        }
    };

    // 获取单例对象
    static Singleton* getInstance()
    {
        // static 局部对象只会构造一次
        // 程序结束时会自动析构
        // 析构时调用 AutoRelease::~AutoRelease()
        static AutoRelease ar;

        // pthread_once 保证 init 函数只执行一次
        pthread_once(&_once, init);

        return _instance;
    }

    // destroy 函数：释放单例对象
    static void destroy()
    {
        if (_instance != nullptr)
        {
            delete _instance;
            _instance = nullptr;

            cout << "AutoRelease 调用 destroy，自动释放 Singleton 对象" << endl;
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

// pthread_once_t 必须初始化为 PTHREAD_ONCE_INIT
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

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
    // 程序结束时，static AutoRelease ar 会自动析构
    // 在析构函数中调用 Singleton::destroy()

    return 0;
}