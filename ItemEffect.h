#pragma once
#include "board.h"
#include "BlockQueue.h"
#include <set>
//일단은 아이템의 알고리즘이 복잡하지 않고, 갯수도 적어서 한 파일에 전부 둠. 나중에 추가시 다른 파일로 분리하기만 하면 됨
class ItemEffect
{
public:
    // 가상 소멸자
    virtual ~ItemEffect() = default;

    // 해당 아이템 효과가 현재 조건에서 적용 가능한지 확인
    virtual bool canApply(const ClearResult& result) const = 0;

    // 라인 삭제 전에 수행되는 선행 효과 적용 (기본: 처리 없음)
    virtual void beforeRemoveLines(ClearResult& result, BlockQueue& queue) const;

    // 점수 계산 후 점수 보정 효과 적용 (기본: 기존 점수 반환)
    virtual int afterCalculateScore(int score, const ClearResult& result) const;

    // 아이템 효과의 고유 이름 반환
    virtual const char* name() const = 0;
};

class BombLineEffect : public ItemEffect
{
public:
    // A 아이템 적용 여부 확인
    bool canApply(const ClearResult& result) const override;
    // 삭제 대상 라인의 상하 라인까지 삭제 범위 확장
    void beforeRemoveLines(ClearResult& result, BlockQueue& queue) const override;
    // 효과명 반환
    const char* name() const override;
};

class DoubleScoreEffect : public ItemEffect
{
public:
    // B 아이템 적용 여부 확인
    bool canApply(const ClearResult& result) const override;
    // 계산된 점수 2배로 증가 보정
    int afterCalculateScore(int score, const ClearResult& result) const override;
    // 효과명 반환
    const char* name() const override;
};

class StickBlockSupplyEffect : public ItemEffect
{
public:
    // C 아이템 적용 여부 확인
    bool canApply(const ClearResult& result) const override;
    // 다음 스폰할 5개 블록을 I 블록으로 큐에 강제 설정
    void beforeRemoveLines(ClearResult& result, BlockQueue& queue) const override;
    // 효과명 반환
    const char* name() const override;
};