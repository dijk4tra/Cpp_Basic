#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

/**
 * 使用配置文件配置 log4cpp
 *
 * 之前的代码中，Appender、Layout、Priority
 * 都是在代码中手动创建和设置的。
 *
 * 例如：
 * 1. new OstreamAppender
 * 2. new FileAppender
 * 3. new PatternLayout
 * 4. root.setPriority(...)
 * 5. root.addAppender(...)
 *
 * 这种方式叫做硬编码配置。
 *
 * 本代码使用 PropertyConfigurator 读取配置文件，
 * 将日志系统的配置写到 log4cpp.properties 文件中。
 *
 * 好处：
 * 如果以后想修改日志输出位置、日志格式、日志级别，
 * 不需要修改 C++ 源代码，
 * 只需要修改配置文件即可。
 */

int main(int argc, char* argv[])
{
    /**
     * 指定配置文件的名字
     *
     * log4cpp.properties：
     * 是 log4cpp 的配置文件。
     *
     * 这个文件中通常会配置：
     * 1. 记录器 Category
     * 2. 输出器 Appender
     * 3. 格式化器 Layout
     * 4. 日志级别 Priority
     */
	std::string initFileName = "log4cpp.properties";

    /**
     * 加载配置文件
     *
     * PropertyConfigurator::configure(initFileName)：
     * 根据指定的配置文件初始化 log4cpp 日志系统。
     *
     * 配置文件加载完成后，
     * 程序中就不需要再手动创建 Appender、Layout，
     * 也不需要手动绑定 Appender。
     *
     * 这些工作都交给配置文件完成。
     */
	log4cpp::PropertyConfigurator::configure(initFileName);

    /**
     * 获取根记录器对象
     *
     * getRoot()：
     * 获取 root 根记录器。
     *
     * root 的日志级别、输出器、格式等信息，
     * 都来自 log4cpp.properties 配置文件。
     */
	log4cpp::Category& root = log4cpp::Category::getRoot();

    /**
     * 获取子记录器 sub1
     *
     * getInstance("sub1")：
     * 获取名字为 sub1 的 Category 对象。
     *
     * 如果配置文件中配置了 sub1，
     * 那么 sub1 会使用配置文件中对应的配置。
     *
     * 如果配置文件中没有单独配置 sub1，
     * 它通常会继承 root 的配置。
     */
	log4cpp::Category& sub1 = 
		log4cpp::Category::getInstance(std::string("sub1"));

    /**
     * 获取子记录器 sub1.sub2
     *
     * log4cpp 的 Category 可以形成层级关系。
     *
     * sub1.sub2 表示：
     * sub2 是 sub1 下面的子记录器。
     *
     * 层级关系类似于：
     *
     * root
     *  |
     * sub1
     *  |
     * sub2
     *
     * 如果 sub1.sub2 没有单独关闭继承关系，
     * 它的日志可能会继续向上级 Category 传递。
     */
	log4cpp::Category& sub2 = 
		log4cpp::Category::getInstance(std::string("sub1.sub2"));

    /**
     * root 产生 WARN 级别日志
     *
     * 是否输出这条日志，
     * 取决于配置文件中 root 的日志级别设置。
     */
	root.warn("Storm is coming");

    /**
     * sub1 产生日志信息
     *
     * debug：
     * DEBUG 级别日志，通常用于调试信息。
     *
     * info：
     * INFO 级别日志，通常用于普通运行信息。
     *
     * 这两条日志是否输出，
     * 取决于配置文件中 sub1 的优先级设置。
     */
	sub1.debug("Received storm warning");
	sub1.info("Closing all hatches");

    /**
     * sub2 产生日志信息
     *
     * sub2 的完整名字是 sub1.sub2。
     *
     * 如果配置文件中对 sub1.sub2 单独设置了日志级别，
     * 就按照自己的配置输出。
     *
     * 如果没有单独设置，
     * 就可能继承上级 sub1 或 root 的配置。
     */
	sub2.debug("Hiding solar panels");
	sub2.error("Solar panels are blocked");
	sub2.debug("Applying protective shield");
	sub2.warn("Unfolding protective shield");
	sub2.info("Solar panels are shielded");

    // sub1 再次产生一条 INFO 级别日志
	sub1.info("All hatches closed");

    // root 产生 INFO 级别日志
	root.info("Ready for storm.");

    /**
     * 关闭日志系统
     *
     * Category::shutdown()：
     * 释放 log4cpp 内部管理的资源。
     *
     * 程序结束前调用该函数，
     * 可以让缓冲区中的日志及时刷新，
     * 并释放 Appender、Layout 等对象。
     */
	log4cpp::Category::shutdown();

	return 0;
}