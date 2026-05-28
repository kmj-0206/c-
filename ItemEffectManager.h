#pragma once
#include "board.h"
#include "BlockQueue.h"

class ItemEffectManager
{
public:
    int applyScoreEffect(int baseScore, const ClearResult& result) const;
    void applyBlockEffect(const ClearResult& result, BlockQueue& queue) const;
};
