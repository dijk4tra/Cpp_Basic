#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
class Info {
private:
    T1 name;
    T2 score;

public:
    Info(T1 n, T2 s) {
        name = n;
        score = s;
    }

    void show() {
        cout << "name: " << name << ", score: " << score << endl;
    }
};

int main() {
    Info<string, int> student1("Tom", 90);
    student1.show();

    Info<string, double> student2("Alice", 88.5);
    student2.show();

    return 0;
}