需求:
存在一个phone.txt文件, 里面保存的是个人信息, 有人名 和 电话号码组成, 一个人可能有多个手机号

比如:
zs 13511111111 13522222222
ls 3988124 13633333333
ww 138344444444

定义如下的PersonInfo类型, 请解析该phone.txt文件内容, 
封装成对象, 并存入vector<PersonInfo> personInfos 的容器中, 
并遍历该数据容器, 打印输出PersonInfo中的个人信息

// 定义个人信息类
class PersonInfo
{
public:
    PersonInfo() = default;
    void setName(string & name);
    void setPhones(vector<string> & phones);
    void print();

private:
    // 人名
    string m_name;
    // 电话号码 一个人可能有多个
    vector<string> m_phones;

本题的本质是：**从文本文件中读取每一行数据，把每一行转换成一个 `PersonInfo` 对象，再把这些对象放进 `vector<PersonInfo>` 容器中，最后遍历输出。**

# 一、题目需求拆解

题目给了一个 `phone.txt` 文件，内容类似：

```txt
zs 13511111111 13522222222
ls 3988124 13633333333
ww 138344444444
```

每一行代表一个人的信息。

以第一行为例：

```txt
zs 13511111111 13522222222
```

可以拆成：

```txt
姓名: zs
手机号1: 13511111111
手机号2: 13522222222
```

也就是说：

* 每一行的第一个数据是人名
* 每一行后面的数据都是电话号码
* 一个人可能有多个电话号码
* 电话号码数量不固定

所以我们不能写死成：

```cpp
iss >> name >> phone1 >> phone2;
```

因为有的人可能只有一个号码，也可能有三个、四个号码。

因此更合适的方式是：

```cpp
iss >> name;

while (iss >> phone)
{
    phones.push_back(phone);
}
```

---

# 二、涉及到的几个重要知识点

## 1. `ifstream`

`ifstream` 是 C++ 中用来读取文件的类。

它需要包含头文件：

```cpp
#include <fstream>
```

打开文件：

```cpp
ifstream ifs("phone.txt");
```

判断是否打开成功：

```cpp
if (!ifs.is_open())
{
    cout << "文件打开失败" << endl;
    return 1;
}
```

---

## 2. `getline`

`getline` 可以一整行一整行地读取文件内容。

例如：

```cpp
string line;

while (getline(ifs, line))
{
    cout << line << endl;
}
```

如果 `phone.txt` 里有三行数据，那么循环就会执行三次。

---

## 3. `istringstream`

这是本题最关键的知识点。

`getline` 读出来的是一整行字符串，比如：

```cpp
"zs 13511111111 13522222222"
```

但是我们还需要把这一整行拆成：

```cpp
"zs"
"13511111111"
"13522222222"
```

这时就可以使用 `istringstream`。

它需要包含头文件：

```cpp
#include <sstream>
```

使用方式：

```cpp
istringstream iss(line);
```

这样 `iss` 就可以像 `cin` 一样读取这一行里的数据：

```cpp
iss >> name;
iss >> phone;
```

---

## 4. `vector`

因为一个人可能有多个手机号，所以不能只用一个 `string` 保存电话号码。

应该使用：

```cpp
vector<string> phones;
```

例如：

```cpp
phones.push_back("13511111111");
phones.push_back("13522222222");
```

然后 `phones` 中就保存了这个人的所有电话号码。

---

## 5. `vector<PersonInfo>`

题目要求把解析出来的对象存入：

```cpp
vector<PersonInfo> personInfos;
```

它的含义是：这个容器中存放很多个 `PersonInfo` 对象。

例如：

```cpp
personInfos[0]  // zs 的信息
personInfos[1]  // ls 的信息
personInfos[2]  // ww 的信息
```

---

# 三、完整详细注释版代码

```cpp
#include <iostream>   // 用于 cout 输出
#include <fstream>    // 用于 ifstream 文件读取
#include <sstream>    // 用于 istringstream 字符串流解析
#include <vector>     // 用于 vector 容器
#include <string>     // 用于 string 字符串

using namespace std;

// 定义个人信息类
class PersonInfo
{
public:
    // 默认构造函数
    // PersonInfo() = default 表示使用编译器自动生成的默认构造函数
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
    // 一个人可能有多个电话号码，所以使用 vector<string>
    vector<string> m_phones;
};

// setName 函数的类外实现
void PersonInfo::setName(string& name)
{
    // 把传进来的 name 保存到成员变量 m_name 中
    m_name = name;
}

// setPhones 函数的类外实现
void PersonInfo::setPhones(vector<string>& phones)
{
    // 把传进来的 phones 保存到成员变量 m_phones 中
    m_phones = phones;
}

// print 函数的类外实现
void PersonInfo::print()
{
    // 输出姓名
    cout << "姓名: " << m_name << endl;

    // 输出电话号码提示
    cout << "电话: ";

    // 遍历 m_phones 容器，依次输出每一个电话号码
    for (const string& phone : m_phones)
    {
        cout << phone << " ";
    }

    cout << endl;

    // 分隔线，让输出结果更清晰
    cout << "----------------" << endl;
}

int main()
{
    // 创建一个 vector 容器，用来保存所有人的信息
    // 每个元素都是一个 PersonInfo 对象
    vector<PersonInfo> personInfos;

    // 创建文件输入流对象，并尝试打开 phone.txt 文件
    ifstream ifs("phone.txt");

    // 判断文件是否成功打开
    // 如果文件不存在，或者路径不对，就会打开失败
    if (!ifs.is_open())
    {
        cout << "文件打开失败，请检查 phone.txt 是否存在。" << endl;
        return 1; // 返回 1 表示程序异常结束
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
        //
        // 例如 line 是：
        // "zs 13511111111 13522222222"
        //
        // 那么 iss 就可以依次读取出：
        // "zs"
        // "13511111111"
        // "13522222222"
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
```

---

# 四、代码执行流程详细分析

假设 `phone.txt` 内容是：

```txt
zs 13511111111 13522222222
ls 3988124 13633333333
ww 138344444444
```

程序开始后：

```cpp
vector<PersonInfo> personInfos;
```

此时容器是空的。

---

## 第一次循环

读取第一行：

```txt
zs 13511111111 13522222222
```

执行：

```cpp
istringstream iss(line);
```

然后：

```cpp
iss >> name;
```

此时：

```cpp
name = "zs"
```

接着进入循环读取电话号码：

```cpp
while (iss >> phone)
```

第一次读取：

```cpp
phone = "13511111111"
```

加入容器：

```cpp
phones = {"13511111111"}
```

第二次读取：

```cpp
phone = "13522222222"
```

加入容器：

```cpp
phones = {"13511111111", "13522222222"}
```

接着没有数据了，循环结束。

然后创建对象：

```cpp
PersonInfo person;
person.setName(name);
person.setPhones(phones);
personInfos.push_back(person);
```

此时：

```cpp
personInfos[0] = zs 的信息
```

---

## 第二次循环

读取第二行：

```txt
ls 3988124 13633333333
```

解析后：

```cpp
name = "ls"
phones = {"3988124", "13633333333"}
```

加入容器后：

```cpp
personInfos[1] = ls 的信息
```

---

## 第三次循环

读取第三行：

```txt
ww 138344444444
```

解析后：

```cpp
name = "ww"
phones = {"138344444444"}
```

加入容器后：

```cpp
personInfos[2] = ww 的信息
```

---

# 五、为什么电话号码要用 `string`，而不是 `int` 或 `long long`？

虽然电话号码看起来像数字，但它更适合用字符串保存。

原因有几个：

## 1. 电话号码不需要做数学运算

比如手机号不会拿来做：

```cpp
13511111111 + 13522222222
```

所以没有必要用数字类型。

## 2. 电话号码可能很长

普通 `int` 容量不够大，容易溢出。

## 3. 电话号码可能以 0 开头

比如固定电话、区号等可能是：

```txt
01088888888
```

如果用整数保存，前面的 `0` 可能会丢失。

所以更安全的做法是：

```cpp
string phone;
```

---

# 六、为什么要用 `getline`，而不是直接用 `ifs >> name >> phone`？

因为每个人的电话号码数量不固定。

如果直接用：

```cpp
ifs >> name >> phone;
```

只能读取一个姓名和一个电话号码，无法判断一行里到底有几个电话号码。

而使用：

```cpp
getline(ifs, line)
```

可以先拿到一整行，再在这一行内部解析。

这样可以明确知道：

```txt
这一行属于同一个人
```

不会把下一行的数据错误地读进来。

---

# 七、可以给类增加构造函数吗？

可以，不过题目已经给了 setter 函数，所以按照题目写就可以。

如果想写得更简洁，可以给 `PersonInfo` 增加一个带参构造函数：

```cpp
PersonInfo(string name, vector<string> phones)
{
    m_name = name;
    m_phones = phones;
}
```

这样主函数中可以简化成：

```cpp
PersonInfo person(name, phones);
personInfos.push_back(person);
```

但是如果老师要求使用题目给出的接口，就不要随意修改类定义。

---

# 八、一个更推荐的改进版本

题目给的函数声明是：

```cpp
void setName(string& name);
void setPhones(vector<string>& phones);
```

这能运行，但不够规范。

更推荐写成：

```cpp
void setName(const string& name);
void setPhones(const vector<string>& phones);
```

原因是：

* `setName` 只是读取 `name` 的值，并不会修改它
* `setPhones` 只是复制 `phones`，也不会修改它
* 加上 `const` 更安全
* 也能接收临时对象和常量对象

改进版如下：

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class PersonInfo
{
public:
    PersonInfo() = default;

    // 使用 const 引用，表示不会修改传入的 name
    void setName(const string& name);

    // 使用 const 引用，表示不会修改传入的 phones
    void setPhones(const vector<string>& phones);

    void print() const;

private:
    string m_name;
    vector<string> m_phones;
};

void PersonInfo::setName(const string& name)
{
    m_name = name;
}

void PersonInfo::setPhones(const vector<string>& phones)
{
    m_phones = phones;
}

void PersonInfo::print() const
{
    cout << "姓名: " << m_name << endl;
    cout << "电话: ";

    for (const string& phone : m_phones)
    {
        cout << phone << " ";
    }

    cout << endl;
    cout << "----------------" << endl;
}

int main()
{
    vector<PersonInfo> personInfos;

    ifstream ifs("phone.txt");

    if (!ifs.is_open())
    {
        cout << "文件打开失败，请检查 phone.txt 是否存在。" << endl;
        return 1;
    }

    string line;

    while (getline(ifs, line))
    {
        if (line.empty())
        {
            continue;
        }

        istringstream iss(line);

        string name;
        vector<string> phones;

        iss >> name;

        string phone;
        while (iss >> phone)
        {
            phones.push_back(phone);
        }

        PersonInfo person;
        person.setName(name);
        person.setPhones(phones);

        personInfos.push_back(person);
    }

    ifs.close();

    for (const PersonInfo& person : personInfos)
    {
        person.print();
    }

    return 0;
}
```

---

# 九、作业提交建议

如果你的老师要求“按照题目给出的类定义完成”，建议你提交第三部分那个版本，因为它严格保留了：

```cpp
void setName(string& name);
void setPhones(vector<string>& phones);
```

如果老师允许你做规范化优化，可以提交第八部分的改进版本。

本题最核心的代码是这几句：

```cpp
while (getline(ifs, line))
{
    istringstream iss(line);

    string name;
    vector<string> phones;

    iss >> name;

    string phone;
    while (iss >> phone)
    {
        phones.push_back(phone);
    }

    PersonInfo person;
    person.setName(name);
    person.setPhones(phones);
    personInfos.push_back(person);
}
```

只要理解这段，整个题目就基本掌握了。
