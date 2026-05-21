#include <iostream>
#include <string>
#include <memory>
#include <cstdio>

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::unique_ptr;

/**
 * 删除器 deleter
 *
 * 1. 删除器是什么？
 *
 *    删除器用于指定智能指针释放资源时的具体操作。
 *
 *    智能指针本质上是 RAII 思想的应用：
 *    - 构造时接管资源
 *    - 析构时释放资源
 *
 *    但是“释放资源”并不一定总是 delete。
 *
 *
 * 2. 默认删除方式
 *
 *    默认情况下：
 *
 *    unique_ptr<T> 和 shared_ptr<T>
 *
 *    管理普通堆对象时，
 *    会使用 delete 释放资源。
 *
 *    例如：
 *    unique_ptr<int> up { new int{10} };
 *
 *    up 析构时，
 *    默认执行：
 *    delete p;
 *
 *
 * 3. 为什么需要自定义删除器？
 *
 *    有些资源不是通过 new 创建的，
 *    或者它们有专门的释放函数。
 *
 *    例如：
 *
 *    - FILE* 文件资源
 *      通过 fopen() 打开，
 *      必须通过 fclose() 关闭。
 *
 *    - 动态数组
 *      通过 new [] 创建，
 *      必须通过 delete [] 释放。
 *
 *    - 网络连接、socket、数据库连接等系统资源
 *      可能需要调用 close()、shutdown() 或专门的释放函数。
 *
 *    如果智能指针管理这些资源时仍然使用默认 delete，
 *    就会导致错误。
 *
 *
 * 4. 当前代码的目的
 *
 *    使用智能指针管理 FILE* 文件资源。
 *
 *    FILE* 不是通过 new 创建出来的对象，
 *    而是通过 fopen() 打开的文件资源。
 *
 *    所以不能使用 delete 释放 FILE*，
 *    必须使用 fclose()。
 *
 *    因此这里需要提供自定义删除器 FileDeleter。
 *
 *
 * 5. unique_ptr 与 shared_ptr 删除器的写法区别
 *
 *    unique_ptr：
 *
 *    删除器类型是 unique_ptr 类型的一部分。
 *
 *    例如：
 *    unique_ptr<FILE, FileDeleter> up;
 *
 *    这里 FileDeleter 写在模板参数中。
 *
 *
 *    shared_ptr：
 *
 *    删除器不是 shared_ptr 类型的一部分。
 *
 *    删除器通常作为构造函数参数传入。
 *
 *    例如：
 *    shared_ptr<FILE> sp { fp, FileDeleter() };
 */

void test1()
{
    /**
     * 使用 C 风格文件操作打开文件。
     *
     * fopen("temp.txt","a+")
     *
     * 含义：
     * - 打开 temp.txt 文件
     * - 如果文件不存在，则创建
     * - 以追加和读写方式打开
     *
     * 返回值：
     * FILE*
     *
     * fp 指向打开的文件资源。
     */
    FILE* fp = fopen("temp.txt","a+");

    string msg = "hello";

    /**
     * 向文件中写入字符串内容。
     *
     * fwrite 参数说明：
     * - msg.c_str()：要写入的数据起始地址
     * - 1：每个数据块的大小，单位是字节
     * - msg.size()：写入的数据块数量
     * - fp：目标文件指针
     */
    fwrite(msg.c_str(),1, msg.size(), fp);

    /**
     * 手动释放文件资源。
     *
     * FILE* 是通过 fopen() 获取的，
     * 所以必须通过 fclose() 关闭。
     *
     * 如果忘记 fclose(fp)，
     * 就可能导致文件资源泄漏。
     *
     * test1 展示的是传统手动管理资源的方式。
     */
    fclose(fp);
}

/**
 * 自定义删除器
 *
 * FileDeleter 是一个函数对象。
 *
 * 所谓函数对象，
 * 就是重载了 operator() 的对象。
 *
 * 当智能指针需要释放 FILE* 资源时，
 * 会自动调用：
 *
 * FileDeleter()(fp);
 *
 * 从而执行 fclose(fp)。
 */
struct FileDeleter
{
    /**
     * operator()
     *
     * 参数：
     * FILE * fp
     *
     * fp 是智能指针当前管理的文件指针。
     *
     * 该函数定义了 FILE* 资源应该如何释放。
     */
    void operator()(FILE * fp)
    {
        cout << "close file" << endl;

        /**
         * FILE* 不能使用 delete 释放。
         *
         * 因为它不是通过 new 创建的普通堆对象，
         * 而是通过 fopen() 打开的文件资源。
         *
         * 所以必须调用 fclose(fp)。
         */
        fclose(fp);
    }
};


// unique_ptr 使用自定义删除器
void test2()
{
    /**
     * unique_ptr<FILE, FileDeleter> up { fopen("temp.txt", "a+") };
     *
     * 使用 unique_ptr 管理 FILE* 文件资源。
     *
     * 注意 unique_ptr 的模板参数：
     *
     * unique_ptr<FILE, FileDeleter>
     *
     * 第一个模板参数 FILE：
     * 表示管理的资源类型。
     *
     * 第二个模板参数 FileDeleter：
     * 表示释放资源时使用的删除器类型。
     *
     *
     * 当 up 离开作用域时，
     * unique_ptr 不会使用默认 delete，
     * 而是调用 FileDeleter::operator()(FILE*)，
     * 从而自动执行 fclose(fp)。
     */
    unique_ptr<FILE, FileDeleter> up { fopen("temp.txt", "a+") };

    string msg = "hello";

    /**
     * get() 获取 unique_ptr 内部保存的 FILE*。
     *
     * fwrite 是 C 风格函数，
     * 它需要 FILE* 类型的参数。
     *
     * 所以这里通过 up.get() 取出底层文件指针。
     *
     * 注意：
     * get() 只是获取原始指针，
     * 不释放资源，
     * 也不转移资源所有权。
     *
     * 文件资源仍然由 up 管理。
     */
    fwrite(msg.c_str(),1, msg.size(), up.get());

    /**
     * test2 结束时：
     *
     * up 作为局部对象自动析构。
     *
     * 析构时自动调用自定义删除器 FileDeleter，
     * 输出 "close file"，
     * 并执行 fclose() 关闭文件。
     */
}


// shared_ptr 使用自定义删除器
void test3()
{
    /**
     * shared_ptr<FILE> sp { fopen("temp.txt", "a+"), FileDeleter() };
     *
     * 使用 shared_ptr 管理 FILE* 文件资源。
     *
     * shared_ptr 的删除器写法与 unique_ptr 不同。
     *
     * 对 shared_ptr 来说，
     * 删除器不是模板参数的一部分，
     * 而是作为构造函数参数传入。
     *
     * 这里：
     * - 第一个参数 fopen(...) 是要管理的资源
     * - 第二个参数 FileDeleter() 是自定义删除器对象
     *
     *
     * 当最后一个 shared_ptr 释放该 FILE* 资源时，
     * shared_ptr 会调用 FileDeleter 关闭文件。
     */
    shared_ptr<FILE> sp { fopen("temp.txt", "a+"), FileDeleter() };

    string msg = "hello";

    /**
     * get() 获取 shared_ptr 内部保存的 FILE*。
     *
     * 这里只是为了调用 fwrite。
     *
     * 注意：
     * 不要对 sp.get() 返回的指针手动 fclose，
     * 否则 shared_ptr 析构时还会再次 fclose，
     * 导致错误。
     */
    fwrite(msg.c_str(),1, msg.size(), sp.get());

    /**
     * test3 结束时：
     *
     * sp 析构。
     *
     * 如果没有其他 shared_ptr 共享该 FILE*，
     * 引用计数变为 0，
     * 然后 shared_ptr 调用自定义删除器 FileDeleter，
     * 自动关闭文件。
     */
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}