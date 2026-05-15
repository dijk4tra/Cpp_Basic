#include <iostream>

using std::cout;
using std::endl;

/**
 * 多态：统一指令，针对不同的子类的对象，表现出不同的行为
 * 
 * 代码中的体现：
 * 继承的前提条件下，父类型接收子类对象，通过父类型的指针或者
 * 引用调用父子同名的虚函数，体现出不同的子类行为 
 *
 *
 */



void test1()
{

}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

