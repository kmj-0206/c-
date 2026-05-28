<<<<<<< HEAD
#include "BlockControl.h"
=======
﻿#include "BlockControl.h"
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
#include "board.h"
#include "Console.h"

using namespace Console;

BlockControl::BlockControl(const Board& board)
<<<<<<< HEAD
    : curControlBlock(nullptr), curBoard(&board)
=======
    : curBoard(&board),
    curControlBlock(nullptr)
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
{
}

BlockControl::~BlockControl()
{
}

bool BlockControl::move(MoveCommand cmd)
{
<<<<<<< HEAD
    BlockState proposed = curControlBlock->propose(cmd);
=======
    BlockState proposed =
        curControlBlock->propose(cmd);
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f

    if (canMoveTo(proposed))
    {
        erase_block(*curControlBlock);
<<<<<<< HEAD
        curControlBlock->commit(proposed);
        show_block(*curControlBlock);
=======

        curControlBlock->commit(proposed);

        show_block(*curControlBlock);

>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
        return true;
    }

    return false;
}

void BlockControl::dropFull()
{
    erase_block(*curControlBlock);

<<<<<<< HEAD
    BlockState proposed = curControlBlock->propose(MoveCommand::DOWN);
    while (canMoveTo(proposed))
    {
        curControlBlock->commit(proposed);
        proposed = curControlBlock->propose(MoveCommand::DOWN);
=======
    BlockState proposed =
        curControlBlock->propose(MoveCommand::DOWN);

    while (canMoveTo(proposed))
    {
        curControlBlock->commit(proposed);

        proposed =
            curControlBlock->propose(
                MoveCommand::DOWN
            );
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
    }

    show_block(*curControlBlock);
}

bool BlockControl::canMoveTo(const BlockState& state) const
{
    return !curBoard->isCollision(state, curControlBlock->getShape());
<<<<<<< HEAD
=======

    
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
}
