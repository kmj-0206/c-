#include "DifficultyManager.h"
#include "Console.h"
#include <iostream>
#include <conio.h>
DifficultyManager::DifficultyManager()
    : difficulty(1), level(0)
{
}

void DifficultyManager::select()
{
    using namespace Console;
    using namespace std;
    int highlighted = 1;
    bool confirmed = false;

    // 화면 뼈대는 최초 1회만 그립니다 (깜빡임 방지)
    Console::clear();
    Console::SetColor(YELLOW);
    std::cout << "\n\n\n\n";
    std::cout << "\t\t=================================\n";
    std::cout << "\t\t        Select Difficulty        \n";
    std::cout << "\t\t=================================\n\n";

    int lastHighlighted = -1;

    while (!confirmed)
    {
        // 바뀐 부분(메뉴 텍스트)만 갱신합니다
        if (highlighted != lastHighlighted)
        {
            gotoxy(0, 8); // 메뉴가 출력될 Y좌표로 이동

            // 1. Easy
            if (highlighted == 1) {
                Console::SetColor(SKY_BLUE);
                std::cout << "\t\t        ▶  1. Easy (Selected) \n\n";
            }
            else {
                Console::SetColor(WHITE);
                std::cout << "\t\t            1. Easy            \n\n";
            }

            // 2. Normal
            if (highlighted == 2) {
                Console::SetColor(SKY_BLUE);
                std::cout << "\t\t        ▶  2. Normal (Selected) \n\n";
            }
            else {
                Console::SetColor(WHITE);
                std::cout << "\t\t            2. Normal          \n\n";
            }

            // 3. Hard
            if (highlighted == 3) {
                Console::SetColor(SKY_BLUE);
                std::cout << "\t\t        ▶  3. Hard (Selected) \n\n";
            }
            else {
                Console::SetColor(WHITE);
                std::cout << "\t\t            3. Hard            \n\n";
            }

            Console::SetColor(GRAY);
            std::cout << "\n\t\t [방향키/숫자] 이동  [엔터/한번더누름] 확정\n";

            lastHighlighted = highlighted;
        }

        int key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72) { highlighted--; if (highlighted < 1) highlighted = 3; }
            else if (key == 80) { highlighted++; if (highlighted > 3) highlighted = 1; }
        }
        else if (key == '1') { if (highlighted == 1) confirmed = true; else highlighted = 1; }
        else if (key == '2') { if (highlighted == 2) confirmed = true; else highlighted = 2; }
        else if (key == '3') { if (highlighted == 3) confirmed = true; else highlighted = 3; }
        else if (key == 13) { confirmed = true; } // 엔터
    }

    difficulty = highlighted;
}

int DifficultyManager::getDifficulty() const
{
    return difficulty;
}

int DifficultyManager::getLevel() const
{
    return level;
}

bool DifficultyManager::updateLevel(int score, int& lines, StageManager& stages)
{
    int requiredLines = stages[level]->getClear_line();

    // 깬 라인이 요구 라인 수에 도달하면 레벨 업
    if (lines >= requiredLines)
    {
        lines -= requiredLines; // 초과 달성분은 다음 레벨로 이월
        level++;

        // 마지막 레벨을 넘어섰다면 게임 클리어!
        if (level >= stages.getCount())
        {
            level = stages.getCount() - 1; // 오버플로우 방지
            return true;
        }
    }
    return false;
}
int DifficultyManager::getRemainingLines(int lines, StageManager& stages) const
{
    return stages[level]->getClear_line() - lines;
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
