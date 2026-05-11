#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/*
 * 嵌套类（Nested Class）：
 * 将一个类定义在另一个类的内部。
 *
 * 作用：
 * 1. 表达从属关系：内部类通常只为外部类提供服务。
 * 2. 增强封装性：可以将内部类定义在 private 区域，避免外界直接访问。
 * 3. 减少命名空间污染：避免辅助类暴露到全局作用域中。
 */

// --- 示例 1：基础语法与访问权限 ---
class Outer
{
private:
    int m_outer_data = 10;

    // 1. 私有内部类：只能在 Outer 类内部使用
    class Inner
    {
    public:
        void display(Outer& o) {
            // C++11 之后，嵌套类可以直接访问外部类的私有成员
            // 但仍然需要通过外部类对象来访问非静态成员
            cout << "Inner 访问 Outer 的私有成员: " << o.m_outer_data << endl;
        }
    };

public:
    // 2. 公有内部类：外界可以通过 Outer::Inner2 访问
    class Inner2
    {
    public:
        void func() {
            cout << "Inner2（public）的成员函数被调用" << endl;
        }
    };
    
    void useInner() {
        Inner in; // 外部类内部可以直接创建私有内部类对象
        in.display(*this);
    }
};

// --- 示例 2：实际场景：汽车与引擎 ---
class Car
{
private:
    // Engine 作为 Car 的内部类，体现“隶属”关系，
    // 并且不需要暴露给外界
    class Engine
    {
    public:
        void start() { cout << "引擎启动：轰隆隆..." << endl; }
        void setPower(int p) { m_power = p; }

    private:
        int m_power = 150;
    };

    Engine m_engine; // 外部类中包含内部类对象
    string m_brand;

public:
    Car(string brand) : m_brand(brand) {}

    void drive() {
        cout << m_brand << " 准备出发：" << endl;
        m_engine.start(); // 外部类调用内部类的成员函数
        cout << "驾驶中..." << endl;
    }
};

// --- 示例 3：自定义数据结构：简易单向链表 ---
class LinkedList {
private:
    // Node 只服务于 LinkedList，因此定义为私有嵌套结构体
    struct Node {
        int value;
        Node* next;
        Node(int val) : value(val), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void add(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        cout << "添加节点: " << val << endl;
    }

    void show() {
        Node* curr = head;
        while (curr) {
            cout << curr->value << " -> ";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    }

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// --- 测试函数 ---
void test1()
{
    cout << "--- Test 1: 基础嵌套类 ---" << endl;
    Outer myOuter;
    myOuter.useInner();

    // 访问公有内部类
    Outer::Inner2 in2;
    in2.func();

    // Outer::Inner in1; // 错误！Inner 是 private，外界无法访问
}

void test2()
{
    cout << "\n--- Test 2: 汽车场景 ---" << endl;
    Car myCar("Tesla");
    myCar.drive();
    
    // Car::Engine e; // 错误！Engine 被隐藏在 Car 内部，外界无法直接访问
}

void test3()
{
    cout << "\n--- Test 3: 简易单向链表场景 ---" << endl;
    LinkedList list;
    list.add(10);
    list.add(20);
    list.add(30);
    list.show();
}

int main(int argc, char * argv[])
{
    test1();
    test2();
    test3();
    return 0;
}