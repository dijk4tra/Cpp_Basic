#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

/**
 * 张三养了三只狗
 * 1岁白色萨摩耶
 * 2岁黄白色柯基
 * 3岁黄色金毛
 *
 */

// 用变量的方式描述
void test1()
{
    int dog1Age = 1;
    string dog1Color = "白色";
    string dog1Name = "萨摩耶";

    int dog2Age = 2;
    string dog2Color = "黄白色";
    string dog2Name = "柯基";

    int dog3Age = 3;
    string dog3Color = "黄色";
    string dog3Name = "金毛";

    // 如果信息比较多,变量随着变多
    // 数据维护起来就比较麻烦
}

// 为了数据维护方便--->采用数组方式来描述
void test2()
{
    // 第一只狗的信息
    const char * dog1[] = {"1", "白色", "萨摩耶"};
    const char * dog2[] = {"2", "黄白色", "柯基"};
    const char * dog3[] = {"3", "黄色", "金毛"};
    cout << dog1[0] << " " << dog1[1] << " " << dog1[2] << endl;
    cout << dog2[0] << " " << dog2[1] << " " << dog2[2] << endl;
    cout << dog3[0] << " " << dog3[1] << " " << dog3[2] << endl;
    // 缺点:数据类型受到限制
    // 属性名和属性值之间的映射关系不明确
}

// 利用面向对象的思想来解决
class Dog
{
public:
    // 属性的集合
    int age;
    string color;
    string name;
    // 行为的集合
    void bark()
    {
        cout << "wwwwwwww!" << endl;
    }
};

void test3()
{
    // 根据class Dog创建对象(实例化)
    int num = 1;
    // dog1 ---> 对象名
    // Dog  ---> 数据类型
    Dog dog1;
    dog1.age = 1;
    dog1.name = "萨摩耶";
    dog1.color = "白色";
    
    Dog dog2;

    Dog dog3;

    cout << dog1.age << " " << dog1.name << " " << dog1.color << endl;
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

