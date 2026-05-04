#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/**
 * 带有指针成员的类
 *
 * 这个类中有一个指针成员：
 * char * m_brand;
 * m_brand 本身是一个指针变量，
 * 它保存的是一块堆内存的地址。
 * 这块堆内存中存放电脑品牌字符串，
 * 例如："xiaomi"、"huawei"。
 *
 *
 * 注意：
 * 如果一个类中有指针成员，
 * 并且这个指针指向的是通过 new / new[] 申请的堆内存，
 * 那么这个类通常需要自己写：
 * 1. 析构函数
 *    用来释放堆内存
 * 2. 拷贝构造函数
 *    用来实现深拷贝
 * 3. 赋值运算符函数
 *    用来实现深拷贝赋值
 * 这三个函数经常一起出现，
 * 也就是常说的“三件套”。
 *
 *
 * 为什么不能直接使用编译器自动生成的版本？
 * 编译器自动生成的拷贝构造函数和赋值运算符函数，
 * 默认只是逐个成员复制。
 * 对于 int 这种普通成员，直接复制没有问题。
 * 但是对于 char * 指针成员，
 * 默认复制只会复制指针中保存的地址，
 * 不会复制地址指向的字符串内容。
 * 这叫做“浅拷贝”。
 *
 *
 * 浅拷贝的问题：
 * 假设：
 * Computer pc1{"xiaomi", 1999};
 * Computer pc2 = pc1;
 * 如果是浅拷贝：
 * pc1.m_brand 和 pc2.m_brand 会指向同一块堆内存。
 * 当 pc1 和 pc2 析构时，
 * 它们都会 delete[] 同一块内存，
 * 造成 double free，也就是重复释放。
 *
 *
 * 深拷贝：
 * 深拷贝不是简单复制指针地址，
 * 而是重新申请一块新的堆内存，
 * 再把字符串内容复制过去。
 * 这样：
 * pc1.m_brand 指向一块堆内存
 * pc2.m_brand 指向另一块堆内存
 *
 * 两个对象各自管理自己的资源，
 * 析构时互不影响。
 */

class Computer
{
public:
    // 构造函数
    Computer(const char * brand, int price)
    : m_brand(new char[strlen(brand) + 1]{})
    , m_price(price)
    {
        cout << "constructor" << endl;

        /*
         * strlen(brand) 计算字符串长度，
         * 不包含字符串结尾的 '\0'。
         *
         * 所以申请空间时必须 + 1，
         * 用来存放字符串结束符 '\0'。
         */

        /*
         * strcpy 将 brand 指向的字符串内容，
         * 拷贝到 m_brand 指向的堆内存中。
         *
         * 拷贝完成后，
         * m_brand 指向的堆内存中保存了一份独立的字符串。
         */
        strcpy(m_brand, brand);
    }

    /**
     * 拷贝构造函数 copy constructor
     *
     * 调用时机：
     * 用一个已经存在的 Computer 对象，
     * 初始化一个新的 Computer 对象。
     * 例如：
     * Computer pc1{"xiaomi", 1999};
     * Computer pc2 = pc1;
     * pc2 是新对象，
     * 所以会调用拷贝构造函数。
     *
     * 为什么这里必须写拷贝构造函数？
     * 因为 Computer 类中有指针成员 m_brand，
     * 如果使用编译器默认生成的拷贝构造函数，
     * 只会进行浅拷贝：
     * pc2.m_brand = pc1.m_brand;
     * 这样两个对象会指向同一块堆内存，
     * 析构时会重复释放。
     *
     * 正确做法：
     * 重新申请一块堆内存，
     * 这就是深拷贝。
     */
    Computer(const Computer & rhs)
    : m_brand(new char[strlen(rhs.m_brand) + 1]{})
    , m_price(rhs.m_price)
    {
        cout << "copy constructor" << endl;

        /*
         * rhs 是被拷贝的对象。
         * 例如：
         * Computer pc2 = pc1;
         * 此时 rhs 引用的就是 pc1。
         * 这里为 pc2 重新申请一块堆内存，
         * 然后把 pc1.m_brand 中的字符串复制到 pc2.m_brand 中。
         * 这样 pc1 和 pc2 的 m_brand 指向不同的堆内存。
         */
        strcpy(m_brand, rhs.m_brand);
    }

    /**
     * 赋值运算符函数 operator=
     *
     * 调用时机：
     * 两个已经存在的 Computer 对象之间进行赋值。
     * 例如：
     * Computer pc1{"xiaomi", 1999};
     * Computer pc2{"huawei", 6999};
     * pc2 = pc1;
     *
     * 注意：
     * pc1 和 pc2 在赋值之前都已经存在，
     * 所以这里不是拷贝构造，
     * 而是调用赋值运算符函数。
     *
     * 和拷贝构造函数的区别：
     * 拷贝构造：
     * 用已有对象创建新对象。
     * 赋值运算符：
     * 两个对象都已经存在，
     * 把右边对象的内容赋给左边对象。
     *
     * 参数：
     * const Computer & rhs
     * rhs 表示赋值号右边的对象。
     * 例如：
     * pc2 = pc1;
     * this 指向 pc2
     * rhs 引用 pc1
     */
    Computer & operator=(const Computer & rhs)
    {
        cout << "operator=" << endl;

        /*
         * 自赋值判断
         *
         * 什么是自赋值？
         * pc1 = pc1;
         * 也就是一个对象自己给自己赋值。
         * 在这种情况下：
         * this 指向 pc1
         * rhs 也引用 pc1
         * 所以：this == &rhs
         *
         * 为什么要判断自赋值？
         * 如果不判断，直接执行：
         * delete [] m_brand;
         * 就会把当前对象自己的字符串资源释放掉。
         *
         * 但 rhs 和当前对象是同一个对象，
         * rhs.m_brand 也指向这块已经被释放的内存。
         *
         * 后面再执行：
         * strlen(rhs.m_brand)
         * 就是在访问已经释放的内存，
         * 会导致未定义行为。
         * 
         * 所以：
         * 如果 this == &rhs，
         * 说明是自己给自己赋值，
         * 什么都不需要做，
         * 直接返回当前对象即可。
         */
        if(this != &rhs){

            /*
             * 先回收当前对象原本管理的堆内存。
             *
             * 例如：
             * Computer pc1{"xiaomi", 1999};
             * Computer pc2{"huawei", 6999};
             * pc2 = pc1;
             *
             * 在赋值之前：
             * pc2.m_brand 指向 "huawei" 那块堆内存。
             *
             * 赋值之后：
             * pc2 应该保存 "xiaomi"。
             *
             * 如果不先 delete[] pc2 原来的 m_brand，
             * "huawei" 那块堆内存就再也找不到了，
             * 会造成内存泄漏。
             */
            delete [] m_brand;
            m_brand = nullptr;

            /*
             * 把浅拷贝变成深拷贝。
             *
             * 错误的浅拷贝写法：
             * this->m_brand = rhs.m_brand;
             * 这样只是复制地址，
             * 会导致两个对象指向同一块堆内存。
             *
             * 正确的深拷贝写法：
             * 1.重新申请一块新的堆内存
             * 2.把 rhs.m_brand 指向的字符串内容复制过来
             */

            /* this->m_brand = rhs.m_brand; */

            // 根据 rhs.m_brand 字符串长度，
            // 重新申请一块足够大的堆内存。
            this->m_brand = new char[strlen(rhs.m_brand)+1]{};

            // 将右边对象中的字符串内容复制到当前对象的新空间中。
            strcpy(m_brand, rhs.m_brand);

            // 普通 int 成员直接赋值即可。
            this->m_price = rhs.m_price;
        }

        /*
         * 返回当前对象
         *
         * this 是当前对象的地址。
         * *this 表示当前对象本身。
         *
         * 返回 *this 的作用：
         * 支持连续赋值。
         *
         * 例如：
         * pc3 = pc2 = pc1;
         * pc2 = pc1 执行完后返回 pc2，
         * pc3 才能继续接着赋值。
         */
        return *this;
    }

    /**
     * 析构函数
     *
     * 当 Computer 对象销毁时自动调用。
     *
     * 作用：
     * 释放构造函数、拷贝构造函数、赋值运算符中
     * 通过 new[] 申请的堆内存。
     */
    ~Computer()
    {
        cout << "~Computer()" << endl;

        /*
         * 如果 m_brand 不为空，
         * 说明它指向一块有效的堆内存。
         */
        if(m_brand){

            /*
             * m_brand 是通过 new char[...] 申请的数组，
             * 所以必须使用 delete[] 释放。
             *
             * new      对应 delete
             * new[]    对应 delete[]
             */
            delete[] m_brand;

            /*
             * 释放之后将指针置空，
             * 避免野指针。
             */
            m_brand = nullptr;
        }
    }

    // 普通成员函数
    // 打印当前电脑对象的品牌和价格
    void print()
    {
        cout << m_brand << " " << m_price << endl;
    }

private:
    /*
     * 指针成员变量

     * m_brand 保存的是堆内存的地址。
     *
     * 这块堆内存中保存品牌字符串。
     *
     * 因为它指向堆内存，
     * 所以对象销毁时需要在析构函数中手动释放。
     */
    char * m_brand;

    /*
     * 普通 int 成员变量
     *
     * m_price 不需要手动释放。
     * 对象销毁时会自动销毁。
     */
    int m_price;
};

void test1()
{
    /**
     * 测试拷贝构造函数
     *
     * 创建 pc1：
     * 调用普通构造函数。
     */
    Computer pc1{"xiaomi", 1999};

    /**
     * 用 pc1 初始化新对象 pc2。
     *
     * 注意：
     * pc2 是新对象。
     *
     * 所以这里调用的是拷贝构造函数，
     * 而不是赋值运算符函数。
     *
     * 等价写法：
     * Computer pc2{pc1};
     */
    Computer pc2 = pc1;

    /*
     * 因为拷贝构造函数中做了深拷贝，
     * 所以 pc1 和 pc2 各自拥有独立的 m_brand 内存。
     *
     * pc2 可以正常打印：
     * xiaomi 1999
     */
    pc2.print();

    /*
     * test1 结束时：
     *
     * pc2 先析构，
     * 释放 pc2 自己的 m_brand。
     *
     * pc1 后析构，
     * 释放 pc1 自己的 m_brand。
     *
     * 因为是深拷贝，
     * 它们释放的是不同的堆内存，
     * 不会重复释放。
     */
}

void test2()
{
    /**
     * 测试赋值运算符函数
     *
     * 创建 pc1：
     * m_brand 指向保存 "xiaomi" 的堆内存。
     */
    Computer pc1{"xiaomi", 1999};

    /**
     * 创建 pc2：
     * m_brand 指向保存 "huawei" 的堆内存。
     */
    Computer pc2{"huawei", 6999};

    /**
     * 对已经存在的两个对象进行赋值。
     *
     * pc2 = pc1;
     *
     * 注意：
     * pc1 和 pc2 都已经存在，
     * 所以这里调用的是赋值运算符函数 operator=，
     * 不是拷贝构造函数。
     *
     * 执行过程：
     * 1. 判断是否自赋值
     *    pc2 和 pc1 不是同一个对象，
     *    所以继续执行。
     * 2. 释放 pc2 原来保存 "huawei" 的堆内存
     * 3. 为 pc2 重新申请一块新内存
     * 4. 把 pc1 中的 "xiaomi" 拷贝到 pc2 的新内存中
     * 5. 把 pc1 的价格 1999 赋值给 pc2
     *
     * 最终：
     * pc2 的内容变成 "xiaomi", 1999。
     */
    pc2 = pc1;

    /*
     * 输出：
     * xiaomi 1999
     */
    pc2.print();

    /*
     * test2 结束时：
     *
     * pc2 析构，释放自己新申请的 "xiaomi" 内存。
     * pc1 析构，释放自己原本的 "xiaomi" 内存。
     *
     * 注意：
     * 虽然两个字符串内容都叫 "xiaomi"，
     * 但它们在堆区是两块不同的内存。
     *
     * 所以不会重复释放。
     */
}

int main(int argc, char * argv[])
{
    // test1 演示拷贝构造函数
    /* test1(); */

    // test2 演示赋值运算符函数
    test2();

    return 0;
}