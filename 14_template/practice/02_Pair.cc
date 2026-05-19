#include <iostream>
using namespace std;

template <typename T>
class Pair {
private:
    T first;
    T second;

public:
    Pair(T a, T b) {
        first = a;
        second = b;
    }

    T getFirst() {
        return first;
    }

    T getSecond() {
        return second;
    }

    void show() {
        cout << first << " " << second << endl;
    }
};

int main() {
    Pair<int> p1(10, 20);
    p1.show();

    Pair<double> p2(1.5, 2.8);
    p2.show();

    Pair<string> p3("hello", "world");
    p3.show();

    return 0;
}