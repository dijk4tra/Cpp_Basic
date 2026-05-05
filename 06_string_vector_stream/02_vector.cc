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
 */

// vector容器的构建
void test1()
{
    // 无参构造函数 空容器
    vector<int> box1;

    // 初始化列表方式构建容器
    vector<int> box2 {1,2,3};

    // 迭代器范围构建 [first, last)
    vector<int> box3 {box2.begin(), box2.end()};
    
    // count个元素
    vector<int> box4(3,10); // ():3个10
    vector<int> box5{3,10}; // {}:3和10
    
    // 拷贝构造
    vector<int> box6 {box2};
    // 上下二者等价
    vector<int> box7 = box2;
}

// vector的常用操作
void test2()
{
    vector<int> box;
    cout << box.empty() << endl;
    cout << box.size() << endl;
    cout << box.capacity() << endl;
    cout << "---------" << endl;
    vector<int> box2 {1,2,3};
    cout << box2.empty() << endl;
    cout << box2.size() << endl;
    cout << box2.capacity() << endl;
    cout << "---------" << endl;
    box2.push_back(4);
    cout << box2.empty() << endl;
    cout << box2.size() << endl;
    cout << box2.capacity() << endl;

}

// vector遍历操作
void visitVector(vector<int> & box)
{
    // 增强for遍历
    for(auto & element : box){
        cout << element << " ";
    }
    cout << endl;
}

void visitVector2(vector<int> & box)
{
    for(int i = 0 ; i < box.size(); ++i){
        /* cout << box.at(i) << " "; */
        cout << box[i] << " ";
    }
    cout << endl;
}

void visitVector3(vector<int> & box)
{
    auto it = box.begin();
    for(; it != box.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}

void test3()
{
    vector<int> box {1,2,3,4,5};
    visitVector(box);
    box.push_back(6);
    box.push_back(7);
    visitVector(box);
    box.pop_back();
    visitVector(box);
    // clear清除元素
    box.clear();
    visitVector(box);
    cout << "size: " << box.size() << endl;
    cout << "capacity: " << box.capacity() << endl;
    cout << "--------" << endl;
    // 回收多余空间
    box.push_back(1);
    box.shrink_to_fit();
    cout << "size: " << box.size() << endl;                              
    cout << "capacity: " << box.capacity() << endl;
    cout << "--------" << endl;
    vector<int> box2;
    // 预留存储空间
    box2.reserve(5);
    cout << "size: " << box2.size() << endl;
    cout << "capacity: " << box2.capacity() << endl;
}

// 元素访问
void test4()
{
    vector<int> box{1,2,3,4,5};
    // at(index)
    cout << box.at(0) << endl;
    // operator[](n)下标访问
    cout << box.operator[](1) << endl;
    // 上下二者等价
    cout << box[2] << endl;
    cout << box.front() << endl;
    cout << box.back() << endl;
    cout << "--------" << endl;
    // 通过迭代器访问
    /* vector<int>::iterator it = box.begin(); //完整写法 */
    auto it = box.begin(); // 简写
    cout << *it << endl;
    ++it;
    cout << *it << endl;
}

// insert/erase, 插入/删除操作
void test5()
{
    vector<int> box{1,2,3,4,5};
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

// 针对自定义类型处理
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

// 存储自定义类型的对象
void test6()
{
    vector<Point> box;
    // 这里不预留存储空间,
    // 就会多三次析构函数调用
    box.reserve(5);
    Point pt1{1,2};
    Point pt2{3,4};
    Point pt3{5,6};
    box.push_back(pt1);
    box.push_back(pt2);
    box.push_back(pt3);
    box.at(0).print();
    box[1].print();
    cout << "--------" << endl;
    auto it = box.begin();
    (*it).print();
    it->print();
    
    // 还可以进行容器嵌套
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

