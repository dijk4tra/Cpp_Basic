#include <iostream>
#include <set>
using namespace std;

// 普通函数模板：用于 int、double 等类型相加
template <typename T>
T add(T a, T b) {
    return a + b;
}

// 函数模板重载：用于 set<int> 集合融合
template <>
set<int> add(set<int> s1, set<int> s2) {
    set<int> result;

    // 把第一个集合中的元素放入结果集合
    for (typename set<int>::iterator it = s1.begin(); it != s1.end(); it++) {
        result.insert(*it);
    }

    // 把第二个集合中的元素放入结果集合
    for (typename set<int>::iterator it = s2.begin(); it != s2.end(); it++) {
        result.insert(*it);
    }

    return result;
}

// 输出 set 集合
template <typename T>
void printSet(set<T> s) {
    for (typename set<T>::iterator it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    // 1. 两个整数类型数据相加
    int a = 10;
    int b = 20;
    cout << "两个 int 相加：" << add(a, b) << endl;

    // 2. 两个 double 型数据相加
    double x = 1.5;
    double y = 2.8;
    cout << "两个 double 相加：" << add(x, y) << endl;

    // 3. 两个存放 int 型元素的 set 融合
    set<int> s1;
    set<int> s2;

    s1.insert(1);
    s1.insert(2);
    s1.insert(3);

    s2.insert(3);
    s2.insert(4);
    s2.insert(5);

    set<int> s3 = add(s1, s2);

    cout << "第一个 set：";
    printSet(s1);

    cout << "第二个 set：";
    printSet(s2);

    cout << "融合后的 set：";
    printSet(s3);

    return 0;
}