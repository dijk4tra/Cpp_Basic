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
    // operator[]
    cout << str[1] << endl;
    // 通过迭代器访问
    auto it = str.begin();
    it += 2;
    cout << *it << endl;

    // 容量
    cout << str.size() << endl;
    cout << str.empty() << endl;
    cout << str.c_str() << endl;
}

// 插入insert
void test2()
{   
    // insert : 插入string对象,C风格字符串....
    string str {"hello"};
    cout << str << endl;
    string str2 {"abc"};
    str.insert(1, str2);
    cout << str << endl;
    str.insert(1, "xyz");
    cout << str << endl;
    cout << "--------" << endl;
    
    // push_back: 末尾追加字符
    str2.push_back('A');
    cout << str2 << endl;
    string str3 {"bbb"};
    str2.append(str3);
    cout << str2 << endl;
    str2.append(str.begin(), str.end());
    cout << str2 << endl;
}

// 删除erase
void test3()
{
    string str {"abcdef"};
    auto it = str.begin();
    it += 2;
    // 删除迭代器位置的字符
    auto it2 = str.erase(it);
    cout << str << endl;
    cout << *it2 << endl;
    cout << "--------" << endl;
    // 删除迭代器范围的元素
    auto it3 = str.begin();
    it3 += 2;
    str.erase(it3, str.end());
    cout << str << endl;
}

// 字符串的拼接
void test4()
{
    string str {"abc"};
    string str2 {"abc"};
    // +
    string str3 = str + str2;
    cout << str3 << endl;

    string str4 = str + "xyz";
    cout << str4 << endl;

    string str5 = str + "A";
    cout << str5 << endl;
}

// 字符串的截取
void test5()
{
    string str {"abcdef"};
    // substr(区间) [a,b) 左闭右开
    string str2 = str.substr(0,3);
    cout << str2 << endl;
    
    // 从某个位置到末尾进行截取
    string str3 = str.substr(2);
    cout << str3 << endl; 
    
}

// 字符串的查找
void test6()
{
    string str {"abcdef"};
    int index = str.find("de");
    if(index < 0){
        cout << "not found" << endl;
    }else{
        cout << "index: " << index << endl;
    }
}

// 字符串的遍历
void test7()
{
    string str = "abc";
    // for i 循环
    for(int i = 0; i < str.size(); i++){
        /* cout << str[i] << endl; */
        cout << str.at(i) <<endl;
    }
    cout << "---------" << endl;
    // foreach增强for循环
    /* for(char & ch : str){ */
    for(char & ch : str){
        cout << ch << endl;
    }
    cout << "---------" << endl;
    // 迭代器遍历
    auto itBegin = str.begin();
    for( ; itBegin != str.end(); ++itBegin){
        cout << *itBegin << endl;
    }
    // 或者使用while循环,条件为 it != end()
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