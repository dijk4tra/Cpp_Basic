#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

/*
    CowString：采用 COW 技术的自定义字符串类

    COW：Copy On Write，写时复制。

    核心思想：
        1. 拷贝构造、赋值时，不马上深拷贝字符串内容。
        2. 多个 CowString 对象可以先共享同一块字符串空间。
        3. 只有当某个对象要修改字符串内容时，才真正拷贝一份独立空间。
        4. 通过引用计数判断当前字符串空间被多少个对象共享。

    本类的内存布局：

        假设保存字符串 "abc"，实际申请的堆空间如下：

        低地址                                      高地址
        +----------------+--------------------------+
        | 引用计数 int   | 字符串内容 'a''b''c''\0' |
        +----------------+--------------------------+
        ^                ^
        |                |
        m_pStr - 4       m_pStr

    注意：
        m_pStr 并不指向整块空间的起始位置，
        而是指向字符串内容的起始位置。

        引用计数存放在 m_pStr 前面的 4 个字节中。
*/
class CowString
{
public:
    /*
        CharProxy：字符代理类

        为什么需要 CharProxy？

        如果 operator[] 直接返回 char&：

            char & operator[](int index);

        那么下面两种代码：

            cout << s[0];    // 读操作
            s[0] = 'A';      // 写操作

        都会先调用 operator[]。

        问题是：
            operator[] 函数内部无法知道调用者接下来到底是读还是写。

        如果在 operator[] 里面直接做写时复制，
        那么读操作 cout << s[0] 也可能触发深拷贝，
        这就违背了 COW “读不复制，写才复制” 的思想。

        所以这里让 operator[] 返回一个 CharProxy 对象。

        当发生读操作时：
            CharProxy 会被转换成 char。

        当发生写操作时：
            会调用 CharProxy::operator=(char)。

        这样就能区分读操作和写操作。
    */
    class CharProxy
    {   
    public:
        /*
            CharProxy 构造函数

            参数说明：
                self  ：当前代理对象属于哪个 CowString 对象
                index ：当前代理对象代表 CowString 中的哪个字符

            例如：

                CowString s("abc");
                s[1];

            s[1] 会返回一个 CharProxy 对象，
            该对象内部保存：

                m_self  -> s
                m_index -> 1

            也就是说，这个 CharProxy 代表 s 中下标为 1 的字符。
        */
        CharProxy(CowString & self, int index)
        : m_self(self)
        , m_index(index)
        {}

        /*
            类型转换函数：CharProxy -> char

            作用：
                用于支持读操作。

            例如：

                CowString s("abc");
                char ch = s[0];

            执行过程：

                1. s[0] 调用 CowString::operator[](0)
                2. operator[] 返回 CharProxy(s, 0)
                3. char ch = CharProxy对象
                4. 编译器需要把 CharProxy 转成 char
                5. 自动调用 operator char() const

            读操作只需要返回字符内容，
            不应该触发写时复制。
        */
        operator char() const
        {
            /*
                下标合法性检查。

                如果 index 小于 0，或者 index 大于等于字符串长度，
                就说明访问越界。
            */
            if(m_index < 0 || m_index >= m_self.size())
            {
                cout << "index is illegal" << endl;

                /*
                    返回 '\0' 表示空字符。

                    这里不能抛出异常的话，
                    就用 '\0' 作为一个安全返回值。
                */
                return '\0'; 
            }

            /*
                直接返回对应位置的字符。

                注意：
                    这里只是读字符，不会修改字符串，
                    所以不需要调用 detach()。
            */
            return m_self.m_pStr[m_index];
        }
        
        /*
            赋值运算符：CharProxy = char

            作用：
                用于支持写操作。

            例如：

                CowString s1("abc");
                CowString s2 = s1;

                s1[0] = 'A';

            执行过程：

                1. s1[0] 调用 CowString::operator[](0)
                2. 返回 CharProxy(s1, 0)
                3. CharProxy 对象调用 operator=('A')
                4. 在 operator= 中判断是否需要写时复制
                5. 如果引用计数大于 1，就调用 detach()
                6. 修改当前对象自己的字符串空间
        */
        CharProxy & operator=(char ch)
        {
            /*
                写操作之前，也要先检查下标是否合法。

                如果下标非法，不能写入，
                直接返回当前代理对象。
            */
            if(m_index < 0 || m_index >= m_self.size())
            {
                cout << "index is illegal" << endl;
                return *this; 
            }

            /*
                写操作之前，检查当前字符串空间是否被共享。

                getRefCount() > 1 说明：
                    当前字符串空间至少被两个 CowString 对象共享。

                例如：

                    CowString s1("abc");
                    CowString s2 = s1;

                此时 s1 和 s2 共享同一块空间，引用计数为 2。

                如果这时直接执行：

                    s1[0] = 'A';

                但不做 detach()，
                那么 s2 的内容也会被改成 "Abc"，
                这显然是不正确的。

                所以写之前必须先让 s1 脱离共享空间。
            */
            if(m_self.getRefCount() > 1)
            {
                /*
                    detach() 会为当前对象申请一块新空间，
                    并把旧字符串内容拷贝过去。

                    执行完 detach() 之后，
                    当前 CowString 对象就独占自己的字符串空间。
                */
                m_self.detach();
            }

            /*
                到这里有两种情况：

                情况一：
                    原本引用计数就是 1，
                    说明当前对象本来就独占字符串空间，
                    可以直接修改。

                情况二：
                    原本引用计数大于 1，
                    已经通过 detach() 拷贝出了一份新空间，
                    当前对象现在也可以安全修改。

                所以这里可以直接写入字符。
            */
            m_self.m_pStr[m_index] = ch;

            /*
                返回当前代理对象本身。

                赋值运算符通常返回左操作数的引用，
                这样更符合 C++ 运算符重载习惯。
            */
            return *this;
        }

        /*
            赋值运算符：CharProxy = CharProxy

            作用：
                支持这种写法：

                    s1[0] = s2[1];

            注意：
                s1[0] 返回的是 CharProxy。
                s2[1] 返回的也是 CharProxy。

            如果没有这个重载，
            CharProxy 对象之间直接赋值可能不符合我们的 COW 逻辑。

            这里的处理方式是：

                1. 先把右边 rhs 转换成 char
                2. 再调用已有的 operator=(char)

            这样可以复用写操作逻辑，
            避免重复写 COW 判断代码。
        */
        CharProxy & operator=(const CharProxy & rhs)
        {
            /*
                static_cast<char>(rhs) 会调用 rhs.operator char()。

                也就是说，右边的 s2[1] 是一次读操作，
                不会触发写时复制。

                然后 *this = 某个字符，
                会调用 operator=(char)，
                左边的 s1[0] 才是写操作。
            */
            return *this = static_cast<char>(rhs);
        }

        /*
            声明输出运算符为友元函数。

            这样 operator<< 可以访问 CharProxy 的私有成员。

            不过在你当前的实现中，
            operator<< 内部是通过 static_cast<char>(rhs) 读取字符，
            并没有直接访问 m_self 和 m_index。

            但保留 friend 也没有问题。
        */
        friend ostream & operator<<(ostream & os, const CharProxy & rhs);

    private:
        /*
            当前代理对象属于哪个 CowString 对象。

            使用引用的原因：
                CharProxy 不应该复制一个 CowString，
                它只是代理访问某个已有 CowString 对象中的字符。
        */
        CowString & m_self;

        /*
            当前代理对象访问 CowString 对象中的哪个字符。
        */
        int m_index;
    };

public:
    /*
        默认无参构造函数

        作用：
            创建一个空字符串对象。

        空字符串也需要堆空间，
        因为我们需要保存：
            1. 引用计数
            2. 字符串结束符 '\0'

        new char[4 + 1]()

            4：用于保存引用计数
            1：用于保存 '\0'

        后面的 () 表示对申请的空间进行值初始化，
        char 数组会被初始化为 0，
        所以字符串区域默认就是 '\0'。
    */
    CowString()
    : m_pStr(new char[4 + 1]() + 4)
    {
        /*
            新申请的空间只有当前对象使用，
            所以引用计数初始化为 1。
        */
        initRefCount();
    }

    /*
        有参构造函数

        作用：
            使用 C 风格字符串初始化 CowString。

        例如：

            CowString s("abc");

        申请空间大小：

            4 + strlen("abc") + 1

        其中：
            4                ：保存引用计数
            strlen("abc")    ：保存字符 'a' 'b' 'c'
            1                ：保存字符串结束符 '\0'
    */
    CowString(const char * pStr)
    : m_pStr(new char[4 + std::strlen(pStr) + 1]() + 4)
    {
        /*
            新申请的空间只有当前对象使用，
            所以引用计数为 1。
        */
        initRefCount();

        /*
            把传入的字符串内容拷贝到 m_pStr 指向的字符串区域。

            注意：
                m_pStr 指向的是字符串内容区，
                不是整块空间的起始地址。
        */
        std::strcpy(m_pStr, pStr);
    }

    /*
        拷贝构造函数

        作用：
            用一个已有 CowString 对象创建新对象。

        例如：

            CowString s1("abc");
            CowString s2 = s1;

        COW 的关键点：
            这里不做深拷贝。

        不深拷贝意味着：
            不重新申请空间；
            不重新复制字符串内容。

        而是让 s2 和 s1 共享同一块字符串空间。

        所以这里只需要：
            1. 让 m_pStr 指向 rhs.m_pStr
            2. 引用计数加 1
    */
    CowString(const CowString & rhs)
    : m_pStr(rhs.m_pStr)
    {
        /*
            多了一个 CowString 对象共享这块空间，
            所以引用计数加 1。
        */
        incrementRefCount();
    }

    /*
        赋值运算符

        作用：
            处理已有对象之间的赋值。

        例如：

            CowString s1("hello");
            CowString s2("world");

            s1 = s2;

        赋值运算符要做两件事：

            1. 释放 s1 原来管理的空间
            2. 让 s1 共享 s2 的空间

        注意：
            释放旧空间时不一定真的 delete。
            要先让旧空间的引用计数减 1。
            只有引用计数变成 0，才真正释放。
    */
    CowString & operator=(const CowString & rhs)
    {
        /*
            防止自赋值。

            例如：

                s1 = s1;

            如果不判断自赋值，
            可能会先 release() 自己，
            导致后续访问 rhs.m_pStr 出现问题。
        */
        if(this != &rhs)
        {
            /*
                当前对象不再使用原来的字符串空间。

                release() 内部会：
                    1. 引用计数减 1
                    2. 如果引用计数为 0，就释放堆空间
            */
            release();

            /*
                当前对象共享 rhs 的字符串空间。
            */
            m_pStr = rhs.m_pStr;

            /*
                因为当前对象也开始共享 rhs 的空间，
                所以引用计数加 1。
            */
            incrementRefCount();
        }

        /*
            返回当前对象本身，
            方便支持连续赋值：

                s1 = s2 = s3;
        */
        return *this;
    }

    /*
        析构函数

        当 CowString 对象生命周期结束时调用。

        注意：
            不能直接 delete m_pStr。

        原因：
            当前对象的字符串空间可能还被其他 CowString 对象共享。

        正确做法：
            调用 release()，
            先让引用计数减 1，
            如果引用计数变成 0，
            才真正释放内存。
    */
    ~CowString()
    {
        release();
    }

    /*
        非 const 版本的 operator[]

        作用：
            用于非 const CowString 对象的下标访问。

        例如：

            CowString s("abc");

            cout << s[0];   // 读
            s[0] = 'A';     // 写

        因为非 const 对象既可能读，也可能写，
        所以不能直接返回 char，
        也不应该直接返回 char&。

        这里返回 CharProxy，
        让 CharProxy 去区分后续到底是读操作还是写操作。
    */
    CharProxy operator[](int index)
    {
        /*
            返回一个代理对象。

            这个代理对象记录：
                1. 当前 CowString 对象是谁
                2. 要访问的下标是多少
        */
        return CharProxy(*this, index);
    }

    /*
        const 版本的 operator[]

        作用：
            用于 const CowString 对象的下标访问。

        例如：

            const CowString s("abc");
            cout << s[0];

        const 对象只能读，不能写。

        所以 const 版本可以直接返回 char，
        不需要返回 CharProxy。

        如果没有这个 const 版本：

            const CowString s("abc");
            cout << s[0];

        会报错。

        原因是：
            const 对象只能调用 const 成员函数。
            非 const 的 operator[] 不能被 const 对象调用。
    */
    char operator[](int index) const
    {
        /*
            下标合法性检查。
        */
        if(index < 0 || index >= size())
        {
            cout << "index is illegal" << endl;
            return '\0';
        }

        /*
            const 对象只能读，
            所以直接返回对应字符即可。
        */
        return m_pStr[index];
    }

    /*
        获取字符串长度

        std::strlen 计算的是 C 风格字符串长度，
        不包含末尾的 '\0'。

        例如：

            strlen("abc") == 3
    */
    int size() const
    {
        return std::strlen(m_pStr);
    }

    /*
        返回 C 风格字符串

        返回 const char * 的原因：

            不希望外部通过 c_str() 直接修改底层字符串内容。

        如果这里返回 char *，外部可以这样做：

            CowString s1("abc");
            CowString s2 = s1;

            char * p = s1.c_str();
            p[0] = 'A';

        这样会绕过 CharProxy，
        也就绕过了写时复制逻辑，
        导致 s2 也可能被一起修改。

        所以这里返回 const char *，
        只允许外部读取字符串内容。
    */
    const char * c_str() const
    {
        return m_pStr;
    }

    /*
        获取引用计数

        因为引用计数存放在 m_pStr 前面的 4 个字节中，
        所以通过：

            m_pStr - 4

        找到引用计数的位置。

        再强转成 int *，
        最后解引用得到引用计数的值。
    */
    int getRefCount() const
    {
        return *(int *)(m_pStr - 4);
    }

    /*
        声明 CowString 的输出运算符为友元函数。

        这样 operator<< 可以访问 CowString 的私有成员 m_pStr。
    */
    friend ostream & operator<<(ostream & os, const CowString & rhs);

private:
    /*
        初始化引用计数为 1。

        只有刚刚申请一块新空间时，才调用这个函数。

        例如：
            构造函数中
            detach() 申请新空间后
    */
    void initRefCount()
    {
        *(int *)(m_pStr - 4) = 1;
    }

    /*
        引用计数加 1。

        当有新的 CowString 对象共享当前字符串空间时调用。

        常见场景：
            1. 拷贝构造函数
            2. 赋值运算符中共享 rhs 空间
    */
    void incrementRefCount()
    {
        ++*(int *)(m_pStr - 4);
    }
    
    /*
        引用计数减 1。

        当某个 CowString 对象不再使用当前字符串空间时调用。

        常见场景：
            1. 析构函数中
            2. 赋值运算符释放旧空间时
            3. detach() 脱离共享空间时
    */
    void decrementRefCount()
    {
        --*(int *)(m_pStr - 4);
    }

    /*
        统一释放当前对象持有的字符串空间。

        注意：
            release() 不一定真的释放堆内存。

        它的逻辑是：

            1. 如果 m_pStr 不为空，说明当前对象持有某块字符串空间。
            2. 先让引用计数减 1。
            3. 如果引用计数减到 0，说明没有对象再使用这块空间。
            4. 此时才真正 delete[]。
            5. 最后把 m_pStr 置为空，避免野指针。
    */
    void release()
    {
        if(m_pStr)
        {
            /*
                当前对象即将不再使用这块空间，
                所以引用计数减 1。
            */
            decrementRefCount();

            /*
                如果引用计数为 0，
                说明当前对象是最后一个使用者。

                这时可以释放整块堆空间。
            */
            if(getRefCount() == 0)
            {
                /*
                    必须 delete[] (m_pStr - 4)，
                    不能 delete[] m_pStr。

                    原因：
                        new[] 返回的是整块空间的起始地址。
                        而 m_pStr 已经向后偏移了 4 个字节，
                        指向的是字符串内容区。

                    所以释放时要回到原始地址：
                        m_pStr - 4
                */
                delete [] (m_pStr - 4);
                cout << "release heap" << endl;
            }

            /*
                当前对象不再指向任何有效字符串空间。
            */
            m_pStr = nullptr;
        }
    }

    /*
        detach：脱离共享空间

        作用：
            在写操作发生之前，
            如果发现当前字符串空间被多个对象共享，
            就为当前对象复制一份独立空间。

        只有满足两个条件时才需要调用 detach()：

            1. 当前操作是写操作
            2. 当前空间引用计数大于 1

        例如：

            CowString s1("abc");
            CowString s2 = s1;

            s1[0] = 'A';

        写之前：

            s1 ----\
                   ---> [refCount = 2]["abc"]
            s2 ----/

        detach() 之后，修改之前：

            s1 ---> [refCount = 1]["abc"]

            s2 ---> [refCount = 1]["abc"]

        然后再执行真正的字符修改：

            s1 ---> [refCount = 1]["Abc"]

            s2 ---> [refCount = 1]["abc"]
    */
    void detach()
    {   
        /*
            保存旧字符串空间的地址。

            因为后面会让 m_pStr 指向新申请的空间，
            如果不先保存旧地址，
            就无法从旧空间拷贝字符串内容了。
        */
        char * old = m_pStr;

        /*
            当前对象即将离开旧的共享空间，
            所以旧空间的引用计数减 1。

            detach() 只会在 getRefCount() > 1 时调用，
            所以减 1 后旧空间仍然至少有一个对象使用，
            不需要在这里 delete。
        */
        decrementRefCount();

        /*
            为当前对象申请一块新的独立空间。

            空间大小仍然是：

                4 字节引用计数
                +
                旧字符串长度
                +
                1 字节 '\0'
        */
        m_pStr = new char[4 + std::strlen(old) + 1]() + 4;

        /*
            新空间只有当前对象一个使用者，
            所以引用计数初始化为 1。
        */
        initRefCount();

        /*
            把旧空间中的字符串内容复制到新空间。

            注意：
                此时只是完成“分离”。
                真正的字符修改发生在 CharProxy::operator=(char) 中。
        */
        std::strcpy(m_pStr, old);
    }

private:
    /*
        指向字符串内容区的指针。

        注意：
            m_pStr 不是整块堆空间的起始地址。

        实际布局如下：

            m_pStr - 4        m_pStr
                |               |
                v               v
            +---------+----------------+
            | refCnt  | 字符串内容      |
            +---------+----------------+

        所以：
            访问引用计数：*(int *)(m_pStr - 4)
            访问字符串内容：m_pStr[index]
            释放整块空间：delete [] (m_pStr - 4)
    */
    char * m_pStr;

    /*
        允许 CharProxy 访问 CowString 的私有成员。

        CharProxy 需要访问：
            1. m_pStr
            2. getRefCount()
            3. detach()
            4. size()

        其中 m_pStr 和 detach() 是私有的，
        所以需要声明友元。
    */
    friend class CharProxy;
};

/*
    输出 CowString 对象

    例如：

        CowString s("abc");
        cout << s << endl;

    输出的就是 s 内部保存的 C 风格字符串。
*/
ostream & operator<<(ostream & os, const CowString & rhs)
{
    /*
        rhs.m_pStr 指向字符串内容区，
        所以可以直接输出。
    */
    os << rhs.m_pStr;
    return os;
}

/*
    输出 CharProxy 对象

    例如：

        CowString s("abc");
        cout << s[0] << endl;

    注意：
        s[0] 返回的不是 char，
        而是 CowString::CharProxy。

    所以需要重载：

        operator<<(ostream &, const CowString::CharProxy &)

    这里通过 static_cast<char>(rhs)
    把 CharProxy 转换成 char。

    这样会调用：

        CharProxy::operator char() const

    因此：
        cout << s[0]

    本质上是一次读操作，
    不会触发写时复制。
*/
ostream & operator<<(ostream & os, const CowString::CharProxy & rhs)
{
    /*
        这里不直接访问 rhs.m_self.m_pStr[rhs.m_index]，
        而是统一调用 operator char()。

        好处：
            1. 读操作逻辑集中在 operator char() 中
            2. 越界检查也集中在 operator char() 中
            3. operator<< 的实现更简洁
    */
    os << static_cast<char>(rhs);
    return os;
}

/*
    测试函数

    用于验证：
        1. 构造函数是否正常
        2. 拷贝构造是否采用共享空间
        3. 读操作是否不会触发写时复制
        4. 写操作是否会触发写时复制
        5. char ch = s[0] 是否可用
        6. s1[0] = s2[1] 是否可用
*/
void test1()
{
    cout << "---------- 创建 s1 ----------" << endl;

    /*
        调用有参构造函数。

        此时 s1 独占一块空间：

            s1 ---> [refCount = 1]["abc"]
    */
    CowString s1("abc");

    cout << "s1 = " << s1 << endl;
    cout << "s1 refCount = " << s1.getRefCount() << endl;

    cout << endl;
    cout << "---------- 拷贝构造 s2 ----------" << endl;

    /*
        调用拷贝构造函数。

        注意：
            这里不会深拷贝字符串内容。

        s2 和 s1 共享同一块字符串空间：

            s1 ----\
                   ---> [refCount = 2]["abc"]
            s2 ----/
    */
    CowString s2 = s1;

    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;

    /*
        因为 s1 和 s2 共享同一块空间，
        所以它们读到的引用计数都是 2。
    */
    cout << "s1 refCount = " << s1.getRefCount() << endl;
    cout << "s2 refCount = " << s2.getRefCount() << endl;

    cout << endl;
    cout << "---------- 读操作：cout << s1[0] ----------" << endl;

    /*
        s1[0] 返回 CharProxy 对象。

        cout << s1[0] 会调用：

            operator<<(ostream &, const CowString::CharProxy &)

        该函数内部会把 CharProxy 转换成 char，
        也就是调用 CharProxy::operator char()。

        这是读操作，不会触发 detach()。
    */
    cout << "s1[0] = " << s1[0] << endl;

    /*
        因为刚才只是读操作，
        所以 s1 和 s2 仍然共享同一块空间，
        引用计数仍然是 2。
    */
    cout << "s1 refCount = " << s1.getRefCount() << endl;
    cout << "s2 refCount = " << s2.getRefCount() << endl;

    cout << endl;
    cout << "---------- 写操作：s1[0] = 'A' ----------" << endl;

    /*
        s1[0] = 'A' 会调用：

            CharProxy::operator=(char)

        在 operator=(char) 中会检查引用计数。

        当前 s1 和 s2 共享空间，引用计数为 2，
        所以会先调用 detach()。

        detach() 后：
            s1 拥有新空间，内容先复制为 "abc"
            s2 继续拥有旧空间，内容仍是 "abc"

        然后再把 s1 的第 0 个字符改成 'A'。
    */
    s1[0] = 'A';

    /*
        写操作完成后：

            s1 ---> [refCount = 1]["Abc"]

            s2 ---> [refCount = 1]["abc"]

        这说明：
            修改 s1 不会影响 s2，
            COW 生效。
    */
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s1 refCount = " << s1.getRefCount() << endl;
    cout << "s2 refCount = " << s2.getRefCount() << endl;

    cout << endl;
    cout << "---------- 支持 char ch = s2[1] ----------" << endl;

    /*
        s2[1] 返回 CharProxy。

        char ch = s2[1] 需要把 CharProxy 转成 char，
        所以会调用 CharProxy::operator char()。

        这是读操作，不触发写时复制。
    */
    char ch = s2[1];

    /*
        s2 的内容是 "abc"，
        下标 1 的字符是 'b'。
    */
    cout << "ch = " << ch << endl;

    cout << endl;
    cout << "---------- 支持 s1[1] = s2[2] ----------" << endl;

    /*
        s1[1] = s2[2];

        左边：
            s1[1] 返回 CharProxy，表示要写入的位置。

        右边：
            s2[2] 返回 CharProxy，表示要读取的字符。

        执行过程：
            1. 右边 s2[2] 通过 operator char() 转成字符 'c'
            2. 左边 s1[1] 调用 operator=(char)
            3. 把 'c' 写入 s1[1]

        当前 s1 的内容是 "Abc"，
        将下标 1 的 'b' 改成 'c'，
        所以 s1 变成 "Acc"。

        s2 不受影响，仍然是 "abc"。
    */
    s1[1] = s2[2];

    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
}

int main()
{
    /*
        调用测试函数，观察 CowString 的行为。
    */
    test1();

    return 0;
}