#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

/**
 * log4cpp 日志系统的基本使用
 *
 * 在 log4cpp 中，常见的几个核心概念：
 *
 * 1. Category
 *    记录器对象。
 *    程序不是直接把日志写到文件或者终端，
 *    而是先把日志交给 Category。
 *
 * 2. Appender
 *    输出器对象。
 *    它决定日志最终输出到哪里。
 *    例如：
 *    OstreamAppender 可以输出到终端；
 *    FileAppender 可以输出到文件。
 *
 * 3. Layout
 *    格式化器对象。
 *    它决定日志输出时采用什么格式。
 *
 * 4. Priority
 *    日志优先级，也就是日志级别。
 *    例如：
 *    DEBUG、INFO、WARN、ERROR、FATAL。
 *
 * 日志输出的大致流程：
 * Category 产生日志信息
 *        |
 *        v
 * Appender 决定输出位置
 *        |
 *        v
 * Layout 决定输出格式
 */

int main(int argc, char** argv) {

    /**
     * 创建一个输出到控制台的输出器对象
     *
     * OstreamAppender：
     * 可以把日志信息输出到一个输出流中。
     *
     * 这里传入的是 &std::cout，
     * 所以日志会输出到标准输出，也就是控制台。
     *
     * 参数：
     * "console"
     * 表示这个输出器对象的名字。
     *
     * &std::cout
     * 表示日志输出到 cout 对应的终端。
     *
     * 注意：
     * new log4cpp::OstreamAppender(...)
     * 实际创建的是 OstreamAppender 对象。
     *
     * 但是这里使用 log4cpp::Appender * 来接收，
     * 也就是使用父类指针指向子类对象。
     * 这是多态的体现。
     */
	log4cpp::Appender *appender1 =
        new log4cpp::OstreamAppender("console", &std::cout);

    /**
     * 给 appender1 绑定一个格式化器对象
     *
     * setLayout：
     * 设置日志的输出格式。
     *
     * BasicLayout：
     * 基础布局方式。
     * 它会使用 log4cpp 提供的默认基础格式输出日志。
     *
     * 注意：
     * 一个 Appender 如果没有绑定 Layout，
     * 通常无法按照指定格式正常输出日志。
     */
	appender1->setLayout(new log4cpp::BasicLayout());


    /**
     * 创建一个输出到文件的输出器对象
     *
     * FileAppender：
     * 可以把日志信息写入到指定文件中。
     *
     * 参数：
     * "default"
     * 表示这个输出器对象的名字。
     *
     * "program.log"
     * 表示日志输出到 program.log 文件中。
     *
     * 这里同样使用 Appender * 接收 FileAppender 对象，
     * 也是父类指针指向子类对象，
     * 体现了多态。
     */
	log4cpp::Appender *appender2 = 
        new log4cpp::FileAppender("default", "program.log");

    // 给 appender2 绑定基础布局格式
    appender2->setLayout(new log4cpp::BasicLayout());


    /**
     * 获取根记录器对象
     *
     * Category：
     * 表示记录器。
     * 之后产生日志信息时，
     * 就是通过 Category 对象来完成的。
     *
     * getRoot()：
     * 是 Category 类的静态成员函数，
     * 用来获取根记录器对象。
     *
     * 返回值是 Category &，
     * 所以这里使用引用 root 接收。
     *
     * 注意：
     * root 不是一个新的记录器对象，
     * 而是根记录器对象的引用。
     */
	log4cpp::Category& root = log4cpp::Category::getRoot();

    /**
     * 设置根记录器的日志优先级
     *
     * setPriority：
     * 设置当前记录器允许输出的最低日志级别。
     *
     * log4cpp::Priority::WARN：
     * 表示日志级别设置为 WARN。
     *
     * 只有级别大于等于 WARN 的日志才会被输出。
     * 例如：
     * WARN、ERROR、FATAL 会输出；
     * DEBUG、INFO 不会输出。
     */
	root.setPriority(log4cpp::Priority::WARN);

    // 给根记录器 root 添加一个输出器
    // root 产生的日志会通过 appender1 输出到控制台
	root.addAppender(appender1);

    /**
     * 获取一个子记录器对象
     *
     * getInstance()：
     * 用来获取指定名字的 Category 对象。
     *
     * std::string("sub1")：
     * 表示这个子记录器的名字叫 sub1。
     *
     * root 是根记录器；
     * sub1 是一个子记录器。
     *
     * 子记录器也可以拥有自己的 Appender，
     * 从而把日志输出到不同的位置。
     */
	log4cpp::Category& sub1 =
        log4cpp::Category::getInstance(std::string("sub1"));

    // 给子记录器 sub1 添加文件输出器
    // sub1 产生的日志会通过 appender2 输出到 program.log 文件
	sub1.addAppender(appender2);

    /**
     * 产生日志信息
     *
     * error、info、warn 等函数：
     * 都是 Category 提供的日志输出接口。
     *
     * 它们的区别在于日志级别不同。
     */

    // root 产生 ERROR 级别日志
    // root 的日志级别是 WARN，
    // ERROR >= WARN，所以这条日志会输出
	root.error("root error");

    // root 产生 INFO 级别日志
    // INFO < WARN，所以这条日志不会输出
	root.info("root info");

    // sub1 产生 ERROR 级别日志
    // sub1 绑定了 appender2，
    // 所以这条日志会写入 program.log 文件
	sub1.error("sub1 error");

    // sub1 产生 WARN 级别日志
    // WARN 级别满足输出条件
	sub1.warn("sub1 warn");

    /**
     * 使用 printf 风格输出日志
     *
     * 这种写法和 printf 类似，
     * 可以使用 %d、%s 等占位符。
     *
     * %d 对应整数；
     * %s 对应字符串。
     */
	root.warn("%d + %d == %s ?", 1, 1, "two");

    /**
     * 使用流的方式输出日志
     *
     * 这种写法类似 cout：
     * root << 日志级别 << 日志内容;
     *
     * 好处：
     * 可以像使用输出流一样拼接日志信息。
     */

    // 通过流的方式输出 ERROR 级别日志
	root << log4cpp::Priority::ERROR << "Streamed root error";

    // 通过流的方式输出 INFO 级别日志
    // INFO < WARN，所以不会输出
	root << log4cpp::Priority::INFO << "Streamed root info";

    // sub1 通过流的方式输出 ERROR 级别日志
	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";

    // sub1 通过流的方式输出 WARN 级别日志
	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

    /**
     * 另一种流式写法
     *
     * errorStream()：
     * 返回一个用于输出 ERROR 级别日志的流对象。
     *
     * 所以下面这句等价于：
     * root 产生一条 ERROR 级别的日志。
     */
	root.errorStream() << "Another streamed error";

	return 0;
}