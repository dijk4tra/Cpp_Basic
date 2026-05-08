根据提供的头文件标准规范，用所学过的类和对象的知识，封装log4cpp，实现一个单例的效果。能够输出到终端，还能保存到文件。让其使用起来更方便，要求：同时输出的日志信息中最好能有文件的名字，函数的名字及其所在的行号, 完成Mylogger.cc实现文件并进行测试.

// Mylogger.h  头文件
#ifndef __MYLOGGER__HH__ 
#define __MYLOGGER__HH__

#include <log4cpp/Category.hh>
using namespace log4cpp;

// 定义一个宏用于日志拼接
#define addPrefix(msg) // 给出具体实现

#define LogWarn(msg) // 给出具体实现

// 单例模式
class Mylogger
{
public:
    //静态方法获取实例
    static Mylogger * getInstance();
    //静态方法销毁实例
    static void destroyInstance();
    // 删除赋值 赋值
    Mylogger(const Mylogger &) = delete;
    Mylogger & operator=(const Mylogger &) = delete;
    // info
    void info(const char * msg);
    // warn
    void warn(const char * msg);
private:
    Mylogger();
    ~Mylogger();
    static Mylogger * ms_instance;
    Category & m_category;
};

#endif

# 一、整体设计思路

这个作业的核心目标是：

**根据给定头文件，对 log4cpp 进行二次封装，写一个单例模式的日志类 `Mylogger`。**

封装之后，使用日志时不需要每次都写复杂的 log4cpp 配置，只需要这样调用：

```cpp
LogInfo("程序开始运行");
LogWarn("这里可能有问题");
```

日志就可以同时输出到：

1. 终端；
2. 日志文件；
3. 并且日志信息中自动带有文件名、函数名和行号。

例如输出结果可能是：

```text
2026-05-08 10:30:12,123 [INFO] [test.cc:15 main] 程序开始运行
```

其中：

```text
test.cc
```

表示日志所在文件名；

```text
15
```

表示调用日志宏时所在的行号；

```text
main
```

表示调用日志宏时所在的函数名。

---

# 二、为什么要封装 log4cpp？

如果直接使用 log4cpp，每次都要配置很多内容，例如：

```cpp
OstreamAppender
FileAppender
PatternLayout
Category
Priority
```

这些代码比较繁琐，而且每个地方都重复写也不方便维护。

所以我们把这些配置封装到 `Mylogger` 类中。

以后用户只需要调用：

```cpp
LogInfo("xxx");
LogWarn("xxx");
```

内部就会自动完成：

1. 获取日志对象；
2. 拼接文件名、行号、函数名；
3. 输出到终端；
4. 输出到日志文件。

这样使用起来更加简单。

---

# 三、为什么使用单例模式？

日志类非常适合使用单例模式。

所谓单例模式，就是整个程序中只创建一个对象。

对于日志系统来说，通常整个程序只需要一个日志对象。如果到处创建多个日志对象，可能会造成：

1. 重复配置输出器；
2. 重复打开日志文件；
3. 日志格式不统一；
4. 程序结构混乱。

比如如果不使用单例，可能会出现：

```cpp
Mylogger logger1;
Mylogger logger2;
Mylogger logger3;
```

这样显然不合理。

所以我们使用：

```cpp
static Mylogger * getInstance();
```

来获取唯一的日志对象。

---

# 四、带详细注释的 Mylogger.h

```cpp
#ifndef __MYLOGGER__HH__
#define __MYLOGGER__HH__

/*
    引入 log4cpp 的 Category 类。

    Category 可以理解为 log4cpp 中真正负责写日志的对象。
    后面我们会通过 Category 来调用 info()、warn() 等函数。
*/
#include <log4cpp/Category.hh>

/*
    引入 string 头文件。

    因为下面的 addPrefix 宏中使用了：
        std::string
        std::to_string

    std::string 用于字符串拼接。
    std::to_string 用于把整数类型的行号转换成字符串。
*/
#include <string>

/*
    使用 log4cpp 命名空间。

    这样后面可以直接写：
        Category

    而不用写：
        log4cpp::Category

    注意：
    实际项目中一般不建议在头文件中使用 using namespace，
    但是本作业代码中可以按照题目给出的形式保留。
*/
using namespace log4cpp;

/*
    addPrefix(msg)

    这个宏的作用是：
    给用户传入的日志内容 msg 添加前缀信息。

    前缀信息包括：
        1. 当前文件名：__FILE__
        2. 当前行号：__LINE__
        3. 当前函数名：__func__

    例如用户写：
        LogInfo("hello");

    假设这行代码在 test.cc 文件的 main 函数第 20 行，
    那么 addPrefix("hello") 会生成类似这样的字符串：

        [test.cc:20 main] hello

    这里使用的是 std::string 的字符串拼接。

    注意：
    std::string("[") 非常重要。

    因为 __FILE__、"["、":" 这些本质上都是 C 风格字符串，
    C 风格字符串之间不能直接使用 + 进行拼接。

    例如下面这样是错误的：
        "[" + __FILE__

    所以我们先写：
        std::string("[")

    这样第一个字符串就是 std::string 类型，
    后面再使用 +，就表示字符串拼接。

    另外：
        __LINE__

    是一个整数，不能直接和字符串拼接。
    所以需要使用：

        std::to_string(__LINE__)

    把行号转换成字符串。
*/
#define addPrefix(msg) \
    (std::string("[") + __FILE__ + ":" + std::to_string(__LINE__) + \
    " " + __func__ + "] " + msg)

/*
    LogInfo(msg)

    这是给用户使用的 info 级别日志宏。

    用户写：
        LogInfo("程序开始");

    实际展开后大致相当于：
        Mylogger::getInstance()->info(addPrefix("程序开始").c_str());

    它做了三件事：
        1. 调用 Mylogger::getInstance() 获取单例对象；
        2. 调用 addPrefix(msg) 给日志添加文件名、行号、函数名；
        3. 调用 info() 输出 info 级别日志。
*/
#define LogInfo(msg) \
    Mylogger::getInstance()->info(addPrefix(msg).c_str())

/*
    LogWarn(msg)

    这是给用户使用的 warn 级别日志宏。

    用户写：
        LogWarn("发生警告");

    实际展开后大致相当于：
        Mylogger::getInstance()->warn(addPrefix("发生警告").c_str());

    它会输出 warn 级别的日志信息。
*/
#define LogWarn(msg) \
    Mylogger::getInstance()->warn(addPrefix(msg).c_str())

/*
    Mylogger 类

    这是我们自己封装的日志类。
    它内部使用 log4cpp 实现真正的日志输出。
*/
class Mylogger
{
public:
    /*
        getInstance()

        静态成员函数，用来获取 Mylogger 的唯一实例。

        因为构造函数是 private，
        所以外部不能这样创建对象：
            Mylogger logger;

        外部只能这样获取对象：
            Mylogger::getInstance();

        第一次调用 getInstance() 时，会创建对象。
        后面再次调用 getInstance() 时，会返回同一个对象。
    */
    static Mylogger * getInstance();

    /*
        destroyInstance()

        静态成员函数，用来销毁单例对象。

        因为单例对象是通过 new 创建出来的，
        所以程序结束前最好通过 destroyInstance() 释放资源。
    */
    static void destroyInstance();

    /*
        删除拷贝构造函数。

        这样可以防止用户通过拷贝方式创建新的 Mylogger 对象。

        例如下面这种写法会被禁止：
            Mylogger logger2(*Mylogger::getInstance());

        这样可以保证单例对象的唯一性。
    */
    Mylogger(const Mylogger &) = delete;

    /*
        删除赋值运算符。

        这样可以防止用户进行对象赋值。

        例如下面这种写法会被禁止：
            logger1 = logger2;

        这同样是为了保证单例模式不被破坏。
    */
    Mylogger & operator=(const Mylogger &) = delete;

    /*
        info()

        输出 info 级别日志。

        info 一般用于普通提示信息，例如：
            程序启动
            用户登录成功
            文件读取完成
    */
    void info(const char * msg);

    /*
        warn()

        输出 warn 级别日志。

        warn 一般用于警告信息，例如：
            文件不存在
            参数可能不合理
            网络连接较慢
    */
    void warn(const char * msg);

private:
    /*
        构造函数私有化。

        这是单例模式的关键。

        外部不能直接创建 Mylogger 对象，
        只能通过 getInstance() 获取唯一对象。
    */
    Mylogger();

    /*
        析构函数私有化。

        外部不能直接 delete Mylogger 对象，
        只能通过 destroyInstance() 统一销毁。
    */
    ~Mylogger();

private:
    /*
        ms_instance

        静态成员变量，用来保存 Mylogger 唯一对象的地址。

        static 表示它属于类本身，而不是属于某一个具体对象。

        一开始它的值是 nullptr，
        表示还没有创建 Mylogger 对象。
    */
    static Mylogger * ms_instance;

    /*
        m_category

        log4cpp 中真正负责写日志的对象。

        这里使用引用，是因为 Category::getRoot()
        返回的就是一个 Category 引用。
    */
    Category & m_category;
};

#endif
```

---

# 五、带详细注释的 Mylogger.cc

```cpp
/*
    引入自己的头文件。
*/
#include "Mylogger.h"

/*
    引入 log4cpp 中需要使用的组件。
*/
#include <log4cpp/OstreamAppender.hh>   // OstreamAppender：用于输出到终端
#include <log4cpp/FileAppender.hh>      // FileAppender：用于输出到文件
#include <log4cpp/PatternLayout.hh>     // PatternLayout：用于设置日志格式
#include <log4cpp/Priority.hh>          // Priority：用于设置日志级别

#include <iostream>

using std::cout;

/*
    静态成员变量必须在类外进行定义。

    在 Mylogger.h 中只是声明：
        static Mylogger * ms_instance;

    这里才是真正定义并初始化。

    nullptr 表示一开始还没有创建 Mylogger 对象。
*/
Mylogger * Mylogger::ms_instance = nullptr;

/*
    getInstance()

    获取单例对象。

    第一次调用时：
        ms_instance == nullptr

    说明对象还没有创建，于是执行：
        ms_instance = new Mylogger();

    后面再次调用时：
        ms_instance != nullptr

    说明对象已经存在，直接返回之前创建好的对象。

    这样就保证整个程序中只有一个 Mylogger 对象。
*/
Mylogger * Mylogger::getInstance()
{
    if(nullptr == ms_instance)
    {
        ms_instance = new Mylogger();
    }

    return ms_instance;
}

/*
    destroyInstance()

    销毁单例对象。

    如果 ms_instance 不为空，说明之前创建过对象，
    需要使用 delete 释放它。

    delete 之后，把指针重新置为 nullptr，
    可以防止出现野指针。
*/
void Mylogger::destroyInstance()
{
    if(ms_instance)
    {
        delete ms_instance;
        ms_instance = nullptr;
    }
}

/*
    Mylogger 构造函数

    构造函数中完成 log4cpp 的初始化配置。

    这里主要做六件事：
        1. 获取 root Category；
        2. 创建终端输出器；
        3. 创建文件输出器；
        4. 给输出器设置日志格式；
        5. 把输出器添加到 Category；
        6. 设置日志优先级。
*/
Mylogger::Mylogger()
: m_category(Category::getRoot())
{
    /*
        1. 创建终端输出器。

        OstreamAppender 可以把日志输出到一个 ostream 对象中。

        这里传入 &cout，表示输出到标准输出，
        也就是终端。
    */
    OstreamAppender * ostreamAppender =
        new OstreamAppender("ostreamAppender", &cout);

    /*
        2. 创建文件输出器。

        FileAppender 可以把日志写入文件。

        "fileAppender" 是这个输出器的名字。
        "mylogger.log" 是日志文件名。

        程序运行后，会自动生成 mylogger.log 文件。
        日志信息会被保存到这个文件中。
    */
    FileAppender * fileAppender =
        new FileAppender("fileAppender", "mylogger.log");

    /*
        3. 创建终端日志格式对象。

        PatternLayout 用来设置日志输出格式。
    */
    PatternLayout * ptnLayout1 = new PatternLayout();

    /*
        设置终端日志格式。

        "%d [%p] %m%n"

        含义：
            %d  表示日期和时间
            %p  表示日志级别，例如 INFO、WARN
            %m  表示用户真正输出的日志内容
            %n  表示换行

        例如最终效果类似：
            2026-05-08 10:30:12,123 [INFO] [test.cc:20 main] hello
    */
    ptnLayout1->setConversionPattern("%d [%p] %m%n");

    /*
        把格式对象绑定到终端输出器。

        这样终端输出日志时，就会按照上面的格式显示。
    */
    ostreamAppender->setLayout(ptnLayout1);

    /*
        4. 创建文件日志格式对象。

        注意：
        终端输出器和文件输出器不能共用同一个 PatternLayout 对象。

        所以这里需要重新 new 一个 PatternLayout。
    */
    PatternLayout * ptnLayout2 = new PatternLayout();

    /*
        给文件输出设置同样的格式。
    */
    ptnLayout2->setConversionPattern("%d [%p] %m%n");

    /*
        把格式对象绑定到文件输出器。

        这样写入 mylogger.log 文件中的日志，
        也会按照相同的格式保存。
    */
    fileAppender->setLayout(ptnLayout2);

    /*
        5. 把两个输出器都添加到 Category 中。

        添加之后，同一条日志会同时输出到：
            1. 终端
            2. 文件 mylogger.log
    */
    m_category.addAppender(ostreamAppender);
    m_category.addAppender(fileAppender);

    /*
        6. 设置日志优先级。

        Priority::DEBUG 表示 DEBUG 及以上级别的日志都可以输出。

        log4cpp 中常见级别大致有：
            DEBUG
            INFO
            WARN
            ERROR
            FATAL

        这里设置为 DEBUG，
        那么 info 和 warn 都可以正常输出。
    */
    m_category.setPriority(Priority::DEBUG);
}

/*
    析构函数

    Category::shutdown() 会关闭 log4cpp，
    并释放相关资源，例如 Appender、Layout 等。

    因为构造函数中 new 了 Appender 和 PatternLayout，
    这些资源会交给 log4cpp 管理，
    最后通过 Category::shutdown() 统一释放。
*/
Mylogger::~Mylogger()
{
    Category::shutdown();
}

/*
    info()

    对外提供 info 级别日志接口。

    内部真正调用的是 log4cpp::Category 的 info()。
*/
void Mylogger::info(const char * msg)
{
    m_category.info(msg);
}

/*
    warn()

    对外提供 warn 级别日志接口。

    内部真正调用的是 log4cpp::Category 的 warn()。
*/
void Mylogger::warn(const char * msg)
{
    m_category.warn(msg);
}
```

---

# 六、测试代码 test.cc

```cpp
#include "Mylogger.h"

/*
    普通函数，用于测试 __func__ 是否能正确显示函数名。

    在这个函数中调用 LogInfo 和 LogWarn，
    日志中应该显示函数名 test。
*/
void test()
{
    LogInfo("this is an info message in test function");
    LogWarn("this is a warn message in test function");
}

int main()
{
    /*
        输出一条 info 日志。

        日志中应该包含：
            文件名 test.cc
            函数名 main
            当前行号
            日志内容 program begin
    */
    LogInfo("program begin");

    /*
        调用 test 函数。
    */
    test();

    /*
        输出一条 warn 日志。
    */
    LogWarn("program will end");

    /*
        销毁单例对象。

        因为 Mylogger 内部使用 new 创建了单例对象，
        所以程序结束前最好主动销毁。
    */
    Mylogger::destroyInstance();

    return 0;
}
```

---

# 七、编译和运行

假设三个文件在同一目录下：

```text
Mylogger.h
Mylogger.cc
test.cc
```

编译命令：

```bash
g++ Mylogger.cc test.cc -o test -llog4cpp
```

运行程序：

```bash
./test
```

运行之后，会有两处输出。

---

## 1. 终端输出

终端中会看到类似内容：

```text
2026-05-08 10:30:12,123 [INFO] [test.cc:21 main] program begin
2026-05-08 10:30:12,124 [INFO] [test.cc:10 test] this is an info message in test function
2026-05-08 10:30:12,124 [WARN] [test.cc:11 test] this is a warn message in test function
2026-05-08 10:30:12,124 [WARN] [test.cc:31 main] program will end
```

---

## 2. 文件输出

当前目录下会生成日志文件：

```text
mylogger.log
```

文件中的内容和终端输出基本一致：

```text
2026-05-08 10:30:12,123 [INFO] [test.cc:21 main] program begin
2026-05-08 10:30:12,124 [INFO] [test.cc:10 test] this is an info message in test function
2026-05-08 10:30:12,124 [WARN] [test.cc:11 test] this is a warn message in test function
2026-05-08 10:30:12,124 [WARN] [test.cc:31 main] program will end
```

---

# 八、重点知识点解释

## 1. `addPrefix` 宏是怎么工作的？

宏定义如下：

```cpp
#define addPrefix(msg) \
    (std::string("[") + __FILE__ + ":" + std::to_string(__LINE__) + \
    " " + __func__ + "] " + msg)
```

它的作用是把日志内容拼接成一条更完整的信息。

例如：

```cpp
LogInfo("hello");
```

内部会先调用：

```cpp
addPrefix("hello")
```

假设这一行在 `test.cc` 的 `main` 函数第 20 行，那么结果类似：

```text
[test.cc:20 main] hello
```

其中：

```cpp
__FILE__
```

表示当前文件名；

```cpp
__LINE__
```

表示当前行号；

```cpp
__func__
```

表示当前函数名。

---

## 2. 为什么要写 `std::string("[")`？

因为 C++ 中，字符串字面量本质上是 C 风格字符串。

例如：

```cpp
"["
__FILE__
":"
```

它们不能直接用 `+` 拼接。

下面这种写法是错误的：

```cpp
"[" + __FILE__
```

因为这不是字符串拼接，而可能被理解成指针运算。

所以我们要先写：

```cpp
std::string("[")
```

这样第一个参与运算的对象就是 `std::string` 类型。

后面继续使用 `+` 时，就会调用 `std::string` 的字符串拼接功能。

因此下面这种写法是正确的：

```cpp
std::string("[") + __FILE__
```

---

## 3. 为什么要使用 `std::to_string(__LINE__)`？

`__LINE__` 是当前代码所在的行号，它是一个整数。

例如：

```cpp
20
```

整数不能直接和字符串拼接。

所以需要使用：

```cpp
std::to_string(__LINE__)
```

把整数转换成字符串。

例如：

```cpp
std::to_string(20)
```

结果是：

```cpp
"20"
```

这样才能和其他字符串继续拼接。

---

## 4. `LogInfo` 和 `LogWarn` 宏是怎么工作的？

定义如下：

```cpp
#define LogInfo(msg) \
    Mylogger::getInstance()->info(addPrefix(msg).c_str())

#define LogWarn(msg) \
    Mylogger::getInstance()->warn(addPrefix(msg).c_str())
```

以这句为例：

```cpp
LogWarn("发生警告");
```

大致会展开成：

```cpp
Mylogger::getInstance()->warn(addPrefix("发生警告").c_str());
```

它的执行过程是：

1. `Mylogger::getInstance()` 获取唯一的日志对象；
2. `addPrefix("发生警告")` 拼接文件名、行号、函数名和日志内容；
3. `.c_str()` 把 `std::string` 转换成 `const char *`；
4. `warn()` 输出 warn 级别日志。

---

## 5. 为什么要使用 `.c_str()`？

因为 `addPrefix(msg)` 的结果是一个 `std::string`。

但是 `Mylogger` 类中定义的日志函数参数是：

```cpp
void info(const char * msg);
void warn(const char * msg);
```

它们需要的是 `const char *` 类型。

所以需要调用：

```cpp
.c_str()
```

把 `std::string` 转换成 `const char *`。

例如：

```cpp
addPrefix(msg).c_str()
```

---

## 6. `addPrefix(msg).c_str()` 这样写安全吗？

在这里是安全的。

因为：

```cpp
addPrefix(msg)
```

会生成一个临时的 `std::string` 对象。

这个临时对象会一直存在到当前完整语句结束。

例如：

```cpp
Mylogger::getInstance()->info(addPrefix(msg).c_str());
```

在 `info()` 函数调用期间，这个临时字符串还没有销毁，所以 `.c_str()` 返回的指针仍然有效。

等 `info()` 调用结束之后，这个临时字符串才会被销毁。

因此当前写法可以正常使用。

---

## 7. `msg` 参数需要注意什么？

因为新版 `addPrefix` 使用了字符串加法：

```cpp
std::string("[") + __FILE__ + ":" + std::to_string(__LINE__) + \
" " + __func__ + "] " + msg
```

所以 `msg` 最好是字符串类型。

下面这些写法是可以的：

```cpp
LogInfo("hello");
```

或者：

```cpp
std::string message = "hello";
LogInfo(message);
```

或者：

```cpp
std::string name = "Alice";
LogInfo(std::string("name = ") + name);
```

但是下面这样不可以：

```cpp
LogInfo(123);
```

因为整数 `123` 不能直接和 `std::string` 拼接。

如果想输出数字，可以这样写：

```cpp
LogInfo(std::to_string(123));
```

或者：

```cpp
int number = 123;
LogInfo(std::string("number = ") + std::to_string(number));
```

---

# 九、单例模式相关知识点

## 1. 为什么构造函数要私有？

```cpp
private:
    Mylogger();
```

如果构造函数是 `public`，外部就可以直接创建对象：

```cpp
Mylogger logger1;
Mylogger logger2;
```

这样就不是单例了。

构造函数私有化之后，外部无法直接创建对象，只能通过：

```cpp
Mylogger::getInstance();
```

来获取唯一实例。

---

## 2. 为什么析构函数也写成私有？

```cpp
private:
    ~Mylogger();
```

析构函数私有化之后，外部不能随便这样释放对象：

```cpp
delete Mylogger::getInstance();
```

这样可以避免用户误操作。

我们统一通过：

```cpp
Mylogger::destroyInstance();
```

来销毁单例对象。

---

## 3. 为什么要删除拷贝构造和赋值运算符？

```cpp
Mylogger(const Mylogger &) = delete;
Mylogger & operator=(const Mylogger &) = delete;
```

单例模式不仅要防止用户直接创建对象，也要防止用户复制对象。

如果不删除拷贝构造，可能有人写：

```cpp
Mylogger logger = *Mylogger::getInstance();
```

这会复制出一个新的对象，破坏单例模式。

如果不删除赋值运算符，可能有人写：

```cpp
logger1 = logger2;
```

这也不符合单例设计。

所以要把拷贝构造和赋值运算符都禁用。

---

## 4. 为什么 `ms_instance` 是 `static`？

```cpp
static Mylogger * ms_instance;
```

因为它要保存整个类唯一对象的地址。

`static` 成员变量属于类本身，而不是属于某一个具体对象。

如果它不是 `static`，那么必须先有对象，才能访问这个成员变量。

但是单例模式的问题正是：

> 对象还没有创建时，需要有一个地方保存这个唯一对象的地址。

所以这里必须使用静态成员变量。

---

## 5. 为什么静态成员变量要在类外定义？

头文件中写的：

```cpp
static Mylogger * ms_instance;
```

只是声明。

真正的定义要写在 `.cc` 文件中：

```cpp
Mylogger * Mylogger::ms_instance = nullptr;
```

这句话的作用是：

1. 给静态成员变量分配存储空间；
2. 把它初始化为 `nullptr`。

如果只在类中声明，不在类外定义，链接时可能会报错。

---

# 十、log4cpp 相关知识点

## 1. `Category` 是什么？

```cpp
Category & m_category;
```

`Category` 是 log4cpp 中用于写日志的核心对象。

我们调用：

```cpp
m_category.info(msg);
m_category.warn(msg);
```

真正完成日志输出。

---

## 2. 为什么 `m_category` 是引用？

```cpp
Category & m_category;
```

因为：

```cpp
Category::getRoot()
```

返回的是一个 `Category` 引用。

所以我们在类中也使用引用来接收它。

引用成员变量必须在构造函数初始化列表中初始化：

```cpp
Mylogger::Mylogger()
: m_category(Category::getRoot())
{
}
```

不能在构造函数体中再赋值。

---

## 3. `OstreamAppender` 是什么？

```cpp
OstreamAppender * ostreamAppender =
    new OstreamAppender("ostreamAppender", &cout);
```

`OstreamAppender` 是 log4cpp 中的终端输出器。

它可以把日志输出到一个 `ostream` 对象中。

这里传入：

```cpp
&cout
```

表示把日志输出到终端。

---

## 4. `FileAppender` 是什么？

```cpp
FileAppender * fileAppender =
    new FileAppender("fileAppender", "mylogger.log");
```

`FileAppender` 是 log4cpp 中的文件输出器。

它可以把日志写入指定文件。

这里：

```cpp
"mylogger.log"
```

就是日志文件名。

程序运行之后，当前目录下会生成这个文件。

---

## 5. `PatternLayout` 是什么？

```cpp
PatternLayout * ptnLayout1 = new PatternLayout();
ptnLayout1->setConversionPattern("%d [%p] %m%n");
```

`PatternLayout` 用于设置日志格式。

这里的格式是：

```cpp
"%d [%p] %m%n"
```

含义如下：

```text
%d  日期和时间
%p  日志级别
%m  日志内容
%n  换行
```

例如最终输出可能是：

```text
2026-05-08 10:30:12,123 [INFO] [test.cc:20 main] hello
```

其中：

```text
2026-05-08 10:30:12,123
```

来自 `%d`；

```text
[INFO]
```

来自 `%p`；

```text
[test.cc:20 main] hello
```

来自 `%m`，也就是我们传入的日志内容；

最后的换行来自 `%n`。

---

## 6. 为什么需要两个 `PatternLayout`？

因为我们有两个输出器：

```cpp
ostreamAppender
fileAppender
```

一个负责输出到终端，一个负责输出到文件。

每个 `Appender` 都需要一个自己的 `Layout`。

所以我们分别创建：

```cpp
PatternLayout * ptnLayout1 = new PatternLayout();
PatternLayout * ptnLayout2 = new PatternLayout();
```

然后分别绑定：

```cpp
ostreamAppender->setLayout(ptnLayout1);
fileAppender->setLayout(ptnLayout2);
```

不要让两个 Appender 共用同一个 `PatternLayout` 对象。

---

## 7. `Priority::DEBUG` 是什么？

```cpp
m_category.setPriority(Priority::DEBUG);
```

这句代码设置日志输出级别。

log4cpp 常见级别大致有：

```text
DEBUG
INFO
WARN
ERROR
FATAL
```

设置为：

```cpp
Priority::DEBUG
```

表示 DEBUG 及以上级别的日志都可以输出。

因为 `INFO` 和 `WARN` 都比 `DEBUG` 级别高，所以：

```cpp
LogInfo("xxx");
LogWarn("xxx");
```

都可以正常输出。

---

# 十一、完整执行流程

以这句代码为例：

```cpp
LogInfo("program begin");
```

它的执行过程大致是：

第一步，展开 `LogInfo` 宏：

```cpp
Mylogger::getInstance()->info(addPrefix("program begin").c_str());
```

第二步，执行 `addPrefix("program begin")`：

```cpp
std::string("[") + __FILE__ + ":" + std::to_string(__LINE__) +
" " + __func__ + "] " + "program begin"
```

假设这行代码在 `test.cc` 的第 21 行，函数名是 `main`，那么会生成：

```text
[test.cc:21 main] program begin
```

第三步，调用 `.c_str()`：

```cpp
addPrefix("program begin").c_str()
```

把 `std::string` 转换成 `const char *`。

第四步，调用单例对象的 `info()`：

```cpp
Mylogger::getInstance()->info(...);
```

第五步，`info()` 内部调用 log4cpp：

```cpp
m_category.info(msg);
```

第六步，log4cpp 根据之前的配置，把日志同时输出到：

```text
终端
mylogger.log 文件
```

最终日志类似：

```text
2026-05-08 10:30:12,123 [INFO] [test.cc:21 main] program begin
```

---

# 十二、作业总结

这个程序完成了以下要求：

1. 使用类和对象封装了 log4cpp；
2. 使用单例模式保证日志对象唯一；
3. 支持输出到终端；
4. 支持保存到文件；
5. 使用宏简化日志调用；
6. 日志中自动包含文件名、函数名和行号；
7. 提供了 `info` 和 `warn` 两种日志级别；
8. 通过 `destroyInstance()` 释放单例对象。

核心使用方式是：

```cpp
LogInfo("普通日志信息");
LogWarn("警告日志信息");
```

最终日志效果类似：

```text
2026-05-08 10:30:12,123 [INFO] [test.cc:21 main] 普通日志信息
2026-05-08 10:30:12,124 [WARN] [test.cc:22 main] 警告日志信息
```
