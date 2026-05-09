#include <iostream>   // 用于 cout 输出
#include <fstream>    // 用于 ifstream 文件读取
#include <sstream>    // 用于 istringstream 字符串流解析
#include <vector>     // 用于 vector 容器
#include <string>     // 用于 string 字符串

using namespace std;

class PersonInfo
{
public:
    // 默认构造函数
    // = default 表示使用编译器自动生成的默认构造函数
    PersonInfo() = default;

    // 设置姓名
    // 参数 name 是外部传进来的姓名
    void setName(string& name);

    // 设置电话号码集合
    // 参数 phones 是外部传进来的电话号码 vector
    void setPhones(vector<string>& phones);

    // 打印当前对象中的个人信息
    void print();

private:
    // 人名
    string m_name;
    // 电话号码
    // 因为一个人可能有多个电话号码，所以使用 vector<string>
    vector<string> m_phones;
};

// setName 函数的类外实现
void PersonInfo::setName(string& name)
{
    m_name = name;
}

// setPhones 函数的类外实现
void PersonInfo::setPhones(vector<string>& phones)
{
    m_phones = phones;
}

// print 函数的类外实现
void PersonInfo::print()
{
    cout << "姓名：" << m_name << endl;
    cout << "电话：" ;
    // 遍历 m_phones 容器，依次输出每一个电话号码
    for (const string& phone : m_phones)
    {
        cout << phone << " ";
    }
    cout << endl;
    cout << "----------------" << endl;
}

int main()
{
    // 创建一个 vector 容器，用来保存所有人的信息
    // 每个元素都是一个 PersonInfo 对象
    vector<PersonInfo> personInfos;

    // 创建文件输入流对象，并尝试打开 phone.txt 文件
    ifstream ifs{"phone.txt"};

    // 判断文件是否成功打开
    if(!ifs.is_open())
    {
        cout << "文件打开失败，请检查 phone.txt 是否存在。" << endl;
        return -1;
    }

    // line 用来保存从文件中读取到的一整行内容
    string line;

    // 使用 getline 一行一行读取文件内容
    // 每成功读取一行，就进入一次 while 循环
    while (getline(ifs, line))
    {
        // 如果读到的是空行，就跳过这一行
        // 防止空行导致解析出错
        if (line.empty())
        {
            continue;
        }

        // 创建字符串输入流 iss
        // 它的作用是把一整行字符串 line 当成输入流来读取
        istringstream iss(line);

        // 用来保存姓名
        string name;
        // 用来保存当前这个人的所有电话号码
        vector<string> phones;

        // 先从这一行中读取第一个字符串，作为姓名
        iss >> name;

        // phone 用来临时保存每次读取到的电话号码
        string phone;
        // 继续从这一行中读取后面的内容
        // 只要还能读到字符串，就说明还有电话号码
        while (iss >> phone)
        {
            // 把读取到的电话号码加入 phones 容器
            phones.push_back(phone);
        }

        // 创建一个 PersonInfo 对象，用来保存当前这一行解析出来的信息
        PersonInfo person;
        // 设置当前对象的姓名
        person.setName(name);
        // 设置当前对象的电话号码集合
        person.setPhones(phones);
        // 把当前这个人的信息对象加入总容器 personInfos 中
        personInfos.push_back(person);
    }

    // 文件读取完毕后，关闭文件
    ifs.close();

    // 遍历 personInfos 容器，输出每个人的信息
    for (PersonInfo& person : personInfos)
    {
        person.print();
    }

    return 0;
}