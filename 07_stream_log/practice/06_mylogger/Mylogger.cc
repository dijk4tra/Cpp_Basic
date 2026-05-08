#include "Mylogger.h"

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>

#include <iostream>

using std::cout;

Mylogger * Mylogger::ms_instance = nullptr;

Mylogger * Mylogger::getInstance()
{
    if(nullptr == ms_instance)
    {
        ms_instance = new Mylogger{};
    }
    return ms_instance;
}

void Mylogger::destroyInstance()
{
    if(ms_instance){
        delete ms_instance;
        ms_instance = nullptr;
    }
}

Mylogger::Mylogger()
: m_category(Category::getRoot())
{
    // 1.创建终端输出器
    OstreamAppender * ostreamAppender =
        new OstreamAppender("ostreamAppender", &cout);
    
    // 2.创建文件输出器
    FileAppender * fileAppender = 
        new FileAppender("fileAppender", "mylogger.log");

    // 3.设置终端日志格式
    PatternLayout * layout1 = new PatternLayout();
    layout1->setConversionPattern("%d [%p] %m%n");
    ostreamAppender->setLayout(layout1);

    // 4.设置文件日志格式
    PatternLayout * layout2 = new PatternLayout();
    layout2->setConversionPattern("%d [%p] %m%n");
    fileAppender->setLayout(layout2);

    // 5.添加输出器
    m_category.addAppender(ostreamAppender);
    m_category.addAppender(fileAppender);

    // 6.设置日志优先级
    m_category.setPriority(Priority::DEBUG);
}

Mylogger::~Mylogger()
{
    m_category.shutdown();
}

void Mylogger::info(const char * msg)
{
    m_category.info(msg);
}

void Mylogger::warn(const char * msg)
{
    m_category.warn(msg);
}
