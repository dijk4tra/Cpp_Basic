#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

/**
 * 文件指针
 *
 * 对于文件输入流 ifstream 来说，
 * 在读取文件内容时，内部会维护一个“文件指针”。
 *
 * 文件指针用来记录当前读取到文件的哪个位置。
 *
 * 常用函数：
 *
 * 1. tellg()
 *    获取当前文件输入指针的位置。
 *
 * 2. seekg()
 *    移动文件输入指针的位置。
 *
 * 3. get()
 *    从文件中读取一个字符。
 *
 * 说明：
 * g 表示 get，
 * 所以 tellg 和 seekg 都是针对输入流的文件读取位置。
 */

void test1()
{
    // 创建文件输入流对象ifs,并打开data.txt文件
    ifstream ifs {"data.txt"};
    // 将文件指针移动到末尾
    ifs.seekg(0, std::ios::end);
    // 获取文件大小
    // 文件指针移动到文件末尾后,
    // tellg()返回的字节数,
    // 就相当于文件的字节数
    int size = ifs.tellg();
    
    // 创建字符数组,用于保存从文件中读取到的内容
    char buf[size + 1];

    // 把文件指针移动到文件开头
    ifs.seekg(0);
    // 从文件中读取size个字节的数据,并保存至buf
    ifs.read(buf, size);
    // 手动添加结束符
    buf[size] = '\0';

    cout << buf << endl;

    // 关闭文件
    ifs.close();
    
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

