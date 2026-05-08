# 一、题目要求拆解

题目是：

> 统计一篇英文文章 `The_Holy_Bible.txt` 中出现的单词和词频。

输入：

```txt
某篇文章的绝对路径
```

例如：

```txt
/home/student/The_Holy_Bible.txt
```

或者 Windows 下：

```txt
D:\test\The_Holy_Bible.txt
```

输出：

```txt
dict.txt
```

文件内容格式为：

```txt
a 66
abandon 77
public 88
...
```

也就是说，每一行包含两个部分：

```txt
单词 词频
```

---

# 二、我们要解决的核心问题

这道题看似简单，但里面有几个关键点：

## 1. 什么算作“单词”？

英文文章里不只有字母，还有：

```txt
God said, Let there be light.
```

其中包含：

```txt
空格
逗号 ,
句号 .
换行符
冒号 :
分号 ;
引号 "
```

这些都不应该算进单词里。

所以我们可以规定：

> 只要是英文字母，就属于单词的一部分；只要不是英文字母，就认为当前单词结束。

例如：

```txt
God, said: Let there be light.
```

处理后得到：

```txt
god
said
let
there
be
light
```

---

## 2. 大小写是否区分？

通常词频统计不区分大小写。

也就是说：

```txt
God
god
GOD
```

都应该统计成同一个单词：

```txt
god
```

所以读取字符时，需要把大写字母统一转成小写。

---

## 3. 单词第二次出现怎么办？

比如读到了：

```txt
god
```

如果 `_dict` 里面已经有了 `god`，就不能再插入一个新的 `god`。

而是应该让原来的词频加一：

```cpp
god 1
```

变成：

```cpp
god 2
```

---

# 三、数据结构设计

题目给了一个结构体：

```cpp
struct Record
{
    string _word;
    int _frequency;
};
```

这个结构体表示一条词典记录。

例如：

```cpp
Record record;
record._word = "god";
record._frequency = 10;
```

就表示：

```txt
god 10
```

---

# 四、类的设计

题目要求设计一个 `Dictionary` 类：

```cpp
class Dictionary
{
public:
    void read(const std::string &filename);
    void store(const std::string &filename);

private:
    vector<Record> _dict;
};
```

这个类可以理解成一个“词典对象”。

它内部有一个成员变量：

```cpp
vector<Record> _dict;
```

用来存放所有单词和词频。

例如统计完之后，`_dict` 里面可能长这样：

```txt
下标  单词      词频
0     the       62103
1     and       38848
2     god       4112
3     light     272
...
```

---

# 五、为什么用 `vector<Record>`？

因为题目提示我们使用 `vector`，所以这里用：

```cpp
vector<Record> _dict;
```

它的含义是：

> `_dict` 是一个动态数组，数组里面每个元素都是一个 `Record`。

每个 `Record` 包含：

```cpp
string _word;
int _frequency;
```

也就是：

```txt
单词 + 出现次数
```

---

# 六、程序整体流程

整个程序可以分成 4 个步骤：

```txt
1. main 函数中输入文章路径
2. 创建 Dictionary 对象
3. 调用 read() 读取文章并统计词频
4. 调用 store() 把结果写入 dict.txt
```

对应代码逻辑是：

```cpp
int main()
{
    string filepath;
    cin >> filepath;

    Dictionary dict;
    dict.read(filepath);
    dict.store("dict.txt");

    return 0;
}
```

---

# 七、最重要的函数：read()

`read()` 的任务是：

> 打开文章文件，读取内容，提取单词，统计词频。

我们采用“逐字符读取”的方式。

例如文章中有：

```txt
God said, Let there be light.
```

程序逐个字符读取：

```txt
G
o
d
,
 
s
a
i
d
,
 
L
e
t
...
```

当读到字母时，就拼接到当前单词里。

当读到非字母时，就说明当前单词结束了。

---

# 八、为什么不用 `ifstream >> word`？

你可能会想到：

```cpp
while (ifs >> word)
```

这样确实可以按空格读取字符串。

但是它有一个问题：标点符号会和单词一起读进来。

比如：

```txt
God said, Let there be light.
```

读出来可能是：

```txt
God
said,
Let
there
be
light.
```

注意：

```txt
said,
light.
```

后面带着逗号和句号。

这样统计时，`said` 和 `said,` 会被认为是两个不同的词。

所以这道题更推荐逐字符读取。

---

# 九、单词插入逻辑

为了让代码更清晰，我们单独写一个私有函数：

```cpp
void insertWord(const string &word);
```

它的作用是：

> 把一个单词加入词典，如果已经存在，就让词频加一。

逻辑如下：

```txt
如果 word 是空字符串：
    直接返回

遍历 _dict：
    如果找到相同单词：
        词频 +1
        返回

如果遍历结束还没有找到：
    创建新的 Record
    把 word 放进去
    频率设置为 1
    push_back 到 _dict
```

---

# 十、为什么要判断空字符串？

比如文章里有多个连续符号：

```txt
God,,, said...
```

当程序读到第一个逗号时，会尝试插入当前单词 `god`。

但后面的第二个逗号、第三个逗号之间没有新单词，此时 `word` 是空的。

如果不判断空字符串，可能会把空字符串也插入词典，这是不对的。

所以需要：

```cpp
if (word.empty())
{
    return;
}
```

---

# 十一、为什么文件结束后还要再插入一次？

看这段文章：

```txt
Let there be light
```

最后一个单词 `light` 后面可能没有空格、句号或换行。

程序在读取字符时，只有遇到“非字母”才会插入单词。

如果文件最后直接结束，那么最后一个单词还保存在 `word` 中，没有被插入。

所以循环结束后需要再执行一次：

```cpp
insertWord(word);
```

这样可以保证最后一个单词不会漏掉。

---

# 十二、完整详细注释版代码

```cpp
#include <iostream>   // 标准输入输出流，使用 cin、cout
#include <fstream>    // 文件输入输出流，使用 ifstream、ofstream
#include <vector>     // 使用 vector 容器
#include <string>     // 使用 string 字符串
#include <cctype>     // 使用 isalpha、tolower 等字符处理函数

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

/*
    Record 表示词典中的一条记录。

    例如：
        _word = "god"
        _frequency = 20

    表示单词 god 出现了 20 次。
*/
struct Record
{
    string _word;      // 保存单词
    int _frequency;   // 保存该单词出现的次数，也就是词频
};

/*
    Dictionary 类用于完成词频统计。

    它的主要功能有两个：
        1. read()  ：读取文章，并统计每个单词的出现次数
        2. store() ：把统计结果写入指定文件

    私有成员：
        _dict ：保存所有单词和词频
*/
class Dictionary
{
public:
    /*
        read 函数：
            根据传入的文件名打开文章文件，
            读取文章内容，
            统计每个单词出现的次数。

        参数：
            filename：文章文件的路径
    */
    void read(const string &filename);

    /*
        store 函数：
            把 _dict 中保存的单词和词频写入文件。

        参数：
            filename：输出文件的路径，例如 "dict.txt"
    */
    void store(const string &filename);

private:
    /*
        insertWord 函数：
            把一个单词插入到 _dict 中。

            如果该单词已经存在：
                词频加 1

            如果该单词不存在：
                新建一条 Record，
                词频设置为 1，
                插入 vector。
    */
    void insertWord(const string &word);

private:
    /*
        _dict 是一个 vector 容器。

        vector<Record> 表示：
            vector 中保存的每一个元素都是 Record 类型。

        每个 Record 里面又保存：
            1. 一个单词
            2. 该单词出现的次数
    */
    vector<Record> _dict;
};

/*
    insertWord 函数的实现。

    这个函数只负责处理“一个完整单词”的统计。
*/
void Dictionary::insertWord(const string &word)
{
    // 如果 word 是空字符串，说明当前没有有效单词，直接返回
    // 例如连续遇到多个标点符号时，就可能出现空字符串
    if (word.empty())
    {
        return;
    }

    /*
        遍历 _dict，查找当前单词是否已经出现过。

        _dict.size() 表示当前 vector 中元素的个数。
        i 从 0 开始，依次访问每一个 Record。
    */
    for (size_t i = 0; i < _dict.size(); ++i)
    {
        /*
            如果 _dict 中某个 Record 的 _word
            和当前传入的 word 相同，
            说明这个单词之前已经统计过。
        */
        if (_dict[i]._word == word)
        {
            // 词频加 1
            ++_dict[i]._frequency;

            // 找到之后就可以结束函数，避免继续遍历
            return;
        }
    }

    /*
        如果程序执行到这里，
        说明 for 循环已经遍历完 _dict，
        但是没有找到相同的单词。

        因此需要创建一条新的记录。
    */
    Record record;

    // 保存新单词
    record._word = word;

    // 第一次出现，所以词频为 1
    record._frequency = 1;

    // 把这条新记录加入 vector 的末尾
    _dict.push_back(record);
}

/*
    read 函数的实现。

    功能：
        读取文章内容，
        从文章中提取单词，
        并调用 insertWord() 统计词频。
*/
void Dictionary::read(const string &filename)
{
    /*
        创建输入文件流对象 ifs，
        并尝试打开 filename 对应的文件。
    */
    ifstream ifs(filename);

    /*
        判断文件是否成功打开。

        如果路径错误、文件不存在、权限不足，
        都可能导致打开失败。
    */
    if (!ifs)
    {
        cout << "文件打开失败: " << filename << endl;
        return;
    }

    char ch;       // 用来保存每次从文件中读取到的一个字符
    string word;   // 用来临时保存正在读取的一个单词

    /*
        ifs.get(ch) 表示从文件中读取一个字符，
        并存入变量 ch。

        只要读取成功，循环就继续；
        如果读到文件末尾，循环结束。
    */
    while (ifs.get(ch))
    {
        /*
            isalpha(ch) 用来判断 ch 是否是英文字母。

            如果 ch 是：
                'a' 到 'z'
                或 'A' 到 'Z'
            就认为它是单词的一部分。

            static_cast<unsigned char>(ch) 是为了避免
            某些特殊字符导致 isalpha 行为异常。
        */
        if (isalpha(static_cast<unsigned char>(ch)))
        {
            /*
                如果当前字符是字母，就把它加入 word。

                tolower(ch) 用来把大写字母转换成小写字母。
                这样 God、god、GOD 都会统计为 god。
            */
            word += static_cast<char>(
                tolower(static_cast<unsigned char>(ch))
            );
        }
        else
        {
            /*
                如果当前字符不是字母，
                说明一个单词结束了。

                例如遇到：
                    空格
                    换行
                    逗号
                    句号
                    冒号
                    分号
                    引号
                    数字

                都会执行这里。
            */
            insertWord(word);

            /*
                当前单词已经统计完成，
                清空 word，
                准备读取下一个单词。
            */
            word.clear();
        }
    }

    /*
        循环结束后，还需要再插入一次 word。

        原因：
            如果文件最后一个字符是字母，
            那么最后一个单词后面没有非字母字符，
            它就不会在 while 循环中被插入。

        例如文件内容为：
            In the beginning

        最后的 beginning 后面如果没有空格或标点，
        就需要这里补充处理。
    */
    insertWord(word);

    // 关闭输入文件
    ifs.close();
}

/*
    store 函数的实现。

    功能：
        把 _dict 中保存的所有单词和词频写入文件。
*/
void Dictionary::store(const string &filename)
{
    /*
        创建输出文件流对象 ofs，
        并打开 filename 对应的文件。

        如果文件不存在，一般会自动创建。
        如果文件已经存在，会覆盖原来的内容。
    */
    ofstream ofs(filename);

    /*
        判断输出文件是否成功打开。

        如果没有写权限、路径非法等，
        可能打开失败。
    */
    if (!ofs)
    {
        cout << "文件打开失败: " << filename << endl;
        return;
    }

    /*
        遍历 _dict 中的所有记录。

        每一条记录写成一行：
            单词 空格 词频
    */
    for (size_t i = 0; i < _dict.size(); ++i)
    {
        ofs << _dict[i]._word
            << " "
            << _dict[i]._frequency
            << endl;
    }

    // 关闭输出文件
    ofs.close();
}

/*
    main 函数是程序入口。
*/
int main()
{
    string filepath;

    /*
        提示用户输入文章的绝对路径。

        例如：
            Linux / macOS:
                /home/student/The_Holy_Bible.txt

            Windows:
                D:\test\The_Holy_Bible.txt
    */
    cout << "请输入文章的绝对路径: ";

    /*
        读取用户输入的文件路径。

        注意：
            如果路径中包含空格，cin >> filepath 只能读取到空格前面的部分。

        如果你的文件路径中有空格，可以改成：
            getline(cin, filepath);
    */
    cin >> filepath;

    /*
        创建 Dictionary 对象 dict。
    */
    Dictionary dict;

    /*
        调用 read 函数读取文章，
        并统计单词词频。
    */
    dict.read(filepath);

    /*
        调用 store 函数，
        把统计结果保存到 dict.txt。

        dict.txt 会生成在程序当前运行目录下。
    */
    dict.store("dict.txt");

    cout << "词典文件 dict.txt 已生成。" << endl;

    return 0;
}
```

---

# 十三、用一个小例子模拟程序执行过程

假设文章内容是：

```txt
God said, God is good.
```

程序逐字符处理：

## 第一步：读取 `G o d`

```cpp
word = "god"
```

## 第二步：读到空格或逗号

调用：

```cpp
insertWord("god");
```

此时 `_dict` 为空，所以插入：

```txt
god 1
```

## 第三步：读取 `said`

调用：

```cpp
insertWord("said");
```

插入：

```txt
god 1
said 1
```

## 第四步：再次读取 `God`

转小写后还是：

```txt
god
```

调用：

```cpp
insertWord("god");
```

发现 `_dict` 中已经有 `god`，所以词频加一：

```txt
god 2
said 1
```

## 最终结果：

```txt
god 2
said 1
is 1
good 1
```

---

# 十四、关于排序的问题

题目示例中：

```txt
a 66
abandon 77
public 88
```

看起来像是按照字母顺序排列。

但是题目并没有明确说“一定要排序”。

上面的代码输出顺序是：

> 单词第一次出现的顺序。

如果老师要求按照字典序排序，可以在 `store()` 之前排序。

需要加头文件：

```cpp
#include <algorithm>
```

然后在 `store()` 函数中写文件之前加入：

```cpp
sort(_dict.begin(), _dict.end(), [](const Record &lhs, const Record &rhs) {
    return lhs._word < rhs._word;
});
```

排序后的 `store()` 可以这样写：

```cpp
void Dictionary::store(const string &filename)
{
    ofstream ofs(filename);

    if (!ofs)
    {
        cout << "文件打开失败: " << filename << endl;
        return;
    }

    sort(_dict.begin(), _dict.end(), [](const Record &lhs, const Record &rhs) {
        return lhs._word < rhs._word;
    });

    for (size_t i = 0; i < _dict.size(); ++i)
    {
        ofs << _dict[i]._word << " " << _dict[i]._frequency << endl;
    }

    ofs.close();
}
```

如果你的老师希望输出像“词典”一样从 `a` 到 `z` 排列，建议加上排序。

---

# 十五、如果路径里有空格怎么办？

原代码：

```cpp
cin >> filepath;
```

只能读取到空格前。

例如输入：

```txt
D:\my files\The_Holy_Bible.txt
```

实际只会读取：

```txt
D:\my
```

所以更稳妥的写法是：

```cpp
getline(cin, filepath);
```

对应 `main()` 可以改成：

```cpp
int main()
{
    string filepath;

    cout << "请输入文章的绝对路径: ";
    getline(cin, filepath);

    Dictionary dict;
    dict.read(filepath);
    dict.store("dict.txt");

    cout << "词典文件 dict.txt 已生成。" << endl;

    return 0;
}
```

---

# 十六、这份代码的复杂度

这份代码符合题目给的 `vector<Record>` 设计，但效率不是最高。

原因是每插入一个单词，都要遍历 `_dict` 查找是否已经存在：

```cpp
for (size_t i = 0; i < _dict.size(); ++i)
```

如果文章很长，单词很多，速度会比较慢。

不过对于初学 C++、并且题目要求使用 `vector<Record>` 的情况，这种写法非常适合作业练习。

如果以后学到 `map` 或 `unordered_map`，词频统计可以写得更简单、更高效。

---

# 十七、推荐你最终提交的版本

如果老师没有禁止排序，我建议提交下面这个版本：
它支持大小写统一、过滤标点、处理最后一个单词，并且输出按字典序排序。

```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::sort;

struct Record
{
    string _word;
    int _frequency;
};

class Dictionary
{
public:
    void read(const string &filename);
    void store(const string &filename);

private:
    void insertWord(const string &word);

private:
    vector<Record> _dict;
};

void Dictionary::insertWord(const string &word)
{
    if (word.empty())
    {
        return;
    }

    for (size_t i = 0; i < _dict.size(); ++i)
    {
        if (_dict[i]._word == word)
        {
            ++_dict[i]._frequency;
            return;
        }
    }

    Record record;
    record._word = word;
    record._frequency = 1;
    _dict.push_back(record);
}

void Dictionary::read(const string &filename)
{
    ifstream ifs(filename);

    if (!ifs)
    {
        cout << "文件打开失败: " << filename << endl;
        return;
    }

    char ch;
    string word;

    while (ifs.get(ch))
    {
        if (isalpha(static_cast<unsigned char>(ch)))
        {
            word += static_cast<char>(
                tolower(static_cast<unsigned char>(ch))
            );
        }
        else
        {
            insertWord(word);
            word.clear();
        }
    }

    insertWord(word);

    ifs.close();
}

void Dictionary::store(const string &filename)
{
    ofstream ofs(filename);

    if (!ofs)
    {
        cout << "文件打开失败: " << filename << endl;
        return;
    }

    sort(_dict.begin(), _dict.end(), [](const Record &lhs, const Record &rhs) {
        return lhs._word < rhs._word;
    });

    for (size_t i = 0; i < _dict.size(); ++i)
    {
        ofs << _dict[i]._word << " " << _dict[i]._frequency << endl;
    }

    ofs.close();
}

int main()
{
    string filepath;

    cout << "请输入文章的绝对路径: ";
    getline(cin, filepath);

    Dictionary dict;
    dict.read(filepath);
    dict.store("dict.txt");

    cout << "词典文件 dict.txt 已生成。" << endl;

    return 0;
}
```

---

你可以按这个顺序理解这道题：

```txt
文件 → 字符 → 单词 → Record → vector → dict.txt
```

这是这道作业最核心的思路。
