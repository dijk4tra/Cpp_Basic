#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/*
 * 静态数据成员 static data member
 *
 * 在类中，使用 static 修饰的数据成员，
 * 叫做静态数据成员。
 *
 * 语法：
 *
 * class 类名
 * {
 * public:
 *     static 数据类型 静态成员名;
 * };
 *
 *
 * 静态数据成员的特点：
 *
 * 1. 静态数据成员不依赖于对象，而是依赖于类
 *
 *    普通数据成员属于具体对象。
 *
 *    例如：
 *    MyClass obj;
 *    obj.m_x;
 *
 *    m_x 是 obj 这个对象自己的成员。
 *
 *    但是 static 数据成员属于类本身。
 *
 *    例如：
 *    MyClass::m_data;
 *
 *    即使没有创建对象，
 *    也可以通过类名访问静态数据成员。
 *
 *
 * 2. 静态数据成员不占据对象的内存大小
 *
 *    普通数据成员存放在每个对象内部。
 *
 *    但是静态数据成员不存放在某个对象内部，
 *    它在内存中只有一份，
 *    所以不会影响 sizeof(对象) 的大小。
 *
 *
 * 3. 静态数据成员一般通过类名作用域访问
 *
 *    推荐写法：
 *
 *    MyClass::m_data
 *
 *    虽然也可以通过对象访问：
 *
 *    obj.m_data
 *
 *    但是这种写法容易让人误以为 m_data 属于 obj，
 *    所以不推荐。
 *
 *
 * 4. 静态数据成员被所有对象共享
 *
 *    因为静态数据成员在内存中只有一份，
 *    所以所有对象访问的是同一个变量。
 *
 *    一个对象修改了静态数据成员，
 *    其他对象看到的也是修改后的值。
 *
 *
 * 5. 静态数据成员通常需要在类外进行定义和初始化
 *
 *    类中写：
 *
 *    static int m_data;
 *
 *    这只是声明，表示 MyClass 类中有一个静态成员 m_data。
 *
 *    类外还要写：
 *
 *    int MyClass::m_data = 1;
 *
 *    这才是真正给静态成员分配存储空间并初始化。
 *
 *
 * 6. 静态数据成员不能使用构造函数初始化列表初始化
 *
 *    因为初始化列表初始化的是“对象自己的成员”。
 *
 *    而 static 成员属于类，
 *    不属于某一个对象。
 *
 *    所以不能写：
 *
 *    MyClass(int a)
 *    : m_data(a)
 *    {
 *    }
 *
 *    这种写法是错误的。
 */

class MyClass
{
public:
    /*
     * 构造函数初始化列表不能初始化静态数据成员。
     *
     * 原因：
     * 初始化列表是用来初始化当前对象中的非静态成员的。
     *
     * m_data 是 static 成员，
     * 它不属于某一个对象，
     * 所以不能出现在初始化列表中。
     */
    /*
    MyClass(int a)
    : m_data(a) // error
    {

    }
    */

    // 静态数据成员
    //
    // 这只是类内声明。
    //
    // 它告诉编译器：
    // MyClass 类中有一个静态 int 成员 m_data。
    //
    // 注意：
    // 这里一般不是定义，也没有真正分配存储空间。
    static int m_data;
};

// 类外初始化静态数据成员
//
// 格式：
// 数据类型 类名::静态成员名 = 初始值;
//
// 这里才是真正定义 MyClass::m_data，
// 并给它初始化为 1。
//
// :: 是作用域限定符，
// 表示 m_data 是 MyClass 类作用域中的成员。
int MyClass::m_data = 1;

void test1()
{
    /*
     * 访问静态数据成员。
     *
     * 推荐通过类名作用域访问：
     *
     * MyClass::m_data
     *
     * 此时还没有创建任何 MyClass 对象，
     * 但是依然可以访问 m_data。
     *
     * 原因：
     * m_data 属于类，不属于某个对象。
     */
    cout << MyClass::m_data << endl;

    cout << "------"<< endl;

    /*
     * 修改静态数据成员。
     *
     * 因为 m_data 只有一份，
     * 所以这里修改的是所有对象共享的那一份数据。
     */
    MyClass::m_data = 2;

    // 创建三个 MyClass 对象
    MyClass obj;
    MyClass obj2;
    MyClass obj3;

    /*
     * 虽然可以通过对象访问 static 成员，
     * 但是不推荐。
     *
     * 因为 obj.m_data、obj2.m_data、obj3.m_data
     * 实际访问的都是同一个 MyClass::m_data。
     *
     * 所以下面三行都会输出 2。
     */
    cout << obj.m_data << endl;
    cout << obj2.m_data << endl;
    cout << obj3.m_data << endl;

    /*
     * 获取对象大小。
     *
     * MyClass 中只有一个 static int m_data，
     * 没有普通非静态数据成员。
     *
     * static 成员不占对象本身的内存。
     *
     * 所以 MyClass 对象本身相当于是空对象。
     *
     * C++ 中空对象大小通常是 1，
     * 用来保证每个对象都有唯一地址。
     */
    cout << sizeof(obj) << endl;
}


class Student
{
public:
    /*
     * Student 构造函数
     *
     * 参数：
     * id：学生编号
     * name：学生姓名
     *
     * 创建一个 Student 对象时，
     * m_id 和 m_name 分别保存每个学生自己的信息。
     */
    Student(int id, string name)
    : m_id(id)
    , m_name(name)
    {
        /*
         * 统计学生对象数量。
         *
         * 每创建一个 Student 对象，
         * 构造函数就会执行一次。
         *
         * 所以在构造函数中执行：
         *
         * m_count++;
         *
         * 就可以统计一共创建了多少个 Student 对象。
         *
         * m_count 是 static 成员，
         * 所有 Student 对象共享同一个 m_count。
         */
        m_count++;
    }

    // 普通成员函数
    // 打印学生编号、姓名和班级编号
    void print()
    {
        /*
         * m_id 和 m_name 是普通成员，
         * 每个学生对象都有自己独立的一份。
         *
         * m_classID 是 static 成员，
         * 所有学生对象共享同一个班级编号。
         */
        cout << m_id << " " << m_name << " " << m_classID <<endl;
    }

    // 普通数据成员
    //
    // 每个 Student 对象都有自己独立的 m_id。
    int m_id;

    // 普通数据成员
    //
    // 每个 Student 对象都有自己独立的 m_name。
    string m_name;

    // 静态数据成员
    //
    // 班级编号。
    //
    // 假设所有 Student 对象都属于同一个班级，
    // 那么班级编号不需要每个对象都保存一份。
    //
    // 使用 static 可以让所有对象共享同一个班级编号。
    static int m_classID;

    // 静态数据成员
    //
    // 用来统计一共创建了多少个学生对象。
    //
    // 因为它属于 Student 类本身，
    // 所以无论创建多少个 Student 对象，
    // 它在内存中都只有一份。
    static int m_count;
};

// 类外定义并初始化 Student 的静态数据成员
//
// 班级编号初始化为 10。
int Student::m_classID = 10;

// 学生数量初始为 0。
// 每调用一次 Student 构造函数，m_count 就会加 1。
int Student::m_count = 0;

// 要描述 zs、ls、ww 这 3 个学生，
// 他们是同一个班级的。
void test2()
{
    /*
     * 创建三个 Student 对象。
     *
     * 每个对象都有自己独立的：
     *
     * m_id
     * m_name
     *
     * 但是它们共享同一个：
     *
     * m_classID
     * m_count
     */
    Student s1 { 1, "zs"};
    Student s2 { 2, "ls"};
    Student s3 { 3, "ww"};

    /*
     * 三个学生打印出来的班级编号都是 10。
     *
     * 因为 m_classID 是 static 成员，
     * 所有 Student 对象共享这一份数据。
     */
    s1.print();
    s2.print();
    s3.print();

    /*
     * 一共创建了多少个学生对象。
     *
     * 因为 Student 构造函数执行了 3 次，
     * 所以 Student::m_count 的值是 3。
     *
     * 推荐通过类名访问静态成员：
     *
     * Student::m_count
     */
    cout << Student::m_count << endl;
}

int main(int argc, char * argv[])
{
    // test1 演示静态成员的基本特点
    /* test1(); */

    // test2 演示 static 成员在多个对象之间共享
    test2();

    return 0;
}