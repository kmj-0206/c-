#pragma once
#include <Windows.h>

class ComboManager
{
private:
    int dropsWithoutClear; // 시간 대신 블록 놓은 횟수로 변경
    int multiplier;

public:
    ComboManager();

    int updateByClear(int clearedLines); // 시간(now) 파라미터 제거
    int getMultiplier() const;
};
