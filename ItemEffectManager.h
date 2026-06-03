#pragma once
#include "ItemEffect.h"
#include <memory>
#include <vector>

class ItemEffectManager
{
private:
    std::vector<std::unique_ptr<ItemEffect>> effects; //std 혼자 사용

public:
    // 기본 생성자 (아이템 효과 클래스들 등록)
    ItemEffectManager();

    // 등록된 모든 효과 객체들을 순회하며 조건 달성 시 삭제 전 효과 전부 실행
    void applyBeforeRemoveLines(ClearResult& result, BlockQueue& queue) const;

    // 등록된 모든 효과 객체들을 순회하며 조건 달성 시 점수 보정 효과 전부 실행
    int applyAfterCalculateScore(int baseScore, const ClearResult& result) const;
};