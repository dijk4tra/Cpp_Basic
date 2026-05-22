#include <iostream>
#include <list>
#include <deque>

using namespace std;

int main()
{
    list<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    deque<int> even_deque; // 存放偶数
    deque<int> odd_deque; // 存放奇数

    for(int num : numbers)
    {
        if(num % 2 == 0){
            even_deque.push_back(num); // 偶数入队
        }
        else
        {
            odd_deque.push_back(num);  // 奇数入队
        }
    }

    cout << "偶数 deque 中的元素: ";
    for(int num : even_deque)
    {
        cout << num << " ";
    }
    cout << endl;

    cout << "奇数 deque 中的元素: ";
    for(int num : odd_deque)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}