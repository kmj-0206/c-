#pragma once
#include "TetrisBlock.h"
#include "StageManager.h"
#include "BlockFactory.h"
#include <vector>

class BlockQueue
{
private:
    static const int PREVIEW_COUNT = 5;

    std::vector<TetrisBlock> nextBlocks;
    int forceStickCount;
    BlockFactory factory;

    TetrisBlock createBlock(StageManager& stages, int level);
    void fillPreview(StageManager& stages, int level);

public:
    BlockQueue();

    void init(StageManager& stages, int level);
    TetrisBlock pop(StageManager& stages, int level);

    // 아이템 C 효과: 다음 count개의 블록을 I 블록으로 만든다.
    void forceNextStickBlocks(int count);

    const std::vector<TetrisBlock>& preview() const;
};
