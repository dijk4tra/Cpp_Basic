#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

/**
 * ostream_iterator：
 *
 * ostream_iterator 是输出流迭代器。
 *
 * 它属于输出迭代器 output iterator，
 * 主要用于向输出流中写数据。
 *
 * 常见输出流：
 * 1. cout
 *    标准输出流，输出到屏幕。
 *
 * 2. ofstream
 *    文件输出流，输出到文件。
 *
 *
 * ostream_iterator 的作用：
 * 可以把输出流包装成一个迭代器对象。
 *
 * 这样 STL 算法就可以像操作普通迭代器一样，
 * 把数据写入输出流。
 *
 *
 * 头文件：
 * #include <iterator>
 *
 *
 * 基本格式：
 * ostream_iterator<T> it(输出流对象, 分隔符);
 *
 * T：
 * 表示要输出的数据类型。
 *
 * 输出流对象：
 * 可以是 cout，也可以是 ofstream 对象。
 *
 * 分隔符：
 * 每输出一个元素之后，自动追加的内容。
 *
 * 例如：
 * ostream_iterator<int> it(cout, " ");
 *
 * 表示创建一个输出流迭代器，
 * 用来向 cout 输出 int 类型数据，
 * 每输出一个 int 后面自动加一个空格。
 *
 *
 * 注意：
 * ostream_iterator 只能写，不能读。
 */


void test1()
{   
    /**
     * 创建 ostream 输出流迭代器对象。
     *
     * ostream_iterator<int> it(cout, " ");
     *
     * 含义：
     * 1. 这个迭代器输出 int 类型数据
     * 2. 数据输出到 cout
     * 3. 每输出一个数据后，自动追加一个空格
     */
    ostream_iterator<int> it(cout, " ");

    /**
     * *it = 1;
     *
     * 对 ostream_iterator 来说，
     * 这个写法不是把 1 存到某个容器中，
     * 而是把 1 写入到绑定的输出流 cout 中。
     *
     * 所以执行后会在屏幕上输出：
     * 1
     *
     * 因为创建迭代器时设置了分隔符 " "，
     * 所以输出 1 后面还会自动输出一个空格。
     */
    *it = 1;

    /**
     * ++it;
     *
     * 对普通容器迭代器来说，
     * ++it 表示移动到下一个元素。
     *
     * 但是 ostream_iterator 不指向容器中的真实位置，
     * 所以 ++it 基本上只是为了满足迭代器语法要求。
     *
     * 写不写 ++it，
     * 在这里通常不会影响输出结果。
     */
    ++it;

    /**
     * 继续向 cout 输出数据 2。
     *
     * 最终输出效果：
     * 1 2
     */
    *it = 2;
}


void test2()
{
    /**
     * ostream_iterator 也可以输出 string 类型数据。
     *
     * 这里创建的迭代器：
     * 1. 输出 string 类型
     * 2. 输出目标是 cout
     * 3. 每输出一个字符串后面追加一个空格
     */
    ostream_iterator<string> it(cout, " ");

    /**
     * 向 cout 写入字符串 "abc"。
     */
    *it = "abc";

    /**
     * 对 ostream_iterator 来说，
     * ++it 通常没有实际移动意义，
     * 主要是为了符合输出迭代器的使用形式。
     */
    ++it;

    /**
     * 继续写入字符串 "hello"。
     *
     * 输出效果：
     * abc hello
     */
    *it = "hello";

    /**
     * 手动输出换行。
     *
     * 注意：
     * ostream_iterator 设置的分隔符是 " "，
     * 它只会在每个元素后面自动输出空格，
     * 不会自动换行。
     */
    cout << endl;
}


void test3()
{
    /**
     * ofstream：
     *
     * 文件输出流。
     *
     * ofstream ofs("temp.txt");
     *
     * 表示打开或创建一个名为 temp.txt 的文件，
     * 用于写入数据。
     *
     * 如果文件不存在，会尝试创建该文件。
     * 如果文件已经存在，默认会清空原文件内容后重新写入。
     */
    ofstream ofs("temp.txt");

    /**
     * 创建 ostream_iterator<string> 对象。
     *
     * 这里绑定的输出流不是 cout，
     * 而是文件输出流 ofs。
     *
     * 所以通过这个迭代器写入的数据，
     * 会被输出到 temp.txt 文件中。
     */
    ostream_iterator<string> it(ofs, " ");

    /**
     * 向文件 temp.txt 中写入字符串。
     *
     * 文件内容大致为：
     * abc hello
     */
    *it = "abc";
    ++it;
    *it = "hello";

    /**
     * close：
     * 关闭文件输出流。
     *
     * 程序结束时 ofstream 析构函数也会自动关闭文件，
     * 但是手动 close 可以更清楚地表达：
     * 文件写入已经完成。
     */
    ofs.close();
}


// 一般使用 std::copy 结合输出流迭代器打印容器中的数据
void test4()
{
    /**
     * 创建 vector 容器，
     * 存放 1、2、3、4、5。
     */
    vector<int> box{1, 2, 3, 4, 5};

    /**
     * 获取容器的起始迭代器。
     *
     * begin()：
     * 返回指向第一个元素的迭代器。
     */
    auto itFirst = box.begin();

    /**
     * 获取容器的尾后迭代器。
     *
     * end()：
     * 返回指向最后一个元素后面位置的迭代器。
     *
     * 注意：
     * end() 不指向有效元素，
     * 不能对 end() 解引用。
     */
    auto itLast = box.end();

    /**
     * 创建一个输出流迭代器对象。
     *
     * 该迭代器用于把 int 类型数据输出到 cout，
     * 每输出一个数据后自动追加一个空格。
     */
    ostream_iterator<int> it(cout, " ");

    /**
     * std::copy：
     *
     * copy 是 STL 算法，
     * 头文件是：
     * #include <algorithm>
     *
     * 基本格式：
     *
     * std::copy(起始迭代器, 结束迭代器, 目标位置);
     *
     * 它会把 [起始迭代器, 结束迭代器) 这个区间中的数据，
     * 依次复制到目标位置。
     *
     *
     * 注意区间是左闭右开：
     *
     * [itFirst, itLast)
     *
     * 包含 itFirst 指向的元素，
     * 不包含 itLast 指向的位置。
     *
     *
     * 在这里：
     *
     * std::copy(++itFirst, itLast, it);
     *
     * 第三个参数 it 是 ostream_iterator，
     * 所以 copy 不是把数据复制到另一个容器，
     * 而是把数据依次输出到 cout。
     *
     *
     * ++itFirst：
     *
     * 这里使用的是前置自增。
     *
     * 原来 itFirst 指向元素 1，
     * 执行 ++itFirst 后，
     * itFirst 指向元素 2。
     *
     * 所以实际输出的区间是：
     * [2, 3, 4, 5]
     *
     * 输出结果：
     * 2 3 4 5
     */
    std::copy(++itFirst, itLast, it);

    /**
     * 输出换行。
     *
     * ostream_iterator 的分隔符只负责元素之间的输出格式，
     * 不会自动在最后换行。
     */
    cout << endl;
}


int main(int argc, char *argv[])
{
    /**
     * test1：
     * 使用 ostream_iterator<int> 向 cout 输出整数。
     *
     * test2：
     * 使用 ostream_iterator<string> 向 cout 输出字符串。
     *
     * test3：
     * 使用 ostream_iterator<string> 向文件输出内容。
     *
     * test4：
     * 使用 std::copy 配合 ostream_iterator
     * 输出 vector 中的部分元素。
     */
    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}