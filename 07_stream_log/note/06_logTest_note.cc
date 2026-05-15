#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>

using std::cout;
using std::endl;

using namespace log4cpp;

/**
 * log4cpp 日志系统
 *
 * 之前已经知道：
 * Category  ：记录器对象，用来产生日志信息
 * Appender  ：输出器对象，决定日志输出到哪里
 * Layout    ：格式化器对象，决定日志输出的格式
 * Priority  ：日志优先级，决定哪些日志可以输出
 *
 * 本文件主要演示：
 *
 * 1. 将日志输出到控制台
 * 2. 将日志输出到文件
 * 3. 同时输出到控制台和文件
 * 4. 子记录器复用 root 记录器的配置
 * 5. 子记录器使用自己的配置
 * 6. 回卷日志文件
 */

/**
 * 将日志信息输出到控制台
 *
 * OstreamAppender：
 * 可以将日志信息输出到指定的输出流。
 *
 * 这里指定的是 cout，
 * 所以日志信息会输出到控制台。
 */
void test1()
{
    // 创建输出器对象
    // "console" 表示输出器的名字
    // &cout 表示日志输出到标准输出流，也就是控制台
    OstreamAppender* appender1 = new OstreamAppender("console", &cout);

    /**
     * 创建格式化器对象
     *
     * PatternLayout：
     * 表示自定义日志输出格式。
     *
     * 与 BasicLayout 不同，
     * PatternLayout 可以通过 setConversionPattern
     * 自己指定日志的输出格式。
     */
    PatternLayout * layout1 = new PatternLayout{};

    /**
     * 设置日志输出格式
     *
     * setConversionPattern：
     * 用来设置自定义日志格式。
     *
     * "%d [%p] %c : %m%n"
     *
     * %d ：日志产生的时间
     * %p ：日志优先级
     * %c ：Category 的名字
     * %m ：日志正文
     * %n ：换行
     */
    layout1->setConversionPattern("%d [%p] %c : %m%n");

    // 将格式化器对象绑定到输出器对象上
    appender1->setLayout(layout1);

    // 获取根记录器对象
    Category & root = Category::getRoot();

    /**
     * 设置日志优先级
     *
     * Priority::INFO 表示日志级别设置为 INFO。
     *
     * 只有级别大于等于 INFO 的日志才会被输出。
     * debug 级别低于 info，
     * 所以后面的 debug 日志不会输出。
     */
    root.setPriority(Priority::INFO);

    // 给 root 记录器添加输出器
    // root 产生的日志会通过 appender1 输出到控制台
    root.addAppender(appender1);

    // 产生日志信息

    // DEBUG < INFO，所以不会输出
    root.debug("dubug msg....");

    // INFO >= INFO，可以输出
    root.info("info msg....");

    // NOTICE >= INFO，可以输出
    root.notice("notice msg....");

    // WARN >= INFO，可以输出
    root.warn("warn msg....");

    /**
     * 释放资源
     *
     * Category::shutdown()：
     * 关闭日志系统，释放 log4cpp 内部管理的资源。
     *
     * 因为 appender 和 layout 是 new 出来的，
     * 交给 log4cpp 管理后，
     * 最后需要调用 shutdown 进行清理。
     */
    Category::shutdown();
}

/**
 * 将日志信息保存到日志文件中
 *
 * FileAppender：
 * 可以将日志信息输出到指定文件。
 */
void test2()
{
    // 创建文件输出器对象
    // "file" 表示输出器名字
    // "log.txt" 表示日志写入到 log.txt 文件中
    FileAppender* appender2 =
        new FileAppender("file", "log.txt");

    // 创建自定义格式化器对象
    PatternLayout * layout2 = new PatternLayout{};

    // 设置日志输出格式
    // 与 test1 中类似，只是分隔符变成了 --
    layout2->setConversionPattern("%d [%p] %c -- %m%n");

    // 将格式化器绑定到文件输出器上
    appender2->setLayout(layout2);

    // 获取根记录器
    Category & root = Category::getRoot();

    // 设置日志优先级为 INFO
    root.setPriority(Priority::INFO);

    // 给 root 添加文件输出器
    // root 产生的日志会写入 log.txt 文件
    root.addAppender(appender2);

    // 产生日志信息

    // DEBUG < INFO，不会写入文件
    root.debug("dubug msg....");

    // 下面三条日志级别都 >= INFO，可以写入文件
    root.info("info msg....");
    root.notice("notice msg....");
    root.warn("warn msg....");

    // 关闭日志系统，释放资源
    Category::shutdown();
}

/**
 * 将日志信息同时保存到日志文件中并输出到控制台
 *
 * 一个 Category 可以绑定多个 Appender。
 *
 * 如果 root 同时添加了控制台输出器和文件输出器，
 * 那么 root 产生的一条日志信息，
 * 就可以同时输出到控制台和文件。
 */
void test3()
{
    // 创建控制台输出器对象
    OstreamAppender* appender1 = new OstreamAppender("console", &cout);

    // 创建控制台输出格式
    PatternLayout * layout1 = new PatternLayout{};

    // 设置控制台输出格式
    layout1->setConversionPattern("%d [%p] %c : %m%n");

    // 绑定格式化器
    appender1->setLayout(layout1);

    // 创建文件输出器对象
    FileAppender* appender2 =
        new FileAppender("file", "log.txt");

    // 创建文件输出格式
    PatternLayout * layout2 = new PatternLayout{};

    // 设置文件输出格式
    layout2->setConversionPattern("%d [%p] %c -- %m%n");

    // 绑定格式化器
    appender2->setLayout(layout2);

    // 获取根记录器
    Category & root = Category::getRoot();

    // 设置日志优先级
    root.setPriority(Priority::INFO);

    // 给 root 添加文件输出器
    root.addAppender(appender2);

    // 再给 root 添加控制台输出器
    // 这样 root 的日志既会写入文件，也会输出到控制台
    root.addAppender(appender1);

    // 产生日志信息
    root.debug("dubug msg....");
    root.info("info msg....");
    root.notice("notice msg....");
    root.warn("warn msg....");

    // 释放资源
    Category::shutdown();
}

/**
 * 子记录器可以复用 root 的配置
 *
 * log4cpp 中的 Category 有层级关系。
 *
 * root 是根记录器。
 * 通过 getInstance 获取到的 UserModel 是子记录器。
 *
 * 默认情况下：
 * 子记录器产生的日志，
 * 可以继续传递给父记录器 root。
 *
 * 所以即使 userModel 自己没有添加 Appender，
 * 它也可以复用 root 的 Appender 进行输出。
 */
void test4()
{
    // 创建控制台输出器对象
    OstreamAppender* appender1 = new OstreamAppender("console", &cout);

    // 创建自定义格式化器对象
    PatternLayout * layout1 = new PatternLayout{};

    // 设置输出格式
    layout1->setConversionPattern("%d [%p] %c : %m%n");

    // 给输出器绑定格式化器
    appender1->setLayout(layout1);

    // 获取根记录器
    Category & root = Category::getRoot();

    // 设置 root 的日志优先级
    root.setPriority(Priority::INFO);

    /**
     * 获取子记录器对象
     *
     * getInstance("UserModel")：
     * 获取名字为 UserModel 的记录器对象。
     *
     * 这个记录器是 root 的子记录器。
     */
    Category & userModel =
        Category::getInstance("UserModel");

    // 给 root 添加控制台输出器
    root.addAppender(appender1);

    // root 产生的日志信息
    root.debug("dubug msg....");
    root.info("info msg....");
    root.notice("notice msg....");
    root.warn("warn msg....");

    /**
     * 子记录器产生的日志信息
     *
     * userModel 没有自己添加 Appender，
     * 但是它默认会向父记录器 root 传递日志。
     *
     * 所以这些日志最终也会通过 root 的 appender1
     * 输出到控制台。
     */
    userModel.debug("dubug msg....");
    userModel.info("info msg....");
    userModel.notice("notice msg....");
    userModel.warn("warn msg....");

    // 释放资源
    Category::shutdown();
}

/**
 * 子记录器做自己的配置
 *
 * 子记录器既可以复用 root 的配置，
 * 也可以拥有自己的 Appender。
 *
 * 默认情况下：
 * 子记录器如果自己添加了 Appender，
 * 同时又会继续把日志传递给 root。
 *
 * 这样可能导致一条日志输出多次。
 *
 * 如果不希望子记录器继续使用 root 的配置，
 * 可以调用：
 *
 * setAdditivity(false)
 *
 * 关闭日志向父记录器传递。
 */
void test5()
{
    // 创建控制台输出器对象
    OstreamAppender* appender1 =
        new OstreamAppender("console", &cout);

    // 创建控制台输出格式
    PatternLayout * layout1 = new PatternLayout{};

    // 设置输出格式
    layout1->setConversionPattern("%d [%p] %c : %m%n");

    // 绑定格式化器
    appender1->setLayout(layout1);

    // 创建文件输出器对象
    FileAppender* appender2 =
        new FileAppender("file", "log2.txt");

    // 创建文件输出格式
    PatternLayout * layout2 = new PatternLayout{};

    // 设置文件输出格式
    layout2->setConversionPattern("%d [%p] %c : %m%n");

    // 绑定格式化器
    appender2->setLayout(layout2);

    // 获取根记录器
    Category & root = Category::getRoot();

    // 设置 root 的日志优先级
    root.setPriority(Priority::INFO);

    // root 添加控制台输出器
    // root 的日志会输出到控制台
    root.addAppender(appender1);

    // 获取子记录器 UserModel
    Category & userModel =
        Category::getInstance("UserModel");

    // 给子记录器添加文件输出器
    // userModel 产生的日志会写入 log2.txt
    userModel.addAppender(appender2);

    /**
     * 关闭子记录器的叠加性
     *
     * setAdditivity(false)：
     * 表示 userModel 产生的日志，
     * 不再继续传递给父记录器 root。
     *
     * 如果不写这句：
     * userModel 的日志既会写入 log2.txt，
     * 又会通过 root 输出到控制台。
     *
     * 写了这句之后：
     * userModel 的日志只会使用自己的 appender2。
     */
    userModel.setAdditivity(false);

    // root 产生的日志信息
    root.debug("dubug msg....");
    root.info("info msg....");
    root.notice("notice msg....");
    root.warn("warn msg....");

    // 子记录器产生的日志信息
    // 因为 userModel 设置了 setAdditivity(false)，
    // 所以这些日志只会写入 log2.txt，不会再输出到控制台
    userModel.debug("dubug msg....");
    userModel.info("info msg....");
    userModel.notice("notice msg....");
    userModel.warn("warn msg....");

    // 释放资源
    Category::shutdown();
}

/**
 * 回卷文件测试
 *
 * RollingFileAppender：
 * 回卷文件输出器。
 *
 * 普通 FileAppender 会一直往同一个文件中写日志。
 * 如果程序运行时间很长，
 * 日志文件可能会越来越大。
 *
 * RollingFileAppender 可以限制单个日志文件的大小。
 * 当日志文件超过指定大小后，
 * 会自动生成新的日志文件，
 * 旧日志文件会被保留下来。
 */
void test6()
{
    /**
     * 创建回卷文件输出器对象
     *
     * RollingFileAppender("roll", "A.log", 100, 5)
     *
     * 参数说明：
     *
     * "roll"
     * 表示输出器的名字。
     *
     * "A.log"
     * 表示当前正在写入的日志文件名。
     *
     * 100
     * 表示单个日志文件的最大字节数。
     * 当文件大小超过 100 字节时，
     * 会发生回卷。
     *
     * 5
     * 表示最多保留 5 个回卷文件。
     */
    RollingFileAppender * appender =
        new RollingFileAppender("roll", "A.log", 100, 5);

    // 创建自定义格式化器
    PatternLayout * layout = new PatternLayout();

    // 设置日志输出格式
    layout->setConversionPattern("%d [%p] %c %m%n");

    // 绑定格式化器
    appender->setLayout(layout);

    // 获取根记录器
    Category & root = Category::getRoot();

    // 设置日志优先级为 INFO
    root.setPriority(Priority::INFO);

    // 给 root 添加回卷文件输出器
    root.addAppender(appender);

    /**
     * 循环产生日志信息
     *
     * 因为 RollingFileAppender 设置的单个文件大小为 100 字节，
     * 所以当日志内容不断写入后，
     * A.log 文件大小超过限制时，
     * log4cpp 会自动进行回卷。
     */
    for(int i = 0; i < 10 ; ++i){
        // 将 int 类型转换成 string 类型
        std::string num = std::to_string(i);

        // DEBUG < INFO，所以不会输出
        root.debug(num + " debug msg.");

        // INFO >= INFO，可以输出
        root.info(num + " info msg.");

        // WARN >= INFO，可以输出
        root.warn(num + " warn msg.");
    }

    // 释放资源
    Category::shutdown();
}

int main(int argc, char * argv[])
{
    /**
     * 每次测试时只打开一个测试函数即可。
     *
     * 因为每个测试函数都会获取 root 记录器，
     * 并且最后调用 Category::shutdown() 释放资源。
     *
     * 如果多个测试函数同时调用，
     * 可能会受到 root 配置、Appender 绑定关系等影响。
     */

    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */

    // 当前测试的是：子记录器使用自己的配置，并关闭对 root 配置的复用
    test5();

    /* test6(); */

    return 0;
}