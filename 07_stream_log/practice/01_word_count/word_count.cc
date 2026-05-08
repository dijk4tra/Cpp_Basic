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

// Record 表示词典中的一条记录
struct Record
{
    string _word;
    int _frequency;
};

// Dictionary 类用于完成词频统计
class Dictionary
{
public:
    // 根据传入的文件名打开文件，读取文件内容，统计每个单词出现的次数
    void read(const string &filename);

    // 将 _dict 中保存的单词和词频写入文件
    void store(const string &filename);

private:
    // 把一个单词插入到 _dict中，如果单词已经存在，则将对应的词频加1
    void insertWord(const string &word);
private:
    vector<Record> _dict; // 用于保存单词和词频的容器
};

// insertWord 函数的实现
void Dictionary::insertWord(const string &word)
{
    // 如果 word 是空字符串，说明当前没有有效单词，直接返回
    // 例如连续遇到多个标点符号时，就可能出现空字符串
    if (word.empty())
    {
        return;
    }

    // 遍历 _dict，查找是否已经存在 word
    for (int i = 0; i <_dict.size(); ++i)
    {
        // 该单词是否已经被统计过
        if (_dict[i]._word == word)
        {
            // 已经存在，词频加1
            _dict[i]._frequency += 1;
            // 找到之后就可以结束函数，避免继续遍历
            return;
        }
    }

    // 没有找到，说明是一个新的单词
    // 创建一个新的 Record 对象，并添加到 _dict 中
    Record record;           
    record._word = word;      // 保存新单词
    record._frequency = 1;        // 第一次出现，词频为1
    _dict.push_back(record); // 将新记录加入到vector的末尾
}

// read 函数的实现
void Dictionary::read(const string &filename)
{
    ifstream ifs(filename); // 打开输入文件
    if (!ifs)
    {
        cout << "文件打开失败: " << filename << endl;
        return; 
    }

    char ch;           // 用来保存每次从文件中读取到的一个字符
    string word;       // 用来临时保存正在读取的一个单词

    // 从文件中逐个字符读取，直到文件末尾
    while (ifs.get(ch))
    {
        // 如果 ch 是一个字母，就将其转换为小写，并添加到 word 中
        if (isalpha(ch))
        {
            word += tolower(ch);
        }
        else
        {
            // 遇到非字母字符，说明一个单词已经结束了
            // 将 word 插入到 _dict 中进行统计
            insertWord(word);
            // 清空 word，为下一个单词的读取做准备
            word.clear();
        }
    }
    // 循环结束后，还需要再插入一次 word
    // 如果文件最后一个字符是字母，
    // 那么最后一个单词后面没有非字母字符，
    // 它就不会在 while 循环中被插入
    insertWord(word);

    // 关闭输入文件
    ifs.close();
}

// store 函数的实现
void Dictionary::store(const string &filename)
{
    // 创建输出文件流对象 ofs
    ofstream ofs(filename);

    // 判断输出文件是否成功打开
    if (!ofs)
    {
        cout << "文件打开失败: " << filename << endl;
        return;
    }

    // 遍历 _dict 中的所有记录
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

int main(int argc, char * argv[])
{
    string filepath;

    cout << "请输入文章的绝对路径: ";
    cin >> filepath;

    Dictionary dict;
    dict.read(filepath);
    dict.store("dict.txt");
    cout << "词典文件 dict.txt 已生成 !" << endl;

    return 0;
}