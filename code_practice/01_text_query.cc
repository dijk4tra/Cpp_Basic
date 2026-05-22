#include <fstream>
#include <iostream>
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
    map<string, set<int>> _wordToLineNumbers;
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

        // 把这行文本拆分成一个一个单词
        istringstream iss(line);
        string word;

        while(iss >> word)
        {
            // 记录单词出现的次数
            ++_dict[word];
            // 记录单词所在行号
            _wordToLineNumbers[word].insert(lineNumber);
        }
    }
    ifs.close();
}

void TextQuery::query(const string &word) const
{
    auto dictIt = _dict.find(word);
    if(dictIt == _dict.end())
    {
        cout << word << " occurs 0 times." << endl;
        return;
    }

    cout << word << " occurs " << dictIt->second << " times." << endl;

    auto lineIt = _wordToLineNumbers.find(word);

    if(lineIt != _wordToLineNumbers.end())
    {
        for(int lineNumber : lineIt->second)
        {
            cout << "(line " << lineNumber << ") "
                 << _lines[lineNumber - 1] << endl;
        }
    }
}


int main(int argc, char *argv[])
{
    string filename;
    string queryWord;

    cout << "Please input filename: ";
    cin >> filename;

    TextQuery tq;
    tq.readFile(filename);

    cout << "Please input query word: ";

    while(cin >> queryWord)
    {
        if(queryWord == "q")
        {
            break;
        }

        tq.query(queryWord);

        cout << endl;
        cout << "Please input query word, or input q to quit: ";
    }

    return 0;
}

