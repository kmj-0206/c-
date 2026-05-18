#include "BlockControl.h"
#include "board.h"
#include "Console.h"

using namespace Console;

BlockControl::BlockControl(const Board& board)
    : curBoard(&board),
    curControlBlock(nullptr)
{
}

BlockControl::~BlockControl()
{
}

bool BlockControl::move(MoveCommand cmd)
{
    BlockState proposed =
        curControlBlock->propose(cmd);

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

    BlockState proposed =
        curControlBlock->propose(MoveCommand::DOWN);

    while (canMoveTo(proposed))
    {
        curControlBlock->commit(proposed);

        proposed =
            curControlBlock->propose(
                MoveCommand::DOWN
            );
    }

    show_block(*curControlBlock);
}

bool BlockControl::canMoveTo(
    const BlockState& state) const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (curControlBlock->getBlock(
                curControlBlock->getShape(),
                state.angle,
                i,
                j) == 1)
            {
                int boardX = state.x + j;
                int boardY = state.y + i;

                if (boardX < 0 ||
                    boardX >= curBoard->getBoardWidth())
                {
                    return false;
                }

                if (boardY >= curBoard->getBoardHeight())
                {
                    return false;
                }

                if (boardY >= 0)
                {
                    if (curBoard->getBoardValue(
                        boardY,
                        boardX) == 1)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}
