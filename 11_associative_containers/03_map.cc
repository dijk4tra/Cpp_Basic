#include <iostream>
#include <map>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;

/**
 * map 的使用场景：
 * 一般适合用于数据统计、分类存储等场景
 *
 * 举例 1：
 * 统计班级中不同省份的同学人数
 *
 * 河南：3
 * 湖北：5
 *
 * key：省份
 * value：人数
 *
 * 可以使用：
 * map<string, int>
 *
 * 举例 2：
 * 统计班级中不同省份的同学分别是谁
 *
 * key：省份
 * value：该省份的学生姓名集合
 *
 * 可以使用：
 * map<string, vector<string>>
 *
 * 如果学生信息比较复杂，也可以将 value 设置为自定义类型集合：
 *
 * key：省份
 * value：该省份的学生对象集合
 *
 * 可以使用：
 * map<string, vector<Student>>
 */

void visitMap(map<string,int> &m)
{
    for(auto & p : m){
        // p.first 表示 key，p.second 表示 value
        cout << p.first << " = " << p.second << endl;
    }
}

// map 的 operator[] 操作
void test1()
{
    map<string,int> m;

    // 使用 insert 插入键值对
    m.insert({"one", 1});
    m.insert({"two", 2});
    m.insert({"three", 3});
    m.insert({"four", 4});

    visitMap(m);

    cout << "---------" << endl;

    // 也可以通过 operator[] 添加或修改元素
    // 如果 key 已存在，则修改对应的 value
    m["two"] = 20;

    // 如果 key 不存在，则插入新的键值对
    m["five"] = 5;

    visitMap(m);
}

// erase 删除元素
void test2()
{
    map<string,int> m;

    // 插入键值对
    m.insert({"one", 1});
    m.insert({"two", 2});
    m.insert({"three", 3});
    m.insert({"four", 4});

    visitMap(m);

    cout << "---------" << endl;

    // 获取 begin() 位置的迭代器
    auto it = m.begin();

    // 将迭代器向后移动一个位置
    ++it;

    // 按迭代器位置删除元素
    m.erase(it);

    visitMap(m);
}

int main(int argc, char *argv[])
{
    /* test1(); */
    test2();

    return 0;
}