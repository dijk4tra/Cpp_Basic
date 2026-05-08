#ifndef __MYLOGGER__HH__
#define __MYLOGGER__HH__

#include <log4cpp/Category.hh>
#include <string>

using namespace log4cpp;

// 定义一个宏用于日志拼接：文件名、函数名、行号、用户日志信息
// [文件名:行号 函数名] 日志内容
#define addPrefix(msg) \
    (std::string("[") + __FILE__ + ":" + std::to_string(__LINE__) + \
    " " + __func__ + "] " + msg)

#define LogInfo(msg) \
    Mylogger::getInstance()->info(addPrefix(msg).c_str())

#define logWarn(msg) \
    Mylogger::getInstance()->warn(addPrefix(msg).c_str())

// 单例模式
class Mylogger
{
public:
    // 静态方法获取实例
    static Mylogger * getInstance();

    // 静态方法销毁实例
    static void destroyInstance();

    // 删除拷贝构造、赋值运算符
    Mylogger(const Mylogger &) = delete;
    Mylogger & operator=(const Mylogger &) = delete;

    // info
    void info(const char * msg);

    // warn
    void warn(const char * msg);

private:
    Mylogger();
    ~Mylogger();

private:
    static Mylogger * ms_instance;
    Category & m_category;
};

#endif

