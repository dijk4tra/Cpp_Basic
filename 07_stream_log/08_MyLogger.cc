#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include <string>


using namespace log4cpp;

using std::cout;
using std::endl;
using std::string;

/*
 * 使用日志工具时，一般都会进行封装处理，
 * 也就是对底层的 log4cpp 再包装一层，
 * 让外部代码通过自定义接口使用日志功能。
 */

// 自定义日志工具类
class MyLogger
{
public:
    MyLogger()
    : m_category(Category::getRoot())
    {
        // 完成日志系统的初始化操作
        // 给记录器配置输出器、格式化器和日志级别
        OstreamAppender * appender = new OstreamAppender("console", &cout);
        PatternLayout * layout = new PatternLayout();
        layout->setConversionPattern("%d [%p] %c : %m%n");
        appender->setLayout(layout);
        
        m_category.setPriority(Priority::INFO);
        m_category.addAppender(appender);
    }
    
    void debug(const string & msg)
    {
        // 底层调用 log4cpp 的 debug 接口
        m_category.debug(msg);
    }

    void info(const string & msg)
    {
        // 底层调用 log4cpp 的 info 接口
        m_category.info(msg);
    }
    
    void warn(const string & msg)
    {
        // 底层调用 log4cpp 的 warn 接口
        m_category.warn(msg);
    }

    void error(const string & msg)
    {
        // 底层调用 log4cpp 的 error 接口
        m_category.error(msg);
    }

private:
    // 将记录器作为数据成员，供日志接口统一使用
    Category & m_category; 
};

// 创建一个全局日志对象，方便在程序各处直接使用
MyLogger logger;

void test1()
{
    // 模拟数据库连接出错
    logger.error("数据库连接出错...");
}

int main(int argc, char * argv[])
{
    logger.info("程序启动了....");
    test1();

    // 获取当前函数名、源文件名和代码行号
    cout << __FUNCTION__ << endl;
    cout << __FILE__ << endl;
    cout << __LINE__ << endl;

    logger.info("程序结束了....");
    return 0;
}
