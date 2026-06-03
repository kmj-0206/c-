#include "BlockQueue.h"

BlockQueue::BlockQueue()
    : forceStickCount(0)
{
}

TetrisBlock BlockQueue::createBlock(StageManager& stages, int level)
{
    // 아이템 C 효과가 남아 있으면 I 블록을 우선 생성한다.
    if (forceStickCount > 0)
    {
        forceStickCount--;
        return factory.createStickBlock(stages, level);
    }

    return factory.createRandomBlock(stages, level);
}

void BlockQueue::fillPreview(StageManager& stages, int level)
{
    while (nextBlocks.size() < PREVIEW_COUNT)
        nextBlocks.push_back(createBlock(stages, level));
}

void BlockQueue::init(StageManager& stages, int level)
{
    forceStickCount = 0;
    nextBlocks.clear();
    fillPreview(stages, level);
}

TetrisBlock BlockQueue::pop(StageManager& stages, int level)
{
    fillPreview(stages, level);

    TetrisBlock block = nextBlocks.front();
    nextBlocks.erase(nextBlocks.begin());

    fillPreview(stages, level);
    return block;
}

void BlockQueue::forceNextStickBlocks(int count)
{
    // 기존 미리보기 큐를 비워야 화면에 보이는 NEXT 5도 즉시 I 블록으로 갱신된다.
    forceStickCount = count;
    nextBlocks.clear();
}

const std::vector<TetrisBlock>& BlockQueue::preview() const
{
    return nextBlocks;
}
