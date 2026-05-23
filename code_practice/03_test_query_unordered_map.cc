#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <memory>

using namespace std;

class QueryResult;

class TextQuery
{
public:
    TextQuery()
    : _lines(make_shared<vector<string>>())
    {}

    void readFile(const string &filename);
    QueryResult query(const string &word) const;

private:
    shared_ptr<vector<string>> _lines; // 保存文件中的所有原始文本行
    // 将map替换为unordered_map
    unordered_map<string, shared_ptr<set<int>>> _wordToLineNumbers; // 保存每个单词出现的行号
    unordered_map<string, int> _wordNumbers; // 保存每个单词的出现次数
};

class QueryResult
{
    friend void print(ostream &os, const QueryResult &qr);

public:
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
    string _word; // 被查询的单词
    int _count;   // 该单词出现的总次数
    shared_ptr<set<int>> _lineNumbers; // 该单词出现过的行号集合
    shared_ptr<vector<string>> _lines; // 整个文件的原始文本内容
};


void TextQuery::readFile(const string &filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cout << "Error: cannot open file " << filename << endl;
        return;
    }

    string line;
    int lineNumber = 0;

    while (getline(ifs, line))
    {
        lineNumber++;
        _lines->push_back(line);

        istringstream iss(line);
        string word;

        while (iss >> word)
        {
            ++_wordNumbers[word];
            
            auto &lineSet = _wordToLineNumbers[word];
            if (!lineSet)
            {
                lineSet = make_shared<set<int>>();
            }
            lineSet->insert(lineNumber);
        }
    }
    ifs.close();
}

QueryResult TextQuery::query(const string &word) const
{
    static shared_ptr<set<int>> nodata(new set<int>);

    // unordered_map 的 find 和 end 用法与 map 完全一致
    auto dictIt = _wordNumbers.find(word);
    if (dictIt == _wordNumbers.end())
    {
        return QueryResult(word, 0, nodata, _lines);
    }

    auto lineIt = _wordToLineNumbers.find(word);
    if (lineIt == _wordToLineNumbers.end())
    {
        return QueryResult(word, dictIt->second, nodata, _lines);
    }

    return QueryResult(word, dictIt->second, lineIt->second, _lines);
}

void print(ostream &os, const QueryResult &qr)
{
    os << qr._word << " occurs " << qr._count << " times" << endl;
    for (int lineNumber : *(qr._lineNumbers))
    {
        os << "    (line " << lineNumber << ") " << (*qr._lines)[lineNumber - 1] << endl;
    }
}

int main(int argc, char *argv[])
{
    string filename;
    if (argc >= 2)
    {
        filename = argv[1];
    }
    else
    {
        cout << "Please input filename: ";
        cin >> filename;
    }

    TextQuery tq;
    tq.readFile(filename);

    string queryWord;
    cout << "Please input query word, or input q to quit: ";

    while (cin >> queryWord)
    {
        if (queryWord == "q") break;

        QueryResult qr = tq.query(queryWord);
        print(cout, qr);

        cout << endl;
        cout << "Please input query word, or input q to quit: ";
    }
    return 0;
}