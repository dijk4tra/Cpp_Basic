#include <iostream>

using std::cout;
using std::endl;

/*
// C语言中使用的是 malloc/free
void test1()
{
    int * p = (int *)malloc(4);
    *p = 100;
    cout << *p << endl;
    free(p);
    p = NULL;
}
*/

void test2()
{   
    // 值初始化
    int * p1 = new int(); // 没有初始化时,默认值为0
    cout << *p1 << endl;

    int * p2 = new int(10);
    cout << *p2 << endl;
    cout << "------" << endl;

    // 其他写法: 初始化列表方式
    int * p3 = new int {  };
    cout << *p3 << endl;
    int * p4 = new int { 100 };
    cout << *p4 << endl;

    delete p1;
    delete p2;
    delete p3;
    delete p4;
    // 安全回收
    p1 = nullptr;
    p2 = nullptr;
    p3 = nullptr;
    p4 = nullptr;

}

// 连续空间的分配释放
void test3()
{
    //在堆空间中申请一个3个int大小的空间
    int * p1 = new int[3]();
    cout << p1[0] << endl;
    cout << p1[1] << endl;
    cout << p1[2] << endl;
    cout << "--------" << endl;

    // 其他写法: 初始化列表方式去做
    int * p2 = new int[]{};
    cout << p2[0] << endl;
    cout << p2[1] << endl;
    cout << p2[2] << endl;
    cout << "--------" << endl;
    
    int *p3 = new int[3]{1,2,3};
    cout << p3[0] << endl;
    cout << p3[1] << endl;
    cout << p3[2] << endl;
    
    // 对于数组这种连续空间 使用delete[]
    delete [] p1;
    delete [] p2;
    delete [] p3;
    p1 = nullptr;
    p2 = nullptr;
    p3 = nullptr;

}

int main(int argc, char *argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

