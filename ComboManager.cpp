#include "ComboManager.h"

ComboManager::ComboManager()
    : dropsWithoutClear(0), multiplier(1)
{
}

int ComboManager::updateByClear(int clearedLines)
{
    if (clearedLines > 0)
    {
        // 라인 클리어에 성공하면 실패 카운트를 초기화하고 콤보 배수를 올린다.
        dropsWithoutClear = 0;
        multiplier++;

        // 첫 클리어부터 최소 2배 보너스를 주는 기존 규칙 유지.
        if (multiplier < 2)
            multiplier = 2;

        return multiplier;
    }

    // 라인 클리어 없이 블록이 고정된 횟수를 센다.
    dropsWithoutClear++;

    if (dropsWithoutClear >= 3)
    {
        multiplier = 1;
        dropsWithoutClear = 0;
    }

    return multiplier;
}

int ComboManager::getMultiplier() const
{
    return multiplier;
}
