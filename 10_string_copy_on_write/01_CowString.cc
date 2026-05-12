#include <iostream>
#include <ostream>
#include <pthread.h>
#include <string.h>

using std::cout;
using std::endl;
using std::ostream;

class CowString
{
public:
    // 默认构造函数：创建空字符串，并初始化引用计数
    CowString()
    : m_pStr(new char[4 + 0 + 1]{} + 4)
    {
        // 初始化引用计数为 1
        /* *(int*)(m_pStr - 4) = 1; */
        // 使用封装函数初始化引用计数
        initRefCount();
    }
    
    // 有参构造函数：根据传入的 C 风格字符串创建对象
    CowString(const char * pStr)
    : m_pStr(new char[4 + strlen(pStr) + 1]{} + 4) // 指针偏移 4 字节，指向实际字符数据区
    {
        // 初始化引用计数为 1
        /* *(int*)(m_pStr - 4) = 1; */
        initRefCount();
        // 拷贝字符串内容
        strcpy(m_pStr, pStr);
    }
    
    // 析构函数：释放当前对象持有的引用
    ~CowString()
    {
        // 引用计数减 1
        decrementRefCount();
        // 判断是否还有其他对象共享该空间
        // 引用计数为 0，说明没有对象再引用这块空间
        if(getRefCount() == 0){
            // 释放引用计数区和字符串数据区对应的整块堆空间
            delete [] (m_pStr - 4);
            cout << "release heap ===>" << endl;
        }
        // 当前对象不再持有该空间
        m_pStr = nullptr;
    }
    
    // 拷贝构造函数：浅拷贝底层指针，共享字符串空间
    CowString(const CowString & rhs)
    : m_pStr(rhs.m_pStr)  // 采用浅拷贝，共享底层字符串空间
    {
        // 引用计数加 1
        /* ++*(int*)(m_pStr - 4); */
        incrementRefCount();
    }

    // 输出运算符重载
    friend
    ostream & operator<<(ostream & os, const CowString & rhs);

    // 赋值运算符重载
    CowString & operator=(const CowString & rhs)
    {
        // 避免自赋值
        if(this != &rhs){
            // 引用计数减 1
            decrementRefCount();
            // 若原空间已无对象引用，则释放原空间
            if(getRefCount() == 0){
                // 释放原本持有的空间
                delete [] (m_pStr - 4);
                cout << "release heap ===>" << endl;
            }
            // 当前对象转而共享右操作数的字符串空间
            m_pStr = rhs.m_pStr;
            // 新空间引用计数加 1
            incrementRefCount();
        }
        // 返回当前对象本身，支持连续赋值
        return *this;
    }

/*
// 该版本 operator[] 未处理写时复制，不适合直接使用
    // 下标运算符重载
    char & operator[](int index)
    {
        if(index < 0 || index >= strlen(m_pStr)){
            cout << "index is illegal" << endl;
            // throw "index is illegal";
            static char nullChar = '\0';
            return nullChar;
        }else{
            return m_pStr[index];
        }   
    }
    // 仅通过下标读取 index 位置字符没有问题
    // 但在共享底层空间时，修改会影响其他 CowString 对象
*/
    

    // 下标运算符重载
    char & operator[](int index)
    {
        if(index < 0 || index >= strlen(m_pStr))
        {
            static char nullChar = '\0';
            return nullChar;
        }else{
            // 引用计数大于 1，说明当前字符串空间被多个对象共享
            if(getRefCount() > 1){
                // 原共享空间引用计数减 1
                decrementRefCount();
                // 为当前对象重新申请独立空间，并拷贝原字符串内容
                char *temp = new char[4 + strlen(m_pStr) + 1]{} + 4;
                strcpy(temp, m_pStr);
                // 底层指针改为指向新空间
                m_pStr = temp;
                // 新空间的引用计数初始化为 1
                initRefCount();
            }
            // 返回指定位置的字符引用
            return m_pStr[index];
        }
    }
    

    // 获取字符串长度
    int size()
    {
        return strlen(m_pStr);
    }
    
    // 返回 C 风格字符串
    char * c_str()
    {
        return m_pStr;
    }

    // 获取当前字符串空间的引用计数
    int getRefCount()
    {
        return *(int*)(m_pStr - 4);
    }


private:
    // 将引用计数相关操作封装为辅助函数，便于复用

    // 初始化引用计数
    void initRefCount()
    {
        *(int *)(m_pStr - 4) = 1;
    }
    
    // 引用计数加 1
    void incrementRefCount()
    {
        ++*(int*)(m_pStr - 4);
    }

    // 引用计数减 1
    void decrementRefCount()
    {

       --*(int*)(m_pStr - 4);
    }

    // 指向实际字符串数据区的指针
    char * m_pStr;
};

// 输出运算符重载
ostream & operator<<(ostream & os, const CowString & rhs)
{
    os << rhs.m_pStr;
    return os;
}

// 测试构造函数
void test1()
{
    CowString s1;
    CowString s2{"abc"};
    cout << s1 << endl;
    cout << s2 << endl;
}

// 测试拷贝构造函数
void test2()
{
    CowString s1{"abc"};

    cout << "s1 refCount:" << s1.getRefCount() << endl;
    cout << "--------" << endl;
    CowString s2 = s1; // 调用拷贝构造函数
    
    cout << s1 << endl;
    cout << s2 << endl;
    cout << "s1 refCount:" << s1.getRefCount() << endl;
    cout << "s2 refCount:" << s2.getRefCount() << endl;
}

// 测试析构函数
void test3()
{
    // 未共享底层空间的情况
    CowString s1{"abc"};
    cout << s1 << endl;
    cout << "------" << endl;
    // 共享底层空间的情况
    CowString s2{"hello"};
    CowString s3 = s2;
    cout << "s2:" << s2 << endl;
    cout << "s3:" << s3 << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "s3 count:" << s3.getRefCount() << endl;  
}

// 测试赋值运算符
void test4()
{
    CowString s1{"abc"};
    CowString s2 = s1;
    cout << "s1:" << s1 << endl;
    cout << "s2:" << s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;

    CowString s3{"bcd"};
    cout << "s3:" << s3 << endl;
    cout << "s3 count:" << s3.getRefCount() << endl;
    cout << "--------" << endl;
    s1 = s3;
    cout << "s1:" << s1 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "s3 count:" << s3.getRefCount() << endl;
    cout << "-----" << endl;

    s2 = s3;
    cout << "s2:" << s2 << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "s3 count:" << s3.getRefCount() << endl;
}

void test5()
{
    // 测试共享底层空间时，下标访问触发写时复制的行为
    CowString s1{"abc"};
    CowString s2 = s1;
    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "----------" << endl;
    cout << s1[0] << endl;
    /* s1[0] = 'A'; */
    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
}


int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    test5();

    return 0;
}