#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/**
 * 继承的意义：
 * 1. 派生类可以复用基类中已有的成员变量和成员函数；
 * 2. 可以减少重复代码，提高代码的复用性和可维护性。
 */

// Animal 是父类，也称为基类
class Animal
{
public:
    string name;
    int age;

    void eat()
    {
        cout << "eat..." << endl;
    }
};

// Dog 通过 public 方式继承 Animal
// Dog 是子类，也称为派生类
// 因此 Dog 对象可以使用 Animal 中 public 的成员
class Dog : public Animal
{

};

// Cat 同样通过 public 方式继承 Animal
// Cat 对象也可以复用 Animal 中的 public 成员
class Cat : public Animal
{

};

void test1()
{
    Dog dog;
    dog.eat();   // Dog 继承了 Animal 的 eat() 函数

    Cat cat;
    cat.eat();   // Cat 继承了 Animal 的 eat() 函数
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}