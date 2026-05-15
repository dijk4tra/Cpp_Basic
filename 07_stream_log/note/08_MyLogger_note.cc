#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>

using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;

/*
 * 使用日志工具时, 一般都会做封装处理
 * 对底层的log4cpp进行包装, 套个外壳
 *
 * 好处：
 * 1. 业务代码不需要直接依赖 log4cpp 的具体接口
 * 2. 以后如果更换日志库，只需要修改封装类
 * 3. 可以统一控制日志格式、日志级别、输出位置
 * 4. 使用起来更简单
 */

// 自定义日志工具类
class MyLogger
{
public:
    /**
     * 构造函数
     *
     * MyLogger 对象创建时，
     * 自动完成日志系统的初始化配置。
     *
     * 这里主要完成：
     * 1. 获取 root 记录器
     * 2. 创建控制台输出器
     * 3. 创建格式化器
     * 4. 设置日志格式
     * 5. 设置日志级别
     * 6. 给记录器绑定输出器
     */
    MyLogger()
    : m_category(Category::getRoot())
    {
        /**
         * 创建控制台输出器对象
         *
         * OstreamAppender：
         * 可以将日志信息输出到指定输出流。
         *
         * 这里传入 &cout，
         * 表示日志输出到控制台。
         */
        OstreamAppender * appender = new OstreamAppender("console", &cout);

        /**
         * 创建格式化器对象
         *
         * PatternLayout：
         * 可以自定义日志输出格式。
         */
        PatternLayout * layout = new PatternLayout();

        /**
         * 设置日志输出格式
         *
         * %d ：日志产生的时间
         * %p ：日志优先级
         * %c ：Category 名字
         * %m ：日志正文
         * %n ：换行
         */
        layout->setConversionPattern("%d [%p] %c : %m%n");

        // 将格式化器绑定到输出器上
        appender->setLayout(layout);

        /**
         * 设置日志优先级
         *
         * Priority::INFO：
         * 表示只输出 INFO 及以上级别的日志。
         *
         * DEBUG 级别低于 INFO，
         * 所以后面调用 debug 时不会输出。
         */
        m_category.setPriority(Priority::INFO);

        // 给记录器添加输出器
        // 之后 m_category 产生的日志都会输出到控制台
        m_category.addAppender(appender);
    }

    /**
     * 输出 INFO 级别日志
     *
     * info：
     * 一般用于记录程序正常运行时的重要信息。
     */
    void info(const string & msg)
    {
        // 底层还是调用 log4cpp 的 info 接口
        m_category.info(msg);
    }

    /**
     * 输出 DEBUG 级别日志
     *
     * debug：
     * 一般用于调试信息。
     *
     * 当前日志级别设置为 INFO，
     * DEBUG < INFO，
     * 所以这类日志不会输出。
     */
    void debug(const string & msg)
    {
        // 底层使用 log4cpp
        m_category.debug(msg);
    }

    /**
     * 输出 ERROR 级别日志
     *
     * error：
     * 一般用于记录错误信息。
     */
    void error(const string & msg)
    {
        // 底层使用 log4cpp
        m_category.error(msg);
    }

private:
    /**
     * 把记录器作为数据成员
     *
     * Category &：
     * 使用引用保存记录器对象。
     *
     * 因为 Category::getRoot() 返回的是引用，
     * 所以这里的数据成员也定义成引用类型。
     *
     * 注意：
     * 引用成员必须在构造函数初始化列表中初始化，
     * 不能在构造函数体内再赋值。
     */
    Category &  m_category;
};

/**
 * 创建一个全局日志对象
 *
 * logger 是全局对象，
 * 在 main 函数执行之前就会被创建。
 *
 * 因此 MyLogger 的构造函数也会在 main 函数之前执行，
 * 日志系统会提前完成初始化。
 *
 * 之后程序中的其他函数就可以直接使用 logger 输出日志。
 */
MyLogger logger;

void test1()
{
    // 模拟数据库连接出错
    // 调用自己封装的 error 接口输出 ERROR 级别日志
    logger.error("数据库连接出错...");
}

int main(int argc, char * argv[])
{
    // 输出 INFO 级别日志
    logger.info("程序启动了....");

    // 调用测试函数
    test1();

    /**
     * 获取当前函数名、文件名、行号
     *
     * __FUNCTION__：
     * 当前所在函数的函数名。
     *
     * __FILE__：
     * 当前源文件的文件名。
     *
     * __LINE__：
     * 当前代码所在的行号。
     *
     * 这些宏经常和日志系统一起使用，
     * 用来定位日志发生的位置。
     */
    cout << __FUNCTION__ << endl;
    cout << __FILE__ << endl;
    cout << __LINE__ << endl;

    // 输出程序结束日志
    logger.info("程序结束了....");

    return 0;
}