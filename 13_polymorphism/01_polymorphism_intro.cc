#include <iostream>

using std::cout;
using std::endl;

/**
 * 多态：同一条指令，作用于不同的子类对象时，表现出不同的行为。
 *
 * 代码中的体现：
 * 1. 在继承关系的前提下，使用父类类型的指针或引用接收子类对象；
 * 2. 通过父类指针或引用调用父子类中同名的虚函数；
 * 3. 程序运行时会根据实际指向的子类对象，调用对应子类重写后的函数。
 *
 * 这种机制也叫“动态多态”或“运行时多态”。
 */

class Phone
{
public:
    // 多态基类建议提供虚析构函数，方便以后通过父类指针安全释放子类对象
    virtual ~Phone() = default;

    // 纯虚函数：要求子类必须重写该函数，Phone 因此成为抽象类
    virtual void aiAssistant() = 0;
};

class Xiaomi : public Phone
{
public:
    // override 表示重写父类虚函数，可帮助编译器检查函数签名是否正确
    virtual void aiAssistant() override
    {
        cout << "小爱同学，今天天气怎么样？" << endl;
    }
};

class Huawei : public Phone
{
public:
    virtual void aiAssistant() override
    {
        cout << "小艺小艺，今天是星期几？" << endl;
    }
};

class Apple : public Phone
{
public:
    virtual void aiAssistant() override
    {
        cout << "嘿Siri，今天中午吃什么？" << endl;
    }
};

class Vivo : public Phone
{
public:
    virtual void aiAssistant() override
    {
        cout << "小V小V，今天晚上吃什么？" << endl;
    }
};

void test1()
{
    Xiaomi phone1;
    Huawei phone2;
    Apple phone3;

    Phone *p;

    // 父类指针接收子类对象地址
    p = &phone1;

    // 通过父类指针调用虚函数，会执行实际子类对象中的重写版本
    p->aiAssistant();

    p = &phone2;
    p->aiAssistant();

    p = &phone3;
    p->aiAssistant();
}

// 处理小米手机
void handlePhone1(Xiaomi *p)
{
    p->aiAssistant();
}

// 处理华为手机
void handlePhone2(Huawei *p)
{
    p->aiAssistant();
}

// 处理苹果手机
void handlePhone3(Apple *p)
{
    p->aiAssistant();
}

// 处理 Vivo 手机
void handlePhone4(Vivo *p)
{
    p->aiAssistant();
}

// 使用父类指针作为参数，可以统一处理所有 Phone 的子类对象。
// 这样不需要为每个子类都单独提供一个 handle 函数，扩展性更好。
void handlePhone(Phone *p)
{
    p->aiAssistant();
}

void test2()
{
    Xiaomi phone1;
    Huawei phone2;
    Apple phone3;
    Vivo phone4;

    // 下面这些写法需要针对每个子类分别提供函数，代码复用性较差
    /* handlePhone1(&phone1); */
    /* handlePhone2(&phone2); */
    /* handlePhone3(&phone3); */
    /* handlePhone4(&phone4); */

    // 使用父类指针统一接收不同子类对象，体现多态
    handlePhone(&phone1);
    handlePhone(&phone2);
    handlePhone(&phone3);
    handlePhone(&phone4);
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();

    return 0;
}