#include <iostream>
#include <string>
#include <utility>
#include <map>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;

void visitMap(map<int,string> & m)
{
    for(auto & p : m)
    {
        cout << p.first << " = " << p.second << endl;
    }
    cout << endl;
}

void visitMap2(map<int,string> & m)
{
    auto it = m.begin();
    for(; it != m.end(); ++it)
    {
        cout << it->first << " = " << it->second << endl;
    }
    cout << endl;
}


void test1()
{   
    // 通过初始化列表构造一个map容器
    map<int,string> m1{
        pair<int,string>{1,"ywj"},
        pair<int,string>{2,"wzk"},
        pair<int,string>{3,"hhl"}
    };

    cout << "key 1: " << m1[1] << endl;
    
    cout << "---------" << endl;
    
    cout << "old key 2: " << m1[2] << endl;
    m1[2] = "lzw";
    cout << "new key 2: " << m1[2] << endl;

    cout << "---------" << endl;
    
    m1[4];
    visitMap(m1);
}


void test2()
{
    map<string,int> m2{
        {"zs",21},
        {"ls",22},
        {"ss",23}
    };
    
    auto it = m2.find("zs");
    if(it != m2.end()){
        cout << "find success!" << endl;
        cout << it->first << "'s age is " << it->second << endl;
    }
    
    cout << "---------" << endl;

    cout << "old ls's age: " << m2["ls"] << endl;
    m2["ls"] = 33;
    cout << "new ls's age: " << m2["ls"] << endl;
    
    cout << "---------" << endl;

    m2["ww"] = 44;
    auto it2 = m2.begin();
    for(; it2 != m2.end(); ++it2)
    {
        cout << it2->first << "'s age is " << it2->second << endl;
    }
}


int main(int argc, char *argv[])
{
    /* test1(); */
    test2();

    return 0;
}

