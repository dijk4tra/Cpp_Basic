#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/**
 * 嵌套类 Nested Class：
 *
 * 嵌套类就是把一个类定义在另一个类的内部。
 *
 * 例如：
 * class Outer
 * {
 *     class Inner
 *     {};
 * };
 *
 * 其中：
 * Outer 是外部类，
 * Inner 是嵌套在 Outer 中的内部类。
 *
 * 嵌套类的作用：
 *
 * 1. 表示一种从属关系
 *    内部类通常只为外部类服务。
 *
 * 2. 增强封装性
 *    可以把内部类放在 private 区域，
 *    这样外界无法直接使用这个内部类。
 *
 * 3. 减少命名空间污染
 *    如果某个类只在另一个类内部使用，
 *    就没必要定义在全局作用域中。
 *
 * 注意：
 * 嵌套类只是定义在外部类的作用域里面，
 * 并不代表内部类对象自动拥有外部类对象。
 *
 * 如果内部类想访问某个外部类对象的成员，
 * 仍然需要拿到外部类对象或者外部类对象的指针/引用。
 */

// --- 示例 1: 基础语法与访问权限 ---
class Outer
{
private:
    // 外部类的 private 成员变量
    int m_outer_data = 10;

    /**
     * 私有内部类。
     *
     * Inner 定义在 Outer 的 private 区域，
     * 所以只能在 Outer 类的内部使用。
     *
     * 类外部不能写：
     * Outer::Inner in;
     */
    class Inner
    {
    public:
        /**
         * 内部类的成员函数。
         *
         * 参数 o 是一个 Outer 对象的引用。
         *
         * 因为嵌套类本身并不自动绑定某个 Outer 对象，
         * 所以如果想访问 Outer 对象的数据，
         * 需要通过参数传入 Outer 对象。
         */
        void display(Outer& o)
        {
            /**
             * C++11 之后，
             * 嵌套类的成员函数可以访问外部类的 private 成员。
             *
             * 这里通过 o.m_outer_data，
             * 访问传入的 Outer 对象的私有成员。
             */
            cout << "Inner 访问 Outer 的私有成员: "
                 << o.m_outer_data << endl;
        }
    };

public:
    /**
     * 公有内部类。
     *
     * Inner2 定义在 Outer 的 public 区域，
     * 所以类外部可以通过：
     *
     * Outer::Inner2
     *
     * 来访问这个内部类类型。
     */
    class Inner2
    {
    public:
        void func()
        {
            cout << "Inner2 (Public) 的方法被调用" << endl;
        }
    };

    /**
     * 外部类的普通成员函数。
     *
     * 因为 useInner 是 Outer 的成员函数，
     * 所以它可以直接使用 private 区域中的 Inner 类型。
     */
    void useInner()
    {
        /**
         * 在 Outer 内部创建私有内部类对象。
         *
         * 类外部不能直接创建 Inner 对象，
         * 但是 Outer 自己的成员函数可以。
         */
        Inner in;

        /**
         * *this 表示当前 Outer 对象。
         *
         * 把当前对象传给 Inner::display，
         * 让内部类函数访问当前 Outer 对象的成员。
         */
        in.display(*this);
    }
};

// --- 示例 2: 实际场景（汽车与引擎） ---
class Car
{
private:
    /**
     * Engine 作为 Car 的内部类。
     *
     * 从语义上看：
     * 引擎是汽车内部的组成部分，
     * 主要为 Car 类服务。
     *
     * 因此可以把 Engine 定义成 Car 的 private 嵌套类，
     * 不对外暴露具体实现。
     */
    class Engine
    {
    public:
        /**
         * 启动引擎。
         */
        void start()
        {
            cout << "引擎启动：轰隆隆..." << endl;
        }

        /**
         * 设置引擎功率。
         */
        void setPower(int p)
        {
            m_power = p;
        }

    private:
        // 引擎功率，默认值为 150
        int m_power = 150;
    };

    /**
     * Car 中包含一个 Engine 对象。
     *
     * 这是组合关系：
     * Car 对象内部拥有一个 Engine 对象。
     */
    Engine m_engine;

    // 汽车品牌
    string m_brand;

public:
    /**
     * Car 构造函数。
     *
     * 用 brand 初始化汽车品牌。
     */
    Car(string brand)
    : m_brand(brand)
    {}

    /**
     * 开车函数。
     *
     * 外界只需要调用 drive，
     * 不需要关心 Engine 的具体实现。
     */
    void drive()
    {
        cout << m_brand << " 准备出发：" << endl;

        /**
         * Car 自己可以访问 private 内部类 Engine，
         * 也可以调用 m_engine 的成员函数。
         */
        m_engine.start();

        cout << "驾驶中..." << endl;
    }
};

// --- 示例 3: 自定义数据结构 - 简易单向链表 ---
class LinkedList
{
private:
    /**
     * Node 是链表节点类型。
     *
     * Node 只为 LinkedList 服务，
     * 外界不需要直接操作 Node。
     *
     * 所以把 Node 定义成 LinkedList 的 private 嵌套结构体，
     * 可以隐藏链表内部实现细节。
     */
    struct Node
    {
        // 节点保存的数据
        int value;

        // 指向下一个节点的指针
        Node* next;

        /**
         * Node 构造函数。
         *
         * val 初始化节点数据，
         * next 初始化为空指针。
         */
        Node(int val)
        : value(val)
        , next(nullptr)
        {}
    };

    /**
     * 链表头指针。
     *
     * head 指向链表中的第一个节点。
     * 如果 head 为 nullptr，
     * 表示链表为空。
     */
    Node* head;

public:
    /**
     * LinkedList 构造函数。
     *
     * 创建空链表，
     * 所以 head 初始化为 nullptr。
     */
    LinkedList()
    : head(nullptr)
    {}

    /**
     * 头插法添加节点。
     *
     * 每次新节点都会插入到链表头部。
     */
    void add(int val)
    {
        /**
         * 在堆上创建一个新的 Node 节点。
         *
         * newNode 指向这个新节点。
         */
        Node* newNode = new Node(val);

        /**
         * 让新节点的 next 指向原来的头节点。
         *
         * 如果原链表为空，
         * head 为 nullptr，
         * 那么 newNode->next 也就是 nullptr。
         */
        newNode->next = head;

        /**
         * 更新 head。
         *
         * 让 head 指向新节点，
         * 新节点就成为链表新的第一个节点。
         */
        head = newNode;

        cout << "添加节点: " << val << endl;
    }

    /**
     * 遍历并打印链表。
     */
    void show()
    {
        /**
         * curr 用来遍历链表。
         *
         * 初始时指向头节点。
         */
        Node* curr = head;

        /**
         * 只要 curr 不为空，
         * 就说明当前还有节点可以访问。
         */
        while (curr)
        {
            cout << curr->value << " -> ";

            // 移动到下一个节点
            curr = curr->next;
        }

        cout << "NULL" << endl;
    }

    /**
     * 析构函数。
     *
     * LinkedList 中的节点是通过 new 创建的，
     * 所以链表对象销毁时，
     * 需要释放所有节点。
     */
    ~LinkedList()
    {
        /**
         * 只要 head 不为空，
         * 就不断删除头节点。
         */
        while (head)
        {
            /**
             * 先保存当前头节点地址。
             *
             * 因为后面 head 会移动到下一个节点，
             * 如果不保存，就找不到当前节点了。
             */
            Node* temp = head;

            /**
             * head 后移到下一个节点。
             */
            head = head->next;

            /**
             * 删除原来的头节点。
             */
            delete temp;
        }
    }
};

// --- 测试函数 ---
void test1()
{
    cout << "--- Test 1: 基础嵌套类 ---" << endl;

    /**
     * 创建 Outer 对象。
     */
    Outer myOuter;

    /**
     * 通过 Outer 的 public 成员函数，
     * 间接使用 private 内部类 Inner。
     */
    myOuter.useInner();

    /**
     * 访问 public 内部类。
     *
     * Inner2 是 Outer 的 public 嵌套类，
     * 所以可以在类外部通过：
     *
     * Outer::Inner2
     *
     * 定义对象。
     */
    Outer::Inner2 in2;
    in2.func();

    /**
     * Inner 是 private 内部类，
     * 外界无法直接访问。
     *
     * 所以下面这行代码如果打开，
     * 会编译报错。
     */
    // Outer::Inner in1; // 错误！Inner 是 private，外界无法访问
}

void test2()
{
    cout << "\n--- Test 2: 汽车场景 ---" << endl;

    /**
     * 创建 Car 对象。
     *
     * 外界只需要知道 Car，
     * 不需要知道 Car 内部的 Engine 细节。
     */
    Car myCar("Tesla");

    /**
     * 调用 drive。
     *
     * drive 内部会启动引擎。
     */
    myCar.drive();

    /**
     * Engine 是 Car 的 private 内部类，
     * 外界无法直接创建 Engine 对象。
     *
     * 这样可以隐藏 Car 的内部实现，
     * 保护封装性。
     */
    // Car::Engine e; // 错误！Engine 被隐藏在 Car 内部，保护了封装性
}

void test3()
{
    cout << "\n--- Test 3: 简易单向链表场景 ---" << endl;

    /**
     * 创建一个空链表。
     */
    LinkedList list;

    /**
     * 依次向链表中添加节点。
     *
     * 当前 add 使用的是头插法，
     * 所以添加顺序是 10、20、30，
     * 实际链表顺序是：
     *
     * 30 -> 20 -> 10 -> NULL
     */
    list.add(10);
    list.add(20);
    list.add(30);

    /**
     * 打印链表内容。
     */
    list.show();
}

int main(int argc, char * argv[])
{
    test1();
    test2();
    test3();

    return 0;
}