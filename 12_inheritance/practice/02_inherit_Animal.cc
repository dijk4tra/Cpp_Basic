#include <iostream>
using namespace std;

class Animal
{
public:
    void speak()
    {
        cout << "Animal speaks" << endl;
    }
};

class Dog : public Animal
{
public:
    void speak()
    {
        cout << "Dog barks" << endl;
    }
};

int main()
{
    Dog dog;

    // 调用派生类 Dog 中的 speak()
    dog.speak();

    // 使用作用域解析符调用基类 Animal 中被隐藏的 speak()
    dog.Animal::speak();

    return 0;
}