#include <iostream>
#include <string>
using namespace std;

// 1. myMin
template <typename T>
T myMin(T a, T b) {
    return a < b ? a : b;
}

// 2. printValue
template <typename T>
void printValue(T value) {
    cout << value << endl;
}

// 3. sumArray
template <typename T>
T sumArray(T arr[], int len) {
    T sum = 0;
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum;
}

// 4. Box
template <typename T>
class Box {
private:
    T value;

public:
    void setValue(T v) {
        value = v;
    }

    T getValue() {
        return value;
    }

    void show() {
        cout << value << endl;
    }
};

// 5. Calculator
template <typename T>
class Calculator {
private:
    T a;
    T b;

public:
    Calculator(T x, T y) {
        a = x;
        b = y;
    }

    T add() {
        return a + b;
    }

    T sub() {
        return a - b;
    }

    T mul() {
        return a * b;
    }

    T div() {
        if (b == 0) {
            cout << "除数不能为0" << endl;
            return 0;
        }
        return a / b;
    }
};

int main() {
    cout << "myMin测试：" << endl;
    cout << myMin(3, 5) << endl;
    cout << myMin(2.5, 1.1) << endl;
    cout << myMin('a', 'b') << endl;

    cout << "\nprintValue测试：" << endl;
    printValue(10);
    printValue(3.14);
    printValue("hello");

    cout << "\nsumArray测试：" << endl;
    int arr1[] = {1, 2, 3};
    double arr2[] = {1.5, 2.5, 3.0};
    cout << sumArray(arr1, 3) << endl;
    cout << sumArray(arr2, 3) << endl;

    cout << "\nBox测试：" << endl;
    Box<int> b1;
    b1.setValue(100);
    b1.show();

    Box<string> b2;
    b2.setValue("C++");
    b2.show();

    cout << "\nCalculator测试：" << endl;
    Calculator<int> c1(10, 3);
    cout << c1.add() << endl;
    cout << c1.sub() << endl;
    cout << c1.mul() << endl;
    cout << c1.div() << endl;

    Calculator<double> c2(10.5, 2.0);
    cout << c2.div() << endl;

    return 0;
}