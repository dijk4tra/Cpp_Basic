/*
文本查询
该程序将读取用户指定的任意文本文件【当前目录下的china_daily.txt】，
然后允许用户从该文件中查找单词。查询的结果是该单词出现的次数，并列
出每次出现所在的行。如果某单词在同一行中多次出现，程序将只显示该行
一次。行号按升序显示。

要求：
a. 它必须允许用户指明要处理的文件名字。

b. 程序将存储该文件的内容，以便输出每个单词所在的原始行。
vector<string> lines;//O(1)

c. 它必须将每一行分解为各个单词，并记录每个单词所在的所有行。
在输出行号时，应保证以升序输出，并且不重复。

map<string, set<int> > wordNumbers;
map<string, int> dict;

d. 对特定单词的查询将返回出现该单词的所有行的行号。

e. 输出某单词所在的行文本时，程序必须能根据给定的行号从输入
文件中获取相应的行。

示例：
使用提供的文件内容，然后查找单词 "element"。输出的前几行为：
---------------------------------------------
element occurs 125 times.
(line 62) element with a given key.
(line 64) second element with the same key.
(line 153) element |==| operator.
(line 250) the element type.
(line 398) corresponding element.
---------------------------------------------

程序接口[可选]:
class TextQuery
{
public:
//......
void readFile(const string & filename);
void query(const string & word);//

private:
//......
vector<string> _lines;//O(1)
map<string, set<int> > _wordNumbers;//the the
map<string, int> _dict;//
};


//程序测试用例
int main(int argc, char *argv[])
{
string queryWord("hello");

TextQuery tq;
tq.readFile("test.dat");
tq.query(queryWord);
return 0;
}
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class TextQuery
{
public:
    void readFile(const string &filename);
    void query(const string &word) const;

private:
    vector<string> _lines;
    map<string, set<int>> _wordNumbers;
    map<string, int> _dict;
};

void TextQuery::readFile(const string &filename)
{
    ifstream ifs(filename);

    if(!ifs)
    {
        cout << "Error: cannot open file " << filename << endl;
        return;
    }

    string line;
    int lineNumber = 0;

    while(getline(ifs, line))
    {
        ++lineNumber;

        // 保存原始行文本
        _lines.push_back(line);

        // 把这行文本拆成一个一个单词
        istringstream iss(line);
        string word;

        while(iss >> word)
        {
            // 记录单词出现次数
            ++_dict[word];
            //记录单词所在行号
            _wordNumbers[word].insert(lineNumber);
        }
    }
    ifs.close();
}

void TextQuery::query(const string& word) const
{
    auto dictIt = _dict.find(word);
    if(dictIt == _dict.end())
    {
        cout << word << " occurs 0 times." << endl;
        return;
    }

    cout << word << " occurs " << dictIt->second << " times." << endl;

    auto lineIt = _wordNumbers.find(word);

    if (lineIt != _wordNumbers.end())
    {
        for(int lineNumber : lineIt->second)
        {
            cout << "(line " << lineNumber << ") "
                 << _lines[lineNumber - 1] << endl;
        }
    }
}

int main()
{
    string filename;
    string queryWord;

    cout << "Please input filename: ";
    cin >> filename;

    TextQuery tq;
    tq.readFile(filename);

    cout << "Please input query word: ";

    while (cin >> queryWord)
    {
        if (queryWord == "q")
        {
            break;
        }

        tq.query(queryWord);

        cout << endl;
        cout << "Please input query word, or input q to quit: ";
    }

    return 0;
}