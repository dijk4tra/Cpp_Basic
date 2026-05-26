#include <iostream>
#include <vector>
#include <algorithm> // 必须引入该头文件以使用 std::for_each

using namespace std;

// 按值捕获 [=] 或 [变量名]
void test1()
{
    int num = 10;
    // [num] 表示只捕获 num 这个变量的值
    auto capture_by_value = [num]() {
        cout << "按值捕获的 num = " << num << std::endl;
    };
    capture_by_value();
}

// 按引用捕获 [&] 或 [&变量名]
void test2()
{
    int count = 100;
    // [&count] 表示按引用捕获 count
    auto capture_by_ref = [&count]() {
        count += 50; // 直接修改外部变量
    };
    capture_by_ref();
    std::cout << "按引用捕获后外部的 count = " << count << std::endl; // 输出 150
}

// 带有参数
void test3()
{
    // (int a, int b) 是参数列表
    auto add = [](int a, int b) {
        cout << "两数之和：" << (a + b) << endl;
    };
    add(2, 3); // 输出 8
}

//带有返回值
void test4()
{
    // -> double 显式指定返回值类型
    auto divide = [](double a, double b) ->double {
        if(b == 0) return 0.0;
        return a / b;
    };
    double result = divide(10.0, 4.0);
    std::cout << "除法结果: " << result << std::endl; // 输出 2.5
}

// 使用 lambda 对容器中的元素进行遍历操作
void test5()
{
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << "容器中的元素有: ";
    // 使用 std::for_each 结合 lambda 表达式遍历
    // 这里的 lambda 接收容器中每个元素的引用或值（这里用 int n）
    for_each(numbers.begin(), numbers.end(), [](int n){
        cout << n << " ";
    });
    cout << endl;
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();

    return 0;
}