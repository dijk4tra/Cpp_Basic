#include <functional>
#include <iostream>
#include <string>

using namespace std;

class Computer
{
private:
    string m_brand;
    double m_price;

public:
    Computer(string brand, double price)
    : m_brand(brand)
    , m_price(price)
    {
        cout << "Computer(string,double)" << endl;  
    }

    ~Computer()
    {
        cout << "~Computer()" << endl;
    }

    void show() const 
    {
        cout << "品牌：" << m_brand << "，价格：" << m_price << endl;
    }
};

template<typename T>
class RAIIManager
{
private:
    T * m_ptr;

public:
    // 构造函数：接收一个堆资源指针，并由 RAIIManager 接管
    //
    // explicit 的作用：
    // 禁止隐式类型转换，要求必须明确调用构造函数。
    //
    // 例如：
    // RAIIManager<Computer> p = new Computer("Lenovo", 5999);
    // 这种写法会被 explicit 禁止。
    //
    // 推荐写法：
    // RAIIManager<Computer> p(new Computer("Lenovo", 5999));
    explicit RAIIManager(T *p = nullptr)
    : m_ptr(p)
    {}

    // 析构函数
    ~RAIIManager()
    {
        delete m_ptr;
        m_ptr = nullptr;
        cout << "~RAIIManager()" << endl;
    }

    // 禁止拷贝构造和拷贝赋值
    // 如果允许拷贝，两个 RAIIManager 对象可能会管理同一个指针
    // 当两个对象析构时，会对同一块内存 delete 两次，造成严重错误
    RAIIManager(const RAIIManager &) = delete;
    RAIIManager& operator=(const RAIIManager &) = delete;
    
    // operator->
    T * operator->()
    {
        return m_ptr;
    }

    // const版本的operator->
    // 当 RAIIManager 对象是 const 时，也可以通过它访问 const 成员函数
    const T * operator->() const
    {
        return m_ptr;
    }

    // operator*
    T & operator*()
    {
        return *m_ptr;
    }
    
    // const版本的operator*
    const T& operator*() const {
        return *m_ptr;
    }

    // 获取内部保存的原始指针
    T * get() const
    {
        return m_ptr;
    }

};



int main(int argc, char *argv[])
{
    // 使用一个局部作用域，方便观察资源自动释放的过程
    {
        // 在堆上创建 Computer 对象
        // new Computer("Lenovo", 5999) 会返回 Computer* 指针
        //
        // RAIIManager<Computer> 接管这个指针
        // 从此以后，不需要手动 delete
        RAIIManager<Computer> computerPtr(
            new Computer("Lenovo", 5999)
        );

        // 使用 -> 运算符访问 Computer 的成员函数
        computerPtr->show();

        // 使用 * 运算符解引用，再访问成员函数
        (*computerPtr).show();

        // 当这个局部作用域结束时，
        // computerPtr 会自动调用析构函数，
        // 析构函数里会 delete 被管理的 Computer 对象
    }

    // 到这里时，Computer 资源已经被自动释放
    cout << "作用域结束" << endl;


    return 0;
}

