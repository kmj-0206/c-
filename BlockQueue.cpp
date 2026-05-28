#include "BlockQueue.h"

BlockQueue::BlockQueue()
    : forceStickCount(0)
{
}

TetrisBlock BlockQueue::createBlock(StageManager& stages, int level)
{
    if (forceStickCount > 0)
    {
        forceStickCount--;
        return TetrisBlock(stages[level]->getStick_rate(), 0, ItemType::NONE);
    }

    return TetrisBlock(stages[level]->getStick_rate());
}

void BlockQueue::init(StageManager& stages, int level)
{
    nextBlocks.clear();
    while (nextBlocks.size() < 5)
    {
        nextBlocks.push_back(createBlock(stages, level));
    }
}

TetrisBlock BlockQueue::pop(StageManager& stages, int level)
{
    while (nextBlocks.size() < 5)
    {
        nextBlocks.push_back(createBlock(stages, level));
    }

    TetrisBlock block = nextBlocks.front();
    nextBlocks.erase(nextBlocks.begin());

    while (nextBlocks.size() < 5)
    {
        nextBlocks.push_back(createBlock(stages, level));
    }

    return block;
}

void BlockQueue::forceNextStickBlocks(int count)
{
    forceStickCount = count;
    nextBlocks.clear();
}

const std::vector<TetrisBlock>& BlockQueue::preview() const
{
    return nextBlocks;
}
