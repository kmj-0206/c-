#include "ComboManager.h"

ComboManager::ComboManager()
    : dropsWithoutClear(0), multiplier(1)
{
}

int ComboManager::updateByClear(int clearedLines)
{
    if (clearedLines > 0)
    {
        dropsWithoutClear = 0;
        multiplier++; // 클리어 시 콤보 배수 증가
        if (multiplier < 2) multiplier = 2; // 최소 2배부터 시작
        return multiplier;
    }
    else
    {
        dropsWithoutClear++;
        if (dropsWithoutClear >= 3)
        {
            multiplier = 1; // 3번 연속 클리어 실패 시 콤보 초기화
            dropsWithoutClear = 0;
        }
        return multiplier;
    }
}

int ComboManager::getMultiplier() const
{
    return multiplier;
}
