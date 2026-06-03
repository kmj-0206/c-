#pragma once
#include "StageManager.h"

class DifficultyManager
{
private:
    int difficulty;
    int level;

public:
    // 기본 생성자
    DifficultyManager();

    // 난이도 선택 UI 출력 및 입력 처리
    int select();
    // 선택된 난이도 반환
    int getDifficulty() const;
    // 현재 레벨 반환
    int getLevel() const;

    // 점수와 라인에 기반한 레벨업 적용
    bool updateLevel(int score, int& lines, StageManager& stages);
    // 다음 레벨업까지 필요한 남은 라인 수 계산
    int getRemainingLines(int lines, StageManager& stages) const;
    // 현재 레벨 및 점수에 따른 블록 낙하 속도 계산
    int getCurrentSpeed(int score, StageManager& stages) const;
};