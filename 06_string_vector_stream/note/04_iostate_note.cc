#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::istream;

/**
 * 流的四种状态
 *
 * C++ 中的输入输出流对象，内部会维护一组状态标志。
 * 通过这些状态标志，可以判断当前流是否还能继续正常使用。
 *
 *
 * 1. good(): 表示流当前状态正常。
 *
 * 如果 good() 返回 true，
 * 说明当前没有发生 bad、fail、eof 等错误，
 * 流可以继续正常读写。
 *
 *
 * 2. bad(): 表示发生了严重错误。
 *
 * 一般是底层 I/O 出现了不可恢复的问题，
 * 例如文件系统错误、设备损坏等。
 *
 * 对于 cin 来说，bad() 比较少见。
 *
 *
 * 3. fail(): 表示输入失败。
 *
 * 常见情况：
 * 输入的数据类型和接收变量的类型不匹配。
 *
 * 例如：
 * int num;
 * cin >> num;
 *
 * 如果用户输入 abc，
 * abc 不能转换成 int，
 * 此时 cin 就会进入 fail 状态。
 *
 *
 * 4. eof(): 表示读到了输入流的末尾。
 *
 * eof 是 end of file 的缩写。
 *
 * 对于文件输入流来说，
 * eof 表示文件已经读到末尾。
 *
 * 对于标准输入 cin 来说，
 * 在 Linux / macOS 终端中通常可以通过 Ctrl + D 触发 eof，
 * 在 Windows 终端中通常可以通过 Ctrl + Z 后回车触发 eof。
 *
 *
 * cin:
 * cin 是标准输入流对象，
 * 类型是 istream。
 * 它通常从键盘读取数据。
 *
 *
 * 注意：
 * 当 cin 进入 fail 状态后，
 * 如果不进行处理，
 * 后续的输入操作会直接失败。
 *
 * 所以一般需要：
 * 1. clear()
 *    重置流的状态。
 * 2. ignore()
 *    清除输入缓冲区中残留的错误数据。
 */

/**
 * printState()
 *
 * 作用：
 * 打印当前输入流对象的状态。
 *
 * 参数：
 * istream & is
 * 使用引用传递，
 * 避免拷贝流对象。
 *
 * 注意：
 * 流对象一般不能被拷贝，
 * 所以这里必须使用引用。
 */
void printState(istream & is)
{
    /**
     * good()
     *
     * 如果流状态完全正常，
     * 返回 true。
     */
    cout << "good: " << is.good() << endl;

    /**
     * bad()
     *
     * 如果发生了严重的底层 I/O 错误，
     * 返回 true。
     */
    cout << "bad: " << is.bad() << endl;

    /**
     * fail()
     *
     * 如果发生了输入失败，
     * 返回 true。
     *
     * 常见原因是：
     * 输入的数据和变量类型不匹配。
     */
    cout << "fail: " << is.fail() << endl;

    /**
     * eof()
     *
     * 如果输入流到达末尾，
     * 返回 true。
     */
    cout << "eof: " << is.eof() << endl;
}

void test1()
{
    /**
     * 一开始先打印 cin 的状态。
     *
     * 正常情况下，
     * 程序刚开始运行时 cin 状态是正常的。
     *
     * 通常输出：
     * good: 1
     * bad: 0
     * fail: 0
     * eof: 0
     */
    printState(cin);

    cout << "input a num: " << endl;

    int num;

    /**
     * 从标准输入读取一个 int 类型的数据。
     *
     * 如果用户输入的是整数，
     * 读取成功。
     *
     * 如果用户输入的是非整数，
     * 例如 abc，
     * cin 会进入 fail 状态。
     */
    cin >> num;

    /**
     * 如果读取失败，
     * num 的值不可靠。
     *
     * 学习时可以打印观察现象，
     * 实际开发中应该先判断输入是否成功。
     */
    cout << "num= " << num << endl;

    cout << "--------" << endl;

    // 打印输入之后 cin 的状态
    printState(cin);

    cout << "--------" << endl;

    /**
     * clear()
     *
     * 作用：
     * 重置流的状态标志。
     *
     * 如果 cin 因为输入类型不匹配进入 fail 状态，
     * 必须先调用 clear()，
     * 后续的输入操作才有机会继续执行。
     *
     * 注意：
     * clear() 只负责恢复状态，
     * 不会清除输入缓冲区中的错误数据。
     */
    cin.clear();

    /**
     * ignore()
     *
     * 作用：
     * 忽略输入缓冲区中的数据。
     *
     * std::numeric_limits<std::streamsize>::max()
     * 表示一个非常大的数，
     * 用来表示最多忽略这么多个字符。
     *
     * '\n'
     * 表示遇到换行符就停止忽略。
     *
     *
     * 这行代码的含义：
     * 从输入缓冲区中一直丢弃字符，
     * 直到遇到换行符为止。
     *
     *
     * 为什么需要 ignore()？
     *
     * 例如：
     * int num;
     * cin >> num;
     *
     * 用户输入 abc。
     *
     * 由于 abc 不能转换成 int，
     * cin 进入 fail 状态，
     * 并且 abc 仍然残留在输入缓冲区中。
     *
     * 如果只调用 clear()，
     * 下一次 cin >> num 还会继续读取这个 abc，
     * 于是再次失败。
     *
     * 所以需要 clear() 和 ignore() 配合使用。
     */
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 再次打印状态，观察 cin 是否恢复正常
    printState(cin);

    cout << "--------" << endl;

    int num2;

    cout << "input a num: " << endl;

    // 再次进行输入测试
    cin >> num2;

    cout << "--------" << endl;

    // 打印第二次输入之后的状态
    printState(cin);

    cout << "num2= " << num2 << endl;
}

// 用户可以连续进行输入,直到输入正确为止
void test2()
{
    int num;

    /**
     * 使用 while(true) 死循环。
     *
     * 只要用户输入不合法，
     * 就一直要求用户重新输入。
     *
     * 当输入合法时，
     * 通过 break 跳出循环。
     */
    while(true){
        cout << "input a num : " << endl;

        /**
         * 尝试读取一个 int 类型数据。
         *
         * 读取之后，
         * 需要根据 cin 的状态判断是否读取成功。
         */
        cin >> num;

        /**
         * bad()
         *
         * 如果发生严重错误，
         * 这里打印 bad。
         *
         * 这种错误一般不容易恢复，
         * 实际开发中可以考虑直接结束程序。
         */
        if(cin.bad()){
            cout << "bad !!!" << endl;
        }
        /**
         * eof()
         *
         * 如果输入流到达末尾，
         * 说明后续可能没有数据可以继续读取。
         *
         * 这里单独判断 eof，
         * 是为了区分“输入结束”和“输入格式错误”。
         */
        else if(cin.eof()){
            cout << "eof!!!!" << endl;
        }
        /**
         * fail()
         *
         * 如果输入的数据和 int 类型不匹配，
         * cin 会进入 fail 状态。
         *
         * 例如用户输入：
         * abc
         */
        else if(cin.fail()){
            cout << "fail!!!" << endl;

            // 重置流的状态,清空缓冲区

            /**
             * 第一步：
             * clear() 重置 cin 的错误状态。
             *
             * 如果不调用 clear()，
             * 后续 cin 仍然处于 fail 状态，
             * 不能继续正常输入。
             */
            cin.clear();

            // 清除缓冲区的数据

            /**
             * 第二步：
             * ignore() 清除输入缓冲区中的错误内容。
             *
             * 这样下一次循环时，
             * cin 才会读取用户新输入的数据。
             */
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "input again: " << endl;
        }
        /**
         * 走到 else，
         * 说明没有 bad、eof、fail。
         *
         * 输入成功。
         */
        else{
            cout << "OK!!" << endl;
            break;
        }
    }

    // 输出最终成功读取到的整数
    cout << "num = " << num << endl;
}

// 用户可以连续进行输入,直到输入正确为止
void test3()
{
    int num;

    /**
     * 这个版本使用 while(!cin.eof()) 作为循环条件。
     *
     * 含义：
     * 只要没有到达输入流末尾，
     * 就继续尝试输入。
     *
     *
     * 注意：
     * eof() 只有在尝试读取之后，
     * 才能准确反映是否到达末尾。
     *
     * 所以实际开发中，
     * 更常见的写法是直接把输入操作放到条件中，
     * 例如：
     *
     * while(cin >> num)
     * {
     *     ...
     * }
     *
     * 当前写法主要用于演示流状态的判断。
     */
    while(!cin.eof()){
        cout << "input a num : " << endl;

        // 尝试读取 int 类型数据
        cin >> num;

        /**
         * 如果发生严重 I/O 错误，
         * bad() 返回 true。
         */
        if(cin.bad()){
            cout << "bad !!!" << endl;
        }
        /**
         * 如果读取失败，
         * 例如输入了不能转换成 int 的内容，
         * fail() 返回 true。
         *
         * 注意：
         * eof 状态也可能伴随 fail 状态出现。
         *
         * 当前循环条件已经判断了 !cin.eof()，
         * 所以这里主要处理普通的格式错误。
         */
        else if(cin.fail()){
            cout << "fail!!!" << endl;

            // 重置流的状态,清空缓冲区

            /**
             * clear()
             *
             * 清除 fail 状态，
             * 让 cin 可以继续执行后续输入。
             */
            cin.clear();

            // 清除缓冲区的数据

            /**
             * ignore()
             *
             * 丢弃当前这一行中残留的错误输入。
             */
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "input again: " << endl;
        }
        /**
         * 没有 bad，也没有 fail，
         * 说明输入成功。
         */
        else{
            cout << "OK!!" << endl;
            break;
        }
    }

    /**
     * 输出 num。
     *
     * 注意：
     * 如果用户直接触发 eof，
     * 并且没有成功输入过整数，
     * 那么 num 的值可能没有被有效赋值。
     *
     * 更严谨的写法可以增加一个 bool 标志，
     * 用来记录是否成功读取过数据。
     */
    cout << "num = " << num << endl;
}

int main(int argc, char *argv[])
{
    /**
     * main 函数是程序入口。
     *
     * 当前只有 test3() 没有被注释，
     * 所以程序运行时只会执行 test3()。
     *
     * 如果想测试其它函数，
     * 可以取消对应函数调用前面的注释。
     */

    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}