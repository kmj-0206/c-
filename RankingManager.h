#pragma once
#include <vector>

class RankingManager
{
private:
    std::vector<int> rankings;
    const char* fileName;

public:
    RankingManager(const char* fileName = "rank.txt");

    void load();
    void saveScore(int score);
    const std::vector<int>& getTop3() const;
};
