#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class CowString
{
    // 定义内部类 CharProxy，用于帮助 CowString 区分读操作和写操作
    class CharProxy
    {
    public:
        CharProxy(CowString& cow, int index)
        : m_self(cow)
        , m_index(index)
        {

        }

        // operator<<
        // cout << s[0]; 先对 CowString 对象调用 operator[]
        // 返回 CharProxy 对象，再通过 m_self 访问底层字符数据
        friend
        ostream & operator<<(ostream & os, const CharProxy & rhs);

        // operator=
        // s[0] = 'A'; 先对 CowString 对象调用 operator[]
        // 返回 CharProxy 对象，再通过代理对象修改 m_self.m_pStr[m_index]
        char & operator=(const char & ch)
        {
            if(m_index < 0 || m_index >= strlen(m_self.m_pStr))
            {
                static char nullChar = '\0';
                return nullChar;
            }else{
                // 获取引用计数，判断当前空间是否被共享
                // 引用计数大于 1，说明有多个对象共享同一块空间
                if(m_self.getRefCount() > 1){
                    // 原共享空间的引用计数减 1
                    m_self.decrementRefCount();

                    // 为当前对象重新申请独立空间，并拷贝原字符串内容
                    char * temp = new char[4 + strlen(m_self.m_pStr) + 1]{} + 4;
                    strcpy(temp, m_self.m_pStr);

                    // 修改底层指针，使其指向新空间
                    m_self.m_pStr = temp;

                    // 新空间的引用计数初始化为 1
                    m_self.initRefCount();
                }

                // 修改指定位置的字符
                m_self.m_pStr[m_index] = ch;

                // 返回修改后的字符引用
                return m_self.m_pStr[m_index];
        }

        }
    private:
        CowString & m_self; // 记录当前 CowString 对象
        int m_index;        // 记录访问的字符下标
    };
public:
    // 默认构造函数
    CowString()
    : m_pStr(new char[4 + 1]{} + 4)
    {
        // 初始化引用计数器为 1
       /* *(int*)(m_pStr - 4) = 1; */
        // 使用封装函数完成引用计数初始化
        initRefCount();
    }

    // 有参构造函数
    CowString(const char * pStr)
    : m_pStr(new char[4 + strlen(pStr) + 1]{} + 4) // 让底层指针指向字符数据区
    {
        // 初始化引用计数器为 1
       /* *(int*)(m_pStr - 4) = 1; */
        initRefCount();

       // 拷贝字符串数据
       strcpy(m_pStr, pStr);
    }

    // 析构函数
    ~CowString()
    {
        // 引用计数减 1
        decrementRefCount();

        // 判断引用计数是否为 0
        // 若为 0，说明没有 CowString 对象再引用这块空间
        if(getRefCount() == 0){
            // 释放引用计数区和字符数据区对应的整块堆空间
            delete [] (m_pStr - 4);
            cout << "release heap====>" << endl;
        }

        // 若引用计数不为 0，则不释放空间，仅将当前对象指针置空
        m_pStr = nullptr;

    }

    // 拷贝构造函数
    CowString(const CowString & rhs)
    : m_pStr(rhs.m_pStr) // 由深拷贝改为浅拷贝，共享底层空间
    {
        // 引用计数加 1
        /* ++*(int*)(m_pStr - 4); */
        incrementRefCount();
    }

    // operator<<
    friend
    ostream & operator<<(ostream & os, const CowString & rhs);

    // operator=
    CowString & operator=(const CowString & rhs)
    {
        // 自赋值判断
        if(this != &rhs){
            // 原空间引用计数减 1
            decrementRefCount();

            // 判断原空间是否还被其他对象引用
            if(getRefCount() == 0){
                // 若引用计数为 0，则释放原本持有的空间
                delete [] (m_pStr - 4);
                cout << "release heap=====>" << endl;
            }

            // 当前对象转而共享 rhs 的字符串空间
            m_pStr = rhs.m_pStr;

            // 新空间引用计数加 1
            incrementRefCount();
        }

        // 返回当前对象本身，支持连续赋值
        return  *this;
    }

# if 0
    // operator[]
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
    // 通过下标访问 index 位置的字符没有问题
    // 但在底层空间共享时，修改字符会影响其他 CowString 对象
#endif

#if 0
    // operator[]
    char & operator[](int index)
    {
        if(index < 0 || index >= strlen(m_pStr))
        {
            static char nullChar = '\0';
            return nullChar;
        }else{
            // 获取引用计数，判断当前空间是否被共享
            // 引用计数大于 1，说明有多个对象共享同一块空间
            if(getRefCount() > 1){
                // 原共享空间引用计数减 1
                decrementRefCount();

                // 为当前对象重新申请独立空间，并拷贝原字符串内容
                char * temp = new char[4 + strlen(m_pStr) + 1]{} + 4;
                strcpy(temp, m_pStr);

                // 修改底层指针，使其指向新空间
                m_pStr = temp;

                // 新空间的引用计数初始化为 1
                initRefCount();
            }
            
            // 返回指定位置的字符引用
            return m_pStr[index];
        }
    }
    // 该版本无法区分读操作和写操作
#endif

    // operator[]
    CharProxy operator[](int index)
    {
        return CharProxy{*this, index};
    };


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

    // 初始化引用计数器
    void initRefCount()
    {
       *(int*)(m_pStr - 4) = 1;
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

    // 指向实际字符数据区的指针
    char * m_pStr;

    friend
    ostream & operator<<(ostream & os, const CowString::CharProxy & rhs);
};

// CowString 的 operator<<
ostream & operator<<(ostream & os, const CowString & rhs)
{

    os << rhs.m_pStr;
    return os;
}

// CharProxy 的 operator<<
ostream & operator<<(ostream & os, const CowString::CharProxy & rhs)
{

    os << rhs.m_self.m_pStr[rhs.m_index];
    return os;
}

void test1()
{
    // 底层数组空间未共享时，读写都没有问题
    // 发生共享后，写操作需要触发写时复制
    CowString s1{"abc"};
    CowString s2 = s1;
    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "----------" << endl;
    cout << s1[0] << endl;
    s1[0] = 'A';
    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;

}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}