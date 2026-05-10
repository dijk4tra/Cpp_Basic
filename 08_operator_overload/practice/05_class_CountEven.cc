#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// CountEven 是一个函数对象类
// 它的作用是：
// 1. 统计被调用了多少次
// 2. 统计传入的数据中有多少个偶数
class CountEven
{
public:
    // 构造函数
    CountEven()
    : m_count(0)
    , m_callCount(0)
    {}
    
    // 重载函数调用运算符 operator()
    // 有了这个函数之后，CountEven 的对象就可以像函数一样被调用
    //
    // 例如：
    // CountEven counter;
    // counter(10);
    //
    // 上面的 counter(10) 实际上就是调用：
    // counter.operator()(10);
    void operator()(int val)
    {
        // 只要 operator() 被调用一次，
        // 就说明函数对象处理了一个元素，
        // 所以调用次数加 1
        ++m_callCount;

        // 判断当前传入的 val 是否是偶数
        // 一个整数能被 2 整除，说明它是偶数
        if(val % 2 == 0)
        {
            ++m_count;
        }
    }

    // 获取偶数的个数
    // const 表示这个函数不会修改成员变量
    int getCount() const
    {
        return m_count;
    }

    // 获取函数对象被调用的次数
    // const 表示这个函数只是读取数据，不修改对象状态
    int getCallCount() const
    {
        return m_callCount;
    }

private:
    int m_count; // 记录偶数的个数
    int m_callCount;  // 记录 operator() 被调用的次数
};

int main(int argc, char *argv[])
{
    // 创建一个 vector 容器，里面存放 1 到 10
    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 创建 CountEven 类型的函数对象
    // 此时 counter 内部的 m_count 和 m_callCount 都是 0
    CountEven counter;

    // 遍历 vector 中的每一个元素
    for(int num : vec)
    {
        // 把当前元素 num 传给函数对象 counter
        // 这里看起来像调用函数，
        // 实际上调用的是 counter.operator()(num)
        counter(num);
    }

    // 输出统计结果
    cout << "偶数的个数: " << counter.getCount() << endl;
    cout << "函数对象被调用的次数: " << counter.getCallCount() << endl;

    return 0;
}

