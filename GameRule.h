#pragma once
#include "BlockControl.h"
#include "TetrisBlock.h"

class GameRule
{
public:
    // 블록 고정 시 게임 오버 판정 (천장 충돌 여부)
    bool isGameOverOnMerge(const TetrisBlock& block) const;
    // 새 블록 스폰 즉시 충돌하는지(게임 오버) 판정
    bool isGameOverOnSpawn(const BlockControl& controller, const TetrisBlock& block) const;
};