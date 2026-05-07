#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

/**
 * 文件输出流 ofstream
 *
 * ofstream 是 output file stream 的缩写，
 * 表示文件输出流。
 *
 * 作用：
 * 向文件中写入数据。
 *
 * 使用步骤：
 * 1. 包含头文件 <fstream>
 * 2. 创建 ofstream 对象，并关联文件
 * 3. 向文件中写入数据
 * 4. 关闭文件
 *
 * 注意：
 * ofstream 默认以 std::ios::out 的方式打开文件。
 *
 * 如果目标文件不存在，
 * 会自动创建该文件。
 *
 * 如果目标文件已经存在，
 * 默认情况下会清空文件原来的内容，
 * 然后再写入新的内容。
 */

// 输出流对象的创建
void test1()
{
    /**
     * 无参构造
     *
     * 先创建一个文件输出流对象 ofs，
     * 此时还没有关联具体的文件。
     *
     * 后面再调用 open 函数打开文件。
     */
    ofstream ofs;

    /**
     * open()
     *
     * 作用：
     * 打开指定文件，并让输出流对象和文件关联起来。
     *
     * ofs.open("data.txt");
     *
     * 表示：
     * 打开当前目录下的 data.txt 文件。
     *
     * 因为 ofstream 默认打开模式是 std::ios::out，
     * 所以这里是以写入方式打开文件。
     */
    ofs.open("data.txt");

    /**
     * 有参构造
     *
     * 创建 ofstream 对象时，
     * 直接传入文件名。
     *
     * 这样对象创建完成后，
     * 就已经和文件关联起来了。
     */
    ofstream ofs2 {"data.txt"};

    // 文件名也可以使用 string 类型的变量保存
    string fileName = "data.txt";

    // 使用 string 类型的文件名创建输出流对象
    ofstream ofs3 {fileName};
}

/**
 * 写数据到文件的步骤
 *
 * 1. 创建输出流对象
 * 2. 利用 write 函数或者输出运算符 << 写数据
 * 3. close 关闭文件
 */

void test2()
{
    /**
     * 有参构造创建输出流对象
     *
     * ofstream ofs {"data2.txt"};
     *
     * 表示：
     * 创建一个文件输出流对象 ofs，
     * 并打开 data2.txt 文件。
     *
     * 如果目标文件不存在，
     * 则会自动创建该文件。
     *
     * 如果目标文件已经存在，
     * 默认打开模式为 std::ios::out，
     * 文件原来的内容会被清空。
     */
    ofstream ofs {"data2.txt"};

    /**
     * 使用输出运算符 << 写入数据
     *
     * 和 cout 的使用方式类似。
     *
     * 区别：
     * cout 是把内容输出到终端；
     * ofs 是把内容输出到文件。
     */
    ofs << "abc";

    // 可以连续写入不同类型的数据
    ofs << 123 << " ";

    // 写入浮点数
    ofs << 3.14;

    // 关闭文件
    ofs.close();
}

// 利用 write 函数写数据
void test3()
{
    // 创建文件输出流对象 ofs，并打开 data.txt 文件
    ofstream ofs {"data.txt"};

    // 要写入文件的字符串内容
    string msg = "hello world";

    /**
     * write()
     *
     * 作用：
     * 向输出流中写入指定字节数的数据。
     *
     * 语法：
     * ofs.write(字符指针, 写入的字节数);
     *
     * msg.c_str()
     * 可以把 string 类型的数据转换成 C 风格字符串。
     *
     * msg.size()
     * 表示字符串中字符的个数。
     *
     * ofs.write(msg.c_str(), msg.size());
     *
     * 表示：
     * 将 msg 中的内容写入到文件中，
     * 写入的字节数为 msg.size()。
     *
     * 注意：
     * write 更适合按照字节写入数据。
     */
    ofs.write(msg.c_str(), msg.size());

    // 关闭文件
    ofs.close();
}

// 追加写入
void test4()
{
    /**
     * 追加模式 std::ios::app
     *
     * app 是 append 的缩写，
     * 表示追加写入。
     *
     * 默认情况下，
     * ofstream 使用 std::ios::out 打开文件，
     * 如果文件已经存在，会清空原来的内容。
     *
     * 如果使用 std::ios::app，
     * 新内容会写到文件末尾，
     * 不会清空文件原来的内容。
     */
    ofstream ofs {"data.txt", std::ios::app};

    // 要追加写入到文件中的字符串内容
    string msg = "abcdef";

    // 使用 write 函数将 msg 的内容写入到文件末尾
    ofs.write(msg.c_str(), msg.size());

    // 关闭文件
    ofs.close();
}

int main(int argc, char *argv[])
{
    // 测试输出流对象的创建方式
    /* test1(); */

    // 测试使用 << 向文件写入数据
    /* test2(); */

    // 测试使用 write 函数向文件写入数据
    /* test3(); */

    // 测试追加写入文件内容
    test4();

    return 0;
}