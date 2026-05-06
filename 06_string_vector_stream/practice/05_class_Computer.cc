/**
 * 定义一个`Computer`类，包含私有数据成员：品牌（`char*`动态分配）、价格（`double`）。
 * 要求：
 * 1. 实现构造函数、析构函数、拷贝构造函数、赋值运算符函数（深拷贝）；
 * 2. 在`main`函数中测试对象的创建、拷贝、赋值操作，并使用`valgrind`检查内存泄漏。
 */

#include <iostream>
#include <string.h>

using std::cout;
using std::endl;
using std::string;

class Computer
{
private:
    char * m_pbrand;
    double m_price;
public:
    Computer(const char * brand, double price)
    : m_pbrand(new char[strlen(brand) + 1]{})
    , m_price(price)
    {
        cout << "Computer(const char *, double)" << endl;
        strcpy(m_pbrand, brand);
    }

    ~Computer()
    {
        cout << "~Computer()" << endl;
        delete [] m_pbrand;
        m_pbrand = nullptr;
    }

    Computer(const Computer & rhs)
    : m_pbrand(new char[strlen(rhs.m_pbrand) + 1]{})
    , m_price(rhs.m_price)
    {
        cout << "Computer(const Computer &)" << endl;
        strcpy(m_pbrand, rhs.m_pbrand);
    }

    Computer & operator=(const Computer & rhs)
    {
        cout << "operator=(const Computer &)" << endl;

        if(this != &rhs) {
            char * temp = new char[strlen(rhs.m_pbrand) + 1]{};
            strcpy(temp, rhs.m_pbrand);

            delete [] m_pbrand;
            m_pbrand = temp;

            m_price = rhs.m_price;
        }

        return *this;
    }

};

int main(int argc, char *argv[])
{
    Computer c1("Xiaomi", 1999.99);
    Computer c2 = c1; // 调用拷贝构造函数
    Computer c3("Huawei", 9999.99);
    c3 = c1; // 调用赋值运算符重载

    return 0;
}