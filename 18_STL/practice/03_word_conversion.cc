#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

// 读取规则文件，构建map
map<string, string> buildMap(ifstream &map_file)
{
    map<string, string> trans_map;
    string key;
    string value;

    // 先读第一个单词作为 key，然后用 getline 把整行的剩余部分读入 value
    while (map_file >> key && getline(map_file, value))
    {
        if (value.size() > 1){
            // getline() 会把 key 后面紧跟着的空格也读进去，需要去掉空格
            trans_map[key] = value.substr(1);
        }
        else
        {
            throw runtime_error("错误：规则文件中 " + key + " 没有对应的转换短语！");
        }
    }
    return trans_map;
}

// 检查单词是否需要转换
const string& transform(const string &s, const map<string, string> &m)
{
    auto map_it = m.find(s);
    if(map_it != m.end())
    {
        return map_it->second; // 找到了，返回转换后的短语
    }
    else
    {
        return s; // 没找到，返回原单词
    }
}

// 主控程序：读取待转换文件并打印结果
void wordTransform(ifstream &map_file, ifstream &input_file)
{
    auto trans_map = buildMap(map_file); // 建立规则字典
    string line;

    // 逐行读取待转换文本，保持原有的换行结构
    while (getline(input_file, line))
    {
        istringstream stream(line); // 将整行文本放入字符串流中，方便拆分单词
        string word;
        bool firstword = true; // 用来控制单词之间空格的打印

        while (stream >> word)
        {
            if(firstword){
                firstword = false;
            }
            else
            {
                cout << " "; // 在单词之间打印空格
            }
            // 打印转换后（或不需要转换）的单词
            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}

int main() 
{
    ifstream map_file("map.txt");
    ifstream input_file("file.txt");

    if (!map_file || !input_file)
    {
        cerr << "无法打开输入文件，请确保 map.txt 和 file.txt 放在正确的目录下！" << endl;
        return -1;
    }

    wordTransform(map_file, input_file);
    return 0;
}