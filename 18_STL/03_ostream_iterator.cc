#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

/**
 * 输出流迭代器 ostream_iterator
 *
 * ostream_iterator 是输出迭代器，用于向输出流中写数据。
 * 常见输出流包括：
 * 1. cout       标准输出流
 * 2. ofstream   文件输出流
 *
 * 写数据方式：
 *    *it = 数据;
 *
 * 注意：
 * ostream_iterator 只能写，不能读。
 */

void test1()
{   
    // 创建 ostream 输出流迭代器对象
    // 第一个参数 cout 表示输出目标是标准输出流
    // 第二个参数 " " 表示每输出一个元素后追加一个空格
    ostream_iterator<int> it(cout, " ");

    // 通过输出流迭代器写数据
    // 对 ostream_iterator 解引用后赋值，相当于向 cout 输出数据
    *it = 1;

    // 对 ostream_iterator 来说，++it 只是为了符合迭代器操作习惯
    // 实际上不会像普通容器迭代器那样移动到下一个元素位置
    ++it;

    *it = 2;
}

void test2()
{
    // 创建 ostream 输出流迭代器对象
    // 该迭代器用于向 cout 输出 string 类型数据
    ostream_iterator<string> it(cout, " ");

    // 写字符串数据到标准输出流
    *it = "abc";
    ++it;
    *it = "hello";

    cout << endl;
}


void test3()
{
    // 创建文件输出流对象
    // 如果文件不存在，会创建 temp.txt
    // 如果文件已存在，默认会清空原内容后重新写入
    ofstream ofs("temp.txt");

    // 创建 ostream 输出流迭代器对象
    // 输出目标由 cout 改为文件输出流 ofs
    ostream_iterator<string> it(ofs, " ");

    // 通过输出流迭代器向文件中写入字符串
    *it = "abc";
    ++it;
    *it = "hello";

    // 关闭文件输出流
    // 程序结束时 ofs 也会自动关闭，这里手动关闭更直观
    ofs.close();
}

// 一般使用 std::copy 结合输出流迭代器打印容器中的数据
void test4()
{
    vector<int> box{1, 2, 3, 4, 5};

    // 获取容器首元素位置
    auto itFirst = box.begin();

    // 获取容器尾后位置
    auto itLast = box.end();

    // 创建输出流迭代器对象，输出目标是 cout
    // 每输出一个 int 元素后追加一个空格
    ostream_iterator<int> it(cout, " ");

    // 使用 std::copy 将 [++itFirst, itLast) 区间中的元素复制到输出流迭代器
    // 注意：++itFirst 会先让 itFirst 向后移动一位，所以第一个元素 1 不会被输出
    // 实际输出的是：2 3 4 5
    std::copy(++itFirst, itLast, it);

    cout << endl;
}


int main(int argc, char *argv[])
{
    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}