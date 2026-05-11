#include <iostream>
using namespace std;

class Singleton
{
private:
    // 指向唯一单例对象的静态指针
    static Singleton* _instance;

    // 构造函数私有化，防止外部创建对象
    Singleton()
    {
        cout << "Singleton 构造函数" << endl;
    }

    // 析构函数私有化，防止外部随意释放对象
    ~Singleton()
    {
        cout << "Singleton 析构函数" << endl;
    }

    // 禁止拷贝构造，避免产生新的对象
    Singleton(const Singleton&) = delete;

    // 禁止赋值操作，避免产生新的对象
    Singleton& operator=(const Singleton&) = delete;

public:
    // 嵌套类：专门负责释放 Singleton 对象
    class AutoRelease
    {
    public:
        // AutoRelease 的析构函数会在程序结束时自动调用
        ~AutoRelease()
        {
            if (_instance != nullptr)
            {
                delete _instance;       // 释放单例对象
                _instance = nullptr;    // 防止野指针
                cout << "AutoRelease 自动释放 Singleton 对象" << endl;
            }
        }
    };

    // 获取唯一单例对象的接口
    static Singleton* getInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new Singleton();
        }

        return _instance;
    }

    // 测试函数
    void print()
    {
        cout << "调用 Singleton::print()" << endl;
    }

private:
    // 静态 AutoRelease 对象
    // 程序结束时，该对象自动析构，从而释放 Singleton 对象
    static AutoRelease _autoRelease;
};

// 静态成员变量需要在类外初始化
Singleton* Singleton::_instance = nullptr;

// 定义静态 AutoRelease 对象
Singleton::AutoRelease Singleton::_autoRelease;

int main()
{
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    s1->print();
    s2->print();

    if (s1 == s2)
    {
        cout << "s1 和 s2 是同一个对象" << endl;
    }

    // 不需要手动 delete
    // 程序结束时 _autoRelease 会自动析构，
    // 并在析构函数中 delete _instance

    return 0;
}