#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

/**
 * 实现一个Computer类只能生成栈对象，
 * 不能生成堆对象的代码 
 */

class Computer
{
private:
    char * m_brand;
    int m_price;

    // 要禁止在堆上创建对象
    // 把operator new / operator delete设为私有即可
    void * operator new(size_t size);
    void operator delete(void * p);

public:
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

    ~Computer()
    {
        cout << "~Computer()" << endl;
        if(m_brand){
            delete [] m_brand;
            m_brand = nullptr;
        }
    }
};

void test1()
{
    Computer pc1("Apple", 10000);  // OK：栈对象
    pc1.print();

    /* Computer * pc2 =  new Computer("Xiaomi", 1999); */
    // 错误：operator new 是 private，不能在堆上创建
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

