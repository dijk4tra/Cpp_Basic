#include <iostream>

using std::cout;
using std::endl;

/**
 * 继承: 让子类去复用父类
 */

// 父类/基类
class Animal
{
public:
    void eat()
    {
        cout << "eat......" << endl;
    }
};

class Dog : public Animal
{

};

class Cat : public Animal
{

};

void test1()
{
    Dog dog;
    dog.eat();
    
    Cat cat;
    cat.eat();
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

