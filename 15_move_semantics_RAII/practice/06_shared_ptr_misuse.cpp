#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// ============================================================
// test1: 误用：用同一个裸指针创建多个 shared_ptr
// ============================================================
void test1() {
    cout << "\n[test1] 不要用同一个裸指针创建多个 shared_ptr\n";

    // 错误：p1 和 p2 有不同的控制块，会 double delete
    /*
    int* raw = new int(10);
    shared_ptr<int> p1(raw);
    shared_ptr<int> p2(raw);
    */

    // 正确写法
    // 使用 make_shared
    auto p1 = make_shared<int>(10);
    // 通过拷贝 shared_ptr 共享同一个控制块
    shared_ptr<int> p2 = p1;

    cout << "p1 = " << *p1 << endl;
    cout << "p2 = " << *p2 << endl;
    cout << "use_count = " << p1.use_count() << endl;
}

// ============================================================
// test2: 误用：从 shared_ptr::get() 创建新的 shared_ptr
// ============================================================
void test2()
{
    cout << "\n[test2] 不要从 shared_ptr::get() 再创建 shared_ptr\n";

    auto p1 = make_shared<int>(20);

    int* raw = p1.get();

    // 错误：p2 会创建新的控制块，导致 double delete
    // shared_ptr<int> p2(raw);

    // 正确：直接拷贝 shared_ptr
    shared_ptr<int> p2 = p1;

    cout << "p1 = " << *p1 << endl;
    cout << "p2 = " << *p2 << endl;
    cout << "use_count = " << p1.use_count() << endl;
}

// ============================================================
// test3: 误用：只读访问却传 shared_ptr，造成不必要的引用计数变化
// ============================================================
struct Config {
    int timeout = 30;
};

// 误用：只是读取 Config，却传 shared_ptr，导致临时增加引用计数
void useConfigWrong(shared_ptr<Config> config) {
    cout << "inside useConfigWrong, use_count = "
         << config.use_count() << endl;

    cout << "timeout = " << config->timeout << endl;
}

// 正确：只读访问传 const 引用，不涉及 shared_ptr 引用计数
void useConfigRight(const Config& config) {
    cout << "inside useConfigRight, no shared_ptr copy\n";
    cout << "timeout = " << config.timeout << endl;
}

void test3() {
    cout << "\n[test3] 只读访问不应该传 shared_ptr\n";
    
    auto config = make_shared<Config>();

    cout << "before useConfigWrong, use_count = " << config.use_count() << endl;

    // 不推荐：只是读取，却临时增加了一次引用计数，导致不必要的开销
    useConfigWrong(config);
    cout << "after useConfigWrong, use_count = " << config.use_count() << endl;

    // 正确：只读访问传引用
    useConfigRight(*config);
}

// ============================================================
// test4: 误用：shared_ptr 循环引用导致对象无法释放
// ============================================================
struct B;

struct A 
{
    shared_ptr<B> b;

    ~A() 
    {
        cout << "A destroyed\n";
    }
};

struct B 
{
    // 错误写法：
    // shared_ptr<A> a;

    // 正确写法：一端改成 weak_ptr，避免循环引用
    weak_ptr<A> a;

    ~B() 
    {
        cout << "B destroyed\n";
    }
};

void test4() {
    cout << "\n[test4] 使用 weak_ptr 避免 shared_ptr 循环引用\n";

    auto a = make_shared<A>();
    auto b = make_shared<B>();

    a->b = b;
    b->a = a;

    cout << "a.use_count = " << a.use_count() << endl;
    cout << "b.use_count = " << b.use_count() << endl;

    // test4 结束时，A 和 B 都会被正确释放
}

// ============================================================
// test5: 误用：在类中用 shared_ptr(this)
// ============================================================
class FooWrong {
public:
    shared_ptr<FooWrong> getPtr() {
        // 错误：会创建新的控制块，可能 double delete
            /*
            严重错误：
            this 是一个裸指针。

            如果写成：
                return shared_ptr<FooWrong>(this);

            这会让 shared_ptr 认为：
            “我是这个对象的新主人，我负责 delete 它。”

            但是这个对象可能已经被另一个 shared_ptr 管理了。

            于是就会出现两个 shared_ptr 控制同一个裸指针，
            但是它们的引用计数控制块不同。

            最终两个 shared_ptr 都会 delete this，
            造成 double delete。
        */
        // return shared_ptr<FooWrong>(this);

        return nullptr;
    }
};

class FooRight : public enable_shared_from_this<FooRight> {
public:
    FooRight() {
        cout << "FooRight constructed\n";
    }

    ~FooRight() {
        cout << "FooRight destroyed\n";
    }

    shared_ptr<FooRight> getPtrRight() {
        /*
            shared_from_this() 的作用：
            它不会创建新的控制块。

            它会找到当前对象已经存在的 shared_ptr 控制块，
            然后基于这个控制块生成一个新的 shared_ptr。

            所以 p1 和 p2 共享同一个引用计数。
        */
        return shared_from_this();
    }
};

void test5() {
    cout << "\n[test5] 不要使用 shared_ptr(this)，使用 enable_shared_from_this\n";
    /*
        make_shared<FooRight>() 会做两件事：
        1. 创建 FooRight 对象
        2. 创建 shared_ptr 的控制块
        此时：
            p1.use_count() == 1
    */
    auto p1 = make_shared<FooRight>();
    cout << "创建 p1 后 use_count = " << p1.use_count() << endl;

    /*
        getPtrRight() 内部调用 shared_from_this()
        它返回一个新的 shared_ptr，
        但是这个 shared_ptr 和 p1 共享同一个控制块。

        此时：
            p1 和 p2 都指向同一个 FooRight 对象
            引用计数变为 2
    */
    auto p2 = p1->getPtrRight();
    cout << "创建 p2 后 p1.use_count = " << p1.use_count() << endl;
    cout << "创建 p2 后 p2.use_count = " << p2.use_count() << endl;
    /*
        test5 结束时：
        p2 先析构，引用计数从 2 变成 1
        p1 再析构，引用计数从 1 变成 0
        FooRight 对象被释放

        所以只会释放一次，这是正确的。
    */
}

// ============================================================
// test6: 误用：在构造函数中调用 shared_from_this()
// ============================================================
class InitWrong : public enable_shared_from_this<InitWrong> {
public:
    InitWrong() {
        cout << "InitWrong constructor\n";
        // 错误：构造函数中对象还没有被 shared_ptr 完整管理
        /*
            错误原因：
            shared_from_this() 依赖对象已经被 shared_ptr 管理。

            但是构造函数执行时，
            当前对象还没有完全交给 shared_ptr 管理。

            所以这里调用 shared_from_this() 是错误的。

            轻则抛出 std::bad_weak_ptr，
            重则导致未定义行为。
        */
        // auto self = shared_from_this();
    }
};

// 正确示例：使用工厂函数 create()
class InitRight : public enable_shared_from_this<InitRight> {
public:
    /*
        使用 static create() 的目的：
        1. 先创建对象
        2. 让 shared_ptr 管理对象
        3. 再调用 init()

        这样 init() 里面调用 shared_from_this() 就是安全的。
    */
    static shared_ptr<InitRight> create() {
        /*
            注意：
            这里不用 make_shared 是因为构造函数是 private 的。

            private 构造函数的作用是：
            防止别人直接写 InitRight obj;
            或者直接 new InitRight。

            这样可以强制用户必须通过 create() 创建对象。
        */
        auto p = shared_ptr<InitRight>(new InitRight());
        
        /*
            到这里，p 已经是一个合法的 shared_ptr。
            InitRight 对象已经被 shared_ptr 管理。
            所以现在调用 init() 是安全的。
        */
        p->init();
        return p;
    }

    void init() {
        /*
            现在可以安全调用 shared_from_this()。
            self 和 create() 中的 p 共享同一个控制块。
            调用 shared_from_this() 后：
                use_count 会临时加 1
        */
        auto self = shared_from_this();
        cout << "InitRight init success\n";
        cout << "init() 中 self.use_count = " << self.use_count() << endl;
    }

private:
    InitRight() {
        cout << "InitRight constructor\n";
    }
};

void test6() {
    cout << "\n[test6] 不要在构造函数中调用 shared_from_this\n";

    /*
        只能通过 create() 创建 InitRight 对象。

        create() 内部保证：
        对象先被 shared_ptr 管理，
        然后才调用 init()。
    */
    auto p = InitRight::create();

    /*
        init() 结束后，局部变量 self 被销毁。
        所以这里一般只剩 p 一个 shared_ptr 持有对象。
        因此 use_count == 1。
    */
    cout << "create() 返回后 p.use_count = " << p.use_count() << endl;
}

// ============================================================
// test7: 误用：数组使用 shared_ptr<T> 管理
// ============================================================
void test7() {
    cout << "\n[test7] 管理数组优先使用 vector 或 unique_ptr<T[]>\n";

    /*
        错误或不推荐写法：
            shared_ptr<int> p(new int[10]);

        问题：
        shared_ptr<int> 看起来像是在管理一个 int，
        但 new int[10] 创建的是一个数组。

        数组应该使用 delete[] 释放，
        普通对象使用 delete 释放。

        如果删除方式不匹配，就可能出问题。
        所以不推荐这样写。
    */
    // shared_ptr<int> p(new int[10]); // 不推荐

    /*
        推荐方式 1：std::vector
        大多数情况下，只要你想要动态数组，
        首选 vector。

        原因：
        1. 自动管理内存
        2. 知道数组长度
        3. 可以动态扩容
        4. 支持范围 for
        5. 更安全
    */
    vector<int> v(10);
    v[0] = 70;
    v[1] = 71;
    v[2] = 72;
    cout << "vector 内容: ";
    for (int x : v) {
        cout << x << " ";
    }

    /*
        推荐方式 2：unique_ptr<int[]>

        如果你确实只想管理一个动态数组，
        并且不需要 vector 的扩容、size 等功能，
        可以用 unique_ptr<T[]>。

        unique_ptr<int[]> 知道自己管理的是数组，
        析构时会自动调用 delete[]。
    */
    unique_ptr<int[]> arr = make_unique<int[]>(10);
    arr[0] = 80;
    arr[1] = 81;
    arr[2] = 82;
    cout << "unique_ptr<int[]> arr[0] = " << arr[0] << endl;
    cout << "unique_ptr<int[]> arr[1] = " << arr[1] << endl;
    cout << "unique_ptr<int[]> arr[2] = " << arr[2] << endl;
    
    /*
        C++17 起，shared_ptr<T[]> 也可以管理数组：

            shared_ptr<int[]> sp(new int[10]);

        但是实际工程里，数组一般还是优先 vector。

        只有确实需要共享数组所有权时，
        才考虑 shared_ptr<T[]>。
    */
    shared_ptr<int[]> sp(new int[10]);
    sp[0] = 90;
    sp[1] = 91;
    cout << "shared_ptr<int[]> sp[0] = " << sp[0] << endl;
    cout << "shared_ptr<int[]> sp[1] = " << sp[1] << endl;
}

// ============================================================
// test8: 正确场景：shared_ptr 表示共享所有权
// ============================================================
class SharedCache {
public:
    /*
        add 接收 shared_ptr<int>。
        这表示：
        调用者持有一份 shared_ptr，
        cache 内部也要保存一份 shared_ptr。
        所以这是共享所有权。
    */
    void add(shared_ptr<int> p) {
        /*
            push_back(p) 会复制 shared_ptr。
            复制 shared_ptr 不会复制 int 对象本身，
            只会让引用计数 +1。

            也就是说：
            cache_ 里面的 shared_ptr
            和外面的 shared_ptr
            指向同一个 int。
        */
        cache_.push_back(p);
    }

    void print() const {
        for (const auto& p : cache_) {
            cout << *p << " ";
        }
        cout << endl;
    }

private:
    /*
        cache_ 保存多个 shared_ptr<int>。
        只要 cache_ 里还有某个 shared_ptr，
        对应的 int 对象就不会被释放。
    */
    vector<shared_ptr<int>> cache_;
};

void test8() {
    cout << "\n[test8] 正确使用：shared_ptr 表示共享所有权\n";

    SharedCache cache;

    /*
        创建一个 int 对象，由 shared_ptr 管理。
        此时只有 p 一个 shared_ptr 持有这个 int。
        所以：
            p.use_count() == 1
    */
    auto p = make_shared<int>(80);

    cout << "刚创建 p 后 use_count = " << p.use_count() << endl;

    /*
        把 p 加入 cache。

        注意：
        这里没有转移所有权。
        p 仍然可以继续使用。

        cache 内部也保存了一份 shared_ptr。

        所以 add 之后，至少有两个 shared_ptr 指向同一个 int：
            1. test8 里的 p
            2. cache.cache_ 里的元素
    */
    cache.add(p);

    cout << "p 仍然可以使用，*p = " << *p << endl;

    cache.print();
    /*
        test8 结束时：
        1. 局部变量 p 析构，引用计数 -1
        2. cache 析构
        3. cache_ 里的 shared_ptr 析构，引用计数再 -1
        4. 引用计数变成 0
        5. int 对象被释放
    */
}


int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();

    return 0;
}