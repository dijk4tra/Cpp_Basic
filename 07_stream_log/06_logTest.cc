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

// 将日志信息输出到控制台
void test1()
{
    // 创建控制台输出器对象
    OstreamAppender * appender1 = new OstreamAppender("console", &cout);
    
    // 创建格式化器对象，用于设置日志输出格式
    PatternLayout * layout1 = new PatternLayout{};

    // 通过 setConversionPattern 设置自定义日志格式
    layout1->setConversionPattern("%d [%p] %c : %m%n");
    // 将格式化器绑定到输出器上
    appender1->setLayout(layout1);

    // 获取根记录器对象
    Category & root = Category::getRoot();
    // 设置日志优先级为 INFO，只有级别大于等于 INFO 的日志才会被输出
    root.setPriority(Priority::INFO);

    // 给记录器添加输出器
    root.addAppender(appender1);
    
    // 产生日志信息
    root.debug("debug msg...");
    root.info("info msg...");
    root.notice("notice msg...");
    root.warn("warn msg...");

}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

