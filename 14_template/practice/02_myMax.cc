#include <iostream>
using namespace std;

template <typename T>
T myMax(T a, T b) {
    return a > b ? a : b;
}

int main() {
    cout << myMax(3, 5) << endl;
    cout << myMax(2.5, 1.8) << endl;
    cout << myMax('a', 'z') << endl;

    return 0;
}