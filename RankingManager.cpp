#include "RankingManager.h"
#include <fstream>
#include <algorithm>
#include <functional>

using namespace std;
RankingManager::RankingManager(const char* fileName)
    : fileName(fileName)
{
}

void RankingManager::load()
{
    rankings.clear();

    ifstream fin(fileName);
    int score;
    while (fin >> score)
    {
        rankings.push_back(score);
    }

    sort(rankings.begin(), rankings.end(), greater<int>());
    if (rankings.size() > RANK_SIZE) // 10위까지 기억하도록 변경
        rankings.resize(RANK_SIZE);
}

void RankingManager::saveScore(int score)
{
    vector<int> allScores;

    ifstream fin(fileName);
    int value;
    while (fin >> value)
    {
        allScores.push_back(value);
    }
    fin.close();

    allScores.push_back(score);

    ofstream fout(fileName, ios::trunc);
    for (int s : allScores)
    {
        fout << s << '\n';
    }
    fout.close();

    load();
}

const vector<int>& RankingManager::getRank() const // 이름 변경
{
    return rankings;
}