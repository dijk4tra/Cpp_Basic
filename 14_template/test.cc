#include "print.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test1()
{
    print(100);
    /* print<int>(100); */
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

