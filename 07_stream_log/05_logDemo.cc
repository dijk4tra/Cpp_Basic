#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

int main(int argc, char** argv) {
	// 创建一个输出到控制台的输出器对象 OstreamAppender
    // 原本可以使用 OstreamAppender* 接收该对象，
    // 这里使用父类指针 Appender* 指向子类对象，体现了多态
	log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
	
	// 给输出器绑定格式化器对象，采用 BasicLayout 基础布局
	appender1->setLayout(new log4cpp::BasicLayout());

	// 创建一个 FileAppender 输出器对象，将日志信息输出到目标文件中
    // 这里同样使用父类指针 Appender* 指向子类对象，体现了多态
	log4cpp::Appender *appender2 = new log4cpp::FileAppender("default", "program.log");
	// 给 appender2 输出器对象绑定格式化器对象，采用 BasicLayout 基础布局
	appender2->setLayout(new log4cpp::BasicLayout());

	// getRoot() 是静态成员函数，用于获取根记录器对象
	log4cpp::Category& root = log4cpp::Category::getRoot();
	// 设置日志级别为 WARN，只有优先级大于等于 WARN 的日志才会被保留并输出
	root.setPriority(log4cpp::Priority::WARN);
	// 给 root 记录器添加控制台输出器 appender1，这样 root 产生的日志会输出到控制台
	root.addAppender(appender1);

	// getInstance() 用于获取指定名字的子记录器对象 sub1
	log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));
	// 给子记录器 sub1 添加文件输出器
	sub1.addAppender(appender2);

	// 产生日志信息
	// 使用成员函数的方式输出日志信息
	// root 产生的日志
	root.error("root error");
	root.info("root info");
	// sub1 产生的日志
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");

	// 使用 printf 风格输出带变量的日志信息
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// 使用流的方式输出日志信息
	root << log4cpp::Priority::ERROR << "Streamed root error";
	root << log4cpp::Priority::INFO << "Streamed root info";
	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

	// 也可以使用 errorStream() 的方式输出 ERROR 级别日志
	root.errorStream() << "Another streamed error";

	return 0;
}
