#pragma once
#include "Stage.h"
#include <vector>

class StageManager
{
private:
    std::vector<Stage> StageList; // 포인터 배열 대신 안전한 vector 사용
    int count;

public:
    StageManager();
    StageManager(int count);
    ~StageManager() = default; // 동적할당 해제 필요 없음

    void init_Stage();
    Stage* operator[](int level);

    int getCount() const {
        return count;
    }
};