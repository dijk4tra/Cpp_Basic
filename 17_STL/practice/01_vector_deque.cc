#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

// 选手类
class Person
{
public:
    Person(string name, double score)
    : m_name(name), m_score(score)
    {}

    string m_name;
    double m_score;
};

// 创建选手
void createPersons(vector<Person>& v)
{
    string nameSeed = "ABCDE";

    for(int i=0; i<5; i++)
    {
        string name = "选手";
        name += nameSeed[i];

        double score = 0;

        Person p{name, score};
        v.push_back(p);
    }
}

// 给选手打分
void setScore(vector<Person>& v)
{
    for(auto& p : v)
    {
        deque<double> d;
        for(int i=0; i<10; i++){
            // 随机生成 60 ~ 100 之间的分数
            double score = rand() % 41 + 60;
            d.push_back(score);
        }

        // 使用 sort 算法对分数排序（默认从小到大）
        sort(d.begin(), d.end());

        // 去掉最低分（队头）和最高分（队尾）
        d.pop_back();
        d.pop_front();

        // 遍历 deque 容器，进行剩余分数的累加
        double sum = 0;
        for(double s : d){
            sum += s;
        }

        // 求平均分并赋值给选手
        p.m_score = sum / d.size();
    }
}

// 输出结果
void showScore(const vector<Person>& v)
{
    cout << "--- 最终比赛成绩 ---" << endl;
    for(const auto& p : v){
        cout << "姓名: " << p.m_name << " \t 最终平均分: " << p.m_score << endl;
    }
}

int main()
{
    // 更改随机数种子，确保每次运行的分数不同
    srand((unsigned int)time(NULL));

    // 创建存放选手的 vector
    vector<Person> player_list;
    
    // 初始化 5 名选手
    createPersons(player_list);

    // 开始打分和计算
    setScore(player_list);

    // 显示成绩
    showScore(player_list);

    return 0;
}
