#include "BlockFactory.h"

TetrisBlock BlockFactory::createRandomBlock(StageManager& stages, int level) const
{
    Stage* stage = stages[level];
    int stickRate = stage ? stage->getStick_rate() : 20;
    return TetrisBlock(stickRate);
}

TetrisBlock BlockFactory::createStickBlock(StageManager& stages, int level) const
{
    Stage* stage = stages[level];
    int stickRate = stage ? stage->getStick_rate() : 20;

    // forceShape = 0 : I 블록, forceItem = NONE : 아이템 효과 없이 순수 막대 블록
    return TetrisBlock(stickRate, 0, ItemType::NONE);
}
