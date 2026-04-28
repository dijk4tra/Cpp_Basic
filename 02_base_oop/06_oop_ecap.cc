#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/**
 * 封装的通常做法:
 * 1.把不想被外界访问的成员使用private修饰
 * 2.给外界提供应该访问的接口:读写分离操作
 * 访问需求: 提供getXx方法,用于读操作
 * 修改需求: 提供一个setXx方法,用于数据修改
 *
 */

class Empolyee
{
public:
    int id = 1;
    string name = "zs";
    double salary = 12000;
};

class Student
{
public:
    int id;
    string name;
    
    // 提供访问的入口getXxx
    int getScore(){
        // 进行权限的校验
        // 如果是老师,则可以访问
        return score;
    }
    // 提供一个修改的入口setXxx
    void setScore(int newScore){
        // 对数据进行校验
        score = newScore;
    }
private:
    int score;
};

void test1()
{
    Empolyee zs;
    cout << zs.id << endl;
    cout << zs.name << endl;
    /* cout << zs.salary << endl; */

    Student stu;
    stu.id;
    stu.name;
    /* stu.score; */
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

