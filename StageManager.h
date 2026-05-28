#pragma once
#include "Stage.h"

class StageManager
{
private:
    Stage* StageList;
    int count;

public:
    StageManager();

    StageManager(int count);

    ~StageManager();

    void init_Stage();

    Stage* operator[](int level);

    int getCount() const {
        return count;
    }
};