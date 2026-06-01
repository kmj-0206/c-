#pragma once
#include "board.h"
#include "BlockQueue.h"
#include <set>

// ------------------------------------------------------------
// ItemEffect
// ------------------------------------------------------------
// 아이템 효과의 공통 부모 클래스.
// GameManager는 구체적인 A/B/C 아이템 클래스를 직접 알 필요 없이
// ItemEffect 포인터를 통해 같은 방식으로 효과를 실행한다.
// 이것이 상속 + 가상함수 + 다형성을 사용하는 핵심 부분이다.
class ItemEffect
{
public:
    virtual ~ItemEffect() = default;

    // 현재 라인 클리어 결과에 이 효과를 적용할 수 있는지 판단한다.
    virtual bool canApply(const ClearResult& result) const = 0;

    // 줄 삭제 전에 실행되는 효과.
    // 예: 아이템 A는 삭제 대상 줄을 위/아래로 확장한다.
    virtual void beforeRemoveLines(ClearResult& result, BlockQueue& queue) const;

    // 점수 계산 후 실행되는 효과.
    // 예: 아이템 B는 점수를 2배로 만든다.
    virtual int afterCalculateScore(int score, const ClearResult& result) const;

    virtual const char* name() const = 0;
};

class BombLineEffect : public ItemEffect
{
public:
    bool canApply(const ClearResult& result) const override;
    void beforeRemoveLines(ClearResult& result, BlockQueue& queue) const override;
    const char* name() const override;
};

class DoubleScoreEffect : public ItemEffect
{
public:
    bool canApply(const ClearResult& result) const override;
    int afterCalculateScore(int score, const ClearResult& result) const override;
    const char* name() const override;
};

class StickBlockSupplyEffect : public ItemEffect
{
public:
    bool canApply(const ClearResult& result) const override;
    void beforeRemoveLines(ClearResult& result, BlockQueue& queue) const override;
    const char* name() const override;
};
