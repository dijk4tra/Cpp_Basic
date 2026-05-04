#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

/**
 * 实现一个Computer类只能生成堆对象，
 * 不能生成栈对象的代码，
 * 并能做到正常回收该堆对象 
 */

class Computer
{
private:
    char * m_brand;
    int m_price;
    
    // 析构函数    
    ~Computer()
    {
        cout << "~Computer" << endl;
        delete [] m_brand;
        m_brand = nullptr;
    }

public:
    // 构造函数
    Computer(const char * brand, int price)
    : m_brand(new char[strlen(brand) + 1]{}),
      m_price(price)
    {
        cout << "constructor" << endl;
        strcpy(m_brand, brand);
    }

    void print()
    {
        cout << m_brand << " " << m_price << endl;
    }

    void destroy()
    {
        delete this;
    }
};

void test1()
{
    /* Computer pc1("Apple", 10000); */
    // error：析构函数是 private，栈对象离开作用域时无法调用析构函数
    
    Computer * pc2 = new Computer("Xiaomi", 1999);
    pc2->print();

    pc2->destroy(); // 正常回收堆对象
    pc2 = nullptr;
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

