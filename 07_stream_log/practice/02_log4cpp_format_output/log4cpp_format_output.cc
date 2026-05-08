#include <iostream>
#include <log4cpp/Category.hh>             // 日志记录器
#include <log4cpp/OstreamAppender.hh>      // 输出器，输出到 std::cout、std::cerr 等流
#include <log4cpp/FileAppender.hh>         // 输出器，输出到普通文件
#include <log4cpp/RollingFileAppender.hh>  // 输出器，输出到回卷文件，文件达到一定大小后滚动
#include <log4cpp/PatternLayout.hh>        // 格式化器，设置日志输出格式
#include <log4cpp/Priority.hh>             // 日志优先级

using namespace std;

int main(int argc, char *argv[])
{   
    // 需要把日志同时输出到三个地方: 
    // 终端(控制台)、普通日志文件、回卷日志文件
    
    // =========================
    // 1.创建终端输出Appender
    // =========================
    
    // 创建控制台输出器对象
    log4cpp::OstreamAppender* consoleAppender = 
        new log4cpp::OstreamAppender("console", &cout);
    // 创建格式化器对象,用于设置日志输出格式
    log4cpp::PatternLayout* consoleLayout =
        new log4cpp::PatternLayout();
    /*
        通过setConversionPattern设置终端日志输出格式

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

    // 将格式化器Layout绑定到输出器Layout上
    consoleAppender->setLayout(consoleLayout);

    
    // =========================
    // 2. 创建普通文件 Appender
    // =========================

    // 创建文件输出器对象
    log4cpp::FileAppender* fileAppender = 
        new log4cpp::FileAppender("file", "normal.log");

    // 为普通文件单独创建一个格式化器对象
    log4cpp::PatternLayout* fileLayout =
        new log4cpp::PatternLayout();

    // 设置普通文件中的日志格式
    fileLayout->setConversionPattern("%d [%p] %c: %m%n");

    // 将文件格式 Layout 绑定到 fileAppender
    fileAppender->setLayout(fileLayout);


    // =========================
    // 3. 创建回卷文件 Appender
    // =========================
    
    // 创建回卷文件输出器对象
    log4cpp::RollingFileAppender* rollingAppender =
        new log4cpp::RollingFileAppender(
            "rolling",       // Appender 名字
            "rolling.log",   // 主日志文件名
            1024,            // 单个日志文件最大大小，单位是字节
            3                // 最多保留 3 个备份文件
        );
    
    // 为回卷文件创建格式化 Layout
    log4cpp::PatternLayout* rollingLayout =
        new log4cpp::PatternLayout();

    // 设置回卷文件中的日志格式
    rollingLayout->setConversionPattern("%d [%p] %c: %m%n");

    // 将 Layout 绑定到 rollingAppender
    rollingAppender->setLayout(rollingLayout);
    

    // ===========================
    // 4. 获取日志记录器 Category
    // ===========================
    
    // Category 是 log4cpp 中真正用来写日志的对象
    log4cpp::Category& root = log4cpp::Category::getRoot();


    // =============================
    // 5. 给 Category 添加 Appender
    // =============================
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
    
    // 设置日志输出等级为 DEBUG
    root.setPriority(log4cpp::Priority::DEBUG);


    // =========================
    // 7. 输出不同级别的日志
    // =========================
    
    root.debug("This is a debug message.");
    root.info("This is an info message.");
    root.warn("This is a warning message.");
    root.error("This is an error message.");
    root.fatal("This is a fatal message.");


    // =========================
    // 8. 测试回卷文件功能
    // =========================

    // 当rolling.log超过1024字节时,
    // log4cpp会自动进行回卷
    for(int i = 0; i < 100; ++i)
    {   
        // to_string(i):将整数 i 转换成字符串
        root.info("This is rolling file test message number: " + to_string(i));
    }
    

    // =========================
    // 9. 关闭 log4cpp
    // =========================
    
    // shutdown()用于释放log4cpp内部资源
    log4cpp::Category::shutdown();


    return 0;
}

