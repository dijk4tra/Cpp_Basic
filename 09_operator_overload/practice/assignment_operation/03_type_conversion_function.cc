#include <iostream>
using namespace std;

// 方式三：在 Point 中定义类型转换函数

class Complex {
private:
    int real, imag;

public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}

    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

class Point {
private:
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}

    operator Complex() const {
        return Complex(x, y);
    }
};

int main() {
    Point pt(8, 9);
    Complex cx(4, 6);

    cx = pt;
    cx.print();

    return 0;
}