/*
    本程序演示 log4cpp 的基本使用方法。

    实现功能：
    1. 使用 PatternLayout 设置日志格式
    2. 使用 OstreamAppender 将日志输出到终端
    3. 使用 FileAppender 将日志输出到普通文件 normal.log
    4. 使用 RollingFileAppender 将日志输出到回卷文件 rolling.log
    5. 当 rolling.log 超过指定大小后，自动生成备份日志文件

    log4cpp 的基本使用流程：
    1. 创建 Appender，指定日志输出位置
    2. 创建 Layout，指定日志输出格式
    3. 将 Layout 绑定到 Appender
    4. 获取 Category
    5. 将 Appender 添加到 Category
    6. 设置日志等级
    7. 使用 Category 输出日志
*/

#include <iostream>

// log4cpp 的核心类 Category，用来真正写日志
#include <log4cpp/Category.hh>

// OstreamAppender 用于把日志输出到 C++ 标准输出流，比如 cout
#include <log4cpp/OstreamAppender.hh>

// FileAppender 用于把日志输出到普通文件
#include <log4cpp/FileAppender.hh>

// RollingFileAppender 用于把日志输出到“回卷文件”
// 当日志文件超过指定大小后，会自动生成备份文件
#include <log4cpp/RollingFileAppender.hh>

// PatternLayout 用于设置日志输出格式
// 例如：时间、日志级别、日志内容等
#include <log4cpp/PatternLayout.hh>

// Priority 用于设置日志等级
// 常见等级有 DEBUG、INFO、WARN、ERROR、FATAL
#include <log4cpp/Priority.hh>

using namespace std;

int main()
{
    /*
        Appender 可以理解为“日志输出目的地”。

        本程序需要把日志同时输出到三个地方：
        1. 终端
        2. 普通日志文件
        3. 回卷日志文件

        所以需要创建三个 Appender。
    */

    // =========================
    // 1. 创建终端输出 Appender
    // =========================

    /*
        OstreamAppender 表示输出到一个 ostream 对象。

        参数说明：
        "console"：这个 Appender 的名字，可以自定义
        &cout：表示把日志输出到标准输出，也就是终端
    */
    log4cpp::OstreamAppender* consoleAppender =
        new log4cpp::OstreamAppender("console", &cout);

    /*
        Layout 可以理解为“日志输出格式”。

        PatternLayout 是 log4cpp 中常用的格式化布局类，
        可以通过格式字符串控制日志最终长什么样。
    */
    log4cpp::PatternLayout* consoleLayout =
        new log4cpp::PatternLayout();

    /*
        设置终端日志输出格式。

        格式说明：
        %d 表示日期时间
        %p 表示日志级别，例如 DEBUG、INFO、ERROR
        %c 表示 Category 名称
        %m 表示真正输出的日志内容
        %n 表示换行

        最终效果类似：
        2026-05-07 12:00:00,123 [INFO] root: This is an info message.
    */
    consoleLayout->setConversionPattern("%d [%p] %c: %m%n");

    /*
        将 Layout 绑定到 Appender。

        也就是说：
        consoleAppender 决定日志输出到终端，
        consoleLayout 决定日志在终端中显示成什么格式。
    */
    consoleAppender->setLayout(consoleLayout);


    // =========================
    // 2. 创建普通文件 Appender
    // =========================

    /*
        FileAppender 表示输出到普通文件。

        参数说明：
        "file"：Appender 的名字
        "normal.log"：日志文件名

        程序运行后，会在当前目录下生成 normal.log 文件。
    */
    log4cpp::FileAppender* fileAppender =
        new log4cpp::FileAppender("file", "normal.log");

    // 为普通文件单独创建一个 PatternLayout
    log4cpp::PatternLayout* fileLayout =
        new log4cpp::PatternLayout();

    /*
        设置普通文件中的日志格式。

        这里和终端使用相同格式，便于观察。
        当然也可以设置成不同格式。
    */
    fileLayout->setConversionPattern("%d [%p] %c: %m%n");

    /*
        将文件格式 Layout 绑定到 fileAppender。

        绑定后，写入 normal.log 的日志就会按照该格式输出。
    */
    fileAppender->setLayout(fileLayout);


    // =========================
    // 3. 创建回卷文件 Appender
    // =========================

    /*
        RollingFileAppender 表示回卷文件输出。

        回卷文件的作用：
        当日志文件达到指定大小后，自动将旧日志重命名为备份文件，
        然后创建新的日志文件继续写入。

        例如可能生成：
        rolling.log
        rolling.log.1
        rolling.log.2
        rolling.log.3
    */
    log4cpp::RollingFileAppender* rollingAppender =
        new log4cpp::RollingFileAppender(
            "rolling",      // Appender 名字
            "rolling.log",  // 主日志文件名
            1024,           // 单个日志文件最大大小，单位是字节
            3               // 最多保留 3 个备份文件
        );

    // 为回卷文件创建格式化 Layout
    log4cpp::PatternLayout* rollingLayout =
        new log4cpp::PatternLayout();

    /*
        设置回卷文件中的日志格式。

        这里仍然使用：
        时间 + 日志级别 + Category 名称 + 日志内容
    */
    rollingLayout->setConversionPattern("%d [%p] %c: %m%n");

    /*
        将 Layout 绑定到 RollingFileAppender。

        这样写入 rolling.log 的日志也会按照指定格式输出。
    */
    rollingAppender->setLayout(rollingLayout);


    // =========================
    // 4. 获取日志 Category
    // =========================

    /*
        Category 是 log4cpp 中真正用来写日志的对象。

        可以把 Category 理解为“日志记录器”。

        getRoot() 表示获取根 Category。
        对于简单程序，直接使用 root 就够了。
    */
    log4cpp::Category& root = log4cpp::Category::getRoot();


    // =========================
    // 5. 给 Category 添加 Appender
    // =========================

    /*
        一个 Category 可以绑定多个 Appender。

        这里给 root 同时绑定三个 Appender：
        1. consoleAppender：输出到终端
        2. fileAppender：输出到 normal.log
        3. rollingAppender：输出到 rolling.log

        因此，只要使用 root 写一条日志，
        这条日志就会同时出现在三个地方。
    */
    root.addAppender(consoleAppender);
    root.addAppender(fileAppender);
    root.addAppender(rollingAppender);


    // =========================
    // 6. 设置日志优先级
    // =========================

    /*
        设置日志输出等级为 DEBUG。

        日志等级通常从低到高大致为：
        DEBUG < INFO < WARN < ERROR < FATAL

        设置为 DEBUG 表示：
        DEBUG 及以上等级的日志都会输出。

        如果设置为 WARN，则 DEBUG 和 INFO 不会输出，
        只有 WARN、ERROR、FATAL 会输出。
    */
    root.setPriority(log4cpp::Priority::DEBUG);


    // =========================
    // 7. 输出不同级别的日志
    // =========================

    /*
        下面分别输出不同等级的日志，
        用于观察日志等级和格式化输出效果。
    */
    root.debug("This is a debug message.");
    root.info("This is an info message.");
    root.warn("This is a warning message.");
    root.error("This is an error message.");
    root.fatal("This is a fatal message.");


    // =========================
    // 8. 测试回卷文件功能
    // =========================

    /*
        由于 rolling.log 的最大大小设置为 1024 字节，
        所以这里循环输出较多日志。

        当 rolling.log 超过 1024 字节时，
        log4cpp 会自动进行回卷。

        可以通过 ls 命令观察是否生成：
        rolling.log
        rolling.log.1
        rolling.log.2
        rolling.log.3
    */
    for (int i = 0; i < 100; ++i)
    {
        /*
            to_string(i) 将整数 i 转换成字符串。

            这里拼接字符串，是为了让每一条日志内容不同，
            便于观察输出结果。
        */
        root.info("This is rolling file test message number: " + to_string(i));
    }


    // =========================
    // 9. 关闭 log4cpp
    // =========================

    /*
        shutdown() 用于释放 log4cpp 内部资源。

        程序结束前调用 shutdown 是一个好习惯，
        可以确保日志内容被正确刷新到文件中。
    */
    log4cpp::Category::shutdown();

    return 0;
}