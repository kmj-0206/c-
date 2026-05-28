#include "BlockControl.h"
#include "board.h"
#include "Console.h"

using namespace Console;

BlockControl::BlockControl(const Board& board)
    : curControlBlock(nullptr), curBoard(&board)
{
}

BlockControl::~BlockControl()
{
}

bool BlockControl::move(MoveCommand cmd)
{
    BlockState proposed = curControlBlock->propose(cmd);

    if (canMoveTo(proposed))
    {
        erase_block(*curControlBlock);
        curControlBlock->commit(proposed);
        show_block(*curControlBlock);
        return true;
    }

    return false;
}

void BlockControl::dropFull()
{
    erase_block(*curControlBlock);

    BlockState proposed = curControlBlock->propose(MoveCommand::DOWN);
    while (canMoveTo(proposed))
    {
        curControlBlock->commit(proposed);
        proposed = curControlBlock->propose(MoveCommand::DOWN);
    }

    show_block(*curControlBlock);
}

bool BlockControl::canMoveTo(const BlockState& state) const
{
    return !curBoard->isCollision(state, curControlBlock->getShape());
}
