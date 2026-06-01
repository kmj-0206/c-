#pragma once
#include "StageManager.h"

class DifficultyManager
{
private:
    int difficulty;
    int level;

public:
    DifficultyManager();

    int select(); //랭킹창 보러 들어가는거면 전용 값 반환 필요
    int getDifficulty() const;
    int getLevel() const;

    bool updateLevel(int score, int& lines, StageManager& stages);
    int getRemainingLines(int lines, StageManager& stages) const; // 남은 라인 계산용
    int getCurrentSpeed(int score, StageManager& stages) const;
};
