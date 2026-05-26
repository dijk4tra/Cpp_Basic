#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>
#include <list>

using namespace std;

/**
 * 迭代器适配器 iterator adapter：
 *
 * 适配器 adapter 的含义是：
 * 在原有对象的基础上进行包装，
 * 改变它对外表现出来的使用方式。
 *
 * 迭代器适配器就是：
 * 把某些对象包装成“像迭代器一样可以使用”的对象。
 *
 *
 * 本文件主要涉及两类迭代器适配器：
 *
 * 1. 插入迭代器适配器
 *
 *    用于配合 STL 算法，
 *    把算法中的“赋值操作”转换成容器的“插入操作”。
 *
 *    例如：
 *
 *    *it = value;
 *
 *    对普通迭代器来说，
 *    表示给当前位置赋值。
 *
 *    但对插入迭代器适配器来说，
 *    表示向容器中插入 value。
 *
 *
 * 2. 反向迭代器适配器
 *
 *    用于从后往前遍历容器。
 *
 *    例如：
 *    rbegin()
 *    rend()
 *
 *
 * 头文件：
 *
 * #include <iterator>
 */


/**
 * 插入迭代器适配器：
 *
 * 1. back_insert_iterator
 *
 *    尾部插入迭代器。
 *
 *    底层调用容器的：
 *    push_back()
 *
 *    适合支持 push_back 的容器。
 *
 *    例如：
 *    vector
 *    list
 *    deque
 *
 *
 * 2. front_insert_iterator
 *
 *    头部插入迭代器。
 *
 *    底层调用容器的：
 *    push_front()
 *
 *    适合支持 push_front 的容器。
 *
 *    例如：
 *    list
 *    deque
 *
 *    注意：
 *    vector 不支持 push_front，
 *    所以不能对 vector 使用 front_insert_iterator。
 *
 *
 * 3. insert_iterator
 *
 *    指定位置插入迭代器。
 *
 *    底层调用容器的：
 *    insert()
 *
 *    插入位置由创建 insert_iterator 时指定。
 *
 *
 * 以上三种都是迭代器适配器类型。
 */


/**
 * 创建插入迭代器适配器的辅助函数：
 *
 * 1. back_inserter(container)
 *
 *    创建 back_insert_iterator 对象。
 *
 *
 * 2. front_inserter(container)
 *
 *    创建 front_insert_iterator 对象。
 *
 *
 * 3. inserter(container, position)
 *
 *    创建 insert_iterator 对象。
 *
 *    position 表示插入位置。
 *
 *
 * 为什么更常用辅助函数？
 *
 * 因为辅助函数可以自动推导容器类型，
 * 写起来更加简单。
 *
 * 例如：
 *
 * back_insert_iterator<vector<int>> it{box};
 *
 * 可以简化为：
 *
 * back_inserter(box)
 */


// 把一个容器中的元素复制到另一个空容器中
void test1()
{
    /**
     * box1 是源容器，
     * 里面已经有 1、2、3、4、5。
     */
    vector<int> box1{1, 2, 3, 4, 5};

    /**
     * box2 是目标容器。
     *
     * 此时 box2 是空的，
     * 不能直接使用 box2.begin() 作为 copy 的目标位置。
     *
     * 因为空 vector 中没有已经存在的元素空间可以被赋值。
     */
    vector<int> box2;

    /**
     * back_insert_iterator：
     *
     * 尾部插入迭代器适配器。
     *
     * back_insert_iterator<vector<int>> it{ box2 };
     *
     * 表示创建一个与 box2 绑定的尾插迭代器。
     *
     *
     * 当 STL 算法执行类似下面的操作时：
     *
     * *it = value;
     *
     * 实际会被转换为：
     *
     * box2.push_back(value);
     *
     *
     * 所以即使 box2 是空容器，
     * 也可以通过 back_insert_iterator 不断向尾部插入新元素。
     */
    back_insert_iterator<vector<int>> it{ box2 };

    /**
     * std::copy：
     *
     * 把 box1 中 [begin, end) 区间的元素
     * 依次写入到目标迭代器 it。
     *
     * 由于 it 是 back_insert_iterator，
     * 所以这些写入操作会变成 box2.push_back()。
     *
     * 最终 box2 中保存：
     * 1 2 3 4 5
     */
    std::copy(box1.begin(), box1.end(), it);

    /**
     * 使用 ostream_iterator 打印 box2。
     *
     * 该知识点前面已经详细解释过，
     * 这里表示把 box2 中的数据依次输出到 cout。
     */
    std::copy(box2.begin(), box2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}


// 尾部插入
void test2()
{
    vector<int> box1{1, 2, 3, 4, 5};
    vector<int> box2;

    /**
     * back_inserter(box2)：
     *
     * 是一个辅助函数。
     *
     * 它会根据 box2 的类型，
     * 自动创建对应的 back_insert_iterator 对象。
     *
     * 下面这句等价于：
     *
     * back_insert_iterator<vector<int>> it{box2};
     * std::copy(box1.begin(), box1.end(), it);
     *
     *
     * 实际开发中更推荐使用 back_inserter，
     * 因为写法更简单。
     */
    std::copy(box1.begin(), box1.end(), back_inserter(box2));

    // 打印 box2：1 2 3 4 5
    std::copy(box2.begin(), box2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}


// 头部插入，底层调用目标容器的 push_front()
void test3()
{
    /**
     * box1 是源容器。
     */
    vector<int> box1{1, 2, 3, 4, 5};

    /**
     * box2 是目标容器。
     *
     * 这里使用 list，
     * 因为 list 支持 push_front()。
     *
     * 注意：
     * vector 不支持 push_front()，
     * 所以不能作为 front_insert_iterator 的目标容器。
     */
    list<int> box2;

    /**
     * front_insert_iterator：
     *
     * 头部插入迭代器适配器。
     *
     * front_insert_iterator<list<int>> it{ box2 };
     *
     * 表示创建一个与 box2 绑定的头插迭代器。
     *
     *
     * 当执行：
     *
     * *it = value;
     *
     * 实际会转换为：
     *
     * box2.push_front(value);
     */
    front_insert_iterator<list<int>> it{ box2 };

    /**
     * 将 box1 中的元素依次插入到 box2 头部。
     *
     * 插入过程：
     *
     * 原始 box2：
     * 空
     *
     * 插入 1：
     * 1
     *
     * 插入 2：
     * 2 1
     *
     * 插入 3：
     * 3 2 1
     *
     * 插入 4：
     * 4 3 2 1
     *
     * 插入 5：
     * 5 4 3 2 1
     *
     * 所以最终顺序会变成：
     * 5 4 3 2 1
     */
    std::copy(box1.begin(), box1.end(), it);

    // 打印 box2：5 4 3 2 1
    std::copy(box2.begin(), box2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}


// 头部插入
void test4()
{
    vector<int> box1{1, 2, 3, 4, 5};
    list<int> box2;

    /**
     * front_inserter(box2)：
     *
     * 自动创建 front_insert_iterator<list<int>> 对象。
     *
     * 它会把 copy 中的赋值操作，
     * 转换成 box2.push_front()。
     *
     * 因此最终顺序会被反转。
     */
    std::copy(box1.begin(), box1.end(), front_inserter(box2));

    // 输出顺序：5 4 3 2 1
    std::copy(box2.begin(), box2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}


// 中间插入，底层调用目标容器的 insert() 函数
void test5()
{
    /**
     * box1 是源容器。
     */
    vector<int> box1{1, 2, 3, 4, 5};

    /**
     * box2 是目标容器，
     * 初始内容为：
     * 6 7 8
     */
    list<int> box2{6, 7, 8};

    /**
     * 中间插入需要指定插入位置。
     *
     * box2.begin() 初始指向第一个元素 6。
     */
    auto it = box2.begin();

    /**
     * it++ 后，
     * it 从元素 6 移动到元素 7。
     *
     * 此时 it 指向第二个元素 7。
     */
    it++;

    /**
     * inserter(box2, it)：
     *
     * 创建 insert_iterator 对象。
     *
     * 它会把写入操作：
     *
     * *it = value;
     *
     * 转换成：
     *
     * box2.insert(插入位置, value);
     *
     *
     * 注意：
     * 插入位置是原来 it 指向的位置之前。
     *
     * 当前 it 指向 7，
     * 所以 box1 中的元素会被插入到 7 的前面。
     *
     *
     * 插入过程：
     *
     * 原始 box2：
     * 6 7 8
     *
     * 插入 box1 中的 1 2 3 4 5 后：
     * 6 1 2 3 4 5 7 8
     */
    std::copy(box1.begin(), box1.end(), inserter(box2, it));

    // 打印 box2：6 1 2 3 4 5 7 8
    std::copy(box2.begin(), box2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}


void test6()
{
    /**
     * 创建 vector 容器。
     *
     * 元素顺序为：
     * 1 2 3 4 5
     */
    vector<int> box1{1, 2, 3, 4, 5};

    /**
     * 正向遍历时，通常使用普通迭代器：
     *
     * for (auto it = box1.begin(); it != box1.end(); ++it)
     *
     * begin() 指向第一个元素。
     * end() 指向最后一个元素的后一个位置。
     */

    /**
     * 反向迭代器 reverse_iterator：
     *
     * 用于从后往前遍历容器。
     *
     * rbegin()：
     * 返回指向最后一个元素的反向迭代器。
     *
     * rend()：
     * 返回指向第一个元素前一个位置的反向迭代器。
     *
     *
     * 对 vector<int> box1{1, 2, 3, 4, 5};
     *
     * box1.rbegin() 指向元素 5。
     * box1.rend() 指向元素 1 前面的位置。
     */
    vector<int>::reverse_iterator it = box1.rbegin();

    /**
     * 当前 it 指向最后一个元素 5。
     */
    cout << *it << endl;

    /**
     * 对反向迭代器执行 ++it：
     *
     * 从遍历逻辑上看，
     * 是访问“反向遍历的下一个元素”。
     *
     * 也就是从 5 移动到 4。
     *
     * 所以虽然写的是 ++it，
     * 但是访问方向是从右往左。
     */
    ++it;

    /**
     * 当前 it 指向元素 4。
     */
    cout << *it << endl;
}


void test7()
{
    /**
     * 创建 vector 容器：
     * 1 2 3 4 5
     */
    vector<int> box1{1,2,3,4,5};

    /**
     * 使用反向迭代器倒序遍历容器。
     *
     * rbegin() 指向最后一个元素 5。
     * rend() 指向第一个元素 1 前面的位置。
     *
     *
     * 遍历过程：
     *
     * it = rbegin()  指向 5
     * ++it           指向 4
     * ++it           指向 3
     * ++it           指向 2
     * ++it           指向 1
     * ++it           到达 rend()
     *
     * 所以输出结果：
     * 5 4 3 2 1
     */
    for(auto it  = box1.rbegin() ; it != box1.rend() ; ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}


int main(int argc, char *argv[])
{
    /**
     * test1：
     * 手动创建 back_insert_iterator，
     * 将元素尾插到空 vector。
     *
     * test2：
     * 使用 back_inserter 简化尾插迭代器的创建。
     *
     * test3：
     * 手动创建 front_insert_iterator，
     * 将元素头插到 list。
     *
     * test4：
     * 使用 front_inserter 简化头插迭代器的创建。
     *
     * test5：
     * 使用 inserter 在指定位置插入元素。
     *
     * test6：
     * 演示 reverse_iterator 的基本移动方式。
     *
     * test7：
     * 使用反向迭代器倒序遍历 vector。
     */
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    test7();

    return 0;
}