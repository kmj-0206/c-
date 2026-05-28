#include "RankingManager.h"
#include <fstream>
#include <algorithm>
#include <functional>

RankingManager::RankingManager(const char* fileName)
    : fileName(fileName)
{
}

void RankingManager::load()
{
    rankings.clear();

    std::ifstream fin(fileName);
    int score;
    while (fin >> score)
    {
        rankings.push_back(score);
    }

    std::sort(rankings.begin(), rankings.end(), std::greater<int>());
    if (rankings.size() > 3)
        rankings.resize(3);
}

void RankingManager::saveScore(int score)
{
    std::vector<int> allScores;

    std::ifstream fin(fileName);
    int value;
    while (fin >> value)
    {
        allScores.push_back(value);
    }
    fin.close();

    allScores.push_back(score);

    std::ofstream fout(fileName, std::ios::trunc);
    for (int s : allScores)
    {
        fout << s << '\n';
    }
    fout.close();

    load();
}

const std::vector<int>& RankingManager::getTop3() const
{
    return rankings;
}
