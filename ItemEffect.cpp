#include "ItemEffect.h"

void ItemEffect::beforeRemoveLines(ClearResult& result, BlockQueue& queue) const
{
    
    (void)result;
    (void)queue;
}

int ItemEffect::afterCalculateScore(int score, const ClearResult& result) const
{
    // 기본 아이템은 점수를 변경 X
    (void)result;
    return score;
}

bool BombLineEffect::canApply(const ClearResult& result) const
{
    return result.hasItem(ItemType::A);
}

void BombLineEffect::beforeRemoveLines(ClearResult& result, BlockQueue& queue) const
{
    (void)queue;

    // 현재 삭제 대상 줄을 기준으로 위/아래 줄까지 삭제 대상에 추가
    std::set<int> expandedRows = result.removedRows;

    for (int row : result.removedRows)
    {
        if (row - 1 >= 0)
            expandedRows.insert(row - 1);

        if (row + 1 < BOARD_PLAY_HEIGHT)
            expandedRows.insert(row + 1);
    }

    result.removedRows = expandedRows;
}

const char* BombLineEffect::name() const
{
    return "A";
}

bool DoubleScoreEffect::canApply(const ClearResult& result) const
{
    return result.hasItem(ItemType::B);
}

int DoubleScoreEffect::afterCalculateScore(int score, const ClearResult& result) const
{
    (void)result;
    return score * 2;
}

const char* DoubleScoreEffect::name() const
{
    return "B";
}

bool StickBlockSupplyEffect::canApply(const ClearResult& result) const
{
    return result.hasItem(ItemType::C);
}

void StickBlockSupplyEffect::beforeRemoveLines(ClearResult& result, BlockQueue& queue) const
{
    (void)result;
    queue.forceNextStickBlocks(5);
}

const char* StickBlockSupplyEffect::name() const
{
    return "C";
}
