#pragma once

class ComboManager
{
private:
    int dropsWithoutClear; // 라인을 지우지 못하고 고정된 블록 수
    int multiplier;        // 현재 콤보 배수

public:
    ComboManager();

    // clearedLines > 0이면 콤보 증가.
    // clearedLines == 0인 블록 고정이 3번 연속 발생하면 콤보 초기화.
    int updateByClear(int clearedLines);
    int getMultiplier() const;
};
