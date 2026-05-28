#pragma once
#include <Windows.h>

class ComboManager
{
private:
    DWORD lastClearTime;
    int multiplier;

public:
    ComboManager();

    int updateByClear(int clearedLines, DWORD now);
    int getMultiplier() const;
};
