#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

// 简单类:类中数据成员都是内置类型,不涉及动态内存分配
class Point
{
public:
    void setX(int x)
    {
        m_x = x;
    }
    void setY(int y)
    {
        m_y = y;
    }
    void print()
    {
        cout << m_x << " "<< m_y << endl;
    }
private:
    int m_x;
    int m_y;
};


// 复杂类:涉及动态内存分配
class Computer
{
public:
    void setBrand(const char * brand){
        // 动态内存分配
        m_brand = new char[strlen(brand) + 1]{};
        strcpy(m_brand, brand);
    }
    void setPrice(int price)
    {
        m_price = price;
    }
    void print()
    {
        cout << m_brand << " " << m_price<<endl;
    }
    // 进行资源释放的操作
private:
    //品牌
    char * m_brand;
    //价格
    int m_price;
};


void test1()
{
    Point pt;
    /* pt.m_x = 1; */
    pt.setX(1);
    pt.setY(2);
    pt.print();
    cout << "----" << endl;
    Computer pc;
    pc.setBrand("huawei");
    pc.setPrice(6999);
    pc.print();
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

