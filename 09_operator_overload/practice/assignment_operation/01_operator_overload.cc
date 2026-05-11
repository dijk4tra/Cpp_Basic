#include <iostream>
using namespace std;

// 方式一：在 Complex 中重载赋值运算符

class Point {
private:
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }
};

class Complex {
private:
    int real, imag;

public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}

    Complex& operator=(const Point& pt) {
        real = pt.getX();
        imag = pt.getY();
        return *this;
    }

    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Point pt(8, 9);
    Complex cx(4, 6);

    cx = pt;
    cx.print();

    return 0;
}