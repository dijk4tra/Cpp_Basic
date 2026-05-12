#include <iostream>
#include <ostream>
#include <pthread.h>
#include <string.h>

using std::cout;
using std::endl;
using std::ostream;

/**
 * CowString：
 * 模拟一个带有写时复制机制的字符串类。
 *
 * COW：Copy On Write
 * 中文通常叫做：写时复制。
 *
 * 核心思想：
 * 1. 多个 CowString 对象可以共享同一块字符串空间。
 * 2. 只读的时候，不需要真正复制字符串内容。
 * 3. 当某个对象要修改字符串内容时，
 *    如果这块空间正在被多个对象共享，
 *    就先开辟一块新空间，把原字符串复制过去，
 *    然后再修改自己的新空间。
 *
 * 这样可以减少不必要的深拷贝，
 * 提高字符串对象复制时的效率。
 *
 *
 * 当前内存布局：
 *
 * new char[4 + strlen(pStr) + 1]{}
 *
 * 前 4 个字节：保存引用计数
 * 后面的空间：保存字符串内容
 *
 * 例如：
 * CowString s{"abc"};
 *
 * 底层空间大致如下：
 *
 * | 引用计数 int | 'a' | 'b' | 'c' | '\0' |
 * ↑             ↑
 * 实际申请地址    m_pStr 指向的位置
 *
 * 注意：
 * m_pStr 并不指向整块空间的起始位置，
 * 而是指向字符串数据部分。
 *
 * 所以：
 * m_pStr - 4
 * 才是整块堆空间真正的起始位置。
 */

class CowString
{
public:
    /**
     * 无参构造函数
     *
     * 创建一个空字符串对象。
     *
     * new char[4 + 0 + 1]{}
     * 4：用于保存引用计数
     * 0：字符串有效字符个数为 0
     * 1：字符串结束符 '\0'
     *
     * + 4 的含义：
     * 让 m_pStr 指向字符串数据区，
     * 而不是引用计数所在的位置。
     */
    CowString()
    : m_pStr(new char[4 + 0 + 1]{} + 4)
    {
        // 初始化引用计数器为 1
        // 表示当前只有一个对象使用这块字符串空间
        /* *(int*)(m_pStr - 4) = 1; */

        // 替换成函数调用
        // 这样可以避免重复书写底层指针运算代码
        initRefCount();
    }
    
    /**
     * 有参构造函数
     *
     * 使用一个 C 风格字符串创建 CowString 对象。
     *
     * 例如：
     * CowString s{"abc"};
     *
     * strlen(pStr)：
     * 获取字符串有效字符个数，
     * 不包含末尾的 '\0'。
     */
    CowString(const char * pStr)
    : m_pStr(new char[4 + strlen(pStr) + 1]{} + 4) // 让底层指针指向数据部分
    {
        // 初始化引用计数器为 1
        /* *(int*)(m_pStr - 4) = 1; */
        initRefCount();

        // 将外部传入的字符串内容复制到当前对象的堆空间中
        strcpy(m_pStr, pStr);
    }
    
    /**
     * 析构函数
     *
     * 对象销毁时，不能直接释放 m_pStr 指向的空间。
     *
     * 原因：
     * 当前字符串空间可能被多个 CowString 对象共享。
     *
     * 正确做法：
     * 1. 先让引用计数 -1。
     * 2. 如果引用计数变成 0，
     *    说明没有任何对象再使用这块空间，
     *    此时才真正释放堆空间。
     * 3. 如果引用计数不为 0，
     *    说明还有其他对象在使用这块空间，
     *    当前对象只需要断开指针即可。
     */
    ~CowString()
    {
        // 引用计数 -1
        decrementRefCount();

        // 判断引用计数和 0 的关系
        // 如果为 0，说明没有字符串对象引用这个空间了
        if(getRefCount() == 0){
            // 进行回收
            // 注意：
            // m_pStr 指向的是字符串数据区，
            // 真正 new 出来的起始地址是 m_pStr - 4。
            delete [] (m_pStr - 4);
            cout << "release heap ===>" << endl;
        }

        // 如果不为 0，则仅将指针设置为空
        // 不能释放空间，因为其他对象还在使用
        m_pStr = nullptr;
    }
    
    /**
     * 拷贝构造函数
     *
     * 作用：
     * 使用一个已经存在的 CowString 对象，
     * 初始化一个新的 CowString 对象。
     *
     * 这里没有进行深拷贝，
     * 而是让两个对象共享同一块字符串空间。
     *
     * 例如：
     * CowString s1{"abc"};
     * CowString s2 = s1;
     *
     * 此时：
     * s1.m_pStr 和 s2.m_pStr 指向同一块字符串数据。
     *
     * 因为多了一个对象共享这块空间，
     * 所以引用计数需要 +1。
     */
    CowString(const CowString & rhs)
    : m_pStr(rhs.m_pStr)  // 深拷贝 ---> 浅拷贝，共享空间
    {
        // 引用计数 +1
        /* ++*(int*)(m_pStr - 4); */
        incrementRefCount();
    }

    /**
     * 输出流运算符重载 operator<<
     *
     * 作用：
     * 让 CowString 对象可以直接使用 cout 输出。
     *
     * 例如：
     * CowString s{"abc"};
     * cout << s << endl;
     *
     * 因为左操作数是 ostream 对象，
     * 不是 CowString 对象，
     * 所以 operator<< 一般写成普通函数。
     *
     * 又因为它需要访问 CowString 的私有成员 m_pStr，
     * 所以这里声明为友元函数。
     */
    friend
    ostream & operator<<(ostream & os, const CowString & rhs);

    /**
     * 赋值运算符重载 operator=
     *
     * 拷贝构造和赋值操作的区别：
     *
     * CowString s1{"abc"};
     * CowString s2 = s1;
     * 这里 s2 是新对象，调用拷贝构造函数。
     *
     * CowString s3{"hello"};
     * s3 = s1;
     * 这里 s3 已经存在，调用赋值运算符函数。
     *
     *
     * 当前 operator= 的逻辑：
     * 1. 先判断是否自赋值。
     * 2. 当前对象先脱离原来的字符串空间。
     * 3. 如果原空间引用计数变成 0，就释放原空间。
     * 4. 当前对象指向 rhs 的字符串空间。
     * 5. rhs 所在空间的引用计数 +1。
     * 6. 返回 *this，支持连续赋值。
     */
    CowString & operator=(const CowString & rhs)
    {
        // 自赋值判断
        // 例如：
        // s1 = s1;
        // 如果不判断，可能会先把自己的空间释放掉，
        // 后面再使用 rhs.m_pStr 时就出问题。
        if(this != &rhs){
            // 当前对象先脱离原来的空间
            // 所以原空间引用计数 -1
            decrementRefCount();

            // 获取引用计数，判断和 0 的关系
            if(getRefCount() == 0){
                // 如果为 0，说明原空间已经没有对象使用了，
                // 可以释放原本空间。
                delete [] (m_pStr - 4);
                cout << "release heap ===>" << endl;
            }

            // 让当前对象的字符串指向新空间
            // 这里仍然是浅拷贝，让当前对象和 rhs 共享空间
            m_pStr = rhs.m_pStr;

            // 新空间的引用计数 +1
            incrementRefCount();
        }

        // 返回当前对象 *this
        // 这样可以支持连续赋值：
        // s1 = s2 = s3;
        return *this;
    }

/*
// 这版 operator[] 不适合直接用于写时复制类
    // operator []
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
    // 这版代码的问题是：
    // 如果多个对象共享同一块字符串空间，
    // 通过其中一个对象修改字符，
    // 会影响其他共享对象。
*/

    char & operator[](int index)
    {
        if(index < 0 || index >= strlen(m_pStr)){
            cout << "index is illegal" << endl;
            // throw "index is illegal";

            // 返回一个静态字符，避免返回局部变量引用
            static char nullChar = '\0';
            return nullChar;
        }else{
            return m_pStr[index];
        }   
    }

    // 通过下标访问 index 位置的字符没问题
    // 但是有共享时，修改会对其他的 string 对象产生影响

    /**
     * 下标运算符重载 operator[]
     *
     * 这是适合写时复制版本的 operator[]。
     *
     * 作用：
     * 既支持读取字符：
     * cout << s1[0] << endl;
     *
     * 也支持修改字符：
     * s1[0] = 'A';
     *
     *
     * 为什么这里要返回 char &？
     *
     * 因为只有返回引用，
     * 才能让下标表达式作为左值使用。
     *
     * 例如：
     * s1[0] = 'A';
     *
     * 如果返回 char，
     * 那么 s1[0] 只是一个临时字符值，
     * 不能真正修改字符串中的字符。
     *
     *
     * 写时复制逻辑：
     * 如果引用计数大于 1，
     * 说明当前字符串空间被多个对象共享。
     * 此时如果要通过下标返回字符引用，
     * 就有可能发生修改。
     *
     * 为了不影响其他共享对象，
     * 当前对象需要先进行深拷贝，
     * 让自己拥有独立空间。
     */
    char & operator[](int index)
    {
        // 下标合法性判断
        if(index < 0 || index >= strlen(m_pStr))
        {
            // 注意：
            // 不能返回局部变量的引用。
            // 所以这里使用 static 静态局部变量。
            //
            // static 局部变量生命周期从程序开始到程序结束，
            // 函数返回后它依然存在。
            static char nullChar = '\0';
            return nullChar;
        }else{
            // 获取引用计数，判断是否大于 1
            // 如果大于 1，说明有共享
            if(getRefCount() > 1){
                // 当前对象准备脱离共享空间，
                // 所以原共享空间的引用计数 -1
                decrementRefCount();

                // 再进行深拷贝
                // 新空间同样预留前 4 个字节保存引用计数
                char *temp = new char[4 + strlen(m_pStr) + 1]{} + 4;

                // 将原字符串内容复制到新空间中
                strcpy(temp, m_pStr);

                // 更改底层指针，指向新空间
                m_pStr = temp;

                // 新的空间只属于当前对象，
                // 所以引用计数初始化为 1
                initRefCount();
            }

            // 返回字符引用
            // 这样 s1[index] 可以作为左值被修改
            return m_pStr[index];
        }
    }
    

    // 用于获取字符串长度的方法
    // strlen 不包含字符串末尾的 '\0'
    int size()
    {
        return strlen(m_pStr);
    }
    
    // 返回 C 风格字符串
    // 方便和 C 字符串相关函数配合使用
    char * c_str()
    {
        return m_pStr;
    }

    // 获取引用计数
    // m_pStr - 4 指向引用计数所在的位置
    int getRefCount()
    {
        return *(int*)(m_pStr - 4);
    }


private:
    // 封装一些代码片段作为函数，方便重复使用
    // 同时也避免在多个地方直接写复杂的指针运算

    // 初始化引用计数器
    void initRefCount()
    {
        *(int *)(m_pStr - 4) = 1;
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
    // 指向字符串数据区，不指向整块堆空间的起始位置
    char * m_pStr;
};

/**
 * operator<< 的函数实现
 *
 * 参数：
 * ostream & os
 * 表示输出流对象，例如 cout。
 *
 * const CowString & rhs
 * 表示要输出的 CowString 对象。
 *
 * 返回值：
 * ostream &
 * 返回输出流本身，
 * 这样可以支持连续输出。
 *
 * 例如：
 * cout << s1 << endl;
 */
ostream & operator<<(ostream & os, const CowString & rhs)
{
    os << rhs.m_pStr;
    return os;
}

// 测试构造函数
void test1()
{
    // 调用无参构造函数，创建空字符串
    CowString s1;

    // 调用有参构造函数，创建内容为 "abc" 的字符串
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

    // 用已经存在的对象 s1 初始化新对象 s2
    // 这里调用拷贝构造函数
    //
    // 因为当前类使用写时复制思想，
    // 所以这里不会立刻深拷贝字符串内容，
    // 而是让 s1 和 s2 共享同一块空间。
    CowString s2 = s1;
    
    cout << s1 << endl;
    cout << s2 << endl;

    // s1 和 s2 共享同一块空间，
    // 所以它们看到的引用计数是一样的。
    cout << "s1 refCount:" << s1.getRefCount() << endl;
    cout << "s2 refCount:" << s2.getRefCount() << endl;
}

// 测试析构函数
void test3()
{
    // 没有共享
    // s1 独占字符串空间
    CowString s1{"abc"};
    cout << s1 << endl;
    cout << "------" << endl;

    // 共享的情况
    // s2 和 s3 共享同一块字符串空间
    CowString s2{"hello"};
    CowString s3 = s2;

    cout << "s2:" << s2 << endl;
    cout << "s3:" << s3 << endl;

    // 因为 s2 和 s3 共享空间，
    // 所以引用计数为 2。
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "s3 count:" << s3.getRefCount() << endl;  
}

// 测试对象的赋值操作
void test4()
{
    CowString s1{"abc"};

    // s2 是新对象，
    // 用 s1 初始化 s2，
    // 调用拷贝构造函数。
    CowString s2 = s1;

    cout << "s1:" << s1 << endl;
    cout << "s2:" << s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;

    // s3 独占一块新的字符串空间
    CowString s3{"bcd"};
    cout << "s3:" << s3 << endl;
    cout << "s3 count:" << s3.getRefCount() << endl;
    cout << "--------" << endl;

    // s1 已经存在，
    // 所以这里不是拷贝构造，
    // 而是调用赋值运算符函数 operator=。
    //
    // 赋值后：
    // s1 脱离原来的 "abc" 空间，
    // 转而和 s3 共享 "bcd" 空间。
    s1 = s3;

    cout << "s1:" << s1 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;

    // s2 仍然指向原来的 "abc" 空间
    cout << "s2 count:" << s2.getRefCount() << endl;

    // s1 和 s3 共享 "bcd" 空间
    cout << "s3 count:" << s3.getRefCount() << endl;

    cout << "-----" << endl;

    // s2 也赋值为 s3
    // 此时 s2 会脱离原来的 "abc" 空间。
    //
    // 如果 "abc" 空间已经没有对象使用，
    // 就会被释放。
    s2 = s3;

    cout << "s2:" << s2 << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "s3 count:" << s3.getRefCount() << endl;
}

// 测试下标运算符和写时复制
void test5()
{
    // 如果底层数组空间没有共享，
    // 直接通过下标访问或修改是没有问题的。
    //
    // 如果发生了共享，
    // 修改之前就需要触发写时复制。
    CowString s1{"abc"};

    // s2 和 s1 共享同一块字符串空间
    CowString s2 = s1;

    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "----------" << endl;

    // 调用 operator[]
    //
    // 注意：
    // 即使这里只是读取 s1[0]，
    // 当前 operator[] 返回的是 char &，
    // 编译器无法判断后面到底会不会修改。
    //
    // 所以只要发现引用计数大于 1，
    // 就会先触发写时复制。
    cout << s1[0] << endl;

    // 如果执行这一行：
    // s1 会先脱离共享空间，
    // 然后只修改自己的字符串内容，
    // 不会影响 s2。
    /* s1[0] = 'A'; */

    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;

    // 如果上面访问 s1[0] 时发生了写时复制，
    // s1 和 s2 就不再共享同一块空间，
    // 各自的引用计数都会变成 1。
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
}


int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */

    // 当前测试下标运算符和写时复制
    test5();

    return 0;
}