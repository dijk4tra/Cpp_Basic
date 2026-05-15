#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;

/**
 * 成员访问运算符的重载：
 *
 * 这里主要学习两个运算符：
 * 1. operator->
 * 2. operator*
 *
 * 对于普通指针来说：
 *
 * Type * p = new Type();
 *
 * 可以通过下面两种方式访问对象成员：
 *
 * 1. 使用 -> 访问成员
 *    p->m_data;
 *    p->func();
 *
 * 2. 使用 * 解引用之后，再通过 . 访问成员
 *    (*p).m_data;
 *    (*p).func();
 *
 * 一般情况下，-> 和 * 是指针相关的操作。
 *
 * 但是如果一个类重载了 operator-> 和 operator*，
 * 那么这个类的对象就可以像指针一样使用。
 *
 * 这种写法常见于智能指针。
 *
 * 自动资源释放：
 *
 * 把堆资源交给一个栈对象管理，
 * 当栈对象生命周期结束时，
 * 会自动调用析构函数释放堆资源。
 *
 * 这就是 RAII 思想：
 * Resource Acquisition Is Initialization
 * 资源获取即初始化。
 */

class Data
{
public:
    /**
     * 构造函数。
     *
     * 创建 Data 对象时调用。
     */
    Data()
    {
        cout << "Data()" << endl;
    }

    /**
     * 普通成员函数。
     *
     * 返回 Data 对象中的 m_data。
     */
    int getData()
    {
        return m_data;
    }

/* private: */
    /**
     * 这里为了测试方便，
     * 暂时把 m_data 放在 public 区域。
     *
     * 如果放在 private 区域，
     * 类外部不能直接访问 m_data。
     */
    int m_data = 1;
};


class MiddleLayer
{
public:
    /**
     * 构造函数。
     *
     * 参数 p 是一个 Data 类型的指针，
     * 指向堆上的 Data 对象。
     *
     * MiddleLayer 接收这个指针之后，
     * 就负责管理这块 Data 资源。
     */
    MiddleLayer(Data * p)
    : m_p(p)
    {
        cout << "MiddleLayer(Data *)" << endl;
    }

    /**
     * 析构函数。
     *
     * MiddleLayer 对象销毁时，
     * 自动释放 m_p 指向的堆资源。
     *
     * 这样外部就不需要手动 delete Data 对象。
     */
    ~MiddleLayer()
    {
        cout << "~MiddleLayer()" << endl;

        /**
         * 释放资源之前先判断 m_p 是否为空。
         *
         * 如果 m_p 不为空，
         * 说明当前对象还管理着一块堆资源，
         * 需要释放。
         */
        if(m_p){
            delete m_p;
            m_p = nullptr;
        }
    }

    /**
     * 重载 operator->。
     *
     * 表达式：
     * ml->getData();
     *
     * 本质上等价于：
     * ml.operator->()->getData();
     *
     * operator-> 的返回值必须是：
     * 1. 指针
     * 或者
     * 2. 重载了 operator-> 的对象
     *
     * 这里返回 Data *，
     * 所以后面可以继续通过 -> 访问 Data 对象的成员。
     */
    Data * operator->()
    {
        return  m_p;
    }

    /**
     * 重载 operator*。
     *
     * 表达式：
     * (*ml).getData();
     *
     * 本质上等价于：
     * ml.operator*().getData();
     *
     * 这里返回 Data &，
     * 表示返回 m_p 指向的 Data 对象本身。
     */
    Data & operator*()
    {
        return *m_p;
    }

private:
    /**
     * 原生指针 / 原始指针 / 裸指针 / 底层指针。
     *
     * m_p 保存 Data 对象的地址。
     *
     * MiddleLayer 负责管理 m_p 指向的堆资源，
     * 并在析构函数中释放它。
     */
    Data * m_p;
};

/**
 * 定义一个第三层结构。
 *
 * ThirdLayer 管理的是 MiddleLayer 对象，
 * MiddleLayer 又管理 Data 对象。
 *
 * 所以对象关系为：
 *
 * ThirdLayer
 *     -> MiddleLayer
 *          -> Data
 *
 * 这种结构用来演示：
 * operator-> 可以连续递归调用。
 */
class ThirdLayer
{
public:
    /**
     * 构造函数。
     *
     * 参数 m_p 是一个 MiddleLayer 类型的指针，
     * 指向堆上的 MiddleLayer 对象。
     *
     * ThirdLayer 接收这个指针后，
     * 就负责管理这个 MiddleLayer 对象。
     */
    ThirdLayer(MiddleLayer * m_p)
    : m_pml(m_p)
    {
        cout << "ThirdLayer(MiddleLayer*)" << endl;
    }

    /**
     * 析构函数。
     *
     * ThirdLayer 对象销毁时，
     * 自动释放它管理的 MiddleLayer 对象。
     *
     * MiddleLayer 被释放时，
     * 又会调用 MiddleLayer 的析构函数，
     * 进而释放 MiddleLayer 管理的 Data 对象。
     */
    ~ThirdLayer()
    {
        cout << "~ThirdLayer()" << endl;

        if(m_pml){
            delete m_pml;
            m_pml = nullptr;
        }
    }

    /**
     * 重载 operator->。
     *
     * 表达式：
     * tl->getData();
     *
     * 首先会调用：
     * tl.operator->()
     *
     * 这里返回 MiddleLayer &。
     *
     * 因为 MiddleLayer 本身也重载了 operator->，
     * 所以编译器会继续调用 MiddleLayer 的 operator->，
     * 最终拿到 Data *，
     * 再调用 Data 的 getData()。
     *
     * 调用过程：
     * tl.operator->()
     * -> MiddleLayer 对象
     * -> MiddleLayer::operator->()
     * -> Data *
     * -> getData()
     */
    MiddleLayer & operator->()
    {
        return *m_pml;
    }

    /**
     * 重载 operator*。
     *
     * 表达式：
     * *tl
     *
     * 本质上等价于：
     * tl.operator*()
     *
     * 当前版本返回 MiddleLayer &，
     * 所以如果想访问 Data 的成员，
     * 还需要再对 MiddleLayer 解引用一次。
     *
     * 也就是：
     * (*(*tl)).getData();
     */
    MiddleLayer & operator*()
    {
        return *m_pml;
    }

    /**
     * 如果希望对 ThirdLayer 对象只解引用一次，
     * 就能直接访问 Data 对象的成员，
     * 可以把 operator* 的返回值改成 Data &。
     *
     * 因为：
     * *m_pml 会调用 MiddleLayer 的 operator*，
     * 得到 Data &。
     *
     * 这样就可以写成：
     * (*tl).getData();
     */
    /* Data & operator*() */
    /* { */
    /*     return **m_pml; */
    /* } */

private:
    /**
     * 保存 MiddleLayer 对象的地址。
     *
     * ThirdLayer 负责管理这个 MiddleLayer 对象。
     */
    MiddleLayer * m_pml;
};

// 让第三层对象作为管理者对象
void test1()
{
    /**
     * 原本可以直接创建 MiddleLayer 对象管理 Data 资源。
     *
     * MiddleLayer ml { new Data{} };
     */

    /**
     * 现在创建 ThirdLayer 对象，
     * 让 ThirdLayer 管理 MiddleLayer，
     * 再让 MiddleLayer 管理 Data。
     *
     * 资源管理链条：
     *
     * tl 管理 MiddleLayer
     * MiddleLayer 管理 Data
     *
     * 当 tl 生命周期结束时：
     * 1. 调用 ThirdLayer 析构函数
     * 2. delete MiddleLayer
     * 3. 调用 MiddleLayer 析构函数
     * 4. delete Data
     */
    ThirdLayer tl {new MiddleLayer{ new Data{} }};

    /**
     * 通过 tl 对象访问最终被管理的 Data 对象中的 getData 函数。
     */

    /**
     * operator-> 的完整调用过程：
     *
     * tl.operator->()
     * 返回 MiddleLayer &
     *
     * 再调用 MiddleLayer 的 operator->()
     * 返回 Data *
     *
     * 最后通过 Data * 调用 getData()
     *
     * 即：
     * tl.operator->().operator->()->getData();
     */
    tl.operator->().operator->()->getData();

    /**
     * 简写形式：
     *
     * tl->getData();
     *
     * 虽然 tl 的 operator-> 返回的是 MiddleLayer &，
     * 不是 Data *，
     * 但是 MiddleLayer 又重载了 operator->。
     *
     * 所以编译器会继续调用，
     * 直到最终得到一个真正的指针 Data *。
     */
    tl->getData();


    cout << "----------" << endl;

    /**
     * operator* 的完整调用过程：
     *
     * tl.operator*()
     * 返回 MiddleLayer &
     *
     * 再调用 MiddleLayer 的 operator*()
     * 返回 Data &
     *
     * 最后通过 Data 对象调用 getData()
     *
     * 即：
     * tl.operator*().operator*().getData();
     */
    tl.operator*().operator*().getData();

    /**
     * 简写形式：
     *
     * (*(*tl)).getData();
     *
     * 第一次 *tl：
     * 调用 ThirdLayer::operator*，
     * 得到 MiddleLayer 对象。
     *
     * 第二次 *：
     * 调用 MiddleLayer::operator*，
     * 得到 Data 对象。
     *
     * 最后通过 Data 对象调用 getData()。
     */
    (*(*tl)).getData();

    /**
     * 如果希望解引用一次就能访问 getData()，
     * 可以修改 ThirdLayer 的 operator*，
     * 让它直接返回 Data &。
     *
     * 这样就可以写成：
     * (*tl).getData();
     */
    /* (*tl).getData(); */
}

int main(int argc, char * argv[])
{
    test1();

    return 0;
}