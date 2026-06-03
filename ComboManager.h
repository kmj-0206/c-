#pragma once

class ComboManager
{
private:
    int dropsWithoutClear; // 라인을 지우지 못하고 고정된 블록 수
    int multiplier;        // 현재 콤보 배수

public:
    // 기본 생성자
    ComboManager();

    // 라인 클리어 결과를 반영하여 콤보 갱신
    int updateByClear(int clearedLines);
    // 현재 콤보 배수 반환
    int getMultiplier() const;
};