#pragma once
#include "TetrisBlock.h"
#include "StageManager.h"
#include <vector>

class BlockQueue
{
private:
    std::vector<TetrisBlock> nextBlocks;
    int forceStickCount;

    TetrisBlock createBlock(StageManager& stages, int level);

public:
    BlockQueue();

    void init(StageManager& stages, int level);
    TetrisBlock pop(StageManager& stages, int level);
    void forceNextStickBlocks(int count);
    const std::vector<TetrisBlock>& preview() const;
};
