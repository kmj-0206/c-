#pragma once
#include <vector>
using namespace std;

class RankingManager
{
private:
    vector<int> rankings;
    const char* fileName;
    const int RANK_SIZE = 10;//랭킹 몇 위까지 보이게 할 것인지 표시하는 상수
public:
    RankingManager(const char* fileName = "rank.txt");

    void load();
    void saveScore(int score);
    const vector<int>& getRank() const; // getTop3 -> getRank로 변경
};