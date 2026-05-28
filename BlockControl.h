<<<<<<< HEAD
#pragma once
=======
﻿#pragma once
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
#include "TetrisBlock.h"

class Board;

class BlockControl
{
private:
    TetrisBlock* curControlBlock;
    const Board* curBoard;

public:
    BlockControl() = delete;
<<<<<<< HEAD
    BlockControl(const Board& board);
    ~BlockControl();

    bool move(MoveCommand cmd);
    void dropFull();
    bool canMoveTo(const BlockState& state) const;

    TetrisBlock* getCurrentBlock() { return curControlBlock; }
    void setCurrentBlock(TetrisBlock& block) { curControlBlock = &block; }
};
=======

    BlockControl(const Board& board);

    ~BlockControl();

    bool move(MoveCommand cmd);

    void dropFull();

    bool canMoveTo(const BlockState& state) const;

    TetrisBlock* getCurrentBlock() {
        return curControlBlock;
    }

    void setCurrentBlock(TetrisBlock& block) {
        curControlBlock = &block;
    }
};
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
