#include <iostream>

using std::cout;
using std::endl;

/**
 * 类的声明:可以多次声明
 * class 类名;
 * 类的定义:
 * class 类名:{
 *     // 类体
 *     数据成员--->属性的集合
 *     成员函数--->行为的集合
 * };
 *
 * 命名规范:
 * 驼峰命名法:
 * 1.小驼峰: 单个单词小写, 多个单词,第一个单词小写
 * 后续单词的首字母大写
 * student,  getMaxValue
 * 2.大驼峰: 单个单词首字母大写,多个单词,第一个单词首字母大写
 * 后续单词的首字母大写
 * Dog    MaxValue
 *
 * 程序中的结构命名:
 * 1.变量 : 小驼峰 user, userName
 * 2.常量 : 全部大写MAX
 * 3.函数名: 小驼峰
 * 4.类名: 大驼峰命名
 */

// 类的声明
class MyClass;
class MyClass;

// 类的定义
class MyClass
{
    // 属性集合
    // 行为的集合
public:
    // 成员函数的声明和实现写在一起
    // 默认情况下是内联函数
    void func(){
        cout << "func()" << endl;
    }

    // 声明和实现分开写
    void func2();

    //类中的数据成员,为了区分,会加
    //一个m_表示这是类中的数据成员
    int m_data;
    double m_data2;
    int _data3;

    void setData(int data)
    {
        m_data = data; //加m_以示区分
    }
};

// 在类的外部实现成员函数
// 需要使用类名作用域方式
void MyClass:: func2()
{
    cout << "func2()" << endl;
}

void test1()
{

}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

