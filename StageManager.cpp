#include "StageManager.h"

StageManager::StageManager()
    : StageManager(5)
{
}

StageManager::StageManager(int count)
    : count(count)
{
    StageList.resize(count);
    init_Stage();
}

void StageManager::init_Stage()
{
    for (int i = 0; i < count; i++)
    {
        StageList[i] = Stage(
            300 - (i * 40),
            20 - i,
            20
        );
    }
}

Stage* StageManager::operator[](int level)
{
    if (level < 0 || level >= count)
    {
        return nullptr;
    }

    return &StageList[level];
}