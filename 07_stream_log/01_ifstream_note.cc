#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

/**
 * 文件输入流 ifstream
 *
 * ifstream 是 input file stream 的缩写，
 * 表示文件输入流。
 *
 * 作用：
 * 从文件中读取数据。
 *
 * 使用步骤：
 * 1. 包含头文件 <fstream>
 * 2. 创建 ifstream 对象，并关联文件
 * 3. 从文件中读取数据
 * 4. 关闭文件
 *
 * 例如：
 * ifstream ifs{"data.txt"};
 *
 * 这行代码表示：
 * 创建一个文件输入流对象 ifs，
 * 并打开当前目录下的 data.txt 文件。
 *
 * 注意：
 * 如果文件不存在，或者文件打开失败，
 * 后续读取操作就不会成功。
 */

// 循环读取单词
void test1()
{
    // 创建文件输入流对象 ifs，并打开 data.txt 文件
    ifstream ifs {"data.txt"};

    // 用来保存每次从文件中读取到的单词
    string word;

    /**
     * 使用 >> 从文件中读取数据
     *
     * ifs >> word
     * 表示从文件输入流 ifs 中读取一个单词，
     * 并保存到 word 中。
     *
     * >> 读取 string 时：
     * 1. 会自动跳过空格、制表符、换行符等空白字符
     * 2. 从第一个非空白字符开始读取
     * 3. 遇到下一个空白字符时停止
     *
     * 所以这种方式适合按“单词”读取。
     *
     * while (ifs >> word)
     * 表示：
     * 只要读取成功，就进入循环。
     * 当文件读完，或者读取失败时，循环结束。
     */
    while (ifs >> word) {
        cout << word << endl;
    }

    // 关闭文件
    ifs.close();
}

// 按行读取 string 中的 getline
void test2()
{
    // 创建文件输入流对象 ifs，并打开 data.txt 文件
    ifstream ifs {"data.txt"};

    // 用来保存每次读取到的一整行内容
    string line;

    /**
     * getline 函数
     *
     * 语法：
     * std::getline(输入流对象, string 对象)
     *
     * 作用：
     * 从输入流中读取一整行内容，
     * 并保存到 string 对象中。
     *
     * 注意：
     * getline 会读取空格，
     * 直到遇到换行符 '\n' 才停止。
     * 换行符本身会被丢弃，不会存入 line 中。
     */
    std::getline(ifs, line);
    cout << line << endl;

    // 再读取下一行内容
    std::getline(ifs, line);
    cout << line << endl;

    // 再读取下一行内容
    std::getline(ifs, line);
    cout << line << endl;

    // 关闭文件
    ifs.close();
}

// 按行读取 string 中的 getline
void test3()
{
    // 创建文件输入流对象 ifs，并打开 data.txt 文件
    ifstream ifs {"data.txt"};

    // 用来保存每次读取到的一整行内容
    string line;

    /**
     * 循环按行读取
     *
     * std::getline(ifs, line)
     * 每次从文件中读取一整行内容。
     *
     * while(std::getline(ifs, line))
     * 表示：
     * 只要按行读取成功，就进入循环。
     *
     * 当文件内容全部读取完毕时，
     * getline 读取失败，循环结束。
     *
     * 和 ifs >> word 的区别：
     * 1. ifs >> word 是按单词读取
     *    遇到空格、制表符、换行符都会停止。
     *
     * 2. getline 是按行读取
     *    一整行中的空格也会被读取进来。
     */
    while(std::getline(ifs, line)){
        cout << line << endl;
    }

    // 关闭文件
    ifs.close();
}

int main(int argc, char *argv[])
{
    // 测试按单词读取文件内容
    /* test1(); */

    // 测试手动调用 getline 读取多行内容
    /* test2(); */

    // 测试循环使用 getline 按行读取文件内容
    test3();

    return 0;
}