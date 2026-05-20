#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

using namespace std;

// 前向声明 QueryResult 类
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
    // value 是一个 shared_ptr,指向 set<int>
    // set<int> 中保存该单词出现过的所有行号
    // set 会自动去重，并且按升序保存行号
    map<string, shared_ptr<set<int>>> _wordToLineNumbers;
    
    // 保存每个单词总共出现的次数
    // key 是单词
    // value 是该单词出现的总次数
    map<string, int> _dict;
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
    ifstream ifs(filename);

    if(!ifs)
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
        // 当前行号+1
        ++lineNumber;
        
        // 将原始行文本保存到 vector 中
        _lines->push_back(line);
        
        // 使用字符串输入流拆分当前行中的单词
        istringstream iss(line);
        string word;

        // 依次读取当前行中的每个单词
        while(iss >> word)
        {
            // 统计该单词出现的总次数
            // 如果 word 第一次出现，map 会自动创建对应的 int，初始值为 0
            ++_dict[word];

            // 取得该单词对应的行号集合
            // 如果 word 第一次出现，map 会自动创建一个空的 shared_ptr
            auto &lineSet = _wordToLineNumbers[word];
            // 如果该单词还没有对应的 set<int>，则创建一个
            if(!lineSet)
            {
                lineSet = make_shared<set<int>>();
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

int main(int argc, char *argv[])
{
    
    return 0;
}
