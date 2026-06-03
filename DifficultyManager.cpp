#include "DifficultyManager.h"
#include "Console.h"
#include <iostream>
#include <conio.h>
DifficultyManager::DifficultyManager()
    : difficulty(1), level(0)
{
}

int DifficultyManager::select()
{
    using namespace Console;
    using namespace std;
    int highlighted = 1;
    bool confirmed = false;

    clear();
    SetColor(YELLOW);
    cout << "\n\n\n\n";
    cout << "\t\t=================================\n";
    cout << "\t\t        Select Difficulty        \n";
    cout << "\t\t=================================\n\n";

    int lastHighlighted = -1;

    while (!confirmed)
    {
        if (highlighted != lastHighlighted)
        {
            gotoxy(0, 8);

            if (highlighted == 1) {
                SetColor(SKY_BLUE);
                cout << "\t\t        ▶  1. Easy (Selected) \n\n";
            }
            else {
                SetColor(WHITE);
                cout << "\t\t            1. Easy            \n\n";
            }

            if (highlighted == 2) {
                SetColor(SKY_BLUE);
                cout << "\t\t        ▶  2. Normal (Selected) \n\n";
            }
            else {
                SetColor(WHITE);
                cout << "\t\t            2. Normal          \n\n";
            }

            if (highlighted == 3) {
                SetColor(SKY_BLUE);
                cout << "\t\t        ▶  3. Hard (Selected) \n\n";
            }
            else {
                SetColor(WHITE);
                cout << "\t\t            3. Hard            \n\n";
            }

            SetColor(GRAY);
            // [R] 랭킹 보기 UI 추가
            cout << "\n\t    [방향키/숫자] 이동  [엔터] 확정  [R] 랭킹\n";

            lastHighlighted = highlighted;
        }

        int key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72) { highlighted--; if (highlighted < 1) highlighted = 3; }
            else if (key == 80) { highlighted++; if (highlighted > 3) highlighted = 1; }
        }
        else if (key == 'r' || key == 'R') {
            return 4; // 랭킹 화면으로 이동하기 위한 특수 값 반환
        }
        else if (key == '1') { if (highlighted == 1) confirmed = true; else highlighted = 1; }
        else if (key == '2') { if (highlighted == 2) confirmed = true; else highlighted = 2; }
        else if (key == '3') { if (highlighted == 3) confirmed = true; else highlighted = 3; }
        else if (key == 13) { confirmed = true; }
    }

    difficulty = highlighted;
    return difficulty;
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
        base += 300; // Easy 난이도 기본 속도 대폭 낮춤 (기존 120 -> 300)
    else if (difficulty == 3)
        base -= 80;

    int scorePenalty = score / 300;
    int speed = base - scorePenalty;

    if (speed < 60)
        speed = 60;

    return speed;
}

