#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

/**
 * 输入流迭代器 istream_iterator
 *
 * istream_iterator 是输入迭代器，用于从输入流中读取数据。
 * 常见输入流包括：
 * 1. cin       标准输入流
 * 2. ifstream  文件输入流
 *
 * 读数据方式：
 *    变量 = *it;
 *
 * 移动到下一个输入数据：
 *    ++it;
 */

void test1()
{   
    // 创建 istream 输入流迭代器对象
    // 该迭代器从标准输入流 cin 中读取 int 类型数据
    istream_iterator<int> it(cin);

    // 读数据
    int num1;
    int num2;

    // 第一次解引用，读取第一个 int 数据
    num1 = *it;

    // 迭代器向后移动，准备读取下一个 int 数据
    ++it;

    // 第二次解引用，读取第二个 int 数据
    num2 = *it;

    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
}

void test2()
{
    // 创建 istream 输入流迭代器对象
    // 该迭代器从标准输入流 cin 中读取 string 类型数据
    istream_iterator<string> it(cin);

    // 读数据
    string str1;
    string str2;

    // 读取第一个字符串
    // string 默认以空白字符作为分隔符
    str1 = *it;

    // 移动到下一个输入数据
    ++it;

    // 读取第二个字符串
    str2 = *it;

    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;
}


// 通过键盘输入数据，填充到容器中
void test3()
{
    vector<int> box;

    // 创建输入流迭代器对象作为 First
    // 从 cin 中读取 int 类型数据
    istream_iterator<int> itFirst(cin);

    // 创建输入流迭代器对象作为 Last
    // 通过 istream_iterator 的无参构造函数创建的对象表示输入流的结束位置
    istream_iterator<int> itLast;

    // 使用 std::copy 实现从输入流读取数据，并写入容器
    //
    // itFirst 不断从 cin 中读取 int 数据
    // itLast 表示输入结束位置
    //
    // 读取会一直进行，直到：
    // 1. 遇到 EOF
    //    Linux / macOS 通常使用 Ctrl + D
    //    Windows 通常使用 Ctrl + Z 后回车
    // 2. 输入的数据类型不匹配，导致输入流失败
    //
    // std::copy(itFirst, itLast, box.begin()); // error
    //
    // 错误原因：
    // box 当前是空 vector，box.begin() 不能作为可写入的目标位置。
    // 这里不是 box.begin() 为 nullptr，而是 vector 中没有已有元素可被覆盖写入。
    
    // 需要使用插入迭代器适配器实现自动扩容插入
    //
    // 方式一：手动创建尾插迭代器适配器对象
    // back_insert_iterator 会调用容器的 push_back() 插入元素
    // back_insert_iterator<vector<int>> it{box};
    // std::copy(itFirst, itLast, it);

    // 方式二：使用 back_inserter() 函数简化操作
    // back_inserter(box) 会返回一个 back_insert_iterator 对象
    // 每读取一个数据，就通过 push_back() 插入到 box 尾部
    std::copy(itFirst, itLast, back_inserter(box));

    // 输出容器中元素个数
    cout << box.size() << endl;

    // 打印容器中的数据
    // 使用 ostream_iterator 将容器中的元素输出到 cout
    std::copy(box.begin(), box.end(), ostream_iterator<int>{cout, " "});
}


int main(int argc, char *argv[])
{
    // test1();
    // test2();
    test3();

    return 0;
}