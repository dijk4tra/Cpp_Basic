#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};

    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        if (*it % 2 == 0)
        {
            it = vec.insert(it + 1, *it * 2);
        }
    }

    std::cout << "vec = ";
    for (int num : vec)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}