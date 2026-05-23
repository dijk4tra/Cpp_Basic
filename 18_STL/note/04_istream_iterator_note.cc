#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

/**
 * istream_iterator：
 *
 * istream_iterator 是输入流迭代器。
 *
 * 它属于输入迭代器 input iterator，
 * 主要用于从输入流中读取数据。
 *
 * 常见输入流：
 * 1. cin
 *    标准输入流，从键盘读取数据。
 *
 * 2. ifstream
 *    文件输入流，从文件读取数据。
 *
 *
 * istream_iterator 的作用：
 * 可以把输入流包装成一个迭代器对象。
 *
 * 这样 STL 算法就可以像操作普通迭代器一样，
 * 从输入流中读取数据。
 *
 *
 * 头文件：
 * #include <iterator>
 *
 *
 * 基本格式：
 *
 * istream_iterator<T> it(输入流对象);
 *
 * T：
 * 表示要读取的数据类型。
 *
 * 输入流对象：
 * 可以是 cin，也可以是 ifstream 对象。
 *
 *
 * 读数据：
 *
 * 变量 = *it;
 *
 * 含义：
 * 从输入流中读取一个 T 类型的数据，
 * 并赋值给变量。
 *
 *
 * 注意：
 * istream_iterator 只能读，不能写。
 */


void test1()
{   
    /**
     * 创建 istream 输入流迭代器对象。
     *
     * istream_iterator<int> it(cin);
     *
     * 含义：
     * 1. 从 cin 中读取数据
     * 2. 读取的数据类型是 int
     *
     * 程序运行到这里后，
     * 并不一定马上完成所有输入，
     * 真正读取数据通常发生在解引用 *it 的时候。
     */
    istream_iterator<int> it(cin);

    /**
     * 定义两个 int 变量，
     * 用来保存从键盘输入的数据。
     */
    int num1;
    int num2;

    /**
     * *it：
     * 解引用输入流迭代器。
     *
     * 对 istream_iterator 来说，
     * 解引用表示获取当前读取到的数据。
     *
     * 如果从键盘输入：
     * 10 20
     *
     * 那么第一次 *it 得到的是 10。
     */
    num1 = *it;

    /**
     * ++it：
     * 让输入流迭代器读取下一个数据。
     *
     * 如果前面已经读取了 10，
     * 执行 ++it 后，
     * 迭代器会继续从 cin 中读取下一个 int。
     */
    ++it;

    /**
     * 再次解引用，
     * 获取第二个输入的数据。
     *
     * 如果键盘输入的是：
     * 10 20
     *
     * 那么 num2 得到的是 20。
     */
    num2 = *it;

    /**
     * 输出读取到的两个整数。
     */
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
}


void test2()
{
    /**
     * 创建 istream_iterator<string> 对象。
     *
     * 表示从 cin 中读取 string 类型数据。
     *
     * 注意：
     * 默认情况下，使用 >> 读取 string 时，
     * 会以空白字符作为分隔。
     *
     * 例如输入：
     * abc hello
     *
     * 会被读取成两个字符串：
     * "abc"
     * "hello"
     */
    istream_iterator<string> it(cin);

    // 用来保存输入的两个字符串
    string str1;
    string str2;

    /**
     * 读取第一个字符串。
     */
    str1 = *it;

    /**
     * 移动到下一个输入数据。
     */
    ++it;

    /**
     * 读取第二个字符串。
     */
    str2 = *it;

    /**
     * 输出读取到的两个字符串。
     */
    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;
}


// 通过键盘输入数据，填充到容器中
void test3()
{
    /**
     * 创建一个空的 vector 容器。
     *
     * 由于此时没有元素，
     * 所以 box.size() == 0。
     */
    vector<int> box;

    /**
     * 创建输入流迭代器对象作为 First。
     *
     * istream_iterator<int> itFirst(cin);
     *
     * 表示从键盘读取 int 类型数据。
     *
     * 这个迭代器会作为输入区间的起始位置。
     */
    istream_iterator<int> itFirst(cin);

    /**
     * 创建输入流迭代器对象作为 Last。
     *
     * istream_iterator<int> itLast;
     *
     * 这里使用的是无参构造函数。
     *
     * 无参构造出来的 istream_iterator
     * 表示输入流的结束位置。
     *
     *
     * 对 cin 来说：
     * 当输入结束时，
     * itFirst 就会等于 itLast。
     *
     * 常见结束输入的方式：
     *
     * Linux / macOS：
     * Ctrl + D
     *
     * Windows：
     * Ctrl + Z，然后回车
     */
    istream_iterator<int> itLast;

    /**
     * 使用 std::copy 从输入流读取数据。
     *
     * std::copy(itFirst, itLast, 目标迭代器);
     *
     * 含义：
     * 从 itFirst 开始不断读取 cin 中的 int 数据，
     * 直到遇到输入流结束为止。
     *
     *
     * 下面这种写法是错误的：
     *
     * std::copy(itFirst, itLast, box.begin());
     *
     * 原因：
     * box 是一个空 vector，
     * box.begin() 并没有指向一个可以写入数据的有效元素位置。
     *
     * copy 的第三个参数要求目标位置已经存在可写空间。
     *
     * 空 vector 中没有元素，
     * 所以不能直接往 box.begin() 写数据。
     */
    // std::copy(itFirst, itLast, box.begin()); // error : box.begin()此时为nullptr
    
    /**
     * 如果想把输入的数据不断插入到 vector 尾部，
     * 需要使用插入迭代器适配器。
     *
     * back_insert_iterator：
     *
     * 它是一种迭代器适配器。
     *
     * 作用：
     * 把赋值操作转换成容器的 push_back 操作。
     *
     * 也就是说：
     *
     * *it = value;
     *
     * 实际效果类似于：
     *
     * box.push_back(value);
     *
     *
     * 方式一：
     * 手动创建 back_insert_iterator 对象。
     */
    // back_insert_iterator<vector<int>> it{box};
    // std::copy(itFirst, itLast, it);

    /**
     * 方式二：
     * 使用 back_inserter 函数。
     *
     * back_inserter(box)
     *
     * 会自动创建一个与 box 绑定的
     * back_insert_iterator 对象。
     *
     * 这样写更加简洁，
     * 也是实际开发中更常用的写法。
     *
     *
     * 执行逻辑：
     *
     * 1. 从 cin 中读取 int 数据
     * 2. 每读取到一个数据
     * 3. 就通过 back_inserter 调用 box.push_back()
     * 4. 把数据插入到 vector 尾部
     *
     *
     * 例如输入：
     * 1 2 3 4 5
     *
     * 然后按下输入结束符，
     * box 中就会保存：
     * 1 2 3 4 5
     */
    std::copy(itFirst, itLast, back_inserter(box));

    /**
     * 输出 vector 中元素个数。
     *
     * size：
     * 返回容器中当前元素的数量。
     */
    cout << box.size() << endl;

    /**
     * 打印容器中的数据。
     *
     * 这里再次使用 std::copy，
     * 把 box 中的数据复制到 ostream_iterator 中。
     *
     * ostream_iterator<int>{cout, " "}
     *
     * 表示：
     * 把 int 数据输出到 cout，
     * 每个数据后面追加一个空格。
     */
    std::copy(box.begin(), box.end(), ostream_iterator<int>{cout, " "});
}


int main(int argc, char *argv[])
{
    /**
     * test1：
     * 使用 istream_iterator<int>
     * 从键盘读取两个整数。
     *
     * test2：
     * 使用 istream_iterator<string>
     * 从键盘读取两个字符串。
     *
     * test3：
     * 使用 istream_iterator + std::copy + back_inserter，
     * 从键盘读取多个整数并保存到 vector 中。
     */
    // test1();
    // test2();
    test3();

    return 0;
}