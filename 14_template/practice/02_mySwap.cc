#include <iostream>

using std::cout;
using std::endl;

template<typename T>
void mySwap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

int main(int argc, char *argv[])
{
    int x = 10, y = 20;
    cout << "before: " << x << " " << y << endl;
    mySwap(x, y);
    cout << "after: " << x << " " << y << endl;
    
    double a = 1.5, b = 2.8;
    cout << "before: "  << a << " " << b << endl;
    mySwap(a, b);
    cout << "after: "  << a << " " << b << endl;

    return 0;
}

