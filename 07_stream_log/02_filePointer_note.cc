#include <fstream>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
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
    // 创建文件输入流对象 ifs，并打开 data.txt 文件
    ifstream ifs {"data.txt"};

    /**
     * tellg()
     *
     * 作用：
     * 获取当前文件输入指针的位置。
     *
     * 文件刚打开时，
     * 如果没有指定其他打开模式，
     * 文件指针默认位于文件开头。
     *
     * 文件开头的位置一般是 0。
     */
    int pos = ifs.tellg();
    cout << "pos: " << pos << endl;

    /**
     * get()
     *
     * 作用：
     * 从输入流中读取一个字符。
     *
     * ifs.get()
     * 表示从文件中读取当前文件指针指向的字符。
     *
     * 读取完成后，
     * 文件指针会自动向后移动一个位置。
     */
    char ch1 = ifs.get();
    cout << ch1 << endl;

    // 再次获取文件指针的位置，观察读取一个字符后指针的变化
    pos = ifs.tellg();
    cout << "pos: " << pos << endl;

    // 再读取一个字符，文件指针继续向后移动
    char ch2 = ifs.get();
    cout << ch2 << endl;

    // 再次获取文件指针的位置
    pos = ifs.tellg();
    cout << "pos : " << pos << endl;

    cout << "---------" << endl;

    /**
     * seekg()
     *
     * 作用：
     * 移动文件输入指针的位置。
     *
     * seekg 可以使用两种方式：
     *
     * 1. 使用绝对位置
     *    ifs.seekg(0);
     *
     *    表示把文件指针移动到文件开头。
     *
     * 2. 使用相对位置
     *    ifs.seekg(偏移量, 参照位置);
     *
     *    常见参照位置：
     *    std::ios::beg  文件开头
     *    std::ios::cur  当前所在位置
     *    std::ios::end  文件末尾
     */

    // 移动文件指针到指定位置
    // 可以使用绝对位置 / 相对位置
    /* ifs.seekg(0); // 使用的是绝对位置 */

    /**
     * 使用相对位置移动文件指针
     *
     * ifs.seekg(1, std::ios::beg);
     *
     * 表示：
     * 以文件开头为参照位置，
     * 向后偏移 1 个字节。
     *
     * 所以文件指针会移动到下标为 1 的位置。
     */
    ifs.seekg(1, std::ios::beg);

    // 获取移动之后的文件指针位置
    pos = ifs.tellg();
    cout << "pos : " << pos << endl;

    // 读取当前位置的字符
    char ch3 = ifs.get();
    cout << ch3 << endl;

    // 读取之后，文件指针会继续向后移动
    pos = ifs.tellg();
    cout << "pos : " << pos << endl;

    // 关闭文件
    ifs.close();
}


void test2()
{
    // 创建文件输入流对象 ifs，并打开 data.txt 文件
    ifstream ifs {"data.txt"};

    /**
     * 将文件指针移动到文件末尾
     *
     * ifs.seekg(0, std::ios::end);
     *
     * 表示：
     * 以文件末尾为参照位置，
     * 偏移量为 0。
     *
     * 也就是直接把文件指针移动到文件末尾。
     */
    ifs.seekg(0, std::ios::end);

    /**
     * 获取文件大小
     *
     * 文件指针移动到文件末尾后，
     * tellg() 返回的位置，
     * 就相当于文件的字节数。
     *
     * 所以这里可以通过 tellg()
     * 获取文件大小。
     */
    int size = ifs.tellg();
    cout << "pos : " << size << endl;

    /**
     * 创建字符数组
     *
     * 作用：
     * 用来保存从文件中读取到的内容。
     *
     * size 是文件的大小，
     * size + 1 是为了多留一个位置，
     * 用来存放字符串结束符 '\0'。
     */
    char buf[size + 1];

    /**
     * 注意：
     * 前面为了获取文件大小，
     * 已经把文件指针移动到了文件末尾。
     *
     * 如果直接读取，
     * 就会从文件末尾开始读，
     * 读不到有效内容。
     *
     * 所以读取文件内容之前，
     * 需要重新把文件指针移动到文件开头。
     */
    ifs.seekg(0);

    /**
     * read()
     *
     * 作用：
     * 从输入流中读取指定字节数的数据。
     *
     * ifs.read(buf, size);
     *
     * 表示：
     * 从文件中读取 size 个字节的数据，
     * 并保存到 buf 数组中。
     *
     * 注意：
     * read 不会自动在末尾添加 '\0'。
     */
    ifs.read(buf, size);

    /**
     * 手动添加字符串结束符
     *
     * 如果想把字符数组当作 C 风格字符串输出，
     * 需要保证末尾有 '\0'。
     */
    buf[size] = '\0';

    cout << buf << endl;

    // 关闭文件
    ifs.close();
}


void test3()
{
    /**
     * 文件打开模式
     *
     * std::ios::in
     * 表示以读取方式打开文件。
     *
     * std::ios::ate
     * 表示打开文件后，
     * 文件指针自动定位到文件末尾。
     *
     * ate 是 at end 的缩写。
     *
     * 注意：
     * ifstream 默认就是以 std::ios::in 的方式打开文件，
     * 所以这里写 std::ios::ate 时，
     * 仍然是用于读取文件，
     * 只是打开后文件指针直接位于文件末尾。
     */

    // 可以修改打开模式，让文件打开后指针直接位于末尾
    ifstream ifs {"data.txt", std::ios::ate};

    /**
     * 因为使用了 std::ios::ate，
     * 所以文件刚打开时，
     * 文件指针已经在文件末尾。
     *
     * 此时 tellg() 返回的结果，
     * 就可以表示文件大小。
     */
    int size = ifs.tellg();
    cout << "pos : " << size << endl;

    // 创建一个字符数组，用来存储读取到的文件数据
    char buf[size + 1];

    /**
     * 注意：
     * 当前文件指针在文件末尾，
     * 如果要读取整个文件内容，
     * 仍然需要先把文件指针移动回文件开头。
     */
    ifs.seekg(0);

    // 从文件中读取 size 个字节的数据到 buf 中
    ifs.read(buf, size);

    // read 不会自动添加 '\0'，所以这里手动添加
    buf[size] = '\0';

    cout << buf << endl;

    // 关闭文件
    ifs.close();
}

int main(int argc, char *argv[])
{
    // 测试 tellg、seekg、get 的使用
    /* test1(); */

    // 测试通过 seekg + tellg 获取文件大小，再读取整个文件
    /* test2(); */

    // 测试使用 std::ios::ate 打开文件后直接获取文件大小
    test3();

    return 0;
}