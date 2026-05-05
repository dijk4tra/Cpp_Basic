#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// 常见的字符串操作
void test1()
{
    string str {"abcdef"};

    // 元素访问
    cout << str.at(0) << endl;

    // 使用 operator[] 访问元素
    cout << str[1] << endl;

    // 通过迭代器访问元素
    auto it = str.begin();
    it += 2;
    cout << *it << endl;

    // 容量相关操作
    cout << str.size() << endl;
    cout << str.empty() << endl;

    // 获取 C 风格字符串
    cout << str.c_str() << endl;
}

// 字符串插入
void test2()
{   
    // insert：可以插入 string 对象、C 风格字符串等
    string str {"hello"};
    cout << str << endl;

    string str2 {"abc"};

    str.insert(1, str2);
    cout << str << endl;

    str.insert(1, "xyz");
    cout << str << endl;

    cout << "--------" << endl;
    
    // push_back：在字符串末尾追加单个字符
    str2.push_back('A');
    cout << str2 << endl;

    string str3 {"bbb"};

    // append：在字符串末尾追加另一个字符串
    str2.append(str3);
    cout << str2 << endl;

    // append：在字符串末尾追加指定迭代器区间内的字符
    str2.append(str.begin(), str.end());
    cout << str2 << endl;
}

// 字符串删除
void test3()
{
    string str {"abcdef"};

    auto it = str.begin();
    it += 2;

    // 删除指定迭代器位置上的字符，并返回被删除位置之后的迭代器
    auto it2 = str.erase(it);
    cout << str << endl;
    cout << *it2 << endl;

    cout << "--------" << endl;

    // 删除指定迭代器区间内的元素
    auto it3 = str.begin();
    it3 += 2;

    str.erase(it3, str.end());
    cout << str << endl;
}

// 字符串拼接
void test4()
{
    string str {"abc"};
    string str2 {"abc"};

    // 使用 + 进行字符串拼接
    string str3 = str + str2;
    cout << str3 << endl;

    string str4 = str + "xyz";
    cout << str4 << endl;

    string str5 = str + "A";
    cout << str5 << endl;
}

// 字符串截取
void test5()
{
    string str {"abcdef"};

    // substr(pos, count)：从 pos 位置开始，截取 count 个字符
    string str2 = str.substr(0, 3);
    cout << str2 << endl;
    
    // substr(pos)：从 pos 位置开始，截取到字符串末尾
    string str3 = str.substr(2);
    cout << str3 << endl; 
}

// 字符串查找
void test6()
{
    string str {"abcdef"};

    // find：查找子串首次出现的位置
    int index = str.find("de");

    if(index < 0){
        cout << "not found" << endl;
    }else{
        cout << "index: " << index << endl;
    }
}

// 字符串遍历
void test7()
{
    string str = "abc";

    // 使用普通 for 循环遍历
    for(int i = 0; i < str.size(); i++){
        /* cout << str[i] << endl; */
        cout << str.at(i) << endl;
    }

    cout << "---------" << endl;

    // 使用增强 for 循环遍历
    /* for(char & ch : str){ */
    for(char & ch : str){
        cout << ch << endl;
    }

    cout << "---------" << endl;

    // 使用迭代器遍历
    auto itBegin = str.begin();

    for( ; itBegin != str.end(); ++itBegin){
        cout << *itBegin << endl;
    }

    // 也可以使用 while 循环，条件为 it != end()
}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    /* test6(); */
    test7();

    return 0;
}