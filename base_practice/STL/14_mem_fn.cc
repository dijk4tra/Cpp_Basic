#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

// 定义一个简单的类
class Widget {
public:
    Widget(int id) : id_(id) {}

    // 无参数的成员函数
    void show() const {
        cout << "Widget ID: " << id_ << endl;
    }

    // 带参数的成员函数
    void update(int factor) {
        id_ *= factor;
        cout << "Widget updated to ID: " << id_ << endl;
    }

private:
    int id_;
};

int main() {
    // ====================================================
    // 1. 使用 mem_fn 包装成员函数指针，生成新的函数对象
    // ====================================================
    auto show_wrapper = mem_fn(&Widget::show);
    auto update_wrapper = mem_fn(&Widget::update);

    Widget w(10);

    cout << "--- 基础调用演示 ---" << endl;
    // ====================================================
    // 2. 进行调用：满足显式传递对象的需求
    // ====================================================
    
    // ① 通过【对象引用/值】调用
    show_wrapper(w);           // 等价于 w.show();
    update_wrapper(w, 2);      // 等价于 w.update(2);

    // ② 通过【裸指针】调用 （mem_fn 会自动解引用）
    Widget* w_ptr = &w;
    show_wrapper(w_ptr);       // 等价于 w_ptr->show();

    // ③ 通过【智能指针】调用 （同样完美支持！）
    auto w_smartptr = make_shared<Widget>(100);
    show_wrapper(w_smartptr);  // 等价于 w_smart->show();

    cout << "\n--- 在 STL 算法中的高级应用 ---" << endl;
    // ====================================================
    // 3. 为什么用 mem_fn？配合 STL 算法极其优雅
    // ====================================================
    vector<Widget> widget_list = { Widget(1), Widget(2), Widget(3) };

    // 以前需要写复杂的 Lambda 表达式：[](const Widget& obj) { obj.show(); }
    // 现在直接把 mem_fn 生成的函数对象传进去即可
    for_each(widget_list.begin(), widget_list.end(), mem_fn(&Widget::show));

    return 0;
}