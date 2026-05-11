#include <iostream>
using namespace std;

class Singleton
{
private:
    // 保存唯一的单例对象指针
    static Singleton* _instance;

    // 构造函数私有化，防止外部直接创建对象
    Singleton()
    {
        cout << "Singleton 构造函数被调用" << endl;
    }

    // 析构函数私有化，防止外部随意 delete 单例对象
    ~Singleton()
    {
        cout << "Singleton 析构函数被调用" << endl;
    }

    // 禁止拷贝构造，防止复制单例对象
    Singleton(const Singleton&) = delete;

    // 禁止赋值操作，防止复制单例对象
    Singleton& operator=(const Singleton&) = delete;

public:
    // 回收类，必须命名为 AutoRelease
    class AutoRelease
    {
    public:
        // AutoRelease 对象析构时，自动释放单例对象
        ~AutoRelease()
        {
            if (_instance != nullptr)
            {
                delete _instance;
                _instance = nullptr;
                cout << "AutoRelease 自动释放 Singleton 对象" << endl;
            }
        }
    };

    // 获取单例对象的静态成员函数
    static Singleton* getInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new Singleton;
        }

        return _instance;
    }

    // 测试用成员函数
    void show()
    {
        cout << "Singleton::show() 被调用" << endl;
    }

private:
    // 静态 AutoRelease 对象
    // 程序结束时，它会自动析构，从而释放 Singleton 对象
    static AutoRelease _autoRelease;
};

// 初始化静态成员变量
Singleton* Singleton::_instance = nullptr;

// 定义静态 AutoRelease 对象
Singleton::AutoRelease Singleton::_autoRelease;

int main()
{
    // 第一次获取单例对象，会创建 Singleton 对象
    Singleton* p1 = Singleton::getInstance();
    p1->show();

    // 第二次获取单例对象，不会重新创建，而是返回同一个对象
    Singleton* p2 = Singleton::getInstance();
    p2->show();

    // 判断两个指针是否指向同一个对象
    if (p1 == p2)
    {
        cout << "p1 和 p2 指向同一个 Singleton 对象" << endl;
    }

    // 不需要手动 delete
    // 程序结束时，静态对象 _autoRelease 会自动析构
    // 在它的析构函数中会释放 Singleton 对象

    return 0;
}