#include "ComboManager.h"

ComboManager::ComboManager()
    : lastClearTime(0), multiplier(1)
{
}

int ComboManager::updateByClear(int clearedLines, ULONGLONG now)
{
    if (clearedLines <= 0)
    {
        multiplier = 1;
        return multiplier;
    }

    if (lastClearTime != 0 && now - lastClearTime <= 10000)
        multiplier = 2;
    else
        multiplier = 1;

    lastClearTime = now;
    return multiplier;
}

int ComboManager::getMultiplier() const
{
    return multiplier;
}
