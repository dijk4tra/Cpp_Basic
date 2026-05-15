#include <iostream>
#include <unistd.h>

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;

/**
 * 通用输入输出流 istream / ostream
 *
 * C++ 中的输入输出操作是通过“流”完成的。
 *
 * 流可以理解为：
 * 数据在程序和外部设备之间传输的通道。
 *
 *
 * 1. istream
 *
 * istream 是输入流类型。
 *
 * 作用：
 * 从外部设备读取数据到程序中。
 *
 * 例如：
 * cin 就是 istream 类型的对象。
 *
 *
 * 2. ostream
 *
 * ostream 是输出流类型。
 *
 * 作用：
 * 将程序中的数据输出到外部设备。
 *
 * 例如：
 * cout 就是 ostream 类型的对象。
 *
 *
 * cin:
 *
 * cin 是标准输入流对象。
 * 默认输入设备是键盘。
 *
 * 本质：
 * cin 是 istream 类型的一个全局对象。
 *
 * 可以简单理解为：
 * istream cin;
 *
 *
 * cout:
 *
 * cout 是标准输出流对象。
 * 默认输出设备是终端控制台。
 *
 * 本质：
 * cout 是 ostream 类型的一个全局对象。
 *
 * 可以简单理解为：
 * ostream cout;
 *
 *
 * 常见标准流对象：
 *
 * 1. cin
 *    标准输入流，默认从键盘读取。
 *
 * 2. cout
 *    标准输出流，默认输出到终端。
 *
 * 3. cerr
 *    标准错误流，默认输出到终端。
 *    一般不带缓冲区，常用于输出错误信息。
 *
 * 4. clog
 *    标准日志流，默认输出到终端。
 *    一般带缓冲区。
 *
 *
 * 缓冲区：
 *
 * 输出内容不一定会立刻显示到终端。
 * 有些内容会先保存到缓冲区中，
 * 等到满足条件时再统一刷新到设备上。
 *
 *
 * 常见缓冲方式：
 *
 * 1. 行缓冲
 *    遇到换行符 '\n' 时刷新缓冲区。
 *
 * 2. 全缓冲
 *    缓冲区满了才刷新。
 *
 * 3. 非缓冲
 *    没有缓冲区，内容会尽快输出。
 *
 *
 * 常见刷新缓冲区的方式：
 *
 * 1. 输出 endl
 *    endl 不只是换行，
 *    还会刷新缓冲区。
 *
 * 2. 输出 '\n'
 *    只是换行，
 *    不一定立即刷新缓冲区。
 *
 * 3. 调用 flush
 *    cout << std::flush;
 *
 * 4. 程序正常结束时
 *    会自动刷新标准输出流。
 */


void test1()
{
    cout << "input nums: " << endl;

    int num1;
    int num2;

    /**
     * cin >> num1;
     *
     * 从标准输入流 cin 中读取一个 int 类型数据，
     * 保存到变量 num1 中。
     *
     * 输入时，空格、制表符、换行符都可以作为分隔符。
     */
    cin >> num1;

    /**
     * 再读取一个 int 类型数据，
     * 保存到 num2 中。
     *
     * 也就是说：
     * 用户可以分两行输入，
     * 也可以在同一行用空格隔开输入。
     */
    cin >> num2;

    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
}

void test2()
{
    cout << "input nums: " << endl;

    int num1;
    int num2;

    /**
     * 连续输入
     *
     * cin >> num1 >> num2;
     *
     * 这行代码等价于：
     * cin >> num1;
     * cin >> num2;
     *
     * 为什么可以连续输入？
     *
     * 因为 operator>> 的返回值是输入流对象本身，
     * 也就是 istream &。
     *
     * 可以简单理解为：
     *
     * cin >> num1 >> num2;
     *
     * 实际执行顺序类似：
     *
     * (cin >> num1) >> num2;
     *
     * cin >> num1 执行完之后，
     * 返回 cin 本身，
     * 然后继续执行 cin >> num2。
     */
    cin >> num1 >> num2;

    /**
     * 连续输出
     *
     * cout << "num1 = " << num1 << endl;
     *
     * 之所以可以连续使用 <<，
     * 原理和连续输入类似。
     *
     * operator<< 的返回值是输出流对象本身，
     * 也就是 ostream &。
     */
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;

    // 能够连续的输入输出,和能够连续赋值是类似的(重点理解)

    /**
     * 连续赋值：
     *
     * Point pt1;
     * Point pt2;
     * Point pt3;
     *
     * pt3 = pt2 = pt1;
     *
     * 执行顺序：
     * pt3 = (pt2 = pt1);
     *
     * pt2 = pt1 调用 operator=，
     * 如果 operator= 返回 Point &，
     * 就可以继续作为右操作数赋值给 pt3。
     *
     *
     * 输入输出流的连续调用也是同样的思想：
     *
     * cin >> num1 >> num2;
     * cout << num1 << num2;
     *
     * 关键点：
     * operator>> 和 operator<< 都返回流对象的引用。
     */
    /**
     * Point pt1;
     * Point pt2;
     * Point pt3;
     * pt3 = pt2 = pt1; //连续调用operator=这个函数
     * 返回值类型为Point &
     * Point & operator=();
     * pt3.operator=(p2.operator=(pt1));
     *
     * << >>
     * ostream & operator<<();
     * cout.operator<<(数据)
     */
}

// cin 可以作为if判断的条件
void test3()
{
    cout << "input a num:" << endl;

    int num;

    /* if(cin.good()){ */

    /**
     * cin 可以放在 if 条件中。
     *
     * if(cin)
     *
     * 这并不是判断 cin 对象是否存在，
     * 而是判断 cin 当前流状态是否正常。
     *
     * 当 cin 处于 good 状态时，
     * 转换成 bool 结果为 true。
     *
     * 当 cin 处于 fail、bad、eof 等非正常状态时，
     * 转换成 bool 结果为 false。
     *
     *
     * 注意：
     * 当前代码是在输入之前判断 cin 的状态。
     * 如果程序刚开始运行，cin 通常是正常的，
     * 所以 if(cin) 通常成立。
     *
     * 更常见、更严谨的写法是：
     *
     * if(cin >> num)
     * {
     *     cout << num << endl;
     * }
     *
     * 这样可以直接判断本次输入是否成功。
     */
    // good状态 ---> true
    // 非good状态---> false
    if(cin){
        cin >> num;
    }

    /**
     * 如果输入失败，
     * num 的值可能不可靠。
     *
     * 学习时可以通过打印观察现象，
     * 实际开发中应该先判断输入是否成功。
     */
    cout << num << endl;
}


// 测试缓冲区
void test4()
{
    /**
     * 这里连续输出 100 个字符 'a'。
     *
     * 注意：
     * 没有输出 endl，
     * 也没有手动 flush。
     *
     * 所以这些字符可能会先进入缓冲区，
     * 不一定立刻显示到终端。
     */
    for(int i = 0; i < 100; ++i){
        cout << 'a';
    }

    // 程序结束时进行刷新

    /**
     * 程序正常结束时，
     * 标准输出流 cout 的缓冲区会被刷新，
     * 所以最终仍然可以看到输出内容。
     */
}

void test5()
{
    /**
     * 这里先输出 100 个字符 'a'。
     *
     * 因为没有 endl，
     * 所以在某些环境下，
     * 这些字符可能先留在缓冲区中。
     */
    for(int i = 0; i < 100; ++i){
        cout << 'a';
    }

    // 让程序暂停执行5s

    /**
     * sleep(5)
     *
     * 作用：
     * 让当前程序暂停执行 5 秒。
     *
     * 头文件：
     * #include <unistd.h>
     *
     * 注意：
     * sleep 是 POSIX 系统中的函数，
     * 在 Linux / macOS 中可以使用。
     * 在 Windows 中通常不能直接使用这个头文件和函数。
     *
     *
     * 这里使用 sleep(5)，
     * 是为了观察 cout 缓冲区是否立即刷新。
     */
    sleep(5);

    /**
     * 如果前面的 'a' 没有刷新，
     * 可能会在后续刷新时一起显示。
     */
    cout << "test5 end";
}

// 全缓冲
void test6()
{
    /**
     * 全缓冲：
     *
     * 当输出目标不是终端，而是普通文件等设备时，
     * 通常可能采用全缓冲。
     *
     * 全缓冲的特点：
     * 缓冲区没有满时，不一定立即输出；
     * 当缓冲区满了，才会自动刷新。
     *
     *
     * 这里输出 1030 个字符，
     * 是为了观察输出内容较多时，
     * 缓冲区可能被填满并触发刷新。
     *
     * 注意：
     * 不同系统、不同终端、不同运行环境下，
     * 缓冲区大小和刷新时机可能不同。
     */
    for(int i = 0; i < 1030; ++i){
        cout << 'a';
    }

    // 让程序暂停执行5s
    sleep(5);

    cout << "test6 end";
}

// 行缓冲
void test7()
{
    /**
     * 行缓冲：
     *
     * 当输出目标是终端时，
     * 标准输出通常表现为行缓冲。
     *
     * 行缓冲的特点：
     * 遇到换行符时刷新缓冲区。
     *
     *
     * endl 的作用：
     * 1. 输出换行。
     * 2. 刷新缓冲区。
     *
     * 所以这里每次输出 'a' << endl，
     * 都会换行并刷新一次缓冲区。
     */
    for(int i = 0; i < 100; ++i){
        cout << 'a' << endl;
    }

    // 让程序暂停执行5s
    sleep(5);

    cout << "test7 end";
}

void test8()
{
    /**
     * cerr
     *
     * cerr 是标准错误流。
     *
     * 默认输出设备通常也是终端控制台。
     *
     * cerr 常用于输出错误信息。
     *
     *
     * cerr 和 cout 的区别：
     *
     * cout 是标准输出流，
     * 一般带缓冲区。
     *
     * cerr 是标准错误流，
     * 一般不带缓冲区。
     *
     * 所以 cerr 输出的内容通常会立刻显示，
     * 不需要等到缓冲区满或者程序结束。
     */
    for(int i = 0; i < 100; ++i){
        // 标准错误流,不带缓冲区
        std::cerr << 'a';
    }

    // 让程序暂停执行5s
    sleep(5);

    /**
     * 这里用 cout 输出结束提示。
     *
     * 因为 cout 和 cerr 是两个不同的流，
     * 在某些环境下，二者混合输出时，
     * 显示顺序可能会受到缓冲区影响。
     */
    cout << "test8 end";
}

int main(int argc, char *argv[])
{
    /**
     * main 函数是程序入口。
     *
     * 当前只有 test8() 没有被注释，
     * 所以程序运行时只会执行 test8()。
     *
     * 如果想测试其它函数，
     * 可以取消对应函数调用前面的注释。
     */

    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    /* test6(); */
    /* test7(); */
    test8();

    return 0;
}