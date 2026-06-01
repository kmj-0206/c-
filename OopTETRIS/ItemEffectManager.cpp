#include "ItemEffectManager.h"

ItemEffectManager::ItemEffectManager()
{
    // 새 아이템을 추가할 때는 여기에서 효과 객체만 하나 추가하면 된다.
    // GameManager나 Board의 if문을 늘릴 필요가 없다.
    effects.push_back(std::make_unique<BombLineEffect>());
    effects.push_back(std::make_unique<DoubleScoreEffect>());
    effects.push_back(std::make_unique<StickBlockSupplyEffect>());
}

void ItemEffectManager::applyBeforeRemoveLines(ClearResult& result, BlockQueue& queue) const
{
    for (const auto& effect : effects)
    {
        if (effect->canApply(result))
            effect->beforeRemoveLines(result, queue); // 가상함수 호출: 실제 자식 클래스 함수 실행
    }
}

int ItemEffectManager::applyAfterCalculateScore(int baseScore, const ClearResult& result) const
{
    int score = baseScore;

    for (const auto& effect : effects)
    {
        if (effect->canApply(result))
            score = effect->afterCalculateScore(score, result); // 가상함수 호출
    }

    return score;
}
