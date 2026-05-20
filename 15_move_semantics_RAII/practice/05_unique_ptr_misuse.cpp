#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// ============================================================
// test1: 误用：拷贝 unique_ptr
// ============================================================
void test1()
{
    cout << "\n[test1] unique_ptr 不能拷贝，只能移动" << endl;

    unique_ptr<int> p1 = make_unique<int>(10);

    // unique_ptr<int> p2 = p1; // 错误：unique_ptr 是独占所有权，不能拷贝
    unique_ptr<int> p2 = move(p1); // 正确：使用 std::move 转移所有权

    if(!p1){
        cout << "p1已经失去所有权" << endl;
    }
    cout << "p2 = " << *p2 << endl;
}

// ============================================================
// test2: 误用：move 后继续使用原 unique_ptr
// ============================================================
void test2()
{
    cout << "\n[test2] unique_ptr move 后不要再解引用原指针" << endl;

    unique_ptr<int> p = make_unique<int>(20);
    unique_ptr<int> p2 = move(p);

    // cout << *p << endl; // 错误：p 已经被 move，通常为空

    // 使用前先判断
    if (p) {
        cout << *p << endl;
    } else {
        cout << "p 已经为空，不能再解引用" << endl;
    }

    cout << "p2 = " << *p2 << endl;
}

// ============================================================
// test3: 误用：用同一个裸指针构造多个 unique_ptr
// ============================================================
void test3()
{
    cout << "\n[test3] 不要用同一个裸指针构造多个 unique_ptr" << endl;
    
    // 错误：p1 和 p2 都认为自己拥有 raw，会 double delete
    /*
    int* raw = new int(30);
    unique_ptr<int> p1(raw);
    unique_ptr<int> p2(raw);
    */

    // 正确用法：直接使用 make_unique
    auto p = make_unique<int>(30);
    cout << "p = " << *p << endl; 
}

// ============================================================
// test4: 误用：对 get() 返回的裸指针手动 delete
// ============================================================
void test4() 
{
    cout << "\n[test4] 不要 delete unique_ptr::get() 返回的指针" << endl;

    auto p = make_unique<int>(40);

    int* raw = p.get();
    // delete raw; // 错误：double free

    // 正确用法：只使用，不释放
    cout << "raw = " << *raw << endl;
}

// ============================================================
// test5: 误用：函数只是读取对象，却用 unique_ptr 参数接管所有权
// ============================================================
void printWrong(unique_ptr<int> p) {
    cout << "value = " << *p << endl;
}

void printRight(const int& value) {
    cout << "value = " << value << endl;
}

void test5()
{
    cout << "\n[test5] 只读访问不应该传 unique_ptr" << endl;

    auto p = make_unique<int>(50);

    // 不推荐：只是打印，却转移了所有权
    // printWrong(move(p));
    // 此后 p 为空

    // 正确：只读访问传引用
    printRight(*p);
    cout << "p 仍然拥有对象: " << *p << endl;
}

// ============================================================
// test6: 正确场景：函数确实需要接管 unique_ptr 所有权
// ============================================================
class UniqueManager {
public:
    void add(unique_ptr<int> p) {
        m_data.push_back(move(p));
    }

    void print() const {
        for (const auto& p : m_data){
            cout << *p << " ";
        }
        cout << endl;
    }

private:
    vector<unique_ptr<int>> m_data;
};

void test6()
{
    cout << "\n[test6] 正确使用：unique_ptr 表示转移所有权" << endl;

    UniqueManager manager;

    auto p = make_unique<int>(60);

    manager.add(move(p));

    if(!p){
        cout << "p 的所有权已经转移给 manager" << endl;
    }

    manager.print();
}

// ============================================================
// test7: 误用：release 后忘记 delete
// ============================================================
void test7()
{
    cout << "\n[test7] release 后必须手动管理资源" << endl;

    auto p = make_unique<int>(70);

    // 错误：release 后如果不 delete，会内存泄漏
    /*
    int* raw = p.release();
    // 忘记 delete raw;
    */

    // 正确：除非必须和 C API 对接，否则尽量不用 release
    int* raw = p.release();
    cout << "raw = " << *raw << endl;
    delete raw;
    raw = nullptr;
}


int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();

    return 0;
}
