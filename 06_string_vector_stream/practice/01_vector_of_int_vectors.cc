#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main(int argc, char *argv[])
{   
    // 创建一个 vector，里面的元素也是 vector<int>
    vector<vector<int>> vv =
    {
        {1, 2, 3},
        {4, 5},
        {6, 7, 8, 9}
    };
    
    cout << "遍历二维 vector 的内容：" << endl;

    for(int i = 0; i < vv.size(); i++){
        for(int j = 0; j < vv[i].size(); j++){
            cout << vv[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    cout << "观察 vector 对象本身的地址：" << endl;
    cout << "&vv = " << &vv << endl;

    for (size_t i = 0; i < vv.size(); i++) {
        cout << "&vv[" << i << "] = " << &vv[i] << endl;
    }

    cout << endl;

    cout << "观察每个内部 vector 中元素的地址：" << endl;
    
    for(int i = 0; i < vv.size(); i++){
        cout << "第 " << i << " 个 vector<int> 中元素地址：" << endl;
        for(int j = 0; j < vv[i].size(); j++){
            cout << "&vv[" << i << "][" << j << "] = "
                 << &vv[i][j]
                 << ", value = " << vv[i][j]
                 << endl;
        }
        cout << endl;
    }
    
    return 0;
}

