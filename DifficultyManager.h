#pragma once
#include "StageManager.h"

class DifficultyManager
{
private:
    int difficulty;
    int level;

public:
    DifficultyManager();

    void select();
    int getDifficulty() const;
    int getLevel() const;

    void updateLevel(int score, int lines, StageManager& stages);
    int getCurrentSpeed(int score, StageManager& stages) const;
};
