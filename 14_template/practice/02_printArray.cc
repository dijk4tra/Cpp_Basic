#include <iostream>
using namespace std;

template <typename T>
void printArray(T arr[], int len) {
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int nums[] = {1, 2, 3, 4};
    double scores[] = {88.5, 90.0, 76.5};
    char letters[] = {'A', 'B', 'C'};

    printArray(nums, 4);
    printArray(scores, 3);
    printArray(letters, 3);

    return 0;
}