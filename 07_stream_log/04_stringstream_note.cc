#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;
using std::ostringstream;

/**
 * 字符串流
 *
 * 字符串流也是一种流对象，
 * 只不过它操作的数据不是文件，
 * 而是字符串。
 *
 * 需要包含头文件：
 * #include <sstream>
 *
 * 常用的字符串流：
 *
 * 1. istringstream
 *    字符串输入流。
 *
 *    作用：
 *    从 string 中读取数据，
 *    常用于把 string 转换成其它类型的数据。
 *
 *    例如：
 *    string ---> int
 *    string ---> double
 *
 * 2. ostringstream
 *    字符串输出流。
 *
 *    作用：
 *    向字符串流中写入数据，
 *    常用于把其它类型的数据转换成 string。
 *
 *    例如：
 *    int ---> string
 *    double ---> string
 *
 * 总结：
 * istringstream: string ---> 其它类型的数据
 * ostringstream: 其它类型的数据 ---> string
 */

void test1()
{
    // 准备一个字符串，里面保存了两个整数形式的数据
    string str = "123 456";

    /**
     * 基于 string 创建字符串输入流对象
     *
     * istringstream iss {str};
     *
     * 表示：
     * 创建一个字符串输入流对象 iss，
     * 并让 iss 从 str 这个字符串中读取数据。
     *
     * 这样就可以像使用 cin 一样，
     * 从字符串中依次提取数据。
     */
    istringstream iss {str};

    // 定义两个 int 类型变量，用来保存转换后的整数
    int num1;
    int num2;

    /**
     * 使用输入运算符 >> 进行数据转换
     *
     * iss >> num1 >> num2;
     *
     * 表示：
     * 从字符串输入流 iss 中依次读取数据，
     * 并转换成 int 类型后保存到 num1 和 num2 中。
     *
     * 其中：
     * "123" ---> int 类型的 123
     * "456" ---> int 类型的 456
     *
     * 注意：
     * >> 读取数据时，会自动跳过空格、换行等空白字符。
     */
    iss >> num1 >> num2;

    cout << "num1:" << num1 << endl;
    cout << "num2:" << num2 << endl;
}


void test2()
{
    // 准备一个字符串，里面保存了一个整数和一个浮点数
    string str = "123 3.14";

    /**
     * 基于 string 创建字符串输入流对象
     *
     * 后续可以通过 >> 从字符串中提取数据，
     * 并转换成对应的数据类型。
     */
    istringstream iss {str};

    // 保存转换后的整数
    int num1;

    // 保存转换后的浮点数
    double num2;

    /**
     * 数据转换
     *
     * iss >> num1 >> num2;
     *
     * 表示：
     * 从 iss 中读取 "123" 并转换成 int 类型，
     * 再读取 "3.14" 并转换成 double 类型。
     *
     * 也就是说：
     * "123"  ---> int
     * "3.14" ---> double
     */
    iss >> num1 >> num2;

    cout << "num1:" << num1 << endl;
    cout << "num2:" << num2 << endl; 
}

// 通过 istringstream 解析数据
void test3()
{
    // 创建文件输入流对象 ifs，并打开 db.conf 文件
    ifstream ifs {"db.conf"};

    // 用来保存每次从文件中读取到的一整行内容
    string line;

    /**
     * 循环按行读取文件内容
     *
     * std::getline(ifs, line)
     *
     * 表示：
     * 每次从文件 ifs 中读取一整行内容，
     * 并保存到 line 中。
     *
     * while 中使用 getline，
     * 表示只要读取成功，就进入循环。
     */
    while (std::getline(ifs, line)) {
        /**
         * 利用 istringstream 解析一行数据
         *
         * 每一行 line 本质上是一个 string。
         *
         * istringstream iss {line};
         *
         * 表示：
         * 创建字符串输入流对象 iss，
         * 并让 iss 从 line 这一行字符串中读取数据。
         *
         * 这样就可以使用 >> 把一行中的不同部分拆分出来。
         */
        istringstream iss {line};

        // 用来保存属性名
        string key;

        // 用来保存属性值
        string value;

        /**
         * 读取属性名和属性值
         *
         * 假设 db.conf 文件中的内容类似：
         * ip 192.168.1.1
         * port 3306
         *
         * iss >> key;
         * 表示读取每一行的第一个单词，作为属性名。
         *
         * iss >> value;
         * 表示读取每一行的第二个单词，作为属性值。
         */
        iss >> key;
        iss >> value;

        cout << "key:" << key << " = " << "value:" << value << endl;
    }
}

void test4()
{
    /**
     * 创建字符串输出流对象
     *
     * ostringstream oss;
     *
     * 表示：
     * 创建一个字符串输出流对象 oss。
     *
     * 后续可以像使用 cout 一样，
     * 使用 << 把数据写入 oss 中。
     *
     * 最后再通过 str() 函数，
     * 得到最终拼接好的 string 字符串。
     */
    ostringstream oss;

    // 准备一个 int 类型数据
    int num1 = 123;

    // 准备一个 double 类型数据
    double num2 = 3.14;

    /**
     * 使用输出运算符 << 进行数据转换
     *
     * oss << num1 << " " << num2;
     *
     * 表示：
     * 把 num1、空格、num2 依次写入字符串输出流 oss 中。
     *
     * 在写入过程中，
     * int 类型的 123 会被转换成字符串 "123"，
     * double 类型的 3.14 会被转换成字符串 "3.14"。
     *
     * 也就是说：
     * 123  ---> "123"
     * 3.14 ---> "3.14"
     */
    oss << num1 << " " << num2;

    /**
     * str()
     *
     * 作用：
     * 获取字符串输出流中保存的字符串内容。
     *
     * string s = oss.str();
     *
     * 表示：
     * 把 oss 中已经写入的数据取出来，
     * 并保存到 string 对象 s 中。
     */
    string s = oss.str();

    cout << "s:" << s << endl;
}


int main(int argc, char *argv[])
{
    // 测试使用 istringstream 将字符串中的两个整数转换成 int
    /* test1(); */

    // 测试使用 istringstream 将字符串中的数据转换成 int 和 double
    /* test2(); */

    // 测试使用 istringstream 按行解析配置文件中的 key 和 value
    /* test3(); */

    // 测试使用 ostringstream 将其它类型的数据转换成 string
    test4();

    return 0;
}