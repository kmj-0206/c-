#pragma once
#include "TetrisBlock.h"
#include "StageManager.h"

// 블록 생성 책임만 담당하는 클래스.
class BlockFactory
{
public:
    // 현재 스테이지 정보에 기반한 일반 랜덤 블록 생성
    TetrisBlock createRandomBlock(StageManager& stages, int level) const;

    // I자 긴 막대 블록 강제 생성 (아이템 효과용)
    TetrisBlock createStickBlock(StageManager& stages, int level) const;
};