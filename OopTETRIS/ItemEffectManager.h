#pragma once
#include "ItemEffect.h"
#include <memory>
#include <vector>

class ItemEffectManager
{
private:
    std::vector<std::unique_ptr<ItemEffect>> effects;

public:
    ItemEffectManager();

    // 라인 삭제 전에 실행할 효과들을 적용한다.
    void applyBeforeRemoveLines(ClearResult& result, BlockQueue& queue) const;

    // 점수 계산 후 점수 보정 효과들을 적용한다.
    int applyAfterCalculateScore(int baseScore, const ClearResult& result) const;
};
