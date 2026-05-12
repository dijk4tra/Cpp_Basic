#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class CowString
{
public:
    class CharProxy
    {   
    public:
        CharProxy(CowString & self, int index)
        : m_self(self)
        , m_index(index)
        {}

        // 类型转换函数：CharProxy -> char
        // 支持读操作：char ch = s[0];
        operator char() const
        {
            if(m_index < 0 || m_index >= m_self.size())
            {
                cout << "index is illegal" << endl;
                return '\0'; 
            }
            return m_self.m_pStr[m_index];
        }
        
        // 赋值运算符
        // 支持写操作：s[0] = 'A';
        CharProxy & operator=(char ch)
        {
            if(m_index < 0 || m_index >= m_self.size())
            {
                cout << "index is illegal" << endl;
                return *this; 
            }

            // 写操作之前，检查是否需要写时复制
            if(m_self.getRefCount() > 1)
            {
                m_self.detach();
            }

            // 当前对象已经拥有独立空间，可以安全修改
            m_self.m_pStr[m_index] = ch;

            return *this;
        }

        // 支持赋值写法：s1[0] = s2[1];
        // s2[1] 返回的是 CharProxy，不是 char。
        // 所以这里需要把 rhs 转换成 char，再复用上面的 operator=(char)
        CharProxy & operator=(const CharProxy & rhs)
        {
            return *this = static_cast<char>(rhs);
        }

        // 声明为友元函数，方便 operator<< 访问 CharProxy 的私有成员
        friend ostream & operator<<(ostream & os, const CharProxy & rhs);

    private:
        CowString & m_self; // 当前代理对象属于哪个 CowString 对象
        int m_index; // 代理对象访问 CowString 对象的哪个字符
    };

public:
    // 默认无参构造函数
    CowString()
    : m_pStr(new char[4 + 1]() + 4)
    {
        initRefCount();
    }

    // 有参构造函数
    CowString(const char * pStr)
    : m_pStr(new char[4 + std::strlen(pStr) + 1]() + 4)
    {
        initRefCount();
        std::strcpy(m_pStr, pStr);
    }

    // 拷贝构造函数
    CowString(const CowString & rhs)
    : m_pStr(rhs.m_pStr)
    {
        incrementRefCount();
    }

    // 赋值运算符
    CowString & operator=(const CowString & rhs)
    {
        if(this != &rhs)
        {
            release();

            m_pStr = rhs.m_pStr;
            incrementRefCount();
        }

        return *this;
    }

    // 析构函数
    ~CowString()
    {
        release();
    }

    // 非 const 版本的 operator[]
    // 返回 CharProxy 对象，用于区分读操作和写操作
    CharProxy operator[](int index)
    {
        return CharProxy(*this, index);
    }

    // const 版本的 operator[]
    // const CowString 对象只能读，不能写
    // const 对象只能调用声明为 const 的成员函数，如果没有
    // 定义char operator[](int index) const，那么当尝试
    // 访问const CowString对象的operator[]时，就会报错，
    // 因为没有合适的函数可调用
    char operator[](int index) const
    {
        if(index < 0 || index >= size())
        {
            cout << "index is illegal" << endl;
            return '\0';
        }

        return m_pStr[index];
    }

    // 获取字符串长度
    int size() const
    {
        return std::strlen(m_pStr);
    }

    // 返回 C 风格字符串
    const char * c_str() const
    {
        return m_pStr;
    }

    // 获取引用计数
    int getRefCount() const
    {
        return *(int *)(m_pStr - 4);
    }

    friend ostream & operator<<(ostream & os, const CowString & rhs);

private:
    // 初始化引用计数为 1
    // 只有刚申请一块新空间时，才调用这个函数
    void initRefCount()
    {
        *(int *)(m_pStr - 4) = 1;
    }

    // 引用计数加 1
    // 当有新的 CowString 对象共享当前空间时调用
    void incrementRefCount()
    {
        ++*(int *)(m_pStr - 4);
    }
    
    // 引用计数减 1
    // 当某个 CowString 对象不再使用当前空间时调用
    void decrementRefCount()
    {
        --*(int *)(m_pStr - 4);
    }

    // 统一释放当前对象持有的字符串空间
    // 只有当前空间的引用计数减到 0，才真正释放内存
    void release()
    {
        if(m_pStr)
        {
            decrementRefCount();

            if(getRefCount() == 0)
            {
                delete [] (m_pStr - 4);
                cout << "release heap" << endl;
            }

            m_pStr = nullptr;
        }
    }

    // 脱离共享空间
    // 只有写操作，并且引用计数大于 1 时才调用
    void detach()
    {   
        // 保存旧空间地址 old
        char * old = m_pStr;

        // 原空间引用计数减 1
        decrementRefCount();

        // 申请新空间
        m_pStr = new char[4 + std::strlen(old) + 1]() + 4;

        // 初始化新空间引用计数
        initRefCount();

        // 拷贝字符串内容
        std::strcpy(m_pStr, old);
    }

private:
    // m_pStr 指向字符串内容区，不指向整块堆空间开头
    char * m_pStr;
    // 允许 CharProxy 访问 CowString 的私有成员
    friend class CharProxy;
};

// 输出 CowString 对象
// 例如: CowString s("abc");
//       cout << s << endl;
ostream & operator<<(ostream & os, const CowString & rhs)
{
    os << rhs.m_pStr;
    return os;
}

// 输出 CharProxy 对象
ostream & operator<<(ostream & os, const CowString::CharProxy & rhs)
{
    os << static_cast<char>(rhs);
    return os;
}

void test1()
{
    cout << "---------- 创建 s1 ----------" << endl;
    CowString s1("abc");

    cout << "s1 = " << s1 << endl;
    cout << "s1 refCount = " << s1.getRefCount() << endl;

    cout << endl;
    cout << "---------- 拷贝构造 s2 ----------" << endl;
    CowString s2 = s1;

    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s1 refCount = " << s1.getRefCount() << endl;
    cout << "s2 refCount = " << s2.getRefCount() << endl;

    cout << endl;
    cout << "---------- 读操作：cout << s1[0] ----------" << endl;
    cout << "s1[0] = " << s1[0] << endl;

    /*
        读操作不会触发写时复制，
        所以 s1 和 s2 仍然共享同一块空间，
        引用计数仍然是 2。
    */
    cout << "s1 refCount = " << s1.getRefCount() << endl;
    cout << "s2 refCount = " << s2.getRefCount() << endl;

    cout << endl;
    cout << "---------- 写操作：s1[0] = 'A' ----------" << endl;
    s1[0] = 'A';

    /*
        写操作会触发 detach。

        修改后：
            s1 独立拥有 "Abc"
            s2 仍然拥有 "abc"

        两边引用计数都应该是 1。
    */
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s1 refCount = " << s1.getRefCount() << endl;
    cout << "s2 refCount = " << s2.getRefCount() << endl;

    cout << endl;
    cout << "---------- 支持 char ch = s2[1] ----------" << endl;
    char ch = s2[1];
    cout << "ch = " << ch << endl;

    cout << endl;
    cout << "---------- 支持 s1[1] = s2[2] ----------" << endl;
    s1[1] = s2[2];
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
}

int main()
{
    test1();
    return 0;
}