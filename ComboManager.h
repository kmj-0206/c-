#pragma once
#include <Windows.h>

class ComboManager
{
private:
    ULONGLONG lastClearTime;
    int multiplier;

public:
    ComboManager();

    int updateByClear(int clearedLines, ULONGLONG now);
    int getMultiplier() const;
};
