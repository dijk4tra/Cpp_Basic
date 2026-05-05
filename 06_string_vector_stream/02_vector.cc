#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/**
 * vector：顺序容器，可以存储任意类型的数据。
 * 既可以存储内置类型，也可以存储自定义类型。
 * 
 * 特点：支持自动扩容。
 *
 * 使用时需要指定元素类型：
 * vector<int> v;
 * vector<Point> v2;
 */

// vector 容器的构建
void test1()
{
    // 无参构造函数：创建空容器
    vector<int> box1;

    // 使用初始化列表构建容器
    vector<int> box2 {1, 2, 3};

    // 使用迭代器区间构建容器，区间为 [first, last)
    vector<int> box3 {box2.begin(), box2.end()};
    
    // 构建包含 count 个元素的容器
    vector<int> box4(3, 10); // ()：3 个 10
    vector<int> box5{3, 10}; // {}：元素为 3 和 10
    
    // 拷贝构造
    vector<int> box6 {box2};

    // 与上面的写法等价
    vector<int> box7 = box2;
}

// vector 的常用操作
void test2()
{
    vector<int> box;

    cout << box.empty() << endl;
    cout << box.size() << endl;
    cout << box.capacity() << endl;

    cout << "---------" << endl;

    vector<int> box2 {1, 2, 3};

    cout << box2.empty() << endl;
    cout << box2.size() << endl;
    cout << box2.capacity() << endl;

    cout << "---------" << endl;

    box2.push_back(4);

    cout << box2.empty() << endl;
    cout << box2.size() << endl;
    cout << box2.capacity() << endl;
}

// vector 遍历操作
void visitVector(vector<int> & box)
{
    // 使用增强 for 循环遍历
    for(auto & element : box){
        cout << element << " ";
    }

    cout << endl;
}

void visitVector2(vector<int> & box)
{
    // 使用普通 for 循环遍历
    for(int i = 0 ; i < box.size(); ++i){
        /* cout << box.at(i) << " "; */
        cout << box[i] << " ";
    }

    cout << endl;
}

void visitVector3(vector<int> & box)
{
    // 使用迭代器遍历
    auto it = box.begin();

    for(; it != box.end(); ++it){
        cout << *it << " ";
    }

    cout << endl;
}

void test3()
{
    vector<int> box {1, 2, 3, 4, 5};

    visitVector(box);

    box.push_back(6);
    box.push_back(7);
    visitVector(box);

    box.pop_back();
    visitVector(box);

    // clear：清除所有元素
    box.clear();
    visitVector(box);

    cout << "size: " << box.size() << endl;
    cout << "capacity: " << box.capacity() << endl;

    cout << "--------" << endl;

    // shrink_to_fit：回收多余容量
    box.push_back(1);
    box.shrink_to_fit();

    cout << "size: " << box.size() << endl;                              
    cout << "capacity: " << box.capacity() << endl;

    cout << "--------" << endl;

    vector<int> box2;

    // reserve：预留存储空间
    box2.reserve(5);

    cout << "size: " << box2.size() << endl;
    cout << "capacity: " << box2.capacity() << endl;
}

// 元素访问
void test4()
{
    vector<int> box{1, 2, 3, 4, 5};

    // at(index)：访问指定下标的元素
    cout << box.at(0) << endl;

    // operator[](n)：通过下标访问元素
    cout << box.operator[](1) << endl;

    // 与上面的写法等价
    cout << box[2] << endl;

    // 访问首元素和尾元素
    cout << box.front() << endl;
    cout << box.back() << endl;

    cout << "--------" << endl;

    // 通过迭代器访问元素
    /* vector<int>::iterator it = box.begin(); // 完整写法 */
    auto it = box.begin(); // 简写

    cout << *it << endl;

    ++it;

    cout << *it << endl;
}

// insert / erase：插入与删除操作
void test5()
{
    vector<int> box{1, 2, 3, 4, 5};

    visitVector(box);

    auto it = box.begin();
    ++it;

    box.insert(it, 10);
    visitVector(box);

    cout << "--------" << endl;

    auto it2 = box.end();
    --it2;
    --it2;

    box.erase(it2);
    visitVector(box);
}

// 针对自定义类型的处理
class Point
{
public:
    Point(int x, int y)
    :m_x(x)
    ,m_y(y)
    {
        cout << "Point(int, int)" << endl;
    }

    Point(const Point & rhs)
    :m_x(rhs.m_x)
    ,m_y(rhs.m_y)
    {
        cout << "Point(const Point & rhs)" << endl;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }

    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

private:
    int m_x;
    int m_y;
};

// 存储自定义类型对象
void test6()
{
    vector<Point> box;

    // 如果不提前预留存储空间，
    // 扩容时可能产生额外的拷贝和析构调用
    box.reserve(5);

    Point pt1{1, 2};
    Point pt2{3, 4};
    Point pt3{5, 6};

    box.push_back(pt1);
    box.push_back(pt2);
    box.push_back(pt3);

    box.at(0).print();
    box[1].print();

    cout << "--------" << endl;

    auto it = box.begin();

    // 通过迭代器访问对象成员
    (*it).print();
    it->print();
    
    // 也可以进行容器嵌套
    vector<vector<int>> box2;
}


int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    test6();

    return 0;
}