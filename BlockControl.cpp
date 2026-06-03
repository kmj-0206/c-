#include "BlockControl.h"
#include "board.h"

BlockControl::BlockControl(const Board& board)
    : curControlBlock(nullptr), curBoard(&board)
{
}

bool BlockControl::move(MoveCommand cmd)
{
    if (curControlBlock == nullptr)
        return false;

    BlockState proposed = curControlBlock->propose(cmd);

    if (!canMoveTo(proposed))
        return false;

    curControlBlock->commit(proposed);
    return true;
}

void BlockControl::dropFull()
{
    if (curControlBlock == nullptr)
        return;

    // 한 칸 아래 후보 상태를 만들고, 충돌하기 직전까지 계속 commit한다.
    BlockState proposed = curControlBlock->propose(MoveCommand::DOWN);
    while (canMoveTo(proposed))
    {
        curControlBlock->commit(proposed);
        proposed = curControlBlock->propose(MoveCommand::DOWN);
    }
}

bool BlockControl::canMoveTo(const BlockState& state) const
{
    if (curControlBlock == nullptr || curBoard == nullptr)
        return false;

    return !curBoard->isCollision(state, curControlBlock->getShape());
}
