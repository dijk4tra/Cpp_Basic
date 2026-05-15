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

class MyClass;

class FriendClass;

class FriendClass
{
public:
    // 只做函数声明
    void func(const MyClass & obj);
};

class MyClass
{
public:
    int getData()
    {
        return m_data;
    }
    
    friend
    void FriendClass::func(const MyClass & obj);

private:
    int m_data = 1;
};

// FriendClass中func的实现
void FriendClass::func(const MyClass & obj){
    cout << obj.m_data << endl;
}


void test1()
{}


int main(int argc, char *argv[])
{
    test1();
    return 0;
}

