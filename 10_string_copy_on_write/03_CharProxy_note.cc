#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

/**
 * CowString：
 * 模拟带有写时复制机制的字符串类。
 *
 * 前一版 operator[] 的问题：
 *
 * char & operator[](int index);
 *
 * 因为返回的是 char &，
 * 所以编译器无法区分下面两种情况：
 *
 * 1. 读操作：
 *    cout << s1[0] << endl;
 *
 * 2. 写操作：
 *    s1[0] = 'A';
 *
 * 对于写时复制而言，
 * 只有写操作才应该触发深拷贝。
 *
 * 但是如果 operator[] 直接返回 char &，
 * 那么即使只是读取 s1[0]，
 * 也可能提前触发写时复制。
 *
 *
 * 当前版本的解决办法：
 *
 * 使用代理模式。
 *
 * operator[] 不再直接返回 char &，
 * 而是返回一个代理类对象 CharProxy。
 *
 * CharProxy 负责区分：
 *
 * 1. 读操作：
 *    cout << s1[0];
 *    调用 CharProxy 的 operator<<，
 *    只读取字符，不触发写时复制。
 *
 * 2. 写操作：
 *    s1[0] = 'A';
 *    调用 CharProxy 的 operator=，
 *    此时才判断是否共享，
 *    如果共享，则触发写时复制。
 */
class CowString
{
    /**
     * CharProxy：
     * CowString 的内部代理类。
     *
     * 作用：
     * 帮助 CowString 区分下标访问时的读操作和写操作。
     *
     *
     * 为什么要定义成内部类？
     *
     * 因为 CharProxy 只服务于 CowString，
     * 主要用于辅助 CowString 完成 operator[] 的功能。
     *
     * 它不需要被外部单独使用，
     * 所以定义成 CowString 的内部类更加合适。
     *
     *
     * CharProxy 中需要记录两个信息：
     *
     * 1. 当前操作的是哪个 CowString 对象
     *    使用 CowString & m_self 保存。
     *
     * 2. 当前访问的是哪个下标
     *    使用 int m_index 保存。
     */
    class CharProxy
    {
    public:
        /**
         * CharProxy 构造函数
         *
         * 参数：
         * CowString& cow
         * 表示当前代理对象绑定的是哪个 CowString 对象。
         *
         * int index
         * 表示当前访问的是字符串中的哪个下标。
         *
         *
         * 例如：
         * s1[0]
         *
         * 实际过程：
         * 1. s1 调用 CowString::operator[](0)
         * 2. operator[] 返回 CharProxy{s1, 0}
         * 3. CharProxy 对象记录：
         *    m_self 绑定 s1
         *    m_index 记录 0
         */
        CharProxy(CowString& cow, int index)
        : m_self(cow)
        , m_index(index)
        {

        }

        /**
         * CharProxy 的输出流运算符重载
         *
         * 作用：
         * 支持下面这种读操作：
         *
         * cout << s1[0] << endl;
         *
         *
         * 执行过程：
         * 1. s1[0] 调用 CowString::operator[]
         * 2. 返回一个 CharProxy 临时对象
         * 3. cout << CharProxy 对象
         * 4. 调用这里的 operator<<
         * 5. 只读取 m_self.m_pStr[m_index] 位置的字符
         *
         *
         * 注意：
         * 这里是读操作，
         * 所以不需要触发写时复制。
         */
        friend
        ostream & operator<<(ostream & os, const CharProxy & rhs);

        /**
         * CharProxy 的赋值运算符重载
         *
         * 作用：
         * 支持下面这种写操作：
         *
         * s1[0] = 'A';
         *
         *
         * 执行过程：
         * 1. s1[0] 调用 CowString::operator[]
         * 2. 返回 CharProxy{s1, 0}
         * 3. CharProxy 对象再调用 operator=('A')
         * 4. 在 operator= 中判断是否需要写时复制
         * 5. 最后修改指定下标的字符
         *
         *
         * 为什么写时复制逻辑放在这里？
         *
         * 因为只有进入 CharProxy::operator=，
         * 才说明当前操作一定是写操作。
         *
         * 这样就解决了前一版 operator[] 无法区分读写的问题。
         */
        char & operator=(const char & ch)
        {
            // 判断下标是否合法
            if(m_index < 0 || m_index >= strlen(m_self.m_pStr))
            {
                // 不能返回局部变量的引用，
                // 所以这里使用 static 静态局部变量。
                static char nullChar = '\0';
                return nullChar;
            }else{
                // 获取引用计数，判断是否大于 1
                //
                // 如果引用计数大于 1，
                // 说明当前字符串空间被多个 CowString 对象共享。
                //
                // 此时如果直接修改字符，
                // 会影响其他共享该空间的对象，
                // 所以需要先进行写时复制。
                if(m_self.getRefCount() > 1){
                    // 当前对象准备脱离原来的共享空间，
                    // 所以原共享空间的引用计数 -1。
                    m_self.decrementRefCount();

                    // 再进行深拷贝
                    //
                    // 新空间仍然采用相同的内存布局：
                    //
                    // | 引用计数 int | 字符串内容 |
                    //
                    // new char[4 + strlen(...) + 1]{}
                    //
                    // 4：保存引用计数
                    // strlen(...)：保存有效字符
                    // 1：保存字符串结束符 '\0'
                    char * temp = new char[4 + strlen(m_self.m_pStr) + 1]{} + 4;

                    // 将原字符串内容复制到新空间
                    strcpy(temp, m_self.m_pStr);

                    // 修改当前 CowString 对象的底层指针，
                    // 让它指向新空间。
                    m_self.m_pStr = temp;

                    // 新空间现在只属于当前对象，
                    // 所以引用计数初始化为 1。
                    m_self.initRefCount();
                }

                // 完成字符赋值
                //
                // 到这里时：
                // 1. 如果原本没有共享，直接修改原空间。
                // 2. 如果原本有共享，已经先完成深拷贝，
                //    再修改自己的新空间。
                m_self.m_pStr[m_index] = ch;

                // 返回修改后的字符引用
                return m_self.m_pStr[m_index];
            }
        }

    private:
        // 记录当前代理对象绑定的是哪个 CowString 对象
        //
        // 使用引用的原因：
        // CharProxy 不需要重新保存一份 CowString，
        // 只需要绑定原来的 CowString 对象即可。
        CowString & m_self;

        // 记录当前访问的字符串下标
        int m_index;
    };

public:
    /**
     * 无参构造函数
     *
     * 创建一个空字符串对象。
     *
     * new char[4 + 1]{}：
     * 4：保存引用计数
     * 1：保存字符串结束符 '\0'
     *
     * + 4：
     * 让 m_pStr 指向字符串数据区。
     */
    CowString()
    : m_pStr(new char[4 + 1]{} + 4)
    {
        // 初始化引用计数器为 1
        /* *(int*)(m_pStr - 4) = 1; */

        // 替换成函数调用，避免重复书写指针运算代码
        initRefCount();
    }

    /**
     * 有参构造函数
     *
     * 使用 C 风格字符串创建 CowString 对象。
     */
    CowString(const char * pStr)
    : m_pStr(new char[4 + strlen(pStr) + 1]{} + 4) // 让底层指针指向字符数据部分
    {
        // 初始化引用计数器为 1
        /* *(int*)(m_pStr - 4) = 1; */
        initRefCount();

        // 数据复制
        strcpy(m_pStr, pStr);
    }

    /**
     * 析构函数
     *
     * 对象销毁时，
     * 先让引用计数 -1。
     *
     * 如果引用计数变成 0，
     * 说明没有对象再使用这块空间，
     * 此时才真正释放堆空间。
     */
    ~CowString()
    {
        // 引用计数 -1
        decrementRefCount();

        // 判断引用计数和 0 的关系
        // 如果为 0，说明没有字符串对象引用这个空间了。
        if(getRefCount() == 0){
            // 进行回收
            //
            // 注意：
            // m_pStr 指向字符串数据区，
            // 真正 new 出来的地址是 m_pStr - 4。
            delete [] (m_pStr - 4);
            cout << "release heap====>" << endl;
        }

        // 如果引用计数不为 0，
        // 说明还有其他对象在使用该空间，
        // 当前对象只需要断开指针即可。
        m_pStr = nullptr;
    }

    /**
     * 拷贝构造函数
     *
     * 使用一个已有对象初始化新对象。
     *
     * 这里采用浅拷贝：
     * 两个对象共享同一块字符串空间。
     *
     * 所以引用计数需要 +1。
     */
    CowString(const CowString & rhs)
    : m_pStr(rhs.m_pStr) // 深拷贝 --> 浅拷贝，共享空间
    {
        // 引用计数 +1
        /* ++*(int*)(m_pStr - 4); */
        incrementRefCount();
    }

    /**
     * CowString 的输出流运算符重载
     *
     * 支持：
     * cout << s1 << endl;
     */
    friend
    ostream & operator<<(ostream & os, const CowString & rhs);

    /**
     * 赋值运算符重载
     *
     * 作用：
     * 处理两个已经存在的 CowString 对象之间的赋值。
     *
     * 例如：
     * s1 = s2;
     *
     * 执行流程：
     * 1. 判断是否自赋值。
     * 2. 当前对象脱离原来的空间。
     * 3. 如果原空间引用计数变成 0，则释放原空间。
     * 4. 当前对象指向 rhs 的字符串空间。
     * 5. 新空间引用计数 +1。
     */
    CowString & operator=(const CowString & rhs)
    {
        // 自赋值判断
        if(this != &rhs){
            // 当前对象准备脱离原空间，
            // 所以原空间引用计数 -1。
            decrementRefCount();

            // 获取引用计数，判断和 0 的关系
            if(getRefCount() == 0){
                // 如果为 0，说明原空间已经没有对象使用了，
                // 可以释放原本空间。
                delete [] (m_pStr - 4);
                cout << "release heap=====>" << endl;
            }

            // 让当前对象的字符指针指向新空间
            //
            // 这里仍然是浅拷贝，
            // 当前对象和 rhs 共享同一块字符串空间。
            m_pStr = rhs.m_pStr;

            // 新空间的引用计数 +1
            incrementRefCount();
        }

        // 返回当前对象 *this，
        // 支持连续赋值：
        // s1 = s2 = s3;
        return  *this;
    }

#if 0
    /**
     * 第一版 operator[]
     *
     * 直接返回 char &。
     *
     * 这种写法可以支持：
     * s1[0] = 'A';
     *
     * 但是问题是：
     * 如果多个 CowString 对象共享同一块空间，
     * 修改其中一个对象的字符，
     * 会影响其他对象。
     */
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

    // 通过下标访问 index 位置的字符没问题
    // 但是有共享时，修改会对其他的 string 对象产生影响。
#endif

#if 0
    /**
     * 第二版 operator[]
     *
     * 加入了写时复制逻辑。
     *
     * 如果引用计数大于 1，
     * 就先深拷贝，再返回字符引用。
     *
     * 问题：
     * 无法区分读操作和写操作。
     *
     * 例如：
     * cout << s1[0] << endl;
     *
     * 这只是读取，
     * 但因为 operator[] 返回 char &，
     * 也可能提前触发深拷贝。
     */
    char & operator[](int index)
    {
        if(index < 0 || index >= strlen(m_pStr))
        {
            static char nullChar = '\0';
            return nullChar;
        }else{
            // 获取引用计数，判断是否大于 1
            // 如果大于 1，说明有共享。
            if(getRefCount() > 1){
                // 当前的引用计数 -1
                decrementRefCount();

                // 再进行深拷贝
                char * temp = new char[4 + strlen(m_pStr) + 1]{} + 4;
                strcpy(temp, m_pStr);

                // 更改底层指针，指向新空间
                m_pStr = temp;

                // 新空间的引用计数初始化为 1
                initRefCount();
            }
            
            // 返回字符引用
            return m_pStr[index];
        }
    }

    // 该版本无法区分读写操作。
#endif

    /**
     * 第三版 operator[]
     *
     * 返回值不再是 char &，
     * 而是 CharProxy 代理对象。
     *
     *
     * 例如：
     * cout << s1[0] << endl;
     *
     * s1[0] 返回 CharProxy 对象，
     * 然后调用 CharProxy 的 operator<<，
     * 只读取字符，不触发写时复制。
     *
     *
     * 例如：
     * s1[0] = 'A';
     *
     * s1[0] 返回 CharProxy 对象，
     * 然后调用 CharProxy 的 operator=，
     * 此时才触发写操作逻辑。
     */
    CharProxy operator[](int index)
    {
        return CharProxy{*this, index};
    };


    // 用于获取字符串长度的方法
    // strlen 不包含字符串末尾的 '\0'
    int size()
    {
        return strlen(m_pStr);
    }

    // 返回 C 风格字符串
    char * c_str()
    {
        return m_pStr;
    }

    // 获取引用计数
    //
    // m_pStr - 4 指向引用计数所在的位置。
    int getRefCount()
    {
        return *(int*)(m_pStr - 4);
    }

private:
    // 封装一些代码片段作为函数，
    // 方便重复使用，也避免多次书写复杂的指针运算。

    // 初始化引用计数器
    void initRefCount()
    {
       *(int*)(m_pStr - 4) = 1;
    }

    // 引用计数 +1
    void incrementRefCount()
    {
       ++*(int*)(m_pStr - 4);
    }

    // 引用计数 -1
    void decrementRefCount()
    {
       --*(int*)(m_pStr - 4);
    }

    // pointer to char array
    // 指向字符串数据区，
    // 不指向整块堆空间真正的起始位置。
    char * m_pStr;

    /**
     * 将 CharProxy 的 operator<< 声明为 CowString 的友元函数。
     *
     * 原因：
     * CharProxy 的输出函数中需要访问：
     *
     * rhs.m_self.m_pStr[rhs.m_index]
     *
     * 其中 m_pStr 是 CowString 的私有成员。
     *
     * 所以需要授权该函数访问 CowString 的私有成员。
     */
    friend
    ostream & operator<<(ostream & os, const CowString::CharProxy & rhs);
};

/**
 * CowString 类的 operator<<
 *
 * 支持：
 * cout << s1 << endl;
 */
ostream & operator<<(ostream & os, const CowString & rhs)
{
    os << rhs.m_pStr;
    return os;
}

/**
 * CharProxy 类的 operator<<
 *
 * 支持：
 * cout << s1[0] << endl;
 *
 *
 * 注意：
 * 这里是读操作。
 *
 * 它只是把指定下标位置的字符输出，
 * 不会修改字符串内容，
 * 也不会触发写时复制。
 */
ostream & operator<<(ostream & os, const CowString::CharProxy & rhs)
{
    os << rhs.m_self.m_pStr[rhs.m_index];
    return os;
}

void test1()
{
    // 创建字符串对象 s1
    CowString s1{"abc"};

    // 使用拷贝构造函数创建 s2
    //
    // s1 和 s2 共享同一块字符串空间，
    // 引用计数变为 2。
    CowString s2 = s1;

    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "----------" << endl;

    // 读操作
    //
    // 执行流程：
    // 1. s1[0] 调用 CowString::operator[]
    // 2. 返回 CharProxy{s1, 0}
    // 3. cout << CharProxy 对象
    // 4. 调用 CharProxy 的 operator<<
    //
    // 因为这里只是读取，
    // 所以不会触发写时复制。
    cout << s1[0] << endl;

    // 写操作
    //
    // 执行流程：
    // 1. s1[0] 返回 CharProxy{s1, 0}
    // 2. CharProxy 对象调用 operator=('A')
    // 3. 因为 s1 和 s2 当前共享空间，
    //    引用计数为 2，
    //    所以 s1 会先进行深拷贝。
    // 4. 深拷贝完成后，
    //    只修改 s1 自己的新空间。
    //
    // 最终结果：
    // s1 变成 "Abc"
    // s2 仍然是 "abc"
    s1[0] = 'A';

    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;

    // 写时复制之后，
    // s1 和 s2 不再共享同一块空间，
    // 所以它们的引用计数都变成 1。
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}