#include <iostream>
#include <numeric> // 用于 accumulate

using std::cout;
using std::endl;

// 打印整型数组
void processArray(int arr[], int size)
{
    cout << "--- 打印整型数组 ---" << endl;
    cout << "数组元素: ";
    for (int i=0; i<size; ++i){
        cout << arr[i] << (i == size-1 ? "" : ", ");
    }
    cout << endl << endl;
}

// 打印双精度浮点数组并计算平均值
void processArray(double arr[], int size)
{
    cout << "--- 打印双精度浮点数组并计算平均值 ---" << endl;
    cout << "数组元素: ";
    
    double sum = 0;
    for (int i=0; i<size; ++i){
        cout << arr[i] << (i == size - 1 ? "" : ", ");
        sum += arr[i];
    }

    cout << endl;

    if (size > 0){
        cout << "平均值: " << sum/size << endl;
    }else{
        cout << "数组为空, 无法计算平均值" << endl;
    }

    cout << endl;
}


int main(int argc, char *argv[])
{   
    int size1 = 5;
    int *arr1 = new int[size1]{1, 2, 3, 4, 5};
    
    int size2 = 4;
    double *arr2 = new double[size2]{1.5, 2.5, 3.5, 4.5};

    processArray(arr1, size1);
    processArray(arr2, size2);
    
    delete[] arr1;
    delete[] arr2;

    return 0;
}

