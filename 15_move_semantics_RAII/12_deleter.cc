#include <iostream>
#include <string>
#include <memory>
#include <cstdio>

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::unique_ptr;

/*
 * 删除器：
 *      用于指定智能指针释放资源时的具体操作。
 *
 * 默认情况下：
 *      unique_ptr / shared_ptr 管理普通堆对象时，
 *      会使用 delete 释放资源。
 *
 * 但有些资源不能用 delete 释放，例如：
 *      文件资源：需要 fclose()
 *      网络连接：需要 close() / shutdown()
 *      动态数组：需要 delete[]
 *      其他系统资源：可能有对应的专门释放函数
 *
 * 因此：
 *      当智能指针管理的不是普通 new 出来的对象时，
 *      通常需要提供自定义删除器。
 */

void test1()
{
    // 使用 C 风格文件操作打开文件
    FILE* fp = fopen("temp.txt","a+");

    string msg = "hello";

    // 向文件中写入字符串内容
    fwrite(msg.c_str(),1, msg.size(), fp);

    // 手动释放文件资源
    fclose(fp);
}

// 自定义删除器：用于释放 FILE* 文件资源
struct FileDeleter
{
    // 重载 operator()，使 FileDeleter 成为函数对象
    // 当智能指针释放资源时，会自动调用该函数
    void operator()(FILE * fp)
    {
        cout << "close file" << endl;

        // FILE* 不能用 delete 释放，必须使用 fclose()
        fclose(fp);
    }
};

// unique_ptr 使用自定义删除器
void test2()
{
    // unique_ptr 管理 FILE* 时，需要指定删除器类型 FileDeleter
    // 当 up 离开作用域时，会自动调用 FileDeleter 关闭文件
    unique_ptr<FILE, FileDeleter> up { fopen("temp.txt", "a+") };

    string msg = "hello";

    // get() 获取底层 FILE*，用于调用 C 风格文件操作函数
    // 注意：get() 不释放资源，也不转移所有权
    fwrite(msg.c_str(),1, msg.size(), up.get());
}

// shared_ptr 使用自定义删除器
void test3()
{
    // shared_ptr 的删除器作为构造函数参数传入
    // 当最后一个 shared_ptr 释放资源时，会调用 FileDeleter 关闭文件
    shared_ptr<FILE> sp { fopen("temp.txt", "a+"), FileDeleter() };

    string msg = "hello";

    // get() 获取底层 FILE*，用于写文件
    // 注意：文件资源仍然由 shared_ptr 管理
    fwrite(msg.c_str(),1, msg.size(), sp.get());
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}