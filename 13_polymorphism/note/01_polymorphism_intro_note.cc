#include <iostream>

using std::cout;
using std::endl;

/**
 * 多态 polymorphism：
 * 统一指令，针对不同的子类对象，
 * 表现出不同的行为。
 *
 * 本文件演示的是：
 * 运行时多态 dynamic polymorphism。
 *
 *
 * 运行时多态成立的条件：
 * 1. 必须有继承关系
 *    例如：
 *    Xiaomi、Huawei、Apple、Vivo 都继承自 Phone。
 *
 * 2. 子类必须重写父类中的虚函数
 *    父类中声明：
 *    virtual void aiAssistant() = 0;
 *
 *    子类中重写：
 *    virtual void aiAssistant() override
 *
 * 3. 通过父类的指针或者引用接收子类对象
 *    例如：
 *    Phone * p = &phone1;
 *
 * 4. 通过父类指针或者引用调用虚函数
 *    例如：
 *    p->aiAssistant();
 *
 *
 * 多态的好处：
 * 1. 接口统一
 *    不同品牌的手机都有 aiAssistant() 这个行为。
 *
 * 2. 扩展性更好
 *    新增一个手机品牌时，
 *    只需要新增一个子类并重写虚函数，
 *    不需要大量修改已有代码。
 *
 * 3. 降低代码耦合度
 *    handlePhone(Phone * p)
 *    不关心具体传入的是 Xiaomi、Huawei 还是 Apple，
 *    只关心它是不是 Phone 的子类。
 */

class Phone
{
public:
    /**
     * 虚函数 virtual function：
     * 父类中使用 virtual 修饰的成员函数，
     * 允许子类进行重写。
     *
     * 纯虚函数 pure virtual function：
     * 在虚函数后面写 = 0，
     * 表示这个函数没有默认实现，
     * 要求子类必须实现自己的版本。
     *
     * 只要一个类中包含纯虚函数，
     * 这个类就是抽象类 abstract class。
     *
     * 抽象类不能直接创建对象：
     * Phone phone; // error
     *
     * 但抽象类可以作为父类型，
     * 用指针或者引用接收子类对象。
     */
    virtual // 虚函数
    void aiAssistant() = 0;
};

class Xiaomi : public Phone
{
public:
    /**
     * 子类重写父类中的虚函数。
     *
     * override：
     * 用来告诉编译器：
     * 当前函数是对父类虚函数的重写。
     *
     * 好处：
     * 如果函数名、参数列表、const 属性等写错，
     * 编译器会直接报错，
     * 可以避免“本来想重写，实际没有重写”的问题。
     */
    virtual void aiAssistant() override
    {
        cout << "小爱同学，今天天气怎么样？" << endl;
    }
};

class Huawei : public Phone
{
public:
    // 重写 Phone 中的 aiAssistant()
    // 表现出 Huawei 自己的语音助手行为
    virtual void aiAssistant() override
    {
        cout << "小艺小艺，今天是星期几？" << endl;
    }
};

class Apple : public Phone
{
public:
    // 重写 Phone 中的 aiAssistant()
    // 表现出 Apple 自己的语音助手行为
    virtual void aiAssistant() override
    {
        cout << "嘿Siri，今天中午吃什么？" << endl;
    }
};

class Vivo : public Phone
{
public:
    // 重写 Phone 中的 aiAssistant()
    // 表现出 Vivo 自己的语音助手行为
    virtual void aiAssistant() override
    {
        cout << "小V小V，今天晚上吃什么？" << endl;
    }
};


void test1()
{
    // 创建不同子类对象
    Xiaomi phone1;
    Huawei phone2;
    Apple phone3;

    /**
     * 父类指针：
     * Phone * p;
     *
     * p 可以指向 Phone 的子类对象。
     * 这就是：
     * 父类型指针接收子类对象。
     */
    Phone *p;

    // 父类型指针或引用接收子类对象
    // p 的静态类型是 Phone *
    // 但是它实际指向的是 Xiaomi 对象
    p = &phone1;

    /**
     * 通过父类指针调用虚函数：
     * p->aiAssistant();
     *
     * 因为 aiAssistant() 是虚函数，
     * 所以程序运行时会根据 p 实际指向的对象类型，
     * 决定调用哪个版本的 aiAssistant()。
     *
     * 此时 p 指向 Xiaomi 对象，
     * 所以调用 Xiaomi::aiAssistant()。
     *
     * 这种机制叫做：
     * 动态绑定 dynamic binding
     * 或者
     * 运行时绑定 runtime binding。
     */
    p->aiAssistant();

    // p 改为指向 Huawei 对象
    // 同样调用 aiAssistant()
    // 但是实际执行的是 Huawei::aiAssistant()
    p = &phone2;
    p->aiAssistant();

    // p 改为指向 Apple 对象
    // 实际执行的是 Apple::aiAssistant()
    p = &phone3;
    p->aiAssistant();
}

// 处理小米手机
void handlePhone1(Xiaomi * p)
{
    // 参数类型写死为 Xiaomi *
    // 所以这个函数只能处理小米手机
    p->aiAssistant();
}

void handlePhone2(Huawei * p)
{
    // 参数类型写死为 Huawei *
    // 所以这个函数只能处理华为手机
    p->aiAssistant();
}

void handlePhone3(Apple * p)
{
    // 参数类型写死为 Apple *
    // 所以这个函数只能处理苹果手机
    p->aiAssistant();
}

void handlePhone4(Vivo * p)
{
    // 参数类型写死为 Vivo *
    // 所以这个函数只能处理 Vivo 手机
    p->aiAssistant();
}


/**
 * 上面 handlePhone1、handlePhone2、handlePhone3、handlePhone4 的问题：
 * 每增加一个新的手机品牌，
 * 就需要额外增加一个对应的 handle 函数。
 *
 * 例如新增 Oppo：
 * class Oppo : public Phone
 * {
 *     ...
 * };
 *
 * 如果不用多态，
 * 可能还需要继续写：
 * void handlePhone5(Oppo * p)
 * {
 *     p->aiAssistant();
 * }
 *
 * 这样代码扩展性比较差。
 *
 *
 * 使用多态以后：
 * 只需要提供一个统一的函数：
 * void handlePhone(Phone * p)
 *
 * 只要传入的是 Phone 的子类对象，
 * 都可以通过这个函数处理。
 */

// 提供一个函数可以进行复用，不需要针对每个子类都提供一个函数
// 扩展性更好，不需要每增加一个子类都提供一个handle函数
void handlePhone(Phone * p)
{
    /**
     * p 是父类指针，
     * 但它可以指向不同的子类对象。
     *
     * 调用虚函数 aiAssistant() 时，
     * 会根据 p 实际指向的对象类型，
     * 执行对应子类中的函数版本。
     */
    p->aiAssistant();
}

void test2()
{
    // 创建不同品牌的手机对象
    Xiaomi phone1;
    Huawei phone2;
    Apple phone3;
    Vivo phone4;

    /**
     * 如果不使用统一的父类指针参数，
     * 就需要为每一种具体类型写一个处理函数。
     *
     * 这种写法扩展性不好：
     * 每新增一个子类，
     * 都可能需要新增一个 handle 函数。
     */
    /* handlePhone1(&phone1); */
    /* handlePhone2(&phone2); */
    /* handlePhone3(&phone3); */
    /* handlePhone4(&phone4); */

    /**
     * 使用多态以后：
     * handlePhone 的参数是 Phone *，
     * 可以接收所有 Phone 的子类对象地址。
     *
     * 虽然调用的都是：
     * handlePhone(...)
     *
     * 但实际执行的 aiAssistant() 版本不同：
     * handlePhone(&phone1) -> Xiaomi::aiAssistant()
     * handlePhone(&phone2) -> Huawei::aiAssistant()
     * handlePhone(&phone3) -> Apple::aiAssistant()
     * handlePhone(&phone4) -> Vivo::aiAssistant()
     */
    handlePhone(&phone1);
    handlePhone(&phone2);
    handlePhone(&phone3);
    handlePhone(&phone4);
}

int main(int argc, char *argv[])
{
    // test1 演示：
    // 父类指针指向不同子类对象，
    // 调用同一个虚函数时表现出不同子类行为
    /* test1(); */

    // test2 演示：
    // 使用父类指针作为函数参数，
    // 提供统一接口处理不同子类对象
    test2();

    return 0;
}