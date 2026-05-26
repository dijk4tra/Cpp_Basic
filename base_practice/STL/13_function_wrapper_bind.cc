#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

/**
 * 传统多态：
 * 强迫不同的类继承自同一个父类，通过虚函数表（vtable）在运行时动态查找。
 * 
 * 函数式多态：
 * 不同的类之间没有任何关联。只要它们的方法经过 std::bind 包装后，
 * 能够适配相同的 std::function 签名，就可以被统一塞进一个容器或传给同一个调用者。
 */

// ==================== 1. 定义完全无关的类 ====================
class Dog
{
public:
    void bark() const {
        cout << "汪汪！[来自 Dog 类的成员函数]" << endl;
    }
};

class Car {
public:
    // 注意：这个函数的签名带有参数，和 Dog::bark 不同
    void honk(const string& soundType) const {
        cout << soundType << "！[来自 Car 类的成员函数]" << endl;
    }
};

class Alarm {
public:
    void ring() const {
        cout << "滴滴！[来自 Alarm 类的成员函数]" << endl;
    }
};

// ==================== 2. 主函数：实现函数式多态 ====================
int main(int argc, char * argv[])
{
    // 实例化三个完全不相关的对象
    Dog myDog;
    Car myCar;
    Alarm myAlarm;

    // 声明一个统一的包装器容器，擦除具体类型，只保留行为签名：void()
    // 也就是说，只要不需要参数、没有返回值的调用，都能放进来
    vector<function<void()>> soundEmitters;

    // 使用 std::bind 将【对象实例】与【成员函数指针】绑定，消除类型的差异性
    // ① 绑定 Dog::bark
    soundEmitters.push_back(bind(&Dog::bark, &myDog));

    // ② 绑定 Car::honk
    // 特别注意：Car::honk 需要一个 string 参数。
    // 可以在 bind 时提前把参数 "哔哔" 绑定死，从而把它改成 void() 签名！
    soundEmitters.push_back(bind(&Car::honk, &myCar, "哔哔"));

    // ③ 绑定 Alarm::ring
    soundEmitters.push_back(bind(&Alarm::ring, &myAlarm));

    // ==================== 3. 动态遍历（多态展现） ====================
    std::cout << "--- 开始函数式多态调用 ---" << std::endl;
    for (const auto& emitSound : soundEmitters) {
        emitSound(); // 统一调用接口，无需关心背后是狗、是车还是闹钟
    }

    return 0;
}