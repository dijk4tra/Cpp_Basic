#include <iostream>   // 标准输入输出流,使用 cin、cout
#include <fstream>    // 文件输入输出流,使用 ifstream、ofstream
#include <map>        // 使用 map 容器
#include <ostream>
#include <string>     // 使用 string 字符串
#include <cctype>     // 使用 isalpha、tolower 等字符处理函数

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::map;

// Dictionary 类用于完成词频统计
class Dictionary
{
public:
    // 根据传入的文件名打开文件,读取文件内容,统计每个单词出现的次数    
    void read(const string &filename);

    // 将 _dict 中保存的单词和词频写入文件
    void store(const string &filename);

private:
    // 把一个单词插入到_dict中,如果单词已经存在,则对应的词频+1
    void insertWord(const string &word);

private:
    // 把一个单词插入到_dict中,如果单词已经存在,则对应的词频+1
    map<string,int> _dict; // 用于保存单词和词频的容器
};

// insertWord 函数的实现
void Dictionary::insertWord(const string &word)
{
    // 如果word是空字符串,说明当前没有有效单词,直接返回
    if(word.empty())
    {
        return;
    }
    
    // map的下标访问:
    // 如果word已存在,直接将对应词频+1
    // 如果word不存在,则会自动创建一个键值对,初始值为0,然后再+1
    ++_dict[word];
}

// read 函数的实现
void Dictionary::read(const string &filename)
{
    ifstream ifs(filename); // 打开输入文件
    if(!ifs){
        cout << "open file failed: " << filename << endl;
        return;
    }

    char ch; // 用来保存每次从文件中读取到的一个字符
    string word; // 用来临时保存正在读取的一个单词

    // 从文件中逐个字符读取,直到文件末尾
    while(ifs.get(ch))
    {
        // 如果ch是一个字母,就将其转换为小写,并添加到word中
        // 先把ch转成unsigned char,保证传给isalpha/tolower的值合法
        if(isalpha(static_cast<unsigned char>(ch))) 
        {
            word += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
            // 然后tolower返回的是int,最后再转回char,方便追加到 string word 中
        }
        else
        {
            // 遇到非字母字符,说明第一个单词已经结束了
            insertWord(word); // 将这个单词插入到_dict中

            // 清空word,准备读取下一个单词
            word.clear();
        }
    }

    // 文件结束后,还需要处理最后一个单词
    insertWord(word);
    
    ifs.close();
}

// store 函数的实现
void Dictionary::store(const string &filename)
{
    ofstream ofs(filename); // 打开输出文件
    
    if(!ofs)
    {
        cout << "open file failed: " << filename << endl;
        return;
    }

    // 遍历map中的所有元素
    // elem.first 是单词
    // elem.second 是词频
    for(const auto &elem : _dict)
    {
        ofs << elem.first << " " << elem.second << endl;
    }

    ofs.close();
}

int main(int argc, char *argv[])
{
    string filepath;

    cout << "请输入文档的绝对路径: ";
    cin >> filepath;

    Dictionary dict;
    dict.read(filepath);
    dict.store("dict.txt");

    cout << "词典文件 dict.txt 已生成 !" << endl;

    return 0;
}


/**
 * vector版本: 每插入一个单词,都要从头到尾查找一次,查找效率为为O(n)
 * map版本：根据平衡二叉搜索树结构快速查找,查找/插入效率为:O(log n)
 */