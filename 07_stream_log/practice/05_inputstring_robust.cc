#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    string line; // 用于保存用户输入的一整行内容
    int num;     // 用于保存最终合法的整数

    while(1)
    {
        cout << "请输入一个int型整数: ";
        // 读取用户输入的一整行
        getline(cin, line);

        // 将字符串line放入字符串输入流iss中
        istringstream iss(line);
        
        // 尝试从字符串输入流中读取一个int
        if(!(iss >> num))
        {
            cout << "输入有误,请重新输入!" << endl;
            continue;
        }

        // 读取int成功后,还有判断后面是否还有多余内容
        char extra;
        // 如果还能读取到字符,说明输入中有多余内容
        if(iss >> extra){
            cout << "输入有误,请重新输入!" << endl;
            continue;
        }

        // 程序如果能运行到这里,说明输入合法
        break;
    }

    cout << "输入的合法整数为: " << num << endl;

    return 0;
}

