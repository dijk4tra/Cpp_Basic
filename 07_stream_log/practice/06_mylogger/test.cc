#include "Mylogger.h"

void test()
{
    LogInfo("this is an info msg");
    LogInfo("this is an warn msg");
}

int main(int argc, char * argv[])
{
    LogInfo("program begin");

    test();

    LogInfo("program end");

    Mylogger::destroyInstance();

    return 0;
}
