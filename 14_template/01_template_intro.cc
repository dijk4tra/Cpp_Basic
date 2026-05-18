#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

/**
 * 模板：把类型参数化，像函数参数一样传递给代码。
 * 模板编程也称为泛型编程，是一种通用编程技术。
 *
 * 模板主要分为两类：
 * 1. 函数模板：把模板应用在函数上
 * 2. 类模板：把模板应用在类上
 *
 * 模板的本质：
 * 模板本身不是具体的函数或类，而是一个“代码生成器”。
 * 在编译期间，编译器会根据使用时提供的具体类型生成对应的代码。
 *
 * 例如：
 * 函数模板实例化后，会生成具体的函数，称为模板函数。
 * 类模板实例化后，会生成具体的类，称为模板类。
 *
 * 由模板生成具体代码的过程，称为实例化。
 *
 * 实例化分为：
 * 1. 显式实例化：明确指定模板参数类型
 * 2. 隐式实例化：不指定模板参数类型，由编译器自动推导
 */


/*
int add(int a, int b)
{
    return a + b;
}

double add(double a, double b)
{
    return a + b;
}

string add(string a, string b)
{
    return a + b;
}

void test1()
{
    add(1, 2);
    add(1.1, 2.2);
}
*/


// 函数模板：把模板应用在函数上
// template：定义模板的关键字
// typename T：声明一个类型参数 T，T 可以代表任意类型
template <typename T>
T add(T a, T b)
{
    cout << "使用了模板" << endl;
    return a + b;
}
// 函数模板的好处：代码更简洁，可复用性更强

void test1()
{
    // 隐式实例化：不指定类型，由编译器根据实参自动推导
    add(1, 2);          // 推导出 add<int>(int, int)
    add(1.1, 2.2);      // 推导出 add<double>(double, double)

    string s1 = "abc";
    string s2 = "bcd";
    cout << add(s1, s2) << endl; // 推导出 add<string>(string, string)

    // 显式实例化：明确指定模板参数类型
    add<int>(1, 2);
}


// 类模板：把模板应用在类上
// T 可以作为成员函数的参数类型、返回值类型，也可以作为数据成员的类型
template <typename T>
class Box
{
public:
    Box(T data)
    : m_data(data)
    {}

private:
    T m_data;
};


class Point
{
};


void test2()
{
    // STL 中大量使用了模板
    vector<int> v1;
    vector<string> v2;
    vector<Point> v3;

    map<int, int> m1;
    map<int, string> m2;

    // 显式指定类模板参数类型
    Box<int> box1{100};
    Box<double> box2{1.1};

    // C++17 起支持类模板参数推导，也可以写成：
    // Box box3{100};      // 推导出 Box<int>
    // Box box4{1.1};      // 推导出 Box<double>
}


int main(int argc, char *argv[])
{
    test1();

    return 0;
}