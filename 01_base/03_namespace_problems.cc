#include <iostream>

/* using namespace std; */
using std::cout;
using std::endl;

// void cout(){}

void test1()
{
    /* cout();  */
}

namespace zs
{
int num = 1;
}

namespace ls
{
int num = 2;
}

void test2()
{
   // 尽量避免下面的情况发生
   /* using zs::num; */
   /* using ls::num; */
   /* cout << num << endl; */

   cout << zs::num << endl;
   cout << ls::num << endl;
}

int main(int argc, char *argv[])
{
    test2();
    return 0;
}

