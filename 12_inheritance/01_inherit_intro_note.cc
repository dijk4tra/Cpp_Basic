#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/**
 * 继承 inheritance：
 *
 * 继承的意义：
 * 子类可以复用父类中的成员。
 *
 * 如果多个类中存在相同的成员变量或者成员函数，
 * 可以把这些公共内容提取到一个父类中。
 * 然后让其他类继承这个父类，
 * 这样子类就可以直接使用父类中的成员。
 *
 * 例如：
 * Dog 和 Cat 都有 name、age，
 * 并且都可以 eat。
 * 所以可以把这些公共内容放到 Animal 中。
 *
 *
 * 父类和子类：
 * 1. 父类 parent class
 *    也叫基类 base class。
 *    用来存放公共成员。
 *
 * 2. 子类 child class
 *    也叫派生类 derived class。
 *    通过继承父类，复用父类中的成员。
 *
 *
 * 继承语法：
 * class 子类名 : 继承方式 父类名
 * {
 *     子类自己的成员
 * };
 *
 * 例如：
 * class Dog : public Animal
 * {
 *
 * };
 *
 * 表示：
 * Dog 类以 public 的方式继承 Animal 类。
 *
 *
 * public 继承：
 * 父类中的 public 成员，
 * 继承到子类中以后，仍然是 public 成员。
 *
 * 所以外部可以通过 Dog 对象调用 Animal 中的 public 成员函数：
 * Dog dog;
 * dog.eat();
 */

// 父类或者基类
class Animal
{
public:
    // 成员变量
    // 动物的名字
    string name;

    // 动物的年龄
    int age;

    // 成员函数
    // 所有动物都具有 eat 行为
    void eat()
    {
        cout << "eat..." << endl;
    }
};

// Dog 类继承了 Animal
// Dog 是子类或者派生类
// Animal 是父类或者基类
class Dog : public Animal
{
    /**
     * 当前 Dog 类中没有定义自己的成员。
     *
     * 但是因为 Dog 继承了 Animal，
     * 所以 Dog 对象可以使用 Animal 中的 public 成员：
     * name、age、eat()
     */
};

// Cat 类继承了 Animal
// 这里和 Dog 类的继承关系类似
class Cat : public Animal
{
    /**
     * Cat 类也继承了 Animal。
     *
     * 所以 Cat 对象同样可以使用 Animal 中的 public 成员：
     * name、age、eat()
     */
};


void test1()
{
    // 创建 Dog 对象
    Dog dog;

    // dog 对象本身属于 Dog 类，
    // 但是 Dog 继承了 Animal，
    // 所以 dog 可以调用 Animal 中的 public 成员函数 eat()
    dog.eat();

    // 创建 Cat 对象
    Cat cat;

    // cat 也可以调用从 Animal 中继承过来的 eat()
    cat.eat();
}


int main(int argc, char *argv[])
{
    // 测试继承后，子类对象是否可以使用父类中的成员函数
    test1();

    return 0;
}