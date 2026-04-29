#include <iostream>

using std::cout;
using std::endl;

/**
 * 异常处理的关键字:
 * try: 代码块,包裹可能出现异常的代码
 * catch: 捕获异常,对异常进行处理
 * throw: 抛出异常信息
 *
 * try{
 *     可能有异常的代码
 * }catch(异常类型 变量名){
 *     对异常进行处理
 * }catch(······){
 *     ······
 * }
 * 可以有很多catch,但是catch匹配是从上往下
 * 依次匹配的,只有try中存在异常,并且catch中
 * 捕获的类型和throw的类型一致,才会匹配成功,
 * 才能进入到对应的catch代码块中执行
 *
 * 另一种使用场景,作为函数的一个特殊的返回结果
 * int func(int arr[], int index)
 * {
 *    if(index < 0 || index >= size){
 *       throw "index is illegal!!!!";
 *    }
 *    return  arr[index];
 * }
 *
 * stack: push pop
 */

int division(int x, int y)
{
    cout << "division start" << endl;
    // 针对特殊情况:分母为0时进行异常处理
    if(y == 0){
        // 抛出一个异常信息
        // throw + 异常类型信息
        /* throw "y is zero!!"; */
        throw 0;
    }
    cout << "division end" << endl;
    return x / y;
}


void test1()
{
    try{
        // 可能出现异常的代码
        cout << "test1 start" << endl;
        int x = 10;
        int y = 0;
        division(x, y);
    }catch(const char * msg){
        // 对异常信息进行处理
        cout << "msg: " << msg << endl;
    }catch(int stateCode){
        cout << "stateCode: " << stateCode << endl;
    }
    cout << "test1 end" << endl;
}


int main(int argc, char *argv[])
{
    cout << "main start" << endl;
    test1();
    cout << "main end" << endl;
    return 0;
}

