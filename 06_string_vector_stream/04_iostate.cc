#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::istream;

/**
 * 流的四种状态
 * 1.good(): 无报错,流可以正常使用
 * 2.fail(): 物理因素可能会导致,比如磁盘损坏
 * 3.bad(): 输入的数据和接收的类型不匹配
 * 4.eof(): 流中的数据不可用,到末尾了
 *
 * cin:标准输入流,istream类型的对象
 *
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

    // 恢复流的状态 clear()
    cin.clear();
    // 清除缓冲区的数据
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

// 用户可以连续进行输入,直到输入正确为止
void test2()
{
    int num;
    // 使用while循环
    while(true){
        cout << "input a num : " << endl;
        cin >> num;
        if(cin.bad()){
            cout << "bad !!!" << endl;
        }else if(cin.eof()){
            cout << "eof!!!!" << endl;
        }else if(cin.fail()){
            cout << "fail!!!" << endl;
            // 重置流的状态,清空缓冲区
            cin.clear();
            // 清除缓冲区的数据
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "input again: " << endl;
        }else{
            cout << "OK!!" << endl;
            break;
        }
    }

    cout << "num = " << num << endl;
}

// 用户可以连续进行输入,直到输入正确为止
void test3()
{
    int num;
    // 使用while循环
    while(!cin.eof()){
        cout << "input a num : " << endl;
        cin >> num;
        if(cin.bad()){
            cout << "bad !!!" << endl;
        }else if(cin.fail()){
            cout << "fail!!!" << endl;
            // 重置流的状态,清空缓冲区
            cin.clear();
            // 清除缓冲区的数据
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

