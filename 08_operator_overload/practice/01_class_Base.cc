#include <iostream>
#include <cmath>

using namespace std;

class Base
{
private:
    int value;

public:
    Base(int v)
    {
        value = v;
    }

    int operator+(const Base & rhs) const
    {
        return abs(value - rhs.value);
    }
};

int main(int argc, char *argv[])
{
    int i = 2;
    int j = 7;

    Base x(i);
    Base y(j);

    cout << (x + y == j - i) << endl;

    return 0;
}

