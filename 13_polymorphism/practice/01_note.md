# 一、题目本质：做一个“单词索引系统”

这个程序要完成的事情类似于书后面的索引。

比如一本书后面可能有：

```txt
element: 62, 64, 153, 250, 398
map: 20, 43, 101
vector: 12, 45
```

意思是：

* `element` 这个单词出现在第 62、64、153、250、398 行
* `map` 出现在第 20、43、101 行
* `vector` 出现在第 12、45 行

我们的程序也是类似的。

程序分成两个阶段：

## 第一阶段：读取文件，建立索引

读取文件中的每一行。

对于每个单词：

1. 记录它总共出现了多少次
2. 记录它出现在哪些行
3. 保存每一行的原始文本，方便之后输出

---

## 第二阶段：查询单词，输出结果

用户输入一个单词，例如：

```txt
element
```

程序输出：

```txt
element occurs 125 times.
(line 62) element with a given key.
(line 64) second element with the same key.
...
```

---

# 二、为什么需要三个容器？

题目中提示了三个核心容器：

```cpp
vector<string> lines;
map<string, set<int>> wordNumbers;
map<string, int> dict;
```

我们分别解释。

---

## 1. `vector<string> _lines`

```cpp
vector<string> _lines;
```

它用于保存文件的原始每一行。

假设文件内容是：

```txt
hello world
hello c++
world hello
```

读取后：

```cpp
_lines[0] = "hello world";
_lines[1] = "hello c++";
_lines[2] = "world hello";
```

注意：

* 文件行号通常从 1 开始
* `vector` 下标从 0 开始

所以：

```cpp
第 1 行 -> _lines[0]
第 2 行 -> _lines[1]
第 3 行 -> _lines[2]
```

因此根据行号输出原文时，要写：

```cpp
_lines[lineNumber - 1]
```

---

## 2. `map<string, int> _dict`

```cpp
map<string, int> _dict;
```

它用于记录每个单词出现的总次数。

例如文件是：

```txt
hello world
hello c++
world hello
```

那么统计结果是：

```cpp
_dict["hello"] = 3;
_dict["world"] = 2;
_dict["c++"] = 1;
```

查询 `hello` 时，只要访问：

```cpp
_dict["hello"]
```

就能知道它出现了 3 次。

不过在查询阶段，一般不直接使用 `[]`，而是用 `find`。

原因后面讲。

---

## 3. `map<string, set<int>> _wordNumbers`

```cpp
map<string, set<int>> _wordNumbers;
```

它用于记录每个单词出现在哪些行。

例如：

```txt
hello world
hello c++
world hello
```

那么：

```cpp
_wordNumbers["hello"] = {1, 2, 3};
_wordNumbers["world"] = {1, 3};
_wordNumbers["c++"] = {2};
```

这里使用 `set<int>` 非常重要。

因为题目要求：

> 如果某单词在同一行中多次出现，程序将只显示该行一次。行号按升序显示。

`set` 正好满足这两个要求：

| 要求     | `set` 是否满足     |
| ------ | -------------- |
| 行号不重复  | 是，`set` 自动去重   |
| 行号升序输出 | 是，`set` 默认升序排列 |

比如这一行：

```txt
hello hello hello
```

假设这是第 5 行，程序会执行三次：

```cpp
_wordNumbers["hello"].insert(5);
_wordNumbers["hello"].insert(5);
_wordNumbers["hello"].insert(5);
```

但是 `set` 中最终只保存一个 `5`。

---

# 三、整体类设计

题目建议使用：

```cpp
class TextQuery
{
public:
    void readFile(const string &filename);
    void query(const string &word);

private:
    vector<string> _lines;
    map<string, set<int>> _wordNumbers;
    map<string, int> _dict;
};
```

我们可以理解为：

```cpp
TextQuery tq;
```

创建了一个文本查询对象。

然后：

```cpp
tq.readFile("china_daily.txt");
```

读取文件，并建立索引。

接着：

```cpp
tq.query("element");
```

查询某个单词。

---

# 四、读取文件时具体做什么？

核心逻辑是：

```cpp
while (getline(ifs, line))
{
    ++lineNumber;
    _lines.push_back(line);

    istringstream iss(line);
    string word;

    while (iss >> word)
    {
        ++_dict[word];
        _wordNumbers[word].insert(lineNumber);
    }
}
```

下面细讲。

---

## 1. 一行一行读取

```cpp
getline(ifs, line)
```

它会从文件输入流 `ifs` 中读取一整行。

为什么不用：

```cpp
ifs >> line
```

因为 `>>` 遇到空格就停止。

比如文件中一行是：

```txt
the element type.
```

如果使用：

```cpp
ifs >> line;
```

只能读到：

```txt
the
```

但使用：

```cpp
getline(ifs, line);
```

可以读到整行：

```txt
the element type.
```

---

## 2. 行号从 1 开始

```cpp
int lineNumber = 0;

while (getline(ifs, line))
{
    ++lineNumber;
}
```

第一行读取后：

```cpp
lineNumber = 1;
```

第二行读取后：

```cpp
lineNumber = 2;
```

这样输出时符合用户习惯：

```txt
(line 1)
(line 2)
```

---

## 3. 保存原始行文本

```cpp
_lines.push_back(line);
```

这一步非常关键。

因为查询时，题目要求：

> 输出某单词所在的行文本时，程序必须能根据给定的行号从输入文件中获取相应的行。

我们不应该查询时重新打开文件去找那一行。

而是在读取文件时，把每一行都保存下来。

查询时直接：

```cpp
_lines[lineNumber - 1]
```

就可以得到原始行文本。

---

## 4. 用 `istringstream` 分解单词

假设：

```cpp
line = "the element type.";
```

我们写：

```cpp
istringstream iss(line);
string word;

while (iss >> word)
{
    ...
}
```

`iss >> word` 会依次读出：

```txt
the
element
type.
```

每读出一个单词，就进入一次循环。

---

# 五、查询时具体做什么？

核心逻辑是：

```cpp
auto it = _dict.find(word);

if (it == _dict.end())
{
    cout << word << " occurs 0 times." << endl;
    return;
}

cout << word << " occurs " << it->second << " times." << endl;

const set<int> &lineNumbers = _wordNumbers.at(word);

for (int lineNumber : lineNumbers)
{
    cout << "(line " << lineNumber << ") "
         << _lines[lineNumber - 1] << endl;
}
```

---

## 1. 为什么用 `find` 查询？

```cpp
auto it = _dict.find(word);
```

`find` 会查找某个单词是否存在。

如果找到了，返回指向该元素的迭代器。

如果没找到，返回：

```cpp
_dict.end()
```

所以可以判断：

```cpp
if (it == _dict.end())
```

表示这个单词没有出现过。

---

## 2. 为什么查询时不建议直接用 `_dict[word]`？

你可能会想：

```cpp
cout << _dict[word] << endl;
```

这样不也能得到次数吗？

问题是：

```cpp
_dict[word]
```

如果 `word` 不存在，`map` 会自动插入一个新元素，值为 `0`。

例如：

```cpp
_dict["notexist"];
```

会导致 `_dict` 中多出一个：

```cpp
"notexist" -> 0
```

查询操作本来不应该修改数据，所以更好的写法是：

```cpp
auto it = _dict.find(word);
```

---

## 3. 输出总次数

```cpp
cout << word << " occurs " << it->second << " times." << endl;
```

对于 `map<string, int>` 来说，一个元素可以看成：

```cpp
pair<const string, int>
```

其中：

```cpp
it->first   // 单词
it->second  // 次数
```

比如：

```cpp
"element" -> 125
```

那么：

```cpp
it->first = "element";
it->second = 125;
```

---

## 4. 输出所有行号和原文

```cpp
const set<int> &lineNumbers = _wordNumbers.at(word);
```

这里得到的是这个单词出现过的所有行号。

比如：

```cpp
lineNumbers = {62, 64, 153, 250, 398};
```

然后：

```cpp
for (int lineNumber : lineNumbers)
{
    cout << "(line " << lineNumber << ") "
         << _lines[lineNumber - 1] << endl;
}
```

逐行输出。

---

# 六、带详细注释的完整代码

下面是一个适合提交的版本，注释比较完整。

```cpp
#include <iostream>   // 输入输出流：cin, cout, cerr
#include <fstream>    // 文件输入输出流：ifstream
#include <sstream>    // 字符串流：istringstream
#include <string>     // string 类型
#include <vector>     // vector 容器
#include <map>        // map 容器
#include <set>        // set 容器

using namespace std;

/*
 * TextQuery 类：
 *
 * 作用：
 *  1. 读取一个文本文件
 *  2. 保存文件中的所有原始行
 *  3. 统计每个单词出现的总次数
 *  4. 记录每个单词出现在哪些行
 *  5. 根据用户输入的单词进行查询并输出结果
 */
class TextQuery
{
public:
    /*
     * readFile:
     *
     * 功能：
     *  读取指定文件，并建立查询所需的数据结构。
     *
     * 参数：
     *  filename：要读取的文件名
     *
     * 例如：
     *  readFile("china_daily.txt");
     */
    void readFile(const string &filename);

    /*
     * query:
     *
     * 功能：
     *  查询某个单词出现的次数，并输出它出现过的所有行。
     *
     * 参数：
     *  word：要查询的单词
     *
     * 例如：
     *  query("element");
     */
    void query(const string &word) const;

private:
    /*
     * _lines:
     *
     * 保存文件的每一行原始内容。
     *
     * 例如文件内容：
     *  hello world
     *  hello c++
     *
     * 则：
     *  _lines[0] = "hello world"
     *  _lines[1] = "hello c++"
     *
     * 注意：
     *  vector 下标从 0 开始；
     *  文件行号通常从 1 开始。
     *
     * 所以：
     *  第 lineNumber 行对应 _lines[lineNumber - 1]
     */
    vector<string> _lines;

    /*
     * _wordNumbers:
     *
     * 保存每个单词出现过的行号集合。
     *
     * 类型解释：
     *  map<string, set<int>>
     *
     *  key   ：单词，例如 "element"
     *  value ：该单词出现过的行号集合，例如 {62, 64, 153}
     *
     * 为什么 value 使用 set<int>？
     *  1. set 会自动去重
     *     如果一个单词在同一行出现多次，该行号只保存一次。
     *
     *  2. set 会自动升序排列
     *     输出行号时自然就是升序。
     */
    map<string, set<int>> _wordNumbers;

    /*
     * _dict:
     *
     * 保存每个单词出现的总次数。
     *
     * 类型解释：
     *  map<string, int>
     *
     *  key   ：单词，例如 "element"
     *  value ：出现次数，例如 125
     */
    map<string, int> _dict;
};

/*
 * readFile 函数实现
 */
void TextQuery::readFile(const string &filename)
{
    /*
     * 创建文件输入流对象 ifs。
     *
     * ifstream 用于从文件中读取数据。
     */
    ifstream ifs(filename);

    /*
     * 判断文件是否成功打开。
     *
     * 如果文件不存在、文件名错误、没有权限等，
     * ifs 会处于失败状态。
     */
    if (!ifs)
    {
        cerr << "Error: cannot open file " << filename << endl;
        return;
    }

    string line;        // 用于保存当前读取到的一整行文本
    int lineNumber = 0; // 当前行号，从 0 开始，读取一行后再加 1

    /*
     * getline(ifs, line)：
     *
     * 从文件 ifs 中读取一整行内容，保存到 line 中。
     *
     * 只要读取成功，就继续循环。
     *
     * 与 ifs >> line 的区别：
     *  ifs >> line 遇到空格就停止；
     *  getline 可以读取完整的一行，包括空格。
     */
    while (getline(ifs, line))
    {
        /*
         * 每读取一行，行号加 1。
         *
         * 第一行：lineNumber = 1
         * 第二行：lineNumber = 2
         * 第三行：lineNumber = 3
         */
        ++lineNumber;

        /*
         * 保存这一行的原始内容。
         *
         * 这样之后查询时，可以根据行号直接输出原文。
         *
         * 注意：
         *  第 1 行保存在 _lines[0]
         *  第 2 行保存在 _lines[1]
         */
        _lines.push_back(line);

        /*
         * 创建字符串输入流 iss。
         *
         * 作用：
         *  把 line 当成一个输入流，
         *  然后可以像 cin 一样使用 >> 从中提取单词。
         *
         * 例如：
         *  line = "the element type"
         *
         *  iss >> word 会依次得到：
         *  "the"
         *  "element"
         *  "type"
         */
        istringstream iss(line);

        string word; // 保存当前从这一行中提取到的单词

        /*
         * 不断从当前行中读取单词。
         *
         * iss >> word：
         *  会跳过空白字符；
         *  每次读取一个由空白分隔的字符串。
         */
        while (iss >> word)
        {
            /*
             * 统计单词出现次数。
             *
             * _dict[word] 的含义：
             *  访问 word 对应的出现次数。
             *
             * 如果 word 第一次出现，
             * map 会自动创建这个 key，
             * 并把 int 默认初始化为 0。
             *
             * 然后 ++ 使其变为 1。
             */
            ++_dict[word];

            /*
             * 记录 word 出现在哪一行。
             *
             * _wordNumbers[word] 的类型是 set<int>。
             *
             * insert(lineNumber) 表示把当前行号插入到集合中。
             *
             * 如果同一行中 word 出现多次，
             * 会多次插入同一个 lineNumber，
             * 但 set 会自动去重。
             */
            _wordNumbers[word].insert(lineNumber);
        }
    }

    /*
     * 文件流对象 ifs 在函数结束时会自动关闭文件。
     * 所以这里不写 ifs.close() 也可以。
     *
     * 如果想显式关闭，也可以写：
     * ifs.close();
     */
}

/*
 * query 函数实现
 */
void TextQuery::query(const string &word) const
{
    /*
     * 在 _dict 中查找 word。
     *
     * find 不会修改 map。
     *
     * 如果找到了：
     *  返回指向该元素的迭代器。
     *
     * 如果没找到：
     *  返回 _dict.end()。
     */
    auto dictIt = _dict.find(word);

    /*
     * 如果 word 不存在，说明该单词在文件中没有出现过。
     */
    if (dictIt == _dict.end())
    {
        cout << word << " occurs 0 times." << endl;
        return;
    }

    /*
     * dictIt->second 表示该单词出现的总次数。
     *
     * 对于 map<string, int>：
     *  dictIt->first  是单词
     *  dictIt->second 是次数
     */
    cout << word << " occurs " << dictIt->second << " times." << endl;

    /*
     * 在 _wordNumbers 中查找该单词对应的行号集合。
     *
     * 因为前面已经确认 word 在 _dict 中存在，
     * 正常情况下它也一定存在于 _wordNumbers 中。
     */
    auto lineIt = _wordNumbers.find(word);

    /*
     * 为了程序更稳妥，这里仍然判断一下。
     */
    if (lineIt == _wordNumbers.end())
    {
        return;
    }

    /*
     * lineIt->second 是 set<int>，
     * 里面保存了 word 出现过的所有行号。
     *
     * set 会自动升序排列，
     * 所以这里遍历出来的行号天然就是升序。
     */
    for (int lineNumber : lineIt->second)
    {
        /*
         * lineNumber 是从 1 开始的行号。
         * _lines 的下标从 0 开始。
         *
         * 所以：
         *  第 lineNumber 行文本是 _lines[lineNumber - 1]
         */
        cout << "(line " << lineNumber << ") "
             << _lines[lineNumber - 1] << endl;
    }
}

/*
 * main 函数：
 *
 * 提供一个简单的交互式测试。
 *
 * 用户先输入文件名，
 * 程序读取文件并建立索引。
 *
 * 然后用户可以反复输入查询单词。
 * 输入 q 表示退出。
 */
int main()
{
    string filename;
    string word;

    /*
     * 让用户输入要处理的文件名。
     *
     * 例如：
     *  china_daily.txt
     */
    cout << "Please input filename: ";
    cin >> filename;

    /*
     * 创建 TextQuery 对象。
     */
    TextQuery tq;

    /*
     * 读取文件，并建立：
     *  1. 原始行数组 _lines
     *  2. 单词出现次数表 _dict
     *  3. 单词行号表 _wordNumbers
     */
    tq.readFile(filename);

    /*
     * 提示用户输入查询单词。
     */
    cout << "Please input query word: ";

    /*
     * 反复读取用户输入的单词。
     *
     * 只要 cin >> word 成功，就继续循环。
     */
    while (cin >> word)
    {
        /*
         * 输入 q 表示退出查询。
         *
         * 注意：
         *  如果文本中真的有单词 q，
         *  这里就不能查询它了。
         *
         *  如果想更严谨，可以改成输入 "quit" 或 ":q" 退出。
         */
        if (word == "q")
        {
            break;
        }

        /*
         * 查询用户输入的单词。
         */
        tq.query(word);

        cout << endl;
        cout << "Please input query word, or q to quit: ";
    }

    return 0;
}
```

---

# 七、用一个小文件完整走一遍

假设 `test.dat` 内容如下：

```txt
hello world
hello c++ hello
world map set
```

执行：

```cpp
tq.readFile("test.dat");
```

---

## 第 1 行

```txt
hello world
```

行号：

```cpp
lineNumber = 1
```

保存：

```cpp
_lines[0] = "hello world";
```

拆出单词：

```txt
hello
world
```

更新统计：

```cpp
_dict["hello"] = 1;
_dict["world"] = 1;
```

更新行号：

```cpp
_wordNumbers["hello"] = {1};
_wordNumbers["world"] = {1};
```

---

## 第 2 行

```txt
hello c++ hello
```

行号：

```cpp
lineNumber = 2
```

保存：

```cpp
_lines[1] = "hello c++ hello";
```

拆出单词：

```txt
hello
c++
hello
```

更新统计：

```cpp
_dict["hello"] = 3;
_dict["c++"] = 1;
```

注意 `hello` 在第 2 行出现了两次，所以总次数增加 2。

更新行号：

```cpp
_wordNumbers["hello"] = {1, 2};
_wordNumbers["c++"] = {2};
```

虽然第 2 行有两个 `hello`，但是 `{1, 2}` 中只有一个 `2`。

---

## 第 3 行

```txt
world map set
```

行号：

```cpp
lineNumber = 3
```

保存：

```cpp
_lines[2] = "world map set";
```

更新后：

```cpp
_dict["world"] = 2;
_dict["map"] = 1;
_dict["set"] = 1;
```

行号表：

```cpp
_wordNumbers["world"] = {1, 3};
_wordNumbers["map"] = {3};
_wordNumbers["set"] = {3};
```

---

## 查询 `hello`

```cpp
tq.query("hello");
```

查次数：

```cpp
_dict["hello"] = 3
```

查行号：

```cpp
_wordNumbers["hello"] = {1, 2}
```

输出：

```txt
hello occurs 3 times.
(line 1) hello world
(line 2) hello c++ hello
```

注意：

第 2 行虽然有两个 `hello`，但只输出一次。

---

# 八、一个更“工程化”的版本：处理标点和大小写

前面的版本有一个问题。

如果文本中有：

```txt
Element element element.
```

基础版本会认为这是三个不同的单词：

```txt
Element
element
element.
```

因为：

* `Element` 首字母大写
* `element.` 带句号

如果希望它们都算作 `element`，可以写一个清洗函数。

---

## 清洗函数

```cpp
#include <cctype>
```

```cpp
string cleanupWord(const string &word)
{
    string result;

    for (char ch : word)
    {
        if (isalpha(static_cast<unsigned char>(ch)))
        {
            result += static_cast<char>(
                tolower(static_cast<unsigned char>(ch))
            );
        }
    }

    return result;
}
```

它的作用是：

```txt
Element   -> element
element.  -> element
ELEMENT,  -> element
```

不过注意：

这个版本只保留英文字母。

如果文件里有：

```txt
c++
map<string,int>
```

会被处理成：

```txt
c
mapstringint
```

所以是否使用清洗函数，要看老师的要求。

如果题目主要是练习 `map`、`set`、`vector`，基础版本更直接。

---

# 九、带单词清洗的增强版代码

如果你希望程序查询更自然，可以使用下面这个增强版。

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cctype>

using namespace std;

class TextQuery
{
public:
    void readFile(const string &filename);
    void query(const string &word) const;

private:
    /*
     * 清洗单词：
     *  1. 去掉非字母字符
     *  2. 把大写字母转成小写
     *
     * 例如：
     *  "Element," -> "element"
     *  "TYPE."    -> "type"
     */
    string cleanupWord(const string &word) const;

private:
    vector<string> _lines;
    map<string, set<int>> _wordNumbers;
    map<string, int> _dict;
};

string TextQuery::cleanupWord(const string &word) const
{
    string result;

    for (char ch : word)
    {
        /*
         * isalpha 用于判断字符是否是字母。
         *
         * static_cast<unsigned char>(ch) 是更安全的写法，
         * 可以避免 char 为负值时导致未定义行为。
         */
        if (isalpha(static_cast<unsigned char>(ch)))
        {
            /*
             * tolower 把大写字母转成小写字母。
             */
            result += static_cast<char>(
                tolower(static_cast<unsigned char>(ch))
            );
        }
    }

    return result;
}

void TextQuery::readFile(const string &filename)
{
    ifstream ifs(filename);

    if (!ifs)
    {
        cerr << "Error: cannot open file " << filename << endl;
        return;
    }

    string line;
    int lineNumber = 0;

    while (getline(ifs, line))
    {
        ++lineNumber;

        /*
         * 保存原始行。
         *
         * 注意：
         * 这里保存的是没有清洗过的原始行，
         * 因为输出时应该显示原文。
         */
        _lines.push_back(line);

        istringstream iss(line);
        string word;

        while (iss >> word)
        {
            /*
             * 对单词进行清洗。
             *
             * 例如：
             *  "Element," -> "element"
             */
            word = cleanupWord(word);

            /*
             * 如果一个字符串中没有任何字母，
             * 清洗后可能变成空字符串。
             *
             * 例如：
             *  "123" 或 "!!!"
             *
             * 这种情况直接跳过。
             */
            if (word.empty())
            {
                continue;
            }

            ++_dict[word];
            _wordNumbers[word].insert(lineNumber);
        }
    }
}

void TextQuery::query(const string &word) const
{
    /*
     * 查询时也要清洗用户输入的单词。
     *
     * 例如用户输入：
     *  Element
     *
     * 实际查询：
     *  element
     */
    string cleanedWord = cleanupWord(word);

    if (cleanedWord.empty())
    {
        cout << word << " occurs 0 times." << endl;
        return;
    }

    auto dictIt = _dict.find(cleanedWord);

    if (dictIt == _dict.end())
    {
        cout << cleanedWord << " occurs 0 times." << endl;
        return;
    }

    cout << cleanedWord << " occurs " << dictIt->second << " times." << endl;

    auto lineIt = _wordNumbers.find(cleanedWord);

    if (lineIt == _wordNumbers.end())
    {
        return;
    }

    for (int lineNumber : lineIt->second)
    {
        cout << "(line " << lineNumber << ") "
             << _lines[lineNumber - 1] << endl;
    }
}

int main()
{
    string filename;
    string word;

    cout << "Please input filename: ";
    cin >> filename;

    TextQuery tq;
    tq.readFile(filename);

    cout << "Please input query word: ";

    while (cin >> word)
    {
        if (word == "q")
        {
            break;
        }

        tq.query(word);

        cout << endl;
        cout << "Please input query word, or q to quit: ";
    }

    return 0;
}
```

---

# 十、基础版和增强版该选哪个？

建议你根据课程要求选择。

如果老师给的文件内容主要是英文单词，并且题目没有要求忽略标点和大小写，那么提交 **基础版** 就可以。

如果老师希望查询更接近真实文本搜索，比如：

```txt
element
element.
Element
ELEMENT
```

都算成同一个单词，那么提交 **增强版** 更好。

不过增强版有一个副作用：

```txt
C++
```

会变成：

```txt
c
```

所以对于 C++ 技术文本，增强版并不一定总是合适。

---

# 十一、这个程序的复杂度

假设：

* 文件一共有 `N` 个单词
* 不同单词数量是 `M`
* 某个单词出现过的行数是 `K`

读取文件时：

```cpp
++_dict[word];
_wordNumbers[word].insert(lineNumber);
```

`map` 查找和插入一般是：

```txt
O(log M)
```

`set` 插入行号一般是：

```txt
O(log K)
```

所以整体效率对普通文本文件来说完全够用。

查询时：

```cpp
_dict.find(word)
```

是：

```txt
O(log M)
```

输出行号需要遍历 `K` 行，所以：

```txt
O(K)
```

---

# 十二、容易出错的地方

## 1. 忘记行号和 vector 下标差 1

错误写法：

```cpp
_lines[lineNumber]
```

正确写法：

```cpp
_lines[lineNumber - 1]
```

因为：

```txt
第 1 行 -> _lines[0]
第 2 行 -> _lines[1]
```

---

## 2. 用 `vector<int>` 保存行号导致重复输出

如果写成：

```cpp
map<string, vector<int>> _wordNumbers;
```

那么一行里多次出现同一个单词时，会保存多个相同的行号。

比如：

```txt
hello hello hello
```

可能得到：

```cpp
_wordNumbers["hello"] = {1, 1, 1};
```

输出就会重复三次。

所以题目推荐：

```cpp
map<string, set<int>>
```

---

## 3. 查询不存在的单词时直接用 `.at`

如果写：

```cpp
_wordNumbers.at(word)
```

但是 `word` 不存在，程序会抛异常。

所以更稳妥的写法是：

```cpp
auto it = _wordNumbers.find(word);

if (it != _wordNumbers.end())
{
    ...
}
```

---

## 4. 文件打开失败没有处理

如果没有判断：

```cpp
if (!ifs)
```

文件打开失败时，程序可能什么都不输出，用户不知道发生了什么。

建议保留：

```cpp
if (!ifs)
{
    cerr << "Error: cannot open file " << filename << endl;
    return;
}
```
