#include "DifficultyManager.h"
#include "Console.h"
#include <iostream>

DifficultyManager::DifficultyManager()
    : difficulty(1), level(0)
{
}

void DifficultyManager::select()
{
    Console::clear();
    std::cout << "Select Difficulty\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Normal\n";
    std::cout << "3. Hard\n";
    std::cout << "Input: ";

    int selected = 1;
    std::cin >> selected;

    if (selected < 1 || selected > 3)
        selected = 1;

    difficulty = selected;
}

int DifficultyManager::getDifficulty() const
{
    return difficulty;
}

int DifficultyManager::getLevel() const
{
    return level;
}

void DifficultyManager::updateLevel(int score, int lines, StageManager& stages)
{
    int scoreLevel = score / 1000;
    if (scoreLevel >= stages.getCount())
        scoreLevel = stages.getCount() - 1;

    int baseLevel = level;
    if (baseLevel < 0 || baseLevel >= stages.getCount())
        baseLevel = 0;

    int lineLevel = lines / stages[baseLevel]->getClear_line();
    if (lineLevel >= stages.getCount())
        lineLevel = stages.getCount() - 1;

    level = (scoreLevel > lineLevel) ? scoreLevel : lineLevel;
}

int DifficultyManager::getCurrentSpeed(int score, StageManager& stages) const
{
    int base = stages[level]->getSpeed();

    if (difficulty == 1)
        base += 120;
    else if (difficulty == 3)
        base -= 80;

    int scorePenalty = score / 300;
    int speed = base - scorePenalty;

    if (speed < 60)
        speed = 60;

    return speed;
}
