#include <iostream>

using std::cout;
using std::endl;

/**
 * 可以使用friend友元破除私有限制
 */


class MyClass
{
public:
    int getData()
    {
        return m_data;
    }
private:
    int m_data = 1;
};


void test1()
{
    MyClass obj;
    /* obj.m_data; */
    obj.getData();
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

