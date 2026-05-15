#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/**
 * vector: 顺序的数据容器,可以存储任意类型的数据
 * 可以是内置类型,也可以是自定义类型的
 * 
 * 特点: 自动扩容
 *
 * 使用时需要指明要存储的数据的类型
 * vector<int> v;
 * vector<Point> v2;
 *
 *
 * vector 容器：
 * vector 是 C++ 标准库中的顺序容器。
 *
 * 可以简单理解为：
 * vector 是一个可以自动扩容的动态数组。
 *
 * 和普通数组相比：
 * 1. 普通数组的大小通常是固定的。
 * 2. vector 可以根据元素数量自动申请更大的空间。
 * 3. vector 提供了很多成员函数，使用起来更加方便。
 *
 *
 * vector 的三个重要概念：
 * 1. size
 *    当前已经存放的元素个数。
 *
 * 2. capacity
 *    当前已经分配好的存储空间最多能放多少个元素。
 *
 * 3. 自动扩容
 *    当 size 达到 capacity 后，
 *    如果继续插入元素，
 *    vector 会重新申请一块更大的空间，
 *    然后把原来的元素搬到新空间中。
 *
 *
 * 注意：
 * vector 的底层存储空间是连续的。
 * 所以可以通过下标访问元素，
 * 也可以通过迭代器遍历元素。
 */

// vector容器的构建
void test1()
{
    /**
     * vector 的构造方式
     *
     * 构造容器时，
     * 需要指定 vector 中元素的类型。
     *
     * 例如：
     * vector<int> 表示这个容器中存放 int 类型的数据。
     */

    // 无参构造函数 空容器
    // box1 当前没有任何元素，size 为 0
    vector<int> box1;

    // 初始化列表方式构建容器
    // box2 中有 3 个元素：1、2、3
    vector<int> box2 {1,2,3};

    /**
     * 迭代器范围构造
     *
     * 使用一段迭代器区间中的元素来构造新的 vector。
     *
     * 区间形式：
     * [first, last)
     *
     * 左闭右开：
     * 包含 first 指向的元素，
     * 不包含 last 指向的元素。
     *
     * box2.begin() 指向第一个元素 1。
     * box2.end() 指向最后一个元素后面的位置。
     *
     * 所以 box3 会拷贝 box2 中的所有元素。
     */
    vector<int> box3 {box2.begin(), box2.end()};
    
    /**
     * vector<int> box4(3, 10);
     *
     * 使用小括号构造。
     *
     * 含义：
     * 创建 3 个元素，
     * 每个元素的值都是 10。
     *
     * 所以 box4 中的内容是：
     * 10 10 10
     */
    vector<int> box4(3,10); // ():3个10

    /**
     * vector<int> box5{3, 10};
     *
     * 使用大括号初始化列表。
     *
     * 含义：
     * 创建一个 vector，
     * 里面有两个元素：3 和 10。
     *
     * 所以 box5 中的内容是：
     * 3 10
     *
     * 注意：
     * 小括号和大括号在这里的含义不同。
     */
    vector<int> box5{3,10}; // {}:3和10
    
    /**
     * 拷贝构造
     *
     * 使用一个已经存在的 vector 对象，
     * 初始化一个新的 vector 对象。
     *
     * box6 是一个新容器，
     * 它的内容来自 box2。
     */
    vector<int> box6 {box2};

    // 上下二者等价
    // 这里也是用 box2 初始化新容器 box7
    vector<int> box7 = box2;
}

// vector的常用操作
void test2()
{
    vector<int> box;

    /**
     * empty()
     *
     * 作用：
     * 判断容器是否为空。
     *
     * 返回值：
     * true  表示容器为空
     * false 表示容器不为空
     *
     * cout 输出 bool 值时，
     * 默认 true 输出 1，
     * false 输出 0。
     */
    cout << box.empty() << endl;

    /**
     * size()
     *
     * 返回当前容器中元素的个数。
     *
     * box 是空容器，
     * 所以 size 为 0。
     */
    cout << box.size() << endl;

    /**
     * capacity()
     *
     * 返回当前容器已经分配的容量。
     *
     * 注意：
     * capacity 表示最多能放多少个元素，
     * 不是当前已经放了多少个元素。
     */
    cout << box.capacity() << endl;

    cout << "---------" << endl;

    vector<int> box2 {1,2,3};

    // box2 中有 3 个元素，所以 empty() 返回 false
    cout << box2.empty() << endl;

    // 当前元素个数为 3
    cout << box2.size() << endl;

    // 当前容量由具体实现决定，通常至少大于等于 size
    cout << box2.capacity() << endl;

    cout << "---------" << endl;

    /**
     * push_back()
     *
     * 作用：
     * 在 vector 的末尾插入一个新元素。
     *
     * 如果当前容量不够，
     * vector 会自动扩容。
     */
    box2.push_back(4);

    cout << box2.empty() << endl;
    cout << box2.size() << endl;
    cout << box2.capacity() << endl;
}

// vector遍历操作
void visitVector(vector<int> & box)
{
    /**
     * 函数参数写成 vector<int> & box
     *
     * 这是引用传递。
     *
     * 好处：
     * 1. 不会拷贝整个 vector，效率更高。
     * 2. box 是实参容器的别名。
     *
     * 如果函数内部只是读取元素，
     * 实际开发中更推荐写成：
     * const vector<int> & box
     */

    // 增强for遍历
    /**
     * 范围 for 循环
     *
     * 每次循环时，
     * element 会依次引用 box 中的每一个元素。
     *
     * auto & element：
     * auto 表示让编译器自动推导元素类型。
     * & 表示引用，避免复制元素。
     */
    for(auto & element : box){
        cout << element << " ";
    }
    cout << endl;
}

void visitVector2(vector<int> & box)
{
    /**
     * 通过下标遍历 vector。
     *
     * vector 底层是连续空间，
     * 所以可以像数组一样通过下标访问元素。
     *
     * 注意：
     * box.size() 的返回类型是无符号整数类型。
     * 学习阶段用 int 可以理解，
     * 实际开发中也可以写成：
     *
     * for(size_t i = 0; i < box.size(); ++i)
     */
    for(int i = 0 ; i < box.size(); ++i){
        /**
         * at(i) 和 operator[] 都可以访问元素。
         *
         * at(i) 会进行越界检查。
         * 如果下标越界，会抛出异常。
         *
         * operator[] 通常不会进行越界检查。
         * 如果下标越界，可能导致未定义行为。
         */
        /* cout << box.at(i) << " "; */
        cout << box[i] << " ";
    }
    cout << endl;
}

void visitVector3(vector<int> & box)
{
    /**
     * 使用迭代器遍历 vector。
     *
     * begin() 返回指向第一个元素的迭代器。
     * end() 返回指向最后一个元素后一个位置的迭代器。
     *
     * 注意：
     * end() 指向的位置不是有效元素，
     * 它只是遍历结束的标记。
     */
    auto it = box.begin();

    for(; it != box.end(); ++it){
        // 解引用迭代器，访问当前元素
        cout << *it << " ";
    }
    cout << endl;
}

void test3()
{
    vector<int> box {1,2,3,4,5};

    // 遍历当前容器中的所有元素
    visitVector(box);

    // 在末尾追加元素 6
    box.push_back(6);

    // 在末尾追加元素 7
    box.push_back(7);

    visitVector(box);

    /**
     * pop_back()
     *
     * 作用：
     * 删除 vector 末尾的一个元素。
     *
     * 注意：
     * pop_back() 只删除元素，
     * 不返回被删除的元素。
     */
    box.pop_back();

    visitVector(box);

    // clear清除元素
    /**
     * clear()
     *
     * 作用：
     * 清空容器中的所有元素。
     *
     * 注意：
     * clear() 会让 size 变成 0，
     * 但是通常不会释放已经申请好的容量。
     *
     * 也就是说：
     * 元素没了，
     * 但 capacity 可能还在。
     */
    box.clear();

    visitVector(box);

    cout << "size: " << box.size() << endl;
    cout << "capacity: " << box.capacity() << endl;

    cout << "--------" << endl;

    // 回收多余空间
    box.push_back(1);

    /**
     * shrink_to_fit()
     *
     * 作用：
     * 请求 vector 回收多余的容量。
     *
     * 例如：
     * 当前 size 为 1，
     * 但是 capacity 可能比 1 大很多。
     *
     * 调用 shrink_to_fit() 后，
     * vector 会尝试让 capacity 接近 size。
     *
     * 注意：
     * shrink_to_fit() 是一个请求，
     * 标准并不强制要求一定回收成功。
     */
    box.shrink_to_fit();

    cout << "size: " << box.size() << endl;                              
    cout << "capacity: " << box.capacity() << endl;

    cout << "--------" << endl;

    vector<int> box2;

    // 预留存储空间
    /**
     * reserve(n)
     *
     * 作用：
     * 提前为 vector 预留至少 n 个元素的存储空间。
     *
     * 注意：
     * reserve 只影响 capacity，
     * 不会创建元素，
     * 所以不会改变 size。
     *
     * 这里 reserve(5) 后：
     * size 仍然是 0，
     * capacity 至少是 5。
     *
     * 好处：
     * 如果提前知道大概要插入多少元素，
     * 可以先 reserve，
     * 减少自动扩容带来的开销。
     */
    box2.reserve(5);

    cout << "size: " << box2.size() << endl;
    cout << "capacity: " << box2.capacity() << endl;
}

// 元素访问
void test4()
{
    vector<int> box{1,2,3,4,5};

    // at(index)
    /**
     * at(index)
     *
     * 访问指定下标位置的元素。
     *
     * at() 会进行越界检查。
     * 如果 index 越界，会抛出异常。
     */
    cout << box.at(0) << endl;

    // operator[](n)下标访问
    /**
     * operator[](n)
     *
     * 通过下标访问元素。
     *
     * box.operator[](1)
     * 等价于：
     * box[1]
     *
     * 只是平时更常写 box[1]。
     */
    cout << box.operator[](1) << endl;

    // 上下二者等价
    cout << box[2] << endl;

    /**
     * front()
     *
     * 返回第一个元素。
     *
     * 当前 box 中第一个元素是 1。
     */
    cout << box.front() << endl;

    /**
     * back()
     *
     * 返回最后一个元素。
     *
     * 当前 box 中最后一个元素是 5。
     */
    cout << box.back() << endl;

    cout << "--------" << endl;

    // 通过迭代器访问
    /**
     * vector<int>::iterator 是完整写法。
     *
     * auto 可以让编译器自动推导 it 的类型，
     * 所以这里可以简写成 auto。
     */
    /* vector<int>::iterator it = box.begin(); //完整写法 */
    auto it = box.begin(); // 简写

    // it 当前指向第一个元素
    cout << *it << endl;

    // 迭代器向后移动一个位置
    ++it;

    // 此时 it 指向第二个元素
    cout << *it << endl;
}

// insert/erase, 插入/删除操作
void test5()
{
    vector<int> box{1,2,3,4,5};

    visitVector(box);

    auto it = box.begin();

    // it 向后移动一个位置，指向第二个元素 2
    ++it;

    /**
     * insert(pos, value)
     *
     * 作用：
     * 在迭代器 pos 指向的位置之前插入 value。
     *
     * 当前 it 指向元素 2，
     * 所以 box.insert(it, 10)
     * 会把 10 插入到 2 的前面。
     *
     * 插入后结果是：
     * 1 10 2 3 4 5
     *
     * 注意：
     * vector 插入元素时可能发生扩容。
     * 一旦扩容，原来的迭代器可能会失效。
     */
    box.insert(it, 10);

    visitVector(box);

    cout << "--------" << endl;

    auto it2 = box.end();

    /**
     * end() 指向最后一个元素后面的位置，
     * 它本身不是有效元素。
     *
     * 所以如果想访问最后一个元素，
     * 需要先 --it2。
     */
    --it2;

    // 再向前移动一次
    // 此时 it2 指向倒数第二个元素
    --it2;

    /**
     * erase(pos)
     *
     * 作用：
     * 删除迭代器 pos 指向的元素。
     *
     * 当前 it2 指向倒数第二个元素，
     * 所以这里删除倒数第二个元素。
     *
     * 注意：
     * 删除 vector 中间的元素后，
     * 后面的元素会整体向前移动。
     */
    box.erase(it2);

    visitVector(box);
}

// 针对自定义类型处理
class Point
{
public:
    /**
     * 有参构造函数
     *
     * 作用：
     * 创建 Point 对象时，
     * 使用传入的 x 和 y 初始化成员变量。
     *
     * 构造函数初始化列表：
     * :m_x(x)
     * ,m_y(y)
     *
     * 表示在对象创建时，
     * 直接初始化 m_x 和 m_y。
     */
    Point(int x, int y)
    :m_x(x)
    ,m_y(y)
    {
        cout << "Point(int, int)" << endl;
    }

    /**
     * 拷贝构造函数
     *
     * 作用：
     * 使用一个已经存在的 Point 对象，
     * 初始化一个新的 Point 对象。
     *
     * 参数：
     * const Point & rhs
     * rhs 表示被拷贝的那个对象。
     *
     * 当 vector<Point> 进行 push_back(pt1) 时，
     * vector 需要在自己的存储空间中创建一个 Point 对象，
     * 这个新对象通常会通过 pt1 拷贝构造出来。
     */
    Point(const Point & rhs)
    :m_x(rhs.m_x)
    ,m_y(rhs.m_y)
    {
        cout << "Point(const Point & rhs)" << endl;
    }

    /**
     * 析构函数
     *
     * 作用：
     * 当 Point 对象生命周期结束时自动调用。
     *
     * 例如：
     * 1. 局部对象离开作用域。
     * 2. vector 中的 Point 元素被销毁。
     * 3. vector 扩容时旧空间中的对象被释放。
     */
    ~Point()
    {
        cout << "~Point()" << endl;
    }

    // 普通成员函数
    // 输出当前 Point 对象的坐标
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

private:
    int m_x;
    int m_y;
};

// 存储自定义类型的对象
void test6()
{
    /**
     * vector 不仅可以存储内置类型，
     * 也可以存储自定义类型对象。
     *
     * 这里 vector<Point> 表示：
     * 容器中的每一个元素都是 Point 对象。
     */
    vector<Point> box;

    // 这里不预留存储空间,
    // 就会多三次析构函数调用
    /**
     * 为什么 reserve(5) 可以减少构造和析构次数？
     *
     * vector 会自动扩容。
     * 如果不提前预留空间，
     * push_back 多个对象时可能发生多次扩容。
     *
     * 每次扩容时，vector 通常会：
     * 1. 申请一块更大的新空间。
     * 2. 把旧空间中的元素拷贝或移动到新空间。
     * 3. 销毁旧空间中的元素。
     * 4. 释放旧空间。
     *
     * 对自定义类型来说，
     * 这个过程可能会额外调用拷贝构造函数和析构函数。
     *
     * reserve(5) 提前准备好容量，
     * 后面 push_back 3 个对象时通常不需要扩容，
     * 因此可以减少额外开销。
     */
    box.reserve(5);

    // 创建三个 Point 局部对象
    Point pt1{1,2};
    Point pt2{3,4};
    Point pt3{5,6};

    /**
     * push_back(pt1)
     *
     * 将 pt1 追加到 vector 的末尾。
     *
     * 注意：
     * vector 中保存的是一个新的 Point 对象，
     * 不是 pt1 本身。
     *
     * 所以这里通常会调用 Point 的拷贝构造函数，
     * 用 pt1 拷贝构造 vector 内部的元素。
     */
    box.push_back(pt1);
    box.push_back(pt2);
    box.push_back(pt3);

    // 通过 at() 访问第 0 个 Point 对象，然后调用 print()
    box.at(0).print();

    // 通过下标访问第 1 个 Point 对象，然后调用 print()
    box[1].print();

    cout << "--------" << endl;

    /**
     * 通过迭代器访问自定义类型对象。
     *
     * box.begin() 返回指向第一个 Point 元素的迭代器。
     */
    auto it = box.begin();

    /**
     * (*it).print()
     *
     * it 是迭代器，
     * *it 得到它指向的 Point 对象。
     *
     * 因为 . 的优先级比 * 高，
     * 所以需要写成 (*it).print()。
     */
    (*it).print();

    /**
     * it->print()
     *
     * 这是上面写法的简化形式。
     *
     * it->print()
     * 等价于：
     * (*it).print()
     */
    it->print();
    
    // 还可以进行容器嵌套
    /**
     * vector<vector<int>>
     *
     * 表示 vector 中存放的元素还是 vector<int>。
     *
     * 可以理解成二维数组。
     *
     * 例如：
     * vector<vector<int>> matrix;
     *
     * matrix 中的每一个元素，
     * 都是一个 vector<int>。
     */
    vector<vector<int>> box2;
}


int main(int argc, char *argv[])
{
    /**
     * main 函数是程序入口。
     *
     * 当前只有 test6() 没有被注释，
     * 所以程序运行时只会执行 test6()。
     *
     * 如果想测试其它函数，
     * 可以取消对应函数调用前面的注释。
     */

    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    test6();

    return 0;
}