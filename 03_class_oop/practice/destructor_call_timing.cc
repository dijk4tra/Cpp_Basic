#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class Computer
{
private:
    char * m_brand;
    int m_price;

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
        cout<< "~Computer()" << endl;
        if(m_brand){
            delete [] m_brand;
            m_brand = nullptr;
        }
    }
};


void test1()
{
    // 局部对象
    Computer pc{"xiaomi", 1999};
    pc.print();
    // 函数结束时会自动调用析构函数
}

// 全局对象,程序结束时自动调用析构函数
Computer pc{"apple", 9999};

void test2()
{
    cout << "test2 start" << endl;
    // 静态对象,程序结束时自动调用析构函数
    static Computer pc{"apple", 9999};
    cout << "test2 end" << endl;
}

void test3()
{
    // 存储在堆空间的对象
    Computer *p = new Computer{"xiaomi", 1999};
    // 这里的对象没有名字,无法通过对象名.访问成员
    // 需要通过指针->访问成员
    p->print();
    // delete指针时会调用析构函数
    delete p;
    p = nullptr;
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

