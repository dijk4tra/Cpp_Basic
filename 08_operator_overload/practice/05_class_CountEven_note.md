这个作业的核心是：**函数对象不仅像函数一样可以被调用，还可以像普通对象一样保存自己的状态信息**。

也就是说，`CountEven` 这个对象一边处理数据，一边把统计结果保存在自己的成员变量里。

---

## 一、什么是函数对象？

函数对象，也叫 **仿函数**，本质上是一个类对象。

只要一个类重载了 `operator()`，这个类创建出来的对象就可以像函数一样使用。

比如：

```cpp
CountEven counter;

counter(10); // 看起来像函数调用
```

实际上调用的是：

```cpp
counter.operator()(10);
```

所以你写的这个成员函数：

```cpp
void operator()(int val);
```

表示：当 `CountEven` 对象被当作函数调用时，要执行什么操作。

---

## 二、这个作业要统计什么？

给定一个 `vector<int>`：

```cpp
vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
```

我们要统计两件事情：

第一，函数对象一共被调用了多少次。

因为 `vector` 中有 10 个元素，每个元素都会传给函数对象处理一次，所以调用次数应该是：

```cpp
10
```

第二，统计其中有多少个偶数。

这组数据中的偶数是：

```cpp
2, 4, 6, 8, 10
```

所以偶数个数是：

```cpp
5
```

最终结果应该是：

```cpp
偶数的个数: 5
函数对象被调用的次数: 10
```

---

## 三、完整代码：使用普通循环版本

这个版本最容易理解，建议你先掌握这个。

```cpp
#include <iostream>
#include <vector>

using namespace std;

// CountEven 是一个函数对象类
// 它的作用是：
// 1. 统计被调用了多少次
// 2. 统计传入的数据中有多少个偶数
class CountEven
{
public:
    // 构造函数
    // 当创建 CountEven 对象时，会自动调用这个构造函数
    // 这里把两个统计值都初始化为 0
    CountEven()
        : m_count(0)       // 初始化偶数个数为 0
        , m_callCount(0)   // 初始化调用次数为 0
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
        if (val % 2 == 0)
        {
            // 如果 val 是偶数，
            // 偶数个数加 1
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
    int m_count;      // 记录偶数的个数
    int m_callCount;  // 记录 operator() 被调用的次数
};

int main()
{
    // 创建一个 vector 容器，里面存放 1 到 10
    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 创建 CountEven 类型的函数对象
    // 此时 counter 内部的 m_count 和 m_callCount 都是 0
    CountEven counter;

    // 遍历 vector 中的每一个元素
    for (int num : vec)
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
```

---

## 四、程序执行过程分析

初始状态：

```cpp
m_count = 0
m_callCount = 0
```

然后依次处理 `vector` 中的元素。

| 当前元素 | 是否调用 `operator()` | 调用次数 | 是否偶数 | 偶数个数 |
| ---- | ----------------: | ---: | ---: | ---: |
| 1    |                 是 |    1 |    否 |    0 |
| 2    |                 是 |    2 |    是 |    1 |
| 3    |                 是 |    3 |    否 |    1 |
| 4    |                 是 |    4 |    是 |    2 |
| 5    |                 是 |    5 |    否 |    2 |
| 6    |                 是 |    6 |    是 |    3 |
| 7    |                 是 |    7 |    否 |    3 |
| 8    |                 是 |    8 |    是 |    4 |
| 9    |                 是 |    9 |    否 |    4 |
| 10   |                 是 |   10 |    是 |    5 |

所以最后：

```cpp
m_count = 5
m_callCount = 10
```

---

## 五、使用 `for_each` 的版本

如果你的作业要求使用 STL 算法，也可以使用 `for_each`。

不过这里有一个容易出错的地方：**`for_each` 会复制函数对象**。

所以推荐使用它的返回值。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class CountEven
{
public:
    CountEven()
        : m_count(0)
        , m_callCount(0)
    {}

    void operator()(int val)
    {
        ++m_callCount;

        if (val % 2 == 0)
        {
            ++m_count;
        }
    }

    int getCount() const
    {
        return m_count;
    }

    int getCallCount() const
    {
        return m_callCount;
    }

private:
    int m_count;
    int m_callCount;
};

int main()
{
    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    CountEven counter;

    // for_each 会遍历 [vec.begin(), vec.end()) 范围内的所有元素
    // 并把每一个元素传给 counter
    //
    // 注意：
    // for_each 内部使用的是 counter 的副本进行调用
    // 但它会把最终修改后的函数对象副本返回出来
    //
    // 所以我们要用 counter 接收返回值
    counter = for_each(vec.begin(), vec.end(), counter);

    cout << "偶数的个数: " << counter.getCount() << endl;
    cout << "函数对象被调用的次数: " << counter.getCallCount() << endl;

    return 0;
}
```

这个版本中：

```cpp
counter = for_each(vec.begin(), vec.end(), counter);
```

意思是：

把 `counter` 传给 `for_each`，让它处理所有元素，然后把处理完成之后的函数对象返回，再赋值给 `counter`。

---

## 六、另一种 `for_each` 写法：使用 `ref`

如果你不想接收返回值，也可以使用 `std::ref`，让 `for_each` 使用原来的对象，而不是复制对象。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class CountEven
{
public:
    CountEven()
        : m_count(0)
        , m_callCount(0)
    {}

    void operator()(int val)
    {
        ++m_callCount;

        if (val % 2 == 0)
        {
            ++m_count;
        }
    }

    int getCount() const
    {
        return m_count;
    }

    int getCallCount() const
    {
        return m_callCount;
    }

private:
    int m_count;
    int m_callCount;
};

int main()
{
    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    CountEven counter;

    // std::ref(counter) 表示传递 counter 的引用包装器
    // 这样 for_each 修改的就是原来的 counter 对象
    // 而不是 counter 的副本
    for_each(vec.begin(), vec.end(), ref(counter));

    cout << "偶数的个数: " << counter.getCount() << endl;
    cout << "函数对象被调用的次数: " << counter.getCallCount() << endl;

    return 0;
}
```

注意这个版本需要包含头文件：

```cpp
#include <functional>
```

因为 `std::ref` 定义在 `<functional>` 中。

---

## 七、重点总结

这个类里面有两个成员变量：

```cpp
int m_count;
int m_callCount;
```

它们就是函数对象保存的状态信息。

`m_callCount` 表示函数对象被调用了多少次：

```cpp
++m_callCount;
```

`m_count` 表示满足条件的元素个数，也就是偶数个数：

```cpp
if (val % 2 == 0)
{
    ++m_count;
}
```

函数对象的优点是：它既可以像函数一样被调用，又可以像对象一样保存数据。

所以这个作业的关键点就是：

```cpp
void operator()(int val)
{
    ++m_callCount;

    if (val % 2 == 0)
    {
        ++m_count;
    }
}
```

这是整个程序最核心的部分。
