#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

using namespace std;

// 前向声明 QueryResult 类
// 因为 TextQuery::query 的返回值类型是 QueryResult，
// 但此时 QueryResult 类还没有正式定义
class QueryResult;

class TextQuery
{
public:
    // 构造函数
    // 使用 make_shared 创建一个动态分配的 vector<string>
    // 用来保存文件中的所有原始文本行
    TextQuery() 
    : _lines(make_shared<vector<string>>()) 
    {}

    // 读取指定文件
    // filename 是用户指定的文件名
    void readFile(const string &filename);

    // 查询某个单词
    // 返回一个 QueryResult 对象，保存查询结果
    QueryResult query(const string &word) const;

private:
    // 保存输入文件中的每一行原始文本
    // 使用 shared_ptr 是为了让 TextQuery 和 QueryResult 共享这些文本行
    shared_ptr<vector<string>> _lines;

    // 保存每个单词出现在哪些行
    // key 是单词
    // value 是一个 shared_ptr，指向 set<int>
    // set<int> 中保存该单词出现过的所有行号
    // set 会自动去重，并且按升序保存行号
    map<string, shared_ptr<set<int>>> _wordToLineNumbers;

    // 保存每个单词总共出现的次数
    // key 是单词
    // value 是该单词出现的总次数
    map<string, int> _wordNumbers;
};

class QueryResult
{
    // 声明 print 函数为友元函数
    // 这样 print 可以访问 QueryResult 的私有成员
    friend void print(ostream &os, const QueryResult &qr);

public:
    // 构造函数
    // word：被查询的单词
    // count：该单词出现的总次数
    // lineNumbers：该单词出现过的行号集合
    // lines：整个文件的原始文本内容
    QueryResult(
        string word,
        int count,
        shared_ptr<set<int>> lineNumbers,
        shared_ptr<vector<string>> lines
    )
    : _word(word),
      _count(count),
      _lineNumbers(lineNumbers),
      _lines(lines)
    {}

private:
    // 被查询的单词
    string _word;

    // 单词出现的总次数
    int _count;

    // 单词出现过的所有行号
    // 使用 shared_ptr 是为了和 TextQuery 中的数据共享
    shared_ptr<set<int>> _lineNumbers;

    // 指向保存原始文本行的 vector
    // 通过行号可以找到对应的原始行文本
    shared_ptr<vector<string>> _lines;
};

void TextQuery::readFile(const string &filename)
{
    // 创建输入文件流对象，并尝试打开文件
    ifstream ifs(filename);

    // 判断文件是否打开成功
    if (!ifs)
    {
        cout << "Error: cannot open file " << filename << endl;
        return;
    }

    string line;

    // 行号从 0 开始计数，读取一行后先自增
    // 因此实际保存的行号从 1 开始
    int lineNumber = 0;

    // 按行读取文件内容
    while (getline(ifs, line))
    {
        // 当前行号加 1
        ++lineNumber;

        // 将原始行文本保存到 vector 中
        // 这样查询结果可以输出完整的原始行内容
        _lines->push_back(line);

        // 使用字符串输入流拆分当前行中的单词
        istringstream iss(line);
        string word;

        // 依次读取当前行中的每个单词
        while (iss >> word)
        {
            // 统计该单词出现的总次数
            // 如果 word 第一次出现，map 会自动创建对应的 int，初始值为 0
            ++_wordNumbers[word];

            // 取得该单词对应的行号集合
            // 如果 word 第一次出现，map 会自动创建一个空的 shared_ptr
            auto &lineSet = _wordToLineNumbers[word];

            // 如果该单词还没有对应的 set<int>，则创建一个
            if (!lineSet)
            {
                lineSet.reset(new set<int>);
                // 也可以写成：
                // lineSet = make_shared<set<int>>();
            }

            // 将当前行号插入 set
            // 如果同一单词在同一行中出现多次，set 会自动去重
            // set 还会自动按升序保存行号
            lineSet->insert(lineNumber);
        }
    }

    // 关闭文件
    ifs.close();
}

QueryResult TextQuery::query(const string &word) const
{
    // 当查询的单词不存在时，使用这个空的 set<int>
    // static 保证 nodata 在函数调用结束后仍然存在
    // shared_ptr 用来和 QueryResult 的接口保持一致
    static shared_ptr<set<int>> nodata(new set<int>);

    // 先在 _wordNumbers 中查找该单词是否出现过
    auto dictIt = _wordNumbers.find(word);

    // 如果没有找到，说明该单词出现次数为 0
    if (dictIt == _wordNumbers.end())
    {
        return QueryResult(word, 0, nodata, _lines);
    }

    // 在 _wordToLineNumbers 中查找该单词对应的行号集合
    auto lineIt = _wordToLineNumbers.find(word);

    // 正常情况下，只要 _wordNumbers 中有该单词，
    // _wordToLineNumbers 中也应该有它。
    // 这里做一次判断，是为了让程序更加安全
    if (lineIt == _wordToLineNumbers.end())
    {
        return QueryResult(word, dictIt->second, nodata, _lines);
    }

    // 返回查询结果：
    // word：查询的单词
    // dictIt->second：该单词出现的总次数
    // lineIt->second：该单词出现过的行号集合
    // _lines：文件的原始文本内容
    return QueryResult(word, dictIt->second, lineIt->second, _lines);
}

void print(ostream &os, const QueryResult &qr)
{
    // 输出单词出现的总次数
    os << qr._word << " occurs " << qr._count << " times." << endl;

    // 遍历该单词出现过的所有行号
    // set<int> 中的行号已经自动升序排列，并且没有重复
    for (int lineNumber : *(qr._lineNumbers)) // 解引用获取到它背后真正指向的 set 容器实体
    {
        // lineNumber 从 1 开始
        // vector 下标从 0 开始
        // 所以访问对应原始行时，需要 lineNumber - 1
        os << "    (line " << lineNumber << ") "
           << (*qr._lines)[lineNumber - 1] << endl;
    }
}

int main(int argc, char *argv[])
{
    string filename;

    // 如果用户在命令行中传入了文件名，
    // 例如：./text_query china_daily.txt
    // 那么 argc >= 2，argv[1] 就是文件名
    if (argc >= 2)
    {
        filename = argv[1];
    }
    else
    {
        // 如果没有通过命令行传入文件名，
        // 就让用户手动输入文件名
        cout << "Please input filename: ";
        cin >> filename;
    }

    // 创建 TextQuery 对象
    TextQuery tq;

    // 读取并处理文件内容
    tq.readFile(filename);

    string queryWord;

    cout << "Please input query word, or input q to quit: ";

    // 循环读取用户输入的查询单词
    while (cin >> queryWord)
    {
        // 输入 q 时退出查询
        if (queryWord == "q")
        {
            break;
        }

        // 查询指定单词，得到查询结果对象
        QueryResult qr = tq.query(queryWord);

        // 输出查询结果
        print(cout, qr);

        cout << endl;
        cout << "Please input query word, or input q to quit: ";
    }

    return 0;
}