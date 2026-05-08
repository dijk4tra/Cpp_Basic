#include <iostream>
#include <ostream>

using std::cout;
using std::endl;

/**
 * friend友元:
 * 1.普通函数的有元形式(有元函数)
 * 2.成员函数的友元形式(把成员函数声明为有元)
 * 3.有元类(把类声明为友元)
 */


class MyClass
{
public:
    int getData()
    {
        return m_data;
    }
    // 把普通函数test1(),test2()声明为友元函数
    friend void test1();

private:
    friend void test2();
    int m_data;
};


void test1()
{
    MyClass obj;
    cout << obj.m_data << endl;
}

void test2()
{
    MyClass obj;
    cout << obj.m_data << endl;
}


int main(int argc, char *argv[])
{
    test1();
    return 0;
}

