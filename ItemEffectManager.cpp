#include "ItemEffectManager.h"

int ItemEffectManager::applyScoreEffect(int baseScore, const ClearResult& result) const
{
    if (result.itemB)
        return baseScore * 2;

    return baseScore;
}

void ItemEffectManager::applyBlockEffect(const ClearResult& result, BlockQueue& queue) const
{
    if (result.itemC)
        queue.forceNextStickBlocks(5);
}
