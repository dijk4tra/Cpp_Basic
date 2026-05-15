#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;

/**
 * 读取文件数据
 *
 * 文件流：
 * C++ 中读写文件也可以通过“流”来完成。
 *
 * ifstream:
 * input file stream
 * 文件输入流，用来从文件中读取数据。
 *
 *
 * 读取文件的一般步骤：
 *
 * 1. 创建文件输入流对象
 *    ifstream ifs;
 *
 * 2. 打开文件，让文件流对象和文件关联
 *    ifs.open("data.txt");
 *
 *    或者也可以在创建对象时直接打开文件：
 *    ifstream ifs{"data.txt"};
 *
 * 3. 读取文件数据
 *    可以使用：
 *    1. 输入运算符 >>
 *    2. get()
 *    3. getline()
 *    4. read()
 *
 * 4. 关闭文件
 *    ifs.close();
 *
 *
 * 注意：
 * 如果 ifstream 对象是局部对象，
 * 当它离开作用域时，
 * 析构函数会自动关闭文件。
 *
 * 但是学习阶段可以显式调用 close()，
 * 方便理解资源释放的过程。
 *
 *
 * 当前 data.txt 中的内容看起来是：
 * abcd
 *
 * 但是实际上文件最后还有一个换行符，
 * 实际内容是：
 * a b c d '\n'
 *
 * 其中 '\n' 的 ASCII 值是 10。
 *
 * 所以读取字符对应的整数值时，
 * 会看到：
 * 97
 * 98
 * 99
 * 100
 * 10
 *
 * 分别对应：
 * 'a'  -> 97
 * 'b'  -> 98
 * 'c'  -> 99
 * 'd'  -> 100
 * '\n' -> 10
 *
 *
 * 注意：
 * 其中的10表示换行符 '\n'。
 * 通常是因为创建或保存 data.txt 时，
 * 编辑器在文件末尾加了一个换行。
 *
 * 在 Linux / macOS 中，
 * 换行符通常是 '\n'，
 * ASCII 值为 10。
 *
 * 在 Windows 文本文件中，
 * 换行通常是 "\r\n"，
 * 也就是：
 * '\r' -> 13
 * '\n' -> 10
 *
 *
 * get() 的返回值：
 *
 * ifs.get() 读取一个字符，
 * 但是它的返回类型不是 char，
 * 而是 int 类型。
 *
 * 原因：
 * 除了要能表示普通字符，
 * 还要能表示 EOF。
 *
 * EOF 表示 end of file，
 * 也就是文件读取结束。
 *
 * EOF 的值通常是 -1。
 *
 * 所以如果读取到文件末尾后继续读取，
 * ifs.get() 会返回 -1。
 */

// 文件流对象的创建
void test1()
{
    /**
     * 创建文件输入流对象 ifs。
     *
     * 这里使用无参构造函数创建，
     * 此时 ifs 还没有和具体文件关联。
     */
    ifstream ifs;

    /**
     * open()
     *
     * 作用：
     * 打开指定文件，
     * 并让文件流对象和该文件关联。
     *
     * 打开成功后，
     * 就可以通过 ifs 从 data.txt 中读取数据。
     */
    ifs.open("data.txt");

    /**
     * 使用有参构造函数创建文件输入流对象。
     *
     * ifstream ifs2 {"data.txt"};
     *
     * 这行代码完成了两件事：
     * 1. 创建 ifstream 对象 ifs2。
     * 2. 打开 data.txt，并和 ifs2 关联。
     */
    ifstream ifs2 {"data.txt"};
    
    /**
     * 文件名也可以使用 string 对象保存。
     *
     * 然后把 string 对象作为参数传给 ifstream。
     */
    std::string fileName = "data.txt";
    ifstream ifs3{ fileName };

    /**
     * 注意：
     * 实际开发中，打开文件后通常要判断是否打开成功。
     *
     * 例如：
     *
     * if(!ifs)
     * {
     *     cout << "open file failed" << endl;
     *     return;
     * }
     */
}

// 读取单个字符
void test2()
{
    /**
     * 创建文件输入流对象 ifs，
     * 并打开 data.txt。
     */
    ifstream ifs {"data.txt"};

    /**
     * get()
     *
     * 作用：
     * 从文件中读取一个字符。
     *
     * 每调用一次 get()，
     * 文件读取位置就会向后移动一个字符。
     *
     * 如果文件内容是：
     * abcd
     *
     * 并且文件末尾没有换行，
     * 那么前 4 次读取分别得到：
     * 'a' 'b' 'c' 'd'
     *
     * 如果文件末尾有换行，
     * 第 5 次会读取到：
     * '\n'
     */
    char ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;

    ch = ifs.get();
    cout << ch << endl;

    /**
     * 这里继续读取第 5 个字符。
     *
     * 如果 data.txt 末尾有换行，
     * ch 读取到的是 '\n'。
     *
     * cout << ch << endl;
     *
     * 会先输出换行符本身，
     * 然后 endl 又输出一个换行，
     * 所以视觉上可能只看到一个空行。
     *
     * 如果文件末尾没有换行，
     * 此时已经读到文件末尾，
     * get() 会返回 EOF。
     *
     * 但是这里用 char 接收 EOF，
     * 不方便观察 EOF 的值，
     * 所以 test3 使用 int 接收 get() 的返回值。
     */
    ch = ifs.get();
    cout << ch << endl;
}

void test3()
{
    ifstream ifs {"data.txt"};

    /**
     * 这里使用 int 接收 ifs.get() 的返回值。
     *
     * 原因：
     * get() 需要能够返回两类信息：
     *
     * 1. 正常读取到的字符
     *    例如 'a'、'b'、'c'
     *
     * 2. 文件结束标记 EOF
     *    通常是 -1
     *
     * 如果用 char 接收，
     * EOF 可能无法准确表示。
     *
     * 所以更推荐使用 int 接收 get() 的返回值，
     * 再判断是否等于 EOF。
     */

    // 读取第 1 个字符
    // 如果内容是 'a'，输出它的 ASCII 值 97
    int ch = ifs.get();
    cout << ch << endl;

    // 读取第 2 个字符
    // 'b' 的 ASCII 值是 98
    ch = ifs.get();
    cout << ch << endl;

    // 读取第 3 个字符
    // 'c' 的 ASCII 值是 99
    ch = ifs.get();
    cout << ch << endl;

    // 读取第 4 个字符
    // 'd' 的 ASCII 值是 100
    ch = ifs.get();
    cout << ch << endl;

    /**
     * 读取第 5 个字符。
     *
     * 如果 data.txt 文件末尾有一个换行，
     * 那么这里读取到的是 '\n'。
     *
     * '\n' 的 ASCII 值是 10。
     *
     * 所以会输出：
     * 10
     *
     *
     * 这个 10 不是 Linux 自动添加到程序里的。
     *
     * 它来自文件本身。
     *
     * 很多编辑器在保存文本文件时，
     * 会在文件最后保留一个换行符。
     *
     * 在 Linux 中，文本文件每一行通常以 '\n' 结尾，
     * '\n' 的 ASCII 值就是 10。
     *
     * 所以你看到的 10，
     * 本质上是 data.txt 文件末尾的换行符。
     */
    ch = ifs.get();
    cout << ch << endl;

    /**
     * 继续读取第 6 个字符。
     *
     * 如果前面已经读完了：
     * 'a' 'b' 'c' 'd' '\n'
     *
     * 那么此时已经到达文件末尾。
     *
     * 再调用 get()，
     * 会返回 EOF。
     *
     * EOF 通常是 -1。
     *
     * 所以这里可能输出：
     * -1
     */
    ch = ifs.get();
    cout << ch << endl;
}

int main(int argc, char *argv[])
{
    /**
     * main 函数是程序入口。
     *
     * 当前只执行 test3()。
     *
     * test3() 用 int 接收 get() 的返回值，
     * 可以观察每个字符对应的 ASCII 值，
     * 以及文件结束时返回的 EOF。
     */

    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}