#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::istream;

/**
 * 流的四种状态：
 * 1. good()：流状态正常，可以继续使用
 * 2. bad() ：发生严重错误，通常由底层物理因素导致，例如磁盘损坏
 * 3. fail()：发生可恢复错误，例如输入数据与接收类型不匹配
 * 4. eof() ：到达流的末尾，已无可读取的数据
 *
 * cin：标准输入流，是 istream 类型的对象
 */

void printState(istream & is)
{
    cout << "good: " << is.good() << endl;
    cout << "bad: " << is.bad() << endl;
    cout << "fail: " << is.fail() << endl;
    cout << "eof: " << is.eof() << endl;
}

void test1()
{
    printState(cin);
    cout << "input a num: " << endl;

    int num;
    cin >> num;
    cout << "num= " << num << endl;

    cout << "--------" << endl;
    printState(cin);
    cout << "--------" << endl;

    // 使用 clear() 恢复流的状态
    cin.clear();

    // 清除缓冲区中的数据
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    printState(cin);
    cout << "--------" << endl;

    int num2;
    cout << "input a num: " << endl;
    cin >> num2;

    cout << "--------" << endl;
    printState(cin);
    cout << "num2= " << num2 << endl;
}

// 用户可以连续输入，直到输入正确为止
void test2()
{
    int num;

    // 使用 while 循环持续接收输入
    while(true){
        cout << "input a num : " << endl;
        cin >> num;

        if(cin.bad()){
            cout << "bad !!!" << endl;
        }else if(cin.eof()){
            cout << "eof!!!!" << endl;
        }else if(cin.fail()){
            cout << "fail!!!" << endl;

            // 重置流的状态
            cin.clear();

            // 清除缓冲区中的数据
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "input again: " << endl;
        }else{
            cout << "OK!!" << endl;
            break;
        }
    }

    cout << "num = " << num << endl;
}

// 用户可以连续输入，直到输入正确为止
void test3()
{
    int num;

    // 使用 while 循环，在未到达输入流末尾时持续接收输入
    while(!cin.eof()){
        cout << "input a num : " << endl;
        cin >> num;

        if(cin.bad()){
            cout << "bad !!!" << endl;
        }else if(cin.fail()){
            cout << "fail!!!" << endl;

            // 重置流的状态
            cin.clear();

            // 清除缓冲区中的数据
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "input again: " << endl;
        }else{
            cout << "OK!!" << endl;
            break;
        }
    }

    cout << "num = " << num << endl;
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}